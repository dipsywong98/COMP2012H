#include "Bee.h"

Bee::Bee(Game* game, int player, int position): Unit(game,player,position){
	hp = MAX_HP;
	atk_damage = DEFAULT_ATK_DAMAGE;
	name = "Bee";

}

Bee::~Bee() {
	
}

void Bee::attack()
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
