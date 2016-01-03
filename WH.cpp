#define DrawLine cout<<"   "<<"————————————————————————————————————————"<<endl
#define Y(x) cout<<"      "<<x<<endl
#define E(x,y) cout<<"      "<<x<<y<<endl
#define S(x,y,z) cout<<"      "<<x<<y<<z<<endl
#define C(x) cout<<"      "<<x<<endl
/*
#defin HJ_DATAPATH "/sdcard/gameproject/WH/data/HJ.dat"
#define HJ_SAVEPATH "/sdcard/gameproject/WH/save/HJ.sav"
#define HS_DATAPATH "/sdcard/gameproject/WH/data/HS.dat"
#define HS_SAVEPATH "/sdcard/gameproject/WH/save/HS.sav"
#define DT_DATAPATH "/sdcard/gameproject/WH/data/Map.dat"
#define NPC_DATAPATH "/sdcard/gameproject/WH/data/NPC.dat"
#define MSG_DATAPATH "/sdcard/gameproject/WH/data/Msg.dat"
#define RW_DATAPATH "/sdcard/gameproject/WH/data/Task.dat"
#define RW_SAVEPATH "/sdcard/gameproject/WH/save/Task.sav"
#define ME_SAVEPATH "/sdcard/gameproject/WH/save/RW.sav"
#define WHS_DATAPATH "/sdcard/gameproject/WH/data/WHHS.dat"
#define WHQ_DATAPATH "/sdcard/gameproject/WH/data/WHQ.dat"
#define WH_SAVEPATH "/sdcard/gameproject/WH/save/WH.sav"
#define DJ_DATAPATH "/sdcard/gameproject/WH/data/Item.dat"
#define WHK_SAVEPATH "/sdcard/gameproject/WH/save/WHK.sav"
*/
#define HJ_DATAPATH "./data/HJ.dat"
#define HJ_SAVEPATH "./save/HJ.sav"
#define HS_DATAPATH "./data/HS.dat"
#define HS_SAVEPATH "./save/HS.sav"
#define DT_DATAPATH "./data/Map.dat"
#define NPC_DATAPATH "./data/NPC.dat"
#define MSG_DATAPATH "./data/Msg.dat"
#define RW_DATAPATH "./data/Task.dat"
#define RW_SAVEPATH "./save/Task.sav"
#define ME_SAVEPATH "./save/RW.sav"
#define WHS_DATAPATH "./data/WHHS.dat"
#define WHQ_DATAPATH "./data/WHQ.dat"
#define WH_SAVEPATH "./save/WH.sav"
#define DJ_DATAPATH "./data/Item.dat"
#define WHK_SAVEPATH "./save/WHK.sav"

#include <iostream>
#include<time.h>
#include<stdlib.h>
#include <fstream>
#include <conio.h>
using namespace std;
#include "WH_Date.h"
#include "WH_HunJi.h"
#include "WH_DaoJu.h"
#include "WH_HunShou.h"
#include "WH_WuHun.h"
#include "WH_Task.h"
#include "WH_NPC.h"
#include "WH_Map.h"
#include "WH_RenWu.h"
#include "WH_Plat.h"
#include "WH_Game.h"

int main()
{
	cout.setf(ios::fixed);
    cout.precision(1);
	Game game;
	game.Load();
	int WEnd = 1;
	while (WEnd != 0)
	{
		switch (WEnd = game.Begin())
		{
		case 1:
			{
				game.Play();
				break;
			}
		case 2:
			{
				game.Search();
				break;
			}

		}
	}
	Y("已退出...请按任意键结束...");
	getch();




	return 0;
}
