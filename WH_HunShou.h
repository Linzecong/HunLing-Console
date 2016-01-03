class HunShou:public RW_Date, public ZS_Date
{
  public:
	char Name[40];				// 名字
    char Des[150];              //描述
	int Level;					// 等级
	double Xiu;					// 修为
	int IsFind;					// 是否已发现
    int MyHJ[10];               //魂兽魂技
		int DItem[10];//会掉落的道具
    HunShou();
    bool Init();
    bool Save();
} HS[100];

HunShou::HunShou()
{
Level=0;
Xiu=0;
IsFind=0;
}

bool HunShou::Save()//保存
{
	ofstream opn(HS_SAVEPATH, ios::binary);
	for (int i = 1; i <= 99; i++)
		opn.write((char *)&HS[i].IsFind, sizeof(IsFind));
	opn.close();
	return 1;
}

bool HunShou::Init()//读取
{
    ifstream opn(HS_SAVEPATH, ios::binary);//读取是否已发现
	for (int i = 1; i <= 99; i++)
		opn.read((char *)&HS[i].IsFind, sizeof(IsFind));
	opn.close();

    ifstream open(HS_DATAPATH, ios::binary);//读取数据
	for (int i = 1; i <= 99; i++)
	{
		open.read((char *)&HS[i].Name, sizeof(Name));
		open.read((char *)&HS[i].Des, sizeof(Des));
		open.read((char *)&HS[i].Li, sizeof(Li));
		open.read((char *)&HS[i].Min, sizeof(Min));
		open.read((char *)&HS[i].M_Li, sizeof(M_Li));
		open.read((char *)&HS[i].M_Min, sizeof(M_Min));
		open.read((char *)&HS[i].APoint, sizeof(APoint));
		open.read((char *)&HS[i].DPoint, sizeof(DPoint));
		open.read((char *)&HS[i].SPoint, sizeof(SPoint));
		open.read((char *)&HS[i].HPoint, sizeof(HPoint));
		open.read((char *)&HS[i].ZL_APoint, sizeof(ZL_APoint));
		open.read((char *)&HS[i].ZL_DPoint, sizeof(ZL_DPoint));
		open.read((char *)&HS[i].ZM_APoint, sizeof(ZM_APoint));
		open.read((char *)&HS[i].ZM_DPoint, sizeof(ZM_DPoint));
		open.read((char *)&HS[i].Z_SPoint, sizeof(Z_SPoint));
		open.read((char *)&HS[i].Z_HPoint, sizeof(Z_HPoint));
		open.read((char *)&HS[i].K_Bing, sizeof(K_Bing));
		open.read((char *)&HS[i].K_Huo, sizeof(K_Huo));
		open.read((char *)&HS[i].K_Dian, sizeof(K_Dian));
		open.read((char *)&HS[i].K_Tu, sizeof(K_Tu));
		open.read((char *)&HS[i].K_Guang, sizeof(K_Guang));
		open.read((char *)&HS[i].K_An, sizeof(K_An));
		open.read((char *)&HS[i].MyHJ[1], sizeof(MyHJ[1]) * 9);
		open.read((char *)&HS[i].DItem, sizeof(DItem));
	}
	open.close();
	return 1;

}

HunShou CreateHS(HunShou _HS, int LV)	// 生成魂兽
{
	_HS.Level = LV;
	_HS.Li = 15+ _HS.M_Li * LV;
	_HS.Min = 15+ _HS.M_Min * LV;
	_HS.APoint = 50+_HS.Li /10* (1+_HS.ZL_APoint/5)*LV+ _HS.Min/10 * (1+_HS.ZM_APoint/5)*LV;
	_HS.DPoint = 50+_HS.Li/10 * (1+_HS.ZL_DPoint/5)*LV+ _HS.Min /10* (1+_HS.ZM_DPoint/5)*LV;
	if (LV < 30)
		_HS.SPoint = 200+ LV * 50 * _HS.Z_SPoint;
	if (LV >= 30 && LV < 70)
		_HS.SPoint = 1500 + LV * 100 * _HS.Z_SPoint;
	if (LV >= 70 && LV < 90)
		_HS.SPoint = 3000 + LV * 150 * _HS.Z_SPoint;
	if (LV >= 90 && LV <= 94)
		_HS.SPoint = 10000 + LV * 200 * _HS.Z_SPoint;
	if (LV == 95)
		_HS.SPoint = 20000+ LV * 300 * _HS.Z_SPoint;
	if (LV == 96)
		_HS.SPoint = 30000 + LV * 400 * _HS.Z_SPoint;
	if (LV == 97)
		_HS.SPoint =40000+ LV * 500 * _HS.Z_SPoint;
	if (LV == 98)
		_HS.SPoint = 50000+ LV * 600 * _HS.Z_SPoint;
	if (LV == 99)
		_HS.SPoint = 100000+ LV * 800 * _HS.Z_SPoint;
	if (LV == 100)
		_HS.SPoint = 100000+ LV * 1000 * _HS.Z_SPoint;
	_HS.HPoint = _HS.HPoint + _HS.SPoint /_HS.Z_HPoint;
	if (LV < 20)
		_HS.Xiu = LV * 20;
	if (LV >= 20 && LV < 40)
		_HS.Xiu = 400 + 50 * (LV - 20);
	if (LV >= 40 && LV < 70)
		_HS.Xiu = 1000 + 300 * (LV - 40);
	if (LV >= 70 && LV < 90)
		_HS.Xiu = 10000 + 5000 * (LV - 70);
	if (LV >= 90 && LV < 95)
		_HS.Xiu = 100000 + 20000 * (LV - 90);
	return _HS;
}