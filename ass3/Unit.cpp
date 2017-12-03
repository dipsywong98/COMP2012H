/**
 *  You SHOULD NOT modify this file
 */
#include "Unit.h"

Unit::Unit(Game* game, int player, int position) {
	allies = game->units[player];
	enemies = game->units[!player];
	pos = position;
	is_dead = false;

}

Unit::~Unit() {
	
}


void Unit::defend(Unit* opponent, int damage)
{
	takeDamage(damage);
}

void Unit::die()
{
	is_dead = true;
}

void Unit::takeDamage(int damage)
{
	hp -= damage;
	if( hp <= 0 )
		die();
}

bool Unit::isDead() const
{
	return is_dead;
}

std::string Unit::getName() const
{
	return name;
}

int Unit::getCurrentHP() const
{
	return hp;
}

int Unit::getAtkDamage() const
{
        return atk_damage;
}

void Unit::specialMove(){
	for(int i=0 ; i<5; i++){
		if(!enemies[i]->isDead()){
			enemies[i]->takeDamage(1);
		}
	}
}