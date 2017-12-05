#ifndef GAME_H_
#define GAME_H_

#include "Unit.h"
class Unit;


class Game {
public:
	enum Player {P1 = 0, P2 = 1 };
	enum UnitIds {WOLF, JAGUAR, HAWK, BAT, TURTLE, CROCODILE, BEE, QUEEN_BEE, DRAGON };
	Unit* units[2][5];

	Game(std::string file);
	virtual ~Game();

	void load(std::string file);
	bool isEnd();
	void start();

	/**
	 * You may add data members and functions to this class to help you implement the Special Moves part.
	 */
	void specialMove(Player p);
	bool isLivingMammal(Unit* unit);
	bool isLivingFlying(Unit* unit);
	bool isLivingSwimming(Unit* unit);
	bool isLivingBee(Unit* unit);
	bool isLivingQueenBee(Unit* unit);
	bool isLivingLegendary(Unit* unit);


	void biteAndScratch(Unit* unit, Unit** allies, Unit** enemies);
	void harass(Unit* unit, Unit** allies, Unit** enemies);
	void summonTsunami(Unit* unit, Unit** allies, Unit** enemies);
	void marchAndConquer(Unit* unit, Unit** allies, Unit** enemies);
	void storm(Unit* unit, Unit** allies, Unit** enemies);

	void generalKill(Unit** enemies, int amount=1);
	void generalHeal(Unit* allies, bool(&isType)(Unit*), int amount);
};

#endif /* GAME_H_ */
