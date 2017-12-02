#ifndef BEE_H_
#define BEE_H_

#include "Unit.h"

class Bee: public Unit {
public:
	Bee(Game* game, int player, int position);
	virtual ~Bee();

	virtual void attack();

private:
	static const int MAX_HP = 15;
	static const int DEFAULT_ATK_DAMAGE = 1;
};

#endif /* BEE_H_ */
