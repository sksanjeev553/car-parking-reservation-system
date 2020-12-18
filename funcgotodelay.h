
# ifndef FUNCGOTODELAY_H_INCLUDED
# define FUNCGOTODELAY_H_INCLUDED
# include<iostream>
# include<iomanip>
# include<conio.h>
# include<time.h>
# include<windows.h>
# include<dos.h>
# include<winsock.h>
# include <mysql.h>
# include<sstream>

using namespace std;
void  book(MYSQL * ,string,string,int);
void  invoice(MYSQL *,string ,string,string,int,int,int);
void depart(MYSQL *,string,string,int);
void viewprofile(MYSQL *,string,string,int);
void viewhistory(MYSQL *,string,string,int);
void choose(MYSQL *,string,string,int);
void delay(int);

void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


void choose(MYSQL *conn,string name,string email_id,int sts)
{  int choice;
   system("Color 09");

   system("CLS");gotoxy(30,8);
   cout<<"ChoosE  YouR  ChoicE";gotoxy(20,10);
   cout<<"1. Wanna book a  parking slot??";
   gotoxy(20,12);cout<<"2.  Depart  the car from  parking";gotoxy(20,14);
   cout<<"3.  View  your parking  history??";gotoxy(20,16);
   cout<<"4.  View your  profile??";gotoxy(20,18);
   cout<<"5.  Exit  the application??     ";
   cin>>choice;
   switch(choice)
   {
   case 1:
    book(conn,name,email_id,sts);
    break;
   case 2:
    depart(conn,name,email_id,sts);
    break;
   case 3:
    viewhistory(conn,name,email_id,sts);
    break;
   case 4:
    viewprofile(conn,name,email_id,sts);
    break;
   case 5:
    system("CLS");
    system("Color 0A");
    gotoxy(40,13);
    cout<<"THANKS  FOR  BEING A PART OF OUR  COMMUNITY :-)";
    delay(2);
    exit(0);
   }

}

void  book(MYSQL * conn,string name,string id,int sts)
{  MYSQL_RES *res;
    MYSQL_ROW row;
     string carnum,hrs,status;float dis;int i;string curdate;
    int hr;
    if(sts==1)
        status="yes";
    else
        status="no";

    system("CLS");
    system("Color 0F");
    gotoxy(20,5);

    cout<<left<<setw(30)<<"Enter  your  car number :  ";
    cin>>carnum;gotoxy(20,7);
    cout<<left<<setw(30)<<"Enter the number of hours  of stay   ";gotoxy(20,9);
    cout<<left<<setw(30)<<"Per hour cost being INR 100 :  ";
    cin>>hr;hrs=to_string(hr);
    float charges=hr*100;
    system("CLS");system("Color 09");gotoxy(40,12);
    cout<<"CHECKING  PARKING  AVAILABITY.";delay(1);cout<<".";delay(1);cout<<".";
    delay(1);cout<<".";
    system("CLS");gotoxy(40,12);
    cout<<"Parking  is  available!!!";gotoxy(45,13);
    cout<<"You  can  park your car";
    stringstream c;
    c<<"select curdate();";
    string qc=c.str();
    int q0=mysql_query(conn,qc.c_str());
    if(q0==0)
    {
        res=mysql_store_result(conn);
        while(row=mysql_fetch_row(res))
        {
             curdate=row[0];
        }
    }
    stringstream r;
    r<<"select * from parkinghistory where (id='"+id+"');";
    string qr=r.str();
    int q1=mysql_query(conn,qr.c_str());
    if(q1==0)
    {
        res=mysql_store_result(conn);
        i=0;
        while(row=mysql_fetch_row(res))
        {
            i=1;
        }
    }
        if(i==0)
        {
             dis=0.5*charges;
            charges=charges-dis;
        }
        else
        {
             dis=0;
        }

        string charge=to_string(charges);string discount=to_string(dis);

    stringstream s;
    s<<"insert into currentbooking values('"+id+"','"+carnum+"','"+hrs+"','"+status+"','"+discount+"','"+charge+"','"+curdate+"');";
    string qs=s.str();
    int q2=mysql_query(conn,qs.c_str());gotoxy(40,15);
    if(status=="yes")
    { stringstream p1;
    p1<<"update vipperson set coins=coins+20 where(name,id)=('"+name+"','"+id+"');";
    string qp1=p1.str();
    int q31=mysql_query(conn,qp1.c_str());

    }
    else if(status=="no")
    { stringstream p2;
p2<<"update nonvipperson set coins=coins+10 where(name,id)=('"+name+"','"+id+"');";
    string qp2=p2.str();
    int q32=mysql_query(conn,qp2.c_str());
    }


    stringstream h;
    h<<"insert into parkinghistory values('"+id+"','"+carnum+"','"+hrs+"','"+status+"','"+discount+"','"+charge+"','"+curdate+"');";
    string qh=h.str();
    int q4=mysql_query(conn,qh.c_str());cout<<mysql_error(conn);
    cout<<"  Press any key to view  your invoice  ";
    _getch();
    invoice(conn,name,carnum,id,dis,charges,sts);
}


