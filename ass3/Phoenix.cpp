#include "Phoenix.h"

Phoenix::Phoenix(Game* game, int player, int position): Wolf(game,player,position){
	hp = MAX_HP;
	atk_damage = DEFAULT_ATK_DAMAGE;
	name = "Phoenix";

}

Phoenix::~Phoenix() {
	
}

void Phoenix::attack()
{
  int min_hp=99999, index=0;
  for(int i=0; i<5; i++){
    if(enemies[i]->isDead())continue;
    if(enemies[i]->getCurrentHP()<min_hp){
      min_hp = enemies[i]->getCurrentHP();
      index=i;
    }
  }
  Wolf::positionAttackAction(enemies[index]);
}

void Phoenix::defend(Unit* opponent, int damage){
  opponent->takeDamage(1);
  if(rand()%100>=30){
    takeDamage(damage);
  }
}

void Phoenix::die(){
  if(dead_before)Wolf::die();
  else{
    hp=MAX_HP;
    dead_before=true;
  }
}
