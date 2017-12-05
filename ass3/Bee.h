#ifndef BEE_H_
#define BEE_H_

#include "Wolf.h"

class Bee: public Wolf{
public:
	Bee(Game* game, int player, int position);
	virtual ~Bee();

	virtual void specialMove();
	virtual void heal(int amount);
private:
	static const int MAX_HP = 15;
	static const int DEFAULT_ATK_DAMAGE = 1;
};

#endif /* BEE_H_ */
