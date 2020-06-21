#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
typedef struct data{//结构体 
	int unum;//用户的编号，0至99 
	char id[10];//用户id 
	char password[10];//用户密码 
	int fnum;//用户所选的精灵编号（1,2,3），如果为0，说明用户没选精灵 
	int lv;//用户精灵等级
}USER;



//全局变量
int count=0;//服务器当前人数 
USER u[100];//服务器仅可以承载100个玩家
int now;//玩家登录后保存当前玩家的编号（对应着unum） 




//下面是函数声明
void welcome1();//欢迎话语
void welcome2();//注册或登录选择提示 
int load();//加载TXT文件至内存中 
int enroll();//注册函数
int login();//登录函数，若返回值为100，则游戏结束
void loginWelcome();//登录成功后的闪烁庆祝
int changePassword();//更改密码
int checkFairy();//检测用户选择的精灵
void mainWel();//显示主界面选择提示
int name(int a);//显示用户所选精灵的名称
int nature(int a);//显示精灵属性 
int hp(int a);//用户所选精灵的血量
int at(int a);//用户所选精灵的攻击力
int de(int a);//用户所选精灵的防御力
int showFairyQuality();//显示精灵名称，等级，血量，攻击，防御
int mission();//进行任务
void quickSort(struct data u[],int left,int right);//快速排序 
void showRanking();//仅显示排位天梯
int upk();//玩家pk 
int save();//保存当前数据到TXT文件的函数



int main(){//主函数
	//游戏开始前.................
	welcome1();
	load();
	welcome2();
	int choice;
	scanf("%d",&choice);
	if(choice!=2){//不选2就是登录
		now=login();//加载登录函数,并把全局变量now设置为当前用户编号
		if(now==100){//如果用户认证失败
			return 0;//那么结束游戏
		}else{//用户登录成功后
			loginWelcome();//显示闪瞎36k氪金狗眼的登录特效
		}
	}else{//选2就是注册,并把全局变量now设置为当前用户编号
		now=enroll();//用户注册
		loginWelcome();//注册成功后，显示闪瞎36k氪金狗眼的特效
		printf("注册成功！已自动登录。\n\n");
	}
	
	
	system("cls");
	//正式开始游戏............. 
	checkFairy();system("cls");
	while(1){
		mainWel();
		scanf("%d",&choice);
		switch(choice){
			case 1:system("color 01");system("cls");showFairyQuality();break;
			case 2:system("color 04");system("cls");mission();break;
			case 3:system("color 06");system("cls");upk();break;
			case 4:system("color 0a");system("cls");showRanking();break;
			case 5:system("color 07");system("cls");changePassword();break;
			default :save();return 0;
		} 
	} 

	
	
	return 0;
}
 




//下面是函数实现部分


//开始游戏之前


void welcome1(){//欢迎话语1 
	system("color 0a");//界面背景黑色，字体绿色
	printf("\n\n******************精灵物语******************\n\n\n");
}

void welcome2(){//欢迎话语2
	printf("**********     **********\n");
	printf("* 1 登录 *     * 2 注册 *\n");
	printf("**********     **********\n");
}


int load(){//加载TXT文件至内存中
	FILE *fp;
	int i=0;
	if((fp=fopen ("data.txt","r"))==NULL){
		fp=fopen("data.txt","w+");
	//	printf("未找到信息文件，已新建新的信息文件\n");
	}
	//读文件，数据存入数组USER u[100]中
	while(!feof(fp))//函数feof()用于检查是否到达文件末尾，到达时返回非0值
	{
		fscanf(fp,"%10d",&u[i].unum);
		fscanf(fp,"%10s",u[i].id);
		fscanf(fp,"%10s",u[i].password);
		fscanf(fp,"%10d",&u[i].fnum);
		fscanf(fp,"%10d",&u[i].lv);
		i++;
		count++;
	}
	count--;
   fclose (fp);//关闭文件
   printf("全服%d位玩家与你同在。\n\n\n\n",count);
   return 0; 
} 


