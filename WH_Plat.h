template < class T > class Platform	// 攻击场景类
{
  public:
	RenWu * Me;
	int ZT[500];				// 技能冷却时间
	int EZT[500];
	WuHun WHTemp;				// 用于恢复正常状态
	template < typename T1, typename S1 > double UseSkill(T1 & A, S1 & B, int C);	// 技能使用，返回伤害值
	T Enemy;
	int Turn;
	Platform(RenWu & A, T B);
	int Begin();
	int OutPut(DaoJu a);		// 输出道具并返回使用了哪个道具
	void OutPut(T a);			// 输出敌人信息
	void OutPut(RenWu * a);
	void OutPutEnemy(T a);
	void OutPutWH(WuHun a);
	void EnemyATK(T & A, WuHun & B);	// 对方攻击
	void Attack(WuHun & A, T & B);	// 普通攻击
	void Skill(WuHun & A, T & B);	// 使用技能攻击
	void Use(RenWu * A, T & B);	// 使用道具攻击
	int Check();
	// 判断战斗是否已结束
};

template < class T > int Platform < T >::Check()
{
	if (Me->WH.SPoint <= 0)		// 我方战斗失败
		return -1;
	if (Enemy.SPoint < 0)		// 我方胜利
		return -2;
	if (Turn > 50)				// 平局
		return -3;
	return 1;
}

template < class T > int Platform < T >::OutPut(DaoJu a)
{
	if (a.Count == 0)
		return -1;
	DrawLine;
	E("道具名：", a.Name);
	E("道具介绍：", a.Des);
	E("数量：", a.Count);
	Y("1.使用");
	Y("0.返回");
	int t = getch() - 48;
	if (t == 1)
		return a.XiaoGuo;
	return -1;
}

