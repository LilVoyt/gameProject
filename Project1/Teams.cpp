#include "Teams.h"

Teams::Teams() : numHeroes{ 5 }, teamIndex{ 0 }, targetIndex{ 0 }, isAttackingTeam1{ 0 }, fieldRow{ 5 }, fieldCol{ 5 } {

	team1 = { new Barbarian("White Barbarian", 0), new Archer("White Archer", 0), new Wizard("White Wizard", 0), new King("White King", 0), new Heal("White Heal", 0) };
	team2 = { new Barbarian("Black Barbarian", 4), new Archer("Black Archer", 4), new Wizard("Black Wizard", 4), new King("Black King", 4), new Heal("Black Heal", 4) };

	battleField.resize(fieldRow, std::vector<string>(fieldCol, "-"));

	for (int i = 0; i < numHeroes; ++i) {
		battleField[i][0] = team1[i]->getIcon();
		battleField[i][4] = team1[i]->getIcon();
	}
	buffs = { new IncreaseDmg(), new IncreaseHp(), new KillRand() };
}

void Teams::printField() {

	const int BLUE_COLOR = 9;
	const int BROWN_COLOR = 6;
	const int WHITE_COLOR = 15;

	for (int i = 0; i < numHeroes; i++) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLUE_COLOR);
		team1[i]->printCharacter();
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE_COLOR);
		for (int j = 0; j < fieldCol; j++) {
			if (j == fieldCol - 1) {
				cout << setw(5) << internal << battleField[i][j] << "\t\t";
			}
			else {
				cout << setw(5) << internal << battleField[i][j];
			}
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BROWN_COLOR);
		team2[i]->printCharacter();
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE_COLOR);
		cout << endl;
	}
}


void Teams::teamMove(bool attackSite1) {
	cout << "Navigation: ([1] - attack, [2] - moove, [3] - heal), [4] - rules, [5] - exit" << endl;
	cout << "Now, you attacking by: ";
	cout << (attackSite1 ? "Team 1" : "Team 2") << endl;
	int choose;
	cin >> choose;
	switch (choose) {
	case 1:

		cout << "Choose attacker index: ";
		cin >> teamIndex;

		cout << "Choose the target: ";
		cin >> targetIndex;

		attackHero(teamIndex, targetIndex, team1, team2, attackSite1);

		break;
	case 2:

		cout << "Choose mooving hero index: ";
		cin >> teamIndex;

		if ((team1[teamIndex]->getNumSteps()) + (team2[teamIndex]->getNumSteps()) < 3) {
			moveCharacter(team1[teamIndex], team2[teamIndex], attackSite1);
		}
		else {
			cout << "Can't moove" << endl;
			teamMove(attackSite1);
		}
		break;
	case 3:

		cout << "Choose healer index: ";
		cin >> teamIndex;

		cout << "Choose hero index to heal: ";
		cin >> targetIndex;
		healHero(teamIndex, targetIndex, attackSite1);
		return;
	case 4:
		displayRules();
		cout << endl;
		_getch();
		cout << endl;
		teamMove(attackSite1);
		return;
	case 5:
		cout << "Are you sure you want to leave?";
		bool isLeave;
		cin >> isLeave;
		if (isLeave) {
			cout << "Exiting the program." << endl;
			Sleep(1000);
			exit(0);
		}
		else {
			teamMove(attackSite1);
		}
	default:
		cout << "Wrong choose!" << endl;
	}
}



void Teams::attackHero(int attackerIndex, int targetIndex, vector<Character*>& team1, vector<Character*>& team2, bool attackSite1) {
	if (attackerIndex >= 0 && attackerIndex < numHeroes && targetIndex >= 0 && targetIndex < numHeroes) {
		if (attackSite1) {
			if (team2[targetIndex]->getIsAlive() && team1[attackerIndex]->getIsAlive()) {
				team1[attackerIndex]->Attack(team2[targetIndex]);
				cout  << team1[attackerIndex]->getName() << " attacking " << team2[targetIndex]->getName() << "!" << endl;
			}
			else {
				cout << "Target hero / attacker is already dead. Choose another target." << endl;
				cout << "-----------------------------------------------" << endl;
				cout << endl;
				teamMove(attackSite1);
			}
		}
		else {
			if (team1[targetIndex]->getIsAlive() && team2[attackerIndex]->getIsAlive()) {
				team2[targetIndex]->Attack(team1[targetIndex]);
				cout << team2[attackerIndex]->getName() << " attacking " << team1[targetIndex]->getName() << "!" << endl;
			}
			else {
				cout << "Target hero / attacker is already dead. Choose another target." << endl;
				cout << "-----------------------------------------------" << endl;
				cout << endl;
				teamMove(attackSite1);
			}
		}
	}
	else {
		cout << "Invalid hero index. Please choose a valid hero." << endl;
		cout << "-----------------------------------------------" << endl;
		cout << endl;
		teamMove(attackSite1);
	}
	Sleep(2000);
}