int enroll(){//注册函数
	system("color 06");//界面背景黑色，字体黄色
	int i;
	if(count<100){
		i=count;
		u[i].unum=i;
		printf("请输入账号（昵称）：");
		char s[10];//暂时保存用户的账号 
		scanf("%s",&s);
		printf("%s",u[i].id);
		for(i=0;i<count;i++){//遍历用户 
			while(!strcmp(u[i].id,s)){//不允许相同的用户id 
				printf("账号（昵称）已存在，请重新输入：");
				i=0;
				scanf("%s",&s);
			}
	    }
		strcpy(u[i].id,s);//把字符串s内容传给u[i].id
		printf("请输入密码：");
		scanf("%s",&u[i].password);
		count++;//用户个数加一 
	}else{
		printf("服务器爆满\n");
	}
	return i;
} 



int login(){//登录函数 
	system("color 04");//界面背景黑色，字体红色 
	printf("请输入账号（昵称）：");
	char s[10];
	scanf("%s",&s);
	int i;
	for(i=0;i<count;i++){
		if(!strcmp(u[i].id,s)){
			printf("请输入密码：");
			scanf("%s",&s);
			if(!strcmp(u[i].password,s)){
				printf("登陆成功\n");
				return  i;
			}else{
				int j;
				for(j=0;j<3;j++){
					printf("密码错误，您还有%d次尝试机会，请重新输入密码：",3-j);
					scanf("%s",&s);
					if(!strcmp(u[i].password,s)){
						printf("登陆成功\n");
						return i;
					}
					if(j==2){
						printf("密码尝试次数达到上限，账户进入保护模式！重启游戏以解除。");
						return 100; 
					}
				}
			}
			
		}
		if(i==count-1){//到达最后还没有 
			printf("账号（昵称）错误，");
	    }
	}
	login();//递归，调用函数本身。我吐血编出来的 
}


void loginWelcome(){//闪瞎36k氪金狗眼的登录特效 
	int i;
	for(i=0;i<5;i++){
		system("color 2a");
		system("color 3a");
		system("color ba");
	}
	system("color 0a");
} 




int changePassword(){//修改密码 
	printf("\n修改密码？\n");
	printf("1 是      2 否\n");
	int choice;
	scanf("%d",&choice);
	if(choice==1){
		printf("请输入新密码：");
		scanf("%s",u[now].password);
		printf("密码修改成功！\n");
	}
	return 0;
}



//开始游戏 


int checkFairy(){//检测用户精灵 
	if(u[now].fnum==0){
		u[now].lv=1;//初始化精灵等级为1级 
		printf("精灵分三种属性：水 火 木 \n其中水克火，火克木，木克水。\n");
		printf("目前有3种精灵供您选择。\n\n");
		printf("1 ：水中灵\n");
		printf("水中灵是水属性精灵，具有极高的血量天赋。可在战斗中消耗敌人。\n\n");
		printf("2 ：火灵儿\n");
		printf("火灵儿是火属性精灵，具有极高的攻击天赋。对敌人造成爆炸伤害。\n\n");
		printf("3 ：花仙子\n");
		printf("花仙子是水属性精灵，具有极高的防御天赋。受到的伤害大大减少。\n\n");
		printf("请输入您选择的精灵编号：");
		scanf("%d",&u[now].fnum);
		while(u[now].fnum!=1&&u[now].fnum!=2&&u[now].fnum!=3){
			printf("您输入有误，请重新输入：");
			scanf("%d",&u[now].fnum);
		}
		printf("恭喜您拥有了它！\n");
	}
	return 0;
}



void mainWel(){
	printf("\n\n");
	printf("--------------------       --------------------       --------------------\n");
	printf("-  1   精灵属性    -       -  2   进行任务    -       -  3   玩家切磋    -\n");
	printf("--------------------       --------------------       --------------------\n");
	printf("\n");
	printf("--------------------       --------------------       --------------------\n");
	printf("-  4   排位天梯    -       -  5   修改密码    -       -  6   保存退出    -\n");
	printf("--------------------       --------------------       --------------------\n");
	printf("\n\n请输入功能标号：");
}


int name(int a){//精灵名称
	if(u[a].lv<60){
		if(u[a].fnum==1)printf("水中灵");
	    if(u[a].fnum==2)printf("火灵儿");
	    if(u[a].fnum==3)printf("花仙子");
	}else{
		if(u[a].fnum==1)printf("冬青海神");
		if(u[a].fnum==2)printf("炎魔之王");
		if(u[a].fnum==3)printf("魔域花仙");
	}
	
	return 0;
}

