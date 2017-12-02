#ifndef BAT_H_
#define BAT_H_

#include "Unit.h"

class Bat: public Unit {
public:
	Bat(Game* game, int player, int position);
	virtual ~Bat();

	virtual void attack();
	virtual void defend(Unit* opponent, int damage);
private:
	static const int MAX_HP = 20;
	static const int DEFAULT_ATK_DAMAGE = 4;
};

#endif /* BAT_H_ */
