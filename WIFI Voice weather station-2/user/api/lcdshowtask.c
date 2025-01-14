#include "lcdshowtask.h"

LV_FONT_DECLARE(font1);	

//内部函数声明
void Show_Interface1(void);
void Show_Interface2(void);
void Create_LV_Task_interface1(void);
void Del_LV_Task_interface1(void);
void Show_Interface3(void);
void play_XCity_xDay_weather(char *city,int i);

LV_IMG_DECLARE(cloudy);				//多云
LV_IMG_DECLARE(qing);					//晴
//LV_IMG_DECLARE(baoyu);				//暴雨
LV_IMG_DECLARE(zhongyu);			//中雨
LV_IMG_DECLARE(zhenyu);				//阵雨
LV_IMG_DECLARE(yin);					//阴
LV_IMG_DECLARE(xiaoyu);				//小雨
LV_IMG_DECLARE(duoyun);				//多云
LV_IMG_DECLARE(dayu);					//大雨
LV_IMG_DECLARE(leizhenyu);		//雷阵雨


char CNWord[20];					//显示天气的汉字文本字符串


u8 nowui_flag = 1;			//当前显示页面的标志位
u8 change_flag = 0;			//切换页面防止重复绘制的标志位
u8 nowcity_flag = 1;				//当前显示的第几个城市的天气
u8 change_cityflag = 0;	//防止重绘箭头图标的标志位




int Get_info_from_Internet(void)
{
	if(!ESP8266_Init())		//连接成功返回1，连接失败返回0
	{
		printf("WIFI连接失败\r\n");
		return -1;
	}
	printf("\r\n初始化完成\r\n");
	if(!RTC_TIME_Init())		//初始化RTC，校准RTC时间
	{
		return -1;			
	}
	Get_Weather1();
	if(!GET_City5Weather())
	{
		printf("获取5天天气失败\r\n");
		return -1;
	}
}


