#include <iostream>
#include <fstream>

#include "Game.h"
#include "Wolf.h"
#include "Jaguar.h"
#include "Hawk.h"
#include "Bat.h"
#include "Turtle.h"
#include "Crocodile.h"
#include "Bee.h"
#include "QueenBee.h"
#include "Dragon.h"

using namespace std;

Game::Game(std::string file) {
	load(file);
}

Game::~Game() {
	for(int i = 0; i < 10; i++)
		delete units[i/5][i%5];
}

/**
 * You should instantiate the unit objects here
 * Please refer to the example of "Wolf" 
 */
void Game::load(std::string file)
{
	ifstream in(file.c_str());
	int c = 0;
	int id;
	while(in >> id)
	{
		switch(id)
		{
		case WOLF:
			units[c/5][c%5] = new Wolf(this, c/5, c%5);
			break;
		case JAGUAR:
		units[c/5][c%5] = new Jaguar(this, c/5, c%5);
			break;
		case HAWK:
		units[c/5][c%5] = new Hawk(this, c/5, c%5);
			break;
		case BAT:
		units[c/5][c%5] = new Bat(this, c/5, c%5);
			break;
		case TURTLE:
		units[c/5][c%5] = new Turtle(this, c/5, c%5);
			break;
		case CROCODILE:
		units[c/5][c%5] = new Crocodile(this, c/5, c%5);
			break;
		case BEE:
		units[c/5][c%5] = new Bee(this, c/5, c%5);
			break;
		case QUEEN_BEE:
		units[c/5][c%5] = new QueenBee(this, c/5, c%5);
			break;
		case DRAGON:
		units[c/5][c%5] = new Dragon(this, c/5, c%5);
			break;
		}

		c++;
	}

}

/**
 * Do NOT modify this function
 */
bool Game::isEnd()
{
	int deadCount1 = 0;
	int deadCount2 = 0;
	for(int i = 0; i < 5; i++)
	{
		deadCount1 += units[P1][i]->isDead();
		deadCount2 += units[P2][i]->isDead();
	}

	if(deadCount1 == 5 && deadCount2 == 5)
	{
		cout << "Draws!" << endl;
	}else if (deadCount1 == 5)
	{
		cout << "Player " << P2+1 << " Wins!" << endl;
	} else if (deadCount2 == 5)
	{
		cout << "Player " << P1+1 << " Wins!" << endl;
	} else {
		return false;
	}
	return true;

}

void Game::start()
{
	Player currentPlayer = P1;
	int turnCount = 1;
	while(!isEnd())
	{
		for(int i = 0; i < 5; i++)
		{
			if(!units[currentPlayer][i]->isDead())
				units[currentPlayer][i]->attack();
		}

		/**
		 * To-Do 2: Codes for Special moves (if any) should be written here
		 * Hint: You should use dynamic binding, you may add data members/ functions in the Game class to help you implement this part
		 */

		// specialMove(currentPlayer);

		//Output turn info
		cout << "Turn " << turnCount++ << " Player " << currentPlayer+1 << " attacks:" << endl;
		cout << "Player 1" << endl;
		for(int i = 0; i < 5; i++)
		{
			if(!units[P1][i]->isDead())
				cout << units[P1][i]->getName() << ":"
				<< units[P1][i]->getCurrentHP() << " ";
			else
				cout << units[P1][i]->getName() << ":"
				<< "DEAD" << " ";
		}
		cout << endl;
		cout << "Player 2" << endl;
		for(int i = 0; i < 5; i++)
		{
			if(!units[P2][i]->isDead())
				cout << units[P2][i]->getName() << ":"
				<< units[P2][i]->getCurrentHP() << " ";
			else
				cout << units[P2][i]->getName() << ":"
				<< "DEAD" << " ";
		}
		cout << endl;


		//Switch player turn
		if(currentPlayer == P1)
			currentPlayer = P2;
		else
			currentPlayer = P1;

		cout<<endl;
	}
}

void Game::specialMove(Player p){
	Unit** allies = units[p];
//	Unit** enemies = units[!p];

	//counting

	int mammal_count=0, flying_count=0, swimming_count=0, bee_count=0, queen_bee_count=0;
  for(int i=0; i<5 ; i++){
		if(allies[i]->isDead())continue;
    if(isMammal(allies[i])){
      mammal_count++;
    }
    else if(isFlying(allies[i])){
      flying_count++;
    }
		else if(isSwimming(allies[i])){
			swimming_count++;
		}
		else if(isBee(allies[i])){
			bee_count++;
		}
		else if(isQueenBee(allies[i])){
			queen_bee_count++;
		}
  }

	// special move

	if(mammal_count>=3){
		for(int i=0; i<5; i++){
			if(allies[i]->isDead())continue;
			if(isMammal(allies[i])){
				allies[i]->specialMove();
			}
		}
	}

	if(flying_count>=3){
		for(int i=0; i<5; i++){
			if(allies[i]->isDead())continue;
			if(isFlying(allies[i])){
				allies[i]->specialMove();
			}
		}
	}

	if(swimming_count>=3){
		for(int i=0; i<5; i++){
			if(allies[i]->isDead())continue;
			if(isSwimming(allies[i])){
				allies[i]->specialMove();
			}
		}
	}

	if((queen_bee_count==1&&bee_count==4)||(bee_count==5)){
		for(int i=0; i<5; i++){
			if(allies[i]->isDead())continue;
			if(isBee(allies[i])){
				allies[i]->specialMove();
			}
			else if(isQueenBee(allies[i])){
				allies[i]->specialMove();
			}
		}
	}
}

bool Game::isMammal(Unit* u){
	return u->getName()=="Wolf"||u->getName()=="Jaguar";
}

bool Game::isFlying(Unit* u){
	return u->getName()=="Hawk"||u->getName()=="Bat"||u->getName()=="Dragon";
}

bool Game::isSwimming(Unit* u){
	return u->getName()=="Turtle"||u->getName()=="Crocodile";
}

bool Game::isBee(Unit* u){
	return u->getName()=="Bee";
}

bool Game::isQueenBee(Unit* u){
	return u->getName()=="QueenBee";
}