void  invoice(MYSQL *conn,string name,string carnum,string id,int discount,int cost,int sts)
{ char ch;gotoxy(30,6);
system("CLS");
system("Color 0F");
gotoxy(30,6);
  cout<<setfill('=')<<setw(65)<<" ";gotoxy(55,7);cout<<"INVOICE";
  gotoxy(40,9);
  cout<<left<<setfill(' ')<<setw(30)<<"Name"<<":  "<<name;gotoxy(40,10);
  cout<<left<<setfill(' ')<<setw(30)<<"EmailID"<<":  "<<id;gotoxy(40,11);
  cout<<left<<setfill(' ')<<setw(30)<<"Car Number"<<":  "<<carnum;gotoxy(40,12);
  cout<<left<<setfill(' ')<<setw(30)<<"Discount(if any) in INR"<<":  "<<discount;gotoxy(40,13);
  cout<<left<<setfill(' ')<<setw(30)<<"Charges in INR"<<":  "<<cost+discount<<" - "<<discount<<" = "<<cost;
  gotoxy(30,16);
  cout<<setfill('=')<<setw(65)<<" ";

  delay(3);
  cout<<"\n\n\n\t\t\twish to continue(y/n)??    ";
  cin>>ch;
  if(ch=='y'||ch=='Y')
  {
    system("CLS");
    choose(conn,name,id,sts);
  }
  else
  {
    system("CLS");system("Color 09");gotoxy(40,12);
    cout<<"THANKS  FOR  BOOKING !!!";delay(2);
    exit(0);
  }
}


void depart(MYSQL *conn,string name,string id,int sts)
{
    string carnum;system("CLS");system("Color 0F");gotoxy(20,5);
    cout<<"Enter  your  car number  : ";
    cin>>carnum;
    stringstream p;
    p<<"delete from currentbooking where (car_number='"+carnum+"');";
    string qp=p.str();
    int q1=mysql_query(conn,qp.c_str());gotoxy(40,15);
    cout<<"Parking  Record  Deleted!!! ";
    delay(2);
    choose(conn,name,id,sts);
}

void viewprofile(MYSQL *conn,string name,string id,int sts)
{   MYSQL_RES *res;
    MYSQL_ROW row;
    stringstream p;
    string vip_sts;
    if(sts==1)
    {
         vip_sts="Yes";
        p<<"select * from  vipperson where(id,name)=('"+id+"','"+name+"');";
    }
    else
    {
         vip_sts="No";
        p<<"select * from nonvipperson where(id,name)=('"+id+"','"+name+"');";
    }

    string qp=p.str();
    int q1=mysql_query(conn,qp.c_str());
    if(q1==0)
    {   system("CLS");system("Color 09");gotoxy(20,6);
        res=mysql_store_result(conn);
        while(row=mysql_fetch_row(res))
        {
            cout<<setfill(' ')<<left<<setw(30)<<"Name"<<":  "<<row[0];gotoxy(20,8);
            cout<<setfill(' ')<<left<<setw(30)<<"EmailID"<<":  "<<row[1];gotoxy(20,10);
            cout<<setfill(' ')<<left<<setw(30)<<"Age"<<":  "<<row[3];gotoxy(20,12);
            cout<<setfill(' ')<<left<<setw(30)<<"Gender"<<":  "<<row[4];gotoxy(20,14);
            cout<<setfill(' ')<<left<<setw(30)<<"Coins"<<":  "<<row[5];gotoxy(20,16);
        }

            cout<<setfill(' ')<<left<<setw(30)<<"VIP status"<<":  "<<vip_sts;gotoxy(20,18);
            _getch();
            choose(conn,name,id,sts);
    }



}


void viewhistory(MYSQL *conn,string name,string id,int sts)
{   MYSQL_RES *res;
MYSQL_ROW row;int i;
    stringstream p;
    system("CLS");system("Color 0A");cout<<"\n\n\n\n\n";
    p<<"select * from parkinghistory where (id='"+id+"');";
    string qp=p.str();
    int q1=mysql_query(conn,qp.c_str());
    if(q1==0)
    {   res=mysql_store_result(conn);
        while(row=mysql_fetch_row(res))
        {   i=1;cout<<"\n\n";
            cout<<setfill(' ')<<left<<setw(30)<<"Car number"<<":  "<<row[1]<<endl<<endl;
            cout<<setfill(' ')<<left<<setw(30)<<"Parking Hours"<<":  "<<row[2]<<endl<<endl;
            cout<<setfill(' ')<<left<<setw(30)<<"Discount(if any)"<<":  "<<row[4]<<endl<<endl;
            cout<<setfill(' ')<<left<<setw(30)<<"Total charges INR"<<":  "<<row[5]<<endl<<endl;
            cout<<setfill(' ')<<left<<setw(30)<<"Date of  Booking"<<":  "<<row[6]<<endl;
            cout<<"\n\n";


        }
        if(i==0)
        {   system("CLS");
            gotoxy(30,12);
            cout<<"No  parking  history  yet!!!";
        }
        _getch();choose(conn,name,id,sts);
    }


}

# endif // FUNCGOTODELAY_H_INCLUDED#