//将天气代码转换为UTF-8汉字文本，传入的参数是天气代码
void Weathercode_to_CNWord(int code,int day)
{
	memset(CNWord,0,sizeof(CNWord));			
	switch(code)
	{
		case 0:	;
		case 1:	;
		case 2:	;
		case 3:	
				strcpy(CNWord,"鏅� "); 
				if(nowui_flag == 1)
				{					
					lv_img_set_src(img_weather,&qing);																	
				}
				else if((nowui_flag ==2)&&(day == 1))
				{
					lv_img_set_src(img2_weather_today,&qing);
				}
				else if((nowui_flag == 2)&&(day == 2))
				{
					lv_img_set_src(img2_weather_tommorrow,&qing);
				}
				else if((nowui_flag == 2)&&(day == 3))
				{
					lv_img_set_src(img2_weather_aftertomm,&qing);
				}
				else if((nowui_flag == 3)&&(day == 1))
				{
						lv_img_set_src(img3_weather_today,&qing);
				}
				else if((nowui_flag == 3)&&(day == 2))
				{
						lv_img_set_src(img3_weather_tommorrow,&qing);
				}
				else if((nowui_flag == 3)&&(day == 3))
				{
						lv_img_set_src(img3_weather_aftertomm,&qing);
				}
																						break;			//晴
		case 4:	;																	
		case 5:	;
		case 6:	;																	
		case 7:	;
		case 8:	
				strcpy(CNWord,"澶氫簯 ");
				if(nowui_flag == 1)
				{					
					lv_img_set_src(img_weather,&duoyun);																	
				}
				else if((nowui_flag ==2)&&(day == 1))
				{
					lv_img_set_src(img2_weather_today,&duoyun);
				}
				else if((nowui_flag == 2)&&(day == 2))
				{
					lv_img_set_src(img2_weather_tommorrow,&duoyun);
				}
				else if((nowui_flag == 2)&&(day == 3))
				{
					lv_img_set_src(img2_weather_aftertomm,&duoyun);
				}
				else if((nowui_flag == 3)&&(day == 1))
				{
					lv_img_set_src(img3_weather_today,&duoyun);
				}
				else if((nowui_flag == 3)&&(day == 2))
				{
					lv_img_set_src(img3_weather_tommorrow,&duoyun);
				}
				else if((nowui_flag == 3)&&(day == 3))
				{
					lv_img_set_src(img3_weather_aftertomm,&duoyun);
				}																																
																					break;			//多云
		case 9:	
				strcpy(CNWord,"闃� ");
				if(nowui_flag == 1)
				{					
					lv_img_set_src(img_weather,&yin);																	
				}
				else if((nowui_flag ==2)&&(day == 1))
				{
					lv_img_set_src(img2_weather_today,&yin);
				}
				else if((nowui_flag == 2)&&(day == 2))
				{
					lv_img_set_src(img2_weather_tommorrow,&yin);
				}
				else if((nowui_flag == 2)&&(day == 3))
				{
					lv_img_set_src(img2_weather_aftertomm,&yin);
				}
				else if((nowui_flag == 3)&&(day == 1))
				{
					lv_img_set_src(img3_weather_today,&yin);
				}
				else if((nowui_flag == 3)&&(day == 2))
				{
					lv_img_set_src(img3_weather_tommorrow,&yin);
				}
				else if((nowui_flag == 3)&&(day == 3))
				{
					lv_img_set_src(img3_weather_aftertomm,&yin);
				}																																
																				break;			//阴
		case 10:
				strcpy(CNWord,"闃甸洦 ");
				if(nowui_flag == 1)
				{					
					lv_img_set_src(img_weather,&zhenyu);																	
				}
				else if((nowui_flag ==2)&&(day == 1))
				{
					lv_img_set_src(img2_weather_today,&zhenyu);
				}
				else if((nowui_flag == 2)&&(day == 2))
				{
					lv_img_set_src(img2_weather_tommorrow,&zhenyu);
				}
				else if((nowui_flag == 2)&&(day == 3))
				{
					lv_img_set_src(img2_weather_aftertomm,&zhenyu);
				}
				else if((nowui_flag == 3)&&(day == 1))
				{
					lv_img_set_src(img3_weather_today,&zhenyu);
				}
				else if((nowui_flag == 3)&&(day == 2))
				{
					lv_img_set_src(img3_weather_tommorrow,&zhenyu);
				}
				else if((nowui_flag == 3)&&(day == 3))
				{
					lv_img_set_src(img3_weather_aftertomm,&zhenyu);
				}																																
																				break;			//阵雨
		case 11:
				strcpy(CNWord,"闆烽樀闆� ");	
				if(nowui_flag == 1)
				{					
					lv_img_set_src(img_weather,&leizhenyu);																	
				}
				else if((nowui_flag ==2)&&(day == 1))
				{
					lv_img_set_src(img2_weather_today,&leizhenyu);
				}
				else if((nowui_flag == 2)&&(day == 2))
				{
					lv_img_set_src(img2_weather_tommorrow,&leizhenyu);
				}
				else if((nowui_flag == 2)&&(day == 3))
				{
					lv_img_set_src(img2_weather_aftertomm,&leizhenyu);
				}
				else if((nowui_flag == 3)&&(day == 1))
				{
					lv_img_set_src(img3_weather_today,&leizhenyu);
				}
				else if((nowui_flag == 3)&&(day == 2))
				{
					lv_img_set_src(img3_weather_tommorrow,&leizhenyu);
				}
				else if((nowui_flag == 3)&&(day == 3))
				{
					lv_img_set_src(img3_weather_aftertomm,&leizhenyu);
				}																																
																				break;			//雷阵雨
		case 13:
				strcpy(CNWord,"灏忛洦 ");		
				if(nowui_flag == 1)
				{					
					lv_img_set_src(img_weather,&xiaoyu);																	
				}
				else if((nowui_flag ==2)&&(day == 1))
				{
					lv_img_set_src(img2_weather_today,&xiaoyu);
				}
				else if((nowui_flag == 2)&&(day == 2))
				{
					lv_img_set_src(img2_weather_tommorrow,&xiaoyu);
				}
				else if((nowui_flag == 2)&&(day == 3))
				{
					lv_img_set_src(img2_weather_aftertomm,&xiaoyu);
				}
				else if((nowui_flag == 3)&&(day == 1))
				{
					lv_img_set_src(img3_weather_today,&xiaoyu);
				}
				else if((nowui_flag == 3)&&(day == 2))
				{
					lv_img_set_src(img3_weather_tommorrow,&xiaoyu);
				}
				else if((nowui_flag == 3)&&(day == 3))
				{
					lv_img_set_src(img3_weather_aftertomm,&xiaoyu);
				}																																
																				break;			//小雨
		case 14:
				strcpy(CNWord,"涓洦 ");		
				if(nowui_flag == 1)
				{					
					lv_img_set_src(img_weather,&zhongyu);																	
				}
				else if((nowui_flag ==2)&&(day == 1))
				{
					lv_img_set_src(img2_weather_today,&zhongyu);
				}
				else if((nowui_flag == 2)&&(day == 2))
				{
					lv_img_set_src(img2_weather_tommorrow,&zhongyu);
				}
				else if((nowui_flag == 2)&&(day == 3))
				{
					lv_img_set_src(img2_weather_aftertomm,&zhongyu);
				}
				else if((nowui_flag == 3)&&(day == 1))
				{
					lv_img_set_src(img3_weather_today,&zhongyu);
				}
				else if((nowui_flag == 3)&&(day == 2))
				{
					lv_img_set_src(img3_weather_tommorrow,&zhongyu);
				}
				else if((nowui_flag == 3)&&(day == 3))
				{
					lv_img_set_src(img3_weather_aftertomm,&zhongyu);
				}																															
																				break;			//中雨
		case 15:
				strcpy(CNWord,"澶ч洦 ");	
				if(nowui_flag == 1)
				{					
					lv_img_set_src(img_weather,&dayu);																	
				}
				else if((nowui_flag ==2)&&(day == 1))
				{
					lv_img_set_src(img2_weather_today,&dayu);
				}
				else if((nowui_flag == 2)&&(day == 2))
				{
					lv_img_set_src(img2_weather_tommorrow,&dayu);
				}
				else if((nowui_flag == 2)&&(day == 3))
				{
					lv_img_set_src(img2_weather_aftertomm,&dayu);
				}
				else if((nowui_flag == 3)&&(day == 1))
				{
					lv_img_set_src(img3_weather_today,&dayu);
				}
				else if((nowui_flag == 3)&&(day == 2))
				{
					lv_img_set_src(img3_weather_tommorrow,&dayu);
				}
				else if((nowui_flag == 3)&&(day == 3))
				{
					lv_img_set_src(img3_weather_aftertomm,&dayu);
				}																																
																					break;			//大雨
		case 16:
				strcpy(CNWord,"鏆撮洦 ");	
				if(nowui_flag == 1)
				{					
					lv_img_set_src(img_weather,&dayu);																	
				}
				else if((nowui_flag ==2)&&(day == 1))
				{
					lv_img_set_src(img2_weather_today,&dayu);
				}
				else if((nowui_flag == 2)&&(day == 2))
				{
					lv_img_set_src(img2_weather_tommorrow,&dayu);
				}
				else if((nowui_flag == 2)&&(day == 3))
				{
					lv_img_set_src(img2_weather_aftertomm,&dayu);
				}
				else if((nowui_flag == 3)&&(day == 1))
				{
					lv_img_set_src(img3_weather_today,&dayu);
				}
				else if((nowui_flag == 3)&&(day == 2))
				{
					lv_img_set_src(img3_weather_tommorrow,&dayu);
				}
				else if((nowui_flag == 3)&&(day == 3))
				{
					lv_img_set_src(img3_weather_aftertomm,&dayu);
				}																														
																						break;			//暴雨
		case 30:
				strcpy(CNWord,"闆� ");			
																						break;			//雾
	}
}

