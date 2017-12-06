#include "Hawk.h"

Hawk::Hawk(Game* game, int player, int position): Wolf(game,player,position){
	hp = MAX_HP;
	atk_damage = DEFAULT_ATK_DAMAGE;
	name = "Hawk";

}

Hawk::~Hawk() {
	
}

void Hawk::attack(){
	Wolf::positionAttack(false);
}

void Hawk::defend(Unit* opponent, int damage){
	takeDamage(damage*7/10);
	Wolf::printDefend(damage*7/10);
	if(!isDead()){
		opponent->takeDamage(1);
	}
}