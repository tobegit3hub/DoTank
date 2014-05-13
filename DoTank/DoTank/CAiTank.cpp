//CAiTank.cpp

#include"CAiTank.h"
#include"CMap.h"

CAiTank::CAiTank(int NumberOfBullet): CTank(NumberOfBullet)
{
	//m_Condition = ALIVE;
	m_Direction = DOWN;
	m_Position.x = 1;
	m_Position.y = 1;
	m_Blood = 3;

}

CAiTank::~CAiTank()
{

}


void CAiTank::Move(EDirection Direction)
{
	if(m_Direction!=Direction)
	{
		m_Direction = Direction;
	}
	else
	{
		SetBlock(m_Position.x, m_Position.y, ROAD);
		switch(m_Direction)
		{
		case UP:
			{
				--m_Position.y;
				if(true==IsRoad(m_Position.x, m_Position.y))
				{
					SetBlock(m_Position.x, m_Position.y, AITANK);
				}
				else
				{
					if(true==IsBullet(m_Position.x, m_Position.y))
					{
						--m_Blood;
						FindBullet(m_Position.x, m_Position.y).m_Condition = DEAD;
						if(0>=m_Blood)
						{
							SetBlock(m_Position.x, m_Position.y, ROAD);
						}
						else
						{
							SetBlock(m_Position.x, m_Position.y, AITANK);
						}
					}
					else
					{
						++m_Position.y;
						SetBlock(m_Position.x, m_Position.y, AITANK);
					}
				}
			}break;

		case RIGHT:
			{
				++m_Position.x;
				if(true==IsRoad(m_Position.x, m_Position.y))
				{
					SetBlock(m_Position.x, m_Position.y, AITANK);
				}
				else
				{
					if(true==IsBullet(m_Position.x, m_Position.y))
					{
						--m_Blood;
						FindBullet(m_Position.x, m_Position.y).m_Condition = DEAD;
						if(0>=m_Blood)
						{
							SetBlock(m_Position.x, m_Position.y, ROAD);
						}
						else
						{
							SetBlock(m_Position.x, m_Position.y, AITANK);
						}
					}
					else
					{
						--m_Position.x;
						SetBlock(m_Position.x, m_Position.y, AITANK);
					}
				}
			}break;

		case DOWN:
			{
				++m_Position.y;
				if(true==IsRoad(m_Position.x, m_Position.y))
				{
					SetBlock(m_Position.x, m_Position.y, AITANK);
				}
				else
				{
					if(true==IsBullet(m_Position.x, m_Position.y))
					{
						--m_Blood;
						FindBullet(m_Position.x, m_Position.y).m_Condition = DEAD;
						if(0>=m_Blood)
						{
							SetBlock(m_Position.x, m_Position.y, ROAD);
						}
						else
						{
							SetBlock(m_Position.x, m_Position.y, AITANK);
						}
					}
					else
					{
						--m_Position.y;
						SetBlock(m_Position.x, m_Position.y, AITANK);
					}
				}
			}break;

		case LEFT:
			{
				--m_Position.x;
				if(true==IsRoad(m_Position.x, m_Position.y))
				{
					SetBlock(m_Position.x, m_Position.y, AITANK);
				}
				else
				{
					if(true==IsBullet(m_Position.x, m_Position.y))
					{
						--m_Blood;
						FindBullet(m_Position.x, m_Position.y).m_Condition = DEAD;
						if(0>=m_Blood)
						{
							SetBlock(m_Position.x, m_Position.y, ROAD);
						}
						else
						{
							SetBlock(m_Position.x, m_Position.y, AITANK);
						}
					}
					else
					{
						++m_Position.x;
						SetBlock(m_Position.x, m_Position.y, AITANK);
					}
				}
			}break;

		}
	}

}







void CAiTank::Shoot()
{
	for(int i=0;i<m_NumberOfBullet;++i)
	{
		if(DEAD==m_pBullet[i].m_Condition)
		{
			m_pBullet[i].m_Condition = ALIVE;
			m_pBullet[i].m_Direction = m_Direction;

			m_pBullet[i].m_Position.x = m_Position.x;
			m_pBullet[i].m_Position.y = m_Position.y;
			m_pBullet[i].Move();

			SetBlock(m_Position.x, m_Position.y, AITANK);

			PlaySound(TEXT("../res/Gunfire.wav"), NULL, SND_ASYNC | SND_FILENAME);
			break;
		}
	}
}