template < class T > template < typename T1,
	typename S1 > double Platform < T >::UseSkill(T1 & A, S1 & B, int C)
{
	double SH = 0;				// 攻击造成伤害
	double XS = 0;				// 防御吸收伤害
	double blood = 0;			// 最终伤害
	HJ[C].IsFind = 1;			// 设置已发现
	switch (HJ[C].XiaoGuo)
	{
	case 1:
		{
			Y("使用技能！冲撞！对对方造成猛烈打击！");
			double Rand = GetRand(800, 100) / 80;
			SH = A.APoint * (1 + (A.ZL_APoint + A.ZM_APoint) / 10) * Rand;
			Rand = GetRand(80, 100) / 500;
			XS = B.DPoint * (1 + (B.ZL_DPoint + B.ZM_DPoint) / 10) * Rand;
			blood = SH - XS;
			break;
		}
	case 2:
		{
			Y("使用技能！高级冲撞！对对方造成极大的打击！");
			double Rand = GetRand(100, 120) / 80;
			SH = A.APoint * (1 + (A.ZL_APoint + A.ZM_APoint) / 10) * Rand;
			Rand = GetRand(80, 100) / 500;
			XS = B.DPoint * (1 + (B.ZL_DPoint + B.ZM_DPoint) / 10) * Rand;
			blood = SH - XS;
			break;
		}
	case 3:
		{
			Y("召唤异世之剑斩向对方！对对方造成极大的打击！");
			double Rand = GetRand(120, 150) / 80;
			SH = A.APoint * (1 + (A.ZL_APoint + A.ZM_APoint) / 10) * Rand;
			Rand = GetRand(80, 100) / 500;
			XS = B.DPoint * (1 + (B.ZL_DPoint + B.ZM_DPoint) / 10) * Rand;
			blood = SH - XS;
			break;
		}
	case 4:
		{
			Y("灵魂窃取！吸取对方生命！呵哈哈哈！");
			double Rand = GetRand(100, 120) / 80;
			SH = A.APoint * (1 + (A.ZL_APoint + A.ZM_APoint) / 10) * Rand;
			A.SPoint += SH/10;
			S("吸取了", SH, "点生命");
			blood = SH;
			break;
		}
	case 5:
		{
			if (B.Xiu == WHTemp.Xiu)
				EZT[C] += 3;
			else
				ZT[C] += 3;
			Y("凝聚吧！我的灵魂！防御力得到提升！");
				double Rand = GetRand(1, 5) ;
			double BB = A.DPoint *Rand/100;
			A.DPoint = A.DPoint + BB;
			S("防御力提升了", BB, "点");
			blood = 0;
			break;
		}
	case 6:
		{
			Y("灵魂冲击！造成极大的精神打击！");
			double Rand = GetRand(150, 180) / 80;
			SH = A.APoint * (1 + (A.ZL_APoint + A.ZM_APoint) / 10) * Rand;
			Rand = GetRand(80, 100) / 500;
			XS = B.DPoint * (1 + (B.ZL_DPoint + B.ZM_DPoint) / 10) * Rand;
			blood = SH - XS;
			break;
		}
	case 7:
		{
			if (B.Xiu == WHTemp.Xiu)
				EZT[C] += 7;
			else
				ZT[C] += 7;
			Y("灵魂实体化！防御力提升100%！");
					double Rand = GetRand(30, 50) ;
			double BB = A.DPoint *Rand/100;
			A.DPoint = A.DPoint + BB;
			S("防御力提升了", BB, "点");
			blood = 0;
			break;
		}
	case 8:
		{
			if (B.Xiu == WHTemp.Xiu)
				EZT[C] += 4;
			else
				ZT[C] += 4;
			Y("地狱之灵涌现！接受惩罚吧！");
			double Rand = GetRand(150, 180) / 80;
			SH = A.APoint * (1 + (A.ZL_APoint + A.ZM_APoint) / 10) * Rand;
			Rand = GetRand(80, 100) / 500;
			Rand = GetRand(1, 5) ;
			double BB = B.DPoint *Rand/100;
			B.DPoint = B.DPoint -BB;
			S("对方防御力降低了", BB, "点");
			XS = B.DPoint * (1 + (B.ZL_DPoint + B.ZM_DPoint) / 10) * Rand;
			blood = SH - XS;
			break;
		}
	case 9:
		{
			if (B.Xiu == WHTemp.Xiu)
				EZT[C] += 4;
			else
				ZT[C] += 4;
			Y("天使降临！命运交响曲响起！");
			double Rand = GetRand(180, 210) / 80;
			SH = A.APoint * (1 + (A.ZL_APoint + A.ZM_APoint) / 10) * Rand;
			Rand = GetRand(1, 5) ;
			double BB = B.DPoint *Rand/100;
			B.DPoint = B.DPoint - BB;
			Rand = GetRand(1, 5) ;
			BB = B.APoint *Rand/100;
			B.APoint = B.APoint - BB;
			Y("对方防御力攻击力都降低了！");
			XS = B.DPoint * (1 + (B.ZL_DPoint + B.ZM_DPoint) / 10) * Rand;
			blood = SH - XS;
			break;
		}
	case 101:
		{
			Y("龙震！一声龙吟响起！");
			double Rand = GetRand(120, 150) / 80;
			SH = A.APoint * (1 + (A.ZL_APoint + A.ZM_APoint) / 10) * Rand;
			Rand = GetRand(80, 100) / 500;
			XS = B.DPoint * (1 + (B.ZL_DPoint + B.ZM_DPoint) / 10) * Rand;
			blood = SH - XS;
			break;
		}
	case 102:
		{
			if (B.Xiu == WHTemp.Xiu)
				EZT[C] += 4;
			else
				ZT[C] += 4;
			Y("龙威！额头龙纹闪现！");
			double Rand = GetRand(120, 130) / 80;
			SH = A.APoint * (1 + (A.ZL_APoint + A.ZM_APoint) / 10) * Rand;
			Rand = GetRand(80, 100) / 500;
			XS = B.DPoint * (1 + (B.ZL_DPoint + B.ZM_DPoint) / 10) * Rand;
			Rand = GetRand(5, 10) ;
			double BB = A.APoint *Rand/100;
			A.APoint = A.APoint + BB;
			Y("攻击力提升了！");
			Rand = GetRand(1, 5) ;
			BB = B.DPoint *Rand/100;
			B.DPoint -= BB;
			Y("对方防御力降低了！");
			blood = SH - XS;
			break;
		}
	case 103:
		{
			if (B.Xiu == WHTemp.Xiu)
				EZT[C] += 4;
			else
				ZT[C] += 4;
			Y("龙吟！！穿心一击！带走灵魂！");
			double Rand = GetRand(120, 150) / 80;
			SH = A.APoint * (1 + (A.ZL_APoint + A.ZM_APoint) / 10) * Rand;
			Rand = GetRand(80, 100) / 500;
			XS = B.DPoint * (1 + (B.ZL_DPoint + B.ZM_DPoint) / 12) * Rand;
			Rand = GetRand(10, 15) ;
			double BB = A.APoint *Rand/100;
			A.APoint = A.APoint + BB;
			Y("攻击力提升了！");
			blood = SH - XS;
			break;
		}
	case 104:
		{
			if (B.Xiu == WHTemp.Xiu)
				EZT[C] += 6;
			else
				ZT[C] += 6;
			Y("龙啸！鼓舞士气！威震对方！");
			double Rand = GetRand(10, 15) ;
			double BB = A.APoint *Rand/100;
			A.APoint = A.APoint + BB;
			Y("攻击力提升了！");
			Rand = GetRand(10, 15) ;
			BB = B.APoint *Rand/100;
			B.APoint = B.APoint - BB;
			Y("对方攻击力降低了！");
			blood = 0;
			break;
		}
	case 105:
		{
			Y("龙王炮！龙枪一挥！哄！！");
			double Rand = GetRand(180, 210) / 80;
			SH = A.APoint * (1 + (A.ZL_APoint + A.ZM_APoint) / 10) * Rand;
			Rand = GetRand(80, 100) / 500;
			XS = B.DPoint * (1 + (B.ZL_DPoint + B.ZM_DPoint) / 10) * Rand;
			blood = SH - XS;
			break;
		}
	case 106:
		{
				if (B.Xiu == WHTemp.Xiu)
				EZT[C] += 4;
			else
				ZT[C] += 4;
			Y("龙枪飞出！带出一片残影！");
			double Rand = GetRand(150, 180) / 80;
			SH = A.APoint * (1 + (A.ZL_APoint + A.ZM_APoint) / 10) * Rand;
			Rand = GetRand(80, 100) / 500;
			XS = B.DPoint * Rand;
			blood = SH - XS;
			Rand = GetRand(10, 15) ;
			double BB = B.DPoint *Rand/100;
			B.DPoint = B.DPoint -BB;
			Y("防御力降低了！");
			break;
		}
	case 107:
		{
			if (B.Xiu == WHTemp.Xiu)
				EZT[C] += 10;
			else
				ZT[C] += 10;
			Y("龙枪附体！力量无限！！");
		    double Rand = GetRand(30, 50) ;
			double BB = A.APoint *Rand/100;
			A.APoint = A.APoint + BB;
			Y("攻击力提升了！");
			blood = 0;
			break;
		}
	case 108:
		{
			if (B.Xiu == WHTemp.Xiu)
				EZT[C] += 10;
			else
				ZT[C] += 10;
			Y("龙枪化鳞！防御无限！！");
			double Rand = GetRand(30, 50) ;
			double BB = A.DPoint *Rand/100;
			A.DPoint = A.DPoint + BB;
			Y("防御力提升了！");blood = 0;
			break;
		}
	case 109:
		{
			if (B.Xiu == WHTemp.Xiu)
				EZT[C] += 10;
			else
				ZT[C] += 10;
			Y("龙王在此！！！");
			Y("龙王炮五连发！");
			double Rand = GetRand(300, 400) / 80;
			SH = A.APoint * (1 + (A.ZL_APoint + A.ZM_APoint) / 10) * Rand;
			Rand = GetRand(80, 100) / 500;
			XS = B.DPoint * (1 + (B.ZL_DPoint + B.ZM_DPoint) / 10) * Rand;
			blood = (SH - XS) ;
			break;
		}
	default:
		break;
	}
	A.HPoint -= HJ[C].HunLi;	// 减魂力
	return blood;

}