/*
	任务调度的思路：
	1、这里使用lvgl的任务调度功能实现类似于时间片的功能，
		相对于时间片，任务调度有优先级的概念，所以
	2、
	3、
*/




char tmpbuff[50];
//LED状态灯闪烁任务，1S闪烁一次
void Led1_TogleTask(lv_task_t * task)
{
	LED1_Toggle;
}

//采集温湿度任务
void getdht_Task(lv_task_t *task)
{
		Get_dhtdata();
		
	//	printf("temp:%d,humi:%d\r\n",dht11_data.TMP,dht11_data.HUM);
}


//页面1显示温湿度任务
void showdht_Task(lv_task_t *task)
{
	memset(tmpbuff,0,sizeof(tmpbuff));
	sprintf(tmpbuff,"%d鈩� ",dht11_data.TMP);
	lv_label_set_text(label_TEM,tmpbuff);					//显示温度

	memset(tmpbuff,0,sizeof(tmpbuff));
	sprintf(tmpbuff,"%d%%",dht11_data.HUM);
	lv_label_set_text(label_HUM,tmpbuff);					//显示湿度
}


//页面1显示时间的任务，1s刷新一次
void showtime_Task(lv_task_t *task)
{
		memset(tmpbuff,0,sizeof(tmpbuff));
		sprintf(tmpbuff,"%02d:%02d:%02d",calendar.hour,calendar.min,calendar.sec);
		lv_label_set_text(label_time, tmpbuff);					//显示时间，LVGL不支持中文，得添加中文库
		memset(tmpbuff,0,sizeof(tmpbuff));
		sprintf(tmpbuff,"%04d-%02d-%02d",calendar.w_year,calendar.w_month,calendar.w_date);
		lv_label_set_text(label_date,tmpbuff);					//显示日期
	
		memset(tmpbuff,0,sizeof(tmpbuff));
		sprintf(tmpbuff,"鏄熸湡%d ",calendar.week);
		lv_label_set_text(label_week,tmpbuff);					//显示"星期x"，x是数字格式
}