int nature(int a){//精灵属性 
	if(u[a].fnum==1)printf("水");
	if(u[a].fnum==2)printf("火");
	if(u[a].fnum==3)printf("木");
	return 0;
} 


int hp(int a){//精灵血量 
	if(u[a].fnum==1){return u[a].lv*12;}
	if(u[a].fnum==2){return u[a].lv*10;}
	if(u[a].fnum==3){return u[a].lv*10;}
}


int at(int a){//精灵攻击 
	if(u[a].fnum==1){return u[a].lv*5;}
	if(u[a].fnum==2){return u[a].lv*6;}
	if(u[a].fnum==3){return u[a].lv*5;}
}


int de(int a){//精灵防御 
	if(u[a].fnum==1){return u[a].lv;}
	if(u[a].fnum==2){return u[a].lv;}
	if(u[a].fnum==3){return u[a].lv*2;}
}


int showFairyQuality(){
	printf("\n精灵：");name(now);
	printf("\n属性：");nature(now);
	printf("\n等级：%d",u[now].lv);
	printf("\n血量：%d",hp(now));
	printf("\n攻击：%d",at(now));
	printf("\n防御：%d",de(now));
	return 0;
}


int mission(){
	
	printf("\n所有怪物属性随机！\n精灵等级达到60级即可进化。\n\n");
	int i;
	printf("0：返回。\n");
	for(i=1;i<=4;i++){
		printf("%d：%d级怪物，击败可升%d级。\n",i,i,i);
	}
	printf("5：5级远古巨兽，击败可升5级。\n");
	for(i=6;i<=9;i++){
		printf("%d：%d级怪物，击败可升%d级。\n",i,i,i);
	}
	printf("10：10级远古巨兽，只有强者才能击败它。击败可升10级。\n\n");
	printf("请输入标号：");
	int choice;
	scanf("%d",&choice);
	while(choice<0||choice>10){
		printf("您的输入输入有误，请重新输入标号：");
		scanf("%d",&choice);
	}
	if(choice==0)return 0;
	int enhp=choice*choice*choice*8  ;
	int enat=choice*choice*choice*4;
	int ende=choice*choice*choice;
	srand((unsigned)time(NULL));
	int enna;//怪物属性
	float mebl,enbl;//我方伤害倍率mebl，敌方伤害倍率enbl
	enna=rand()%3+1;//怪物属性随机 
	if(enna==1){
		printf("\n当前怪物属性为：水\n");
	}else if(enna==2){
		printf("\n当前怪物属性为：火\n");
	}else{
		printf("\n当前怪物属性为：木\n");
	} 
	//确定双方伤害倍率 
	if(u[now].fnum==1){
		if(enna==1){mebl=1.0;enbl=1.0;}
		if(enna==2){mebl=1.2;enbl=0.8;}
		if(enna==3){mebl=0.8;enbl=1.2;}
	}
	if(u[now].fnum==2){
		if(enna==1){mebl=0.8;enbl=1.2;}
		if(enna==2){mebl=1.0;enbl=1.0;}
		if(enna==3){mebl=1.2;enbl=0.8;}
	}
	if(u[now].fnum==3){
		if(enna==1){mebl=1.2;enbl=0.8;}
		if(enna==2){mebl=0.8;enbl=1.2;}
		if(enna==3){mebl=1.0;enbl=1.0;}
	}
	int meAtNum=0,enAtNum=0,winner;
	float meHP=hp(now);
	while(1){
		enhp-=(at(now)-ende)*mebl;//我方先手 
		meAtNum++;//我方攻击次数 
		if(enhp<0){winner=1;break;}//我方胜利，winner就是1，结束循环 
		meHP-=(enat-de(now))*enbl;//敌方后手 
		enAtNum++;//敌方攻击次数 
		if(meHP<0){winner=0;break;}//敌方胜利，winner就是0，结束循环 
	}
	if(winner){
		u[now].lv+=choice;//胜利就升级
		printf("我方攻击敌方%d次，敌方攻击我方%d次。\n最终我方胜利！充分显示了我们的实力。",meAtNum,enAtNum);
		printf("\n等级提升，当前精灵等级为：%d\n",u[now].lv); 
	}else{
		printf("我方攻击敌方%d次，敌方攻击我方%d次。\n最终我方失败。不要气馁，下次再战。\n",meAtNum,enAtNum);
	}

	mission();//这里又是一个递归 
}

