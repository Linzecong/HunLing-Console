class RenWu
{
  public:
	WuHun WH;					// 魂灵
	char Name[40];				// 名字
	double HB;					// 魂币
	int PositionX;				// 目前位置
	int PositionY;				// 目前位置
	DaoJu Bag[100];				// 背包
	Task MyRW[50];				// 任务列表
	bool Init();
	bool Save();
	bool ExceptTask(Task a);	// 接受任务
	bool FinishTask(Task & a);	// 任务奖励
	bool UseItem(DaoJu & a);	// 使用道具
	void OutPutWH();
	void OutPutBag();
	void OutPutRW();
	void OutPut(DaoJu & a);
	void OutPut(HunJi a);
	void OutPut(Task & a);
	void UpdateRW(); // 更新任务列表
	void UpdateBag() ;// 更新背包
	void UpdateLV() ;// 更新魂灵
};

void RenWu::UpdateLV()
{
	int i = 5;
	int LV = WH.Level;
	while (i--)
	{
		if (WH.Level < 20)
			if (WH.Xiu > WH.Level * 20)
			{
				WH.Xiu -= WH.Level * 20;
				WH.Level++;
				Y("恭喜你！升级了！");
				getch();
			}
		if (WH.Level >= 20 && WH.Level < 40)
			if (WH.Xiu > 400 + 50 * (WH.Level - 20))
			{
				WH.Xiu -= 400 + 50 * (WH.Level - 20);
				WH.Level++;
				Y("恭喜你！升级了！");
				getch();
			}
		if (WH.Level >= 40 && WH.Level < 70)
			if (WH.Xiu > 1000 + 300 * (WH.Level - 40))
			{
				WH.Xiu -= 1000 + 300 * (WH.Level - 40);
				WH.Level++;
				Y("恭喜你！升级了！");
				getch();
			}
		if (WH.Level >= 70 && WH.Level < 90)
			if (WH.Xiu > 10000 + 5000 * (WH.Level - 70))
			{
				WH.Xiu -= 10000 + 5000 * (WH.Level - 70);
				WH.Level++;
				Y("恭喜你！升级了！");
				getch();
			}
		if (WH.Level >= 90 && WH.Level < 100)
			if (WH.Xiu > 100000 + 2000 * (WH.Level - 90))
			{
				WH.Xiu -= 100000 + 2000 * (WH.Level - 90);
				WH.Level++;
				Y("恭喜你！升级了！");
				getch();
			}
	}
	// 生成新魂灵
	double Li = WH.Li;
	double Min = WH.Min;
	double APoint = WH.APoint;	// 攻击力
	double SPoint = WH.SPoint;	// 生命力
	double HPoint = WH.HPoint;	// 魂力
	double DPoint = WH.DPoint;	// 防御力
	WuHun temp = CreateWH(WH, LV);
	Li -= temp.Li;
	Min -= temp.Min;
	APoint -= temp.APoint;
	SPoint -= temp.SPoint;
	HPoint -= temp.HPoint;
	DPoint -= temp.DPoint;
	WH = CreateWH(WH, WH.Level);
	WH.Li += Li;
	WH.Min += Min;
	WH.APoint += APoint;		// 攻击力
	WH.SPoint += SPoint;		// 生命力
	WH.HPoint += HPoint;		// 魂力
	WH.DPoint += DPoint;		// 防御力
}

void RenWu::UpdateBag()
{
	for (int i = 1; i < 100; i++)
	{
		if (Bag[i].Count == 0)
			Bag[i].XiaoGuo = 0;
		if (Bag[i].Count == 0)	// 往上移
		{
			Bag[i] = Bag[i + 1];
			Bag[i + 1] = Item[0];
		}
	}

}

void RenWu::UpdateRW()
{
	for (int i = 1; i < 50; i++)
	{
		if (MyRW[i].IsFinish == 1)
			MyRW[i].Reward = 0;
		if (MyRW[i].Reward == 0)
		{
			MyRW[i] = MyRW[i + 1];
			MyRW[i + 1] = RW[0];
		}
	}
}

