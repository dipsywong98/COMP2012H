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
	// cout<<"hit by "<<opponent->getName()<<" "<<damage<<" "<<(int)(damage*6/10)<<" "<<hp;
	takeDamage(damage*6/10);
	Wolf::printDefend(damage*6/10);
	// cout<<" "<<hp<<endl;
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
		atk_damage = SINGLE_ATK_DAMAGE;
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
	// cout<<endl;
}