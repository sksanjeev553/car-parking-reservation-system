# ifndef NVIPPERSON_H_INCLUDED
# define NVIPPERSON_H_INCLUDED
# include "funcgotodelay.h"
# include<iostream>
# include<winsock.h>
# include<windows.h>
# include<mysql.h>
using namespace std;
class nvipp
{
    string name,password,email_id,gender,age;

public:
    int registration(MYSQL *,string,string);    //  function overloading
    void registration(MYSQL *,string,string,string,string,string);  // compile polymorphism
};

int nvipp::registration(MYSQL *conn,string id,string pass)
{ email_id=id;
password=pass;
 MYSQL_RES* res;
MYSQL_ROW row;
  system("CLS");
  system("Color 09");
  gotoxy(40,15);




cout<<"Validating user..";delay(1);cout<<".";delay(1);cout<<".";delay(1);cout<<".";
   system("CLS");
  stringstream s;
  s<<"select * from nonvipperson where (id,password)=('"+email_id+"','"+password+"');";
  string qs=s.str();
    int qstate=mysql_query(conn,qs.c_str());
    if(qstate==0)
    {  res=mysql_store_result(conn);
       int i=0;
        while(row=mysql_fetch_row(res))
        {   name=row[0];
            i=1;
            gotoxy(50,15);
            cout<<"SUCCESSFULLY LOGGED IN !!";
            delay(2);
            system("CLS");
            gotoxy(20,5);
            cout<<"WELCOME  "<<name;

            gotoxy(15,40);
            choose(conn,name,email_id,0);
            return 0;

        }
        if(i==0)
        {   int inval;

            system("Color 0C");
            gotoxy(40,10);
            cout<<"FAILED TO MATCH A USER WITH ENTERED CREDENTIALS ";
            cout<<"1. try again???"<<setw(30)<<left<<"2.  forgot password???";
            cin>>inval;
            if(inval==1)
            {
                system("CLS");
                return 1;

            }
            else
            {
                sendpass(id,password);
                return 1;
            }

        }


}
}


void nvipp :: registration(MYSQL *conn,string nam,string pass,string id,
                     string gen,string ag)
{ name=nam; email_id=id; password=pass;  gender=gen; age=ag;char choice;



    stringstream r;
    r<<"insert into nonvipperson values ('"+name+"','"+email_id+"','"+password+"','"+age+"','"+gender+"',10);";

    string qr=r.str();
    int qstate=mysql_query(conn,qr.c_str());

            system("CLS");
            gotoxy(30,6);
            system("Color 09");

            cout<<"WELCOME  "<<name;
            gotoxy(20,9);
            cout<<"We  Have  A  Surprise  For  U !!!";
            delay(1);
            gotoxy(30,12);
            cout<<"1. get  50% percent on your first booking !!!";delay(1);
            gotoxy(30,14);
            cout<<"2. earn 10 coins  after  each booking !!";delay(1);
            gotoxy(30,16);
            cout<<"3. a free booking  after each 200 coins collected !!";delay(1);
            gotoxy(30,18);
            cout<<"WISH  U  HAPPY   BOOKING  ";delay(1);
            gotoxy(30,20);
            cout<<"want to continue??(y/n)  ";
            cin>>choice;
            if(choice=='y'||choice=='Y')

               choose(conn,name,email_id,0);
            else
            exit(0);
}









# endif // NVIPPERSON_H_INCLUDED


