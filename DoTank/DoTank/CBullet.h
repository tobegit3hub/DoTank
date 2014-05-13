//CBullet.h

#ifndef _H_H_CBullet
#define _H_H_CBullet

#include"Extern.h"


class CBullet
{
private:
	
public:
	CBullet();		//initialize all data members
	~CBullet();

	ECondition m_Condition;		//indicate the bullet's condition
	SPosition m_Position;		//indicate the bullet's position	
	EDirection m_Direction;		//indicate the bullet's direction

	void Move();		//move by m_Position and m_Direction		//判断是否CTank，是则调用FindTank（返回CTank），然后擦除m_Map，设m_Condition
						//设m_Map用SetBlock() 				    	//判断是否CBullet，是则调用FindBullet，然后擦除m_Map，设m_Condition

};

#endif