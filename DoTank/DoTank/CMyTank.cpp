//CMyTank.cpp

#include"CMyTank.h"
#include"CMap.h"

CMyTank::CMyTank(int NumberOfBullet): CTank(NumberOfBullet)
{
	m_Direction = UP;
	m_Position.x = LENGTH/2-2;
	m_Position.y = WIDTH-2;
	m_Blood = 3;

}

void CMyTank::ReBorn1()
{
	m_Condition = ALIVE;
	m_Direction = UP;
	m_Position.x = LENGTH/2-2;
	m_Position.y = WIDTH-2;
	m_Blood = 3;
}

void CMyTank::ReBorn2()
{
	m_Condition = ALIVE;
	m_Direction = UP;
	m_Position.x = LENGTH/2+2;
	m_Position.y = WIDTH-2;
	m_Blood = 3;


}

void CMyTank::Move(EDirection Direction)
{
	PlaySound(TEXT("../res/Peow.wav"), NULL, SND_ASYNC | SND_FILENAME);

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
					SetBlock(m_Position.x, m_Position.y, MYTANK);
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
							SetBlock(m_Position.x, m_Position.y, MYTANK);
						}
					}
					else
					{
						++m_Position.y;
						SetBlock(m_Position.x, m_Position.y, MYTANK);
					}
				}
			}break;

		case RIGHT:
			{
				++m_Position.x;
				if(true==IsRoad(m_Position.x, m_Position.y))
				{
					SetBlock(m_Position.x, m_Position.y, MYTANK);
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
							SetBlock(m_Position.x, m_Position.y, MYTANK);
						}
					}
					else
					{
						--m_Position.x;
						SetBlock(m_Position.x, m_Position.y, MYTANK);
					}
				}
			}break;

		case DOWN:
			{
				++m_Position.y;
				if(true==IsRoad(m_Position.x, m_Position.y))
				{
					SetBlock(m_Position.x, m_Position.y, MYTANK);
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
							SetBlock(m_Position.x, m_Position.y, MYTANK);
						}
					}
					else
					{
						--m_Position.y;
						SetBlock(m_Position.x, m_Position.y, MYTANK);
					}
				}
			}break;

		case LEFT:
			{
				--m_Position.x;
				if(true==IsRoad(m_Position.x, m_Position.y))
				{
					SetBlock(m_Position.x, m_Position.y, MYTANK);
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
							SetBlock(m_Position.x, m_Position.y, MYTANK);
						}
					}
					else
					{
						++m_Position.x;
						SetBlock(m_Position.x, m_Position.y, MYTANK);
					}
				}
			}break;

		}
	}

}



void CMyTank::Shoot()
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

			SetBlock(m_Position.x, m_Position.y, MYTANK);

			PlaySound(TEXT("../res/Bang.wav"), NULL, SND_ASYNC | SND_FILENAME);
			break;
		}
	}
}


