//CTank.h

#ifndef _H_H_CTank
#define _H_H_CTank

#include"CBullet.h"

class CTank
{
private:

public:
	CTank(int NumberOfBullet = 3);		//know the number of bullet when constructing, and initialize all data members
	~CTank();		//remember to release m_pBullet

	ECondition m_Condition;		//indicate the tank's condition
	SPosition m_Position;		//indicate the tank's position	
	EDirection m_Direction;		//indicate the tank's direction
	int m_NumberOfBullet;		//indicate the tank's number of bullet
	CBullet * m_pBullet;		//dynamic new m_NumberOfBullet CBullet objects
	int m_Blood;		//the default value is one

	virtual void Move(EDirection Direction) = 0;		//move by the direction		//如果方向不同则转方向
																		//否则判断如果是tank或wall则不移，如果是bullet则死，擦m_Map，设m_Condition, 设m_Map用SetBlock()
	virtual void Shoot() = 0;		//shoot by position and direction		//判断是否还有bullet为DEAD，否则改其condition, direction, position, 设m_Map用SetBlock()

	
};



#endif