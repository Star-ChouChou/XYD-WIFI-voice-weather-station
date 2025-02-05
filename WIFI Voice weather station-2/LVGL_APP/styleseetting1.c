#include "stylesetting1.h"
#include "lv_tutorial_hello_world.h"
#include "stdio.h"
#include "lcdshowtask.h"
#include "ESP8266.h"


LV_IMG_DECLARE(qing);					//晴

void day1_weather_show(int i);
void day2_weather_show(int i);
void day3_weather_show(int i);

/*
	图片备注：
	cloudy是多云图标；wifi是蓝色的WIFI图标；yunduan是背景图；shangxiafanjiantou是温度范围图标；
	location是定位图标；font1是包含ASCII码和所用汉字的字库字库样式参考的是谷歌的常规字体；
*/
//临时字符串变量
char text_setting_tmpbuff[50];


//先申明图片
//天气图片

LV_IMG_DECLARE(wifi);
LV_IMG_DECLARE(location);
LV_IMG_DECLARE(yunduan);
LV_IMG_DECLARE(shangxiafanjiantou);
LV_IMG_DECLARE(wenduji);
LV_IMG_DECLARE(shiduji);
LV_IMG_DECLARE(guangzhaoqiangdu);
LV_IMG_DECLARE(kongqizhiliang);
LV_IMG_DECLARE(dianchi);
LV_IMG_DECLARE(interface3img);
LV_IMG_DECLARE(zuojiantou);


//首先对字体进行外部声明
LV_FONT_DECLARE(font1);
LV_FONT_DECLARE(font3);				
lv_obj_t *img1=NULL,*img2=NULL,*img3=NULL,*img4=NULL,*img_weather=NULL;
lv_obj_t *controot1=NULL;
lv_style_t title0_style,contstyle1;



/*
	显示图片函数，在容器中显示图片的时候注意
	图片的覆盖规则是后出现的覆盖之前出现的，
	所以背景图要先设置，在设置小图标和文本
	再bsp_lcd.c使用Display_Dir设置屏幕方向
	***************************************
	这里的容器创建在picture函数中
	***************************************
	注意事项：!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	----------------------------------------------------------------------------
	1、在滴答定时器中要给lv任务管理一个心跳，不给心跳也会导致删除任容器失败。心跳
		频率是1ms一次，所以lv_task中任务执行频率的单位就是1ms的整数倍
	2、删除容器之后不要再对标签容器内的标签进行显示操作，否则也会导致删除容器失败。
	3、没有创建标签就对标签内容进行写入会导致页面显示异常，阻塞程序导致handler无法
		执行，会导致整个页面都无法显示。
	4、关于lv_obj_t *变量的使用，定义一个变量，创建此变量指定父类，创建之后为该变量
		设置其他的属性。这里我们的img控件和label标签都是使用该变量创建的。以label显
		示字体为例，创建之后text1变量之后，设置字体样式，设置文本对齐方式，使用
		lv_label_set_text显示文本。当我们显示下一个文本的时候如果仅仅还使用上一个文
		本的lv_obj_t *text1变量再设置样式，就会导致第一个显示的文本消失。这里的操作
		本质是，再次对第一次创建的label进行样式设置，再次使用set_text显示文本，那么
		第一个操作就被“覆盖”掉了，即只有第二个操作生效了（不是位置上的覆盖）。如果以
		后我们不再对该文本进行修改，那就可以再次使用text1接收一个新的create创建结果，
		这里的text1是一个新的变量，不再与之前的文本显示相关联了，上一个文本设置和显示
		已经完成，开始了一个新的文本设置。img控件变量的使用与此相同，直接使用创建的img
		变量会导致只有后面设置的图片操作有效。
	5、对lv_style_t样式进行设置的时候，也是后设置的会覆盖先设置的。
	6、实现滚动的时候。先设置滚动模式再设置标签大小，否则可能会失效。
	7、lv_label_set_text函数设置文本的时候，如果是字符串变量直接放到指定参数位置即可，
		如果是“”内手动输入的文本子需要输入UTF-8编码格式的文本。可以调整编译器的编码格式
		为UTF-8进行输入，或者使用转换工具得到UTF-8类型的编码写入。
	8、如果一个lv_obj_t *类型的控件没有create就去设置样式并且生效会导致阻塞，一旦阻塞
		会导致整个显示出现问题，即整个显示页面不再显示。主函数中的handle无法及时运行
	----------------------------------------------------------------------------
*/
//页面1显示图片，创建根容器1****************************************************************************************************************
void lv_interface1_show_picture(void)
{
	//设置容器样式
	lv_style_copy(&contstyle1,&lv_style_plain_color);
	contstyle1.body.main_color = LV_COLOR_WHITE;
	contstyle1.body.grad_color = LV_COLOR_WHITE;					//设置容器的颜色
	
	
	controot1 = lv_cont_create(lv_scr_act(),NULL);				//创建容器
	lv_obj_set_style(controot1,&contstyle1);							//设置容器样式
	lv_obj_set_size(controot1,320,240);										//设置容器的大小
	lv_obj_align(controot1,NULL,LV_ALIGN_CENTER,0,0);			//屏幕居中对齐
	lv_cont_set_layout(controot1,LV_LAYOUT_OFF);					//设置无布局方式
	
	img2 = lv_img_create(controot1,NULL);							
	lv_img_set_src(img2,&yunduan);
	lv_obj_align(img2,NULL,LV_ALIGN_CENTER,0,0);					//显示背景图
	
	
	img2 = lv_img_create(controot1,NULL);										
	lv_img_set_src(img2,&wifi);
	lv_obj_align(img2,NULL,LV_ALIGN_IN_TOP_RIGHT,0,0);		//显示WIFI图标
//	
	img2 = lv_img_create(controot1,NULL);
	lv_img_set_src(img2,&location);
	lv_obj_align(img2,NULL,LV_ALIGN_IN_TOP_LEFT,0,16);		//显示定位图标
	
	img_weather = lv_img_create(controot1,NULL);
	lv_obj_align(img_weather,NULL,LV_ALIGN_IN_TOP_RIGHT,-16,16);		//显示天气图标
	
	img2 = lv_img_create(controot1,NULL);
	lv_img_set_src(img2,&shangxiafanjiantou);
	lv_obj_align(img2,NULL,LV_ALIGN_IN_TOP_MID,50,40);				//显示双向箭头图标
	
	img2 = lv_img_create(controot1,NULL);
	lv_img_set_src(img2,&wenduji);
	lv_obj_align(img2,NULL,LV_ALIGN_IN_LEFT_MID,5,-32);				//显示温度计图标
	
	img2 = lv_img_create(controot1,NULL);
	lv_img_set_src(img2,&shiduji);
	lv_obj_align(img2,NULL,LV_ALIGN_IN_LEFT_MID,5,0);				//显示湿度计图标
	
	img2 = lv_img_create(controot1,NULL);
	lv_img_set_src(img2,&guangzhaoqiangdu);
	lv_obj_align(img2,NULL,LV_ALIGN_IN_LEFT_MID,5,32);				//显示光照强度图标
	
	img2 = lv_img_create(controot1,NULL);
	lv_img_set_src(img2,&kongqizhiliang);
	lv_obj_align(img2,NULL,LV_ALIGN_IN_LEFT_MID,5,64);				//显示空气质量图标
	
	img2 = lv_img_create(controot1,NULL);
	lv_img_set_src(img2,&dianchi);
	lv_obj_align(img2,NULL,LV_ALIGN_IN_TOP_RIGHT,-32,0);				//显示电池图标
	
}


