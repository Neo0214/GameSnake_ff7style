#include "head.h"
using namespace std;
int main()
{
	Graph MainGraph(1080, 608); // 游戏窗口1080*608  宽幅  逐行
	Map MainMap;
	RANK rank;
	MainMap.UserName();
	MainGraph.start(); // 启动游戏，加载loading界面
	while (true)
	{
		int choice = 0; // 0-4分别对应五个选项卡
		MainMap.clean();
		MainGraph.ShowTab(); // 加载选项卡界面
		choice = MainGraph.GetChoice(); // 获取选项
		mciSendString(_T("stop .\\Music\\Begin.mp3 "), 0, 0, 0);
		switch (choice)
		{ 
			// 每一种玩法分别进不同函数，在其中再建立对象
			case 0: // 基础版
				MainMap.PlayMode1();
				break;
			case 1:
				MainMap.PlayMode2();
				break;
			case 2:
				MainMap.PlayMode3();
				break;
			case 3:
				MainMap.PlayStory();
				break;
			case 4:
				rank.ShowRank();
				break;
			default:
				break;
		}
		mciSendString(_T("play .\\Music\\Begin.mp3 repeat"), 0, 0, 0);
	}
	MainGraph.CloseGraph();
	return 0;
}