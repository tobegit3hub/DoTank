//WinMain.cpp


#pragma comment (lib, "winmm.lib")

#include<Windows.h>
#include<MMSystem.h>                  //should be declare after  #include<Windows.h>
#include<CommDlg.h>
#include<stdio.h>

#include"CGame.h"
#include"resource.h"

ATOM MyRegisterClass(HINSTANCE hInstance);		//design and register the window
bool InitInstance(HINSTANCE hInstance, int nCmdShow);		//create the window
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);		//handle the message but keydown
VOID CALLBACK TimerProcOfBullet(HWND hWnd,
						UINT uMsg,
						UINT_PTR idEvent,
						DWORD dwTime);


void InitGraph();
void ReleaseGraph();
void HandleKeys();
void HandleJoystick();
void GameCircle();
void PaintAll(HDC hDC);



LPCWSTR lpAppName = TEXT("DoTank");		//define the name of program and title of window
HINSTANCE hInst;
HWND hWnd;
JOYINFO jinfo;
HDC hDC;
RECT rect;


static int TickTrigger=0;
int TickCount=0;		//to get the tick automatically
int cx, cy;		//the length and width of client area
int cxOfChecker, cyOfChecker;		//the length and width of each checker
HBITMAP hBmpAll;
HDC hdcMemAll;
HBITMAP hBmpMyTankUp, hBmpMyTankRight, hBmpMyTankDown, hBmpMyTankLeft;
HBITMAP hBmpMyTankUp_bk, hBmpMyTankRight_bk, hBmpMyTankDown_bk, hBmpMyTankLeft_bk;
HBITMAP hBmpAiTankUp, hBmpAiTankRight, hBmpAiTankDown, hBmpAiTankLeft;
HBITMAP hBmpWall, hBmpBullet;
HDC hdcMemMyTankUp, hdcMemMyTankRight, hdcMemMyTankDown, hdcMemMyTankLeft;
HDC hdcMemMyTankUp_bk, hdcMemMyTankRight_bk, hdcMemMyTankDown_bk, hdcMemMyTankLeft_bk;
HDC hdcMemAiTankUp, hdcMemAiTankRight, hdcMemAiTankDown, hdcMemAiTankLeft; 
HDC hdcMemWall, hdcMemBullet;



CGame Game;		//the game itself



int APIENTRY WinMain(HINSTANCE hInstance,
					 HINSTANCE hPrevInstance,
					 LPSTR lpCmdLine, 
					 int nCmdShow)
{
	MyRegisterClass(hInstance);

	InitInstance(hInstance, nCmdShow);

	MSG msg;
	while(true)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(WM_QUIT!=msg.message)
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				break;		//then quit the program
			}
		}
		else
		{
			if(true==Game.m_StatusOfGame)
			{
				TickCount = GetTickCount();		//get the tick by operating system
				if(TickCount>TickTrigger)
				{			
					TickTrigger = TickCount + FRAMEDELAY;
					HandleKeys();		//handle the message from keyboard
					HandleJoystick();		//handle the message from joystick
					GameCircle();		//paint the game and add enemy
				}	
			}
		}
	}

	return msg.wParam;
}



ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASS wc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wc.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_POINTER1));		//use my cursor
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));		//use my icon
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WindowProc;
	wc.lpszClassName = lpAppName;
	wc.lpszMenuName = MAKEINTRESOURCE(IDM_MENU1);		//use a menu
	wc.style = CS_HREDRAW | CS_VREDRAW;

	return RegisterClass(&wc);
}


bool InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hWnd = CreateWindow( lpAppName, lpAppName,
						 WS_OVERLAPPEDWINDOW,
						 CW_USEDEFAULT, CW_USEDEFAULT,
						 CW_USEDEFAULT, CW_USEDEFAULT,
						 NULL, 
						 NULL,
						 hInstance,
						 NULL);

	ShowWindow(hWnd, SW_SHOWNORMAL);		//not full-screen
	UpdateWindow(hWnd);

	return true;
}