lv_obj_t *label_time = NULL;
lv_obj_t *label_date = NULL,*label_week;
lv_style_t date_style,date_style2;
//lv_obj_t *label_test = NULL;
//显示时间标签函数****************************************************************************************************************
void lv_interface1_show_time(void)
{
	//配置样式
	lv_style_copy(&date_style,&lv_style_plain_color);			//将字体格式赋初值 这一步必须写 
	date_style.text.font = &font1;												//在样式中使用这个字体,font1是汉字字库
	date_style.text.color = LV_COLOR_BLACK;
	
	
	lv_style_copy(&date_style2,&lv_style_plain_color);			//将字体格式赋初值 这一步必须写 
	date_style2.text.font = &font3;												//在样式中使用这个字体,font1是汉字字库
	date_style2.text.color = LV_COLOR_RED;
    /*在当前活动的屏幕上创建一个Label*/
	//显示时分秒
	label_time = lv_label_create(controot1, NULL);
	lv_label_set_style(label_time,LV_LABEL_STYLE_MAIN,&date_style2);
	lv_obj_align(label_time, NULL, LV_ALIGN_IN_TOP_LEFT, 35, 20);
	
	//显示年月日
	label_date = lv_label_create(controot1,NULL);
	lv_label_set_style(label_date,LV_LABEL_STYLE_MAIN,&date_style);
	lv_obj_align(label_date, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);
	
		//显示周几
	label_week = lv_label_create(controot1,NULL);
	lv_label_set_style(label_week,LV_LABEL_STYLE_MAIN,&date_style);
	lv_obj_align(label_week, label_time, LV_ALIGN_OUT_BOTTOM_MID, 40, 0 );
	
	lv_task_ready(Task3_Handle);
		//label_test = lv_label_create(controot1,NULL);
	/* Align the Label to the center
     * NULL means align on parent (which is the screen now)
     * 0, 0 at the end means an x, y offset after alignment
		 *	将标签对齐到中心
		 * NULL意味着对齐父母(这是现在的屏幕)
		 * 0,0在末尾表示在对齐后的x, y偏移量
	*/
		//lv_obj_align(label_test, NULL, LV_ALIGN_IN_TOP_MID, 128, 0);
		
/*
	Modify the Label's text（修改Label的文本），在主函数中可继续使用该函数
	修改文本，这里的文本和前面字库生成的文本显示方式是不一样的，这里文本不
	会有单独的矩形的背景出现在屏幕上，只有要显示的文字出现。
*/
}


