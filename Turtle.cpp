#include "Turtle.h"

Turtle::Turtle(Game* game, int player, int position): Unit(game,player,position){
	hp = MAX_HP;
	atk_damage = DEFAULT_ATK_DAMAGE;
	name = "Turtle";

}

Turtle::~Turtle() {
	
}

void Turtle::defend(Unit* opponent, int damage){
	takeDamage(damage*0.5);
}

void Turtle::attack()
{
	if(!enemies[pos]->isDead())
		enemies[pos]->defend(this, atk_damage);
	else {
		for(int i = 1; i < 5; i++)
		{
			if(pos-i >= 0 && !enemies[pos-i]->isDead())
			{
				enemies[pos-i]->defend(this, atk_damage);
				break;
			}
			else if(pos+i < 5 && !enemies[pos+i]->isDead())
			{
				enemies[pos+i]->defend(this, atk_damage);
				break;
			}
		}
	}
}
