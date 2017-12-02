#ifndef JAGUAR_H_
#define JAGUAR_H_

#include "Unit.h"

class Jaguar: public Unit {
public:
	Jaguar(Game* game, int player, int position);
	virtual ~Jaguar();

	virtual void attack();

private:
	static const int MAX_HP = 25;
	static const int DEFAULT_ATK_DAMAGE = 6;
};

#endif /* JAGUAR_H_ */
