#ifndef MANTICORE_H_
#define MANTICORE_H_

#include <random>
#include "Wolf.h"

class Manticore: public Wolf {
public:
	Manticore(Game* game, int player, int position);
	virtual ~Manticore();

	virtual void attack();
	virtual void defend(Unit* opponent, int damage);
private:
	static const int MAX_HP = 30;
	static const int DEFAULT_ATK_DAMAGE = 0;
};

#endif /* MANTICORE_H_ */
