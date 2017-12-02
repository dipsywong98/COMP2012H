#ifndef WOLF_H_
#define WOLF_H_

#include "Unit.h"

class Wolf: public Unit {
public:
	Wolf(Game* game, int player, int position);
	virtual ~Wolf();

	virtual void attack();

private:
	static const int MAX_HP = 30;
	static const int DEFAULT_ATK_DAMAGE = 5;
};

#endif /* WOLF_H_ */
