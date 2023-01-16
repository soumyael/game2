#pragma once
#include "types.h"
#include"pointwell.h"
#include "ability.h"
#include "statblock.h"
#include "item.h"
#include<string>
#include<memory>
#include <vector>
#include <algorithm>


#define pcconstruct \
hp->setmax(BASEHP);\
hp->increasecurrent(BASEHP);\
if (mp){\
	mp->setmax(BASEMP);\
	mp->increasecurrent(BASEMP);\
}\
increasestates(BASESTR, BASEINT,BASEAGI);

#define LEVELUP \
hp->setmax((welltype)((BASEHP / 2.f) + hp->getmax()));\
hp->increasecurrent((welltype)(BASEHP / 2.f));\
if (mp){\
	mp->setmax((welltype)((BASEMP / 2.f) + hp->getmax()));\
	mp->increasecurrent((welltype)(BASEMP / 2.f));\
}\
increasestates((stattype)((BASESTR + 1u) / 2.f), (stattype)((BASEINT + 1u) / 2.f),(stattype)((BASEAGI+ 1u) / 2.f));
class playercharacterdelegate :public statblock {
public:
	
	static const exptype level2at = 100u;


	playercharacterdelegate(): statblock(0u,0u) {
		currentlevel = (leveltype) 1u;
		currentexp =(exptype) 0u;
		exptonextlevel = level2at;
		hp =std::make_unique<pointwell>(1u,1u);

	}

	void gainexp(exptype gained_exp) {
		currentexp += gained_exp;
		while (check_if_leveled()){}

	}
	leveltype getlevel() {
		return currentlevel;
	}
	exptype getcurrentexp() {
		return currentexp;
	}
	exptype getexptonextlevel() {
		return exptonextlevel;
	}
	void applyBuff(Buff b) {


		addnewbuff(b);

	}

	virtual void levelup() = 0;
	virtual std::string getclassname() = 0;
	std::unique_ptr<pointwell> hp;
	std::unique_ptr<pointwell> mp;

	std::vector<ability>abilities;
	
	

protected :
	leveltype currentlevel;
	exptype  currentexp;
	exptype exptonextlevel;

	bool check_if_leveled() {
		static const leveltype levelscalar = 2u;
		if (currentexp >= exptonextlevel){
			currentlevel++;
		    levelup();
		    exptonextlevel *= levelscalar;
			return true;
	    }
		return false; 
		
	}
};


class cleric : public playercharacterdelegate{
public:
	static const welltype BASEHP = (welltype)14u;
	static const welltype BASEMP = (welltype)10u;
	static const stattype BASESTR = (stattype)3u;
	static const stattype BASEINT = (stattype)5u;
    static const stattype BASEAGI = (stattype)1u;
	
	std::string getclassname() override { return std::string("cleric"); }\
	cleric(): playercharacterdelegate() {
		mp =std::make_unique<pointwell>(BASEMP,BASEMP);  //be sure to init before pcconstruct macro
		pcconstruct

		abilities.emplace_back("heal", 2u, 1u, ABILITYTARGET::ALLY, 2u,ABILITYSCALER::INT);
	}
private: 
	void levelup() override {
		LEVELUP
		if (currentlevel == 2) {
			abilities.emplace_back("smit", 2u, 1u, ABILITYTARGET::ENEMY, 2u, ABILITYSCALER::INT);

		}

	}
};
class wizard : public playercharacterdelegate {
public:
	static const welltype BASEHP = (welltype)10u;
	static const welltype BASEMP = (welltype)14u;
	static const stattype BASESTR = (stattype)1u;
	static const stattype BASEINT = (stattype)8u;
	static const stattype BASEAGI = (stattype)2u;

	std::string getclassname() override { return std::string("wizard"); }\
		wizard() : playercharacterdelegate() {
		mp = std::make_unique<pointwell>(BASEMP, BASEMP);  //be sure to init before pcconstruct macro
		pcconstruct
			abilities.emplace_back("firebolt", 2u, 1u, ABILITYTARGET::ENEMY, 4u, ABILITYSCALER::INT);
	}
private:
	void levelup() override {
		LEVELUP
			if (currentlevel == 2) {
				abilities.emplace_back("icebolt", 3u, 1u, ABILITYTARGET::ENEMY, 6u, ABILITYSCALER::INT);

				mp->setmax(1u + mp->getmax());
				mp->increasecurrent(1u);

				increasestates(0, 1);

			}
	}
};
class warrior : public playercharacterdelegate {
public:
	static const welltype BASEHP = (welltype)18u;
	static const welltype BASEMP = (welltype)0u;
	static const stattype BASESTR = (stattype)6u;
	static const stattype BASEINT = (stattype)2u;
	static const stattype BASEAGI = (stattype)2u;

