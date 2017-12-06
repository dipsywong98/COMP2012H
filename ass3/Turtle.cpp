#include "Turtle.h"

Turtle::Turtle(Game* game, int player, int position): Wolf(game,player,position){
	hp = MAX_HP;
	atk_damage = DEFAULT_ATK_DAMAGE;
	name = "Turtle";

}

Turtle::~Turtle() {
	
}

void Turtle::defend(Unit* opponent, int damage){
	takeDamage(damage*DAMAGE_TAKE_PERCENT/100);
}
