//CBullet.cpp

#include"CBullet.h"
#include"CMap.h"		///////////////////////only way to use FindMyTank()///////////////////////////////// 

CBullet::CBullet()
{
	m_Condition = DEAD;
	m_Position.x = 0;
	m_Position.y = 0;
	m_Direction = RIGHT;
}


CBullet::~CBullet()
{

}


void CBullet::Move()
{
	SetBlock(m_Position.x, m_Position.y, ROAD);
	switch(m_Direction)
	{
	case UP:
		{
			--m_Position.y;
		}break;
	case RIGHT:
		{
			++m_Position.x;
		}break;
	case DOWN:
		{
			++m_Position.y;
		}break;
	case LEFT:
		{
			--m_Position.x;
		}break;
	}

	if(ROAD==GetBlock(m_Position.x, m_Position.y))
	{
		SetBlock(m_Position.x, m_Position.y, BULLET);
	}
	else if(WALL==GetBlock(m_Position.x, m_Position.y))
	{
		m_Condition = DEAD;
		SetBlock(m_Position.x, m_Position.y, ROAD);
	}
	else if(BORDER==GetBlock(m_Position.x, m_Position.y))
	{
		m_Condition = DEAD;
		SetBlock(m_Position.x, m_Position.y, BORDER);
	}
	else if(BULLET==GetBlock(m_Position.x, m_Position.y))
	{
		m_Condition = DEAD;
		FindBullet(m_Position.x, m_Position.y).m_Condition = DEAD;
		SetBlock(m_Position.x, m_Position.y, ROAD);
	}
	else if(AITANK==GetBlock(m_Position.x, m_Position.y))
	{
		m_Condition = DEAD;
		FindAiTank(m_Position.x, m_Position.y).m_Condition = DEAD;
		SetBlock(m_Position.x, m_Position.y, ROAD);
	}
	else if(MYTANK==GetBlock(m_Position.x, m_Position.y))
	{
		m_Condition = DEAD;
		--FindMyTank(m_Position.x, m_Position.y).m_Blood;
		if(0>=FindMyTank(m_Position.x, m_Position.y).m_Blood)
		{
			FindMyTank(m_Position.x, m_Position.y).m_Condition = DEAD;
			SetBlock(m_Position.x, m_Position.y, ROAD);
		}
		else
		{
			SetBlock(m_Position.x, m_Position.y, MYTANK);
		}
	}
	else if(BASE==GetBlock(m_Position.x, m_Position.y))
	{
		m_Condition = DEAD;

		PlaySound(TEXT("../res/Gunfire.wav"), NULL, SND_ASYNC | SND_FILENAME);
		MessageBox(NULL, TEXT("You lost the game... but it's OK to give you another chance."), TEXT("Game Might Be Over"), MB_OK | MB_ICONWARNING);
	}

}