	std::string getclassname() override { return std::string("warrior"); }\
		warrior() : playercharacterdelegate() {
		//mp = std::make_unique<pointwell>(BASEMP, BASEMP);  //be sure to init before pcconstruct macro
		pcconstruct
			
	}
private:
	void levelup() override {
		LEVELUP
			if (currentlevel == 2) {
				abilities.emplace_back("powerattack", 0u, 3u, ABILITYTARGET::ENEMY, 4u, ABILITYSCALER::STR);

			}
	}
};
class rogue : public playercharacterdelegate {
public:
	static const welltype BASEHP = (welltype)18u;
	static const welltype BASEMP = (welltype)0u;
	static const stattype BASESTR = (stattype)6u;
	static const stattype BASEINT = (stattype)2u;
	static const stattype BASEAGI = (stattype)2u;

	std::string getclassname() override { return std::string("rogue"); }\
		rogue() : playercharacterdelegate() {
		//mp = std::make_unique<pointwell>(BASEMP, BASEMP);  //be sure to init before pcconstruct macro
		pcconstruct

	}
private:
	void levelup() override {
		LEVELUP
			if (currentlevel == 2) {
				abilities.emplace_back("preciseattack", 0u, 3u, ABILITYTARGET::ENEMY, 4u, ABILITYSCALER::STR);

			}
	}
};


class playercharacter {
private :
	playercharacterdelegate* pcclass;
	item* Equippedarmors[(unsigned long long)ARMORSLOT::NUM_SLOTS];
	item* Equippedweapons[(unsigned long long)WEAPONSLOT::NUM_SLOTS];
	std::vector <item*> backpack;
	void cleanup_backpack(){
		const auto to_remove = std::stable_partition(backpack.begin(), backpack.end(),
			[](const item* i)->bool {return !i->getmarkfordeletion();}
		);
		std::for_each(to_remove, backpack.end(), [](item* pi) {delete pi;});
		backpack.erase(to_remove, backpack.end());
	}
	friend class itemmanager;
public :
	
	playercharacter(playercharacterdelegate*pc):pcclass(pc){
		auto i = 0;
		for (i=0; i < (unsigned long long) ARMORSLOT::NUM_SLOTS;i++) {
			Equippedarmors[i] = nullptr;

		}
		for (i = 0;i < (unsigned long long)WEAPONSLOT::NUM_SLOTS;i++) {
			Equippedweapons[i] = nullptr;
		}
	
	}
	~playercharacter() { 
		delete pcclass;
		pcclass = nullptr;
		auto i = 0;
		for (i = 0; i < (unsigned long long) ARMORSLOT::NUM_SLOTS;i++) {
			if (Equippedarmors[i]) {
				delete Equippedarmors[i];
				Equippedarmors[i] = nullptr;

			}
		}
		for (i = 0; i < (unsigned long long) WEAPONSLOT::NUM_SLOTS;i++) {
			if (Equippedweapons[i]) {
				delete Equippedweapons[i];
				Equippedweapons[i] = nullptr;

			}
		}
	}
	//getters
	std::string getclassname() const { return pcclass->getclassname(); }
	leveltype getlevel() const {return pcclass->getlevel();}
	exptype getcurrentexp() const {return pcclass->getcurrentexp(); }
	exptype getexptonextlevel() const {return pcclass->getexptonextlevel(); }
	welltype getcurrenthp()const {return pcclass->hp->getcurrent(); }
	welltype getmaxhp() const {return pcclass->hp->getmax(); }

	welltype getcurrentmp()const  { 
		if (pcclass->mp)
			return pcclass->mp->getcurrent();
		else
			return 0;
	}
	welltype getmaxmp()const  {
		if (pcclass->mp)
			return pcclass->mp->getmax();
		else
			return 0;
	}

	stattype getbasestrength() const {return pcclass->getbasestrength(); }
	stattype getbaseintellect() const {return pcclass->getbaseintellect(); }
	stattype getbaseagility() const  { return pcclass->getbaseagility(); }
	stattype getbasearmor() const { return pcclass->getbasearmor(); }
	stattype getbaseelementres() const { return pcclass->getbaseelementres(); }

