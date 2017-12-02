#include "Bat.h"
inline constexpr int min(int a, int b){return (a<b?a:b);}
Bat::Bat(Game* game, int player, int position): Unit(game,player,position){
	hp = MAX_HP;
	atk_damage = DEFAULT_ATK_DAMAGE;
	name = "Bat";

}

Bat::~Bat() {
	
}

void Bat::defend(Unit* opponent, int damage){
	takeDamage(damage*0.8);
}

void Bat::attack()
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
	if(!isDead()){
		hp = min(hp+1,MAX_HP);
	}
}
