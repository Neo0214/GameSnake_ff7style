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
#define NamePosY -290 // 标题位置
#define LengthPosX -440
#define LengthPosY -200
#define LifePosX -440
#define LifePosY -170 // 生命值位置
#define ScorePosX -440 
#define ScorePosY -140 // 当前分数位置
#define HighestPosX -440
#define HighestPosY -110 // 最高分位置
#define TimePosX -440
#define TimePosY -80 // 时间位置
#define CardX -375
#define CardY 120
#define RankPosX -200
#define RankPosY -100

#define BackGroundColor 0xCEAC00 // 主背景颜色
#define SnakeColor 0xffffff // 蛇身颜色
#define WallColor 0x00C0FF // 墙体颜色
#define HeadColor 0x000000 // 蛇头颜色
#define WindColor 0x00ff00 // 食物颜色  
#define SnowColor 0xFFFB83 // 食物颜色
#define LightningColor 0xEE1C00 // 食物颜色
#define FireColor 0x003CFF // 食物颜色

#define LTPosX -164
#define LTPosY -304
#define STEP 16 // 16像素一格
#define MapRow 38
#define MapCol 44

class Graph; // 主屏幕，生成启动界面、选项卡等
class Map; // 游戏主地图，维护地图数据等
class STORY; // 剧情界面
class BOSS; // boss属性
class RANK;
struct rankinfo {
	int mode;
	int score;
	char name[12] = { '\0' };
	rankinfo* next;
}; // 链表 排行榜信息
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
	unsigned short (*map)[MapCol]; // 坐标信息
	unsigned short head[2]; // 蛇头位置
	unsigned short tail[2]; // 蛇尾位置
	IMAGE choosen, unchoosen;
	HWND _hWnd;
	LOGFONT f; // 字体信息
	TCHAR ModeName[3][10] = { _T("入门版"),_T("进阶版"),_T("高级版") };
	TCHAR ATB[6][14] = { _T("火焰    1ATB"),_T("暴雪    1ATB"),_T("劲风    1ATB"),_T("雷电    1ATB") ,_T("恢复    1ATB") ,_T("洞察    2ATB") };
	IMAGE SnakeHead[4], wall;
	IMAGE food[4];
	int SnakeLength;
	int Life;
	int score;
	int HighestScore;
	void MoveAnime(char);
	void MoveAnime_S(char, int&, BOSS&); // special模式
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
	void init(int); // 生成地图
	void Ready(); // 回车开始
	bool CommandValid(char, char);
	bool CreateSnake(); // 生成初始小蛇
	bool FindPos(unsigned short&, unsigned short&); // 寻找可以生成蛇的位置
	void GameOver(int, time_t); // 游戏结束界面
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
	int total; // 总条数
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