#define START_NUM  10000000		//开始ID

#ifdef _DEBUG_
#define SUM_NUM 10
#else
#define SUM_NUM	10000		//总数
#endif

#define DestIp "59.151.18.26"			//www.jiayuan.com
#define DestPort 80
#define SLEEP_TIME 20

struct var{
	char *front;
	char *end;
	char *f_str;
	char *e_str;
};

char CR[]={0x0D,0x0A,0x0};				//回车
struct var req_args[]={
	{"个人资料_",	"（",	"个人资料_",	"（"},		//0.	//网名
	{"佳缘ID:",	"）",	"佳缘ID:",	"）"},				//1.	//ID
	{"member_name","岁","member_name\">","岁"},				//2.		//年龄
	{"，","，","，","，"},							//3.	//婚否
	{"来自","</h6>","来自","</h6>"},				//4.	//地区
	{"<em>","</em>","<em>","</em>"},				//5.	//学历
	{" <em>","</em>"," <em>","</em>"},				//6.	//身高
	{"<em  >","</em>","<em  >","</em>"},			//7.	//体重
	{"星座","</em>","星座：</div>\
		                                    <div class=\"fl pr\">\
												                                    <em>","</em>"},				//8.	//星座
	{"民族","</em>","民族：</div>\
		                                    <div class=\"fl pr\">\
												                                    <em  >","</em>"},		//9.		//民族
	{"<em>","</em>","属相：</div>\
		                                    <div class=\"fl pr\">\
												                                    <em>","</em>"},			//10.		//属相
	{"js_text",CR,"js_text\">\
		                            　　",CR},				//11.	//自我介绍
	{"爱好\"></span>","</li>","爱好\"></span>","</li>"},			//12.		//爱好
	{"职业职位：","</em>","职业职位：</span>\
		                                        <div class=\"ifno_r_con\"><em  >","</em>"},			//13.		//职位
	{"公司行业","</em>","公司行业：</span>\
		                                        <div class=\"ifno_r_con\"><em  class=\"info_null\" msg_id=\"31\"  >","</em>"},			//14.		//公司行业
	{"公司类型","</em>","公司类型：</span>\
		                                        <div class=\"ifno_r_con\"><em  class=\"info_null\" msg_id=\"32\"  >","</em>"},			//15.		//公司类型
	{"毕业院校","</em>","毕业院校：</span>\
		                                        <div class=\"ifno_r_con\"><em  >","</em>"},			//16.		//毕业学校
	{"专业类型","</em>","专业类型：</span>\
		                                        <div class=\"ifno_r_con\"><em  class=\"info_null\" msg_id=\"40\"  >","</em>"},			//17.		//专业类型
};

struct result_str{
	char net_name[40];		//0.	//网名
	char id[20];			//1.	//ID
	char age[20];			//2.	//年龄
	char marry[40];			//3.	//婚否
	char aray[40];			//4.	//地区
	char study[20];			//5.	//学历
	char high[20];			//6.	//身高
	char hight[20];			//7.	//体重
	char star[20];			//8.	//星座
	char nation[40];		//9.	//名族
	char zodiac[20];		//10.		//属相
	char explain[4096];		//11.	//自我介绍
	char hobbies[20];		//12.	//爱好
	char position[20];		//13.	//职位
	char company[20];		//14.	//公司行业
	char company_type[20];	//15.		//公司类型
	char school[40];		//16.		//学校
	char professional[40];	//17.		//专业
};

#define SQL_CREATE_TABLE "CREATE TABLE test_tb (id varchar(20),	net_name varchar(40), age varchar(20), marray varchar(40), aray varchar(40),study varchar(40), high varchar(20), hight	varchar(20), star varchar(20), nation varchar(40), zodiac varchar(20), hobbies varchar(20), position varchar(20), company varchar(20), company_type varchar(20),school varchar(40), professional varchar(40), explain varchar(4096))"


