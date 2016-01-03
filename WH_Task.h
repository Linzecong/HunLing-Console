class Task
{
 public:
    char Name[80];//任务名
    char Des[200];//任务描述
    int NTask;//接受所需任务完成
    int IsFinish;//是否完成
    int MB;//目标一
    int FMB;//目标一已完成
	int NKillHS;//要杀死的魂兽
	int NGetItem;//要获得的道具
	int NKillNPC;//要杀死的NPC
	int NTalkNPC;//要谈话的NPC
	int Reward;//任务奖励
    bool Init();
    bool Save();
    Task();

} RW[200];

Task::Task()
{
    IsFinish=0;
    Reward=0;
}

bool Task::Init()//读取
{
    ifstream opn(RW_DATAPATH,ios::binary);//读取数据
	opn.read((char *)&RW,sizeof(RW));//任务名
	opn.close();
	
    ifstream open(RW_SAVEPATH,ios::binary);//读取是否已完成
    for(int i=1;i<=199;i++)
        open.read((char *)&RW[i].IsFinish,sizeof(RW[i].IsFinish));
	open.close();
	RW[0].IsFinish=1;
	return 1;
}
	
bool Task::Save()//保存
{
	ofstream open(RW_SAVEPATH,ios::binary);
    for(int i=1;i<=199;i++)
        open.write((char *)&RW[i].IsFinish,sizeof(RW[i].IsFinish));
	open.close();
        return 1;
}








