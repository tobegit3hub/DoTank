//CMap.h

#ifndef _H_H_CMap
#define _H_H_CMap

#include"CMyTank.h"
#include"CAiTank.h"

CMyTank & FindMyTank(int x, int y);		/////////////////only available in CMap.h/////////////////////////
CAiTank & FindAiTank(int x, int y);
CBullet & FindBullet(int x, int y);


class CMap
{
private:

public:
	CMap(int Length, int Width, int NumberOfMyTank=2, int NumberOfAiTank=1);		//initialize all data members  //文件读入m_Map（注意去掉换行符），设置BASE，UpdateMap()
	~CMap();

	int m_Length, m_Width;
	EBlock ** m_Map;		//dynamic new by LENGTH and WIDTH
	int m_NumberOfMyTank;		//indicate the number of player's tank
	CMyTank * m_pMyTank;		//dynamic new by m_NumberOfMyTak
	int m_NumberOfAiTank;		//indicate the number of computer's tank
	CAiTank * m_pAiTank;		//dynamic new by m_NumberOfAiTak

	void ActiveAiTank();		//active the DEACTIVED CAiTank object to join the battle	//改m_Map,用SetBlock()
	void UpdateMap();		//update the m_Map by setting tank, bullet and wall

};




#endif