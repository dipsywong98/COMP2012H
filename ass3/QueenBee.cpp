#include "QueenBee.h"

QueenBee::QueenBee(Game* game, int player, int position): Unit(game,player,position){
	hp = MAX_HP;
	atk_damage = DEFAULT_ATK_DAMAGE;
	name = "QueenBee";
}

QueenBee::~QueenBee() {
	
}

void QueenBee::defend(Unit* opponent, int damage){
	takeDamage(damage);
	if(!isDead()){
		for(int i=0; i<5; i++){
			if(allies[i]->getName()=="Bee"&&!allies[i]->isDead()){
				opponent->takeDamage(2);
			}
		}
	}
}

void QueenBee::attack()
{
}

void QueenBee::specialMove(){
	for(int i=0; i<5; i++){
		if(allies[i]->getName()=="Bee"){
			heal((Bee*) allies[i], 2);
		}
	}
}

void QueenBee::heal(Bee* target, int amount=2){
	if(!isDead()){
		target->hp = min(target->hp+amount,MAX_HP);
	}
}
