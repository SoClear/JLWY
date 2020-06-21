#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
typedef struct data{//�ṹ�� 
	int unum;//�û��ı�ţ�0��99 
	char id[10];//�û�id 
	char password[10];//�û����� 
	int fnum;//�û���ѡ�ľ����ţ�1,2,3�������Ϊ0��˵���û�ûѡ���� 
	int lv;//�û�����ȼ�
}USER;



//ȫ�ֱ���
int count=0;//��������ǰ���� 
USER u[100];//�����������Գ���100�����
int now;//��ҵ�¼�󱣴浱ǰ��ҵı�ţ���Ӧ��unum�� 




//�����Ǻ�������
void welcome1();//��ӭ����
void welcome2();//ע����¼ѡ����ʾ 
int load();//����TXT�ļ����ڴ��� 
int enroll();//ע�ắ��
int login();//��¼������������ֵΪ100������Ϸ����
void loginWelcome();//��¼�ɹ������˸��ף
int changePassword();//��������
int checkFairy();//����û�ѡ��ľ���
void mainWel();//��ʾ������ѡ����ʾ
int name(int a);//��ʾ�û���ѡ���������
int nature(int a);//��ʾ�������� 
int hp(int a);//�û���ѡ�����Ѫ��
int at(int a);//�û���ѡ����Ĺ�����
int de(int a);//�û���ѡ����ķ�����
int showFairyQuality();//��ʾ�������ƣ��ȼ���Ѫ��������������
int mission();//��������
void quickSort(struct data u[],int left,int right);//�������� 
void showRanking();//����ʾ��λ����
int upk();//���pk 
int save();//���浱ǰ���ݵ�TXT�ļ��ĺ���



