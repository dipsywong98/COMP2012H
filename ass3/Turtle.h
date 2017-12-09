#ifndef TURTLE_H_
#define TURTLE_H_

#include "Wolf.h"

class Turtle: public Wolf {
public:
	Turtle(Game* game, int player, int position);
	virtual ~Turtle();

	virtual void defend(Unit* opponent, int damage);
private:
	static const int MAX_HP = 35;
	static const int DEFAULT_ATK_DAMAGE = 2;
	static const int DAMAGE_TAKE_PERCENT = 50;
};

#endif /* TURTLE_H_ */