void RenWu::OutPut(Task & a)
{
	for (int i = 1; i < 50; i++)	// 道具数加到任务里
		for (int j = 1; j < 100; j++)
			if (MyRW[i].NGetItem == Bag[j].XiaoGuo && Bag[j].XiaoGuo != 0)
				MyRW[i].FMB = Bag[j].Count;
	DrawLine;
	if (a.Reward == 0)
		return;
	E("任务名：", a.Name);
	E("任务描述：", a.Des);
	C("已完成：" << a.FMB << "/" << a.MB);
	if (a.FMB >= a.MB)
		Y("1：完成");
	Y("0：返回");
	int t = getch() - 48;
	if (a.FMB >= a.MB)
		if (t == 1)
		{
			FinishTask(a);
			DrawLine;
			Y("已完成！");
		}
}

void RenWu::OutPut(DaoJu & a)
{
	clrscr();
	if (a.Count == 0)
		return;
	DrawLine;
	E("道具名：", a.Name);
	E("道具介绍：", a.Des);
	E("数量：", a.Count);
	Y("1.使用");
	Y("0.返回");
	int t = getch() - 48;
	if (t == 1)
	{
		UseItem(a);
		DrawLine;
	}
}

bool RenWu::Save()				// 保存
{
	ofstream open(ME_SAVEPATH, ios::binary);
	open.write((char *)this, sizeof(RenWu));
	open.close();
	return 1;
}

bool RenWu::Init()				// 读取
{
	ifstream open(ME_SAVEPATH, ios::binary);
	open.read((char *)this, sizeof(RenWu));
	open.close();
	return 1;
}

bool RenWu::ExceptTask(Task a)	// 接受任务
{

	for (int i = 1; i < 50; i++)
		if (MyRW[i].Reward == 0)
		{
			MyRW[i] = a;
			Y("已接受！");
			getch();
			return true;
		}
	return false;
}

bool RenWu::FinishTask(Task & a)	// 完成任务
{
	switch (a.Reward)
	{
	case 1:
		{
			WH.Xiu += 50;
			HB += 500;
			Y("获得魂币500修为50");
			getch();
			break;
		}
	case 3:
		{
			WH.Xiu += 100;
			HB += 500;
			
			Y("获得魂币500修为100");
			getch();
			break;
		}
	case 2:
		{
			Npc[3].CanShow = 1;
			WH.Xiu += 100;
			HB += 500;
			for (int i = 1; i <= 99; i++)
				if (Bag[i].XiaoGuo == 1)
					Bag[i].Count -= 5;
			UpdateBag();
			Y("获得魂币500修为100");
			getch();
			break;
		}
	case 4:
		{
			WH.Xiu += 200;
			HB += 1000;
			for (int i = 1; i <= 99; i++)
				if (Bag[i].XiaoGuo == 0 || Bag[i].XiaoGuo == 2)
				{
					Bag[i] = Item[2];
					Bag[i].Count += 10;
					break;
				}
			Y("获得魂币1000修为200回魂丹10个");
			Npc[3].CanShow=0;
			getch();
			break;
		}
	}
	RW[a.Reward].IsFinish = 1;
	a.IsFinish = 1;
	UpdateRW();
	UpdateBag();
	UpdateLV();
	return 1;
}

bool RenWu::UseItem(DaoJu & a)	// 使用道具
{
	switch (a.XiaoGuo)
	{
	case 1:
		{
			Y("这东西没啥用……");
			break;
		}
	case 2:
		{
			Y("这东西只能在战斗中使用……");
			break;
		}
	case 3:
		{
			Y("这东西没啥用……");
			break;
		}
	}
	getch();
	UpdateBag();
	return 1;
}

