#include <iostream>

#include "Game.h"
using namespace std;


int main(int argc, char* argv[]) {
	Game game("game.txt");
	if(argc>1){
		game.fastforward();
	}
	game.start();
	return 0;
}
