//CAiTank.h

#ifndef _H_H_CAiTank
#define _H_H_CAiTank

#include"CTank.h"

class CAiTank: public CTank
{
private:

public:
	CAiTank(int NumberOfBullet = 3);
	~CAiTank();

	virtual void Move(EDirection Direction);
	virtual void Shoot();
	void AiMove();		//automatically move randomly
	void AiShoot();		//automatically shoot randomly

};




#endif