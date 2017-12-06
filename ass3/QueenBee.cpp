#include "QueenBee.h"

inline constexpr int min(int a, int b){return (a<b?a:b);}

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

