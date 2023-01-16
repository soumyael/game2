#pragma once
class cleric : public playercharacterdelegate {
public:
	static const welltype BASEHP = (welltype)14u;
	static const stattype BASESTR = (stattype)2u;
	static const stattype BASEINT = (stattype)3u;

	std::string getclassname() override { return std::string("cleric"); }
	cleric()pcconstruct



private:
	LEVELUP
};
class rogue : public playercharacterdelegate {
public:
	static const welltype BASEHP = (welltype)12u;
	static const stattype BASESTR = (stattype)3u;
	static const stattype BASEINT = (stattype)2u;

	std::string getclassname() override { return std::string("rogue"); }
	rogue() pcconstruct



private:
	LEVELUP
};
class warrior : public playercharacterdelegate {
public:
	static const welltype BASEHP = (welltype)18u;
	static const stattype BASESTR = (stattype)4u;
	static const stattype BASEINT = (stattype)1u;

	std::string getclassname() override { return std::string("warrior"); }
	warrior() pcconstruct



private:
	LEVELUP
};
class wizard : public playercharacterdelegate {
public:
	static const welltype BASEHP = (welltype)10u;
	static const stattype BASESTR = (stattype)1u;
	static const stattype BASEINT = (stattype)4u;

	std::string getclassname() override { return std::string("wizard"); }
	wizard() pcconstruct



private:
	LEVELUP
};




stattype basestrength;
stattype baseintellect;
stattype baseagility;
stattype basearmor;
stattype baseelementres;

stattype Totalstrengthfrombuffs = 0;
stattype Totalintellectfrombuffs = 0;
stattype Totalagilityfrombuffs = 0;
stattype Totalarmorfrombuffs = 0;
stattype Totalelementresfrombuffs = 0;