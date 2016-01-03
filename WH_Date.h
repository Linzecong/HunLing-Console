//Z开头的为指数
//M开头的为每级增加
//K开头的为克性
//D开头的为抗性
class ZS_Date
{
 public:
	double ZL_APoint;			// 力量攻击力
	double ZL_DPoint;			// 力量防御力
    double ZM_APoint;           //敏捷攻击力
    double ZM_DPoint;           //敏捷防御力
	double Z_SPoint;			// 生命力
	double Z_HPoint;			// 魂力
	double M_Li;
	double M_Min;
};

class K_Date
{
 public:    double K_Bing;//冰
    double K_Huo;//火
    double K_Dian;//电
    double K_Tu;//土
    double K_Guang;//光
    double K_An;//暗
};


class RW_Date :public K_Date
{
 public:
    double Li;
    double Min;
    double APoint;//攻击力#00ff00
    double SPoint;//生命力
    double HPoint;//魂力
    double DPoint;//防御力
};

class Z_Date //增加的数据
{
 public:
    double Xiu;//修为，年限
    double Z_Li;
    double Z_Min;
    double Z_Hun;//魂力
    double Z_Sheng;//生命
    double Z_Xiu;//修为
    double Z_KBing;//克
    double Z_KHuo;
    double Z_KDian;
    double Z_KTu;
    double Z_KGuang;
    double Z_KAn;
};


	double GetRand(int start, int end)
	{
		srand(time(NULL));
		double n = rand() % (end +1- start) + start;
		return n;
	}

    void clrscr()
    {
        system("cls");
    }
