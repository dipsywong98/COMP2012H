/**
 *  You SHOULD NOT modify this file
 */
#include "Unit.h"
#include <iostream>
using namespace std;

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

void Unit::poison(int amount){
	poison_level+=3;
}

int Unit::getPoison(){
	return poison_level;
}

void Unit::paralysis(){
	is_paralysis=true;
}

bool Unit::isParalysis(){
	return is_paralysis;
}

void Unit::resetParalysis(){
	is_paralysis = false;
}

void Unit::resetPoison(){
	poison_level=0;
}

void Unit::poisonKill(){
	takeDamage(poison_level--);
}