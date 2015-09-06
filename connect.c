#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <sys/wait.h>
#include <sqlite3.h>
#include "define.h"
#include "var.h"

#ifdef _DEBUG_
#define qz_printf(format,args...) printf(format, ##args)
#else
#define qz_printf(format,args...) 
#endif

//#define Req "GET /38061262 HTTP/1.1\r\nHost: 59.151.18.26\r\nConnection: Close\r\n\r\n"
#define BUFSIZE 1024
#define BUFF_LEN 1024*1
#define RES_BUFF_LEN 1024*1024*1
char buff[RES_BUFF_LEN];
char res_buff[RES_BUFF_LEN];
char html_buff[RES_BUFF_LEN];

int create_result_file()
{
	int fd;
	char buff[1024];
	time_t   now;
	struct   tm     *timenow; 

	time(&now);
	timenow   =   localtime(&now);

	fd = open("result.txt",O_CREAT | O_APPEND | O_WRONLY, S_IRUSR | S_IWUSR);
	if(fd == -1)
	{
		printf("error:open result file\n");
		exit(0);
	}
	sprintf(buff,"*******************************************\n");
	write(fd,buff,strlen(buff));
	sprintf(buff,"			http get date		\n");
	write(fd,buff,strlen(buff));
	sprintf(buff,"			time:%d-%d-%d %d:%d		\n",timenow->tm_year+1900,timenow->tm_mon+1,timenow->tm_mday,timenow->tm_hour,timenow->tm_min);
	write(fd,buff,strlen(buff));
	sprintf(buff,"*******************************************\n");
	write(fd,buff,strlen(buff));
	sprintf(buff,"no	name	id		age\n");
	write(fd,buff,strlen(buff));
	sprintf(buff,"-------------------------------------------\n");
	write(fd,buff,strlen(buff));
	qz_printf("create file ok !\r\n");

	return fd;
}

#ifdef DB_FILE
sqlite3 *db;  
int create_db_file()  
{
	char sql[128];  
	int rt;

	sqlite3_open("test.db", &db); 

	memset(sql, 0, 128);  
	//sprintf(sql, "%s%s%s", "create table ",	"test_tb",	"(id INTEGER PRIMARY KEY, data TEXT)");  
	rt = sqlite3_exec(db, SQL_CREATE_TABLE, NULL, NULL, NULL);  
//	rt = sqlite3_exec(db, "create table test_tb(id varchar(40),name varchar(40),sex varchar(40),age varchar(40))", NULL, NULL, NULL);  
	qz_printf("rt==%d\n",rt);
	return 0;
}
int write_db(char *sql)
{
	char *p;
	int rt;

	rt = sqlite3_exec(db, sql, NULL, NULL, &p);  
	if(rt != SQLITE_OK)
	{
		printf("sqlite3_exec error:%s\n",p);
		exit(0);
	}
//	sqlite3_exec(db, "insert into test_tb values('111','222','333','444')", NULL, NULL, NULL);  
	//printf("insert test_db ok!\n");

	return 0;
}
#endif
#if 1
int print_result(char *buf, int len)
{
	int fd;
	int result;

	qz_printf("into print_result!\n");
	fd = open("html.txt",O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);
	if(fd == -1)
	{
		printf("error:open html file\n");
		return -1;
	}
	qz_printf("create html.txt success!\n");
	result = write(fd,buf,len);
	if(result == -1)
	{
		printf("error:write html file\n");
		return -1;
	}
	close(fd);
}
#endif

char strRequest[BUFSIZE];
int http_connect()
{
	int cfd;
	struct sockaddr_in s_add,c_add;

	cfd = socket(AF_INET,SOCK_STREAM,0);
	if(cfd == -1)
	{
		printf("error: socket create\n");
		return 0;
	}

	qz_printf("socket ok!\n");
	bzero(&s_add,sizeof(struct sockaddr_in));
	s_add.sin_family=AF_INET;
	s_add.sin_addr.s_addr= inet_addr(DestIp);
	s_add.sin_port=htons(DestPort);
	qz_printf("s_addr = %#x ,port : %#x\r\n",s_add.sin_addr.s_addr,s_add.sin_port);

	if(-1 == connect(cfd,(struct sockaddr *)(&s_add), sizeof(struct sockaddr)))
	{
		printf("connect fail !\r\n");
		exit(0);
	}
	qz_printf("connect ok !\r\n");

	return cfd;
}