template < class T > void Platform < T >::Skill(WuHun & A, T & B)
{
	int JS = 0;
	double blood = 0;
	while (JS == 0)
	{
		clrscr();
		Y("****【请输入你要发动的技能】****");
		int temp = 0;
		for (int i = 1; i <= 9; i++)
		{
			temp = A.MyHJ[i];
			C(i << "." << HJ[temp].
			  Name << "  " << HJ[temp].Des << " " << HJ[temp].HunLi);
		}
		Y("输入【G】切换成普通攻击【B】切换背包");
		int p = getch();
		if (p < 96)
		{
			p -= 48;
			temp = A.MyHJ[p];
			if (HJ[temp].HunLi > A.HPoint || ZT[temp] > 0 || p > 9 || p < 1)
			{
				Y("魂力不足！或冷却中-_-||或无效操作-_-||");
				getch();
			}
			else
			{
				clrscr();
				Y("*******【我方使用技能攻击】*******");
				blood = UseSkill(A, B, temp);
				JS = 1;
			}
		}
		if (p == 'g')			// 切换到普通攻击
		{
			Attack(A, B);
			JS = 1;
			return;
		}
		if (p == 'b')			// 切换到背包
		{
			Use(Me, B);
			JS = 1;
			return;
		}
	}
	// 抗性相关
	double total = A.K_Bing + A.K_Huo + A.K_Dian + A.K_Tu + A.K_Guang + A.K_An;
	total =
		total - (B.K_Bing + B.K_Huo + B.K_Dian + B.K_Tu + B.K_Guang + B.K_An);
	if (total <= 0)
		total = 0;
	else
		blood = blood * ((total / 10) + 1);
	if (blood <= 0)
		blood = 0;
	S(A.Name, "使用技能攻击造成伤害：", blood);
	B.SPoint = B.SPoint - blood;
}