void RenWu::OutPutBag()			// 输出背包
{
	DrawLine;
	int JS = 1;
	int i = 1, j = 1;
	while (JS != 0)
	{
		clrscr();
		Y("*****背包*****");
		for (; i <= j + 4; i++)
			if (Bag[i].XiaoGuo != 0)
				S(i - j + 1, ".", Bag[i].Name);
			else
				S(i - j + 1, ".", "空");
		C("6.下一页 " << "7.上一页" << " 0.返回");
		DrawLine;
		Y("请输入：");
		int a = getch() - 48;
		switch (a)
		{
		case 1:
			{
				OutPut(Bag[i - 5]);
				i = i - 5;
				break;
			}
		case 2:
			{
				OutPut(Bag[i - 4]);
				i = i - 5;
				break;
			}
		case 3:
			{

				OutPut(Bag[i - 3]);
				i = i - 5;
				break;
			}

		case 4:
			{
				OutPut(Bag[i - 2]);
				i = i - 5;
				break;
			}
		case 5:
			{
				OutPut(Bag[i - 1]);
				i = i - 5;
				break;
			}

		case 6:
			{
				j = j + 5;
				if (j >= 91)
					j = 91;
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
					          clrscr();
}

void RenWu::OutPut(HunJi a)
{
	E("魂技名称：", a.Name);
	E("魂技描述：", a.Des);
	E("所需魂力：", a.HunLi);
	DrawLine;

}

void RenWu::OutPutWH()			// 输出魂灵
{
	clrscr();
	WuHun a = WH;
	Y("*****魂灵*****");
	E("魂币：", HB);
	E("魂兽名字：", a.Name);
	E("魂兽描述：", a.Des);
	E("等级：", a.Level);
	E("修为：", a.Xiu);
	E("力量：", a.Li);
	E("敏捷：", a.Min);
	E("每级增加力量：", a.M_Li);
	E("每级增加敏捷：", a.M_Min);
	E("攻击力：", a.APoint);
	E("防御力：", a.DPoint);
	E("生命力：", a.SPoint);
	E("魂力：", a.HPoint);
	E("力量攻击指数：", a.ZL_APoint);
	E("力量防御指数：", a.ZL_DPoint);
	E("敏捷攻击指数：", a.ZM_APoint);
	E("敏捷防御指数：", a.ZM_DPoint);
	E("生命等级指数：", a.Z_SPoint);
	E("魂力生命指数：", a.Z_HPoint);
	E("冰抗：", a.K_Bing);
	E("火抗：", a.K_Huo);
	E("电抗：", a.K_Dian);
	E("土抗：", a.K_Tu);
	E("暗抗：", a.K_An);
	E("光抗：", a.K_Guang);
	DrawLine;
	for (int i = 1; i <= 9; i++)
	{
		int temp = a.MyHJ[i];
		Y(temp);
		OutPut(HJ[temp]);
	}
	getch();
					          clrscr();
}

void RenWu::OutPutRW()			// 输出任务
{
	clrscr();
	DrawLine;
	int JS = 1;
	int i = 1, j = 1;
	while (JS != 0)
	{
		clrscr();
		Y("*****任务*****");
		for (; i <= j + 4; i++)
			if (MyRW[i].Reward != 0)
				S(i - j + 1, ".", MyRW[i].Name);
			else
				S(i - j + 1, ".", "未接");
		C("6.下一页 " << "7.上一页" << " 0.返回");
		DrawLine;
		Y("请输入：");
		int a = getch() - 48;
		switch (a)
		{
		case 1:
			{
				OutPut(MyRW[i - 5]);
				i = i - 5;
				break;
			}
		case 2:
			{
				OutPut(MyRW[i - 4]);
				i = i - 5;
				break;
			}
		case 3:
			{
				OutPut(MyRW[i - 3]);
				i = i - 5;
				break;
			}

		case 4:
			{
				OutPut(MyRW[i - 2]);
				i = i - 5;
				break;
			}
		case 5:
			{
				OutPut(MyRW[i - 1]);
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
		default:
			break;
		}
	}
				          clrscr();
}