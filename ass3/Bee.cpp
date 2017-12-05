#include "Bee.h"
inline constexpr int min(int a, int b){return (a<b?a:b);}

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

void Bee::heal(int amount=1){
	if(!isDead()){
		hp = min(hp+amount,MAX_HP);
	}
}