lv_obj_t *label_weather1_hight = NULL,*label_weather1_lowt=NULL,*label_weather2 = NULL,*label_weather3 = NULL;
lv_obj_t *label_weather_text=NULL;		//天气文本显示标签
//页面1显示天气文本****************************************************************************************************************
void lv_interface1_show_weather(void)
{
    label_weather1_hight =  lv_label_create(controot1, NULL);						//创建高温标签
		lv_label_set_style(label_weather1_hight,LV_LABEL_STYLE_MAIN,&date_style);
		lv_obj_align(label_weather1_hight, NULL, LV_ALIGN_IN_TOP_MID,50,26);						
	
	  label_weather1_lowt =  lv_label_create(controot1, NULL);						//创建低温标签
		lv_label_set_style(label_weather1_lowt,LV_LABEL_STYLE_MAIN,&date_style);
		lv_obj_align(label_weather1_lowt, NULL, LV_ALIGN_IN_TOP_MID,50,66);

		label_weather_text =  lv_label_create(controot1, NULL);						//创建文本显示标签
		lv_label_set_style(label_weather_text,LV_LABEL_STYLE_MAIN,&date_style);
		lv_obj_align(label_weather_text, img_weather, LV_ALIGN_OUT_BOTTOM_MID,0,10);			//参照天气图标位置设置文本
		
	
//		label_weather2 = lv_label_create(controot1,NULL);
//    lv_obj_align(label_weather2, NULL, LV_ALIGN_IN_LEFT_MID, 0, 16);
//	
//		label_weather3 = lv_label_create(controot1,NULL);
//    lv_obj_align(label_weather3, NULL, LV_ALIGN_IN_LEFT_MID, 0, 32);
}




lv_obj_t *label_text1=NULL,*label_text2=NULL,*label_nowtemper=NULL;
lv_style_t city_style,text_style1;

/*
	页面1的文本显示****************************************************************************************************************
*/
void lv_interface1_show_text(void)
{
	//配置样式
	lv_style_copy(&city_style,&lv_style_plain_color);			//将字体格式赋初值 这一步必须写 
	city_style.text.font = &font1;												//在样式中使用这个字体,font1是汉字字库
	city_style.text.color = LV_COLOR_RED; 
 
	
	//设置文本
	label_text1 = lv_label_create(controot1, NULL);	
	lv_label_set_style(label_text1,LV_LABEL_STYLE_MAIN,&city_style); 
	lv_obj_align(label_text1, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 45); 
	lv_label_set_text(label_text1, "閮戝窞");							//显示汉字郑州
	//lv_label_set_text(title0,"\xE8\xAF\xAD\xE9\x9F\xB3\xE6\xB0\x94\xE8\xB1\xA1\xE7\xAB\x99");
	
	//配置样式
	lv_style_copy(&text_style1,&lv_style_plain_color);			//将字体格式赋初值 这一步必须写 
	text_style1.text.font = &font3;												//在样式中使用这个字体,font1是汉字字库
	text_style1.text.color = LV_COLOR_RED;
	
	//设置文本
//	label_text2 = lv_label_create(controot1, NULL); 
//	lv_label_set_style(label_text2,LV_LABEL_STYLE_MAIN,&text_style1); 
//	lv_obj_align(label_text2, NULL, LV_ALIGN_CENTER, -48, -17); 
//	lv_label_set_text(label_text2, "1銆佷富椤甸潰 ");			//“主页面”文字
//	
//	label_text2 = lv_label_create(controot1, NULL); 
//	lv_label_set_style(label_text2,LV_LABEL_STYLE_MAIN,&text_style1); 
//	lv_obj_align(label_text2, NULL, LV_ALIGN_CENTER, -48,0); 
//	lv_label_set_text(label_text2, "2銆佷笁澶╁ぉ姘� ");			//“三天天气”文字
//	
//	label_text2 = lv_label_create(controot1, NULL); 
//	lv_label_set_style(label_text2,LV_LABEL_STYLE_MAIN,&text_style1); 
//	lv_obj_align(label_text2, NULL, LV_ALIGN_CENTER, -48,17); 
//	lv_label_set_text(label_text2, "3銆佸鍐呯幆澧� ");			//“室内环境”文字
	
	memset(tmpbuff,0,sizeof(tmpbuff));
	sprintf(tmpbuff,"%s鈩� ",Now_temperature);
	
	label_nowtemper = lv_label_create(controot1, NULL); 
	lv_label_set_style(label_nowtemper,LV_LABEL_STYLE_MAIN,&text_style1); 
	lv_obj_align(label_nowtemper, NULL, LV_ALIGN_IN_TOP_MID,80,100); 		
	lv_label_set_text(label_nowtemper, tmpbuff);								//当前温度 

}