void InitGraph()
{
	hDC = GetDC(hWnd);

	hBmpMyTankUp = (HBITMAP)LoadImage(NULL, TEXT("../res/MyTankUp.bmp"), IMAGE_BITMAP, cxOfChecker, cxOfChecker, LR_LOADFROMFILE);
	hdcMemMyTankUp = CreateCompatibleDC(hDC);
	SelectObject(hdcMemMyTankUp, hBmpMyTankUp);

	hBmpMyTankRight = (HBITMAP)LoadImage(NULL, TEXT("../res/MyTankRight.bmp"), IMAGE_BITMAP, cxOfChecker, cxOfChecker, LR_LOADFROMFILE);
	hdcMemMyTankRight = CreateCompatibleDC(hDC);
	SelectObject(hdcMemMyTankRight, hBmpMyTankRight);

	hBmpMyTankDown = (HBITMAP)LoadImage(NULL, TEXT("../res/MyTankDown.bmp"), IMAGE_BITMAP, cxOfChecker, cxOfChecker, LR_LOADFROMFILE);
	hdcMemMyTankDown = CreateCompatibleDC(hDC);
	SelectObject(hdcMemMyTankDown, hBmpMyTankDown);

	hBmpMyTankLeft = (HBITMAP)LoadImage(NULL, TEXT("../res/MyTankLeft.bmp"), IMAGE_BITMAP, cxOfChecker, cxOfChecker, LR_LOADFROMFILE);
	hdcMemMyTankLeft = CreateCompatibleDC(hDC);
	SelectObject(hdcMemMyTankLeft, hBmpMyTankLeft);


	hBmpMyTankUp_bk = (HBITMAP)LoadImage(NULL, TEXT("../res/MyTankUp_bk.bmp"), IMAGE_BITMAP, cxOfChecker, cxOfChecker, LR_LOADFROMFILE);
	hdcMemMyTankUp_bk = CreateCompatibleDC(hDC);
	SelectObject(hdcMemMyTankUp_bk, hBmpMyTankUp_bk);

	hBmpMyTankRight_bk = (HBITMAP)LoadImage(NULL, TEXT("../res/MyTankRight_bk.bmp"), IMAGE_BITMAP, cxOfChecker, cxOfChecker, LR_LOADFROMFILE);
	hdcMemMyTankRight_bk = CreateCompatibleDC(hDC);
	SelectObject(hdcMemMyTankRight_bk, hBmpMyTankRight_bk);

	hBmpMyTankDown_bk = (HBITMAP)LoadImage(NULL, TEXT("../res/MyTankDown_bk.bmp"), IMAGE_BITMAP, cxOfChecker, cxOfChecker, LR_LOADFROMFILE);
	hdcMemMyTankDown_bk = CreateCompatibleDC(hDC);
	SelectObject(hdcMemMyTankDown_bk, hBmpMyTankDown_bk);

	hBmpMyTankLeft_bk = (HBITMAP)LoadImage(NULL, TEXT("../res/MyTankLeft_bk.bmp"), IMAGE_BITMAP, cxOfChecker, cxOfChecker, LR_LOADFROMFILE);
	hdcMemMyTankLeft_bk = CreateCompatibleDC(hDC);
	SelectObject(hdcMemMyTankLeft_bk, hBmpMyTankLeft_bk);



	hBmpAiTankUp = (HBITMAP)LoadImage(NULL, TEXT("../res/AiTankUp.bmp"), IMAGE_BITMAP, cxOfChecker, cxOfChecker, LR_LOADFROMFILE);
	hdcMemAiTankUp = CreateCompatibleDC(hDC);
	SelectObject(hdcMemAiTankUp, hBmpAiTankUp);

	hBmpAiTankRight = (HBITMAP)LoadImage(NULL, TEXT("../res/AiTankRight.bmp"), IMAGE_BITMAP, cxOfChecker, cxOfChecker, LR_LOADFROMFILE);
	hdcMemAiTankRight = CreateCompatibleDC(hDC);
	SelectObject(hdcMemAiTankRight, hBmpAiTankRight);

	hBmpAiTankDown = (HBITMAP)LoadImage(NULL, TEXT("../res/AiTankDown.bmp"), IMAGE_BITMAP, cxOfChecker, cxOfChecker, LR_LOADFROMFILE);
	hdcMemAiTankDown = CreateCompatibleDC(hDC);
	SelectObject(hdcMemAiTankDown, hBmpAiTankDown);

	hBmpAiTankLeft = (HBITMAP)LoadImage(NULL, TEXT("../res/AiTankLeft.bmp"), IMAGE_BITMAP, cxOfChecker, cxOfChecker, LR_LOADFROMFILE);
	hdcMemAiTankLeft = CreateCompatibleDC(hDC);
	SelectObject(hdcMemAiTankLeft, hBmpAiTankLeft);





	hBmpWall = (HBITMAP)LoadImage(NULL, TEXT("../res/Wall.bmp"), IMAGE_BITMAP, cxOfChecker, cxOfChecker, LR_LOADFROMFILE);
	hdcMemWall = CreateCompatibleDC(hDC);
	SelectObject(hdcMemWall, hBmpWall);


	hBmpBullet = (HBITMAP)LoadImage(NULL, TEXT("../res/Bullet.bmp"), IMAGE_BITMAP, cxOfChecker, cxOfChecker, LR_LOADFROMFILE);
	hdcMemBullet = CreateCompatibleDC(hDC);
	SelectObject(hdcMemBullet, hBmpBullet);


	ReleaseDC(hWnd, hDC);
}

