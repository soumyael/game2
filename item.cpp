#include"item.h"
//don't touch this only the Equipmentdelegate constructer should touch this 
static std::uint32_t EQUIPMENTUNIQUEIDITERATOR=0u;
Equipmentdelegate::Equipmentdelegate(std::string name, corestats cstats)
	:itemdelegate(name), stats(cstats), uniqueid(++EQUIPMENTUNIQUEIDITERATOR) {}

