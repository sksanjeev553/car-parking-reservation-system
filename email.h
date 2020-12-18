# ifndef EMAIL_H_INCLUDED
# define EMAIL_H_INCLUDED
# include<iostream>
# include "funcgotodelay.h"
# include<fstream>
# include<unistd.h>  // contains getcwd()
using namespace std;
void sendpass(string receiver,string password)
{

char cwd[10000];//this finds the path of .cpp file (absolute)
getcwd(cwd, sizeof(cwd));

string path_of_file = "";
int i=0;
while(cwd[i]!='\0')
    {    //converts array to string


        path_of_file += cwd[i];
        i++;
    }

    ofstream MyFile("script_for_email.py");//file opened in filestream


  string text =                //python used
  "import smtplib\n"
  "from email.message import EmailMessage\n"
  "msg = EmailMessage()\n"
  "msg['Subject'] = 'Password  Recovery'\n"
  "msg['From'] = '@gmail.com'\n"  //
  "msg['To'] = '"+receiver+"'\n"
  "msg.set_content('Your  password  for  parkingclick  account  is  :: "+password+"')\n"

  "smtp = smtplib.SMTP_SSL('smtp.gmail.com',465)\n"
  "smtp.login('parkingclickofficial@gmail.com','hhuryikxggjiwfnu')\n"      //

  "smtp.send_message(msg)";

  // Write to the file
  MyFile << text;

  // Close the file
  MyFile.close();


    string filename = path_of_file+"\\script_for_email.py";//absolute path of file containing email script in python
    string command = "python -u ";
    command += filename;
    system(command.c_str()); // sending a command in python for execution
    system("CLS");
    gotoxy(40,10);
    system("Color 0D");cout<<"mail sent for password recovery";delay(3);

}






# endif // EMAIL_H_INCLUDED
