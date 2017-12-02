#ifndef DRAGON_H_
#define DRAGON_H_

#include "Unit.h"

class Dragon: public Unit {
public:
	Dragon(Game* game, int player, int position);
	virtual ~Dragon();

	virtual void attack();
	virtual void defend(Unit* opponent, int damage);
private:
	static const int MAX_HP = 40;
	static const int AREA_ATK_DAMAGE = 4;
	static const int SINGLE_ATK_DAMAGE = 4;

	void areaAttack();
	void singleAttack();
};

#endif /* DRAGON_H_ */
