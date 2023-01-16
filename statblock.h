#pragma once
#include <vector>
#include"types.h"
#include "buff.h"

class  statblock {
    corestats base;
    corestats frombuffs;

public : 
    
    explicit statblock(stattype s=1 , stattype i=1,stattype a=1,stattype arm=0,stattype elres=0){
        base.strength = s;
        base.intellect = i;
        base.agility = a;
        base.armor = arm;
        base.elementres = elres;
    }
    
    stattype getbasestrength() { return base.strength; }
    stattype getbaseintellect() { return base.intellect; }
    stattype getbaseagility() { return base.agility; }
    stattype getbasearmor() { return base.armor; }
    stattype getbaseelementres() { return base.elementres; }

    stattype getTotalstrength() { return base.strength + frombuffs.strength; }
    stattype getTotalintellect() { return base.intellect + frombuffs.intellect; }
    stattype getTotalagility() { return base.agility+ frombuffs.agility; }
    stattype getTotalarmor() { return base.armor+ frombuffs.armor; }
    stattype getTotalelementres() { return base.elementres+ frombuffs.elementres; }
    
   
protected :
    void addnewbuff(Buff b) {
        for (auto& buff : Buffs) {
            if (b.Name == buff.Name) {
                buff.duration = b.duration;
                return;

            }
        }
        Buffs.push_back(b);
        recalculate_buffs();
    }
    std::vector<Buff>Buffs;
    void increasestates(stattype s = 0, stattype i = 0, stattype a = 0, stattype arm = 0, stattype elres = 0) {
        base.strength += s;
        base.intellect += i;
        base.agility += a;
        base.armor += arm;
        base.elementres += elres;
    }

    void increasestates(corestats cs) {
        base += cs;
    }
private:
    void recalculate_buffs() {
        corestats tmp_total;


        for (const auto& b : Buffs) {
            if (b.isDebuff) {
                tmp_total -= b.buffedstats;

            }
            else {
                tmp_total += b.buffedstats;
            }
        }
        frombuffs = tmp_total;
    }
};
