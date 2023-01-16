#pragma once
#include <cstdint>
#include"types.h"
class pointwell {
public:
    bool setmax(welltype new_max) {
        if (new_max < 1) 
            return false;

        maxwell = new_max;
        if (currentfullness > maxwell) 
            currentfullness = maxwell;
            return true;
        
    }
    welltype getmax() {
        return maxwell;
    }
    welltype getcurrent() {
        return currentfullness;
    }
    bool isfull() { return (currentfullness == maxwell); }
    void reducecurrent(welltype damage) {
        if (damage > currentfullness) {
            currentfullness = 0;
            return;
        }

        currentfullness -= damage;
    }
    void increasecurrent(welltype amount) {
        if (amount + currentfullness > maxwell) {
            currentfullness = maxwell;
            return;
        }
        currentfullness += amount;
    }
    pointwell() { currentfullness = 1; maxwell = 1; }
    pointwell(welltype c, welltype m) {
        currentfullness = c;
        maxwell = m;
        if (currentfullness > maxwell) {
            currentfullness = maxwell;
        }
    }
private:
    welltype currentfullness;
    welltype maxwell;

};
