#ifndef MANTICORE_H_
#define MANTICORE_H_

#include <random>
#include "Unit.h"

class Manticore: public Unit {
public:
	Manticore(Game* game, int player, int position);
	virtual ~Manticore();

	virtual void attack();
	virtual void defend(Unit* opponent, int damage);
private:
	static const int MAX_HP = 35;
	static const int DEFAULT_ATK_DAMAGE = 0;
	static const int DAMAGE_TAKE_PERCENT = 80;
	static const int PARALYSIS_PERCENT = 40;
};

#endif /* MANTICORE_H_ */
