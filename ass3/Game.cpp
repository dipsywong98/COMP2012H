#include <iostream>
#include <fstream>
#include <time.h>

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
#include "Phoenix.h"

using namespace std;

#ifdef _WIN32
#include <windows.h>
void Game::gotoxy(int x, int y) {
    COORD coord;
    coord.X = x; 
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    
}
#else
void Game::gotoxy(int x, int y) {
    printf("\033[%d;%dH", y, x);
}
#endif

ostream& Game::xyout(int x, int y){
	gotoxy(x,y);
	return cout;
}

Game::Game(std::string file):fout("log.txt") {
	srand(time(NULL));
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
		case PHOENIX:
		units[c/5][c%5] = new Phoenix(this, c/5, c%5);
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
		fout << "Draws!" << endl;
		stageMessage()<<"Draws"<<endl;
	}else if (deadCount1 == 5)
	{
		fout << "Player " << P2+1 << " Wins!" << endl;
		stageMessage()<<"Player " << P2+1 << " Wins!"<<endl;
	} else if (deadCount2 == 5)
	{
		fout << "Player " << P1+1 << " Wins!" << endl;
		stageMessage()<<"Player " << P1+1 << " Wins!"<<endl;
	} else {
		return false;
	}
	return true;

}

void Game::start()
{
	Player currentPlayer = P1;
	int turnCount = 1;
	console_init();
	while(!isEnd())
	{
		printAll();
		clearStage();
		stageMessage()<<"Player "<<currentPlayer+1<<" is attacking!"<<endl;
		waitNextFrame();
		int original_hp[5];

		
		for(int i = 0; i < 5; i++)
		{
			printUnit(units[currentPlayer][i]);
			if(allDead(units[!currentPlayer]))break;
			if(!units[currentPlayer][i]->isDead()){
				if(units[currentPlayer][i]->getName()=="QueenBee")continue;
				int ohp = -units[currentPlayer][i]->getCurrentHP();
				clearStage();
				stageMessage()<<units[currentPlayer][i]->getName()<<" is attacking";
				printAttack(units[currentPlayer][i]);
				waitNextFrame();
				units[currentPlayer][i]->attack();
				ohp+=units[currentPlayer][i]->getCurrentHP();
				if(ohp)printNumber(units[currentPlayer][i],ohp);
				waitNextFrame();
				printAll();
				waitNextFrame();
			}

		}
		
		specialMove(currentPlayer);

		//Output turn info
		fout << "Turn " << turnCount++ << " Player " << currentPlayer+1 << " attacks:" << endl;
		fout << "Player 1" << endl;
		for(int i = 0; i < 5; i++)
		{
			if(!units[P1][i]->isDead())
				fout << units[P1][i]->getName() << ":"
				<< units[P1][i]->getCurrentHP() << " ";
			else
				fout << units[P1][i]->getName() << ":"
				<< "DEAD" << " ";
		}
		fout << endl;
		fout << "Player 2" << endl;
		for(int i = 0; i < 5; i++)
		{
			if(!units[P2][i]->isDead())
				fout << units[P2][i]->getName() << ":"
				<< units[P2][i]->getCurrentHP() << " ";
			else
				fout << units[P2][i]->getName() << ":"
				<< "DEAD" << " ";
		}
		fout << endl;


		//Switch player turn
		if(currentPlayer == P1)
			currentPlayer = P2;
		else
			currentPlayer = P1;

	}
}

bool Game::allDead(Unit** team){
	int dead_sum=0;
	for(int i=0; i<5; i++)dead_sum+=team[i]->isDead();
	return dead_sum==5;
}