//页面1显示光强和空气质量的任务，2s刷新一次
void showLP_Task(lv_task_t *task)
{
//		printf("光照模拟值：%d\r\n",ADCValue[0]);			//采集光强和烟雾不要重复初始化，初始化之后刚开始采集到的数据误差很大
		switch(ADCValue[0]/1000)
		{
			case 0:	;
			case 1:
//				printf("光照强度：很亮\r\n");
				lv_label_set_text(label_light,"寰堜寒 ");
			break;
			
			case 2:
//				printf("光照强度：亮\r\n");
				lv_label_set_text(label_light,"浜� ");			
			break;
			
			case 3:
//				printf("光照强度：适中\r\n");		
				lv_label_set_text(label_light,"閫備腑 ");
			break;
			
			case 4:
//				printf("光照强度：暗\r\n");
				lv_label_set_text(label_light,"鏆� ");
			break;
		}
		
//		printf("烟雾模拟值：%d\r\n",ADCValue[1]);
		switch(ADCValue[1]/100)
		{
			case 0:
//				printf("空气质量：优\r\n");
				lv_label_set_text(label_ppm,"浼� ");
			break;
			
			case 1:
//				printf("空气质量：良\r\n");
				lv_label_set_text(label_ppm,"鑹� ");
			break;
			
			case 2:
//				printf("空气质量：中\r\n");
				lv_label_set_text(label_ppm,"涓� ");
			break;
			
			case 3:
//				printf("空气质量：差\r\n");
				lv_label_set_text(label_ppm,"宸� ");
			break;
			
			default:
//				printf("空气质量：特别差\r\n");
				lv_label_set_text(label_ppm,"鐗瑰埆宸� ");
		}
}



//显示天气的汉字文本
void show_weather_text(lv_task_t *task)
{
	
}



