#pragma once
#include<string>
#include"corestats.h"
#include"types.h"
struct Buff {
    Buff(const char* name,stattype str = 0, stattype intel = 0,
        stattype agi = 0, stattype arm = 0, stattype elres = 0, uint16_t dur = 2u, bool isdebuff = false)
        : Name(name), duration(dur), isDebuff(isdebuff)
    {
        buffedstats.strength=str;
        buffedstats.intellect = intel;
        buffedstats.agility = agi;
        buffedstats.armor = arm;
        buffedstats.elementres = elres;

    }
    Buff(const char* name, corestats cs, uint16_t dur = 2u, bool isdebuff = false)
        : Name(name), duration(dur), isDebuff(isdebuff) {
        buffedstats = cs;
    }




    std::string Name;
	uint16_t duration;

    corestats buffedstats;

    bool isDebuff;
};