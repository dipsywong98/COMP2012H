#include "Dragon.h"
inline constexpr int min(int a, int b){return (a<b?a:b);}
inline constexpr int max(int a, int b){return (a>b?a:b);}
Dragon::Dragon(Game* game, int player, int position): Unit(game,player,position){
	hp = MAX_HP;
	atk_damage = SINGLE_ATK_DAMAGE;
	name = "Dragon";

}

Dragon::~Dragon() {
	
}

void Dragon::defend(Unit* opponent, int damage){
	takeDamage(damage*0.6);
}

void Dragon::attack()
{
	int alive_sum=0;
	for(int i=max(0,pos-1);i<min(5,pos+2);i++){
		if(!enemies[i]->isDead()){
			alive_sum++;
		}
	}
	if(alive_sum){
		areaAttack();
	}
	else{
		singleAttack();
	}
}

void Dragon::singleAttack(){
	atk_damage = SINGLE_ATK_DAMAGE;
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

void Dragon::areaAttack(){
	atk_damage = AREA_ATK_DAMAGE;
	for(int i=max(0,pos-1);i<min(5,pos+2);i++){
		if(!enemies[i]->isDead()){
			enemies[i]->defend(this, atk_damage);
		}
	}
}