class HunJi
{
  public:
	char Name[40];
	char Des[150];
	double HunLi;				// 使用所需魂力
	int XiaoGuo;				// 效果索引号
    int IsFind;                 //是否已发现
    bool Init();
    bool Save();
    HunJi();

}HJ[500];

HunJi::HunJi()
{
    IsFind=0;
}

bool HunJi::Init()//读取魂技数据
{
    ifstream oen(HJ_DATAPATH,ios::binary);//读取数据
	oen.read((char *)&HJ[1], sizeof(HunJi) * 498);
	oen.close();
    ifstream open(HJ_SAVEPATH,ios::binary);//读取是否已发现
	for(int i=1;i<=499;i++)
        open.read((char *)&HJ[i].IsFind,sizeof(IsFind));
	open.close();
	return 1;
}

bool HunJi::Save()//保存
{
    ofstream open(HJ_SAVEPATH,ios::binary);
    for(int i=1;i<=499;i++)
        open.write((char *)&HJ[i].IsFind,sizeof(IsFind));
	open.close();
    return 1;
}


