#pragma once
#include"types.h"

struct corestats {
    stattype strength = 0;
    stattype intellect = 0;
    stattype agility = 0;
    stattype armor = 0;
    stattype elementres = 0;

    corestats() {
    stattype strength = 0;
    stattype intellect = 0;
    stattype agility = 0;
    stattype armor = 0;
    stattype elementres = 0;
    }
    corestats(stattype s, stattype i, stattype ag, stattype arm, stattype eres)
        : strength(s), intellect(i), agility(ag), armor(arm), elementres(eres) {

    }

    corestats& operator+=(const corestats& rhs) {
        this->strength += rhs.strength;
        this->intellect += rhs.intellect;
        this->agility += rhs.agility;
        this->armor += rhs.armor;
        this->elementres += rhs.elementres;
        return *this;

    };
    corestats& operator-=(const corestats& rhs) {
        corestats tmp = *this;

        this->strength -= rhs.strength;
        this->intellect -= rhs.intellect;
        this->agility -= rhs.agility;
        this->armor -= rhs.armor;
        this->elementres -= rhs.elementres;
        if (this->strength > tmp.strength) this->strength = 0u;
        if (this->intellect > tmp.intellect) this->intellect = 0u;
        if (this->agility > tmp.agility) this->agility = 0u;
        if (this->armor > tmp.armor) this->armor = 0u;
        if (this->elementres > tmp.elementres) this->elementres = 0u;
        return *this;

    };
    corestats& operator=(const stattype& rhs) {
        this->strength = rhs;
        this->intellect = rhs;
        this->agility = rhs;
        this->armor = rhs;
        this->elementres = rhs;
        return *this;
    }

};