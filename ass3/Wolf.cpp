#include "Wolf.h"
#include <iostream>

Wolf::Wolf(Game* game, int player, int position): Unit(game,player,position){
	hp = MAX_HP;
	atk_damage = DEFAULT_ATK_DAMAGE;
	name = "Wolf";

}

Wolf::~Wolf() {
	
}

void Wolf::attack()
{
	positionAttack();
}

void Wolf::positionAttack(bool defenable){
	if(!enemies[pos]->isDead()){
		positionAttackAction(enemies[pos],defenable);
	}
	else {
		for(int i = 1; i < 5; i++)
		{
			if(pos-i >= 0 && !enemies[pos-i]->isDead())
			{
				positionAttackAction(enemies[pos-i],defenable);
				break;
			}
			else if(pos+i < 5 && !enemies[pos+i]->isDead())
			{
				positionAttackAction(enemies[pos+i],defenable);
				break;
			}
		}
	}
}

void Wolf::positionAttackAction(Unit* enemy, bool defenable){
	// std::cout<<name<<" attack "<<enemy->getName()<<std::endl;
	if(defenable){
		enemy->defend(this, atk_damage);
	}
	else{
		enemy->takeDamage(atk_damage);
	}
}
