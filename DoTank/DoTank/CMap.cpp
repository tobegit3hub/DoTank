//CMap.cpp

#include"CMap.h"
#include<fstream>
#include<iostream>
using namespace std;


CMap::CMap(int Length, int Width, int NumberOfMyTank, int NumberOfAiTank)
{
	m_Length = Length;
	m_Width = Width;
	m_NumberOfMyTank = NumberOfMyTank;
	m_NumberOfAiTank = NumberOfAiTank;

	m_Map = new EBlock* [m_Length];
	for(int i=0;i<m_Length;++i)
	{
		m_Map[i] = new EBlock [m_Width];
	}



	ifstream in;
	in.open("..\\res\\Map.txt",ios::in);		//读入文件来确定地图
	if(!in)
	{
		MessageBox(NULL, TEXT("Loadind a default map now..."), TEXT("No Map Finded"), MB_OK | MB_ICONHAND);
		for(int i=0;i<m_Length;++i)
			for(int j=0;j<m_Width;++j)
				m_Map[i][j] = ROAD;
		//cerr<<"File could not be open."<<endl;
		//abort();
	}
	else
	{
		char c;
		for(int i=0;i<WIDTH;++i)
		{
			for(int j=0;j<LENGTH;++j)
			{
				in.get(c);
				if('\n'==c)
					--j;
				else if('0'==c)                       //这里假设文件中用0 1 2来表示ROAD,WALL1，TANK
					m_Map[j][i] = ROAD;
				else if('1'==c)
					m_Map[j][i] = WALL;
				else if('2'==c)
					m_Map[j][i] = BASE;
			}
		}
	}
	in.close();

	//for(int i=0;i<m_Length;++i)		///////////////infile////////////////////
	//{
	//	for(int j=0;j<m_Width;++j)
	//	{
	//		m_Map[i][j] = ROAD;
	//	}
	//}
	//m_Map[2][2] = WALL;


	m_pMyTank = new CMyTank [m_NumberOfMyTank];

	m_pAiTank = new CAiTank [m_NumberOfAiTank];
}


CMap::~CMap()
{
	for(int i=0;i<m_Length;++i)
	{
		delete []m_Map[i];
		m_Map[i] = NULL;
	}
	delete []m_Map;
	m_Map = NULL;

	delete []m_pMyTank;
	m_pMyTank = NULL;

	delete []m_pAiTank;
	m_pAiTank = NULL;
	
}


void CMap::ActiveAiTank()
{
	for(int i=0;i<m_NumberOfAiTank;++i)
	{
		if(INACTIVE==m_pAiTank[i].m_Condition)
		{
			m_pAiTank[i].m_Condition = ALIVE;
			break;
		}
	}
}



void CMap::UpdateMap()
{
	for(int i=0;i<m_Length;++i)
	{
		for(int j=0;j<m_Width;++j)
		{
			if(0==i || m_Length-1==i || 0==j || m_Width-1==j)
			{
				m_Map[i][j] = BORDER;
			}
			else
			{
				//m_Map[i][j] = ROAD;
			}
		}
	}
	m_Map[m_Length/2][m_Width-2] = BASE;
	m_Map[m_Length/2-1][m_Width-2] = WALL;
	m_Map[m_Length/2-1][m_Width-2-1] = WALL;
	m_Map[m_Length/2][m_Width-2-1] = WALL;
	m_Map[m_Length/2+1][m_Width-2-1] = WALL;
	m_Map[m_Length/2+1][m_Width-2] = WALL;


	for(int i=0;i<m_NumberOfMyTank;++i)
	{
		if(ALIVE==m_pMyTank[i].m_Condition)
		{
			m_Map[m_pMyTank[i].m_Position.x][m_pMyTank[i].m_Position.y] = MYTANK;
		}

		for(int j=0;j<m_pMyTank[i].m_NumberOfBullet;++j)
		{
			m_Map[m_pMyTank[i].m_pBullet[j].m_Position.x][m_pMyTank[i].m_pBullet[j].m_Position.y] = BULLET;
		}
	}
	for(int i=0;i<m_NumberOfAiTank;++i)
	{
		if(ALIVE==m_pMyTank[i].m_Condition)
		{
			m_Map[m_pAiTank[i].m_Position.x][m_pAiTank[i].m_Position.y] = MYTANK;
		}
	
		for(int j=0;j<m_pAiTank[i].m_NumberOfBullet;++j)
		{
			m_Map[m_pAiTank[i].m_pBullet[j].m_Position.x][m_pAiTank[i].m_pBullet[j].m_Position.y] = BULLET;
		}	
	}

}
