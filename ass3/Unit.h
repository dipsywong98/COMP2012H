/**
 *  You SHOULD NOT modify this file
 */
#ifndef UNIT_H_
#define UNIT_H_
#include <string>
#include <iostream>
#include "Game.h"

using namespace std;

class Game;

class Unit {
public:
	virtual ~Unit();

	virtual void attack() = 0;
	virtual void defend(Unit* opponent, int damage);

	void takeDamage(int damage);
	virtual void die();
	bool isDead() const;
	std::string getName() const;
	int getCurrentHP() const;
	int getAtkDamage() const;
	void poison(int amount);
	int getPoison();
	void paralysis();
	bool isParalysis();
	void resetParalysis();
	void resetPoison();
	void poisonKill();
protected:
	int hp;
	int atk_damage;
	bool is_dead;
	int pos;
	std::string name;
	Unit** allies;
	Unit** enemies;

	Unit(Game *game, int player, int position);

	int poison_level=0;
	bool is_paralysis=false;
};

#endif /* UNIT_H_ */
