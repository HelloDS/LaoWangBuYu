#include "AllRobot.h" 
#include "GameData.h" 
#include "GameScene.h"
#include "GameBegin.h"

int AllRobot::myrank = 0;
bool  AllRobot::shanshan = false;
int  AllRobot::readnetHuafeiQuan[4] = {0};
int  AllRobot::readnetLeiji[4] = {0};
int AllRobot:: iRobotWinNum = 100;

AllRobot::AllRobot(void)
{
}


AllRobot::~AllRobot(void)
{


}

bool MyStruct::operator >(const MyStruct& pinfo) const
{
	return money>pinfo.money;
}
bool MyStruct::operator<(const MyStruct& pinfo) const
{
	return money<pinfo.money;
}


void AllRobot::initplayer(int iPlayerNum,int itype,string SelfName)
{
	iTime = 0;
	int iRobotBase[20] = {1,2,5,10,20,50,80,100,200,500,1000,2000,3000,4000,5000,6000,7000,8000,9000,10000};
	myrank = 0;
	shanshan = false;
 

	iRandomTime[0] = 50+CCRANDOM_0_1()*50;
	iRandomTime[1] = 100+CCRANDOM_0_1()*50;
	iRandomTime[2] = 150+CCRANDOM_0_1()*50;
	iRandomTime[3] = 200+CCRANDOM_0_1()*30;
	iRandomTime[4] = 230+CCRANDOM_0_1()*30;
	iRandomTime[5] = 260+CCRANDOM_0_1()*30;
  //  int iTempLeiJi = GameBegin::getFileData("wflei.txt");
 //   int iTempHuaFeiQuan = GameBegin::getFileData("wfsound.txt");
    
    if(itype == 0)
    {
        	int iFourTypeRobot[4] = {0};
       
            iFourTypeRobot[0] =iPlayerNum*0.1;
            iFourTypeRobot[1] =iFourTypeRobot[0]+iPlayerNum*0.2;
            iFourTypeRobot[2] =iFourTypeRobot[1]+iPlayerNum*0.6;
            iFourTypeRobot[3] =iPlayerNum +1;
            for(int i =0; i< iFourTypeRobot[0]; i++)
            {
                MyStruct TempSdf;
                
                TempSdf.ctype = 0;
                TempSdf.shootnum = 3+CCRANDOM_0_1()*3.9;
                if(CCRANDOM_0_1()*100 < 50)
                {
                    TempSdf.base = 85;
                }
                else
                {
                    TempSdf.base = 75;
                }
                
                int TempName = 1+((CCRANDOM_0_1()*500 )-1);
                char tmp_jfb[50];
                sprintf(tmp_jfb,"robotNName%d", TempName);
                TempSdf.name=GAME_DATA_STRING(tmp_jfb);
                TempSdf.money = 0;
                TempSdf.wfcool = false;
                robot.push_back(TempSdf);  
            }
            for(int i =iFourTypeRobot[0]; i< iFourTypeRobot[1]; i++)
            {
                MyStruct TempSdf; 
                TempSdf.ctype = 1;
                TempSdf.shootnum = 3+CCRANDOM_0_1()*3.9;
                if(CCRANDOM_0_1()*100 < 50)
                {
                    TempSdf.base = 65;
                }
                else
                {
                    TempSdf.base = 50;
                    
                }
                
                int TempName = 1+((CCRANDOM_0_1()*500 )-1);
                char tmp_jfb[50];
                sprintf(tmp_jfb,"robotNName%d", TempName);
                TempSdf.name=GAME_DATA_STRING(tmp_jfb);
                TempSdf.money = 0;
                TempSdf.wfcool = false;
                robot.push_back(TempSdf);
                

            }
            for(int i =iFourTypeRobot[1]; i< iFourTypeRobot[2]; i++)
            {
                MyStruct TempSdf;
                
                    TempSdf.shootnum = 1+CCRANDOM_0_1()*3.9;
                
                
                if(CCRANDOM_0_1()*100 < 50)
                {
                    TempSdf.base = 30;
                }
                else
                {
                    TempSdf.base = 10;
                }
                
                TempSdf.ctype = 2;
                
                int TempName = 1+((CCRANDOM_0_1()*500 )-1);
                char tmp_jfb[50];
                sprintf(tmp_jfb,"robotNName%d", TempName);
                TempSdf.name=GAME_DATA_STRING(tmp_jfb);
                TempSdf.money = 0;
                TempSdf.wfcool = false;
                robot.push_back(TempSdf);
                

            }
            for(int i =iFourTypeRobot[2]; i< iFourTypeRobot[3]; i++)
            {
                MyStruct TempSdf;

                TempSdf.shootnum = 1+((CCRANDOM_0_1()*3)-0.000001);
                TempSdf.ctype = 3;
                TempSdf.base = CCRANDOM_0_1()*4;
                TempSdf.base =  iRobotBase[TempSdf.base];
                
                int TempName = 1+((CCRANDOM_0_1()*500 )-1);
                char tmp_jfb[50];
                sprintf(tmp_jfb,"robotNName%d", TempName);
                TempSdf.name=GAME_DATA_STRING(tmp_jfb);
                TempSdf.money = 0;
                TempSdf.wfcool = false;
                robot.push_back(TempSdf);
            }
        
    }
    else if(itype == 1)
    {
        
        int iFourTypeRobot[4] = {0};
       
            iFourTypeRobot[0] =iPlayerNum*0.1;
            iFourTypeRobot[1] =iFourTypeRobot[0]+iPlayerNum*0.2;
            iFourTypeRobot[2] =iFourTypeRobot[1]+iPlayerNum*0.6;
            iFourTypeRobot[3] =iPlayerNum +1;
            for(int i =0; i< iFourTypeRobot[0]; i++)
            {
                MyStruct TempSdf;
                
                TempSdf.shootnum = 3+CCRANDOM_0_1()*3.99;
                TempSdf.ctype = 0;
                if(CCRANDOM_0_1()*100 < 50)
                {
                    TempSdf.base = 450;
                }
                else
                {
                    TempSdf.base = 400;
                }
                int TempName = 1+((CCRANDOM_0_1()*500 )-1);
                char tmp_jfb[50];
                sprintf(tmp_jfb,"robotNName%d", TempName);
                TempSdf.name=GAME_DATA_STRING(tmp_jfb);
                TempSdf.money = 0;
                TempSdf.wfcool = false;
                robot.push_back(TempSdf);
                
            }
            for(int i =iFourTypeRobot[0]; i< iFourTypeRobot[1]; i++)
            {
                MyStruct TempSdf;
                
                TempSdf.shootnum = 3+CCRANDOM_0_1()*3.99;
                TempSdf.ctype = 1;
                
                if(CCRANDOM_0_1()*100 < 50)
                {
                    TempSdf.base = 300;
                }
                else
                {
                    TempSdf.base = 200;
                }
                int TempName = 1+((CCRANDOM_0_1()*500 )-1);
                char tmp_jfb[50];
                sprintf(tmp_jfb,"robotNName%d", TempName);
                TempSdf.name=GAME_DATA_STRING(tmp_jfb);
                TempSdf.money = 0;
                TempSdf.wfcool = false;
                robot.push_back(TempSdf);
                
            }
            for(int i =iFourTypeRobot[1]; i< iFourTypeRobot[2]; i++)
            {
                MyStruct TempSdf;
                
                TempSdf.shootnum  = 1+CCRANDOM_0_1()*5;
                TempSdf.ctype = 2;
                
                int iTempRandom = CCRANDOM_0_1()*100;
                if( iTempRandom < 30)
                {
                    TempSdf.base = 150;
                }
                else if(iTempRandom < 60)
                {
                    TempSdf.base = 100;
                }
                else
                {
                    TempSdf.base = 50;
                }
                int TempName = 1+((CCRANDOM_0_1()*500 )-1);
                char tmp_jfb[50];
                sprintf(tmp_jfb,"robotNName%d", TempName);
                TempSdf.name=GAME_DATA_STRING(tmp_jfb);
                TempSdf.money = 0;
                TempSdf.wfcool = false;
                robot.push_back(TempSdf);
                
            }
            for(int i =iFourTypeRobot[2]; i< iFourTypeRobot[3]; i++)
            {
                MyStruct TempSdf;
                
                TempSdf.shootnum = 1+((CCRANDOM_0_1()*3)-0.000001);
                
                TempSdf.ctype = 3;
                if(CCRANDOM_0_1()*100 < 50)
                {
                    TempSdf.base = 50;
                }
                else
                {
                    TempSdf.base = 100;
                }
                
                int TempName = 1+((CCRANDOM_0_1()*500 )-1);
                char tmp_jfb[50];
                sprintf(tmp_jfb,"robotNName%d", TempName);
                TempSdf.name=GAME_DATA_STRING(tmp_jfb);
                TempSdf.money = 0;
                TempSdf.wfcool = false;
                robot.push_back(TempSdf);
                
            }
        
    }
    else if(itype == 2)
    {
        int iFourTypeRobot[4] = {0};
        
            iFourTypeRobot[0] =iPlayerNum*0.1;
            iFourTypeRobot[1] =iFourTypeRobot[0]+iPlayerNum*0.2;
            iFourTypeRobot[2] =iFourTypeRobot[1]+iPlayerNum*0.6;
            iFourTypeRobot[3] =iPlayerNum +1;
            for(int i =0; i< iFourTypeRobot[0]; i++)
            {
                MyStruct TempSdf;
                
                TempSdf.shootnum = 3+CCRANDOM_0_1()*3.99;
                TempSdf.ctype = 0;
                if(CCRANDOM_0_1()*100 < 50)
                {
                    TempSdf.base = 7000;
                }
                else
                {
                    TempSdf.base = 6500;
                }
                
                int TempName = 1+((CCRANDOM_0_1()*500 )-1);
                char tmp_jfb[50];
                sprintf(tmp_jfb,"robotNName%d", TempName);
                TempSdf.name=GAME_DATA_STRING(tmp_jfb);
                TempSdf.money = 0;
                TempSdf.wfcool = false;
                robot.push_back(TempSdf);
                
            }
            for(int i =iFourTypeRobot[0]; i< iFourTypeRobot[1]; i++)
            {
                MyStruct TempSdf;
                
                TempSdf.shootnum = 3+CCRANDOM_0_1()*3.99;
                TempSdf.ctype = 1;
                TempSdf.base = 14+CCRANDOM_0_1()*3;
                TempSdf.base =  iRobotBase[TempSdf.base];
                
                int TempName = 1+((CCRANDOM_0_1()*500 )-1);
                char tmp_jfb[50];
                sprintf(tmp_jfb,"robotNName%d", TempName);
                TempSdf.name=GAME_DATA_STRING(tmp_jfb);
                TempSdf.money = 0;
                TempSdf.wfcool = false;
                robot.push_back(TempSdf);
            
            }
            for(int i =iFourTypeRobot[1]; i< iFourTypeRobot[2]; i++)
            {
                MyStruct TempSdf;
                
                TempSdf.shootnum =  1+CCRANDOM_0_1()*6;
                
                TempSdf.ctype = 2;
                TempSdf.base = 9+CCRANDOM_0_1()*7;
                TempSdf.base =  iRobotBase[TempSdf.base];
                
                int TempName = 1+((CCRANDOM_0_1()*500 )-1);
                char tmp_jfb[50];
                sprintf(tmp_jfb,"robotNName%d", TempName);
                TempSdf.name=GAME_DATA_STRING(tmp_jfb);
                TempSdf.money = 0;
                TempSdf.wfcool = false;
                robot.push_back(TempSdf);
            }
            for(int i =iFourTypeRobot[2]; i< iFourTypeRobot[3]; i++)
            {
                MyStruct TempSdf;
                
                TempSdf.shootnum =  1+CCRANDOM_0_1()*6;
                
                TempSdf.ctype = 2;
                TempSdf.base = 9+CCRANDOM_0_1()*7;
                TempSdf.base =  iRobotBase[TempSdf.base];
                
                int TempName = 1+((CCRANDOM_0_1()*500 )-1);
                char tmp_jfb[50];
                sprintf(tmp_jfb,"robotNName%d", TempName);
                TempSdf.name=GAME_DATA_STRING(tmp_jfb);
                TempSdf.money = 0;
                TempSdf.wfcool = false;
                robot.push_back(TempSdf);
            }
        
    }
    else if(itype == 3)
    {
        
        
        
        int iFourTypeRobot[4] = {0};
        
            iFourTypeRobot[0] =iPlayerNum*0.1;
            iFourTypeRobot[1] =iFourTypeRobot[0]+iPlayerNum*0.2;
            iFourTypeRobot[2] =iFourTypeRobot[1]+iPlayerNum*0.6;
            iFourTypeRobot[3] =iPlayerNum +1;
            for(int i =0; i< iFourTypeRobot[0]; i++)
            {
                MyStruct TempSdf;
                
                TempSdf.shootnum = 3+CCRANDOM_0_1()*3.99;
                TempSdf.ctype = 0;
                if(CCRANDOM_0_1()*100 < 50)
                {
                    TempSdf.base = 9500;
                }
                else
                {
                    TempSdf.base = 9000;
                }
                
                int TempName = 1+((CCRANDOM_0_1()*500 )-1);
                char tmp_jfb[50];
                sprintf(tmp_jfb,"robotNName%d", TempName);
                TempSdf.name=GAME_DATA_STRING(tmp_jfb);
                TempSdf.money = 0;
                TempSdf.wfcool = false;
                robot.push_back(TempSdf);
                
                sprintf(tmp_jfb,"robotNName%d", TempName);
                sprintf(tmp_jfb,"i = %d", i);
            }
            for(int i =iFourTypeRobot[0]; i< iFourTypeRobot[1]; i++)
            {
                MyStruct TempSdf;
                
                TempSdf.shootnum = 3+CCRANDOM_0_1()*3.99;
                TempSdf.ctype = 1;
                if(CCRANDOM_0_1()*100 < 50)
                {
                    TempSdf.base = 8000;
                }
                else
                {
                    TempSdf.base = 7000;
                }
                
                int TempName = 1+((CCRANDOM_0_1()*500 )-1);
                char tmp_jfb[50];
                sprintf(tmp_jfb,"robotNName%d", TempName);
                TempSdf.name=GAME_DATA_STRING(tmp_jfb);
                TempSdf.money = 0;
                TempSdf.wfcool = false;
                robot.push_back(TempSdf);
            }
            for(int i =iFourTypeRobot[1]; i< iFourTypeRobot[2]; i++)
            {
                MyStruct TempSdf;
                
                TempSdf.shootnum =  1+CCRANDOM_0_1()*6;
                
                TempSdf.ctype = 2;
                TempSdf.base = 14+CCRANDOM_0_1()*5;
                TempSdf.base =  iRobotBase[TempSdf.base];
                
                int TempName = 1+((CCRANDOM_0_1()*500 )-1);
                char tmp_jfb[50];
                sprintf(tmp_jfb,"robotNName%d", TempName);
                TempSdf.name=GAME_DATA_STRING(tmp_jfb);
                TempSdf.money = 0;
                TempSdf.wfcool = false;
                robot.push_back(TempSdf);
            }
            for(int i =iFourTypeRobot[2]; i< iFourTypeRobot[3]; i++)
            {
                MyStruct TempSdf;
                TempSdf.shootnum =  1+CCRANDOM_0_1()*6;
                
                TempSdf.ctype = 2;
                TempSdf.base = 14+CCRANDOM_0_1()*5;
                TempSdf.base =  iRobotBase[TempSdf.base];
                
                int TempName = 1+((CCRANDOM_0_1()*500 )-1);
                char tmp_jfb[50];
                sprintf(tmp_jfb,"robotNName%d", TempName);
                TempSdf.name=GAME_DATA_STRING(tmp_jfb);
                TempSdf.money = 0;
                TempSdf.wfcool = false;
                robot.push_back(TempSdf);
            }
        
    }
    else if(itype == 4)
    {
        for(int i =0; i< iPlayerNum+1; i++)
        {
            MyStruct TempSdf;
            TempSdf.shootnum = 1+CCRANDOM_0_1()*2.9;
            TempSdf.ctype = 2;
            
            if(CCRANDOM_0_1() * 100 < 50)
            TempSdf.base = 2;
            else
                TempSdf.base = 5;
            
            int TempName = 1+((CCRANDOM_0_1()*500 )-1);
            char tmp_jfb[50];
            sprintf(tmp_jfb,"robotNName%d", TempName);
            TempSdf.name=GAME_DATA_STRING(tmp_jfb);
            TempSdf.money = 0;
            TempSdf.wfcool = false;
            robot.push_back(TempSdf);
        }
    }
	   
	robot[robot.size()-1].wfcool = true;
	robot[robot.size()-1].name = SelfName;

}

