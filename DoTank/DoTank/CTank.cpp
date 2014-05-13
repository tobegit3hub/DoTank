//CTank.cpp

#include"CTank.h"
#include"CMap.h"

CTank::CTank(int NumberOfBullet)
{
	m_NumberOfBullet = NumberOfBullet;

	m_Position.x = 0;
	m_Position.y = 0;
	m_Direction = RIGHT;
	m_Condition = INACTIVE;

	m_pBullet = new CBullet[NumberOfBullet];
}

CTank::~CTank()
{
	delete []m_pBullet;
	m_pBullet = NULL;
}