int send_msg(int cfd)
{
	char strResponse[BUFSIZE]={0};
	int nRequestLen;
	int recbytes;
	int size_html;
	int i;

	nRequestLen = strlen(strRequest);
	//	strncpy(strRequest, Req,strlen(Req));
	//qz_printf("%s\n",strRequest);
	if(-1 == (recbytes = write(cfd,strRequest,nRequestLen)))
	{
		printf("read data fail !\r\n");
		return -1;
	}

	size_html = 0;
	memset(html_buff,0,sizeof(html_buff));
	while(1)
	{
		i = read(cfd,strResponse,BUFSIZE-1);	
		if(0 >= i){
			break;
		}
		strResponse[i]='\0';
		strcat(html_buff,strResponse);

		size_html += i;
	}
	print_result(html_buff,size_html);
	qz_printf("size_html:%d\n",size_html);

	return size_html;
}

int insert_array(struct result_str* str,char *p[])
{
	p[0] = str->id;
	p[1] = str->net_name;
	p[2] = str->age;
	p[3] = str->marry;
	p[4] = str->aray;
	p[5] = str->study;
	p[6] = str->high;
	p[7] = str->hight;
	p[8] = str->star;
	p[9] = str->nation;
	p[10]= str->zodiac;
	p[11]= str->hobbies;
	p[12]= str->position;
	p[13]= str->company;
	p[14]= str->company_type;
	p[15]= str->school;
	p[16]= str->professional;
	p[17]= str->explain;
}

int no_date;
//char sql_buff[1*1024*1024];
//struct result_str result_str_buff;
char p_str[20][4*1024];
int do_things(int rfd)
{
	int rd;
	char *p,*f,*e;
	int i,num;
	char var_buf[1024],seg_buf[100];
	char buff[100];
	int str_len;

	char *sql_buff = malloc(8*1024);
	memset(sql_buff,0,sizeof(sql_buff));
	qz_printf("haha\n");
	//qz_printf("%s",html_buff);
	memset(res_buff,0,sizeof(res_buff));
	no_date++;
	sprintf(res_buff,"%d:",no_date);
	num = sizeof(req_args)/sizeof(struct var);
	f = html_buff;

//	num = 12;
	for(i=0; i< num; i++)
	{
		qz_printf("i == %d\n",i);
		f = strstr(html_buff,req_args[i].front);
		qz_printf("f:%d\n",f-html_buff);
		if(f <= 0)	{ memset(&p_str[i],0,4*1024);memcpy(&p_str[i][0],"\'---\'",strlen("\'---\'"));continue; }
		if(i < 5)
		{
			e = strstr(f+strlen(req_args[i].f_str),req_args[i].end);
			p = f + strlen(req_args[i].f_str);
			str_len = e - f - strlen(req_args[i].f_str);
		}
		else
		{
			char *f_old; 
			f_old = strstr(f,"em"); 
			f=strstr(f_old,">");
			e = strstr(f,"<");
			p = f + 1;
			str_len = e - p;
		}
		memset(var_buf,0,1024);
		memcpy(var_buf, p, str_len);
		var_buf[str_len] = 0;

		qz_printf("e==%d\n",e-html_buff);
		qz_printf("p==%d\n",p-html_buff);
		qz_printf("str_len==%d\n",str_len);
		qz_printf("f_str_len==%d\n",strlen(req_args[i].f_str));
		qz_printf("%s\n",var_buf);

		//sprintf(seg_buf,"%10s\t",var_buf);
		//strcat(res_buff,seg_buf);
	//	f += strlen(req_args[i].f_str);
		//f = e + strlen(req_args[i].e_str);
		qz_printf("f:%d\n",f-html_buff);

#ifdef DB_FILE
	//	p_str[i][0] = "\"";
	//	memcpy(&(p_str[i][1]),var_buf,strlen(var_buf));	
	//	p_str[i][strlen(var_buf)+1] = "\"";
		memset(&p_str[i],0,4*1024);
		sprintf(&p_str[i],"\'%s\'",var_buf);
#endif
	}
//	res_buff[strlen(res_buff)] = '\n';
//	qz_printf("%s\n",res_buff);
//	printf("ok\n");

#ifdef DB_FILE
	//for(i=0; i<num; i++)
	//{	printf("%d:%s\n",i,p_str[i]);}
	qz_printf("hehe\n");
	memset(sql_buff,0,8*1024);
	sprintf(sql_buff,"%s","INSERT INTO \"test_tb\" VALUES(");
	memcpy(&sql_buff[strlen(sql_buff)],&p_str[0],strlen(p_str[0]));
//	printf("%s\n",sql_buff);
	char CR[]={0x0D,0x0A,0};
	for(i=1;i<num;i++)
	{	
		if(i == 11)
		{
			if((p = strstr(&p_str[i][0],CR)) > 0)
			{*p='\'';*(p+1)= 0;}
		}
		sql_buff[strlen(sql_buff)] = ',';
		memcpy(&sql_buff[strlen(sql_buff)],&p_str[i],strlen(p_str[i]));
	}
	sql_buff[strlen(sql_buff)] = ')';
	qz_printf("%s\n",sql_buff);
	rd = write_db(sql_buff);
#else
	rd = write(rfd,res_buff,strlen(res_buff));
#endif

	free(sql_buff);
	return rd;
}

