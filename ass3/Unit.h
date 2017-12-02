/**
 *  You SHOULD NOT modify this file
 */
#ifndef UNIT_H_
#define UNIT_H_
#include <string>

#include "Game.h"
class Game;

class Unit {
public:
	virtual ~Unit();

	virtual void attack() = 0;
	virtual void defend(Unit* opponent, int damage);

	void takeDamage(int damage);
	void die();
	bool isDead() const;
	std::string getName() const;
	int getCurrentHP() const;
    int getAtkDamage() const;
protected:
	int hp;
	int atk_damage;
	bool is_dead;
	int pos;
	std::string name;
	Unit** allies;
	Unit** enemies;

	Unit(Game *game, int player, int position);


};

#endif /* UNIT_H_ */
