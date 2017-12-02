/*
* COMP2012 (Fall 2017) Assignment 1: Designing the game of Minesweeper 
*
* Student name: WONG Yuk Chun 
* Student ID: 20419764
* Student email: ycwongal
*
* Be reminded that you are only allowed to modify a certain part of this file. Read the assignment description and
 requirement carefully.
*/

#include <iostream>
#include <fstream>

using namespace std;

#define HEIGHT 15
#define WIDTH 15

const char MINE='X';
const char SAFE='@';
const char UNKNOWN='*';
const char WALL='W';

/* Given Functions */

//The function to print current mine_map in command line
void print_map(char map[HEIGHT][WIDTH]) 
{
   cout << " |012345678901234" << endl;
   cout << " ----------------" << endl;
   for (int i = 0; i < HEIGHT; i++) 
   {
      cout << i % 10 << "|";
      for (int j = 0; j < WIDTH; j++) 
      {
         if (map[i][j] == MINE || map[i][j] == SAFE)
            cout << UNKNOWN;
         else 
            cout << map[i][j];      
      } 
         cout << endl; 
   }
   cout << " ----------------" << endl;
   cout << " |012345678901234" << endl;
}

//main helper function; useless for tasks
bool all_open(const char mine_map[HEIGHT][WIDTH]) 
{
   for (int i = 0; i < HEIGHT; i++)
      for (int j = 0; j < WIDTH; j++)
         if (mine_map[i][j] == SAFE)
            return false;
   return true;
}
//main helper function; useless for tasks; Load input file
bool load_mine_map(char mine_map[HEIGHT][WIDTH], int coin_map[HEIGHT][WIDTH], 
                   int& initial_i, int& initial_j, const char file_name[])
{
   ifstream ifile(file_name);
   if (!ifile.is_open())
      return false;
   for (int i = 0; i < HEIGHT ;i++)
      for (int j = 0; j < WIDTH; j++)
         ifile >> mine_map[i][j];
   for(int i = 0;i < HEIGHT; i++)
      for(int j = 0; j < WIDTH; j++)
         ifile >> coin_map[i][j];
   ifile >> initial_i >> initial_j;
   ifile.close();
   return true;
}

int clamp(int lower, int number, int upper){
	return max(lower,min(number,upper));
}

int count_neighbour_mines(char mine_map[HEIGHT][WIDTH], int row, int col){
	int mine_sum = 0;
	for(int i=clamp(0,row-1,HEIGHT);i<=clamp(0,row+1,HEIGHT);i++){
		for(int j=clamp(0,col-1,WIDTH);j<=clamp(0,col+1,WIDTH);j++){
			if(mine_map[i][j] == MINE) mine_sum++;
		}
	}
	return mine_sum;
}

/* Your Tasks */
/*
 Task 1: You are required to implement this function by recursively using this function to complete task 1
 Parameters:
   mine_map: 2D char array to represent the current mine map
   row, col: The place swept now.In main function, this place is specified by input file or users.
*/
void sweep_fill_along_line(char mine_map[HEIGHT][WIDTH], int row, int col)
{
   //TODO: Add your code here
	if(row<0||row>=HEIGHT||col<0||col>WIDTH||mine_map[row][col]!=SAFE) return;
	int mine_sum = count_neighbour_mines(mine_map, row, col);
	mine_map[row][col] = 48+mine_sum;
	if(mine_sum==0){
		sweep_fill_along_line(mine_map, row, col-1);
		sweep_fill_along_line(mine_map, row, col+1);
	}
}


/* 
 Task 2: You are required to implement this function by recursively using this function to complete task 2
 Parameters:
   mine_map: 2D char array to represent the current mine map
   row, col: The place swept now.In main function, this place is specified by input file or users. 
*/
void sweep_fill(char mine_map[HEIGHT][WIDTH], int row, int col)
{
   //TODO: Add your code here
	if(row<0||row>=HEIGHT||col<0||col>WIDTH||mine_map[row][col]!=SAFE) return;
    int mine_sum = count_neighbour_mines(mine_map, row, col);
	mine_map[row][col] = 48+mine_sum;
	if(mine_sum==0){
		for(int i=clamp(0,row-1,HEIGHT);i<=clamp(0,row+1,HEIGHT);i++){
			for(int j=clamp(0,col-1,WIDTH);j<=clamp(0,col+1,WIDTH);j++){
				if(mine_map[i][j] == SAFE) sweep_fill(mine_map,i,j);
			}
		}
	}
}