lv_obj_t *label_HUM=NULL,*label_TEM=NULL;
//页面1显示温湿度函数*************************************************************************************
void lv_show_dht11(void)
{
//	lv_style_copy(&city_style,&lv_style_plain_color);			//将字体格式赋初值 这一步必须写 
//	city_style.text.font = &font1;												//在样式中使用这个字体,font1是汉字字库
//	city_style.text.color = LV_COLOR_BLACK; 
	 
	label_TEM = lv_label_create(controot1, NULL);
	lv_label_set_style(label_TEM,LV_LABEL_STYLE_MAIN,&city_style); 
	lv_obj_align(label_TEM, NULL, LV_ALIGN_IN_LEFT_MID, 37, -35);
	
	//设置文本
	label_HUM = lv_label_create(controot1, NULL);
	lv_label_set_style(label_HUM,LV_LABEL_STYLE_MAIN,&city_style); 
	lv_obj_align(label_HUM, NULL, LV_ALIGN_IN_LEFT_MID, 37, -3); 
	
	
	//生成标签之后就立即赋值一次，防止卡顿
		lv_task_ready(Task6_Handle);
//	memset(text_setting_tmpbuff,0,sizeof(text_setting_tmpbuff));
//	sprintf(text_setting_tmpbuff,"%d鈩?",dht11_data.TMP);
//	lv_label_set_text(label_TEM,text_setting_tmpbuff);					//显示温度

//	memset(text_setting_tmpbuff,0,sizeof(text_setting_tmpbuff));
//	sprintf(text_setting_tmpbuff,"%d%%",dht11_data.HUM);
//	lv_label_set_text(label_HUM,text_setting_tmpbuff);					//显示湿度				
}


lv_obj_t *label_light=NULL,*label_ppm=NULL;
lv_style_t LP_style;
//显示光照强度和空气质量
void lv_show_LP(void)
{
		//配置样式
	lv_style_copy(&LP_style,&lv_style_plain_color);			//将字体格式赋初值 这一步必须写 
	LP_style.text.font = &font1;												//在样式中使用这个字体,font1是汉字字库
	LP_style.text.color = LV_COLOR_RED;
	
	label_light = lv_label_create(controot1, NULL);
	lv_label_set_style(label_light,LV_LABEL_STYLE_MAIN,&city_style); 
	lv_obj_align(label_light, NULL, LV_ALIGN_IN_LEFT_MID, 37,29);
	
	//设置文本
	label_ppm = lv_label_create(controot1, NULL);
	lv_label_set_style(label_ppm,LV_LABEL_STYLE_MAIN,&city_style); 
	lv_obj_align(label_ppm, NULL, LV_ALIGN_IN_LEFT_MID, 37,61); 
	

	lv_task_ready(Task4_Handle);
}	




LV_IMG_DECLARE(xiaotu1);			//先申明此图片
LV_IMG_DECLARE(xiaotu2);
LV_IMG_DECLARE(xiaotu3);



lv_style_t contstyle2;				
lv_obj_t *controot2=NULL,*interface2_img1=NULL,*interface2_img2=NULL,*interface2_img3=NULL;
lv_obj_t *img2_weather_today=NULL,*img2_weather_tommorrow=NULL,*img2_weather_aftertomm=NULL;
/*
	在页面2实现的过程中，页面被分了三份，这里分别填充了三张大小一致的图片
	每张图片都是一个容器，容器名就是图片的obj类型的变量。（注意：这里图片可以理解为一个容器）
*/
//页面2的根容器创建和图片显示*******************************************************************************************************************————————————————————————————————————
void lv_interface2_show_picture(void)
{
	//设置容器样式
	lv_style_copy(&contstyle2,&lv_style_plain_color);
	contstyle2.body.main_color = LV_COLOR_WHITE;
	contstyle2.body.grad_color = LV_COLOR_WHITE;					//设置容器的颜色
	
	controot2 = lv_cont_create(lv_scr_act(),NULL);				//创建容器
	lv_obj_set_style(controot2,&contstyle2);							//设置容器样式	
	lv_obj_set_size(controot2,320,240);										//设置容器的大小
	lv_obj_align(controot2,NULL,LV_ALIGN_CENTER,0,0);			//屏幕居中对齐
	lv_cont_set_layout(controot2,LV_LAYOUT_OFF);					//设置无布局方式
	
	interface2_img1 = lv_img_create(controot2,NULL);							
	lv_img_set_src(interface2_img1,&xiaotu1);
	lv_obj_align(interface2_img1,NULL,LV_ALIGN_IN_BOTTOM_LEFT,0,0);					//显示背景图
	
	interface2_img2 = lv_img_create(controot2,NULL);										
	lv_img_set_src(interface2_img2,&xiaotu2);
	lv_obj_align(interface2_img2,NULL,LV_ALIGN_IN_LEFT_MID,107,0);

	interface2_img3 = lv_img_create(controot2,NULL);
	lv_img_set_src(interface2_img3,&xiaotu3);	
	lv_obj_align(interface2_img3,NULL,LV_ALIGN_IN_LEFT_MID,212,0);
	
	img2_weather_today = lv_img_create(controot2,NULL);	
//	lv_img_set_src(img2_weather_today,&qing);
	lv_obj_align(img2_weather_today,NULL,LV_ALIGN_IN_TOP_LEFT,30,95);
	
	img2_weather_tommorrow = lv_img_create(interface2_img2,NULL);	
	lv_obj_align(img2_weather_tommorrow,NULL,LV_ALIGN_IN_TOP_MID,-10,95);
//		lv_img_set_src(img2_weather_tommorrow,&qing);

	
	img2_weather_aftertomm = lv_img_create(interface2_img3,NULL);	
	lv_obj_align(img2_weather_aftertomm,NULL,LV_ALIGN_IN_TOP_MID,-10,95);
//		lv_img_set_src(img2_weather_aftertomm,&qing);

	
	
}

