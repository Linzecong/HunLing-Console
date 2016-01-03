class Map
{
 public:
    char Name[40];
    int IndexNPC[10];//人物
    char Des[80];//描述
    char BC[25];//所属国
    int IndexHS[10];//会出现的混兽
    int SMaxLV;//魂兽最高级别
    int SMinLV;//魂兽最低级别
    int NTask;
Map(){SMaxLV=-1;}
    bool Init();
}DT[50][50];

 bool Map::Init()//读取
{
    ifstream open(DT_DATAPATH, ios::binary);
		 open.read((char *)&DT, sizeof(DT));
	     open.close();
	return 1;
}








