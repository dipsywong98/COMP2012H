#ifndef GAME_H_
#define GAME_H_

#include <map>
#include "Unit.h"
#include <iostream>
#include <fstream>
using namespace std;
class Unit;

class Game {
private:
	ofstream fout;
public:
	enum Player {P1 = 0, P2 = 1 };
	enum UnitIds {WOLF, JAGUAR, HAWK, BAT, TURTLE, CROCODILE, BEE, QUEEN_BEE, DRAGON, PHOENIX };
	Unit* units[2][5];

	Game(std::string file);
	virtual ~Game();

	void load(std::string file);
	bool isEnd();
	void start();

	bool allDead(Unit** team);
	/**
	 * You may add data members and functions to this class to help you implement the Special Moves part.
	 */
	void specialMove(Player p);
	bool isLivingMammal(Unit* unit);
	bool isLivingFlying(Unit* unit);
	bool isLivingSwimming(Unit* unit);
	bool isLivingBee(Unit* unit);
	bool isLivingQueenBee(Unit* unit);
	bool isLivingAnyBee(Unit* unit);
	bool isLivingLegendary(Unit* unit);


	void generalKill(Unit** enemies, int amount=1);
	void specialMoveGeneral(bool(Game::*isType)(Unit*),void(Game::*action)(Unit*,Unit**,Unit**),Unit** allies, Unit** enemies);

	void biteAndScratch(Unit* unit, Unit** allies, Unit** enemies);
	void harass(Unit* unit, Unit** allies, Unit** enemies);
	void summonTsunami(Unit* unit, Unit** allies, Unit** enemies);
	void marchAndConquer(Unit* unit, Unit** allies, Unit** enemies);
	void weatherTheStorm(Unit* unit, Unit** allies, Unit** enemies);


	/**
	 * Console Animation Helper
	 */
	void gotoxy(int x, int y);
	ostream& xyout(int x, int y);
	ostream& stageMessage(){clearStage();return xyout(3,17);}
	ostream& log(){return xyout(3,index++);}
	std::map<Unit*,std::pair<int,int>> position;
	void console_init();
	void printUnit(Unit* u);
	void printAll();
	void clearAll(){}
	void clearStage();
	void printAttack(Unit* u);
	void printDefend(Unit* u, int delta);
	void printNumber(Unit* u, int number);
	void printText(Unit* u, string text);
	void waitNextFrame();

	int index = 18;
};

#endif /* GAME_H_ */