int read_start_no(int *start_num)
{
	int fd;
	int ret;
	char buff[100];

	fd = open("start_no.txt",O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	if(fd <= 0)
	{
		printf("error:open start_no file\n");
		exit(0);
	}

	lseek(fd,0,SEEK_SET);
	ret = read(fd,buff,100);
	if(ret <= 0)
		*start_num = START_NUM;
	else
		*start_num = atoi(buff);

	return fd;
}
int main(int argc, char **argv)
{
	int i;
	int ret;
	int rfd,cfd,nfd;
	int start_num,sum_num;
	char id_buff[50];
	int fpid;

	for(;;)
	{
		fpid = fork();
		if(fpid < 0)
		{printf("fork error!\n"); return 0;}
		else if(fpid == 0)
		{
			qz_printf("fork success!\n");
			nfd = read_start_no(&start_num);
#ifdef DB_FILE
			create_db_file();  
#else 
			rfd = create_result_file();
#endif

			for(i=0; i< SUM_NUM; i++)
			{
				printf("i==%d:",start_num + i);
				cfd = http_connect();
				if(cfd <= 0)
				{
				//	printf("sleep:%ds\n",SLEEP_TIME);
				//	sleep(SLEEP_TIME);
				//	i--;
				//	continue;
					return 0;
				}

				sprintf(strRequest,"GET /%d HTTP/1.1\r\nHost: %s\r\nConnection: Close\r\n\r\n",start_num + i,DestIp);
				ret = send_msg(cfd);
				if (ret < 40*1024)
				{
					printf("no\n");
					goto write_start_no;
				}
				do_things(rfd);
				printf("ok\n");
				close(cfd);
write_start_no:
				sprintf(id_buff,"%d            ",start_num + i);
				lseek(nfd,0,SEEK_SET);
				write(nfd,id_buff,strlen(id_buff));
			}

#ifdef DB_FILE
			close(db);
#else
			close(rfd);
#endif
			//close(cfd);
			close(nfd);
			return 0;
		}
		else 
		{
			waitpid(fpid,0,0);	
			qz_printf("child process exit!\n");
			return 0;
		}
	}
}
