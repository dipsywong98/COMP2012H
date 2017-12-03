#include "Bee.h"

Bee::Bee(Game* game, int player, int position): Wolf(game,player,position){
	hp = MAX_HP;
	atk_damage = DEFAULT_ATK_DAMAGE;
	name = "Bee";

}

Bee::~Bee() {
	
}

void Bee::specialMove(){
	for(int i=0 ; i<5; i++){
		if(!enemies[i]->isDead()){
			enemies[i]->takeDamage(3);
		}
	}
}