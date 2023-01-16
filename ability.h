#pragma once
#include<cstdint>
#include<string>

enum class ABILITYTARGET { SELF, ALLY,ENEMY };
enum class ABILITYSCALER { NONE, STR, AGI,INT };

struct ability {
	ability (std::string name,uint32_t cost ,uint32_t cd, ABILITYTARGET t, uint32_t hpe ,ABILITYSCALER s ):
		Name(name),Cost(cost),Cooldown(cd),Target(t),Hpeffect(hpe),scaler(s) {}

	std::string Name="unnamed";
	uint32_t Cost=0;
	uint32_t Cooldown=1;
	ABILITYTARGET Target=ABILITYTARGET::SELF;
	uint32_t Hpeffect=1;
	ABILITYSCALER scaler = ABILITYSCALER::NONE;

	
};