#ifndef HAWK_H_
#define HAWK_H_

#include "Wolf.h"

class Hawk: public Wolf {
public:
	Hawk(Game* game, int player, int position);
	virtual ~Hawk();

	virtual void attack();
	virtual void defend(Unit* opponent, int damage);
private:
	static const int MAX_HP = 25;
	static const int DEFAULT_ATK_DAMAGE = 5;
};

#endif /* HAWK_H_ */
