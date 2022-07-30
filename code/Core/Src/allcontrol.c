#include"allcontrol.h"
int button_turn()
{
	if(HAL_GPIO_ReadPin(key2_GPIO_Port,key2_Pin)==0){
			HAL_Delay(100);
			if(HAL_GPIO_ReadPin(key2_GPIO_Port,key2_Pin)==0){
				return 1;
			}
	}
	return 0;
}
int button_sure()
{
	if(HAL_GPIO_ReadPin(key0_GPIO_Port,key0_Pin)==0){
			HAL_Delay(100);
			if(HAL_GPIO_ReadPin(key0_GPIO_Port,key0_Pin)==0){
				return 1;
			}
	}
	return 0;
}
int button_return()
{
	if(HAL_GPIO_ReadPin(key4_GPIO_Port,key4_Pin)==0){
			HAL_Delay(100);
			if(HAL_GPIO_ReadPin(key4_GPIO_Port,key4_Pin)==0){
				return 1;
			}
	}
	return 0;
}
int button_other1()
{
	if(HAL_GPIO_ReadPin(key0_GPIO_Port,key0_Pin)==0){
			HAL_Delay(100);
			if(HAL_GPIO_ReadPin(key0_GPIO_Port,key0_Pin)==0){
				return 1;
			}
	}
	return 0;
}
int button_other2()
{
	if(HAL_GPIO_ReadPin(key1_GPIO_Port,key1_Pin)==0){
			HAL_Delay(100);
			if(HAL_GPIO_ReadPin(key1_GPIO_Port,key1_Pin)==0){
				return 1;
			}
	}
	return 0;
}
int get_tem()
{

}
void fresh_bat(int bat,u8g2_t u8g2){
	u8g2_SetFont(&u8g2,u8g2_font_siji_t_6x10);
	u8g2_DrawGlyph(&u8g2,113,10,0xe242);
	u8g2_SendBuffer(&u8g2);
}
void display_page_time(int time[],u8g2_t u8g2){
	char ptime[12]="";
	convert_time(time,ptime);
	char time_str2[9]={ptime[0],ptime[1],'.',ptime[2],ptime[3],'.',ptime[4],ptime[5]};
	char time_str1[6]={ptime[6],ptime[7],':',ptime[8],ptime[9]};
	char time_str3[3]={ptime[10],ptime[11]};
	u8g2_SetFont(&u8g2,u8g2_font_inr21_mf);
	u8g2_DrawStr(&u8g2,20,48,time_str1);
	u8g2_SetFont(&u8g2,u8g2_font_t0_14_mf);
	u8g2_DrawStr(&u8g2,40,10,time_str2);
	u8g2_DrawStr(&u8g2,113,48,time_str3);
}
void display_page_init(u8g2_t u8g2){
	u8g2_ClearDisplay(&u8g2);
	u8g2_SetBitmapMode(&u8g2,0);
	u8g2_DrawXBM(&u8g2,0,0,128,64,start_pic);
	u8g2_SendBuffer(&u8g2);
	HAL_Delay(1500);
	for(int i=1;i<=128;i+=3){
		u8g2_DrawLine(&u8g2,i,0,i,64);
		u8g2_SetFont(&u8g2,u8g2_font_inr21_mf);
		if(i<=48&&i>30)
			u8g2_DrawStr(&u8g2,30,45,"S");
		if(i>48&&i<=67)
			u8g2_DrawStr(&u8g2,30,45,"SF");
		if(i>68&&i<=86)
			u8g2_DrawStr(&u8g2,30,45,"SFW");
		if(i>87)
			u8g2_DrawStr(&u8g2,30,45,"SFWR");
		u8g2_SendBuffer(&u8g2);
		u8g2_ClearBuffer(&u8g2);
	}
	u8g2_ClearBuffer(&u8g2);
	u8g2_DrawStr(&u8g2,30,45,"SFWR");
	u8g2_SendBuffer(&u8g2);
	HAL_Delay(1500);
}
void display_page_music(u8g2_t u8g2,int music_pos){

	u8g2_ClearBuffer(&u8g2);
	u8g2_DrawStr(&u8g2,10,10,"music1");
	u8g2_DrawStr(&u8g2,10,22,"music2");
	u8g2_DrawStr(&u8g2,10,34,"music3");
	u8g2_DrawStr(&u8g2,10,46,"music4");
	u8g2_DrawStr(&u8g2,10,58,"music5");
	u8g2_SetFont(&u8g2,u8g2_font_siji_t_6x10);
	u8g2_DrawGlyph(&u8g2,60,10+music_pos*12-12,0xe12e);
	//u8g2_SendBuffer(&u8g2);
}
void display_card(u8g2_t u8g2,int p1[]){//display now card/p1 card/p2 card
	int posnow=0,pos_sure=0;
	u8g2_SetFont(&u8g2,u8g2_font_unifont_t_cards);
	for(int i=1;i<=14;i++)
		if(p1[i]){
			p1_reline[++posnow]=0x20+i;
			u8g2_DrawGlyph(&u8g2,(posnow-1)%7*12,(posnow-1)/7*22+33,0x20+i);
			if(p1[i]==2){
				p1_reline[++posnow]=0x30+i;
				u8g2_DrawGlyph(&u8g2,(posnow-1)%7*12 ,(posnow-1)/7*22+33,0x30+i);
			}
		}
	for(int i=1;i<=p1_card;i++)
		if(p1_flag[i]){
			if(pos_sure<=10)
				u8g2_DrawGlyph(&u8g2,pos_sure*11,16,p1_reline[i]);
			if(pos_sure>10)
				u8g2_DrawGlyph(&u8g2,pos_sure%10*11+72,33,p1_reline[i]);
			pos_sure++;
		}
	if(p2_len){
		char char_p2[8]="",char_p2_2[8]="";
		u8g2_SetFont(&u8g2,u8g2_font_5x7_tf);
		for(int i=1;i<=minn(7,p2_len);i++)
			char_p2_2[i-1]=get_card_p2(p2_line[i]);
		for(int i=7;i<=p2_len;i++)
			char_p2_2[i-8]=get_card_p2(p2_line[i]);
		u8g2_DrawStr(&u8g2,88,47,char_p2);
		u8g2_DrawStr(&u8g2,88,57,char_p2_2);
	}
}
void card_feedback(int from_line[],int from_len){
	for(int i=1;i<=14;i++)p2_line[i]=0;
	p2_len=0;
	if(from_len==1){
		for(int i=from_line[1]+1;i<=14;i++)
			if(p2[i]){
				p2_line[1]=i;
				p2_len=1;
				p2[i]--;
				return;
			}
	}
	if(from_len==2){
		for(int i=from_line[1]+1;i<=14;i++)
			if(p2[i]==2){
				p2_line[1]=i;
				p2_line[2]=i;
				p2[i]=0;
				p2_len=2;
				return;
			}
	}
	if(from_len>=5){
		int tem_len=0;
		if(from_line[1]==from_line[2]){
			for(int i=from_line[1]+1;i<=14;i++)
				if(p2[i]==2)
					tem_len++;
				else{
					if(tem_len*2>=from_len){
						for(int j=i-tem_len;j<i;j++){
							p2_line[++p2_len]=i;
							p2_line[++p2_len]=i;
							p2[j]=0;
						}
						return;
					}
					tem_len=0;
				}
		}
		else{
			for(int i=from_line[1]+1;i<=14;i++)
				if(p2[i])
					tem_len++;
				else{
					if(tem_len>=from_len){
						for(int j=i-tem_len;j<i;j++){
							p2_line[++p2_len]=j;
							p2[j]--;
						}
						return;
					}
					tem_len=0;
				}
		}
	}
}
void let_p2(){
	for(int i=1;i<=14;i++)p2_line[i]=0;
	p2_len=0;
	int tem_len=0;
	for(int i=1;i<=14;i++)
		if(p2[i]==2)
			tem_len++;
		else{
			if(tem_len>=3){
				for(int j=i-tem_len;j<i;j++){
					p2_line[++p2_len]=j;
					p2_line[++p2_len]=j;
					p2[j]=0;
				}
				return;
			}
			tem_len=0;
		}
	for(int i=1;i<=14;i++)
		if(p2[i])
			tem_len++;
		else{
			if(tem_len>=5){
				for(int j=i-tem_len;j<i;j++){
					p2_line[++p2_len]=j;
					p2[j]--;
				}
				return;
			}
			tem_len=0;
		}

	for(int i=1;i<=14;i++){
		if(p2[i]){
			p2_line[++p2_len]=i;
			if(p2[i]==2)
				p2_line[++p2_len]=i;
			p2[i]=0;
			return;
		}
	}
}
int card_check(int len){
	int check_flag=0;
	if(len==1)check_flag=1;
	if(len==2&&p1_line[1]==p1_line[2])check_flag=1;
	if(len==0||(len<5&&len>=3)||p1_line[len]==14)return 0;
	if(len>=5){
		if(p1_line[1]==p1_line[2]){
			if(len%2!=0)return 0;
			for(int i=1;i<len/2;i++)
				if(p1_line[i*2]!=p1_line[i*2+1])return 0;
			check_flag=1;
		}
		else {
			for(int i=1;i<len;i++)
				if(p1_line[i]+1!=p1_line[i+1])return 0;
			check_flag=1;
		}
	}
	if(p2_len==0&&check_flag)return 1;
	if(p2_len!=0&&check_flag){
		if(p2_len<=2){
			if(p2_len!=len)return 0;
			if(p1_line[1]<=p2_line[1])return 0;
			return 1;
		}
		if(p2_len>=5){
			if((p1_line[1]==p1_line[2])&&(p2_line[1]!=p2_line[2]))return 0;
			if((p1_line[1]!=p1_line[2])&&(p2_line[1]==p2_line[2]))return 0;
			if(p1_line[1]<=p2_line[1]||len<p2_len)return 0;
			return 1;
		}
		return 0;
	}
	return 0;
}
void refresh_card(u8g2_t u8g2,int set_pos[15][2]){
	u8g2_ClearBuffer(&u8g2);
	display_card(u8g2,p1);
	u8g2_SetFont(&u8g2,u8g2_font_6x12_t_symbols);
	u8g2_DrawGlyph(&u8g2,set_pos[set_card_pos][0],set_pos[set_card_pos][1],0x25b4);
	u8g2_SendBuffer(&u8g2);
}
void card_init(int seed){
	rand_cnt=0;
	p1_card=14;
	p2_card=14;
	p2_len=0;
	set_card_pos=1;
	for(int i=1;i<=14;i++){
		p1[i]=0;
		p2[i]=0;
		p1_flag[i]=0;
		p1_line[i]=0;
		p2_line[i]=0;
	}
	srand(seed);
	while(1){
		int pos=rand()%14+1;
		if(p1[pos]<=1){
			p1[pos]++;
			rand_cnt++;
		}
		if(rand_cnt==14)break;
	}
	for(int i=1;i<=14;i++)p2[i]=2-p1[i];
}
void play_card(u8g2_t u8g2,int seed){
	int card_set_pos[15][2]={{0,0},{5,42},{17,42},{29,42},{41,42},{53,42},{65,42},{77,42},{5,64},{17,64},{29,64},{41,64},{53,64},{65,64},{77,64}};
	card_init(seed);
	display_card(u8g2,p1);
	u8g2_SetFont(&u8g2,u8g2_font_6x12_t_symbols);
	u8g2_DrawGlyph(&u8g2,card_set_pos[1][0],card_set_pos[1][1],0x25b4);
	u8g2_SendBuffer(&u8g2);
	while(p1_card&&p2_card){
		if(button_turn()){
			set_card_pos++;
			if(set_card_pos>p1_card)set_card_pos=1;
			refresh_card(u8g2,card_set_pos);
		}
		if(button_sure()){
			p1_flag[set_card_pos]=1^p1_flag[set_card_pos];
			refresh_card(u8g2,card_set_pos);
		}
		if(button_return()){
			int p1_len=0;
			for(int i=1;i<=p1_card;i++)
				if(p1_flag[i]){
					if(p1_reline[i]>0x30)
						p1_line[++p1_len]=p1_reline[i]-0x30;
					else
						p1_line[++p1_len]=p1_reline[i]-0x20;
				}
			if(card_check(p1_len)){
				card_feedback(p1_line,p1_len);
				p2_card-=p2_len;
				for(int i=1;i<=p1_len;i++)
					p1[p1_line[i]]--;
				for(int i=1;i<=14;i++){
					p1_line[i]=0;
					p1_flag[i]=0;
				}
				p1_card-=p1_len;
				p1_len=0;
				refresh_card(u8g2,card_set_pos);
			}
			else{
				u8g2_SetFont(&u8g2,u8g2_font_t0_14_mf);
				u8g2_DrawStr(&u8g2,88,57,"Err");
				u8g2_SendBuffer(&u8g2);
			}
		}
		if(button_other1()){
			let_p2();
			p2_card-=p2_len;
			refresh_card(u8g2,card_set_pos);
		}
	}
	u8g2_ClearDisplay(&u8g2);
	u8g2_SetFont(&u8g2,u8g2_font_inr21_mf);
	if(!p1_card)
		u8g2_DrawStr(&u8g2,10,45,"Win");
	else
		u8g2_DrawStr(&u8g2,10,45,"Lose");
	u8g2_SendBuffer(&u8g2);
}
void broadcast_music(int music_p[],int music_l[]){
	int music_p_pos=1;
		while(music_p[music_p_pos]!=0xff){
			if(music_p[music_p_pos]==0)break;
			for(int i=1;i<=music_l[music_p_pos]*897*music_tone[music_p[music_p_pos]]/2500;i++){
				HAL_GPIO_TogglePin(music_GPIO_Port,music_Pin);
				delay_us(108696/music_tone[music_p[music_p_pos]]);
				HAL_GPIO_TogglePin(music_GPIO_Port,music_Pin);

				delay_us(108696/music_tone[music_p[music_p_pos]]);
			}
			music_p_pos++;
			if(music_1_p[music_p_pos]==0)break;
		}
}
void display_music(int music_pos){
	if(music_pos==1)broadcast_music(music_1_p,music_1_l);
	if(music_pos==2)broadcast_music(music_2_p,music_2_l);
}


