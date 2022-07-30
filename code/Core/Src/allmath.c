#include"allmath.h"
int check_time(int y,int m,int d){
	if(m==2){
		if((y%4==0&&y%100!=0)||(y%400==0)){
			if(d>29)return 1;
		}
		else{
			if(d>28)return 1;
		}
	}
	if(m==1||m==3||m==5||m==7||m==8||m==10||m==12)
		if(d>31)return 1;
	if(m==4||m==6||m==9||m==11)
		if(d>30)return 1;
	return 0;
}
void next_time(int *nowtime){
	if(nowtime[5]==60){
		nowtime[5]=0;
		nowtime[4]++;
		if(nowtime[4]==60){
			nowtime[4]=0;
			nowtime[3]++;
			if(nowtime[3]==24){
				nowtime[3]=0;
				nowtime[2]++;
				if(nowtime[2]>=28&&check_time(nowtime[0],nowtime[1],nowtime[2])){
					nowtime[2]=0;
					nowtime[1]++;
					if(nowtime[1]>=13){
						nowtime[1]=1;
						nowtime[0]++;
					}
				}
			}
		}
	}
}
void convert_time(int nowtime[],char *p){
	p[0]=nowtime[0]/10%10+'0';
	p[1]=nowtime[0]%10+'0';
	for(int i=1;i<=5;i++){
		p[i*2]=nowtime[i]/10+'0';
		p[i*2+1]=nowtime[i]%10+'0';
	}
}
void modify_time(int *nowtime,int pos,int direction)
{
	if(pos==0)nowtime[0]+=(direction*2-1);
	if(pos==1)nowtime[1]=(nowtime[1]+direction*2+10)%12+1;
	if(pos==2){
		nowtime[2]+=(direction*2-1);
		int y=nowtime[0],m=nowtime[1],d=nowtime[1];
		if(m==2){
			if((y%4==0&&y%100!=0)||(y%400==0)){
				if(d>29)nowtime[2]=1;
				if(d==0)nowtime[2]=29;
			}
			else{
				if(d>28)nowtime[2]=1;
				if(d==0)nowtime[2]=28;
			}
		}
		if(m==1||m==3||m==5||m==7||m==8||m==10||m==12){
			if(d>31)nowtime[2]=1;
			if(d==0)nowtime[2]=31;
		}
		if(m==4||m==6||m==9||m==11){
			if(d>30)nowtime[2]=1;
			if(d==0)nowtime[2]=30;
		}
	}
	if(pos==3)nowtime[3]=(nowtime[3]+direction*2-1+24)%24;
	if(pos==4||pos==5)nowtime[pos]=(nowtime[pos]+direction*2-1+60)%60;
}
void evaluate_array(int *a,int *b,int len){
	for(int i=0;i<len;i++)a[i]=b[i];
}
int minn(int a,int b){
	if(a>b)return b;
	return a;
}
char get_card_p2(int card_num){
	if(card_num<10)return card_num+'0';
	if(card_num==10)return 'O';
	if(card_num==11)return 'J';
	if(card_num==12)return 'C';
	if(card_num==13)return 'Q';
	if(card_num==14)return 'K';
}

