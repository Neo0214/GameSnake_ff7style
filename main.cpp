#include "head.h"
using namespace std;
int main()
{
	Graph MainGraph(1080, 608); // ��Ϸ����1080*608  ���  ����
	Map MainMap;
	RANK rank;
	MainMap.UserName();
	MainGraph.start(); // ������Ϸ������loading����
	while (true)
	{
		int choice = 0; // 0-4�ֱ��Ӧ���ѡ�
		MainMap.clean();
		MainGraph.ShowTab(); // ����ѡ�����
		choice = MainGraph.GetChoice(); // ��ȡѡ��
		mciSendString(_T("stop .\\Music\\Begin.mp3 "), 0, 0, 0);
		switch (choice)
		{ 
			// ÿһ���淨�ֱ����ͬ�������������ٽ�������
			case 0: // ������
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