void key_Task(lv_task_t *task)
{
	switch(KEY_Check())							//检测是哪个按键按下了
	{
		case 1:
//			printf("按键1按下\r\n");
			change_flag = 1;				
		//标志位检测切换任务进行切换，防止一直重绘要切换的页面，会占用大量系统时间 
			nowui_flag++;
			if(nowui_flag == 4)
			{
				nowui_flag=1;
			}																		
																		break;
		
		case 2:	
//			printf("按键2按下\r\n");			
			if(nowui_flag == 3)		//在页面3的时候切换才会生效
			{
				change_cityflag=1;
				nowcity_flag++;
			}
			else if(nowui_flag == 2)				//页面2的时候有效
			{
//					Play_Day3("Zhengzhou",city5_weather[0].acity_weather[0].code,city5_weather[0].acity_weather[0].lowt,city5_weather[0].acity_weather[0].hight,0);
						play_XCity_xDay_weather("Zhengzhou",0);	
			}
			if(nowcity_flag == 5)
			{
				nowcity_flag = 1;
			}
			
																		break;

		case 3:	
//			printf("按键3按下\r\n");			
			if(nowui_flag == 2)
			{
//					Play_Day3("Zhengzhou",city5_weather[0].acity_weather[1].code,city5_weather[0].acity_weather[1].lowt,city5_weather[0].acity_weather[1].hight,1);
									play_XCity_xDay_weather("Zhengzhou",1);	
			}
			else if((nowui_flag == 3)&&(nowcity_flag == 1))
			{
									play_XCity_xDay_weather("Beijing",0);	
			}
			else if((nowui_flag == 3)&&(nowcity_flag == 2))
			{
									play_XCity_xDay_weather("Shanghai",0);	
			}
			else if((nowui_flag == 3)&&(nowcity_flag == 3))
			{
									play_XCity_xDay_weather("Guangzhou",0);	
			}
			else if((nowui_flag == 3)&&(nowcity_flag == 4))
			{
									play_XCity_xDay_weather("Shenzhen",0);	
			}
																		break;

		case 4:
//			printf("按键4按下\r\n");			
			if(nowui_flag == 2)
			{
//					Play_Day3("Zhengzhou",city5_weather[0].acity_weather[2].code,city5_weather[0].acity_weather[2].lowt,city5_weather[0].acity_weather[2].hight,2);
									play_XCity_xDay_weather("Zhengzhou",2);	
			}
			else if((nowui_flag == 3)&&(nowcity_flag == 1))
			{
									play_XCity_xDay_weather("Beijing",1);	
			}
			else if((nowui_flag == 3)&&(nowcity_flag == 2))
			{
									play_XCity_xDay_weather("Shanghai",1);	
			}
			else if((nowui_flag == 3)&&(nowcity_flag == 3))
			{
									play_XCity_xDay_weather("Guangzhou",1);	
			}
			else if((nowui_flag == 3)&&(nowcity_flag == 4))
			{
									play_XCity_xDay_weather("Shenzhen",1);	
			}

																		break;
	}
}

void play_XCity_xDay_weather(char *city,int i)
{
	if(strcmp(city,"Zhengzhou") == 0)
	{
			Play_Day3("Zhengzhou",city5_weather[0].acity_weather[i].code,city5_weather[0].acity_weather[i].lowt,city5_weather[0].acity_weather[i].hight,i);
	}
	else if(strcmp(city,"Beijing") == 0)
	{
			Play_Day3("Beijing",city5_weather[1].acity_weather[i].code,city5_weather[1].acity_weather[i].lowt,city5_weather[1].acity_weather[i].hight,i);
	}
		else if(strcmp(city,"Shanghai") == 0)
	{
			Play_Day3("Shanghai",city5_weather[2].acity_weather[i].code,city5_weather[2].acity_weather[i].lowt,city5_weather[2].acity_weather[i].hight,i);
	}
	else if(strcmp(city,"Guangzhou") == 0)
	{
			Play_Day3("Guangzhou",city5_weather[3].acity_weather[i].code,city5_weather[3].acity_weather[i].lowt,city5_weather[3].acity_weather[i].hight,i);
	}
	else if(strcmp(city,"Shenzhen") == 0)
	{
		Play_Day3("Shenzhen",city5_weather[4].acity_weather[i].code,city5_weather[4].acity_weather[i].lowt,city5_weather[4].acity_weather[i].hight,i);
	}
	
}





/*
	切换页面的函数，10ms检测一次，此函数其实可以放到按键检测中
	切换标志位检测函数，检测要切换显示的页面，检测是否可以切换
	nowui_flag：现在显示的页面，change_flag：是否生效当前页面
*/
void interface_change(lv_task_t *task)
{
	if((nowui_flag == 2)&&(change_flag == 1))				//切换显示页面2
	{
		change_flag = 0;
//		printf("切换到页面2\r\n");
		Del_LV_Task_interface1();				//删除页面1的刷新文本任务，否则卡死
		lv_obj_del(controot1);					//删除页面1的根容器
		Show_Interface2();							//创建页面2的根容器和显示标签
	}
	else if((nowui_flag == 3)&&(change_flag == 1))	//切换显示页面3
	{
		change_flag = 0;
		nowcity_flag = 1;
		change_cityflag = 1; 
//		printf("切换到页面1\r\n");
		lv_obj_del(controot2);
		Show_Interface3();
	}	
	else if((nowui_flag == 1)&&(change_flag == 1))		//切换显示页面1
	{
		change_flag = 0;
		lv_obj_del(controot3);
		Create_LV_Task_interface1();			//创建页面1的文本时刷新任务
		Show_Interface1();								//创建根容器和显示标签
	}
}

