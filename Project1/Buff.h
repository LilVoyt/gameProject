#pragma once
#include <iostream>
#include <string>
#include "Character.h"
#include <vector>

class Buff
{
public:
    virtual void action(Character*) = 0;
};

class IncreaseDmg : public Buff {
public:
    void action(Character* character) override {
        character->increaseDmg(10);
    }
};

class IncreaseHp: public Buff {
public:
    void action(Character* character) override {
        character->reduceHp(10);
    }
};

class KillRand : public Buff {
public:
    void action(Character* character) override {
        character->setIsAlive();
    }
};



