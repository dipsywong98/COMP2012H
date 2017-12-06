#ifndef PHOENIX_H_
#define PHOENIX_H_

#include <random>
#include "Wolf.h"

class Phoenix: public Wolf {
public:
	Phoenix(Game* game, int player, int position);
	virtual ~Phoenix();

	virtual void attack();
	virtual void defend(Unit* opponent, int damage);
  virtual void die();
private:
  bool dead_before = false;
	static const int MAX_HP = 30;
	static const int DEFAULT_ATK_DAMAGE = 8;
};

#endif /* PHOENIX_H_ */