template < class T > void Platform < T >::Use(RenWu * A, T & B)
{
	double SH = 0;				// 攻击造成伤害
	double XS = 0;				// 防御吸收伤害
	double blood = 0;			// 最终伤害
	int XG = 0;					// 使用了哪个道具
	int JS = 1;
	int i = 1, j = 1;
	int ZJS = 1;
	while (XG != -1 && ZJS == 1)
	{
		clrscr();
		JS = 1;
		while (JS != 0)
		{
			Y("*****【使用道具】*****");
			Y("【请输入要使用的道具】");
			for (; i <= j + 4; i++)
				if (A->Bag[i].XiaoGuo != 0)
					S(i - j + 1, ".", A->Bag[i].Name);
				else
					S(i - j + 1, ".", "空");
			C("6.下一页 " << "7.上一页" << "【G】切换普攻" <<
			  "【S】切换技能");
			DrawLine;
			int p = getch();
			if (p < 96)
				p -= 48;
			if (p == 'g')
			{
				Attack(A->WH, B);
				JS = 0;
				return;
			}
			if (p == 's')
			{
				Skill(A->WH, B);
				JS = 0;
				return;
			}
			switch (p)
			{
			case 1:
				{
					XG = OutPut(A->Bag[i - 5]);
					i = i - 5;
					break;
				}
			case 2:
				{
					XG = OutPut(A->Bag[i - 4]);
					i = i - 5;
					break;
				}
			case 3:
				{

					XG = OutPut(A->Bag[i - 3]);
					i = i - 5;
					break;
				}

			case 4:
				{
					XG = OutPut(A->Bag[i - 2]);
					i = i - 5;
					break;
				}
			case 5:
				{
					XG = OutPut(A->Bag[i - 1]);
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
			default:
				i = i - 5;

			}
			clrscr();
			if (XG > 0)
				JS = 0;
		}
		// 道具效果
		switch (XG)
		{
		case 1:
			{
				Y("这东西貌似没啥用……");
				getch();
				ZJS = 1;
				break;
			}
		case 2:
			{
				A->WH.SPoint += 200;
				if (A->WH.SPoint > WHTemp.SPoint)
					A->WH.SPoint = WHTemp.SPoint;
				Y("生命恢复了200点！");
				getch();
				ZJS = 0;
				for (int ABC = 1; ABC < 100; ABC++)
					if (A->Bag[ABC].XiaoGuo == XG)
					{
						A->Bag[ABC].Count--;
						break;
					}
				break;
			}
		case 3:
			{
				Y("这东西貌似没啥用……");
				getch();
				ZJS = 1;
				break;
			}

		}
		XG = 0;
	}
	// 抗性相关
	WuHun A1 = A->WH;
	double total =
		A1.K_Bing + A1.K_Huo + A1.K_Dian + A1.K_Tu + A1.K_Guang + A1.K_An;
	total =
		total - (B.K_Bing + B.K_Huo + B.K_Dian + B.K_Tu + B.K_Guang + B.K_An);
	if (total <= 0)
		total = 0;
	else
		blood = blood * ((total / 10) + 1);
	if (blood <= 0)
		blood = 0;
	S(A->Name, "使用道具！造成伤害：", blood);
	B.SPoint = B.SPoint - blood;
	Check();

	A->UpdateBag();


}

template < class T > void Platform < T >::Attack(WuHun & A, T & B)
{
	if (Check() < 0)
		return;
	Y("*******【我方使用普通攻击】*******");
	double SH = 0;				// 攻击造成伤害
	double XS = 0;				// 防御吸收伤害
	double blood = 0;			// 最终伤害
	double Rand = GetRand(50, 80) / 80;
	SH = A.APoint * (1 + (A.ZL_APoint + A.ZM_APoint) / 10) * Rand;
	Rand = GetRand(80, 100) / 500;
	XS = B.DPoint * (1 + (B.ZL_DPoint + B.ZM_DPoint) / 10) * Rand;
	blood = SH - XS;

	double total = A.K_Bing + A.K_Huo + A.K_Dian + A.K_Tu + A.K_Guang + A.K_An;
	total =
		total - (B.K_Bing + B.K_Huo + B.K_Dian + B.K_Tu + B.K_Guang + B.K_An);
	if (total <= 0)
		total = 0;
	else
		blood = blood * ((total / 10) + 1);
	if (blood <= 0)
		blood = 0;
	S(A.Name, "使用普通攻击，造成伤害：", blood);
	B.SPoint = B.SPoint - blood;
}

template < class T > void Platform < T >::EnemyATK(T & A, WuHun & B)
{
	if (Check() < 0)
		return;
	int type = GetRand(1, 5);
	double blood = 0;			// 最终伤害
	if (type >= 2)
	{
		if (A.HPoint < HJ[A.MyHJ[1]].HunLi)
			type = 1;
		int Skill = 1;
		int i = 9;
		Skill = A.MyHJ[i];
		while ((A.HPoint < HJ[Skill].HunLi || EZT[Skill] > 0) && type != 1)
		{
			i--;
			Skill = A.MyHJ[i];
			if (A.HPoint < HJ[A.MyHJ[1]].HunLi || i == 0)
				type = 1;
		}
		if (type != 1)
		{
			Y("*******〖对方使用技能攻击〗*******");
			blood = UseSkill(A, B, Skill);
		}
	}
	if (type == 1)
	{
		Y("*******〖对方使用普通攻击〗*******");
		double SH = 0;			// 攻击造成伤害
		double XS = 0;			// 防御吸收伤害
		double Rand = GetRand(50, 80) / 80;
		SH = A.APoint * (1 + (A.ZL_APoint + A.ZM_APoint) / 10) * Rand;
		Rand = GetRand(80, 100) / 500;
		XS = B.DPoint * (1 + (B.ZL_DPoint + B.ZM_DPoint) / 10) * Rand;
		blood = SH - XS;
	}
	double total = A.K_Bing + A.K_Huo + A.K_Dian + A.K_Tu + A.K_Guang + A.K_An;
	total =
		total - (B.K_Bing + B.K_Huo + B.K_Dian + B.K_Tu + B.K_Guang + B.K_An);
	if (total <= 0)
		total = 0;
	else
		blood = blood * ((total / 10) + 1);
	if (blood <= 0)
		blood = 0;
	S(A.Name, "攻击，造成伤害：", blood);
	B.SPoint = B.SPoint - blood;

	Check();
}

template < class T > void Platform < T >::OutPutEnemy(T a)
{
	E("名字：", a.Name);
	E("描述：", a.Des);
	E("等级：", a.Level);
	E("力量：", a.Li);
	E("敏捷：", a.Min);
	E("生命力：", a.SPoint);
	E("魂力：", a.HPoint);
	E("攻击力：", a.APoint);
	E("防御力：", a.DPoint);
}

template < class T > void Platform < T >::OutPutWH(WuHun a)
{
	E("名字：", a.Name);
	E("描述：", a.Des);
	E("等级：", a.Level);
	E("力量：", a.Li);
	E("敏捷：", a.Min);
	E("生命力：", a.SPoint);
	E("魂力：", a.HPoint);
	E("攻击力：", a.APoint);
	E("防御力：", a.DPoint);
}

template < class T > void Platform < T >::OutPut(T a)
{
	S("******", a.Name, "******");
	Y(a.Name);
	E("生命：", a.SPoint);
	E("魂力：", a.HPoint);
}

template < class T > void Platform < T >::OutPut(RenWu * a)
{
	S("******", a->Name, "******");
	Y(a->WH.Name);
	E("生命：", a->WH.SPoint);
	E("魂力：", a->WH.HPoint);
}

template < class T > Platform < T >::Platform(RenWu & A, T B)
{
	Enemy = B;
	Me = &A;
	Turn = 0;
	WHTemp = Me->WH;
}

template < class T > int Platform < T >::Begin()
{
	for (int i = 0; i < 500; i++)
	{
		ZT[i] = 0;
		EZT[i] = 0;
	}
	int End = 0;
	int type = 0;
	while (End == 0)
	{
		DrawLine;
		Y("******【战斗进行中】******");
		OutPut(Enemy);
		OutPut(Me);
		DrawLine;
		Y("1.普攻 2.技能  3.道具 4.查看 5.魂灵 ");
		int a;
		a = getch() - 48;
		clrscr();
		if (a == 1)
		{
			Turn++;
			for (int i = 0; i < 500; i++)
			{
				ZT[i]--;
				EZT[i]--;
				if (ZT[i] < 0)
					ZT[i] = 0;
				if (EZT[i] < 0)
					EZT[i] = 0;
			}
			if (Me->WH.Min >= Enemy.Min)
			{
				Attack(Me->WH, Enemy);
				type = Check();
				if (type == -1)
				{
					Y("***【我方战斗失败！】***");
					Me->WH = WHTemp;
					return -1;
				}
				if (type == -2)
				{
					Y("***【我方战斗胜利！】***");
					Me->WH = WHTemp;
					return -2;
				}
				if (type == -3)
				{
					Y("******【平局！】******");
					Me->WH = WHTemp;
					return -3;
				}
				EnemyATK(Enemy, Me->WH);
				type = Check();
				if (type == -1)
				{
					Y("***【我方战斗失败！】***");
					Me->WH = WHTemp;
					return -1;
				}
				if (type == -2)
				{
					Y("***【我方战斗胜利！】***");
					Me->WH = WHTemp;
					return -2;
				}
				if (type == -3)
				{
					Y("******【平局！】******");
					Me->WH = WHTemp;
					return -3;
				}
			}
			else
			{

				EnemyATK(Enemy, Me->WH);
				type = Check();
				if (type == -1)
				{
					Y("***【我方战斗失败！】***");
					Me->WH = WHTemp;
					return -1;
				}
				if (type == -2)
				{
					Y("***【我方战斗胜利！】***");
					Me->WH = WHTemp;
					return -2;
				}
				if (type == -3)
				{
					Y("******【平局！】******");
					Me->WH = WHTemp;
					return -3;
				}
				Attack(Me->WH, Enemy);
				type = Check();
				if (type == -1)
				{
					Y("***【我方战斗失败！】***");
					Me->WH = WHTemp;
					return -1;
				}
				if (type == -2)
				{
					Y("***【我方战斗胜利！】***");
					Me->WH = WHTemp;
					return -2;
				}
				if (type == -3)
				{
					Y("******【平局！】******");
					Me->WH = WHTemp;
					return -3;
				}
			}
		}
		if (a == 2)
		{
			Turn++;
			for (int i = 0; i < 500; i++)
			{
				ZT[i]--;
				EZT[i]--;
				if (ZT[i] < 0)
					ZT[i] = 0;
				if (EZT[i] < 0)
					EZT[i] = 0;
			}
			if (Me->WH.Min >= Enemy.Min)
			{
				Skill(Me->WH, Enemy);
				type = Check();
				if (type == -1)
				{
					Y("***【我方战斗失败！】***");
					Me->WH = WHTemp;
					return -1;
				}
				if (type == -2)
				{
					Y("***【我方战斗胜利！】***");
					Me->WH = WHTemp;
					return -2;
				}
				if (type == -3)
				{
					Y("******【平局！】******");
					Me->WH = WHTemp;
					return -3;
				}
				EnemyATK(Enemy, Me->WH);
				type = Check();
				if (type == -1)
				{
					Y("***【我方战斗失败！】***");
					Me->WH = WHTemp;
					return -1;
				}
				if (type == -2)
				{
					Y("***【我方战斗胜利！】***");
					Me->WH = WHTemp;
					return -2;
				}
				if (type == -3)
				{
					Y("******【平局！】******");
					Me->WH = WHTemp;
					return -3;
				}
			}
			else
			{
				EnemyATK(Enemy, Me->WH);
				type = Check();
				if (type == -1)
				{
					Y("***【我方战斗失败！】***");
					Me->WH = WHTemp;
					return -1;
				}
				if (type == -2)
				{
					Y("***【我方战斗胜利！】***");
					Me->WH = WHTemp;
					return -2;
				}
				if (type == -3)
				{
					Y("******【平局！】******");
					Me->WH = WHTemp;
					return -3;
				}
				Skill(Me->WH, Enemy);
				type = Check();
				if (type == -1)
				{
					Y("***【我方战斗失败！】***");
					Me->WH = WHTemp;
					return -1;
				}
				if (type == -2)
				{
					Y("***【我方战斗胜利！】***");
					Me->WH = WHTemp;
					return -2;
				}
				if (type == -3)
				{
					Y("******【平局！】******");
					Me->WH = WHTemp;
					return -3;
				}
			}
		}
		if (a == 3)
		{
			Turn++;
			for (int i = 0; i < 500; i++)
			{

				ZT[i]--;
				EZT[i]--;
				if (ZT[i] < 0)
					ZT[i] = 0;
				if (EZT[i] < 0)
					EZT[i] = 0;
			}
			if (Me->WH.Min >= Enemy.Min)
			{
				Use(Me, Enemy);
				type = Check();
				if (type == -1)
				{
					Y("***【我方战斗失败！】***");
					Me->WH = WHTemp;
					return -1;
				}
				if (type == -2)
				{
					Y("***【我方战斗胜利！】***");
					Me->WH = WHTemp;
					return -2;
				}
				if (type == -3)
				{
					Y("******【平局！】******");
					Me->WH = WHTemp;
					return -3;
				}
				EnemyATK(Enemy, Me->WH);
				type = Check();
				if (type == -1)
				{
					Y("***【我方战斗失败！】***");
					Me->WH = WHTemp;
					return -1;
				}
				if (type == -2)
				{
					Y("***【我方战斗胜利！】***");
					Me->WH = WHTemp;
					return -2;
				}
				if (type == -3)
				{
					Y("******【平局！】******");
					Me->WH = WHTemp;
					return -3;
				}
			}
			else
			{
				EnemyATK(Enemy, Me->WH);
				type = Check();
				if (type == -1)
				{
					Y("***【我方战斗失败！】***");
					Me->WH = WHTemp;
					return -1;
				}
				if (type == -2)
				{
					Y("***【我方战斗胜利！】***");
					Me->WH = WHTemp;
					return -2;
				}
				if (type == -3)
				{
					Y("******【平局！】******");
					Me->WH = WHTemp;
					return -3;
				}
				Use(Me, Enemy);
				type = Check();
				if (type == -1)
				{
					Y("***【我方战斗失败！】***");
					Me->WH = WHTemp;
					return -1;
				}
				if (type == -2)
				{
					Y("***【我方战斗胜利！】***");
					Me->WH = WHTemp;
					return -2;
				}
				if (type == -3)
				{
					Y("******【平局！】******");
					Me->WH = WHTemp;
					return -3;
				}
			}
		}
		if (a == 4)
			OutPutEnemy(Enemy);
		if (a == 5)
			OutPutWH(Me->WH);

		type = Check();
		if (type == -1)
		{
			Y("***【我方战斗失败！】***");
			Me->WH = WHTemp;
			return -1;
		}
		if (type == -2)
		{
			Y("***【我方战斗胜利！】***");
			Me->WH = WHTemp;
			return -2;
		}
		if (type == -3)
		{
			Y("******【平局！】******");
			Me->WH = WHTemp;
			return -3;
		}
	}
}