void ReleaseGraph()
{
	DeleteObject(hBmpMyTankUp);
	DeleteObject(hBmpMyTankRight);
	DeleteObject(hBmpMyTankDown);
	DeleteObject(hBmpMyTankLeft);
	DeleteObject(hBmpMyTankUp_bk);
	DeleteObject(hBmpMyTankRight_bk);
	DeleteObject(hBmpMyTankDown_bk);
	DeleteObject(hBmpMyTankLeft_bk);
	DeleteObject(hBmpAiTankUp);
	DeleteObject(hBmpAiTankRight);
	DeleteObject(hBmpAiTankDown);
	DeleteObject(hBmpAiTankLeft);
	DeleteObject(hBmpWall);
	DeleteObject(hBmpBullet);

	ReleaseDC(hWnd, hdcMemMyTankUp);
	ReleaseDC(hWnd, hdcMemMyTankRight);
	ReleaseDC(hWnd, hdcMemMyTankDown);
	ReleaseDC(hWnd, hdcMemMyTankLeft);
	ReleaseDC(hWnd, hdcMemMyTankUp_bk);
	ReleaseDC(hWnd, hdcMemMyTankRight_bk);
	ReleaseDC(hWnd, hdcMemMyTankDown_bk);
	ReleaseDC(hWnd, hdcMemMyTankLeft_bk);
	ReleaseDC(hWnd, hdcMemWall);
	ReleaseDC(hWnd, hdcMemBullet);

}









LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	

	switch(uMsg)
	{
	case WM_CREATE:
		{
			hInst = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);

			GetClientRect(hWnd, &rect);		//get the length and width of game area
			cx = rect.right - rect.left;
			cy = rect.bottom - rect.top;
			cxOfChecker = cx / LENGTH;
			cyOfChecker = cy / WIDTH;


			InitGraph();
			Game.StartGame();
			
			SetTimer(hWnd, TIMEROFBULLET, SPEEDOFBULLET, TimerProcOfBullet);

		}break;

	case WM_SIZE:
		{
			GetClientRect(hWnd, &rect);		//when the screen changes, the game area changes
			cx = rect.right - rect.left;
			cy = rect.bottom - rect.top;
			cxOfChecker = cx / LENGTH;
			cyOfChecker = cy / WIDTH;
		}break;

	case WM_PAINT:
		{
			hDC = BeginPaint(hWnd, &ps);

			//hdcMemAll = CreateCompatibleDC(hDC);
			//hBmpAll = CreateCompatibleBitmap(hDC, cx, cy);		/////////////////////useless////////////////
			//SelectObject(hdcMemAll, hBmpAll);

			//PaintAll(hdcMemAll);	
			//BitBlt(hDC, 0, 0, cx, cy, hdcMemAll, 0, 0, SRCCOPY);	

			//DeleteObject(hBmpAll);
			//DeleteDC(hdcMemAll);

			PaintAll(hDC);

			EndPaint(hWnd, &ps);
		}break;

	case WM_COMMAND:		//the message from menu
		{
			switch(wParam)
			{
			case IDM_START:
				{
					//MessageBox(NULL,TEXT(""),TEXT(""),MB_OK);
				}break;

			case IDM_HOWTOPLAY:
				{
					MessageBox(hWnd, TEXT("WSAF for move   and   Ctrl for shoot"), TEXT("Player2's Key"), MB_OK | MB_ICONINFORMATION);
				}break;

			case IDM_REBORN1P:
				{
					Game.m_pMap->m_pMyTank[0].m_Condition = DEAD;
					SetBlock(Game.m_pMap->m_pMyTank[0].m_Position.x, Game.m_pMap->m_pMyTank[0].m_Position.y, ROAD);
					Game.m_pMap->m_pMyTank[0].ReBorn1();
					
					Game.m_pMap->UpdateMap();
				}break;
				
			case IDM_ACTIVE2P:
				{
					Game.m_pMap->m_pMyTank[1].ReBorn2();
					
					Game.m_pMap->UpdateMap();
				}break;

			case IDM_DEACTIVE2P:
				{
					Game.m_pMap->m_pMyTank[1].m_Condition = DEAD;
					SetBlock(Game.m_pMap->m_pMyTank[1].m_Position.x, Game.m_pMap->m_pMyTank[1].m_Position.y, ROAD);
					Game.m_pMap->UpdateMap();
				}break;
				
			case IDM_OPEN:		//choose the song by yourself
				{
					OPENFILENAME ofn;						
					TCHAR szFile[MAX_PATH];
					ZeroMemory(&ofn,sizeof(ofn));
					ofn.lStructSize = sizeof(ofn);
					ofn.lpstrFile = szFile;
					ofn.lpstrFile[0] = TEXT('\0');
					ofn.nMaxFile = sizeof(szFile);
					ofn.lpstrFilter = TEXT("mp3\0*.mp3\0ALL\0*.*\0Text\0*.TXT\0C++\0*.cpp\0");
					ofn.nFilterIndex = 1;
					ofn.lpstrFileTitle = NULL;
					ofn.nMaxFileTitle = 0;						
					ofn.lpstrInitialDir = NULL;
					ofn.Flags = OFN_EXPLORER |OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
					GetOpenFileName(&ofn);

					TCHAR lpShortPath[64];
					GetShortPathName(szFile, lpShortPath, sizeof(lpShortPath));
					
					TCHAR buffer[64];
					wsprintf(buffer, TEXT("play %s"), lpShortPath);
						
					PlaySound(NULL,0,SND_PURGE);		//make the PlaySound's song pause
					mciSendString(buffer, NULL, 0, NULL);		//play the song in fact
				}break;
			}
		}break;


	case WM_KEYDOWN:
		{
			if(true==Game.m_StatusOfGame)
			{
				switch(wParam)
				{
				case VK_SHIFT:
					{
						//if(ALIVE==Game.m_pMap->m_pMyTank[1].m_pBullet[1].m_Condition)
						//	MessageBox(NULL,TEXT(""),TEXT(""),MB_OK);
						//Game.m_pMap->m_pMyTank[1].m_pBullet[0].Move();
					}break;
				}


				if(ALIVE==Game.m_pMap->m_pMyTank[1].m_Condition)
				{
					switch(wParam)
					{
					case 'W':
						{
							Game.m_pMap->m_pMyTank[1].Move(UP);
						}break;
					case 'D':
						{
							Game.m_pMap->m_pMyTank[1].Move(RIGHT);
						}break;
					case 'S':
						{
							Game.m_pMap->m_pMyTank[1].Move(DOWN);
						}break;
					case 'A':
						{
							Game.m_pMap->m_pMyTank[1].Move(LEFT);
						}break;
					case VK_CONTROL:
						{
							Game.m_pMap->m_pMyTank[1].Shoot();
						}break;
					}
				}
			}
		}break;

	case WM_DESTROY:
		{		
			Game.EndGame();
			ReleaseGraph();
			PostQuitMessage(0);
		}break;

	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void HandleKeys()
{
	////MessageBox(NULL,TEXT(""),TEXT(""),MB_OK);
	if(ALIVE==Game.m_pMap->m_pMyTank[0].m_Condition)
	{
		if(GetAsyncKeyState(VK_UP)<0)
		{
			Game.m_pMap->m_pMyTank[0].Move(UP);
		}
		else if(GetAsyncKeyState(VK_RIGHT)<0)
		{
			Game.m_pMap->m_pMyTank[0].Move(RIGHT);
		}
		else if(GetAsyncKeyState(VK_DOWN)<0)
		{
			Game.m_pMap->m_pMyTank[0].Move(DOWN);
		}
		else if(GetAsyncKeyState(VK_LEFT)<0)
		{
			Game.m_pMap->m_pMyTank[0].Move(LEFT);
		}
		else if(GetAsyncKeyState(VK_SPACE)<0)
		{
			Game.m_pMap->m_pMyTank[0].Shoot();
		}
	}




	InvalidateRect(hWnd, &rect, true);		//force to redraw the window
}


