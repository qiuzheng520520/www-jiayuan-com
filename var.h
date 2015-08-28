#define START_NUM  10000000		//开始ID
#define SUM_NUM	1		//总数

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
	{"个人资料_",	"（",	"个人资料_",	"（"},		//网名
	{"佳缘ID:",	"）",	"佳缘ID:",	"）"},				//ID
	{"member_name","，","member_name\">","，"},						//年龄
	{"岁","，来自","岁，","，来自"},							//婚否
	{"来自","</h6>","来自","</h6>"},					//地区
	{"<em>","</em>","<em>","</em>"},					//学历
	{" <em>","</em>"," <em>","</em>"},					//身高
	{"<em  >","</em>","<em  >","</em>"},				//体重
	{"<em>","</em>","<em>","</em>"},					//星座
	{"<em  >","</em>","<em  >","</em>"},				//名族
	{"<em>","</em>","<em>","</em>"},					//属相
	{"js_text",CR,"js_text\">\
		                            　　",CR},					//自我介绍
	{"爱好\"></span>","</li>","爱好\"></span>","</li>"},					//爱好
	{"职业职位：","</em>","职业职位：</span>\
		                                        <div class=\"ifno_r_con\"><em  >","</em>"},					//职位
	{"公司行业","</em>","公司行业：</span>\
		                                        <div class=\"ifno_r_con\"><em  class=\"info_null\" msg_id=\"31\"  >","</em>"},					//公司行业
	{"公司类型","</em>","公司类型：</span>\
		                                        <div class=\"ifno_r_con\"><em  class=\"info_null\" msg_id=\"32\"  >","</em>"},					//公司类型
	{"毕业院校","</em>","毕业院校：</span>\
		                                        <div class=\"ifno_r_con\"><em  >","</em>"},					//毕业学校
	{"专业类型","</em>","专业类型：</span>\
		                                        <div class=\"ifno_r_con\"><em  class=\"info_null\" msg_id=\"40\"  >","</em>"},					//专业类型
};

struct result_str{
	char net_name[40];			//网名
	char id[20];				//ID
	char age[20];				//年龄
	char marry[40];				//婚否
	char aray[40];				//地区
	char study[20];				//学历
	char high[20];				//身高
	char hight[20];				//体重
	char star[20];				//星座
	char nation[40];				//名族
	char zodiac[20];				//属相
	char explain[4096];			//自我介绍
	char hobbies[20];			//爱好
	char position[20];			//职位
	char company[20];			//公司行业
	char company_type[20];			//公司类型
	char school[40];				//学校
	char professional[40];			//专业
};

#define SQL_CREATE_TABLE "CREATE TABLE test_tb \
(							\
	id varchar(20)			//ID		\
	net_name varchar(40),		//网名		\
	age varchar(20)			//年龄		\
	marray varchar(40)		//婚否		\
	aray varchar(40)			//地区		\
	study varchar(40)		//学历		\
	high varchar(20)			//身高		\
	hight	varchar(20)		//体重		\
	star varchar(20)			//星座		\
	nation varchar(40)		//名族		\
	zodiac varchar(20)		//属相		\
	hobbies varchar(20)		//爱好		\
	position varchar(20)		//职位		\
	company varchar(20)		//公司行业	\
	company_type varchar(20)		//公司类型	\
	school varchar(40)		//学校		\
	professional varchar(40)		//专业		\
	explain varchar(4096)		//自我介绍	\
)"