//lv_obj_t *label_weather2_hight=NULL;
//void lv_interface2_show_weather(void)
//{
//		label_weather2_hight =  lv_label_create(controot1, NULL);						//创建高温标签
//		lv_label_set_style(label_weather2_hight,LV_LABEL_STYLE_MAIN,&date_style);
//		lv_obj_align(label_weather2_hight, NULL, LV_ALIGN_IN_TOP_MID,50,26);						
//	
////	  label_weather1_lowt =  lv_label_create(controot1, NULL);						//创建低温标签
////		lv_label_set_style(label_weather1_lowt,LV_LABEL_STYLE_MAIN,&date_style);
////		lv_obj_align(label_weather1_lowt, NULL, LV_ALIGN_IN_TOP_MID,50,66);
//}

lv_style_t three_day_Words;
//页面2显示文本函数****************************************************************************************
void lv_interface2_show_text()
{
	//配置字体样式
	lv_style_copy(&three_day_Words,&lv_style_plain_color);			//将字体格式赋初值 这一步必须写 
	three_day_Words.text.font = &font1;												//在样式中使用这个字体,font1是汉字字库
	three_day_Words.text.color = LV_COLOR_GREEN;
	
	//设置文本
	label_text2 = lv_label_create(lv_scr_act(), NULL); 
	lv_label_set_style(label_text2,LV_LABEL_STYLE_MAIN,&three_day_Words); 
	lv_obj_align(label_text2, NULL, LV_ALIGN_IN_TOP_LEFT, 30, 30); 
	lv_label_set_text(label_text2, "浠婂ぉ ");			//“今天”文字
	
	//设置温度文本
	label_text2 = lv_label_create(lv_scr_act(), NULL); 
	lv_label_set_style(label_text2,LV_LABEL_STYLE_MAIN,&three_day_Words); 
	lv_obj_align(label_text2, NULL, LV_ALIGN_IN_TOP_LEFT, 30, 50); 
	memset(text_setting_tmpbuff,0,sizeof(text_setting_tmpbuff));
	sprintf(text_setting_tmpbuff,"%s/%s鈩� ",city5_weather[0].acity_weather[0].lowt,city5_weather[0].acity_weather[0].hight);
	lv_label_set_text(label_text2, text_setting_tmpbuff);			//今天温度
	
	//设置天气文本
	label_text2 = lv_label_create(lv_scr_act(), NULL); 
	lv_label_set_style(label_text2,LV_LABEL_STYLE_MAIN,&three_day_Words); 
	lv_obj_align(label_text2, NULL, LV_ALIGN_IN_TOP_LEFT, 30, 70); 
	Weathercode_to_CNWord(atoi(city5_weather[0].acity_weather[0].code),1);
	lv_label_set_text(label_text2, CNWord);			//今天天气
	
	//设置文本
	label_text2 = lv_label_create(interface2_img2, NULL); 
	lv_label_set_style(label_text2,LV_LABEL_STYLE_MAIN,&three_day_Words); 
	lv_obj_align(label_text2, NULL, LV_ALIGN_IN_TOP_MID,0,30); 
	lv_label_set_text(label_text2, "鏄庡ぉ ");			//“明天”文字
	
	//设置温度文本
	label_text2 = lv_label_create(interface2_img2, NULL); 
	lv_label_set_style(label_text2,LV_LABEL_STYLE_MAIN,&three_day_Words); 
	lv_obj_align(label_text2, NULL, LV_ALIGN_IN_TOP_MID, 0, 50); 
	memset(text_setting_tmpbuff,0,sizeof(text_setting_tmpbuff));
	sprintf(text_setting_tmpbuff,"%s/%s鈩� ",city5_weather[0].acity_weather[1].lowt,city5_weather[0].acity_weather[1].hight);
	lv_label_set_text(label_text2,text_setting_tmpbuff );			//明天温度
	
	//设置天气文本
	label_text2 = lv_label_create(interface2_img2, NULL); 
	lv_label_set_style(label_text2,LV_LABEL_STYLE_MAIN,&three_day_Words); 
	lv_obj_align(label_text2, NULL, LV_ALIGN_IN_TOP_MID, 0, 70); 
	Weathercode_to_CNWord(atoi(city5_weather[0].acity_weather[1].code),2);
	lv_label_set_text(label_text2, CNWord);			//明天天气
	
	
	//设置文本
	label_text2 = lv_label_create(interface2_img3, NULL); 
	lv_label_set_style(label_text2,LV_LABEL_STYLE_MAIN,&three_day_Words); 
	lv_obj_align(label_text2, NULL, LV_ALIGN_IN_TOP_MID,0, 30); 
	lv_label_set_text(label_text2, "鍚庡ぉ ");			//“后天”文字
	
	//设置温度文本
	label_text2 = lv_label_create(interface2_img3, NULL); 
	lv_label_set_style(label_text2,LV_LABEL_STYLE_MAIN,&three_day_Words); 
	lv_obj_align(label_text2, NULL, LV_ALIGN_IN_TOP_MID, 0, 50); 
	memset(text_setting_tmpbuff,0,sizeof(text_setting_tmpbuff));
	sprintf(text_setting_tmpbuff,"%s/%s鈩� ",city5_weather[0].acity_weather[2].lowt,city5_weather[0].acity_weather[2].hight);
	lv_label_set_text(label_text2, text_setting_tmpbuff);			//后天温度

	//设置天气文本
	label_text2 = lv_label_create(interface2_img3, NULL); 
	lv_label_set_style(label_text2,LV_LABEL_STYLE_MAIN,&three_day_Words); 
	lv_obj_align(label_text2, NULL, LV_ALIGN_IN_TOP_MID, 0, 70); 
	Weathercode_to_CNWord(atoi(city5_weather[0].acity_weather[2].code),3);
	lv_label_set_text(label_text2, CNWord);			//后天天气
	
	//设置页面2的提示文本
	label_text2 = lv_label_create(controot2, NULL); 
	lv_label_set_style(label_text2,LV_LABEL_STYLE_MAIN,&three_day_Words); 
	lv_obj_align(label_text2, NULL, LV_ALIGN_IN_TOP_MID, -64,5); 
	lv_label_set_text(label_text2, "鏈�杩戜笁澶╁ぉ姘斿睍绀� ");			//“最近三天天气展示”文本显示
	
//		//设置文本显示几天年
//	label_text2 = lv_label_create(interface2_img3, NULL); 
//	lv_label_set_style(label_text2,LV_LABEL_STYLE_MAIN,&three_day_Words); 
//	lv_obj_align(label_text2, NULL, LV_ALIGN_IN_TOP_MID,0, 20); 
	
}


