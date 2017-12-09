#include "Manticore.h"

Manticore::Manticore(Game* game, int player, int position): Unit(game,player,position){
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
  takeDamage(damage*DAMAGE_TAKE_PERCENT/100);
  if(rand()%100<PARALYSIS_PERCENT){
    opponent->paralysis();
    // game->printText(opponent,"paralysis");
  }
}
