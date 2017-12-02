#ifndef TURTLE_H_
#define TURTLE_H_

#include "Unit.h"

class Turtle: public Unit {
public:
	Turtle(Game* game, int player, int position);
	virtual ~Turtle();

	virtual void attack();
	virtual void defend(Unit* opponent, int damage);
private:
	static const int MAX_HP = 35;
	static const int DEFAULT_ATK_DAMAGE = 2;
};

#endif /* TURTLE_H_ */
