#include "Jaguar.h"

Jaguar::Jaguar(Game* game, int player, int position): Wolf(game,player,position){
	hp = MAX_HP;
	atk_damage = DEFAULT_ATK_DAMAGE;
	name = "Jaguar";

}

Jaguar::~Jaguar() {
	
}

void Jaguar::attack()
{
	if(hp<13){
		atk_damage = DEFAULT_ATK_DAMAGE*1.5;
	}
	else{
		atk_damage = DEFAULT_ATK_DAMAGE;
	}
	Wolf::attack();
}