void HandleJoystick()
{
	if(joyGetPos(JOYSTICKID1, &jinfo)==JOYERR_NOERROR)
	{
		if(ALIVE!=Game.m_pMap->m_pMyTank[1].m_Condition)
		{
			if(jinfo.wButtons & JOY_BUTTON13)
			{
				Game.m_pMap->m_pMyTank[1].ReBorn2();
				Game.m_pMap->UpdateMap();
			}
		}
		if(ALIVE==Game.m_pMap->m_pMyTank[1].m_Condition)
		{
			if(jinfo.wButtons & JOY_BUTTON5)
			{
				Game.m_pMap->m_pMyTank[1].Move(UP);
			}
			else if(jinfo.wButtons & JOY_BUTTON6)
			{
				Game.m_pMap->m_pMyTank[1].Move(RIGHT);
			}
			else if(jinfo.wButtons & JOY_BUTTON7)
			{
				Game.m_pMap->m_pMyTank[1].Move(DOWN);
			}
			else if(jinfo.wButtons & JOY_BUTTON8)
			{
				Game.m_pMap->m_pMyTank[1].Move(LEFT);
			}
			else if(jinfo.wButtons & JOY_BUTTON15)
			{
				Game.m_pMap->m_pMyTank[1].Shoot();
			}
		}
	}
}

void GameCircle()
{
	hDC = GetDC(hWnd);


	//hdcMemAll = CreateCompatibleDC(hDC);
	//hBmpAll = CreateCompatibleBitmap(hDC, cx, cy);		/////////////////////useless////////////////
	//SelectObject(hdcMemAll, hBmpAll);

	//PaintAll(hdcMemAll);	
	//BitBlt(hDC, 0, 0, cx, cy, hdcMemAll, 0, 0, SRCCOPY);

	//DeleteObject(hBmpAll);
	//DeleteDC(hdcMemAll);

	PaintAll(hDC);	

	ReleaseDC(hWnd, hDC);
}

