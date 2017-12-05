#ifndef GAME_H_
#define GAME_H_

#include <map>
#include "Unit.h"
#include <iostream>
using namespace std;
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
	void weatherTheStorm(Unit* unit, Unit** allies, Unit** enemies);

	void generalKill(Unit** enemies, int amount=1);

	/**
	 * Console Animation Helper
	 */
	void gotoxy(int x, int y);
	ostream& xyout(int x, int y);
	int active_player;
	std::map<Unit*,std::pair<int,int>> position;
	void console_init();
	void printUnit(Unit* u);
	void printAll();
	void printUnit();
	void clearAll();
	void clearStage();
	void printAttack();
	void printDefend();
};

#endif /* GAME_H_ */
