#define _CRT_SECURE_NO_WARNINGS
#include "head.h"
using namespace std;

Graph::Graph(int length, int height)
{
	loadimage(&TabUnchoosen, _T(".\\Image\\Unchoosen.png"));
	loadimage(&TabChoosen, _T(".\\Image\\choosen.png"));
	_Mouse = { 0 };
	GraphLength = length;
	GraphHeight = height;
	initgraph(GraphLength, GraphHeight);
	setorigin(540, 304);
	_hWnd = GetHWnd();
}
void Graph::CloseGraph()
{
	closegraph();
}
void Graph::start()
{
	mciSendString(_T("play .\\Music\\Begin.mp3 repeat"), 0, 0, 0);
	IMAGE img[42];
	TCHAR LogoName[] = _T(".\\Image\\Logo\\Logo_00001.jpg");
	for (int i = 0; i < 42; i++)
	{
		LogoName[21] = (i + 1) / 10 + '0';
		LogoName[22] = (i + 1) % 10 + '0';
		loadimage(&img[i], LogoName);
	}
	Sleep(1500);
	for (int i = 0; i < 42; i++)
	{
		putimage(-540, -304, &img[i]);
		Sleep(41);
	}
	TCHAR StartLogoName[] = _T(".\\Image\\StartLogo\\StartLogo_00001.png");
	for (int i = 0; i < 48; i++)
	{
		StartLogoName[31] = (i + 1) / 10 + '0';
		StartLogoName[32] = (i + 1) % 10 + '0';
		loadimage(&StartLogo[i], StartLogoName);
	} // Ԥ���غ���֡
	Sleep(1500);
	for (int i = 41; i >= 0; i--)
	{
		putimage(-540, -304, &img[i]);
		Sleep(41);
	}
	setfillcolor(RGB(0, 0, 0));
	solidrectangle(-540, -304, 540, 304);
}
void Graph::ShowTab()
{
	setfillcolor(0x000000);
	solidrectangle(-540, -304, 540, 304);
	// ����������Ļ
	IMAGE load;
	loadimage(&load, _T(".\\Image\\unchoosen.png"));
	putimage(TabBeginX, TabBeginY, &load);
	putimage(TabBeginX, TabBeginY + 35, &load);
	putimage(TabBeginX, TabBeginY + 70, &load);
	putimage(TabBeginX, TabBeginY + 105, &load);
	putimage(TabBeginX, TabBeginY + 140, &load);
	// ��ʼ��ӡѡ�
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 20;
	f.lfWidth = 15;
	_tcscpy(f.lfFaceName, _T("����"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextcolor(RGB(0xff, 0xff, 0xff));
	settextstyle(&f);
	setbkmode(TRANSPARENT);
	outtextxy(TabBeginX+5, TabBeginY + 5, _T("MODE 1"));
	outtextxy(TabBeginX + 5, TabBeginY + 40, _T("MODE 2"));
	outtextxy(TabBeginX + 5, TabBeginY + 75, _T("MODE 3"));
	outtextxy(TabBeginX + 5, TabBeginY + 110, _T("Story Mode"));
	outtextxy(TabBeginX + 5, TabBeginY + 145, _T("Rank"));

	// Ĭ��ѡ���˵�һ��ѡ�
	putimage(TabBeginX, TabBeginY, &TabChoosen);
	outtextxy(TabBeginX + 5, TabBeginY + 5, _T("MODE 1"));
	setlinecolor(RGB(00, 0xD2, 0xFF));
	line(TabBeginX, TabBeginY, TabBeginX, TabBeginY + 29);
}
void Graph::_GetTextPosition(int& y, int pos)
{
	switch (pos)
	{
		case 0:
			y = 5;
			break;
		case 1:
			y = 40;
			break;
		case 2:
			y = 75;
			break;
		case 3:
			y = 110;
			break;
		case 4:
			y = 145;
			break;
		default:
			break;
	}
}
int Graph::GetChoice()
{
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
	FlushMouseMsgBuffer();
	int y; // ѡ��λ����Ϣ
	int PrePos = 0;
	int NewPos = 0; // ��ʼλ��ΪTabName[0]
	TCHAR TabName[5][20] = { _T("MODE 1"), _T("MODE 2"),_T("MODE 3"),_T("Story Mode"),_T("Rank") };
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 20;
	f.lfWidth = 15;
	_tcscpy(f.lfFaceName, _T("����"));
	settextstyle(&f);
	f.lfQuality = ANTIALIASED_QUALITY;

	int LogoPos = 0;
	setlinecolor(RGB(00, 0xD2, 0xFF));
	while (true)
	{
		putimage(0, -304, &StartLogo[LogoPos++]);
		Sleep(41); // һ֡��ʱ��
		if (LogoPos == 48)
			LogoPos = 0;
		if (MouseHit())
		{ // ���������¼����ͻ�ȡ��ǰ�����Ϣ
			_Mouse = GetMouseMsg();
			if (_Mouse.mkLButton)
			{ // �������ѡ��
				mciSendString(_T("play .\\Music\\click.mp3"), 0, 0, 0);
				return NewPos;
			}
			if ((_Mouse.wheel== 0))
			{
				FlushMouseMsgBuffer();
				continue;
			}
			else
			{
				PrePos = NewPos;
				NewPos += (_Mouse.wheel > 0 ? -1 : 1);
				NewPos = (NewPos < 0) ? 4 : NewPos;
				NewPos = (NewPos > 4) ? 0 : NewPos; // תȦ�ƶ�
				if (PrePos != NewPos)
				{
					_GetTextPosition(y, PrePos);
					putimage(TabBeginX,TabBeginY+y-5,&TabUnchoosen); // �����һ��ѡ��
					outtextxy(TabBeginX + 5, TabBeginY + y, TabName[PrePos]);
					_GetTextPosition(y, NewPos);
					putimage(TabBeginX, TabBeginY + y-5, &TabChoosen); // ������ǰѡ��
					outtextxy(TabBeginX + 5, TabBeginY + y, TabName[NewPos]);
					line(TabBeginX, TabBeginY + y - 5, TabBeginX, TabBeginY + y + 24);
				}
			}
			
		}
	}
	return -1;
}

/************************
map��
1   2   3      ʳ   ��   ʳ
4   5   6      ��   ǽ   ��
7   8   9      ʳ   ��   ʳ
    0               ��
���þŹ������ּ��̣�����ֱ�map��ֵͬ�ĺ���
****************************/
Map::Map()
{
	map = new(nothrow) unsigned short[MapRow][MapCol]{ {0} };
	if (map == NULL)
	{
		closegraph();
		cout << "No Memory" << endl;
		exit(EXIT_FAILURE);
	}
	srand(unsigned int(time(0)));
	_hWnd = GetHWnd();
	HighestScore = 0;
	SnakeLength = 2;
	Life = 1;
	score = 0;
	head[0] = 0;
	head[1] = 0;
	tail[0] = 0;
	tail[1] = 0;

	gettextstyle(&f);
	f.lfHeight = 20;
	f.lfWidth = 8;
	_tcscpy(f.lfFaceName, _T("����"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	setbkmode(TRANSPARENT);
	loadimage(&SnakeHead[0], _T(".\\Image\\head_2.jpg"));
	loadimage(&SnakeHead[1], _T(".\\Image\\head_4.jpg"));
	loadimage(&SnakeHead[2], _T(".\\Image\\head_6.jpg"));
	loadimage(&SnakeHead[3], _T(".\\Image\\head_8.jpg"));
	loadimage(&wall, _T(".\\Image\\wall.jpg"));
	loadimage(&choosen, _T(".\\Image\\choosen.png"));
	loadimage(&unchoosen, _T(".\\Image\\unchoosen.png"));
	loadimage(&food[0], _T(".\\Image\\fire.png"));
	loadimage(&food[1], _T(".\\Image\\snow.png"));
	loadimage(&food[2], _T(".\\Image\\wind.png"));
	loadimage(&food[3], _T(".\\Image\\lightning.png"));
}
Map::~Map()
{
	delete[]map;
}
void Map::UserName()
{
	settextstyle(&f);
	settextcolor(BackGroundColor);
	outtextxy(-100, -50, _T("�����뱾�ε�¼���û���"));
	outtextxy(-170, 250, _T("������10����ĸ�����֡�Ӣ�ı�㹹�ɣ��Իس�����"));
	TCHAR tmp;
	OwnerName[10] = '\0';
	int i;
	for (i = 0; i < 10; i++)
	{
		OwnerName[i] = '\0';
		tmp = _getch();
		if (tmp == '\r' && i!=0)
			break;
		if (!(tmp >= 33 && tmp <= 126))
		{
			i--;
			FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
			continue;
		}
		outtextxy(-100 + i * 20, 20, tmp);
		OwnerName[i] = char(tmp);
	}
	if (i == 10)
	{
		char ch;
		while (ch = _getch())
			if (ch == '\r')
				break;
	}
}
void Map::ShowLength(int NowLength)
{
	TCHAR output[5] = _T("\0\0\0\0"); // ���Ȳ�������λ��
	int totallength = 0;
	for (;; totallength++)
	{
		if (NowLength / int(pow(10, totallength)) == 0)
			break;
	} // ��ȡ����
	for (int i = 0; i < totallength; i++)
	{
		output[i] = '0' + NowLength / int(pow(10, totallength - i - 1));
		NowLength = NowLength % int(pow(10, totallength - i - 1));
	}
	outtextxy(LengthPosX, LengthPosY, _T("��ǰ����:"));
	outtextxy(LengthPosX + 120, LengthPosY, output);
}
void Map::ShowLife(int NowLife)
{
	TCHAR output[5] = _T("\0\0\0\0"); // ������������λ��
	int totallength = 0;
	for (;; totallength++)
	{
		if (NowLife / int(pow(10, totallength)) == 0)
			break;
	} // ��ȡ����
	for (int i = 0; i < totallength; i++)
	{
		output[i] = '0' + NowLife / int(pow(10, totallength - i - 1));
		NowLife = NowLife % int(pow(10, totallength - i - 1));
	}
	outtextxy(LifePosX, LifePosY, _T("ʣ������:"));
	outtextxy(LifePosX + 120, LifePosY, output);
}
void Map::ShowScore(int NowScore)
{
	TCHAR output[8] = _T("0\0\0\0\0\0\0"); // ����������7λ��
	int totallength = 0;
	for (;; totallength++)
	{
		if (NowScore / int(pow(10, totallength)) == 0)
			break;
	} // ��ȡ����
	for (int i = 0; i < totallength; i++)
	{
		output[i] = '0' + NowScore / int(pow(10, totallength - i - 1));
		NowScore = NowScore % int(pow(10, totallength - i - 1));
	}
	outtextxy(ScorePosX, ScorePosY, _T("��ǰ����:"));
	outtextxy(ScorePosX + 120, ScorePosY, output);
}
void Map::ShowHighest(int HighestScore)
{
	TCHAR output[8] = _T("0\0\0\0\0\0\0"); // ����������7λ��
	int totallength = 0;
	for (;; totallength++)
	{
		if (HighestScore / int(pow(10, totallength)) == 0)
			break;
	} // ��ȡ����
	for (int i = 0; i < totallength; i++)
	{
		output[i] = '0' + HighestScore / int(pow(10, totallength - i - 1));
		HighestScore = HighestScore % int(pow(10, totallength - i - 1));
	}
	outtextxy(HighestPosX, HighestPosY, _T("��ʷ���:"));
	outtextxy(HighestPosX + 120, HighestPosY, output);
}
void Map::ShowTime(int hour, int min, int sec)
{
	TCHAR play_hour[3] = { _T("00") }, play_min[3] = { _T("00") }, play_sec[3] = { _T("00") };
	play_hour[0] = hour / 10 + '0';
	play_hour[1] = hour % 10 + '0';
	play_min[0] = min / 10 + '0';
	play_min[1] = min % 10 + '0';
	play_sec[0] = sec / 10 + '0';
	play_sec[1] = sec % 10 + '0';
	outtextxy(TimePosX, TimePosY, _T("��Ϸʱ��:"));
	outtextxy(TimePosX + 120, TimePosY, play_hour);
	outtextxy(TimePosX + 140, TimePosY, _T(":"));
	outtextxy(TimePosX + 150, TimePosY, play_min);
	outtextxy(TimePosX + 170, TimePosY, _T(":"));
	outtextxy(TimePosX + 180, TimePosY, play_sec);
}
void Map::ShowInfo(int mode,time_t t)
{
	CleanInfo();
	f.lfWidth = 10;
	settextstyle(&f);
	settextcolor(BackGroundColor);
	ShowLength(SnakeLength);
	ShowLife(Life);
	ShowScore(score);
	if (score > HighestScore)
		ShowHighest(score);
	else
		ShowHighest(HighestScore);
	tm Time;
	localtime_s(&Time, &t);
	ShowTime(Time.tm_hour-8, Time.tm_min, Time.tm_sec);
}
void Map::CleanInfo()
{
	setbkmode(OPAQUE);
	settextcolor(0x000000);
	outtextxy(LengthPosX, LengthPosY, _T("                      "));
	outtextxy(LifePosX, LifePosY, _T("                      "));
	outtextxy(ScorePosX, ScorePosY, _T("                      "));
	outtextxy(HighestPosX, HighestPosY, _T("                      "));
	outtextxy(TimePosX, TimePosY, _T("                      "));
	setbkmode(TRANSPARENT);
}
void Map::clean()
{
	HighestScore = 0;
	SnakeLength = 2;
	Life = 1;
	score = 0;
	for (int i = 0; i < MapRow; i++)
	{
		for (int j = 0; j < MapCol; j++)
			map[i][j] = 0;
	}
	head[0] = 0;
	head[1] = 0;
	tail[0] = 0;
	tail[1] = 0;
}
void Map::init(int mode)
{
	setfillcolor(0x000000);
	solidrectangle(-540, -304, 540, 304);
	settextcolor(BackGroundColor);
	outtextxy(NamePosX, NamePosY, ModeName[mode - 1]);
	if (mode != 5)
		ShowInfo(mode);
	// ���ɵ�ɫ��
	setfillcolor(BackGroundColor);
	solidrectangle(-164, -304, 540, 304);
	// ����ǽ��
	// ����������ǽ��
	for (int i = 0, j = 0; j < MapCol; j++)
	{
		putimage(LTPosX + j * STEP, LTPosY + i * STEP, &wall);
		map[i][j] = 5; // ���ö���ǽ
	}
	for (int i = MapRow - 1, j = 0; j < MapCol; j++)
	{
		putimage(LTPosX + j * STEP, LTPosY + i * STEP, &wall);
		map[i][j] = 5; // ���õײ�ǽ
	}
	for (int i = 0, j = 0; i < MapRow; i++)
	{
		putimage(LTPosX + j * STEP, LTPosY + i * STEP, &wall);
		map[i][j] = 5; // �������ǽ
	}
	for (int i = 0, j = MapCol - 1; i < MapRow; i++)
	{
		putimage(LTPosX + j * STEP, LTPosY + i * STEP, &wall);
		map[i][j] = 5; // �����Ҳ�ǽ
	}
	// ��ʼ��ʱ����ͷ����ֱ�������ڵ�ͼ��
	SnakeLength = 2;
	head[0] = 34;
	head[1] = 34;
	tail[0] = 35;
	tail[1] = 34;
	map[34][34] = 2;
	map[35][34] = 2; // ��ʼ״̬�������˶�
	putimage(LTPosX + head[1] * STEP, LTPosY + head[0] * STEP, &SnakeHead[0], SRCAND);
	setfillcolor(SnakeColor);
	solidrectangle(LTPosX + head[1] * STEP, LTPosY + 35 * STEP,
		LTPosX + head[1] * STEP + STEP-1, LTPosY + 35 * STEP + STEP-1);
	
	CreateFood(rand()%5+1);
}
bool Map::CreateSnake()
{
	int sum = 0;
	for (sum = 0; sum < 10; sum++)
	{
		int i = rand() % (MapRow - 2) + 1;
		int j = rand() % (MapCol - 2) + 1;
		if (map[i][j] == 0)
		{
			if (map[i - 1][j] == 0)
			{
				head[0] = i - 1;
				head[1] = j;
				map[i - 1][j] = 2;
				putimage(LTPosX + j * STEP, LTPosY + (i - 1) * STEP, &SnakeHead[0], SRCAND);
				tail[0] = i;
				tail[1] = j;
				map[i][j] = 2;
				setfillcolor(SnakeColor);
				solidrectangle(LTPosX + j * STEP, LTPosY + i * STEP,
					LTPosX + j * STEP + STEP - 1, LTPosY + i * STEP + STEP - 1);
				SnakeLength = 2;
				return true;
			}
			else if (map[i][j + 1] == 0)
			{
				head[0] = i;
				head[1] = j + 1;
				map[i][j + 1] = 6;
				putimage(LTPosX + (j + 1) * STEP, LTPosY + i * STEP, &SnakeHead[2], SRCAND);
				tail[0] = i;
				tail[1] = j;
				map[i][j] = 6;
				setfillcolor(SnakeColor);
				solidrectangle(LTPosX + j * STEP, LTPosY + i * STEP,
					LTPosX + j * STEP + STEP - 1, LTPosY + i * STEP + STEP - 1);
				SnakeLength = 2;
				return true;
			}
		}
	}
	if (sum == 10)
	{
		for (int i = 1; i < MapRow - 1; i++)
		{
			for (int j = 1; j < MapCol - 1; j++)
			{
				if (map[i][j] == 0)
				{
					if (map[i - 1][j] == 0)
					{
						head[0] = i - 1;
						head[1] = j;
						map[i - 1][j] = 2;
						putimage(LTPosX + j * STEP, LTPosY + (i - 1) * STEP, &SnakeHead[0], SRCAND);
						tail[0] = i;
						tail[1] = j;
						map[i][j] = 2;
						setfillcolor(SnakeColor);
						solidrectangle(LTPosX + j * STEP, LTPosY + i * STEP,
							LTPosX + j * STEP + STEP - 1, LTPosY + i * STEP + STEP - 1);
						SnakeLength = 2;
						return true;
					}
					else if (map[i][j + 1] == 0)
					{
						head[0] = i;
						head[1] = j + 1;
						map[i][j + 1] = 6;
						putimage(LTPosX + (j + 1) * STEP, LTPosY + i * STEP, &SnakeHead[2], SRCAND);
						tail[0] = i;
						tail[1] = j;
						map[i][j] = 6;
						setfillcolor(SnakeColor);
						solidrectangle(LTPosX + j * STEP, LTPosY + i * STEP,
							LTPosX + j * STEP + STEP - 1, LTPosY + i * STEP + STEP - 1);
						SnakeLength = 2;
						return true;
					}
				}
			}
		}
	}
	return false;
}
void Map::Record(int mode)
{
	ofstream file(".\\Save&Load\\Save.sav", ios::binary | ios::_Nocreate);
	if (!file.is_open())
	{
		closegraph();
		cout << "Save Document Wrong!" << endl;
		exit(EXIT_FAILURE);
	}
	file.seekp(0, ios::end); // �����ļ�ĩβ
	file << mode<<' ';
	file << score<<' ';
	file << OwnerName;
	file << '\n';
	file.close();
}
void Map::GameOver(int mode,time_t t)
{
	ShowInfo(mode, t);
	mciSendString(_T("play .\\Music\\gameover.mp3 repeat"), 0, 0, 0);
	mciSendString(_T("stop .\\Music\\play.mp3"), 0, 0, 0);
	Record(mode);
	MessageBox(_hWnd, _T("���η����Ѽ�¼"), _T("GameOver"), MB_OK);
	mciSendString(_T("stop .\\Music\\gameover.mp3"), 0, 0, 0);
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
}
void Map::Ready()
{
	char ch = 0;
	while (ch = _getch())
	{
		if (ch == '\r')
			break;
	}
}
bool Map::CommandValid(char direction, char PreState)
{
	if (direction != 'w' && direction != 'a' && direction != 's' && direction != 'd')
		return false;
	if (direction == 'w' && (PreState == '8' || PreState=='2'))
		return false;
	if (direction == 's' && (PreState == '2' || PreState == '8'))
		return false;
	if (direction == 'a' && (PreState == '6' || PreState == '4'))
		return false;
	if (direction == 'd' && (PreState == '4' || PreState == '6'))
		return false;
	return true;
}
bool Map::Death(char command)
{
	if (command == '2')
	{
		if ((map[head[0]-1][head[1]] >= 4 && map[head[0] - 1][head[1]] <= 6)
			|| map[head[0] - 1][head[1]] == 2 || map[head[0] - 1][head[1]] == 8)
			return true;
	}
	else if (command == '8')
	{
		if ((map[head[0] + 1][head[1]] >= 4 && map[head[0] + 1][head[1]] <= 6)
			|| map[head[0] + 1][head[1]] == 2 || map[head[0] + 1][head[1]] == 8)
			return true;
	}
	else if (command == '4')
	{
		if ((map[head[0]][head[1] - 1] >= 4 && map[head[0]][head[1] - 1] <= 6)
			|| map[head[0]][head[1] - 1] == 2 || map[head[0]][head[1] - 1] == 8)
			return true;
	}
	else if (command=='6')
	{
		if ((map[head[0]][head[1] + 1] >= 4 && map[head[0]][head[1] + 1] <= 6)
			|| map[head[0]][head[1] + 1] == 2 || map[head[0]][head[1] + 1] == 8)
			return true;
	}
	return false;
}
char Map::SwitchCommand(char command)
{
	switch (command)
	{
		case 'w':
			return '2';
			break;
		case 's':
			return '8';
			break;
		case 'a':
			return '4';
			break;
		case 'd':
			return '6';
			break;
		default:
			break;
	}
	return 0;
}
bool Map::FoodConfirm(unsigned short value)
{
	if (value == 1 || value == 3 || value == 7 || value == 9)
	{
		SnakeLength++;
		if (value == 1)
			score++;
		else if (value == 3)
			score += 3;
		else if (value == 7)
			score += 7;
		else if (value == 9)
			score += 9;
		return true;
	}
	return false;
}
bool Map::FoodConfirm_S(unsigned short value, int& ATBVALUE, BOSS& boss)
{
	if (value == 1 || value == 3 || value == 7 || value == 9)
	{
		ATBVALUE += 10;
		boss.Kill(value);
		return true;
	}
	return false;
}
void Map::MoveAnime(char command)
{
	bool HaveFood = false;
	setfillcolor(SnakeColor);
	solidrectangle(LTPosX + head[1] * STEP, LTPosY + head[0] * STEP,
		LTPosX + head[1] * STEP + STEP-1, LTPosY + head[0] * STEP + STEP-1);
	// Ĩȥ����ͷ
	if (command == '2')
	{ // ��ͷ�����ƶ�
		map[head[0]][head[1]] = 2;
		head[0]--;
		HaveFood = FoodConfirm(map[head[0]][head[1]]);
		map[head[0]][head[1]] = 2; // ����ͷ������ͷmapֵ���䣬�൱�ڱ����˷���
		putimage(LTPosX + head[1] * STEP, LTPosY + head[0] * STEP, &SnakeHead[0],SRCAND); // ��ʾ����ͷ
	}
	else if (command == '8')
	{ // ��ͷ�����ƶ�
		map[head[0]][head[1]] = 8;
		head[0]++;
		HaveFood = FoodConfirm(map[head[0]][head[1]]);
		map[head[0]][head[1]] = 8;
		putimage(LTPosX + head[1] * STEP, LTPosY + head[0] * STEP, &SnakeHead[3], SRCAND); // ��ʾ����ͷ
	}
	else if (command == '4')
	{ // ��ͷ�����ƶ�
		map[head[0]][head[1]] = 4;
		head[1]--;
		HaveFood = FoodConfirm(map[head[0]][head[1]]);
		map[head[0]][head[1]] = 4;
		putimage(LTPosX + head[1] * STEP, LTPosY + head[0] * STEP, &SnakeHead[1], SRCAND); // ��ʾ����ͷ
	}
	else if (command == '6')
	{
		map[head[0]][head[1]] = 6;
		head[1]++;
		HaveFood = FoodConfirm(map[head[0]][head[1]]);
		map[head[0]][head[1]] = 6;
		putimage(LTPosX + head[1] * STEP, LTPosY + head[0] * STEP, &SnakeHead[2],SRCAND); // ��ʾ����ͷ
	}
	

	// ������β
	if (!HaveFood)
	{
		setfillcolor(BackGroundColor);
		solidrectangle(LTPosX + tail[1] * STEP, LTPosY + tail[0] * STEP,
			LTPosX + tail[1] * STEP + STEP-1, LTPosY + tail[0] * STEP + STEP-1);
	}
	if (map[tail[0]][tail[1]] == 2)
	{
		if (!HaveFood) // û�Ե�ʳ�ԭ��β�ͱ�գ�β��λ���޸�
		{
			map[tail[0]][tail[1]] = 0;
			tail[0]--;
		}
		
	}
	else if (map[tail[0]][tail[1]] == 8)
	{
		if (!HaveFood)
		{
			map[tail[0]][tail[1]] = 0;
			tail[0]++;
		}
	}
	else if (map[tail[0]][tail[1]] == 4)
	{
		if (!HaveFood)
		{
			map[tail[0]][tail[1]] = 0;
			tail[1]--;
		}
	}
	else if (map[tail[0]][tail[1]] == 6)
	{
		if (!HaveFood)
		{
			map[tail[0]][tail[1]] = 0;
			tail[1]++;
		}
	}	
}
void Map::MoveAnime_S(char command, int& ATBVALUE, BOSS& boss)
{
	bool HaveFood = false;
	setfillcolor(SnakeColor);
	solidrectangle(LTPosX + head[1] * STEP, LTPosY + head[0] * STEP,
		LTPosX + head[1] * STEP + STEP - 1, LTPosY + head[0] * STEP + STEP - 1);
	// Ĩȥ����ͷ
	if (command == '2')
	{ // ��ͷ�����ƶ�
		map[head[0]][head[1]] = 2;
		head[0]--;
		HaveFood = FoodConfirm_S(map[head[0]][head[1]], ATBVALUE, boss);
		map[head[0]][head[1]] = 2; // ����ͷ������ͷmapֵ���䣬�൱�ڱ����˷���
		putimage(LTPosX + head[1] * STEP, LTPosY + head[0] * STEP, &SnakeHead[0], SRCAND); // ��ʾ����ͷ
	}
	else if (command == '8')
	{ // ��ͷ�����ƶ�
		map[head[0]][head[1]] = 8;
		head[0]++;
		HaveFood = FoodConfirm_S(map[head[0]][head[1]], ATBVALUE, boss);
		map[head[0]][head[1]] = 8;
		putimage(LTPosX + head[1] * STEP, LTPosY + head[0] * STEP, &SnakeHead[3], SRCAND); // ��ʾ����ͷ
	}
	else if (command == '4')
	{ // ��ͷ�����ƶ�
		map[head[0]][head[1]] = 4;
		head[1]--;
		HaveFood = FoodConfirm_S(map[head[0]][head[1]], ATBVALUE, boss);
		map[head[0]][head[1]] = 4;
		putimage(LTPosX + head[1] * STEP, LTPosY + head[0] * STEP, &SnakeHead[1], SRCAND); // ��ʾ����ͷ
	}
	else if (command == '6')
	{
		map[head[0]][head[1]] = 6;
		head[1]++;
		HaveFood = FoodConfirm_S(map[head[0]][head[1]], ATBVALUE, boss);
		map[head[0]][head[1]] = 6;
		putimage(LTPosX + head[1] * STEP, LTPosY + head[0] * STEP, &SnakeHead[2], SRCAND); // ��ʾ����ͷ
	}


	// ������β
	if (!HaveFood)
	{
		setfillcolor(BackGroundColor);
		solidrectangle(LTPosX + tail[1] * STEP, LTPosY + tail[0] * STEP,
			LTPosX + tail[1] * STEP + STEP - 1, LTPosY + tail[0] * STEP + STEP - 1);
	}
	if (map[tail[0]][tail[1]] == 2)
	{
		if (!HaveFood) // û�Ե�ʳ�ԭ��β�ͱ�գ�β��λ���޸�
		{
			map[tail[0]][tail[1]] = 0;
			tail[0]--;
		}

	}
	else if (map[tail[0]][tail[1]] == 8)
	{
		if (!HaveFood)
		{
			map[tail[0]][tail[1]] = 0;
			tail[0]++;
		}
	}
	else if (map[tail[0]][tail[1]] == 4)
	{
		if (!HaveFood)
		{
			map[tail[0]][tail[1]] = 0;
			tail[1]--;
		}
	}
	else if (map[tail[0]][tail[1]] == 6)
	{
		if (!HaveFood)
		{
			map[tail[0]][tail[1]] = 0;
			tail[1]++;
		}
	}
}
bool Map::NoFood()
{
	for (int i = 0; i < MapRow; i++)
	{
		for (int j = 0; j < MapCol; j++)
		{
			if (map[i][j] == 1 || map[i][j] == 3 || map[i][j] == 7 || map[i][j] == 9)
				return false;
		}
	}
	return true;
}
void Map::CreateFood(int num)
{
	// ���ɡ���ʾʳ��
	for (int i = 0; i < num;)
	{
		int tmpx = rand() % (MapCol - 1) + 1;
		int tmpy = rand() % (MapRow - 1) + 1;
		if (map[tmpy][tmpx] == 0)
		{
			int value = rand() % 4;
			if (value == 0)
			{
				map[tmpy][tmpx] = 1;
				putimage(LTPosX + tmpx * STEP, LTPosY + tmpy * STEP, &food[0]);
			}
			else if (value == 1)
			{
				map[tmpy][tmpx] = 3;
				putimage(LTPosX + tmpx * STEP, LTPosY + tmpy * STEP, &food[1]);
			}
			else if (value == 2)
			{
				map[tmpy][tmpx] = 7;
				putimage(LTPosX + tmpx * STEP, LTPosY + tmpy * STEP, &food[2]);
			}
			else
			{
				map[tmpy][tmpx] = 9;
				putimage(LTPosX + tmpx * STEP, LTPosY + tmpy * STEP, &food[3]);
			}
			i++;
		}
	}
}
void Map::SnakeToWall()
{ // ͬʱ�����ԭ�е�ʳ��
	for (int i = 0; i < MapRow; i++)
	{
		for (int j = 0; j < MapCol; j++)
		{
			if (map[i][j] == 1 || map[i][j] == 3 || map[i][j] == 7 || map[i][j] == 9)
			{
				map[i][j] = 0;
				setfillcolor(BackGroundColor);
				solidrectangle(LTPosX + j * STEP, LTPosY + i * STEP,
					LTPosX + j * STEP + STEP - 1, LTPosY + i * STEP + STEP - 1);
			}
			else if (map[i][j]!=0 && map[i][j] % 2 == 0)
			{
				map[i][j] = 5;
				putimage(LTPosX + j * STEP, LTPosY + i * STEP, &wall);
			}
		}
	}
}
void Map::SnakeToFood()
{ // ͬʱ�����ԭ�е�ʳ��
	for (int i = 0; i < MapRow; i++)
	{
		for (int j = 0; j < MapCol; j++)
		{
			if (map[i][j] != 0 && map[i][j] % 2 == 0)
			{ // ��λ�������ߣ����ʳ��
				map[i][j] = 3;
				putimage(LTPosX + j * STEP, LTPosY + i * STEP, &food[1]);
			}
		}
	}
}
void Map::ShowATB(int ATB)
{
	setlinecolor(0xffffff);
	setfillcolor(0x000000);
	solidrectangle(-500, -10, -500 + 210, -5); // clean
	if (ATB < 100)
	{
		setfillcolor(0xA39B70);
		fillrectangle(-500, -10, -500 + ATB, -5); // չʾatb����
	}
	else if (ATB == 100)
	{
		setfillcolor(BackGroundColor);
		fillrectangle(-500, -10, -500 + ATB, -5); // չʾatb����
	}
	else if (ATB > 100 && ATB < 200)
	{
		setfillcolor(BackGroundColor);
		fillrectangle(-500, -10, -500 + 100, -5); // չʾatb����
		setfillcolor(0xA39B70);
		fillrectangle(-395, -10, -395 + ATB-100, -5); // չʾatb����
	}
	else if (ATB == 200)
	{
		setfillcolor(BackGroundColor);
		fillrectangle(-500, -10, -500 + 100, -5); // չʾatb����
		setfillcolor(BackGroundColor);
		fillrectangle(-395, -10, -395 + +100, -5); // չʾatb����
	}
}
void Map::ShowStrategy()
{
	putimage(StrX, StrY, &choosen); // Ĭ��ѡ��һ
	putimage(StrX, StrY + 35, &unchoosen);
	putimage(StrX, StrY + 70, &unchoosen);
	putimage(StrX, StrY + 105, &unchoosen);
	putimage(StrX, StrY + 140, &unchoosen);
	putimage(StrX, StrY + 175, &unchoosen);
	settextcolor(RGB(0xff, 0xff, 0xff));
	setbkmode(TRANSPARENT);
	outtextxy(StrX+5, StrY+5, ATB[0]);
	outtextxy(StrX + 5, StrY + 40, ATB[1]);
	outtextxy(StrX + 5, StrY + 75, ATB[2]);
	outtextxy(StrX + 5, StrY + 110, ATB[3]);
	outtextxy(StrX + 5, StrY + 145, ATB[4]);
	outtextxy(StrX + 5, StrY + 180, ATB[5]);
}
void Map::_GetPos(int& y, int pos)
{
	switch (pos)
	{
		case 0:
			y = 5;
			break;
		case 1:
			y = 40;
			break;
		case 2:
			y = 75;
			break;
		case 3:
			y = 110;
			break;
		case 4:
			y = 145;
			break;
		case 5:
			y = 180;
			break;
		default:
			break;
	}
}
void Map::Kill(int Pos, BOSS& boss)
{
	if (Pos == 0) // ��
		boss.ATBKill(1);
	else if (Pos == 1)
		boss.ATBKill(3);
	else if (Pos == 2)
		boss.ATBKill(7);
	else if (Pos == 3)
		boss.ATBKill(9);
}
void Map::ShowInsight()
{
	outtextxy(-530, -190, _T("��ʿ�в�ͬ���� ʳ����˺�"));
	outtextxy(-530, -160, _T("���ݷ�VS�� ��VS����ɸ����˺�"));
	outtextxy(-530, -130, _T("���ܿ�����ȫ�ֵ�ͬ���Թ���"));
}
bool Map::ChooseStrategy(int& ATB, MOUSEMSG _Mouse, int& Pos, BOSS& boss)
{
	int y = 0;
	settextcolor(0xffffff);
	if (_Mouse.wheel < 0)
	{ // ���¹���
		_GetPos(y, Pos);
		putimage(StrX, StrY + y - 5, &unchoosen);
		outtextxy(StrX + 5, StrY + y, Map::ATB[Pos]);
		Pos++;
		if (Pos == 6)
			Pos = 0;
		_GetPos(y, Pos);
		putimage(StrX, StrY + y - 5, &choosen);
		outtextxy(StrX + 5, StrY + y, Map::ATB[Pos]);
	}
	else if (_Mouse.wheel > 0)
	{ // ���Ϲ���
		_GetPos(y, Pos);
		putimage(StrX, StrY + y - 5, &unchoosen);
		outtextxy(StrX + 5, StrY + y, Map::ATB[Pos]);
		Pos--;
		if (Pos == -1)
			Pos = 5;
		_GetPos(y, Pos);
		putimage(StrX, StrY + y - 5, &choosen);
		outtextxy(StrX + 5, StrY + y, Map::ATB[Pos]);
	}
	if (_Mouse.mkLButton)
	{
		if (Pos != 5 && ATB >= 100)
		{
			ATB -= 100;
			if (Pos != 4)
				Kill(Pos, boss);
			else
				Life += 100;
			return true;
		}
		else if (Pos == 5 && ATB == 200)
		{
			ATB = 0;
			ShowInsight();
			return true;
		}
	}
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
	return false;
}
bool Map::ATBStrategy(int& ATB, BOSS& boss, time_t& offset, bool& launched, time_t past)
{
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
	time_t now;
	int SleepTime = 41;
	int times = 0;
	MOUSEMSG _Mouse;
	int Pos = 0; // ��ʼ�ڵ�0ѡ�
	ShowStrategy(); // ���Գ�ʼ����
	while (true)
	{
		time(&now); // ��ȡĿǰʱ��
		offset = now - past; // �Ѿ������ʱ��
		times++;
		ShowATB(ATB);
		Sleep(SleepTime);
		RandomWall(offset, launched);
		if (MouseHit())
		{ // �������Ϣ
			_Mouse = GetMouseMsg();
			if (_Mouse.wheel == 0 && !_Mouse.mkLButton && !_Mouse.mkRButton)
				FlushMouseMsgBuffer();
			else if (_Mouse.mkRButton)
			{ // ���Ҽ����˳�ѡ��
				setfillcolor(0x000000);
				solidrectangle(-540, 0, -165, 304);
				FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
				return false;
			}
			else
			{ // ��������
				if (ChooseStrategy(ATB, _Mouse, Pos, boss))
				{
					setfillcolor(0x000000);
					solidrectangle(-540, 0, -165, 304);
					FlushMouseMsgBuffer();
					return false;
				}
			}
		}
		// �����Ƿ��������Ϣ����ִ�������Զ�ǰ��
		if (Death('0' + map[head[0]][head[1]]))
		{ // ����
			FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
			return true;
		}
		else if (times == 20)// �߻�
		{
			MoveAnime_S('0' + map[head[0]][head[1]], ATB, boss); // ��ͷ����ǰ��
			times = 0;
		}
		boss.ShowInfo(boss.GetBossShield(), Life);
	}
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
	return false;
}
bool Map::Quit()
{
	int choice;
	choice=MessageBox(_hWnd, _T("�˳���ǰ��Ϸ?\n��ģʽ������Ȳ��ᱣ��"), _T("Attention"), MB_YESNO);
	if (choice == IDYES)
	{
		mciSendString(_T("stop .\\Music\\play.mp3"), 0, 0, 0);
		return true;
	}
	else
		return false;
	return false;
}
void Map::GetTime(tm& t, time_t& now)
{
	time(&now);
	localtime_s(&t, &now);
}
void Map::GameOver_S()
{
	mciSendString(_T("play .\\Music\\gameover.mp3 repeat"), 0, 0, 0);
	mciSendString(_T("stop .\\Music\\Boss.mp3"), 0, 0, 0);
	MessageBox(_hWnd, _T("������ʿսʤ����"), _T("GameOver"), MB_OK);
	mciSendString(_T("stop .\\Music\\gameover.mp3"), 0, 0, 0);
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
}
void Map::GameWin()
{
	mciSendString(_T("play .\\Music\\win.mp3 repeat"), 0, 0, 0);
	mciSendString(_T("stop .\\Music\\Boss.mp3"), 0, 0, 0);
	MessageBox(_hWnd, _T("��սʤ�˱�����ʿ"), _T("You Win!"), MB_OK);
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
}
void Map::GetHighestScore(int mode)
{
	ifstream file(".\\Save&Load\\Save.sav", ios::binary);
	if (!file.is_open())
	{
		closegraph();
		cout << "Save Document Wrong!" << endl;
		exit(EXIT_FAILURE);
	}
	int score_tmp, max=0, mode_tmp;
	char tmp[11] = { '\0' };
	while (true)
	{
		mode_tmp = 0;
		file >> mode_tmp >> score_tmp;
		file.getline(tmp, 11);
		if (mode_tmp == 0)
			break;
		else if (mode_tmp == mode)
		{
			if (max < score_tmp)
				max = score_tmp;
		}
	}
	Map::HighestScore = max;
	file.close();
}
void Map::RandomWall(time_t offset, bool& launched)
{
	if (offset == 53 || offset == 129)
	{ // ������ǰһ����ʾ��������
		settextcolor(RGB(0xff, rand() % 256, rand() % 256));
		outtextxy(-530, -250, _T("����ǽ��"));
	}
	if (offset == 55 || offset==130)
	{
		launched = false;
		settextcolor(0x000000);
		setbkmode(OPAQUE);
		outtextxy(-530, -250, _T("        "));
		setbkmode(TRANSPARENT);
	}
	if (offset == 78 || offset == 155)
	{ // ������ǰ����
		setfillcolor(BackGroundColor);
		for (int i = 1; i < MapRow - 1; i++)
		{
			for (int j = 1; j < MapCol - 1; j++)
			{
				if (map[i][j] == 5)
				{
					map[i][j] = 0;
					solidrectangle(LTPosX + j * STEP, LTPosY + i * STEP,
						LTPosX + j * STEP + STEP - 1, LTPosY + i * STEP + STEP - 1);
				}
			}
		}
	}
	if ((offset==54 || offset==129) && !launched)
	{ // δ���� �ҷ���ʱ������
		launched = true;
		
		for (int num = 0; num < 40;)
		{
			int x = rand() % (MapRow - 2) + 1;
			int y = rand() % (MapCol - 2) + 1;
			if (map[x][y] == 0)
			{
				map[x][y] = 5;
				putimage(LTPosX + y * STEP, LTPosY + x * STEP, &wall);
				num++;
			}
		}
	}
}
void Map::SpreadShield(time_t offset, bool& launched, int ShieldMode)
{
	if (offset == 53 || offset == 90)
	{ // ������ǰһ����ʾ��������
		settextcolor(RGB(0xff, rand() % 256, rand() % 256));
		outtextxy(-400, -250, _T("������ɢ"));
	}
	if (offset == 55 || offset == 92)
	{
		launched = false;
		settextcolor(0x000000);
		setbkmode(OPAQUE);
		outtextxy(-400, -250, _T("        "));
		setbkmode(TRANSPARENT);
	}
	int FoodNum;
	switch (ShieldMode)
	{
		case 1:
			FoodNum = 0;
			break;
		case 3:
			FoodNum = 1;
			break;
		case 7:
			FoodNum = 2;
			break;
		case 9:
			FoodNum = 3;
			break;
	}
	if ((offset == 54 || offset == 91) && !launched)
	{ // δ���� �ҷ���ʱ������
		launched = true;

		for (int num = 0; num < 5;)
		{
			int x = rand() % (MapRow - 2) + 1;
			int y = rand() % (MapCol - 2) + 1;
			if (map[x][y] == 0)
			{
				map[x][y] = ShieldMode;
				putimage(LTPosX + y * STEP, LTPosY + x * STEP, &food[FoodNum]);
				num++;
			}
		}
	}
}
void Map::Decrease(time_t offset)
{
	static time_t tmp= offset;
	if (tmp != offset)
	{
		Life-=2;
		tmp = offset;
	}
}
void Map::PlayMode1()
{
	GetHighestScore(1);
	time_t offset = 0;
	time_t past, now; // ���ڻ�ȡ��ǰʱ��
	time_t sleep = 0;
	mciSendString(_T("play .\\Music\\play.mp3 repeat"), 0, 0, 0);
	Life = 1; // һ����
	init(1); // ��ʼ����ͼ
	Ready(); // ȷ����ҿ�ʼ
	time(&past);
	while (true)
	{
		time(&now); // ��ȡĿǰʱ��
		offset = now - past - sleep; // �Ѿ������ʱ��
		if (NoFood())
			CreateFood(rand() % 5 + 1);
		Sleep(125 - SnakeLength); // ֡�� 8->�ɼӿ�
		if (_kbhit())
		{ // �м�����Ϣ,ֻ֧��Сд
			char command = _getch();
			// ����Ҫ�����û��Ұ�һͨ�����⣬ʵ�����鲢������Ӱ��
			if (command == 'q')
			{
				time_t past_Q = time(&past_Q);
				if (Quit())
					break;
				time_t now_Q = time(&now_Q);
				sleep += (now_Q - past_Q);
			}
			if (CommandValid(command, '0' + map[head[0]][head[1]])) // �ж��Ƿ�Ϊ��Ҫ�����ָ��
			{ // ��Чָ��
				command = SwitchCommand(command); // �޸�commandΪ�ַ�����ָ��
				if (Death(command))
				{ // ����
					GameOver(2, offset);
					break;
				}
				else // �߻�
					MoveAnime(command);
			}
			else
			{ // ��Чָ��
				if (Death('0' + map[head[0]][head[1]]))
				{ // ����
					GameOver(2, offset);
					break;
				}
				else
					MoveAnime('0' + map[head[0]][head[1]]);
			}
		}
		else
		{ // �޼�����Ϣ
			if (Death('0' + map[head[0]][head[1]]))
			{ // ����
				GameOver(2, offset);
				break;
			}
			else // �߻�
				MoveAnime('0' + map[head[0]][head[1]]); // ��ͷ����ǰ��
		}
		ShowInfo(1, offset);
	}
}
void Map::PlayMode2()
{
	GetHighestScore(2);
	time_t offset = 0;
	time_t past, now; // ���ڻ�ȡ��ǰʱ��
	mciSendString(_T("play .\\Music\\play.mp3 repeat"), 0, 0, 0);
	Life = 765; // �㹻Ҫ��
	init(2); // ��ʼ����ͼ
	Ready(); // ȷ����ҿ�ʼ
	time(&past);
	while (true)
	{
		time(&now); // ��ȡĿǰʱ��
		offset = now - past; // �Ѿ������ʱ��
		if (NoFood())
			CreateFood(rand() % 5 + 1);
		Sleep(125 - SnakeLength); // ֡�� 8->�ɼӿ�
		if (_kbhit())
		{ // �м�����Ϣ
			char command = _getch();
			// ����Ҫ�����û��Ұ�һͨ�����⣬ʵ�����鲢������Ӱ��
			if (command == 'q')
			{
				if (Quit())
					break;
			}
			if (CommandValid(command, '0' + map[head[0]][head[1]])) // �ж��Ƿ�Ϊ��Ҫ�����ָ��
			{ // ��Чָ��
				command = SwitchCommand(command); // �޸�commandΪ�ַ�����ָ��
				if (Death(command))
				{ // ����
					Life--;
					if (Life == 0)
					{
						GameOver(2, offset);
						break;
					}
					else
					{
						SnakeToWall();
						CreateFood(rand() % 5 + 1);
						if (!CreateSnake())
						{
							GameOver(2, offset);
							break;
						}
						Ready();
					}
					
				}
				else // �߻�
					MoveAnime(command);
			}
			else
			{ // ��Чָ��
				if (Death('0' + map[head[0]][head[1]]))
				{ // ����
					Life--;
					if (Life == 0)
					{
						GameOver(2, offset);
						break;
					}
					else
					{
						SnakeToWall();
						CreateFood(rand() % 5 + 1);
						if (!CreateSnake())
						{
							GameOver(2, offset);
							break;
						}
						Ready();
					}
				}
				else
					MoveAnime('0' + map[head[0]][head[1]]);
			}
		}
		else
		{ // �޼�����Ϣ
			if (Death('0' + map[head[0]][head[1]]))
			{ // ����
				Life--;
				if (Life == 0)
				{
					GameOver(2, offset);
					break;
				}
				else
				{
					SnakeToWall();
					CreateFood(rand() % 5 + 1);
					if (!CreateSnake())
					{
						GameOver(2, offset);
						break;
					}
					Ready();
				}
			}
			else // �߻�
				MoveAnime('0' + map[head[0]][head[1]]); // ��ͷ����ǰ��
		}
		ShowInfo(2, offset);
	}
	Record(2);
}
void Map::PlayMode3()
{
	GetHighestScore(3);
	time_t offset = 0;
	time_t past, now; // ���ڻ�ȡ��ǰʱ��
	mciSendString(_T("play .\\Music\\play.mp3 repeat"), 0, 0, 0);
	Life = 5; 
	init(3); // ��ʼ����ͼ
	Ready(); // ȷ����ҿ�ʼ
	time(&past);
	while (true)
	{
		time(&now); // ��ȡĿǰʱ��
		offset = now - past; // �Ѿ������ʱ��
		if (NoFood())
			CreateFood(rand() % 5 + 1);
		Sleep(125 - SnakeLength); // ֡�� 8->�ɼӿ�
		if (_kbhit())
		{ // �м�����Ϣ
			char command = _getch();
			// ����Ҫ�����û��Ұ�һͨ�����⣬ʵ�����鲢������Ӱ��
			if (command == 'q')
			{
				if (Quit())
					break;
			}
			if (CommandValid(command, '0' + map[head[0]][head[1]])) // �ж��Ƿ�Ϊ��Ҫ�����ָ��
			{ // ��Чָ��
				command = SwitchCommand(command); // �޸�commandΪ�ַ�����ָ��
				if (Death(command))
				{ // ����
					Life--;
					if (Life == 0)
					{
						GameOver(3, offset);
						break;
					}
					else
					{
						SnakeToFood();
						CreateFood(rand() % 5 + 1);
						if (!CreateSnake())
						{
							GameOver(3, offset);
							break;
						}
						Ready();
					}

				}
				else // �߻�
					MoveAnime(command);
			}
			else
			{ // ��Чָ��
				if (Death('0' + map[head[0]][head[1]]))
				{ // ����
					Life--;
					if (Life == 0)
					{
						GameOver(3, offset);
						break;
					}
					else
					{
						SnakeToFood();
						CreateFood(rand() % 5 + 1);
						if (!CreateSnake())
						{
							GameOver(3, offset);
							break;
						}
						Ready();
					}
				}
				else
					MoveAnime('0' + map[head[0]][head[1]]);
			}
		}
		else
		{ // �޼�����Ϣ
			if (Death('0' + map[head[0]][head[1]]))
			{ // ����
				Life--;
				if (Life == 0)
				{
					GameOver(3, offset);
					break;
				}
				else
				{
					SnakeToFood();
					CreateFood(rand() % 5 + 1);
					if (!CreateSnake())
					{
						GameOver(3, offset);
						break;
					}
					Ready();
				}
			}
			else // �߻�
				MoveAnime('0' + map[head[0]][head[1]]); // ��ͷ����ǰ��
		}
		ShowInfo(3, offset);
	}
}
void Map::PlayStory()
{
	settextcolor(0x000000);
	gettextstyle(&f);
	f.lfHeight = 20;
	f.lfWidth = 12;
	_tcscpy(f.lfFaceName, _T("����"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	STORY story;
	settextcolor(0x000000);
	for (int i = 0; i < 5; i++)
	{
		story.EveryCut();
		Ready();
	}
	// chapter1
	story.EveryCut();
	Ready();
	for (int i = 0; i < 8; i++)
	{
		story.EveryCut(true, i / 2 % 2);
		Ready();
	}
	if (!PlaySpecial())
		return;
	// chapter2
	
	settextcolor(0x000000);
	story.EveryCut();
	Ready();
	for (int i = 0; i < 4; i++)
	{
		story.EveryCut(true, i / 2 % 2);
		Ready();
	}
	mciSendString(_T("stop .\\Music\\win.mp3"), 0, 0, 0);
	mciSendString(_T("play .\\Music\\story.mp3 repeat"), 0, 0, 0);
	for (int i = 0; i < 4; i++)
	{
		story.EveryCut(true, i / 2 % 2);
		Ready();
	}
	for (int i = 0; i < 6; i++)
	{
		story.EveryCut(true, 1);
		Ready();
	}
	story.EveryCut(true, 0);
	Ready();
	story.EveryCut(true, 1);
	Ready();
	story.EveryCut(true, 0);
	Ready();
	story.EveryCut(true, 0);
	Ready();
	story.EveryCut(true, 0);
	Ready();
	story.EveryCut(true, 1);
	Ready();
	story.EveryCut(true, 1);
	Ready();
	story.EveryCut(true, 0);
	Ready();
	story.EveryCut(true, 1);
	Ready();
	story.EveryCut(true, 0);
	Ready();
	story.EveryCut(true, 0);
	Ready();
	setfillcolor(0x000000);
	solidrectangle(-540, -304, 540, 304);
	// ����
	settextcolor(0xffffff);
	Sleep(3000);
	outtextxy(-100, -10, _T("������  Peking_Neo"));
	Sleep(6000);
	solidrectangle(-540, -304, 540, 304);
	outtextxy(-200, -10, _T("ʳ�����ͼ�����͵¡���ͼƬ����������"));
	Sleep(6000);
	solidrectangle(-540, -304, 540, 304);
	outtextxy(-70, -10, _T("�����Ϊԭ��"));
	Sleep(6000);
	solidrectangle(-540, -304, 540, 304);
	outtextxy(-180, -10, _T("�������� FF7Re WordGame ����ϵ��й�"));
	Sleep(6000);
	solidrectangle(-540, -304, 540, 304);
	outtextxy(-140, -10, _T("And Thank You For Your Time"));
	Sleep(6000);
	mciSendString(_T("stop .\\Music\\story.mp3"), 0, 0, 0);
}
bool Map::PlaySpecial()
{
	bool if_BigWall = false, if_Shield = false, if_RandomWall = false; // �������ܾ�δ����
	time_t offset = 0;
	time_t past, now; // ���ڻ�ȡ��ǰʱ��
	time_t sleep = 0;
	int SleepTime = 125; // �����ٶ�
	int ATBVALUE = 0; // ����atb����
	BOSS boss(5000, 10); // 5000Ѫ�����޻���
	Life = 500; // �˴����⣬Ϊ����ֵ500
	init(5); // ��ʼ����ͼ
	Ready(); // ȷ����ҿ�ʼ
	mciSendString(_T("play .\\Music\\Boss.mp3 repeat"), 0, 0, 0);
	time(&past);
	boss.ShowInfo(10, Life);
	time_t tmp = 0;
	while (true)
	{
		if (boss.GetBossLife() <= 0)
		{
			GameWin();
			return true;
		}
		time(&now); // ��ȡĿǰʱ��
		offset = now - past - sleep; // �Ѿ������ʱ��
		if (offset != tmp)
		{
			ATBVALUE++;
			tmp = offset;
		}
		Decrease(offset);
		RandomWall(offset, if_RandomWall); // boss���� 
		SpreadShield(offset, if_Shield, boss.GetBossShield());
		if (offset % 26 == 0)
			boss.NewShield(); // �����������
		if (ATBVALUE > 200)
			ATBVALUE = 200;
		ShowATB(ATBVALUE);
		if (NoFood())
			CreateFood(rand() % 5 + 1); // ʳ���������������ʳ��
		Sleep(SleepTime); // ֡��
		if (_kbhit())
		{ // �м�����Ϣ
			char command = _getch();
			// ����Ҫ�����û��Ұ�һͨ�����⣬ʵ�����鲢������Ӱ��
			if (command == ' ') // �пո��������ATB�ӵ�ʱ��
			{
				FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
				if (ATBStrategy(ATBVALUE, boss, offset, if_RandomWall, past))
				{
					GameOver_S();
					return false;
				}
			}
			else if (CommandValid(command, '0' + map[head[0]][head[1]])) // �ж��Ƿ�Ϊ��Ҫ�����ָ��
			{ // ��Чָ��
				command = SwitchCommand(command); // �޸�commandΪ�ַ�����ָ��
				if (Death(command))
				{ // ����
					GameOver_S();
					return false;
				}
				else // �߻�
					MoveAnime_S(command, ATBVALUE, boss);
			}
			else
			{ // ��Чָ��
				if (Death('0' + map[head[0]][head[1]]))
				{ // ����
					GameOver_S();
					return false;
				}
				else
					MoveAnime_S('0' + map[head[0]][head[1]], ATBVALUE, boss);
			}
		}
		else
		{ // �޼�����Ϣ
			if (Death('0' + map[head[0]][head[1]]))
			{ // ����
				GameOver_S();
				return false;
			}
			else // �߻�
				MoveAnime_S('0' + map[head[0]][head[1]], ATBVALUE, boss); // ��ͷ����ǰ��
		}
		boss.ShowInfo(boss.GetBossShield(), Life);
	}
}


STORY::STORY()
{
	for (int i = 0; i < 50; i++)
		LineContent[i] = '\0';
	ContentPosX = -300;
	ContentPosY = 185;
	file.open(".\\Story\\Chapter.txt", ios::binary);
	if (!file.is_open())
	{
		exit(EXIT_FAILURE);
	}
	locale china("zh_CN.utf-8");
	file.imbue(china);
	loadimage(&chara[0], _T(".\\Image\\story_snake.jpg"));
	loadimage(&chara[1], _T(".\\Image\\story_cloud.jpg"));
	loadimage(&enemy, _T(".\\Image\\soldier.jpg"));
	loadimage(&CG, _T(".\\Image\\city.jpg"));
	loadimage(&card, _T(".\\Image\\card.jpg"));
}
STORY::~STORY()
{
	file.close();
}
void STORY::EveryCut(bool mode, int name)
{
	Showcity();
	if (mode)
	{ // ��Ҫ��ʾ����
		putimage(-540, -304, &chara[name]);
	}
	Showcard();
	readline();
	putline();
}
void STORY::Showcard()
{
	putimage(CardX, CardY, &card);
}
void STORY::Showcity()
{
	putimage(-540, -304, &CG);
}
void STORY::readline()
{
	file.getline(LineContent, 50);
}
void STORY::putline()
{
	setbkmode(TRANSPARENT);
	outtextxy(ContentPosX, ContentPosY, LineContent);
}
void STORY::RaceGame()
{

}

BOSS::BOSS(int life, int element) :bosslife(life), shield(element) 
{
	gettextstyle(&f);
	f.lfHeight = 20;
	f.lfWidth = 11;
	_tcscpy(f.lfFaceName, _T("����"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	setbkmode(TRANSPARENT);
};
void BOSS::ShowInfo(int shieldmode, int snakelife)
{
	if (shieldmode == 1)
		settextcolor(FireColor);
	else if (shieldmode == 3)
		settextcolor(SnowColor);
	else if (shieldmode == 7)
		settextcolor(WindColor);
	else if (shieldmode == 9)
		settextcolor(LightningColor);
	else
		settextcolor(0xffffff);
	settextstyle(&f);
	outtextxy(-430, -280, _T("������ʿ"));
	setfillcolor(0x000000);
	solidrectangle(-500, -200, -499 + 5000 / 20, -205);
	setfillcolor(0x0000ff);
	setlinecolor(0xffffff);
	if (bosslife < 0)
		bosslife = 0;
	fillrectangle(-500, -200, -499 + bosslife / 20, -205);
	setfillcolor(0x000000);
	solidrectangle(-540, 274, -200, 304);
	settextcolor(BackGroundColor);
	ShowSnakeLife(snakelife);
}
void BOSS::ShowSnakeLife(int NowLife)
{
	TCHAR output[5] = _T("\0\0\0\0"); // ������������λ��
	int totallength = 0;
	for (;; totallength++)
	{
		if (NowLife / int(pow(10, totallength)) == 0)
			break;
	} // ��ȡ����
	for (int i = 0; i < totallength; i++)
	{
		output[i] = '0' + NowLife / int(pow(10, totallength - i - 1));
		NowLife = NowLife % int(pow(10, totallength - i - 1));
	}
	outtextxy(-520, 280, _T("����ֵ:"));
	outtextxy(-400, 280, output);
}
void BOSS::NewShield()
{
	int tmp = rand() % 4;
	if (tmp == 0)
		shield = 1;
	else if (tmp == 1)
		shield = 3;
	else if (tmp == 2)
		shield = 7;
	else if (tmp == 3)
		shield = 9;
}
int BOSS::GetBossLife()
{
	return bosslife;
}
int BOSS::GetBossShield()
{
	return shield;
}
void BOSS::Kill(int damage)
{
	if (damage == shield)
		return;
	else if (abs(damage - shield) == 2)
		bosslife -= 10;
	else
		bosslife -= 1;
}
void BOSS::ATBKill(int damage)
{
	if (damage == shield)
		return;
	else if (abs(damage - shield) == 2)
		bosslife -= 500;
	else
		bosslife -= 50;
}

void RANK::GetData()
{
	If_empty = false;
	ifstream file(".\\Save&Load\\Save.sav", ios::binary);
	if (!file.is_open())
	{
		closegraph();
		cout << "Save Document Wrong!" << endl;
		exit(EXIT_FAILURE);
	}
	rankinfo* p = NULL, * q = NULL;
	int i = 0, mode_tmp, score_tmp;
	char name_tmp[12] = { '\0' };
	while (true)
	{
		mode_tmp = 0;
		for (int i = 0; i < 12; i++)
			name_tmp[i] = '\0';
		file >> mode_tmp >> score_tmp;
		char ch = file.get();
		file.getline(name_tmp, 12);
		for (int i = 0; i < 12; i++)
		{
			if (name_tmp[i] == '\r')
				name_tmp[i] = '\0';
		}
		if (mode_tmp != 0) // ������ȡ
		{
			p = new(nothrow) rankinfo;
			if (p == NULL)
			{
				closegraph();
				cout << "No Memory" << endl;
				exit(EXIT_FAILURE);
			}
			p->mode = mode_tmp;
			p->score = score_tmp;
			for (int i = 0; i < 12; i++)
				p->name[i] = name_tmp[i];
			if (i == 0)
			{ // �״ζ�ȡ
				head = p;
				q = p;
			}
			else
			{ // ���״ζ�ȡ
				q->next = p;
				q = p;
			}
		}
		else
		{ // û�����ݿɶ�
			if (i != 0)
				p->next = NULL;
			break;
		}
		i++;
	}
	if (i == 0)
		If_empty = true; // ���а�Ϊ��
	total = i;
	file.close();
}
void RANK::del()
{
	rankinfo* p = head, * q = NULL;
	while (p != NULL)
	{
		q = p;
		p = p->next;
		delete q;
	}
}
void RANK::ShowAPiece(int no, rankinfo* p)
{
	TCHAR number = '0' + no + 1;
	outtextxy(RankPosX, RankPosY + no * 30, number);
	TCHAR modeNo = '0' + p->mode;
	outtextxy(RankPosX + 100, RankPosY + no * 30, modeNo);
	ShowScore(p->score, no);
	TCHAR nameTmp[12] = { '\0' };
	for (int i = 0; i < 12; i++)
		nameTmp[i] = p->name[i];
	outtextxy(RankPosX + 320, RankPosY + no * 30, nameTmp);
}
void RANK::statistic()
{
	rankinfo* p = head, * above = NULL;
	int i, j;
	for (i = 0; i < total - 1; i++)
	{
		p = head; // ÿ������ʼʱ��p����
		for (j = 0; j < total - i - 1; j++)
		{ // ð������
			if ((p->score < p->next->score))
			{ // ����С����һ����������Ų
				if (p == head) // ������Ҫ�Ķ��׸�
				{
					head = p->next; 
					p->next = p->next->next;
					head->next = p;
					// ������ɣ����������һ�ڵ�
					above = head;
				}
				else if (j == total - i - 2 && i == 0) // ��Ҫ�Ķ�β���
				{
					above->next = p->next;
					p->next->next = p;
					p->next = NULL;
				}
				else // �����ǸĶ���β�ڵ�
				{
					above->next = p->next;
					p->next = p->next->next;
					above->next->next = p;
					// ������ɣ����������һ�ڵ�
					above = above->next;
				}
			}
			else
			{
				above = p;
				p = p->next;
			}
		}
	}
}
void RANK::ShowScore(int NowScore, int no)
{
	TCHAR output[8] = _T("0\0\0\0\0\0\0"); // ����������7λ��
	int totallength = 0;
	for (;; totallength++)
	{
		if (NowScore / int(pow(10, totallength)) == 0)
			break;
	} // ��ȡ����
	for (int i = 0; i < totallength; i++)
	{
		output[i] = '0' + NowScore / int(pow(10, totallength - i - 1));
		NowScore = NowScore % int(pow(10, totallength - i - 1));
	}
	outtextxy(RankPosX + 200, RankPosY + no * 30, output);
}
bool RANK::cmp(char* query, char* in)
{
	for (int i = 0; i < 11; i++)
	{
		if (query[i] != in[i])
			return false;
	}
	return true;
}
void RANK::Query()
{
	setfillcolor(0x000000);
	solidrectangle(-540, -304, 540, 304);
	// ����
	outtextxy(-120, -100, _T("������Ҫ��ѯ���û���"));
	char tmp;
	char OwnerName[12];
	for (int i = 0; i < 12; i++)
		OwnerName[i] = '\0';
	int i;
	for (i = 0; i < 10; i++)
	{
		tmp = _getch();
		if (tmp == '\r' && i != 0)
			break;
		if (!(tmp >= 33 && tmp <= 126))
		{
			i--;
			FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
			continue;
		}
		outtextxy(-120 + i * 20, -50, tmp);
		OwnerName[i] = char(tmp);
	}
	if (i == 10)
	{
		char ch;
		while (ch = _getch())
			if (ch == '\r')
				break;
	}
	// ��ȡ�û���
	setfillcolor(0x000000);
	solidrectangle(-540, -304, 540, 304);
	// ����
	settextcolor(BackGroundColor);
	outtextxy(-70, -200, _T("���а�"));
	outtextxy(-210, -165, _T("����   ģʽ   ����    ����"));
	rankinfo* p = head;
	int sum = 0;
	for (int i = 0; i < total && i < 9; i++)
	{
		if (cmp(OwnerName, p->name))
		{
			ShowAPiece(i, p);
			sum++;
		}
		p = p->next;
	}
	if (sum == 0)
	{
		outtextxy(-30, -10, _T("�޼�¼!"));
	}
	char ch;
	while (ch = _getch())
	{
		if (ch == '\r')
			break;
	}
	return;

}
void RANK::Choose()
{
	char ch;
	ch = _getch();
	if (ch == 'q')
		Query();
	else if (ch == '\r')
		return;
}
void RANK::ReWrite()
{
	rankinfo* p = head;
	ofstream file(".\\Save&Load\\Save.sav", ios::binary);
	if (!file.is_open())
	{
		closegraph();
		cout << "Save Document Wrong!" << endl;
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < 9 && i < total; i++)
	{
		file << p->mode << ' ';
		file << p->score << ' ';
		for (int i = 0; p->name[i] != '\0'; i++)
			file << p->name[i];
		file << '\n';
		p = p->next;
	}
	file.close();
}
void RANK::ShowRank()
{
	GetData();
	setfillcolor(0x000000);
	solidrectangle(-540, -304, 540, 304);
	// ����
	if (If_empty)
	{
		outtextxy(-30, -10, _T("�޼�¼!"));
		char ch;
		while (ch = _getch())
		{
			if (ch == '\r')
				break;
		}
		return;
	}
	settextcolor(BackGroundColor);
	outtextxy(-70, -200, _T("���а�"));
	outtextxy(-210, -165, _T("����   ģʽ   ����    ����"));
	statistic();
	rankinfo* p = head;
	for (int i = 0; i < 9 && i < total; i++)
	{ // ֻ��ʾ��߼���
		ShowAPiece(i, p);
		p = p->next;
	}
	Choose();
	ReWrite();
	del();
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
}