lv_obj_t *img3_weather_today=NULL,*img3_weather_tommorrow=NULL,*img3_weather_aftertomm=NULL;
lv_obj_t *controot3=NULL,*interface3_img1=NULL,*interface3_img2=NULL;
//页面3根容器创建和图片显示****************************************************************************************************——————————————————————————————————————————————————————
void lv_interface3_show_picture(void)
{
	controot3 = lv_cont_create(lv_scr_act(),NULL);				//创建容器

	lv_obj_set_size(controot3,320,240);										//设置容器的大小
	lv_obj_align(controot3,NULL,LV_ALIGN_CENTER,0,0);			//屏幕居中对齐
	lv_cont_set_layout(controot3,LV_LAYOUT_OFF);					//设置无布局方式
	
	interface3_img1 = lv_img_create(controot3,NULL);										
	lv_img_set_src(interface3_img1,&yunduan);
	lv_obj_align(interface3_img1,NULL,LV_ALIGN_IN_TOP_LEFT,0,0);
	
	interface3_img2 = lv_img_create(controot3,NULL);										
	lv_img_set_src(interface3_img2,&zuojiantou);
	lv_obj_align(interface3_img2,NULL,LV_ALIGN_IN_TOP_RIGHT,-20,40);
	
	
	img3_weather_today = lv_img_create(controot3,NULL);	
//	lv_img_set_src(img3_weather_today,&qing);
	lv_obj_align(img3_weather_today,NULL,LV_ALIGN_IN_BOTTOM_LEFT,20,-30);
	
	img3_weather_tommorrow = lv_img_create(controot3,NULL);	
	lv_obj_align(img3_weather_tommorrow,img3_weather_today,LV_ALIGN_OUT_RIGHT_MID,25,0);
//		lv_img_set_src(img3_weather_tommorrow,&qing);

	
	img3_weather_aftertomm = lv_img_create(controot3,NULL);	
	lv_obj_align(img3_weather_aftertomm,img3_weather_tommorrow,LV_ALIGN_OUT_RIGHT_MID,25,0);
//		lv_img_set_src(img3_weather_aftertomm,&qing);
}



