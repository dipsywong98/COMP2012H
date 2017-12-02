#ifndef CROCODILE_H_
#define CROCODILE_H_

#include "Unit.h"

class Crocodile: public Unit {
public:
	Crocodile(Game* game, int player, int position);
	virtual ~Crocodile();

	virtual void attack();
	virtual void defend(Unit* opponent, int damage);
private:
	static const int MAX_HP = 30;
	static const int DEFAULT_ATK_DAMAGE = 7;
};

#endif /* CROCODILE_H_ */
