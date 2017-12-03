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

	void biteAndScratch(Player p);
	void harass(Player p);
	void summonTsunami(Player p);
	void marchAndConquer(Player p);
};

#endif /* GAME_H_ */
