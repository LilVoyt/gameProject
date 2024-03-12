#include "Game.h"

void Game::showLogo() {
	cout << "Starting the game" << endl;
	Sleep(2000);
	system("cls");
}

void Game::showEnd() {
	cout << "End of the game!" << endl;
	Sleep(2000);
	system("cls");
}

void Game::printUpper() {
    cout << setw(20) << internal << "Team 1";
    cout << "\t\t\t\t\t\t\t\t";
    cout << setw(20) << internal << "Team 2" << endl;
}

Game::Game() {
    Teams teams;
    showLogo();
    int mainCount = 0;
    int secondCount = 0;
    bool site1;
    //cout << "From witch site you want to start(0 - Site 2, 1 - Site 1): " << endl;
    cout << "Choose the team: " << endl;
    cout << "[1] - Team 1, [0] - Team 2" << endl;
    cin >> site1;
    Sleep(1000);
    system("cls");
    while (teams.isAnyTeamAlive()) {
        if (mainCount >= 3) {
            mainCount = 0;
            site1 = !site1;
            ++secondCount;
            if (secondCount >= 2) {
                teams.applyRandomBuff();
                secondCount = 0;
            }
        }
        printUpper();
        teams.printField();
        teams.teamMove(site1);
        system("cls");
        mainCount++;
    }

    showEnd();
}