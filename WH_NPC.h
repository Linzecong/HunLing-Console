class Msg
{
 public:
 	int Task;//接受哪个任务后可以说
 	char Message[200];

    bool Init();
}msg[800];

bool Msg::Init()//读取消息
{
	ifstream oen(MSG_DATAPATH,ios::binary);
        oen.read((char *)&msg,sizeof(msg));		
	oen.close();
    return true;
}
	
class NPC
{
 public:
    char Name[40];
    char Des[200];
    int NPCRW[5];//任务列表
    int wuhun[2];//魂灵/等级
    int CanATK;//能否被攻击
    int IndexMsg[10];//会说的话
    int CanShow;//否已死亡或不能显示
    bool Init();
    bool Save();

}Npc[100];

bool NPC::Init()//读取数据
{
 	ifstream open(NPC_DATAPATH,ios::binary);
	open.read((char *)&Npc,sizeof(Npc));
	open.close();
 	return 1;
}

bool NPC::Save()
{
    ofstream open(NPC_DATAPATH,ios::binary);
	open.write((char *)&Npc,sizeof(Npc));
    open.close();
    return 1;
}
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 