lv_style_t city4_style;
lv_obj_t *label3_text1=NULL,*label3_text2=NULL,*label3_text3=NULL;
lv_obj_t *label3_today=NULL,*label3_tommorrow=NULL,*label3_aftertomm=NULL;
lv_obj_t *label3_todayCN=NULL,*label3_tommorrowCN=NULL,*label3_aftertommCN=NULL;
void lv_interface3_show_text(void)
{
	//配置字体样式
	lv_style_copy(&city4_style,&lv_style_plain_color);			//将字体格式赋初值 这一步必须写 
	city4_style.text.font = &font1;												//在样式中使用这个字体,font1是汉字字库
	city4_style.text.color = LV_COLOR_RED;
	
	//设置文本
	label3_text1 = lv_label_create(controot3, NULL); 
	lv_label_set_style(label3_text1,LV_LABEL_STYLE_MAIN,&city4_style); 
	lv_obj_align(label3_text1, NULL, LV_ALIGN_IN_TOP_RIGHT, -40, 40); 
	lv_label_set_text(label3_text1, "鍖椾含 ");			//“北京”文字
	
	//设置文本
	label3_text2 = lv_label_create(controot3, NULL); 
	lv_label_set_style(label3_text2,LV_LABEL_STYLE_MAIN,&city4_style); 
	lv_obj_align(label3_text2, label3_text1, LV_ALIGN_IN_BOTTOM_MID, 0, 40); 
	lv_label_set_text(label3_text2, "涓婃捣 ");			//“上海”文字
	
	//设置文本
	label3_text2 = lv_label_create(controot3, NULL); 
	lv_label_set_style(label3_text2,LV_LABEL_STYLE_MAIN,&city4_style); 
	lv_obj_align(label3_text2, label3_text1, LV_ALIGN_IN_BOTTOM_MID, 0, 80); 
	lv_label_set_text(label3_text2, "骞垮窞 ");			//“广州”文字
	
	//设置文本
	label3_text2 = lv_label_create(controot3, NULL); 
	lv_label_set_style(label3_text2,LV_LABEL_STYLE_MAIN,&city4_style); 
	lv_obj_align(label3_text2, label3_text1, LV_ALIGN_IN_BOTTOM_MID, 0, 120); 
	lv_label_set_text(label3_text2, "娣卞湷 ");			//“深圳”文字
	
		//设置文本
	label3_text2 = lv_label_create(controot3, NULL); 
	lv_label_set_style(label3_text2,LV_LABEL_STYLE_MAIN,&city4_style); 
	lv_obj_align(label3_text2, NULL, LV_ALIGN_IN_TOP_MID, -80, 0); 
	lv_label_set_text(label3_text2, "鍏ㄥ浗涓昏鍩庡競澶╂皵灞曠ず ");			//“全国主要天气展示”文字
	
	//设置文本
	label3_text2 = lv_label_create(controot3, NULL); 
	lv_label_set_style(label3_text2,LV_LABEL_STYLE_MAIN,&city4_style); 
	lv_obj_align(label3_text2, NULL, LV_ALIGN_IN_TOP_LEFT, 20, 50); 
	lv_label_set_text(label3_text2, "浠婂ぉ ");														//“今天”文字
	
	//设置文本
	label3_text3 = lv_label_create(controot3, NULL); 
	lv_label_set_style(label3_text3,LV_LABEL_STYLE_MAIN,&city4_style); 
	lv_obj_align(label3_text3, label3_text2, LV_ALIGN_OUT_RIGHT_MID, 40, 0); 
	lv_label_set_text(label3_text3, "鏄庡ぉ ");			//“明天”文字
	
	//设置文本
	label3_text3 = lv_label_create(controot3, NULL); 
	lv_label_set_style(label3_text3,LV_LABEL_STYLE_MAIN,&city4_style); 
	lv_obj_align(label3_text3, label3_text2, LV_ALIGN_OUT_RIGHT_MID, 100, 0); 
	lv_label_set_text(label3_text3, "鍚庡ぉ ");			//“后天”文字

	//设置温度文本
	label3_today = lv_label_create(controot3, NULL); 
	lv_label_set_style(label3_today,LV_LABEL_STYLE_MAIN,&city4_style); 
	lv_obj_align(label3_today, label3_text2, LV_ALIGN_IN_BOTTOM_MID, 0, 30);
//	memset(text_setting_tmpbuff,0,sizeof(text_setting_tmpbuff));
//	sprintf(text_setting_tmpbuff,"%s/%s鈩� ",city5_weather[1].acity_weather[0].lowt,city5_weather[1].acity_weather[0].hight);	
//	lv_label_set_text(label3_today, text_setting_tmpbuff);									//今天温度
	
		//设置温度文本
	label3_tommorrow = lv_label_create(controot3, NULL); 
	lv_label_set_style(label3_tommorrow,LV_LABEL_STYLE_MAIN,&city4_style); 
	lv_obj_align(label3_tommorrow, label3_today, LV_ALIGN_OUT_RIGHT_MID, 40, 0);
//	memset(text_setting_tmpbuff,0,sizeof(text_setting_tmpbuff));
//	sprintf(text_setting_tmpbuff,"%s/%s鈩� ",city5_weather[1].acity_weather[1].lowt,city5_weather[1].acity_weather[1].hight);	
//	lv_label_set_text(label3_tommorrow, text_setting_tmpbuff);									//明天温度
	
		//设置温度文本
	label3_aftertomm = lv_label_create(controot3, NULL); 
	lv_label_set_style(label3_aftertomm,LV_LABEL_STYLE_MAIN,&city4_style); 
	lv_obj_align(label3_aftertomm, label3_today, LV_ALIGN_OUT_RIGHT_MID, 100, 0);
//	memset(text_setting_tmpbuff,0,sizeof(text_setting_tmpbuff));
//	sprintf(text_setting_tmpbuff,"%s/%s鈩� ",city5_weather[1].acity_weather[2].lowt,city5_weather[1].acity_weather[2].hight);		
//	lv_label_set_text(label3_aftertomm, text_setting_tmpbuff);									//后天温度
	
	//设置天气中文文本
	label3_todayCN = lv_label_create(controot3, NULL); 
	lv_label_set_style(label3_todayCN,LV_LABEL_STYLE_MAIN,&city4_style); 
	lv_obj_align(label3_todayCN, label3_today, LV_ALIGN_OUT_BOTTOM_MID, 0, 30);
//	Weathercode_to_CNWord(atoi(city5_weather[1].acity_weather[0].code));
//	lv_label_set_text(label3_todayCN, CNWord);																//今天天气文本
	
		//设置天气中文文本
	label3_tommorrowCN = lv_label_create(controot3, NULL); 
	lv_label_set_style(label3_tommorrowCN,LV_LABEL_STYLE_MAIN,&city4_style); 
	lv_obj_align(label3_tommorrowCN, label3_todayCN, LV_ALIGN_OUT_RIGHT_MID, 40, 0);
//	Weathercode_to_CNWord(atoi(city5_weather[1].acity_weather[1].code));
//	lv_label_set_text(label3_tommorrowCN, CNWord);														//明天天气文本

	//设置天气中文文本
	label3_aftertommCN = lv_label_create(controot3, NULL); 
	lv_label_set_style(label3_aftertommCN,LV_LABEL_STYLE_MAIN,&city4_style); 
	lv_obj_align(label3_aftertommCN, label3_todayCN, LV_ALIGN_OUT_RIGHT_MID, 100, 0);
//	Weathercode_to_CNWord(atoi(city5_weather[1].acity_weather[2].code));
//	lv_label_set_text(label3_aftertommCN, CNWord);														//后天天气文本
	
	//切换到该页面的时候默认显示北京天气，后续可手动切换
	day1_weather_show(1);
	day2_weather_show(1);
	day3_weather_show(1);


	
}