/* 
 Task 3: You are required to implement this function by recursively using this function to complete task 3. 
 You are not allowed to call the function sweep_fill and results in task 2.
 Paramters:
   mine_map: 2D char array to represent the current mine map
   coin_map: 2D int array to record the number of coins in each block
   row, col: The place swept now.In main function, this place is specified by input file or users.
*/
int sweep_fill_collect_coin(char mine_map[HEIGHT][WIDTH], const int coin_map[HEIGHT][WIDTH], int row, int col)
{
   //TODO: Add your code here
	if(row<0||row>=HEIGHT||col<0||col>WIDTH||mine_map[row][col]!=SAFE) return 0;
    int mine_sum = count_neighbour_mines(mine_map, row, col);
	if(coin_map[row][col]<0){
		mine_map[row][col] = WALL;
		return 0;
	}
	mine_map[row][col] = 48+mine_sum;
	int coin_sum = coin_map[row][col];
	if(mine_sum==0){
		for(int i=clamp(0,row-1,HEIGHT);i<=clamp(0,row+1,HEIGHT);i++){
			for(int j=clamp(0,col-1,WIDTH);j<=clamp(0,col+1,WIDTH);j++){
				if(mine_map[i][j] == SAFE) coin_sum+=sweep_fill_collect_coin(mine_map,coin_map,i,j);
			}
		}
	}
	return coin_sum;
}


/* Main function */
int main()
{
   int option = 1;
   char fname[100] = "";
   cout << "Welcome to the game!" << endl;  
   cout << "Please input the file name: ";
   cin >> fname;

   char mine_map[HEIGHT][WIDTH];
   int coin_map[HEIGHT][WIDTH];

   int row, col;
   int coin_num;

   if (!load_mine_map(mine_map, coin_map, row, col, fname)) {
         cout << "Cannot load file!" << endl;
         return 0;
   }
   cout << "Please select playing mode (1, 2 or 3): " << endl;
   cin >> option;

   switch (option)
   {
      case 1:
         sweep_fill_along_line(mine_map, row, col);
         print_map(mine_map);
         break;
      case 2:
         sweep_fill(mine_map, row, col);
         print_map(mine_map);
         break;
      case 3:
         coin_num = sweep_fill_collect_coin(mine_map, coin_map, row, col);
         print_map(mine_map);
         cout << "You have collected " << coin_num << " coins." << endl;
   }

   char game_status = 'y';
   cout << "Continue? (Y/N)";
   cin >> game_status;

   while ((game_status == 'Y' || game_status == 'y') && (!all_open(mine_map)))
   {
      bool valid_input = true;
      do
      {
         cout << "Enter (row, col) coordinate: ";
         cin >> row >> col;

         if (row < 0 || row >= HEIGHT || col < 0 || col >= WIDTH)
         {
            cout << "Input row and col are out of boundary! Please input again." << endl;
            valid_input = false;
         } else if (mine_map[row][col] == MINE) {
            cout << "It's a mine. Game Over!" << endl;
            return 0;
         } else if ((mine_map[row][col] >= '0' && mine_map[row][col] <= '9') || (mine_map[row][col] == WALL)) {
            cout << "This block has been swept! Pleae select another block." << endl;
            valid_input = false;
         } else 
            valid_input = true;
         
      } while (!valid_input);


      switch (option)
      {
         case 1:
            sweep_fill_along_line(mine_map, row, col);
            print_map(mine_map);
            break;
         case 2:
            sweep_fill(mine_map, row, col);
            print_map(mine_map);
            break;
         case 3:
            coin_num=sweep_fill_collect_coin(mine_map, coin_map, row, col);
            print_map(mine_map);
            cout << "You have collected " << coin_num << " coins."<<endl;
      }

      cout << "Continue? (Y/N) ";
      cin >> game_status;
   }
   if ((game_status == 'Y') || (game_status == 'y'))
      cout << "You Win!" << endl;

   return 0;
}

