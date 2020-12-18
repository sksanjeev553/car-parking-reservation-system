# include "funcgotodelay.h"
# include "vipperson.h"
# include "nvipperson.h"
# include<iostream>
# include<winsock.h>
# include<mysql.h>
# include<conio.h>




MYSQL *conn,mysql;
void login(MYSQL *);
void existing(MYSQL *);
void newuser(MYSQL *);


int main()
{
    mysql_init(&mysql);
   conn =mysql_real_connect(&mysql,"remotemysql.com","mH2kQ9m8IW","tXfgICQA3d","mH2kQ9m8IW",3306,NULL,0);
   system("Color 0C");   // to change foreground text color
   if(conn==0)
   {   gotoxy(50,12);
       cout<<"An  Error  Occurred!!!";
       gotoxy(45,15);
       cout<<"Please   Try  Again  Later";
       mysql_close(conn);
       exit(0);
   }
   login(conn);
   mysql_close(conn);
}

void login(MYSQL *conn)
{   int choice,i=1;
    gotoxy(27,5);    // to take cursor to positions specified in arguments
    cout<<"*************************************************************";
    gotoxy(32,7);
    cout<<"WELCOME TO  \"PARKING  CLICK\"   RESERVATION   SYSTEM";
    gotoxy(27,9);
    cout<<"**************************************************************";
    delay(2);   // to induce delay in seconds to execution
    gotoxy(70,23);
    system("Color 0A");
    cout<<"A  SynergisM   By  : ";gotoxy(75,25);cout<<"1.  SanjeeV ";gotoxy(75,26);cout<<"2.  NimisH  ";
    gotoxy(75,27);cout<<"3.  MuskaN ";
    delay(3);
    gotoxy(10,25);
    system("Color 09");
    cout<<"(\\___/)";gotoxy(10,26);cout<<"( . . )";gotoxy(10,27);cout<<"(__^__)";gotoxy(10,28);//cout<<"(__~__)";

    gotoxy(35,11);
    do
    {

    cout<<"ChoosE    YouR     ChoicE "; gotoxy(36,13);cout<<"1.  ALREADY  A  USER ???";gotoxy(36,14);
    cout<<"2.  WANNA   CREATE  AN ACCOUNT  ??    ";
    cin>>choice;
    switch(choice)
        {
        case 1:
            existing(conn);
            i=0;
            break;
        case 2:
            newuser(conn);
            i=0;
            break;
        default:
            gotoxy(39,17);
            cout<<"ENTER   VALID  CHOICE  ";
        }
    }while (i==1);

}


void existing(MYSQL *conn)
{
    char vip,ch;int i=0;
    string id,pass="";
    system("CLS");
    system("Color 0F");
    gotoxy(15,10);
    cout<<setw(30)<<"Enter   Your  EmailID"<<":  ";
   cin>>id;gotoxy(15,12);
    cout<<setw(30)<<"Enter   Your  Password"<<":  ";
     ch=_getch();
    while(ch != '\r')         //character '\r' is enter
        {
      pass.push_back(ch);
      cout << '*';
      ch = _getch();
   }




    gotoxy(15,14);
    cout<<setw(30)<<"Are  You  A VIP(y/n)??"<<":  ";
    cin>>vip;
    if(vip=='y'||vip=='Y')
    {
        vipp v1;
        int log=v1.registration(conn,id,pass);
        if(log==1)
            existing(conn);
    }
    else if(vip=='n'||vip=='N')
    {
        nvipp n1;
        int nlog=n1.registration(conn,id,pass);
        if(nlog==1)
            existing(conn);
    }
    else
    {
     cout<<"\n\n\n\n  INVALID  ENTRY ";
     existing(conn);
    }
}


void newuser(MYSQL *conn)
{
    char choice;
string name,gender,email_id;string password="";
int ag;char ch;
    system("CLS");
    system("Color 0F");
    gotoxy(15,5);
    cout<<left<<setw(50)<<"Enter  Your  Name "<<": ";
  cin>>name;
  gotoxy(15,7);
  cout<<left<<setw(50)<<"Enter Your Age "<<": ";
  cin>>ag;
  if(ag<18)
  { system("CLS");
    gotoxy(50,15);
    system("Color 0C");
    cout<<" SORRY !! YOU  ARE   STILL TOO YOUNG TO REGISTER ";
    exit(0);
  }
  else
  {
    string age=to_string(ag);
    gotoxy(15,9);
    cout<<left<<setw(50)<<"Enter  Your  Gender "<<": ";
    cin>>gender;
    gotoxy(15,11);
    cout<<left<<setw(50)<<"Enter  Your EmailID "<<": ";
    cin>>email_id;
    gotoxy(15,13);
    cout<<left<<setw(50)<<"Enter  The Password  To  Be  Set "<<": ";
   ch=_getch();
    while(ch != '\r')         //character '\r' is enter
        {
      password.push_back(ch);
      cout << '*';
      ch = _getch();
   }

   gotoxy(15,15);
    cout<<left<<setw(50)<<"VIP   REGISTRATION??? (y/n) "<<": ";
    cin>>choice;
    if(choice=='y'||choice=='Y')
    {
        vipp v2;
        v2.registration(conn,name,password,email_id,gender,age);
    }
    else if(choice=='n'||choice=='N')
    {
        nvipp n2;
        n2.registration(conn,name,password,email_id,gender,age);
    }
    else
    { system("Color 0C");
     cout<<"\n\n\n\n  INVALID  ENTRY ";
     newuser(conn);
    }
  }

}



