#include "Bat.h"
inline constexpr int min(int a, int b){return (a<b?a:b);}

Bat::Bat(Game* game, int player, int position): Wolf(game,player,position){
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
	Wolf::attack();
	heal(1);
}

void Bat::specialMove(){
	Wolf::specialMove();
	heal(1);
}

void Bat::heal(int amount=1){
	if(!isDead()){
		hp = min(hp+amount,MAX_HP);
	}
}
