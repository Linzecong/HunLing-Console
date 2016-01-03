
class Game
{
  public:
	RenWu Me;
	WuHun WHK[200];				// 魂灵/等级
	int IsFirst;				// 是否第一次
	void OutPut(HunJi a);
	void OutPut(HunShou a);
	void OutPut(Task a);
	void OutPut(WuHun a);
	void OutPut(NPC a);
	void OutPut(Map a);
	void Load();				// 读取游戏
	int Begin();				// 开始界面
	void Play();				// 进入游戏
	void Start();
	void Search();				// 看图鉴
	void Save();				// 保存
	void GetMonster(Map a);		// 获取怪物
	void GetNPC(Map a);			// 获取NPC
	void GetHelp();				// 帮助
	template<typename T> void DropItem(T A, RenWu & B);
	  			// 道具掉落
};

template<typename T>void Game::DropItem(T A, RenWu & B)	// 道具掉落
{

		int temp = GetRand(1,10);
		int D=A.DItem[temp];
		if(D!=0)
			for (int i = 1; i <= 99; i++)
				if (B.Bag[i].XiaoGuo == 0
					|| B.Bag[i].XiaoGuo == Item[D].XiaoGuo)
				{
					int p = B.Bag[i].Count;
					B.Bag[i] = Item[D];
					B.Bag[i].Count = p + 1;
					E("获得道具，",Item[D].Name);
					break;
				}
								// 特定怪物
	
	if (A.Level <= 10)
	{
		int temp = GetRand(1, 10);
		if (temp >= 8)
			for (int i = 1; i <= 99; i++)
				if (B.Bag[i].XiaoGuo == 0
					|| B.Bag[i].XiaoGuo == Item[2].XiaoGuo)
				{
					int p = B.Bag[i].Count;
					B.Bag[i] = Item[2];
					B.Bag[i].Count = p + 1;
					E("获得道具，",Item[2].Name);
					break;
				}
		temp = GetRand(1, 10);
		if (temp >= 9)
			for (int i = 1; i <= 99; i++)
				if (B.Bag[i].XiaoGuo == 0
					|| B.Bag[i].XiaoGuo == Item[3].XiaoGuo)
				{
					int p = B.Bag[i].Count;
					B.Bag[i] = Item[3];
					B.Bag[i].Count = p + 1;
					E("获得道具，",Item[3].Name);
					break;
				}

		temp = GetRand(1 * A.Level, 5 * A.Level);
		E("获得修为：", temp);
		B.WH.Xiu += temp;
		temp = GetRand(5 * A.Level, 10 * A.Level);
		E("获得魂币：", temp);
		B.HB += temp;
	}							// 10级以下公共掉落
	
	Me.UpdateLV();
}

void Game::OutPut(HunJi a)
{
	if (a.IsFind)
	{
		E("魂技名称：", a.Name);
		E("魂技描述：", a.Des);
		E("所需魂力：", a.HunLi);
	}
	else
	{
		Y("未知技能");
	}
	DrawLine;
}

void Game::OutPut(HunShou a)
{
	if (a.IsFind)
	{
		int End = 1;
		while (End != 0)
		{
			E("魂兽名字：", a.Name);
			E("魂兽描述：", a.Des);
			DrawLine;
			Y("1.查看抗性");
			Y("2.查看技能");
			Y("0.返回");
			DrawLine;
			Y("请输入");
			int aa = getch() - 48;
			switch (aa)
			{
			case 1:
				{
					clrscr();
					E("冰：", a.K_Bing);
					E("火：", a.K_Huo);
					E("电：", a.K_Dian);
					E("土：", a.K_Tu);
					E("暗：", a.K_An);
					E("光：", a.K_Guang);
					DrawLine;
					break;
				}
			case 2:
				{
					clrscr();
					for (int i = 1; i <= 9; i++)
						OutPut(HJ[a.MyHJ[i]]);
					break;
				}
			case 0:
				{
					clrscr();
					End = 0;
					break;
				}

			}
		}
	}
	else
		Y("未知魂兽");
}

void Game::OutPut(Task a)
{
	clrscr();
	DrawLine;
	E("任务名：", a.Name);
	E("任务描述：", a.Des);
	C("已完成：" << a.FMB << "/" << a.MB);
	Y("1：接受");
	Y("0：返回");
	int t = getch() - 48;
	if (t == 1)
	{
		Me.ExceptTask(a);		// 接受
		DrawLine;
	}

}

