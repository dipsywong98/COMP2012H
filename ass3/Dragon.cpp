#include "Dragon.h"
inline constexpr int min(int a, int b){return (a<b?a:b);}
inline constexpr int max(int a, int b){return (a>b?a:b);}

Dragon::Dragon(Game* game, int player, int position): Wolf(game,player,position){
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
		Wolf::attack();
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

void Dragon::specialMove(){
	for(int i=0 ; i<5; i++){
		if(!enemies[i]->isDead()){
			enemies[i]->takeDamage(2);
		}
	}
}