void Teams::healHero(int attackerIndex, int targetIndex, bool attackSite1) {
	if (attackerIndex >= 0 && attackerIndex < numHeroes && targetIndex >= 0 && targetIndex < numHeroes) {
		if (attackSite1) {
			if (team1[targetIndex]->getIsAlive() && team1[attackerIndex]->getIsAlive()) {
				team1[attackerIndex]->HealTeammate(team1[targetIndex]);
				cout << team2[targetIndex]->getName() << " healing by: " << team1[attackerIndex]->getName() << "!" << endl;
			}
			else {
				cout << "Target hero / attacker is already dead. Choose another target." << endl;
				cout << "-----------------------------------------------" << endl;
				cout << endl;
				teamMove(attackSite1);

			}
		}
		else {
			if (team2[targetIndex]->getIsAlive()) {
				team2[attackerIndex]->HealTeammate(team2[targetIndex]);
				cout << team1[targetIndex]->getName() << " healing by: " << team2[attackerIndex]->getName() << "!" << endl;
			}
			else {
				cout << "Target hero / attacker is already dead. Choose another target." << endl;
				cout << "-----------------------------------------------" << endl;
				cout << endl;
				teamMove(attackSite1);
			}
		}
	}
	else {
		cout << "Invalid hero index. Please choose a valid hero." << endl;
		cout << "-----------------------------------------------" << endl;
		cout << endl;
		teamMove(attackSite1);
	}

	Sleep(2000);

}

bool Teams::isAnyTeamAlive() {
	bool isTeam1Alive = false;
	bool isTeam2Alive = false;

	for (int i = 0; i < numHeroes; ++i) {
		if (team1[i]->getIsAlive()) {
			isTeam1Alive = true;
			break;
		}
	}

	for (int i = 0; i < numHeroes; ++i) {
		if (team2[i]->getIsAlive()) {
			isTeam2Alive = true;
			break;
		}
	}

	return isTeam1Alive && isTeam2Alive;
}

void Teams::moveCharacter(Character* character1, Character* character2, bool attackSite1) {
	if (attackSite1) {
		battleField[character1->getRow()][character1->getSpot()] = "-";
		character1->moveForward(attackSite1);
		battleField[character1->getRow()][character1->getSpot()] = character1->getIcon();
		character1->increaseSteps();
		character1->setDamage(character1);
		character2->setDamage(character2);
		cout << character1->getName() << " will stay at " << character1->getSpot() << " spot" << endl;
	}
	else {
		battleField[character2->getRow()][character2->getSpot()] = "-";
		character2->moveForward(attackSite1);
		battleField[character2->getRow()][character2->getSpot()] = character2->getIcon();
		character2->increaseSteps();
		character2->setDamage(character2);
		character1->setDamage(character1);
		cout << character2->getName() << " will stay at " << character2->getSpot() << " spot" << endl;
	}
	Sleep(3000);
}


void Teams::applyRandomBuff() {
	buffs[rand() % buffs.size()]->action(team1[rand() % numHeroes]);
	buffs[rand() % buffs.size()]->action(team2[rand() % numHeroes]);
	cout << "Random buff added!" << endl;
}

void Teams::displayRules() {
	ifstream rulesFile("rules.txt");

	try {
		if (!rulesFile.is_open()) {
			throw runtime_error("Unable to open rules file!");
		}

		string rule;
		cout << "Rules:" << endl;
		while (getline(rulesFile, rule)) {
			cout << rule << endl;
		}

		rulesFile.close();
	}
	catch (const exception& e) {
		cerr << "Error: " << e.what() << endl;
	}
}