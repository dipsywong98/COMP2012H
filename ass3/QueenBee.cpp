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
	for(int i=0; i<5; i++){
		if(allies[i]->getName()=="Bee"&&!allies[i]->isDead()){
			game->printAttack(allies[i]);
			game->printText(allies[i]," revenge");
			opponent->takeDamage(2);
		}
	}
	
}

void QueenBee::attack()
{
}

