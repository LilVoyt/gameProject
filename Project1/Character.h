#pragma once
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Character
{
private:
	string icon;
	string name;
	int hp;
	int maxHp;
	int dmg;
	bool isAlive;
	int witchRow;
	int spot;
	int numSteps;

public:
	Character(string _icon, string _name, int _hp, int _dmg, int _witchRow, int _spot) : 
		icon(_icon), name(_name), hp(_hp), dmg(_dmg), isAlive(true), witchRow(_witchRow), spot(_spot), numSteps(0){
		maxHp = _hp;
	}

	virtual void Attack(Character* hero) = 0;

	virtual void setDamage(Character* hero) = 0;

	virtual void HealTeammate(Character* target) {
		cout << "Cannot heal players." << endl;
	}

	void printCharacter() const;

	void reduceHp(int _dmg);

	void increaseDmg(int multiply);

	void setIsAlive();

	void increaseHp(int _hp);

	void increaseSteps();

	void moveForward(bool attackSite1);

	bool getIsAlive() const {
		return isAlive;
	}

	int getDmg() const {
		return dmg;
	}

	string getName() const {
		return name;
	}

	string getIcon(){
		return icon;
	}

	int getRow() {
		return witchRow;
	}

	int getSpot() {
		return spot;
	}

	int getNumSteps() {
		return numSteps;
	}

};

class Barbarian : public Character {
public:
	Barbarian(string _name, int _spot) : Character("B", _name, 100, 30, 0, _spot){}
	void Attack(Character* hero) override {
		hero->reduceHp(getDmg());
	}
	void setDamage(Character* hero) override {
		hero->increaseDmg(20);
	}
};

class Archer : public Character {
public:
	Archer(string _name, int _spot) : Character("A", _name, 80, 15, 1, _spot) {}
	void Attack(Character* hero) override {
		hero->reduceHp(getDmg());
	}
	void setDamage(Character* hero) override {
		hero->increaseDmg(10);
	}
};

class Wizard : public Character {
public:
	Wizard(string _name, int _spot) : Character("W", _name, 90, 20, 2, _spot) {}
	void Attack(Character* hero) override {
		hero->reduceHp(getDmg());
	}
	void setDamage(Character* hero) override {
		hero->increaseDmg(30);
	}
};

class King : public Character {
public:
	King(string _name, int _spot) : Character("K", _name, 150, 40, 3, _spot) {}
	void Attack(Character* hero) override {
		hero->reduceHp(getDmg());
	}
	void setDamage(Character* hero) override {
		hero->increaseDmg(50);
	}
};

class Heal: public Character {
private:
	int healAbility;
public:
	Heal(string _name, int _spot) : Character("H", _name, 150, 40, 4, _spot), healAbility{ 30 } {}
	void Attack(Character* hero) override {
		hero->reduceHp(getDmg());
	}
	void HealTeammate(Character* hero) override {
		if (hero != nullptr) {
			hero->increaseHp(healAbility);
		}
		else {
			cout << "Error!" << endl;
		}
	}
	void setDamage(Character* hero) override {
		hero->increaseDmg(1);
	}
};