/*===城市参数对照表===
			i值			城市
			1				北京
			2				上海
			3				广州
			4				深圳
*/
//展示第i个城市第一天的温度和中文天气文本
void day1_weather_show(int i)
{
	memset(text_setting_tmpbuff,0,sizeof(text_setting_tmpbuff));
	sprintf(text_setting_tmpbuff,"%s/%s鈩� ",city5_weather[i].acity_weather[0].lowt,city5_weather[i].acity_weather[0].hight);	
	lv_label_set_text(label3_today, text_setting_tmpbuff);
	Weathercode_to_CNWord(atoi(city5_weather[i].acity_weather[0].code),1);
	lv_label_set_text(label3_todayCN, CNWord);								//今天天气
}


//展示第i个城市第二天的温度和中文天气文本
void day2_weather_show(int i)
{
		memset(text_setting_tmpbuff,0,sizeof(text_setting_tmpbuff));
	sprintf(text_setting_tmpbuff,"%s/%s鈩� ",city5_weather[i].acity_weather[1].lowt,city5_weather[i].acity_weather[1].hight);	
	lv_label_set_text(label3_tommorrow, text_setting_tmpbuff);
	Weathercode_to_CNWord(atoi(city5_weather[i].acity_weather[1].code),2);
	lv_label_set_text(label3_tommorrowCN, CNWord);														//明天天气文本
}


//展示第i个城市第三天的温度和中文天气文本
void day3_weather_show(int i)
{
	memset(text_setting_tmpbuff,0,sizeof(text_setting_tmpbuff));
	sprintf(text_setting_tmpbuff,"%s/%s鈩� ",city5_weather[i].acity_weather[2].lowt,city5_weather[i].acity_weather[2].hight);		
	lv_label_set_text(label3_aftertomm, text_setting_tmpbuff);
	Weathercode_to_CNWord(atoi(city5_weather[i].acity_weather[2].code),3);
	lv_label_set_text(label3_aftertommCN, CNWord);														//后天天气文本	

}

void lv_interface4_show_picture(void)
{
	controot3 = lv_cont_create(lv_scr_act(),NULL);				//创建容器

	lv_obj_set_size(controot3,320,240);										//设置容器的大小
	lv_obj_align(controot3,NULL,LV_ALIGN_CENTER,0,0);			//屏幕居中对齐
	lv_cont_set_layout(controot3,LV_LAYOUT_OFF);					//设置无布局方式
	
	interface3_img1 = lv_img_create(controot3,NULL);										
	lv_img_set_src(interface3_img1,&yunduan);
	lv_obj_align(interface3_img1,NULL,LV_ALIGN_IN_TOP_LEFT,0,0);

}



