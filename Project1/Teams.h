#pragma once
#include <iostream>
#include <string>
#include <windows.h>
#include "Character.h"
#include "Buff.h"
#include <vector>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <fstream>


class Teams {
private:
    vector<Character*> team1;
    vector<Character*> team2;
    vector<vector<string>> battleField; 
    vector<Buff*> buffs;

    int numHeroes;
    int teamIndex;
    int targetIndex;
    bool isAttackingTeam1; 
    int fieldRow;
    int fieldCol;

public:
    Teams();

    void printField();

    void teamMove(bool attackSite1);

    void attackHero(int attackerIndex, int targetIndex, vector<Character*>& attackingTeam, vector<Character*>& targetTeam, bool attackSite1);

    bool isAnyTeamAlive();

    void healHero(int attackerIndex, int targetIndex, bool attackSite1);

    void moveCharacter(Character* character1, Character* character2, bool attackSite1);

    void applyRandomBuff();

    void displayRules();

};