int main(){//������
	//��Ϸ��ʼǰ.................
	welcome1();
	load();
	welcome2();
	int choice;
	scanf("%d",&choice);
	if(choice!=2){//��ѡ2���ǵ�¼
		now=login();//���ص�¼����,����ȫ�ֱ���now����Ϊ��ǰ�û����
		if(now==100){//����û���֤ʧ��
			return 0;//��ô������Ϸ
		}else{//�û���¼�ɹ���
			loginWelcome();//��ʾ��Ϲ36k봽��۵ĵ�¼��Ч
		}
	}else{//ѡ2����ע��,����ȫ�ֱ���now����Ϊ��ǰ�û����
		now=enroll();//�û�ע��
		loginWelcome();//ע��ɹ�����ʾ��Ϲ36k봽��۵���Ч
		printf("ע��ɹ������Զ���¼��\n\n");
	}
	
	
	system("cls");
	//��ʽ��ʼ��Ϸ............. 
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
 




//�����Ǻ���ʵ�ֲ���


//��ʼ��Ϸ֮ǰ


void welcome1(){//��ӭ����1 
	system("color 0a");//���汳����ɫ��������ɫ
	printf("\n\n******************��������******************\n\n\n");
}

void welcome2(){//��ӭ����2
	printf("**********     **********\n");
	printf("* 1 ��¼ *     * 2 ע�� *\n");
	printf("**********     **********\n");
}


int load(){//����TXT�ļ����ڴ���
	FILE *fp;
	int i=0;
	if((fp=fopen ("data.txt","r"))==NULL){
		fp=fopen("data.txt","w+");
	//	printf("δ�ҵ���Ϣ�ļ������½��µ���Ϣ�ļ�\n");
	}
	//���ļ������ݴ�������USER u[100]��
	while(!feof(fp))//����feof()���ڼ���Ƿ񵽴��ļ�ĩβ������ʱ���ط�0ֵ
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
   fclose (fp);//�ر��ļ�
   printf("ȫ��%dλ�������ͬ�ڡ�\n\n\n\n",count);
   return 0; 
} 


int enroll(){//ע�ắ��
	system("color 06");//���汳����ɫ�������ɫ
	int i;
	if(count<100){
		i=count;
		u[i].unum=i;
		printf("�������˺ţ��ǳƣ���");
		char s[10];//��ʱ�����û����˺� 
		scanf("%s",&s);
		printf("%s",u[i].id);
		for(i=0;i<count;i++){//�����û� 
			while(!strcmp(u[i].id,s)){//��������ͬ���û�id 
				printf("�˺ţ��ǳƣ��Ѵ��ڣ����������룺");
				i=0;
				scanf("%s",&s);
			}
	    }
		strcpy(u[i].id,s);//���ַ���s���ݴ���u[i].id
		printf("���������룺");
		scanf("%s",&u[i].password);
		count++;//�û�������һ 
	}else{
		printf("����������\n");
	}
	return i;
} 



int login(){//��¼���� 
	system("color 04");//���汳����ɫ�������ɫ 
	printf("�������˺ţ��ǳƣ���");
	char s[10];
	scanf("%s",&s);
	int i;
	for(i=0;i<count;i++){
		if(!strcmp(u[i].id,s)){
			printf("���������룺");
			scanf("%s",&s);
			if(!strcmp(u[i].password,s)){
				printf("��½�ɹ�\n");
				return  i;
			}else{
				int j;
				for(j=0;j<3;j++){
					printf("�������������%d�γ��Ի��ᣬ�������������룺",3-j);
					scanf("%s",&s);
					if(!strcmp(u[i].password,s)){
						printf("��½�ɹ�\n");
						return i;
					}
					if(j==2){
						printf("���볢�Դ����ﵽ���ޣ��˻����뱣��ģʽ��������Ϸ�Խ����");
						return 100; 
					}
				}
			}
			
		}
		if(i==count-1){//�������û�� 
			printf("�˺ţ��ǳƣ�����");
	    }
	}
	login();//�ݹ飬���ú�����������Ѫ������� 
}


void loginWelcome(){//��Ϲ36k봽��۵ĵ�¼��Ч 
	int i;
	for(i=0;i<5;i++){
		system("color 2a");
		system("color 3a");
		system("color ba");
	}
	system("color 0a");
} 




int changePassword(){//�޸����� 
	printf("\n�޸����룿\n");
	printf("1 ��      2 ��\n");
	int choice;
	scanf("%d",&choice);
	if(choice==1){
		printf("�����������룺");
		scanf("%s",u[now].password);
		printf("�����޸ĳɹ���\n");
	}
	return 0;
}



//��ʼ��Ϸ 


int checkFairy(){//����û����� 
	if(u[now].fnum==0){
		u[now].lv=1;//��ʼ������ȼ�Ϊ1�� 
		printf("������������ԣ�ˮ �� ľ \n����ˮ�˻𣬻��ľ��ľ��ˮ��\n");
		printf("Ŀǰ��3�־��鹩��ѡ��\n\n");
		printf("1 ��ˮ����\n");
		printf("ˮ������ˮ���Ծ��飬���м��ߵ�Ѫ���츳������ս�������ĵ��ˡ�\n\n");
		printf("2 �������\n");
		printf("������ǻ����Ծ��飬���м��ߵĹ����츳���Ե�����ɱ�ը�˺���\n\n");
		printf("3 ��������\n");
		printf("��������ˮ���Ծ��飬���м��ߵķ����츳���ܵ����˺������١�\n\n");
		printf("��������ѡ��ľ����ţ�");
		scanf("%d",&u[now].fnum);
		while(u[now].fnum!=1&&u[now].fnum!=2&&u[now].fnum!=3){
			printf("�������������������룺");
			scanf("%d",&u[now].fnum);
		}
		printf("��ϲ��ӵ��������\n");
	}
	return 0;
}



void mainWel(){
	printf("\n\n");
	printf("--------------------       --------------------       --------------------\n");
	printf("-  1   ��������    -       -  2   ��������    -       -  3   ����д�    -\n");
	printf("--------------------       --------------------       --------------------\n");
	printf("\n");
	printf("--------------------       --------------------       --------------------\n");
	printf("-  4   ��λ����    -       -  5   �޸�����    -       -  6   �����˳�    -\n");
	printf("--------------------       --------------------       --------------------\n");
	printf("\n\n�����빦�ܱ�ţ�");
}


int name(int a){//��������
	if(u[a].lv<60){
		if(u[a].fnum==1)printf("ˮ����");
	    if(u[a].fnum==2)printf("�����");
	    if(u[a].fnum==3)printf("������");
	}else{
		if(u[a].fnum==1)printf("���ຣ��");
		if(u[a].fnum==2)printf("��ħ֮��");
		if(u[a].fnum==3)printf("ħ����");
	}
	
	return 0;
}

int nature(int a){//�������� 
	if(u[a].fnum==1)printf("ˮ");
	if(u[a].fnum==2)printf("��");
	if(u[a].fnum==3)printf("ľ");
	return 0;
} 


int hp(int a){//����Ѫ�� 
	if(u[a].fnum==1){return u[a].lv*12;}
	if(u[a].fnum==2){return u[a].lv*10;}
	if(u[a].fnum==3){return u[a].lv*10;}
}


int at(int a){//���鹥�� 
	if(u[a].fnum==1){return u[a].lv*5;}
	if(u[a].fnum==2){return u[a].lv*6;}
	if(u[a].fnum==3){return u[a].lv*5;}
}


int de(int a){//������� 
	if(u[a].fnum==1){return u[a].lv;}
	if(u[a].fnum==2){return u[a].lv;}
	if(u[a].fnum==3){return u[a].lv*2;}
}


int showFairyQuality(){
	printf("\n���飺");name(now);
	printf("\n���ԣ�");nature(now);
	printf("\n�ȼ���%d",u[now].lv);
	printf("\nѪ����%d",hp(now));
	printf("\n������%d",at(now));
	printf("\n������%d",de(now));
	return 0;
}


int mission(){
	
	printf("\n���й������������\n����ȼ��ﵽ60�����ɽ�����\n\n");
	int i;
	printf("0�����ء�\n");
	for(i=1;i<=4;i++){
		printf("%d��%d��������ܿ���%d����\n",i,i,i);
	}
	printf("5��5��Զ�ž��ޣ����ܿ���5����\n");
	for(i=6;i<=9;i++){
		printf("%d��%d��������ܿ���%d����\n",i,i,i);
	}
	printf("10��10��Զ�ž��ޣ�ֻ��ǿ�߲��ܻ����������ܿ���10����\n\n");
	printf("�������ţ�");
	int choice;
	scanf("%d",&choice);
	while(choice<0||choice>10){
		printf("���������������������������ţ�");
		scanf("%d",&choice);
	}
	if(choice==0)return 0;
	int enhp=choice*choice*choice*8  ;
	int enat=choice*choice*choice*4;
	int ende=choice*choice*choice;
	srand((unsigned)time(NULL));
	int enna;//��������
	float mebl,enbl;//�ҷ��˺�����mebl���з��˺�����enbl
	enna=rand()%3+1;//����������� 
	if(enna==1){
		printf("\n��ǰ��������Ϊ��ˮ\n");
	}else if(enna==2){
		printf("\n��ǰ��������Ϊ����\n");
	}else{
		printf("\n��ǰ��������Ϊ��ľ\n");
	} 
	//ȷ��˫���˺����� 
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
		enhp-=(at(now)-ende)*mebl;//�ҷ����� 
		meAtNum++;//�ҷ��������� 
		if(enhp<0){winner=1;break;}//�ҷ�ʤ����winner����1������ѭ�� 
		meHP-=(enat-de(now))*enbl;//�з����� 
		enAtNum++;//�з��������� 
		if(meHP<0){winner=0;break;}//�з�ʤ����winner����0������ѭ�� 
	}
	if(winner){
		u[now].lv+=choice;//ʤ��������
		printf("�ҷ������з�%d�Σ��з������ҷ�%d�Ρ�\n�����ҷ�ʤ���������ʾ�����ǵ�ʵ����",meAtNum,enAtNum);
		printf("\n�ȼ���������ǰ����ȼ�Ϊ��%d\n",u[now].lv); 
	}else{
		printf("�ҷ������з�%d�Σ��з������ҷ�%d�Ρ�\n�����ҷ�ʧ�ܡ���Ҫ���٣��´���ս��\n",meAtNum,enAtNum);
	}

	mission();//��������һ���ݹ� 
}

