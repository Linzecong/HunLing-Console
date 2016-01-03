class WuHun:public ZS_Date, public RW_Date
{
  public:
	char Name[40];
    char Des[150];				// 描述
	int IsFind;					// 是否已发现
	int MyHJ[10];				// 将会获得的魂技
	int Level;					// 级别
	double Xiu;					// 修为
    bool Init();			// 初始化
    bool Save();
    bool InitWH(HunShou A_HS);	// 用魂兽初始化武魂
    WuHun(){}
} WH[200];

bool WuHun::InitWH(HunShou A_HS)// 用魂兽初始化武魂
{
	for(int i=0;i<=39;i++)
	Name[i]=A_HS.Name[i];
	Li = A_HS.Li;
	Min = A_HS.Min;
	APoint = A_HS.APoint;
	DPoint = A_HS.DPoint;
	SPoint = A_HS.SPoint;
	HPoint = A_HS.HPoint;
	ZL_APoint = A_HS.ZL_APoint;
	ZL_DPoint = A_HS.ZL_DPoint;
	ZM_APoint = A_HS.ZM_APoint;
	ZM_DPoint = A_HS.ZM_DPoint;
	Z_SPoint = A_HS.Z_SPoint;
	Z_HPoint = A_HS.Z_HPoint;
	M_Li = A_HS.M_Li;
	M_Min = A_HS.M_Min;
	K_Bing = A_HS.K_Bing;		// 冰
	K_Huo = A_HS.K_Huo;			// 火
	K_Dian = A_HS.K_Dian;		// 电
	K_Tu = A_HS.K_Tu;			// 土
	K_Guang = A_HS.K_Guang;		// 光
	K_An = A_HS.K_An;			// 暗
	for (int i = 1; i <= 9; i++)
		MyHJ[i] = A_HS.MyHJ[i];

    return 1;
}

bool WuHun::Save()//保存
{
    ofstream on(WH_SAVEPATH,ios::binary);
	for (int i = 1; i <= 199; i++)
        on.write((char *)&WH[i].IsFind,sizeof(IsFind));
	on.close();
	return 1;
}

bool WuHun::Init()//读取
{
    ifstream on(WH_SAVEPATH, ios::binary);//读取是否已发现
	for (int i = 1; i <= 199; i++)
		on.read((char *)&WH[i].IsFind, sizeof(IsFind));
	on.close();
    ifstream oen(WHS_DATAPATH, ios::binary);//读取魂兽武魂
	for (int i = 1; i <= 99; i++)
	{
		oen.read((char *)&WH[i].Des, sizeof(Des));
		WH[i].InitWH(HS[i]);
	}
	oen.close();
    ifstream open(WHQ_DATAPATH, ios::binary);//读取器武魂
	for (int i = 100; i <= 199; i++)
	{
		open.read((char *)&WH[i].Name, sizeof(Name));
		open.read((char *)&WH[i].Des, sizeof(Des));
		open.read((char *)&WH[i].Li, sizeof(Li));
		open.read((char *)&WH[i].Min, sizeof(Min));
		open.read((char *)&WH[i].M_Li, sizeof(M_Li));
		open.read((char *)&WH[i].M_Min, sizeof(M_Min));
		open.read((char *)&WH[i].APoint, sizeof(APoint));
		open.read((char *)&WH[i].DPoint, sizeof(DPoint));
		open.read((char *)&WH[i].SPoint, sizeof(SPoint));
		open.read((char *)&WH[i].HPoint, sizeof(HPoint));
		open.read((char *)&WH[i].ZL_APoint, sizeof(ZL_APoint));
		open.read((char *)&WH[i].ZL_DPoint, sizeof(ZL_DPoint));
		open.read((char *)&WH[i].ZM_APoint, sizeof(ZM_APoint));
        open.read((char *)&WH[i].ZM_DPoint, sizeof(ZM_DPoint));;
		open.read((char *)&WH[i].Z_SPoint, sizeof(Z_SPoint));
		open.read((char *)&WH[i].Z_HPoint, sizeof(Z_HPoint));
		open.read((char *)&WH[i].K_Bing, sizeof(K_Bing));
		open.read((char *)&WH[i].K_Huo, sizeof(K_Huo));
		open.read((char *)&WH[i].K_Dian, sizeof(K_Dian));
		open.read((char *)&WH[i].K_Tu, sizeof(K_Tu));
		open.read((char *)&WH[i].K_Guang, sizeof(K_Guang));
		open.read((char *)&WH[i].K_An, sizeof(K_An));
		open.read((char *)&WH[i].MyHJ[1], sizeof(MyHJ[1]) * 9);
	}
	open.close();
	return 1;
}

WuHun CreateWH(WuHun _HS, int LV)	// 生成武魂
{
	_HS.Level = LV;
	_HS.Li = 20+ _HS.M_Li * LV;
	_HS.Min = 20 + _HS.M_Min * LV;
	_HS.APoint = 50+_HS.Li /10* (1+_HS.ZL_APoint/5)*LV+ _HS.Min/10 * (1+_HS.ZM_APoint/5)*LV;
	_HS.DPoint = 50+_HS.Li/10 * (1+_HS.ZL_DPoint/5)*LV+ _HS.Min /10* (1+_HS.ZM_DPoint/5)*LV;
	if (LV < 30)
		_HS.SPoint = 300 + LV * 50 * _HS.Z_SPoint;
	if (LV >= 30 && LV < 70)
		_HS.SPoint = 1500 + LV * 100 * _HS.Z_SPoint;
	if (LV >= 70 && LV < 90)
		_HS.SPoint = 3000 + LV * 150 * _HS.Z_SPoint;
	if (LV >= 90 && LV <= 94)
		_HS.SPoint = 5000 + LV * 200 * _HS.Z_SPoint;
	if (LV == 95)
		_HS.SPoint = 10000 + LV * 300 * _HS.Z_SPoint;
	if (LV == 96)
		_HS.SPoint = 20000+ LV * 400 * _HS.Z_SPoint;
	if (LV == 97)
		_HS.SPoint = 30000+ LV * 500 * _HS.Z_SPoint;
	if (LV == 98)
		_HS.SPoint = 40000+ LV * 600 * _HS.Z_SPoint;
	if (LV == 99)
		_HS.SPoint = 50000 + LV * 800 * _HS.Z_SPoint;
	if (LV == 100)
		_HS.SPoint = 100000+ LV * 1000 * _HS.Z_SPoint;

	_HS.HPoint = 100+ _HS.SPoint / _HS.Z_HPoint;
/*	if (LV < 20)
		_HS.Xiu = LV * 20;
	if (LV >= 20 && LV < 40)
		_HS.Xiu = 400 + 50 * (LV - 20);
	if (LV >= 40 && LV < 70)
		_HS.Xiu = 1000 + 300 * (LV - 40);
	if (LV >= 70 && LV < 90)
		_HS.Xiu = 10000 + 5000 * (LV - 70);
	if (LV >= 90 && LV < 95)
		_HS.Xiu = 100000 + 20000 * (LV - 90);
*/
	return _HS;
}