void PaintAll(HDC hDC)
{
	//Game.m_pMap->m_pAiTank[0].m_Condition = ALIVE;
	//Game.m_pMap->m_pAiTank[0].m_Direction = DOWN;
	//Game.m_pMap->m_pAiTank[0].m_Position.x = 4;
	//Game.m_pMap->m_pAiTank[0].m_Position.y = 4;
	//Game.m_pMap->m_pAiTank[0].m_Blood = 1;
	for(int i=0;i<LENGTH;++i)
	{
		for(int j=0;j<WIDTH;++j)
		{
			if(MYTANK==Game.m_pMap->m_Map[i][j])
			{
				if(ALIVE==FindMyTank(i,j).m_Condition)
				{
					////Ellipse(hDC, i*cxOfChecker, j*cyOfChecker, (i+1)*cxOfChecker, (j+1)*cyOfChecker);
					if(UP==FindMyTank(i,j).m_Direction)
					{
						BitBlt(hDC, i*cxOfChecker, j*cyOfChecker, cxOfChecker, cyOfChecker, hdcMemMyTankUp_bk, 0, 0, SRCAND);
						BitBlt(hDC, i*cxOfChecker, j*cyOfChecker, cxOfChecker, cyOfChecker, hdcMemMyTankUp, 0, 0, SRCPAINT);
					}
					else if(RIGHT==FindMyTank(i,j).m_Direction)
					{
						BitBlt(hDC, i*cxOfChecker, j*cyOfChecker, cxOfChecker, cyOfChecker, hdcMemMyTankRight_bk, 0, 0, SRCAND);
						BitBlt(hDC, i*cxOfChecker, j*cyOfChecker, cxOfChecker, cyOfChecker, hdcMemMyTankRight, 0, 0, SRCPAINT);
					}
					else if(DOWN==FindMyTank(i,j).m_Direction)
					{
						BitBlt(hDC, i*cxOfChecker, j*cyOfChecker, cxOfChecker, cyOfChecker, hdcMemMyTankDown_bk, 0, 0, SRCAND);
						BitBlt(hDC, i*cxOfChecker, j*cyOfChecker, cxOfChecker, cyOfChecker, hdcMemMyTankDown, 0, 0, SRCPAINT);
					}
					else if(LEFT==FindMyTank(i,j).m_Direction)
					{
						BitBlt(hDC, i*cxOfChecker, j*cyOfChecker, cxOfChecker, cyOfChecker, hdcMemMyTankLeft_bk, 0, 0, SRCAND);
						BitBlt(hDC, i*cxOfChecker, j*cyOfChecker, cxOfChecker, cyOfChecker, hdcMemMyTankLeft, 0, 0, SRCPAINT);
					}
				}

			}
			else if(AITANK==Game.m_pMap->m_Map[i][j])
			{
				if(ALIVE==FindAiTank(i,j).m_Condition)
				{
					if(UP==FindAiTank(i,j).m_Direction)
					{
						BitBlt(hDC, i*cxOfChecker, j*cyOfChecker, cxOfChecker, cyOfChecker, hdcMemMyTankUp_bk, 0, 0, SRCAND);
						BitBlt(hDC, i*cxOfChecker, j*cyOfChecker, cxOfChecker, cyOfChecker, hdcMemAiTankUp, 0, 0, SRCPAINT);
					}
					else if(RIGHT==FindAiTank(i,j).m_Direction)
					{
						BitBlt(hDC, i*cxOfChecker, j*cyOfChecker, cxOfChecker, cyOfChecker, hdcMemMyTankRight_bk, 0, 0, SRCAND);
						BitBlt(hDC, i*cxOfChecker, j*cyOfChecker, cxOfChecker, cyOfChecker, hdcMemAiTankRight, 0, 0, SRCPAINT);
					}
					else if(DOWN==FindAiTank(i,j).m_Direction)
					{
						BitBlt(hDC, i*cxOfChecker, j*cyOfChecker, cxOfChecker, cyOfChecker, hdcMemMyTankDown_bk, 0, 0, SRCAND);
						BitBlt(hDC, i*cxOfChecker, j*cyOfChecker, cxOfChecker, cyOfChecker, hdcMemAiTankDown, 0, 0, SRCPAINT);
					}
					else if(LEFT==FindAiTank(i,j).m_Direction)
					{
						BitBlt(hDC, i*cxOfChecker, j*cyOfChecker, cxOfChecker, cyOfChecker, hdcMemMyTankLeft_bk, 0, 0, SRCAND);
						BitBlt(hDC, i*cxOfChecker, j*cyOfChecker, cxOfChecker, cyOfChecker, hdcMemAiTankLeft, 0, 0, SRCPAINT);
					}
				}

			}				
			else if(BULLET==Game.m_pMap->m_Map[i][j])
			{
				//BitBlt(hDC, i*cxOfChecker, j*cyOfChecker, cxOfChecker, cyOfChecker, hdcMemBullet, 0, 0, SRCCOPY);
				Ellipse(hDC, i*cxOfChecker, j*cyOfChecker, (i+1)*cxOfChecker, (j+1)*cyOfChecker);
			}
			else if(WALL==Game.m_pMap->m_Map[i][j])
			{
				//Rectangle(hDC, i*cxOfChecker, j*cyOfChecker, (i+1)*cxOfChecker, (j+1)*cyOfChecker);
				//BitBlt(hDC, i*cxOfChecker, j*cyOfChecker, cxOfChecker, cyOfChecker, hdcMemWall, 0, 0, SRCCOPY);
				Rectangle(hDC, i*cxOfChecker, j*cyOfChecker, (i+1)*cxOfChecker, (j+1)*cyOfChecker);
			}
			else if(BORDER==Game.m_pMap->m_Map[i][j])
			{
				Rectangle(hDC, i*cxOfChecker, j*cyOfChecker, (i+1)*cxOfChecker, (j+1)*cyOfChecker);
			}
			else if(BASE==Game.m_pMap->m_Map[i][j])
			{
				Ellipse(hDC, i*cxOfChecker, j*cyOfChecker, (i+1)*cxOfChecker, (j+1)*cyOfChecker);
			}		
		}
	}
}




