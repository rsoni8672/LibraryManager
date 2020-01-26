#include<stdio.h>
#include<sqlite3.h>
#include<stdlib.h>
static int callback(void *NotUsed,int argc,char **argv,char **azColName)
{
int i;
//printf("%s:",(const char*)data);
for(i=0;i<argc;i++)
{
printf("%s=%s\n",azColName[i],argv[i] ? argv[i]:"NULL");
}
printf("\n");
return(0);
}
static int callback2(void *data,int argc,char **argv,char **azColName)
{
int i;
printf("%s:",(const char*)data);
for(i=0;i<argc;i++)
{
printf("%s=%s\n",azColName[i],argv[i] ? argv[i]:"NULL");
}
printf("\n");
return(0);
}
sqlite3 *db;
void createtable()
{
 char *zErrMsg=0;
 /*CREATE SQL STATEMENT*/
 char *sql="CREATE TABLE RECORDS("\
"STUDENTID INT PRIMARY KEY NOT NULL,"\
"STUDENTNAME TEXT NOT NULL,"\
"BOOKNAME TEXT NOT NULL,"\
"BOOKID INT NOT NULL,"\
"NOOFDAYS INT NOT NULL,"\
"PENALTY INT NOT NULL,"\
"NOOFBOOKS INT NOT NULL,"\
"MOREBOOKS TEXT NOT NULL);";
/*EXECUTE SQL STATEMENT*/
int rc=sqlite3_exec(db,sql,callback,0,&zErrMsg);
if(rc!=SQLITE_OK)
{
printf("SQL ERROR:%s\n",zErrMsg);
sqlite3_free(zErrMsg);
}
else
{
printf("TABLE CREATED SUCCESSFULLY\n");
}
}
void insertintotable()
{
char *zErrmsg=0;
int rc6;
char *sql6;
/*INSERT INTO SQL STATEMENT*/
sql6="INSERT INTO RECORDS(STUDENTID,STUDENTNAME,BOOKNAME,BOOKID,NOOFDAYS,PENALTY,NOOFBOOKS,MOREBOOKS)"\
    "VALUES(207130056,'shlokashah','BOOKS',48,10,0,1,'YES');"\
    "INSERT INTO RECORDS(STUDENTID,STUDENTNAME,BOOKNAME,BOOKID,NOOFDAYS,PENALTY,NOOFBOOKS,MOREBOOKS)"\
    "VALUES(563,'MAMTAshah','BOOKS1',49,3,0,3,'YES');"\
    "INSERT INTO RECORDS(STUDENTID,STUDENTNAME,BOOKNAME,BOOKID,NOOFDAYS,PENALTY,NOOFBOOKS,MOREBOOKS)"\
    "VALUES(564,'MAMTA','BOOKS',481,10,0,4,'YES');"\
    "INSERT INTO RECORDS(STUDENTID,STUDENTNAME,BOOKNAME,BOOKID,NOOFDAYS,PENALTY,NOOFBOOKS,MOREBOOKS)"\
    "VALUES(565,'MAMTAS','BOOKS',480,26,0,8,'YES');";
/*EXECUTE "\SQL STATEMENT*/
rc6=sqlite3_exec(db,sql6,callback,0,&zErrmsg);
if(rc6!=SQLITE_OK)
{
printf("SQL ERROR:%s\n",zErrmsg);
sqlite3_free(zErrmsg);
}
else
{
printf("RECORD INSERTED SUCCESSFULLY\n");
}
}
void tablecreated()
{
char *zErr=0;
char *sql5;
int rc5;
const char* data="callback2 function called";
sql5="SELECT * FROM RECORDS";
rc5 =sqlite3_exec(db,sql5,callback2,(void*)data,&zErr);
if(rc5!=SQLITE_OK)
{
printf("SQL ERROR:%s\n",zErr);
sqlite3_free(zErr);
}
else
{
printf("TABLE CREATED SUCCESSFULLY\n");
}
}
void penalty()
{
char *zmsg=0;
char *sql1;
int rc1;
const char* data="callback2 function called";
sql1="UPDATE RECORDS set PENALTY=0 where NOOFDAYS<=7;"\
     "UPDATE RECORDS set PENALTY=30 where NOOFDAYS>7;"\
     "SELECT * FROM RECORDS";
rc1 =sqlite3_exec(db,sql1,callback2,(void*)data,&zmsg);
if(rc1!=SQLITE_OK)
{
printf("SQL ERROR:%s\n",zmsg);
sqlite3_free(zmsg);
}
else
{
printf("TABLE updated SUCCESSFULLY\n");
}
}
void finaltable()
{
char *sql2;
char *zErrM=0;
int rc3;
const char* data="callback2 function called";
sql2="UPDATE RECORDS set MOREBOOKS='NO' where PENALTY>0;"\
     "UPDATE RECORDS set MOREBOOKS='NO' where NOOFBOOKS>3;"\
     "SELECT * FROM RECORDS";
rc3 =sqlite3_exec(db,sql2,callback2,(void*)data,&zErrM);
if(rc3!=SQLITE_OK)
{
printf("SQL ERROR:%s\n",zErrM);
sqlite3_free(zErrM);
}
else
{
printf("TABLE updated SUCCESSFULLY\n");
}
}
int main(int argc,char* argv[])
{
 int rc2;
 /* opens database*/
 rc2=sqlite3_open("libraryproject.db",&db);
 if(rc2)
 {
   printf("CANT OPEN DATABASE:%s\n",sqlite3_errmsg(db));
   return(0);
 }
 else
 {
  printf("OPENED DATABASE\n");
 }
createtable();
insertintotable();
tablecreated();
penalty();
finaltable();
sqlite3_close(db);
return(0);
}
//output
/*
OPENED DATABASE
TABLE CREATED SUCCESSFULLY
RECORD INSERTED SUCCESSFULLY
callback2 function called:STUDENTID=207130056
STUDENTNAME=shlokashah
BOOKNAME=BOOKS
BOOKID=48
NOOFDAYS=10
PENALTY=0
NOOFBOOKS=1
MOREBOOKS=YES

callback2 function called:STUDENTID=563
STUDENTNAME=MAMTAshah
BOOKNAME=BOOKS1
BOOKID=49
NOOFDAYS=3
PENALTY=0
NOOFBOOKS=3
MOREBOOKS=YES

callback2 function called:STUDENTID=564
STUDENTNAME=MAMTA
BOOKNAME=BOOKS
BOOKID=481
NOOFDAYS=10
PENALTY=0
NOOFBOOKS=4
MOREBOOKS=YES

callback2 function called:STUDENTID=565
STUDENTNAME=MAMTAS
BOOKNAME=BOOKS
BOOKID=480
NOOFDAYS=26
PENALTY=0
NOOFBOOKS=8
MOREBOOKS=YES

TABLE CREATED SUCCESSFULLY
callback2 function called:STUDENTID=207130056
STUDENTNAME=shlokashah
BOOKNAME=BOOKS
BOOKID=48
NOOFDAYS=10
PENALTY=30
NOOFBOOKS=1
MOREBOOKS=YES

callback2 function called:STUDENTID=563
STUDENTNAME=MAMTAshah
BOOKNAME=BOOKS1
BOOKID=49
NOOFDAYS=3
PENALTY=0
NOOFBOOKS=3
MOREBOOKS=YES

callback2 function called:STUDENTID=564
STUDENTNAME=MAMTA
BOOKNAME=BOOKS
BOOKID=481
NOOFDAYS=10
PENALTY=30
NOOFBOOKS=4
MOREBOOKS=YES

callback2 function called:STUDENTID=565
STUDENTNAME=MAMTAS
BOOKNAME=BOOKS
BOOKID=480
NOOFDAYS=26
PENALTY=30
NOOFBOOKS=8
MOREBOOKS=YES

TABLE updated SUCCESSFULLY
callback2 function called:STUDENTID=207130056
STUDENTNAME=shlokashah
BOOKNAME=BOOKS
BOOKID=48
NOOFDAYS=10
PENALTY=30
NOOFBOOKS=1
MOREBOOKS=NO

callback2 function called:STUDENTID=563
STUDENTNAME=MAMTAshah
BOOKNAME=BOOKS1
BOOKID=49
NOOFDAYS=3
PENALTY=0
NOOFBOOKS=3
MOREBOOKS=YES

callback2 function called:STUDENTID=564
STUDENTNAME=MAMTA
BOOKNAME=BOOKS
BOOKID=481
NOOFDAYS=10
PENALTY=30
NOOFBOOKS=4
MOREBOOKS=NO

callback2 function called:STUDENTID=565
STUDENTNAME=MAMTAS
BOOKNAME=BOOKS
BOOKID=480
NOOFDAYS=26
PENALTY=30
NOOFBOOKS=8
MOREBOOKS=NO

TABLE updated SUCCESSFULLY
*/
