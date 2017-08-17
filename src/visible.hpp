#ifndef VISIBLE_HPP
/*
 * Base klasse for alt som er synlig.
 * Har en char som representerer bildet, informasjon om elementet, metoder for å aktivere/deaktivere synlighet, beveglighet og tilgang.
*/

#define VISIBLE_HPP
#include "position.hpp"
#include <string>

class visible:public position{

	char icon_;
    std::string info_;
	bool visible_;
	bool accessable_;
	bool moveable_;
public:
    // See resources.qrc
	static const char NAKED_PLAYER='@';
	static const char ARMORED_PLAYER='A';
	static const char LOOTABLE='L';
	static const char GHOST='F';
	static const char PRIEST='R';
	static const char ELF='E';
    static const char STAIR_DOWN='D';
	static const char FLOOR='.';
    static const char STAIR_UP='U';
	static const char CHEST='C';
	static const char ARMORED_CAPE_PLAYER='P';
	static const char CREATURE_BARD='B';
	static const char CREATURE_BOSS='O';
	static const char CREATURE_GIRL='W';
	static const char CREATURE_KING='K';
	static const char CREATURE_NINJA='N';
	static const char HOUSE='H';
    static const char DEFAULT_MONSTER='M';
	static const char SKELETON='S';
	static const char TREE='T';
	static const char WALL='#';
	
	static const int NO_ACTION=0;
	static const int NEXT_LEVEL=1;
	static const int PREV_LEVEL=2;
    visible(char icon, std::string info, int x, int y);
	virtual int access()=0;//return en av konstantene
	char get_icon();
	void set_icon(char c);
	void set_visible(bool v);
	void set_accessable(bool a);
	void set_moveable(bool m);
    void set_info(std::string newinfo);
	bool is_visible();
	bool is_moveable();
	bool is_accessable();
	bool is_visible(bool v);
    virtual std::string to_string();//hva er dette?
    virtual ~visible(){}
};

#endif
