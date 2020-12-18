# ifndef VIPPERSON_H_INCLUDED
# define VIPPERSON_H_INCLUDED

# include "funcgotodelay.h"
# include "email.h"
# include<iomanip>
# include<sstream>
# include<winsock.h>
# include<mysql.h>
# include<windows.h>
using namespace std;

class vipp
{
    string name,password,email_id,gender,age;

public:
    int registration(MYSQL *,string,string);  // static  polymorphism
    void registration(MYSQL *,string,string,string,string,string);  // in form of function overloading
};

int vipp::registration(MYSQL*conn,string id,string pass)
{ email_id=id;
password=pass;string passwrd;
MYSQL_RES* res;
MYSQL_ROW row;
  system("CLS");
  system("Color 09");
  gotoxy(40,15);


   cout<<"Validating user..";delay(1);cout<<".";delay(1);cout<<".";delay(1);cout<<".";
   system("CLS");
  stringstream s;
  s<<"select * from vipperson where (id,password)=('"+email_id+"','"+password+"');";
  string qs=s.str();
    int qstate=mysql_query(conn,qs.c_str());
    if(qstate==0)
    {  res=mysql_store_result(conn);
       int i=0;
        while(row=mysql_fetch_row(res))
        {   name=row[0];
            i=1;
            system("Color 09");
            gotoxy(50,15);
            cout<<"SUCCESSFULLY LOGGED IN !!";
            delay(2);
            system("CLS");
            gotoxy(20,5);
            cout<<"WELCOME  "<<name;


            choose(conn,name,email_id,1);
            return 0;
        }
        if(i==0)
        {  stringstream r;
        r<<"select * from vipperson where (id='"+email_id+"');";
        string qr=r.str();
        int qstate=mysql_query(conn,qr.c_str());
    if(qstate==0)
    {  res=mysql_store_result(conn);

        while(row=mysql_fetch_row(res))
        {    passwrd=row[2];   // get password tuple no from database
        }
         int inval;
            system("Color 0C");
            gotoxy(40,10);
            cout<<"FAILED TO MATCH A USER WITH ENTERED CREDENTIALS ";gotoxy(40,12);
            cout<<"1. try again???"<<setw(30)<<left<<"  2.  forgot password???";
            cin>>inval;
            if(inval==1)
            {
                system("CLS");
                return 1;

            }
            else
            {
                sendpass(id,passwrd);
                return 1;
            }
        }


}
}
}

void vipp ::  registration(MYSQL *conn,string nam,string pass,string id,
                     string gen,string ag)
{ name=nam; email_id=id; password=pass;  gender=gen; age=ag;char choice;





    stringstream r;
    r<<"insert into vipperson values ('"+name+"','"+email_id+"','"+password+"','"+age+"','"+gender+"',10);";

    string qr=r.str();
    int qstate=mysql_query(conn,qr.c_str());

            system("CLS");

            system("Color  09");
            gotoxy(40,15);
            cout<<"SUCCESSFULLY  REGISTERED ";delay(2);system("CLS");gotoxy(20,5);
            cout<<"WELCOME  "<<name;
            gotoxy(20,9);
            cout<<"We  Have  A  Surprise  For  U !!!";
            delay(2);
            gotoxy(30,12);
            cout<<"1. get  50% discount on your first booking !!!";delay(2);
            gotoxy(30,14);
            cout<<"2. earn 20 coins  after  each booking !!";delay(2);
            gotoxy(30,16);
            cout<<"3. a free booking  after each 200 coins collected !!";delay(2);
            gotoxy(30,18);
            cout<<"WISH  U  HAPPY   BOOKING  ";delay(2);
            gotoxy(30,20);
            cout<<"want to continue??(y/n)  ";
            cin>>choice;
            if(choice=='y'||choice=='Y')
            {


               choose(conn,name,email_id,1);
            }
            else
            exit(0);



}

# endif