void Game::OutPut(WuHun a)
{
	if (a.IsFind)
	{
		int End = 1;
		while (End != 0)
		{
			E("武魂名字：", a.Name);
			E("武魂描述：", a.Des);
			DrawLine;
			if (a.Level != 0)
			{
				E("等级：", a.Level);
				E("修为：", a.Xiu);
				E("力量：", a.Li);
				E("敏捷：", a.Min);
				E("生命力：", a.SPoint);
				E("魂力：", a.HPoint);
				E("攻击力：", a.APoint);
				E("防御力：", a.DPoint);
				DrawLine;
			}

			Y("1.查看抗性");
			Y("2.查看技能");
			Y("0.返回");
			int aa = getch() - 48;
			switch (aa)
			{
			case 1:
				{
					clrscr();
					E("冰：", a.K_Bing);
					E("火：", a.K_Huo);
					E("电：", a.K_Dian);
					E("土：", a.K_Tu);
					E("暗：", a.K_An);
					E("光：", a.K_Guang);
					DrawLine;
					break;
				}
			case 2:
				{
					clrscr();
					for (int i = 1; i <= 9; i++)
						OutPut(HJ[a.MyHJ[i]]);
					break;
				}
			case 0:

				{
					clrscr();
					End = 0;
					break;
				}

			}
		}
	}
	else
		Y("未知武魂");
}

void Game::OutPut(NPC a)
{
	E("名字：", a.Name);
	E("介绍：", a.Des);
	for (int i = 0; i <= 9; i++)	// 输出聊天信息
	{
		int temp = a.IndexMsg[i];
		if(temp==0)continue;
		int t = msg[temp].Task;
	    for(int j=1;j<50;j++)
		if (RW[t].Reward== Me.MyRW[j].Reward)
		{
			E("★", msg[temp].Message);
			break;
		}
	}
	for (int i = 1; i <= 49; i++)	// 任务更新
	{
		int NPCtemp = Me.MyRW[i].NTalkNPC;
		if (a.IndexMsg[1] == Npc[NPCtemp].IndexMsg[1])
			Me.MyRW[i].FMB++;
	}
	Y("可接任务：");
	int rwNum = 1;
	int Rtemp[5] = { 0, 0, 0, 0, 0 };
	for (int i = 0; i <= 4; i++)
	{
		int rw = a.NPCRW[i];
		if (a.NPCRW[0] == 0)
		{
			Y("无！");
			break;
		}
		int wc = RW[rw].NTask;
		int bbb = 0;
		for (int i = 1; i < 50; i++)
			if (RW[rw].Reward == Me.MyRW[i].Reward && Me.MyRW[i].Reward != 0)	// 判断是否已接受
				bbb = 1;
		if (RW[wc].IsFinish == 1 && RW[rw].IsFinish == 0 && bbb == 0)	// 判断是否已完成或已接或暂不可接
		{
			S(rwNum, "：", RW[rw].Name);
			Rtemp[rwNum] = rw;
			rwNum++;
		}
		else
		{
			if (RW[rw].IsFinish == 1 && rw != 0)
				Y("☆已完成！");
			if (RW[wc].IsFinish == 0)
				Y("★暂不可接！");
			if (bbb == 1)
				Y("?已接受");
		}
	}
	if (a.CanATK == 1)
	{
	Y("W：查看武魂");
		Y("A：攻击");
}
	DrawLine;
	Y("请输入：");
	int c = getch();
	if (c < 96)
	{
		c = c - 48;
		if (c <= 5)
		{
			int bb = Rtemp[c];
			if (bb != 0 && RW[bb].MB != 0)
				OutPut(RW[bb]);
			clrscr();
		}
		else
		{
			clrscr();
			Y("无效操作！");
		}
	}
	switch (c)
	{
	case 'w':
		{
			if (a.CanATK == 1)
			{
			int temp = a.wuhun[0];
			C(WH[temp].Name << " " << a.wuhun[1] << "级");
			WH[temp].IsFind = 1;
		}
			break;
		}
	case 'a':
		{
			if (a.CanATK == 1)
			{
				Y("攻击！");

				int temp = a.wuhun[0];
				int p = a.wuhun[1];
				WuHun ABC = CreateWH(WH[temp], 84);
				WH[temp].IsFind = 1;
				Platform < WuHun > temp1(Me, ABC);	// 创建战斗场景
				int type = temp1.Begin();
				switch (type)
				{
				case -1:
					{
						Y("少年！再来一次？");
						break;
					}
				case -2:
					{
						Y("年轻有为啊！");
						for (int i = 1; i <= 49; i++)	// 更新任务
						{
							int NPCtemp = Me.MyRW[i].NKillNPC;
							if (a.IndexMsg[1] == Npc[NPCtemp].IndexMsg[1])
								Me.MyRW[i].FMB++;
						}
					
						break;
					}
				case -3:
					{
						Y("再来！");
						break;
					}
				}
			}
			else
				Y("不能被攻击");
			break;
		}
		break;
	default:
		break;
	}
}