void Game::specialMove(Player p){
	Unit** allies = units[p];
	Unit** enemies = units[!p];

	//counting

	int mammal_count=0, flying_count=0, swimming_count=0, bee_count=0, queen_bee_count=0, legendary_count=0;
  for(int i=0; i<5 ; i++){
		if(allies[i]->isDead())continue;
    if(isLivingMammal(allies[i])){
      mammal_count++;
    }
    if(isLivingFlying(allies[i])){
      flying_count++;
    }
		if(isLivingSwimming(allies[i])){
			swimming_count++;
		}
		if(isLivingBee(allies[i])){
			bee_count++;
		}
		if(isLivingQueenBee(allies[i])){
			queen_bee_count++;
		}
		if(isLivingLegendary(allies[i])){
			legendary_count++;
		}
  }

	
		if(mammal_count>=3){
			stageMessage()<<"Bite And Scratch"<<endl;
			specialMoveGeneral(&Game::isLivingMammal,&Game::biteAndScratch, allies,enemies);
		}
		if(flying_count>=3){
			stageMessage()<<"harass"<<endl;
			specialMoveGeneral(&Game::isLivingFlying,&Game::harass, allies,enemies);
		}
		if(swimming_count>=3){
			stageMessage()<<"Summon Tsunami"<<endl;
			specialMoveGeneral(&Game::isLivingSwimming,&Game::summonTsunami, allies,enemies);
		}
		if(bee_count==5||(bee_count==4&&queen_bee_count==1)){
			stageMessage()<<"March And Conquer"<<endl;
			specialMoveGeneral(&Game::isLivingAnyBee,&Game::marchAndConquer, allies,enemies);
		}
		if(legendary_count>=3){
			stageMessage()<<"Weather The Storm"<<endl;
			specialMoveGeneral(&Game::isLivingLegendary,&Game::weatherTheStorm, allies,enemies);
		}
	
}

bool Game::isLivingMammal(Unit* u){
	return (!u->isDead())&&(u->getName()=="Wolf"||u->getName()=="Jaguar");
}

bool Game::isLivingFlying(Unit* u){
	return (!u->isDead())&&(u->getName()=="Hawk"||u->getName()=="Bat"||u->getName()=="Dragon");
}

bool Game::isLivingSwimming(Unit* u){
	return (!u->isDead())&&(u->getName()=="Turtle"||u->getName()=="Crocodile");
}

bool Game::isLivingBee(Unit* u){
	return (!u->isDead())&&(u->getName()=="Bee");
}

bool Game::isLivingQueenBee(Unit* u){
	return (!u->isDead())&&(u->getName()=="QueenBee");
}

bool Game::isLivingAnyBee(Unit* u){
	return isLivingBee(u)||isLivingQueenBee(u);
}

bool Game::isLivingLegendary(Unit* u){
	return (!u->isDead())&&(u->getName()=="Phoenix"||u->getName()=="Dragon"||u->getName()=="Manticore");
}

void Game::generalKill(Unit** enemies, int amount){
	for(int i=0; i<5; i++){
		if(!enemies[i]->isDead()){
			enemies[i]->takeDamage(amount);
			// printDefend(enemies[i],-amount);
		}
	}
}

void Game::specialMoveGeneral(bool(Game::*isType)(Unit*),void(Game::*action)(Unit*,Unit**,Unit**),Unit** allies, Unit** enemies){
	if(allDead(enemies))return;
	int original_hp_enemies[5];
	for(int i=0;i<5;i++){
		original_hp_enemies[i]=-enemies[i]->getCurrentHP();
	}
	for(int i=0;i<5;i++)if((this->*isType)(allies[i]))printAttack(allies[i]);
	waitNextFrame();
	for(int i=0;i<5;i++)(this->*action)(allies[i],allies,enemies);
	for(int i=0;i<5;i++)printDefend(enemies[i],original_hp_enemies[i]+enemies[i]->getCurrentHP());
	waitNextFrame();
	printAll();
	waitNextFrame();
}

void Game::biteAndScratch(Unit* unit, Unit** allies, Unit** enemies){
	if(!isLivingMammal(unit))return;
	generalKill(enemies,1);
}

void Game::harass(Unit* unit, Unit** allies, Unit** enemies){
	if(!isLivingFlying(unit))return;
	if(unit->getName()=="Dragon"){
		generalKill(enemies,2);
	}
	else{
		generalKill(enemies,1);
		if(unit->getName()=="Bat"){
			((Bat*)unit)->heal(1);
			printNumber(unit,1);
		}
	}
}

void Game::summonTsunami(Unit* unit, Unit** allies, Unit** enemies){
	if(!isLivingSwimming(unit))return;
	if(unit->getName()=="Crocodile"){
		generalKill(enemies,2);
		unit->takeDamage(2);
		printNumber(unit,-2);
	}
	else{
		generalKill(enemies,1);
	}
}

