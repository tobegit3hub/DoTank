//CMyTank.h

#ifndef _H_H_CMyTank
#define _H_H_CMyTank

#include"CTank.h"

class CMyTank: public CTank
{
private:

public:
	CMyTank(int NumberOfBullet = 3);
	~CMyTank(){}

	virtual void Move(EDirection Direction);
	virtual void Shoot();
	void ReBorn1();
	void ReBorn2();
};




#endif