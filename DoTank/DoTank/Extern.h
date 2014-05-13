//Constant.h


#ifndef _H_H_Constant
#define _H_H_Constant

#include<Windows.h>

#define FRAMEDELAY 100			//define the speed of GameCircle which is for painting
#define TIMEROFBULLET 1001
#define SPEEDOFBULLET 70

#define NUMBEROFBULLET 3

#define LENGTH 32		//define the number of checkers in row
#define WIDTH  18		//define the number of checkers in column


struct SPosition		//define the type like point
{
	int x;
	int y;
};


enum ECondition {DEAD, ALIVE, INACTIVE};		//define the type to show condition of tanks and bullets


enum EDirection{UP, RIGHT, DOWN, LEFT};		//define the type to show direction of tanks and bullets


enum EBlock{ROAD, WALL, BASE, BORDER, MYTANK, AITANK, BULLET};			//define all the object in the map


bool IsRoad(int x, int y);
bool IsWall(int x, int y);		//detect (x, y) is WALL or not and return the result
bool IsMyTank(int x, int y);
bool IsAiTank(int x, int y);
bool IsBullet(int x, int y);

//CTank FindTank(int x, int y);		//check all the tanks and get the exact object
//CBullet FindBullet(int x, int y);		//check all bullets and get the exact object

void SetBlock(int x, int y, EBlock Block);		//set the (x, y) as Block for tanks and bullets change the m_Map
EBlock GetBlock(int x, int y);		//because only one map so it's OK


#endif