#pragma once
#include<string>
#include<typeinfo>
#include"corestats.h"
#include"buff.h"



class itemdelegate {
public :
	std::string Name;
	virtual const char* gettype() = 0;
	
protected:
	
	itemdelegate(std::string name):Name(name){}
};
#define GETTYPE const char* gettype() override { return typeid(*this).name(); };

class potion final :public itemdelegate {
public:
	Buff* buff;
	welltype healamount;
	itemcount quantity;
	
	~potion() {
		if (buff) {
			delete buff;
			buff = nullptr;
		}
	}
	GETTYPE

private:
	potion(std::string name, welltype hp_heal = 1u,itemcount quant=1u ,Buff * buf = nullptr)
		:itemdelegate(name),buff(buf),healamount(hp_heal),quantity(quant) {}
	friend class itemmanager;
};




class Equipmentdelegate : public itemdelegate{
public:
	const std::uint32_t uniqueid;
	corestats stats;
protected:
	Equipmentdelegate(std::string name, corestats cstats);
private:
};


enum class ARMORSLOT{HELMET,CHEST,LEGS,BOOTS,GLOVES,RING1,RING2,NECK,NUM_SLOTS};// NUM SLOT for making arrays of armor slots 
class armor final :public Equipmentdelegate {
public:
	ARMORSLOT Slot;
	armor(std::string name, corestats cstats, ARMORSLOT slot) : Equipmentdelegate(name, cstats), Slot(slot) {}
    GETTYPE
private:
	
	armor() = delete;
	armor(const armor&) = delete;
	armor(const armor&&) = delete;
	friend class itemmanger;
};
enum class WEAPONSLOT { MELEE,RANGED,NUM_SLOTS };
class weapon final :public Equipmentdelegate {
public:
	WEAPONSLOT Slot;
	damagetype mindamage;
	damagetype maxdamage;
	bool is2H;
    GETTYPE
private:
	weapon(std::string name, corestats cstats, WEAPONSLOT slot, damagetype min,damagetype max,bool twohanded=false)
		: Equipmentdelegate(name, cstats), Slot(slot) , mindamage(min),maxdamage(max), is2H(twohanded) {
	}
	
	weapon() = delete;
	weapon(const weapon&) = delete;
	weapon(const weapon&&) = delete;
	friend class itemmanager;
};
//use this one in your runtime
#include<iostream>
class item {
public:
	const itemdelegate* getdata() { return _data; }
	~item() {
		if (_data) {
			delete _data;
			_data = nullptr;
		}
		
	}
	bool getmarkfordeletion() const { return marked_for_deletion; };

private:
	itemdelegate* _data;
	bool marked_for_deletion = false;
	item(itemdelegate* iitem) :_data(iitem) {}
	friend class itemmanager;
	friend class playercharacter;
	friend std::ostream& operator<<(std::ostream& os, const item& t) {
		armor* tmp_cast = dynamic_cast<armor*>(t._data);
		if (tmp_cast) {
			return os << tmp_cast->Name << "(Armor: " << tmp_cast->stats.armor << ", resist " << tmp_cast->stats.elementres << ')';
		}
		weapon* tmp_cast2 = dynamic_cast<weapon*>(t._data);
		if (tmp_cast2) {
			return os << tmp_cast2->Name << "(damage: " << tmp_cast2->mindamage << "- " << tmp_cast2->maxdamage << ')';
		}
		potion* tmp_cast3 = dynamic_cast<potion*>(t._data);
		if (tmp_cast) {
			return os << tmp_cast->Name << "(" << tmp_cast3->quantity << ')';
		}
		return os;

	}
	
};