void change_arrow(lv_task_t *task)
{
//	if((nowcity_flag<5)&&(nowcity_flag>0))
//		if(nowui_flag == 3)
//	{
//		printf("现在的nowcity=%d",nowcity_flag);
//	}
	if((nowui_flag == 3)&&(nowcity_flag ==2)&&(change_cityflag == 1))					//指向上海		
	{
			change_cityflag = 0; 
			printf("箭头移位1\r\n");
			lv_obj_align(interface3_img2,NULL,LV_ALIGN_IN_TOP_RIGHT,-20,80);			//改变箭头指向位置
			day1_weather_show(2);
			day2_weather_show(2);
			day3_weather_show(2);
	}
	else if((nowui_flag == 3)&&(nowcity_flag ==3)&&(change_cityflag == 1))		//指向广州
	{
			change_cityflag = 0;
			printf("箭头移位2\r\n");
			lv_obj_align(interface3_img2,NULL,LV_ALIGN_IN_TOP_RIGHT,-20,120);
			day1_weather_show(3);
			day2_weather_show(3);
			day3_weather_show(3);
	}
	else if((nowui_flag == 3)&&(nowcity_flag ==4)&&(change_cityflag == 1))		//指向深圳
	{
		change_cityflag = 0;
		printf("箭头移位3\r\n");
		lv_obj_align(interface3_img2,NULL,LV_ALIGN_IN_TOP_RIGHT,-20,160);
			day1_weather_show(4);
			day2_weather_show(4);
			day3_weather_show(4);
		
	}
	else if((nowui_flag == 3)&&(nowcity_flag ==1)&&(change_cityflag == 1))		//指向郑州
	{
		change_cityflag = 0;
		printf("箭头移位4\r\n");
		lv_obj_align(interface3_img2,NULL,LV_ALIGN_IN_TOP_RIGHT,-20,40);
			day1_weather_show(1);
			day2_weather_show(1);
			day3_weather_show(1);
	}
}





//页面1显示温度的函数
void interface1_showWeather_Task(void)
{
//	//显示今日天气
	memset(tmpbuff,0,sizeof(tmpbuff));
	sprintf(tmpbuff,"%s鈩� ",city5_weather[0].acity_weather[0].hight);
	lv_label_set_text(label_weather1_hight,tmpbuff);
	
	memset(tmpbuff,0,sizeof(tmpbuff));
	sprintf(tmpbuff,"%s鈩� ",city5_weather[0].acity_weather[0].lowt);
	lv_label_set_text(label_weather1_lowt,tmpbuff);
	
	Weathercode_to_CNWord(atoi(city5_weather[0].acity_weather[0].code),1);
	lv_label_set_text(label_weather_text,CNWord);		
}

lv_obj_t *label_init_text=NULL,*controot5=NULL;
lv_style_t init_style;
//展示初始化提示文字
void show_Initwords(void)
{
	//配置样式
	lv_style_copy(&init_style,&lv_style_plain_color);			//将字体格式赋初值 这一步必须写 
	init_style.text.font = &font1;												//在样式中使用这个字体,font1是汉字字库
	init_style.text.color = LV_COLOR_BLACK;
	
    
//	controot5 = lv_label_create(lv_scr_act(), NULL);
//	lv_obj_set_size(controot5,320,240);										//设置容器的大小
//	lv_obj_align(controot5,NULL,LV_ALIGN_CENTER,0,0);			//屏幕居中对齐
//	lv_cont_set_layout(controot5,LV_LAYOUT_OFF);					//设置无布局方式
	
	/*在当前活动的屏幕上创建一个Label*/
	label_init_text = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_style(label_init_text,LV_LABEL_STYLE_MAIN,&init_style);
	lv_obj_align(label_init_text, NULL, LV_ALIGN_CENTER, -32, 0);
	lv_label_set_text(label_init_text,"loading... ");
	lv_task_handler();
}






