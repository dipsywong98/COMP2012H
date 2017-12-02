#ifndef QUEENBEE_H_
#define QUEENBEE_H_

#include "Unit.h"

class QueenBee: public Unit {
public:
	QueenBee(Game* game, int player, int position);
	virtual ~QueenBee();

	virtual void attack();
	virtual void defend(Unit* opponent, int damage);
private:
	static const int MAX_HP = 15;
	static const int DEFAULT_ATK_DAMAGE = 0;
};

#endif /* QUEENBEE_H_ */