void Game::marchAndConquer(Unit* unit, Unit** allies, Unit** enemies){
	if(!isLivingBee(unit)&&!isLivingQueenBee(unit))return;
	if(unit->getName()=="Bee"){
		generalKill(enemies,3);
	}
	else{
		for(int i=0; i<5; i++){
			if(allies[i]->getName()=="Bee"){
				((Bee*) allies[i])->heal(2);
				printNumber(allies[i],2);
			}
		}
	}
}

void Game::weatherTheStorm(Unit* unit, Unit** allies, Unit** enemies){
	if(!isLivingLegendary(unit))return;
	printAttack(unit);
	generalKill(enemies,3);
}

/**
 *Console animations 
 * 
 */

void Game::console_init(){
	for(int i=0;i<2;i++){
		for(int j=0; j<5; j++){
			position[units[i][j]] = pair<int,int>(14*j,9*i+1);
		}
	}
}

void Game::printUnit(Unit* unit){
	int x = position[unit].first;
	int y = position[unit].second;
	xyout(x,y+0)<<"--------------"<<endl;
	xyout(x,y+1)<<"|            |"<<endl;
	xyout(x,y+2)<<"|            |"<<endl;
	xyout(x,y+3)<<"|            |"<<endl;
	xyout(x,y+4)<<"|            |"<<endl;
	xyout(x,y+5)<<"--------------"<<endl;
	xyout(x+3,y+2)<<unit->getName()<<endl;
	xyout(x+3,y+3)<<"atk:"<<unit->getAtkDamage()<<endl;
	if(unit->isDead()){
		xyout(x+3,y+4)<<"DEAD"<<endl;
	}
	else{
		xyout(x+3,y+4)<<"hp"<<unit->getCurrentHP()<<endl;
	}
	// log()<<unit->getName()<<" "<<unit->getCurrentHP();
}

void Game::printAll(){
	for(int i=0;i<2;i++){
		for(int j=0; j<5; j++){
			printUnit(units[i][j]);
		}
	}
}

void Game::clearStage(){
	xyout(0,7)<<"                                                                      "<<endl;
	xyout(0,8)<<"                                                                      "<<endl;
	xyout(0,9)<<"                                                                      "<<endl;
	xyout(0,17)<<"                                                                      "<<endl;
}

void Game::printAttack(Unit* unit){
	int x = position[unit].first;
	int y = position[unit].second;
	if(y<8){
		xyout(x,7)<<"  v         v  "<<endl;
	}
	else{
		xyout(x,9)<<"  ^         ^  "<<endl;
	}
}

void Game::printDefend(Unit* unit, int delta){
	int x = position[unit].first;
	int y = position[unit].second;
	if(y<8){
		xyout(x,7)<<"  ^         ^  "<<endl;
		
	}
	else{
		xyout(x,9)<<"  v         v  "<<endl;
	}
	if(unit->getName()=="Phoenix"){
		if(delta>0){
			printText(unit," reborn ");
		}else if(delta==0){
			printText(unit," missed ");
		}else {
			printNumber(unit, delta);
		}
	}
	else { 
		printNumber(unit, delta);
	}
}

void Game::printNumber(Unit* unit, int number){
	int x = position[unit].first;
	int y = position[unit].second;
	if(y<8){
		if(number<0)xyout(x+6,7)<<number<<endl;
		else if(number>0)xyout(x+6,7)<<"+"<<number<<endl;
		else xyout(x+6,7)<<"no harm"<<endl;
	}
	else{
		if(number<0)xyout(x+6,9)<<number<<endl;
		else if(number>0)xyout(x+6,9)<<"+"<<number<<endl;
		else xyout(x+6,9)<<"no harm"<<endl;
	}
}

void Game::printText(Unit* unit, string text){
	int x = position[unit].first;
	int y = position[unit].second;
	if(y<8){
		xyout(x+3,7)<<text<<endl;
	}
	else{
		xyout(x+3,9)<<text<<endl;
	}
}

void Game::waitNextFrame(){
	for(int i=0; i<10000; i++)for(int j=0; j<15000; j++);
}
