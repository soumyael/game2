#include <iostream>
#include "playercharacter.h"
#include "item_manager.h"

int main() {
    playercharacter p1(new warrior());
    item* fullplatemail = itemmanager::createarmor("shiny plate armor", corestats(0, 0, 0, 5, 3), ARMORSLOT::CHEST);
    item* leatherarmor = itemmanager::createarmor("plain leather armor", corestats(0, 0, 0, 2, 1), ARMORSLOT::CHEST);
    item* longsword=itemmanager::createweapon("long sword",corestats(), WEAPONSLOT::MELEE, 3, 9);
    
    itemmanager::Equip(fullplatemail, &p1);
    itemmanager::Equip(leatherarmor, &p1);
    itemmanager::Equip(longsword, &p1);


    for (int i = 0;i < 2;i++) {
        std::cout
            << p1.getclassname()
            << "level " << p1.getlevel() << '\n'
            << "-exp: " << p1.getcurrentexp() << '/' << p1.getexptonextlevel() << '\n'
            << "-hp : " << p1.getcurrenthp() << '/' << p1.getmaxhp() << '\n'
            << "-mp : " << p1.getcurrentmp() << '/' << p1.getmaxmp() << '\n'
            << "-strength: " << p1.getTotalstrength() << '\n'
            << "-intellect : " << p1.getTotalintellect() << '\n'
            << "-agility : " << p1.getTotalagility() << '\n'
            << "-armor : " << p1.getTotalarmor() << '\n'
            << "-resist : " << p1.getTotalelementres() << '\n';
        auto allabilities = p1.getabilitylist();

        std::cout << "-abilities:\n";
        for (auto& abil : allabilities) {
            std::cout << " -" << abil.Name << '\n';
        }

        std::cout << "-Armor:\n";
        for (int i = 0;i < (int)ARMORSLOT::NUM_SLOTS;i++) {
            const armor* tmp = dynamic_cast<armor*>(p1.getequippedarmorat(i));

            if (tmp) {
                std::cout << " " << tmp->Name << ",A(" << tmp->stats.armor << ") R:(" << tmp->stats.armor << ")\n";
            }
        }


        if (i < 1) {
            p1.gainexp(100u);
            Buff arm_buff("thickskin" ,0, 0, 0, 2, 2);
            p1.applybuff(arm_buff);

        }
           
    }
    std::cout << "health before taking damage: "  << p1.getcurrenthp() << '/' << p1.getmaxhp() << '\n';
    p1.takedamage(4);
    std::cout << "health after taking damage: " << p1.getcurrenthp() << '/' << p1.getmaxhp() << '\n';

    item* healpotion = itemmanager::createpotion("minor heal potion", 3u, 3u);

    itemmanager::Movetoback(healpotion, &p1);
    itemmanager::Use(healpotion,&p1);

    std::cout << "health after using potion: " << p1.getcurrenthp() << '/' << p1.getmaxhp() << '\n';
    item* rustyhandaxe = itemmanager::createweapon("rusty hand axe", corestats(), WEAPONSLOT::MELEE, 2, 4);

    itemmanager::Movetoback(
        itemmanager::createweapon("rusty hand axe", corestats(), WEAPONSLOT::MELEE, 2, 4),&p1);

    { auto inv = p1.getbackpacklist();
      std::cout << "invantory :";
      for (auto it : inv) {
       std::cout << *it << ",";
      }
      itemmanager::Use(healpotion, &p1);
      itemmanager::Use(healpotion, &p1);
    }
    { auto inv = p1.getbackpacklist();
      std::cout << "invantory(after using potions) :";
      for (auto it : inv) {
        std::cout << *it << ",";
      }
    }
    return 0;
}