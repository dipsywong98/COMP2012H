#include "Crocodile.h"

Crocodile::Crocodile(Game* game, int player, int position): Wolf(game,player,position){
	hp = MAX_HP;
	atk_damage = DEFAULT_ATK_DAMAGE;
	name = "Crocodile";

}

Crocodile::~Crocodile() {
	
}

void Crocodile::defend(Unit* opponent, int damage){
	takeDamage(damage);
	if(!isDead()) opponent->takeDamage(2);
}

void Crocodile::attack()
{
	Wolf::attack();
	takeDamage(1);
}