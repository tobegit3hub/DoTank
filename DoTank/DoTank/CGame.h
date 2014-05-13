//CGame.h

#ifndef _H_H_CGame
#define _H_H_CGame

#include"CMap.h"

class CGame
{
private:

public:
	CGame();
	~CGame();

	CMap * m_pMap;		//the unique map
	bool m_StatusOfGame;		//indicate the status of game

	void StartGame();		//new a map
	void EndGame();		//delete the map

};



#endif