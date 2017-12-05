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
	bool isMammal(Unit* unit);
	bool isFlying(Unit* unit);
	bool isSwimming(Unit* unit);
	bool isBee(Unit* unit);
	bool isQueenBee(Unit* unit);
};

#endif /* GAME_H_ */