lv_task_t *Task1_Handle = NULL;
lv_task_t *Task2_Handle = NULL;
lv_task_t *Task3_Handle = NULL;
lv_task_t *Task4_Handle = NULL;
lv_task_t *Task5_Handle = NULL;
lv_task_t *Task6_Handle = NULL;
lv_task_t *Task7_Handle = NULL;
lv_task_t *Task8_Handle = NULL;
lv_task_t *Task9_Handle = NULL;
/*
	可能用到的函数
	lv_task_ready(lv_task_t *task);	立即让相关的任务准备好执行，此次不按周期执行
*/
//系统初始化函数
void SYSTEM_Init()
{
	SysTick_Config(SystemCoreClock/1000);
	BEEP_Init();
	Led_Config();
	KEY_Init();	
	RTC_Init();					//初始化RTCs
	USART1_Config();		//串口1初始化
	USART4_Config();
	printf("系统开始运行\r\n");						//输出必须再串口配置好之后，否则会导致阻塞
	
	TFTLCD_Init();			//屏幕底层驱动初始化
	sFLASH_Init();
	lv_init();					//初始化LVGL,中间包括lvgl样式的初始化
	lv_port_disp_init();//初始化显示接口
	light_resistance_adcConfig();		//初始化ADC并获取模拟数值
	Get_dhtdata();					//先采一次温湿度，否则系统启动等待才可以显示温湿度
	show_Initwords();
}

void refresh_weather(lv_task_t *task)				//刷新天气数据
{
	Get_Weather1();
	if(!GET_City5Weather())
	{
		printf("获取5天天气失败\r\n");
//		return -1;
	}
	memset(tmpbuff,0,sizeof(tmpbuff));
	sprintf(tmpbuff,"%s鈩?",Now_temperature);
	lv_label_set_text(label_nowtemper, tmpbuff);								//当前温度

}



//创建lv任务函数，主函数开始运行一次
void Create_LV_Task(void)
{	
	lv_obj_del(label_init_text);
	Create_LV_Task_interface1();		//刷新页面1数据任务，创建之后程序需要时间执行,注意和下一个语句的搭配使用
	Show_Interface1();							//开机默认显示页面1，配置页面1的显示标签

	Task1_Handle = lv_task_create(Led1_TogleTask,1000,LV_TASK_PRIO_MID,NULL);					//闪灯任务
	Task2_Handle = lv_task_create(getdht_Task,5000,LV_TASK_PRIO_HIGH,NULL);						//采集温湿度任务
	Task5_Handle = lv_task_create(key_Task,10,LV_TASK_PRIO_HIGH,NULL);								//按键检测任务
	Task7_Handle = lv_task_create(interface_change,10,LV_TASK_PRIO_HIGH,NULL);				//检测是否需要切换页面的任务
	Task8_Handle = lv_task_create(change_arrow,10,LV_TASK_PRIO_HIGH,NULL);
	Task9_Handle = lv_task_create(refresh_weather,36000000,LV_TASK_PRIO_LOWEST,NULL);	//刷新天气数据
//	printf("\r\n用于观察的时间结点\r\n");
}

//创建页面1需要刷新的任务
void Create_LV_Task_interface1(void)
{
	Task3_Handle = lv_task_create(showtime_Task,1000,LV_TASK_PRIO_HIGHEST,NULL);			//刷新显示时间任务
	Task4_Handle = lv_task_create(showLP_Task,2000,LV_TASK_PRIO_LOWEST,NULL);					//刷新显示烟雾和光照任务
	Task6_Handle = lv_task_create(showdht_Task,5000,LV_TASK_PRIO_HIGH,NULL);					//刷新显示温湿度任务
}


//删除页面1的刷新任务，如果继续刷新文本会卡死
void Del_LV_Task_interface1(void)
{
	lv_task_del(Task3_Handle);
	lv_task_del(Task4_Handle);
	lv_task_del(Task6_Handle);
}

//void Create_LV_Task_interface3(void)
//{
//	Task8_Handle = lv_task_create(change_arrow,10,LV_TASK_PRIO_HIGH,NULL);
//}

//页面1显示函数，创建根容器，显示标签的设置
void Show_Interface1(void)
{
	lv_interface1_show_picture();				//显示首页面图片
	lv_interface1_show_time();					//显示时间
	lv_show_LP();												//显示光强和烟雾
	lv_show_dht11();										//显示温湿度
	lv_interface1_show_weather();				//显示天气
	lv_interface1_show_text();					//显示选项文字
	interface1_showWeather_Task();			//显示天气数据
}



//页面2显示函数
void Show_Interface2(void)
{
	lv_interface2_show_picture();				//显示三分屏页面
	lv_interface2_show_text();					//显示“今天 明天 后天”文本
}


void Show_Interface3(void)
{
	lv_interface3_show_picture();
	lv_interface3_show_text();
}





