#pragma once
#include <graphics.h>
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <conio.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
using namespace std;
#define TabBeginX -350
#define TabBeginY 30
#define StrX -450
#define StrY 0
#define NamePosX -440
#define NamePosY -290 // ����λ��
#define LengthPosX -440
#define LengthPosY -200
#define LifePosX -440
#define LifePosY -170 // ����ֵλ��
#define ScorePosX -440 
#define ScorePosY -140 // ��ǰ����λ��
#define HighestPosX -440
#define HighestPosY -110 // ��߷�λ��
#define TimePosX -440
#define TimePosY -80 // ʱ��λ��
#define CardX -375
#define CardY 120
#define RankPosX -200
#define RankPosY -100

#define BackGroundColor 0xCEAC00 // ��������ɫ
#define SnakeColor 0xffffff // ������ɫ
#define WallColor 0x00C0FF // ǽ����ɫ
#define HeadColor 0x000000 // ��ͷ��ɫ
#define WindColor 0x00ff00 // ʳ����ɫ  
#define SnowColor 0xFFFB83 // ʳ����ɫ
#define LightningColor 0xEE1C00 // ʳ����ɫ
#define FireColor 0x003CFF // ʳ����ɫ

#define LTPosX -164
#define LTPosY -304
#define STEP 16 // 16����һ��
#define MapRow 38
#define MapCol 44

class Graph; // ����Ļ�������������桢ѡ���
class Map; // ��Ϸ����ͼ��ά����ͼ���ݵ�
class STORY; // �������
class BOSS; // boss����
class RANK;
struct rankinfo {
	int mode;
	int score;
	char name[12] = { '\0' };
	rankinfo* next;
}; // ���� ���а���Ϣ
class Graph {
private:
	int GraphLength;
	int GraphHeight;
	HWND _hWnd;
	MOUSEMSG _Mouse;
	IMAGE StartLogo[48] = { 0 };
	IMAGE TabUnchoosen, TabChoosen;
public:
	Graph(int length, int height);
	void CloseGraph();
	void ShowTab();
	int GetChoice();
	void start();
	void _GetTextPosition(int& y, int pos);
};
class Map {
private:
	char OwnerName[11];
	unsigned short (*map)[MapCol]; // ������Ϣ
	unsigned short head[2]; // ��ͷλ��
	unsigned short tail[2]; // ��βλ��
	IMAGE choosen, unchoosen;
	HWND _hWnd;
	LOGFONT f; // ������Ϣ
	TCHAR ModeName[3][10] = { _T("���Ű�"),_T("���װ�"),_T("�߼���") };
	TCHAR ATB[6][14] = { _T("����    1ATB"),_T("��ѩ    1ATB"),_T("����    1ATB"),_T("�׵�    1ATB") ,_T("�ָ�    1ATB") ,_T("����    2ATB") };
	IMAGE SnakeHead[4], wall;
	IMAGE food[4];
	int SnakeLength;
	int Life;
	int score;
	int HighestScore;
	void MoveAnime(char);
	void MoveAnime_S(char, int&, BOSS&); // specialģʽ
	bool Death(char);
	char SwitchCommand(char);

	void ShowLength(int);
	void ShowLife(int);
	void ShowScore(int);
	void ShowHighest(int);
	void ShowTime(int, int, int);
	bool NoFood();
	void CreateFood(int);
	void CleanInfo();
	void SnakeToWall();
	void SnakeToFood();
	void ShowATB(int);
	bool ATBStrategy(int&, BOSS&, time_t&, bool&, time_t);
	bool ChooseStrategy(int&, MOUSEMSG, int&, BOSS& boss);
	void ShowStrategy();
	void _GetPos(int& y, int pos);
	bool Quit();
	void GetTime(tm&, time_t&);
	void GameOver_S();
	void GetHighestScore(int);
	void Kill(int, BOSS&);
	bool FoodConfirm_S(unsigned short, int&, BOSS&);
	void ShowInsight();
	void Record(int);
	void Decrease(time_t);
public:
	Map();
	~Map();
	void UserName();
	void init(int); // ���ɵ�ͼ
	void Ready(); // �س���ʼ
	bool CommandValid(char, char);
	bool CreateSnake(); // ���ɳ�ʼС��
	bool FindPos(unsigned short&, unsigned short&); // Ѱ�ҿ��������ߵ�λ��
	void GameOver(int, time_t); // ��Ϸ��������
	void GameWin();
	void PlayMode1();
	void PlayMode2();
	void PlayMode3();
	void PlayStory();
	bool PlaySpecial();
	void clean();
	bool FoodConfirm(unsigned short);
	void ShowInfo(int, time_t = 0);
	void RandomWall(time_t, bool&);
	void SpreadShield(time_t, bool&, int);
};
class STORY {
private:
	int ContentPosX, ContentPosY;
	TCHAR LineContent[50];
	wifstream file;
	IMAGE chara[2];
	IMAGE enemy;
	IMAGE CG;
	IMAGE card;

	void readline();
	void putline();
	void Showcity();
	void Showcard();
public:
	STORY();
	~STORY();
	void EveryCut(bool mode = false, int name = 0);
	void RaceGame();
};

class BOSS {
private:
	int bosslife;
	int shield;
	LOGFONT f;
public:
	void ShowInfo(int, int);
	void NewShield();
	int GetBossLife();
	int GetBossShield();
	void Kill(int);
	void ShowSnakeLife(int);
	void ATBKill(int);
	BOSS(int, int);
};

class RANK {
private:
	bool If_empty;
	int total; // ������
	rankinfo* head;
	void statistic();
	void ShowScore(int, int);
	void GetData();
	void Choose();
	void Query();
	bool cmp(char*, char*);
public:
	void del();
	void ShowAPiece(int, rankinfo*);
	void ShowRank();
	void ReWrite();
};