void quickSort(struct data u[],int left,int right){//降序 
	if(left>=right)return;//left>=right下标时结束排序
	int key=u[left].lv;//设定基准元素为第一个元素array[left]的值 
	int i=left;//因为用到了递归，所以不能改变left和right的值
	int j=right;
	struct data temp;
	for(;i<j;){
		for(;u[j].lv<=key&&j>i;j--);//从右往左找到第一个大于基准的数，j等于i时结束循环
		temp=u[i];u[i]=u[j];u[j]=temp;//交换u[i] u[j];
		for(;u[i].lv>=key&&i<j;i++);//从左往右找到第一个小于于基准的数，i等于j时结束循环
		temp=u[i];u[i]=u[j];u[j]=temp;//交换u[i] u[j];
		u[i].lv=key;//array[i]就应该是基准元素最后排好的位置
	}
	quickSort(u,left,i-1);//左侧数组递归
	quickSort(u,i+1,right);//右侧数组递归
} 


void showRanking(){
	quickSort(u,0,count-1);
	printf("\n  全服排名      玩家昵称      精灵名称      精灵等级\n");
	int i;
	for(i=0;i<count;i++){
		u[i].unum=i;//让用户编号从0至count-1 
		printf("%10d",i+1);
		printf("%10s           ",u[i].id);
		name(i);
		printf("%10d\n",u[i].lv);
	} 
}




int upk(){
	showRanking();
	printf("\n请输入要切磋的玩家标号：");
	int choice;
	scanf("%d",&choice);
	while(choice>count||choice<1){
		printf("输入有误，请重新输入要切磋的玩家标号：");
		scanf("%d",&choice);
	}

	float mebl,enbl;//我方伤害倍率mebl，敌方伤害倍率enbl
	if(u[now].fnum==1){
		if(u[choice-1].fnum==1){mebl=1.0;enbl=1.0;}
		if(u[choice-1].fnum==2){mebl=1.2;enbl=0.8;}
		if(u[choice-1].fnum==3){mebl=0.8;enbl=1.2;}
	}
	if(u[now].fnum==2){
		if(u[choice-1].fnum==1){mebl=0.8;enbl=1.2;}
		if(u[choice-1].fnum==2){mebl=1.0;enbl=1.0;}
		if(u[choice-1].fnum==3){mebl=1.2;enbl=0.8;}
	}
	if(u[now].fnum==3){
		if(u[choice-1].fnum==1){mebl=1.2;enbl=0.8;}
		if(u[choice-1].fnum==2){mebl=0.8;enbl=1.2;}
		if(u[choice-1].fnum==3){mebl=1.0;enbl=1.0;}
	}
	int meAtNum=0,enAtNum=0,winner;
	float meHP=hp(now),enHP=hp(choice-1);
	while(1){
		enHP-=(at(now)-de(choice-1))*mebl;
		meAtNum++;
		if(enHP<0){winner=1;break;}
		meHP-=(at(choice-1)-de(now))*enbl;
		enAtNum++;
		if(meHP<0){winner=0;break;}
	}
	if(winner){
		printf("我方攻击敌方%d次，敌方攻击我方%d次。\n最终我方胜利！充分显示了我们的实力。",meAtNum,enAtNum);
	}else{
		printf("我方攻击敌方%d次，敌方攻击我方%d次。\n最终我方失败。不要气馁，下次再战。",meAtNum,enAtNum);
	}
}


int save(){//保存数据至文件 
	FILE *fp;
	int i;
	if((fp=fopen ("data.txt","w"))==NULL){
		printf("信息文件打开失败！\n");
		return 1;
	}
	for(i=0;i<count;i++){
		fprintf(fp,"%10d%10s%10s%10d%10d\n",u[i].unum,u[i].id,u[i].password,u[i].fnum,u[i].lv);
	}
	return 0;
}
//结束