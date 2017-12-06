#include "Manticore.h"

Manticore::Manticore(Game* game, int player, int position): Wolf(game,player,position){
	hp = MAX_HP;
	atk_damage = DEFAULT_ATK_DAMAGE;
	name = "Manticore";

}

Manticore::~Manticore() {
	
}

void Manticore::attack()
{
  int max_hp=-1, index=-1;
  for(int i=0; i<5; i++){
    if(enemies[i]->isDead())continue;
    if(enemies[i]->getCurrentHP()-enemies[i]->getPoison()<=0)continue;
    if(enemies[i]->getCurrentHP()>max_hp){
      max_hp = enemies[i]->getCurrentHP();
      index=i;
    }
  }
  game->printDefend(enemies[index],0);
  game->printText(enemies[index],"  poison ");
  enemies[index]->poison(3);
}

void Manticore::defend(Unit* opponent, int damage){
  takeDamage(damage);
  if(rand()%100<30){
    opponent->paralysis();
    // game->printText(opponent,"paralysis");
  }
}