/*

using namespace std;
static int base[22] = {2,2,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,10,20,30,45,40};

static float shootboom[22] = {0.4844,0.4844,0.4844,0.4844,
0.322,0.322,0.242,0.242,
0.193,0.193,0.161,0.161,
0.138,0.138,0.121,0.121,
0.107,0.096,0.048,0.032,0.027,0.024};

static float chuxian[22] = {10178,10178,10178,10178,
5089,5089,5089,5089,5089,5089,5089,5089,
2544,2544,2544,2544,2544,1272,1272,1272,
1017,1017};
int main()
{
int end  = 0;
int paobase = 500; 
float chuxianwf [22];
chuxianwf[0] = 10178;
for(int i = 1 ; i<22; i++)
{
chuxianwf[i] = chuxian[i]+chuxian[i-1];
}

int fishindex[20];
for(int i=0; i< 300; i++)
{
srand(time(NULL));

for(int j=0; j<20; j++)
{ 
float temprandom = rand()%4;
}


}

printf("dfe");
system("pause");
}
*/

bool copare(  MyStruct  &pfirst,MyStruct &psecond) //如果该vector存入的是对象的话该函数参数须是

{                                                    // 对象的引用，而不该是指针
	return pfirst.money  >= psecond.money;
}



void AllRobot::sortandshoot(long long selfmoney)
{
	iTime ++;
	if((iTime > iRandomTime[0] && iTime < iRandomTime[0] +5  )||
		(iTime > iRandomTime[1] && iTime < iRandomTime[1] +5  )||
		(iTime > iRandomTime[2] && iTime < iRandomTime[2] +5  )||
		(iTime > iRandomTime[3] && iTime < iRandomTime[3] +5  )||
		(iTime > iRandomTime[4] && iTime < iRandomTime[4] +5  )||
		(iTime > iRandomTime[5] && iTime < iRandomTime[5] +5  ))
	{

		int base[4] = {100,150,300,300};
		float basefloat[4] = {0.969,0.646,0.100,0.080}; 
		for(int i =0; i< robot.size(); i++)
		{
			if(robot[i].wfcool == true)
			{
				robot[i].money = selfmoney;
				continue;
			}
			for(int j=0; j<  robot[i].shootnum; j++)
			{ 
				float temprandom = CCRANDOM_0_1()*12;
				if(temprandom <5)
				{ 
					if(CCRANDOM_0_1()*100 < 0.969)
					{
						robot[i].money  += robot[i].base*100;
					}
				}
				else if(temprandom <10)
				{ 
					if(CCRANDOM_0_1()*100 < 0.646)
					{
						robot[i].money  += robot[i].base*150;
					}
				}
				else if(temprandom < 11)
				{ 
					if(CCRANDOM_0_1()*100 < 0.100)
					{
						int iTempRand = 300+(CCRANDOM_0_1()*699);
						robot[i].money  += robot[i].base*iTempRand;
					}
				}
				else
				{ 
					if(CCRANDOM_0_1()*100 < 0.080)
					{
						int iTempRand = 300+(CCRANDOM_0_1()*699);
						robot[i].money  += robot[i].base*iTempRand;
					}
				} 
			} 
		}
	}
	else
	{
		/*float fishcome[22] = {10.18,10.18,10.18,10.18,
			5.09,5.09,5.09,5.09,5.09,5.09,5.09,
			2.51,2.51,2.51,2.51,2.51,2.51,
			1.27,1.27,1.27,1.02,1.02};
			*/


		float shootboom[22] = {0.4844,0.4844,0.4844,0.4844,
			0.322,0.322,0.242,0.242,
			0.193,0.193,0.161,0.161,
			0.138,0.138,0.121,0.121,
			0.107,0.096,0.048,0.032,0.027,0.024};
		 int base[22] = {2,2,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,10,20,30,45,40};

		int iIndex = 0;
		float  shootgailv = 0;
		for(int i =0; i< robot.size(); i++)
		{
			if(robot[i].wfcool == true)
			{
				robot[i].money = selfmoney;
				continue;
			}
			for(int j=0; j< robot[i].shootnum; j++)
			{
				iIndex = ((CCRANDOM_0_1()*22)-0.00001);				
				shootgailv = CCRANDOM_0_1()*1;
				if(shootgailv < shootboom[iIndex] )
				{
					robot[i].money +=  robot[i].base*base[iIndex];
				}
			}
		}
		/*float fishcomerandom[22];
		fishcomerandom[0] = 10.18;
		for(int i =1; i< 22; i++)
		{
			fishcomerandom[i] = fishcome[i]+fishcomerandom[i-1];
		}*/
	}

	sort(robot.begin(),robot.end(),greater<MyStruct>()); 

	 

	 
	for(int i=0; i<3; i++)
	{
		char tmp[40]; 
		sprintf(tmp,"%lld",robot[i].money );
		GameScene::bs_jfb_l[i]->setString(tmp);
		GameScene::bs_jfb_n[i]->setString(robot[i].name);
	}
}


void AllRobot::setRobotWin()
{
    
    for(int i=0; i< iRobotWinNum; i++)
    {
        robot[i].shootnum = 10+CCRANDOM_0_1()*3;
        robot[i].base = robot[i].base + robot[i].base/2;
    }

}
int AllRobot::getmyrank( )
{
	for(int i=0; i<robot.size(); i++)
	{
		if(robot[i].wfcool == true)
		{ 
			myrank = i+1;
			return i+1;
		}
		
	}
}