void Game::OutPut(Map a)
{
	DrawLine;
	E("☆所属国：", a.BC);
	S("【", a.Name, "】");
	int i = 0;

	while (a.IndexNPC[i] != 0 && i < 10)	// 输出NPC
	{
		if (Npc[a.IndexNPC[i]].CanShow != 0)	// 是否能显示
			E("★", Npc[a.IndexNPC[i]].Name);
		i++;
	}
	S("【", a.Des, "】");
	DrawLine;
}

void Game::Load()
{
	Y("读取游戏中，请稍等...");
	HJ[1].Init();
	Y("加载魂技成功");
	Item[1].Init();
	Y("加载道具成功");
	RW[1].Init();
	Y("加载任务成功");
	HS[1].Init();
	Y("加载魂兽成功");
	msg[1].Init();
	Y("加载消息成功");
	Npc[1].Init();
	Y("加载NPC成功");
	DT[1][0].Init();
	Y("加载地图成功");
	WH[1].Init();
	Y("加载武魂成功");
	ifstream open(WHK_SAVEPATH, ios::binary);
	open.read((char *)&IsFirst, sizeof(IsFirst));
	open.read((char *)&WHK, sizeof(WHK));
	open.close();
	Y("加载武魂库成功");
	Me.Init();
	Y("加载人物成功");
	DrawLine;
	clrscr();
}

void Game::Save()
{
	HJ[1].Save();
	RW[1].Save();
	HS[1].Save();
	WH[1].Save();
	ofstream open(WHK_SAVEPATH, ios::binary);
	open.write((char *)&IsFirst, sizeof(IsFirst));
	open.write((char *)&WHK, sizeof(WHK));
	open.close();
	Me.Save();
}

void Game::Play()
{
	if (IsFirst)
	{
		IsFirst = 0;
		Me.PositionX = 20;
		Me.PositionY = 5;
		Me.HB = 500;
		Me.WH = CreateWH(WH[2], 80);
		clrscr();
		Y("请输入您的名字...");
		// Me.Name=getch();
		clrscr();
		Y(".............(按任意键继续)");
		getch();
		Y("...这是哪里？...");
		getch();
		clrscr();
		Start();
	}
	else
	{
		clrscr();
		Start();
	}
}

void Game::GetMonster(Map a)
{
	int Rand = GetRand(0, 9);
	int Hun = a.IndexHS[Rand];
	int time = 0;
	while (Hun == 0)			// 随机魂兽
	{
		Rand = GetRand(0, 9);
		Hun = a.IndexHS[Rand];
		time++;
		if (time > 10)
		{
			Y("★魂兽死光了？没有魂兽或魂兽稀少！★");
			return;
		}
	}
	int LV = GetRand(a.SMinLV, a.SMaxLV);
	HunShou HStemp = CreateHS(HS[Hun], LV);
	Platform < HunShou > temp(Me, HStemp);	// 创建战斗场景
	int type = temp.Begin();
	HS[Hun].IsFind = 1;
	switch (type)
	{
	case -1:
		{
			Y("<<你输了.....>>");
			break;
		}
	case -2:
		{
			Y("这魂兽太弱了！");
			for (int i = 0; i <= 49; i++)	// 更新任务
			{
				int HStemp = Me.MyRW[i].NKillHS;
				if (HS[Hun].MyHJ[9] == HS[HStemp].MyHJ[9])
					Me.MyRW[i].FMB++;
			}
			DropItem(HStemp, Me);
			break;
		}
	case -3:
		{
			Y("太难分出胜负了！");
			break;
		}
	}
}

