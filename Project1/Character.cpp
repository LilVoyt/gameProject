#include "Character.h"

void Character::printCharacter() const {
	if (isAlive) {	
		cout << setw(40) << left << icon + " " + name + " " + to_string(hp) + " / (" + to_string(maxHp)+") " + " hp.";
	}
	else {
		cout << setw(40) << left << "Dead: " + icon + " " + name;
	}

}

void Character::reduceHp(int _dmg) {
	hp -= _dmg;
	if (hp < 0) {
		isAlive = false;
	}
}

void Character::increaseHp(int _hp) {
	hp += _hp;
	if (hp > maxHp) {
		hp = maxHp;
	}
}

void Character::moveForward(bool attackSite1) {
	if (attackSite1) {
		++spot;
	}
	else {
		--spot;
	}
}

void Character::increaseSteps() {
	++numSteps;
}

void Character::increaseDmg(int multiply) {
	dmg = dmg + ((dmg * multiply)/100);
}

void Character::setIsAlive() {
	if (isAlive) {
		isAlive = false;
		hp = 0;
	}
}