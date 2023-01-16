#pragma once
#include"item.h"
#include"types.h"


class itemmanager {
public:
	static item* createarmor(std::string name, corestats cstats, ARMORSLOT slot) {
		item* temp_item = new item(new armor(name, cstats, slot));
		return temp_item;
	}
	static item* createweapon(std::string name, corestats cstats, WEAPONSLOT slot, damagetype min, damagetype max, bool twohanded = false) {
		item* temp_item = new item(new weapon(name, cstats, slot, min, max, twohanded));
		return temp_item;
	}
	//makes at least one potion 
	static item* createpotion(std::string name, welltype heal=1u,itemcount quant=1u, Buff* buff = nullptr) {
		if (quant == 0)quant = 1;
		item* temp_item = new item(new potion(name, heal, (quant == 0)?1:quant, buff));
		return temp_item;

	}
	static bool Equip(item* item_to_equip,playercharacter* p_char) {
		if (!item_to_equip->getdata() || !item_to_equip|| !p_char)
			return false;

		armor* aarmor = dynamic_cast<armor*>(item_to_equip->_data);
		if (aarmor) {
			unsigned long long slot_num = (unsigned long long)aarmor->Slot;
			if (p_char->Equippedarmors[slot_num]) {
				Movetoback(p_char->Equippedarmors[slot_num], p_char);
				p_char->Equippedarmors[slot_num] = item_to_equip;
			}else {
				p_char->Equippedarmors[slot_num] = item_to_equip;
			}
			return true;
		}
		weapon* weeapon = dynamic_cast<weapon*>(item_to_equip->_data);
		if (weeapon) {
			unsigned long long slot_num = (unsigned long long)weeapon->Slot;
			if (p_char->Equippedweapons[slot_num]) {
				Movetoback(p_char->Equippedweapons[slot_num], p_char);
				p_char->Equippedweapons[slot_num] = item_to_equip;
			}
			else {
				p_char->Equippedweapons[slot_num] = item_to_equip;
			}
			return true;

		}
		return false;

	}
	static bool Use(item* item_to_use, playercharacter* p_char) {
		if (!item_to_use->getdata() || !item_to_use || !p_char)
			return false;
		potion* potio = dynamic_cast<potion*>(item_to_use->_data);
		if (potio) {
			//apply buff if it has one
			if (potio->buff) {
				p_char->applybuff(*potio->buff);
			}
			//if max health and trying to use a heal potion do not use it 
			if (p_char->pcclass->hp->isfull() && !potio->buff)
				return false;//do not use the potion 

			//increase hp by the heal amount (could be 0 and that's fine )
			p_char->pcclass->hp->increasecurrent(potio->healamount);

			//we used the potion reduce quantity 
			potio->quantity--;
			if (potio->quantity == 0) {
				item_to_use->marked_for_deletion=true;
				p_char->cleanup_backpack();
			}
			return true;
		}
		return false;
	}
	static bool Movetoback(item* item_to_move, playercharacter* p_char) {
		if (!item_to_move->getdata()|| !item_to_move|| !p_char)
			return false;
		p_char->backpack.push_back(item_to_move);
		return true;
	}

};

	
