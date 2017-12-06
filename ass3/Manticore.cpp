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
  int min_hp=0, index=0;
  for(int i=0; i<5; i++){
    if(enemies[i]->getCurrentHP()<min_hp){
      min_hp = enemies[i]->getCurrentHP();
      index=i;
    }
  }
  game->printDefend(enemies[index],0);
  game->printText(enemies[index]," poison ");
  enemies[index]->poison();
}

void Manticore::defend(Unit* opponent, int damage){
  takeDamage(damage);
  if(rand()%100<30){
    opponent->paralysis();
    game->printText(enemies[index],"paralysis");
  }
}