void quickSort(struct data u[],int left,int right){//���� 
	if(left>=right)return;//left>=right�±�ʱ��������
	int key=u[left].lv;//�趨��׼Ԫ��Ϊ��һ��Ԫ��array[left]��ֵ 
	int i=left;//��Ϊ�õ��˵ݹ飬���Բ��ܸı�left��right��ֵ
	int j=right;
	struct data temp;
	for(;i<j;){
		for(;u[j].lv<=key&&j>i;j--);//���������ҵ���һ�����ڻ�׼������j����iʱ����ѭ��
		temp=u[i];u[i]=u[j];u[j]=temp;//����u[i] u[j];
		for(;u[i].lv>=key&&i<j;i++);//���������ҵ���һ��С���ڻ�׼������i����jʱ����ѭ��
		temp=u[i];u[i]=u[j];u[j]=temp;//����u[i] u[j];
		u[i].lv=key;//array[i]��Ӧ���ǻ�׼Ԫ������źõ�λ��
	}
	quickSort(u,left,i-1);//�������ݹ�
	quickSort(u,i+1,right);//�Ҳ�����ݹ�
} 


void showRanking(){
	quickSort(u,0,count-1);
	printf("\n  ȫ������      ����ǳ�      ��������      ����ȼ�\n");
	int i;
	for(i=0;i<count;i++){
		u[i].unum=i;//���û���Ŵ�0��count-1 
		printf("%10d",i+1);
		printf("%10s           ",u[i].id);
		name(i);
		printf("%10d\n",u[i].lv);
	} 
}




int upk(){
	showRanking();
	printf("\n������Ҫ�д����ұ�ţ�");
	int choice;
	scanf("%d",&choice);
	while(choice>count||choice<1){
		printf("������������������Ҫ�д����ұ�ţ�");
		scanf("%d",&choice);
	}

	float mebl,enbl;//�ҷ��˺�����mebl���з��˺�����enbl
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
		printf("�ҷ������з�%d�Σ��з������ҷ�%d�Ρ�\n�����ҷ�ʤ���������ʾ�����ǵ�ʵ����",meAtNum,enAtNum);
	}else{
		printf("�ҷ������з�%d�Σ��з������ҷ�%d�Ρ�\n�����ҷ�ʧ�ܡ���Ҫ���٣��´���ս��",meAtNum,enAtNum);
	}
}


int save(){//�����������ļ� 
	FILE *fp;
	int i;
	if((fp=fopen ("data.txt","w"))==NULL){
		printf("��Ϣ�ļ���ʧ�ܣ�\n");
		return 1;
	}
	for(i=0;i<count;i++){
		fprintf(fp,"%10d%10s%10s%10d%10d\n",u[i].unum,u[i].id,u[i].password,u[i].fnum,u[i].lv);
	}
	return 0;
}
//����