VOID CALLBACK TimerProcOfBullet(HWND hWnd,
						UINT uMsg,
						UINT_PTR idEvent,
						DWORD dwTime)
{
	for(int i=0;i<Game.m_pMap->m_NumberOfMyTank;++i)
	{
		for(int j=0;j<Game.m_pMap->m_pMyTank[i].m_NumberOfBullet;++j)
		{
			if(ALIVE==Game.m_pMap->m_pMyTank[i].m_pBullet[j].m_Condition)
			{
				Game.m_pMap->m_pMyTank[i].m_pBullet[j].Move();
				//MessageBox(NULL,TEXT("UP"),TEXT(""),MB_OK);
			}
		}
	}

	for(int i=0;i<Game.m_pMap->m_NumberOfAiTank;++i)
	{
		for(int j=0;j<Game.m_pMap->m_pAiTank[i].m_NumberOfBullet;++j)
		{
			if(ALIVE==Game.m_pMap->m_pAiTank[i].m_pBullet[j].m_Condition)
			{
				Game.m_pMap->m_pAiTank[i].m_pBullet[j].Move();
			}
			
		}
	}


	//InvalidateRect(hWnd, &rect, true);
	//UpdateWindow(hWnd);
}








bool IsRoad(int x, int y)
{
	if(ROAD==Game.m_pMap->m_Map[x][y])
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool IsWall(int x, int y)
{
	if(WALL==Game.m_pMap->m_Map[x][y])
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool IsMyTank(int x, int y)
{
	if(MYTANK==Game.m_pMap->m_Map[x][y])
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool IsAiTank(int x, int y)
{
	if(AITANK==Game.m_pMap->m_Map[x][y])
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool IsBullet(int x, int y)
{
	if(BULLET==Game.m_pMap->m_Map[x][y])
	{
		return true;
	}
	else
	{
		return false;
	}
}


CMyTank & FindMyTank(int x, int y)
{
	for(int i=0;i<Game.m_pMap->m_NumberOfMyTank;++i)
	{
		if(x==Game.m_pMap->m_pMyTank[i].m_Position.x && y==Game.m_pMap->m_pMyTank[i].m_Position.y)
		{
			return Game.m_pMap->m_pMyTank[i];
		}
	}
}

CAiTank & FindAiTank(int x, int y)
{
	for(int i=0;i<Game.m_pMap->m_NumberOfAiTank;++i)
	{
		if(x==Game.m_pMap->m_pAiTank[i].m_Position.x && y==Game.m_pMap->m_pAiTank[i].m_Position.y)
		{
			return Game.m_pMap->m_pAiTank[i];
		}
	}

}

CBullet & FindBullet(int x, int y)
{
	for(int i=0;i<Game.m_pMap->m_NumberOfMyTank;++i)
	{
		for(int j=0;j<Game.m_pMap->m_pMyTank[i].m_NumberOfBullet;++j)
		{
			if(x==Game.m_pMap->m_pMyTank[i].m_pBullet[j].m_Position.x && y==Game.m_pMap->m_pMyTank[i].m_pBullet[j].m_Position.y)
			{
				return Game.m_pMap->m_pMyTank[i].m_pBullet[j];
			}
		}
	}
	for(int i=0;i<Game.m_pMap->m_NumberOfAiTank;++i)
	{
		for(int j=0;j<Game.m_pMap->m_pAiTank[i].m_NumberOfBullet;++j)
		{
			if(x==Game.m_pMap->m_pAiTank[i].m_pBullet[j].m_Position.x && y==Game.m_pMap->m_pAiTank[i].m_pBullet[j].m_Position.y)
			{
				return Game.m_pMap->m_pAiTank[i].m_pBullet[j];
			}
		}
	}
}



EBlock GetBlock(int x, int y)
{
	return Game.m_pMap->m_Map[x][y];
}

void SetBlock(int x, int y, EBlock Block)
{
	Game.m_pMap->m_Map[x][y] = Block;
}