	stattype getTotalstrength()const  {
		stattype str_from_armor = 0;
		for (auto i = 0; i < (unsigned long long) ARMORSLOT::NUM_SLOTS;i++) {
			if (Equippedarmors[i]) {
				armor* aarmor = dynamic_cast <armor*>(Equippedarmors[i]->_data);
				str_from_armor += aarmor->stats.strength;
			}
		}
		stattype str_from_weapons = 0;
		for (auto i = 0; i < (unsigned long long) WEAPONSLOT::NUM_SLOTS;i++) {
			if (Equippedweapons[i]) {
				weapon* weapeen = dynamic_cast <weapon*>(Equippedweapons[i]->_data);
				str_from_weapons += weapeen->stats.strength;
			}
		}
		return pcclass-> getTotalstrength()+ str_from_armor+ str_from_weapons;
	}
	stattype getTotalintellect() {
		stattype int_from_armor = 0;
		for (auto i = 0; i < (unsigned long long) ARMORSLOT::NUM_SLOTS;i++) {
			if (Equippedarmors[i]) {
				armor* aarmor = dynamic_cast <armor*>(Equippedarmors[i]->_data);
				int_from_armor += aarmor->stats.intellect;
			}
		}
		stattype int_from_weapons = 0;
		for (auto i = 0; i < (unsigned long long) WEAPONSLOT::NUM_SLOTS;i++) {
			if (Equippedweapons[i]) {
				weapon* weapeen = dynamic_cast <weapon*>(Equippedweapons[i]->_data);
				int_from_weapons += weapeen->stats.intellect;
			}
		}
		return pcclass->getTotalintellect()+ int_from_armor+ int_from_weapons;
	}
	stattype getTotalagility()const  {
		stattype agil_from_armor = 0;
		for (auto i = 0; i < (unsigned long long) ARMORSLOT::NUM_SLOTS;i++) {
			if (Equippedarmors[i]) {
				armor* aarmor = dynamic_cast <armor*>(Equippedarmors[i]->_data);
				agil_from_armor += aarmor->stats.agility;
			}
		}
		stattype agil_from_weapons = 0;
		for (auto i = 0; i < (unsigned long long) WEAPONSLOT::NUM_SLOTS;i++) {
			if (Equippedweapons[i]) {
				weapon* weapeen = dynamic_cast <weapon*>(Equippedweapons[i]->_data);
				agil_from_weapons += weapeen->stats.agility;
			}
		}
		return pcclass->getTotalagility()+ agil_from_armor + agil_from_weapons;
	}
	stattype getTotalarmor()const  {
		//get all armor from equipped armor
		stattype armor_from_armor = 0;
		for (auto i = 0; i < (unsigned long long) ARMORSLOT::NUM_SLOTS;i++) {
			if (Equippedarmors[i]) {
				armor* aarmor =dynamic_cast <armor*>(Equippedarmors[i]->_data);
				armor_from_armor +=aarmor->stats.armor;
			}
		}
		stattype armor_from_weapons = 0;
		for (auto i = 0; i < (unsigned long long) WEAPONSLOT::NUM_SLOTS;i++) {
			if (Equippedweapons[i]) {
				weapon* weapeen = dynamic_cast <weapon*>(Equippedweapons[i]->_data);
				armor_from_weapons += weapeen->stats.armor;
			}
		}
		return pcclass->getTotalarmor()+ armor_from_armor + armor_from_weapons;
	}
	stattype getTotalelementres()const  {
		stattype resist_from_armor = 0;
		for (auto i = 0; i < (unsigned long long) ARMORSLOT::NUM_SLOTS;i++) {
			if (Equippedweapons[i]) {
			armor* aarmor = dynamic_cast <armor*>(Equippedarmors[i]->_data);
			resist_from_armor += aarmor->stats.elementres;
			}
		}
		stattype elres_from_weapons = 0;
		for (auto i = 0; i < (unsigned long long) WEAPONSLOT::NUM_SLOTS;i++) {
			if (Equippedweapons[i]) {
				weapon* weapeen = dynamic_cast <weapon*>(Equippedweapons[i]->_data);
				elres_from_weapons += weapeen->stats.elementres;
			}
		}

		return pcclass->getTotalelementres()+ resist_from_armor+ elres_from_weapons;
	}

	const std::vector<ability> getabilitylist() const { return pcclass->abilities; }
	//const std::vector<Buff> getbufflist()const { return pcclass->getbufflist(); }
	const std::vector<item*>getbackpacklist() const{ return backpack;}
	Equipmentdelegate* getequippedarmorat (unsigned long long i)const  {
		if(!Equippedarmors[i] )return nullptr;
		return (dynamic_cast<armor*> (Equippedarmors[i]->_data)); 
	}

	Equipmentdelegate* getequippedweaponat(unsigned long long i)const  {
		if (!Equippedweapons[i]) return nullptr;
		return (dynamic_cast<weapon*> (Equippedweapons[i]->_data));
	}

	//modifiers
	void gainexp(exptype amt) { pcclass->gainexp(amt);}
	void takedamage(welltype amt) { pcclass->hp->reducecurrent(amt); }
	void heal(welltype amt) { pcclass->hp->increasecurrent(amt); }
	void applybuff(Buff buff) {
		pcclass->applyBuff(buff);
	}

	//deleted constructors
	playercharacter() = delete;
	playercharacter(const playercharacter&) = delete;
	playercharacter(const playercharacter&&) = delete;
};