void Game::GetNPC(Map a)
{
	DrawLine;
	int i = 0;
	int N = a.IndexNPC[i];
	if (N == 0 || Npc[N].CanShow == 0)
	{
		Y("***没有NPC***");
		return;
	}
		Y("*****NPC列表*****");
	int temp = 1;
	int Ntemp[10];
	while ((N != 0) && (i <= 9))
	{
		if (Npc[N].CanShow == 1)
		{
			S(temp, ".", Npc[N].Name);
			Ntemp[temp] = N;
			temp++;
		}
		i++;
		N = a.IndexNPC[i];
	}
	DrawLine;
	int b = getch() - 48;
	while (b < 1 || b > 9 || Ntemp[b] == 0)
		b = getch() - 48;
	int bb = Ntemp[b];
	OutPut(Npc[bb]);
}

void Game::GetHelp()
{
	Y("【***帮助***】");
}

void Game::Start()
{
	int JS = 0;
	while (JS != 1)
	{
		OutPut(DT[Me.PositionX][Me.PositionY]);
		if (DT[Me.PositionX][Me.PositionY + 1].SMaxLV != -1)
			E("【W】", DT[Me.PositionX][Me.PositionY + 1].Name);
		if (DT[Me.PositionX][Me.PositionY - 1].SMaxLV != -1)
			E("【S】", DT[Me.PositionX][Me.PositionY - 1].Name);
		if (DT[Me.PositionX - 1][Me.PositionY + 1].SMaxLV != -1)
			E("【A】", DT[Me.PositionX - 1][Me.PositionY].Name);
		if (DT[Me.PositionX + 1][Me.PositionY + 1].SMaxLV != -1)
			E("【D】", DT[Me.PositionX + 1][Me.PositionY].Name);
		Y("1.遇怪 2.NPC 3.背包 4.任务");
		Y("5.魂灵 6.帮助 7.保存 8.退出");
		int LV = Me.WH.Level;	// 判断最高等级
		int a = getch();
		if (a < 96)
			a = a - 48;
		clrscr();
		switch (a)
		{
		case 'w':
			{
				if (RW[DT[Me.PositionX][Me.PositionY + 1].NTask].IsFinish!=1)
					Y("〖你还不能去那里！〗");
				else
				{
					if (DT[Me.PositionX][Me.PositionY + 1].SMaxLV == -1)
						Y("没有路！！！");
					else
						Me.PositionY++;
				}
				break;
			}
		case 's':
			{
				if (RW[DT[Me.PositionX][Me.PositionY - 1].NTask].IsFinish!=1)
					Y("你还不能去那里！");
				else
				{
					if (DT[Me.PositionX][Me.PositionY - 1].SMaxLV == -1)
						Y("没有路！！");
					else
						Me.PositionY--;
				}
				break;
			}
		case 'a':
			{
				if (RW[DT[Me.PositionX - 1][Me.PositionY].NTask].IsFinish!=1)
					Y("你还不能去那里！");
				else
				{
					if (DT[Me.PositionX - 1][Me.PositionY].SMaxLV == -1)
						Y("没有路！！");
					else
						Me.PositionX--;
				}
				break;
			}
		case 'd':
			{
				if (RW[DT[Me.PositionX + 1][Me.PositionY].NTask].IsFinish!=1)
					Y("你还不能够去那里！");
				else
				{
					if (DT[Me.PositionX + 1][Me.PositionY].SMaxLV == -1)
						Y("没有路！！");
					else
						Me.PositionX++;
				}
				break;
			}
		case 1:
			{
				GetMonster(DT[Me.PositionX][Me.PositionY]);
				break;
			}
		case 2:
			{
				GetNPC(DT[Me.PositionX][Me.PositionY]);
				break;
			}
		case 3:
			{
				Me.OutPutBag();
				break;
			}
		case 4:
			{
				Me.OutPutRW();
				break;
			}
		case 5:
			{
				Me.OutPutWH();
				break;
			}
		case 6:
			{
				GetHelp();
				break;
			}
		case 7:
			{
				Save();
				Y("保存成功！");
				getch();
				break;
			}
		case 8:
			{
				JS = 1;
				Y("已退出");
				break;
			}
		}
	}
}

int Game::Begin()
{
	clrscr();
	DrawLine;
	Y("         欢迎来到武魂的世界！");
	Y("1.开始游戏");
	Y("2.查看图鉴");
	Y("0.退出");
	DrawLine;
	return getch() - 48;
}

