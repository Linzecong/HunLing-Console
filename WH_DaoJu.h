class DaoJu
{
 public:
    char Name[40];//名字
    char Des[150];//描述
    int Count;//计数
    int XiaoGuo;//效果
    double Cost;//购买所需
    double Sell;//能卖多少
    DaoJu();
    bool Init();
}Item[200];

bool DaoJu::Init()//读取道具数据
{
	ifstream open(DJ_DATAPATH,ios::binary);
	open.read((char *)&Item,sizeof(Item));
	open.close();
	return 1;
}

DaoJu::DaoJu()
{
    Count=0;
    XiaoGuo=0;
}





