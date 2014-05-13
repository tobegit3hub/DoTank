//CGame.cpp

#include"CGame.h"


CGame::CGame()
{
	m_StatusOfGame = false;
}

CGame::~CGame()
{

}


void CGame::StartGame()
{
	m_StatusOfGame = true;

	m_pMap = new CMap(LENGTH, WIDTH);

	m_pMap->m_pMyTank[0].m_Condition = ALIVE;
	m_pMap->UpdateMap();
}


void CGame::EndGame()
{
	delete m_pMap;
}