/************选项2***************/
void Game::Search()
{
	int End = 1;
	while (End != 0)
	{
		clrscr();
		Y("1.已发现魂技");
		Y("2.已发现魂灵");
		Y("3.已发现魂兽");
		Y("0.返回");
		DrawLine;
		switch (getch() - 48)
		{
		case 1:				// 魂技
			{
				clrscr();
				int JS = 1;
				int i = 1, j = 1;
				while (JS != 0)
				{
					for (; i <= j + 4; i++)
						if (HJ[i].IsFind)
							S(i - j + 1, ".", HJ[i].Name);
						else
							S(i - j + 1, ".", "未知技能");
					C("6.下一页 " << "7.上一页" << "0.返回");
					DrawLine;
					Y("请输入：");
					int a = getch() - 48;
					switch (a)
					{
					case 1:
						{
							OutPut(HJ[i - 5]);
							i = i - 5;
							break;
						}
					case 2:
						{
							OutPut(HJ[i - 4]);
							i = i - 5;
							break;
						}
					case 3:
						{

							OutPut(HJ[i - 3]);
							i = i - 5;
							break;
						}

					case 4:
						{
							OutPut(HJ[i - 2]);
							i = i - 5;
							break;
						}
					case 5:
						{
							OutPut(HJ[i - 1]);
							i = i - 5;
							break;
						}

					case 6:
						{
							j = j + 5;
							break;
						}
					case 7:
						{
							j = j - 5;
							i = i - 10;
							if (j < 0)
							{
								i = 1;
								j = 1;
							}
							break;
						}

					case 0:
						{
							JS = 0;
							break;
						}

					}



				}
				break;
			}
		case 2:				// 魂灵
			{
				clrscr();
				int JS = 1;
				int i = 1, j = 1;
				while (JS != 0)
				{
					for (; i <= j + 4; i++)
						if (WH[i].IsFind)
							S(i - j + 1, ".", WH[i].Name);
						else
							S(i - j + 1, ".", "未知魂灵");
					C("6.下一页 " << "7.上一页" << "0.返回");
					DrawLine;
					Y("请输入：");
					int a = getch() - 48;
					switch (a)
					{
					case 1:
						{

							OutPut(WH[i - 5]);
							i = i - 5;
							break;
						}
					case 2:
						{
							OutPut(WH[i - 4]);
							i = i - 5;
							break;
						}
					case 3:
						{

							OutPut(WH[i - 3]);
							i = i - 5;
							break;
						}

					case 4:
						{
							OutPut(WH[i - 2]);
							i = i - 5;
							break;
						}
					case 5:
						{
							OutPut(WH[i - 1]);
							i = i - 5;
							break;
						}

					case 6:
						{
							j = j + 5;
							break;
						}
					case 7:
						{
							j = j - 5;
							i = i - 10;
							if (j < 0)
							{
								i = 1;
								j = 1;
							}
							break;
						}

					case 0:
						{
							JS = 0;
							break;
						}

					}



				}
				break;
			}
		case 3:				// 魂兽
			{

				clrscr();
				int JS = 1;
				int i = 1, j = 1;
				while (JS != 0)
				{
					for (; i <= j + 4; i++)
						if (HS[i].IsFind)
							S(i - j + 1, ".", HS[i].Name);
						else
							S(i - j + 1, ".", "未知魂兽");
					C("6.下一页 " << "7.上一页" << "0.返回");
					DrawLine;
					Y("请输入：");
					int a = getch() - 48;
					switch (a)
					{
					case 1:
						{

							OutPut(HS[i - 5]);
							i = i - 5;
							break;
						}
					case 2:
						{
							OutPut(HS[i - 4]);
							i = i - 5;
							break;
						}
					case 3:
						{

							OutPut(HS[i - 3]);
							i = i - 5;
							break;
						}

					case 4:
						{
							OutPut(HS[i - 2]);
							i = i - 5;
							break;
						}
					case 5:
						{
							OutPut(HS[i - 1]);
							i = i - 5;
							break;
						}

					case 6:
						{
							j = j + 5;
							break;
						}
					case 7:
						{
							j = j - 5;
							i = i - 10;
							if (j < 0)
							{
								i = 1;
								j = 1;
							}
							break;
						}

					case 0:
						{
							JS = 0;
							break;
						}

					}



				}
				break;
			}
		case 0:
			{
				End = 0;
				break;
			}
		}
	}							// 看图鉴

}