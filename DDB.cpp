#include <iostream>
#include <fstream>
#include <stdio.h>
//#include <stdin>
#include <conio.h>
#include <iomanip>
#include <string>
#include <ctime>
#include <windows.h>
#include <stdlib.h>
#include <mmsystem.h>
//#include <unistd.h> // for STDOUT_FILENO
#include "DDB.h"
using namespace std;

	const char* prior[5] = {"none","extreme","high","normal","low"};//����� ��� ������������� ������������ ���������� ���������, �� ������ ������������ �������� ������������
	const char* weekDays[7] = { "Sunday","Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};//�����, ��� �� ����� ��������� ���� ����� � ���� ������� ��� ����������� (��������) ���� 
	const char* filename = "DDayBook.bin";
	//int n;
//	struct winsize size;
//	GetConsoleScreenBufferInfo( _In_ HANDLE hConsoleOutput, _Out_ PCONSOLE_SCREEN_BUFFER_INFO lpConsoleScreenBufferInfo);
//	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
//	GetLargestConsoleWindowSize( _In_ HANDLE hConsoleOutput);
	 
DDayBook::DDayBook ()
{
	f_Daybook=fopen(filename, "rb+");
}

void DDayBook::line(int x)
{
    if (x == 1)
    	cout << setw(130) << setfill('-') << " " << endl;
    else
        cout << endl << setw(130) << setfill('=') << " " << endl;
	setw(0);
	setfill(' ');
	return;
}

int DDayBook::List()
{	
	if ((f_Daybook=fopen(filename, "rb+")) == NULL)
	{
    	cout << "Error occurred while accessing the file..." << endl;
    	return 1;
	}
	int k=0, r;
	fseek(f_Daybook, 0, 0); 
	cout<<"Here is all your tasks: \n";
	line(2);
	while (!feof(f_Daybook)) 
	{
		r=fread(&T, sizeof(T), 1, f_Daybook);
        if (r < 1) break;
		Out1(T, k);
		line(1);
		k++;
		Sleep(400);
	}
	fclose(f_Daybook);
	return 0; 
}

void DDayBook::List_short()
{
	f_Daybook = fopen (filename, "ab+");
	int r, k;
	fseek(f_Daybook, 0, 0);
	cout << "Here`s a short list of your tasks \n";
	cout << setw(3) << setfill(' ') << right << "#" << setw(1) << "." << setw(3) << " | " <<  setw(24) << left << " Name:" <<  setw(3) << " | " << setw(20) << "Time of start:" <<  setw(3) << " | " << setw(15) << "Durability:" <<  setw(3) << " | " << setw(11) << "Priority:" << setw(3) << " | " << setw(9) << "Status:";
	line(2);
	while (!feof(f_Daybook)) 
	{
		r=fread(&T, sizeof(T), 1, f_Daybook);
     	if (r < 1) break;
		Out1_short(T, k+1);
		k++;
	}
	cout << "success!" << endl;
	fclose(f_Daybook);	
	cout << "Enter the number (#) of the tast to open its menu (or enter 0 to get back to the main menu): ";
	int Task;
	cin >> Task;
	if (Task == 0)
	{
		return;
	}
	else
	{
		oneMenu(Task);
	}
}

void DDayBook::Out1(Note T, int k)
{
	GetLocalTime(&lt);
	int tleft, h, d, hm;
	cout<<k+1<<".";
	cout<<"Category:\t\t\t"<<T.cg<<endl;
	cout<<"Name:\t\t\t\t"<<T.name<<endl;
	cout<<"Details to note #"<<k+1<<":\t\t"<<T.text<<endl;
	cout<<"Priority level:\t\t\t"<<prior[T.pr]<<endl;
	cout<<"Duration:\t\t\t"<<T.duration<<endl;
	cout<<"\nStatus:\t\t\t\t";
	if (T.done == true)
	{
		SetConsoleTextAttribute(hConsole, 10);
		cout<<"Done!\n\n";
		SetConsoleTextAttribute(hConsole, 15);
	}
	else 
	{
		SetConsoleTextAttribute(hConsole, 12);
		cout<<"Undone!\n\n";
		SetConsoleTextAttribute(hConsole, 15);
	}	
			
	cout<<"Start time:\t\t\t";
	SetConsoleTextAttribute(hConsole, 14);
	cout<<T.date1.hour<<":"<<T.date1.min<<"\t"
	<<T.date1.day<<"."<<T.date1.month<<"."<<
	T.date1.year<<"\t"<<weekDays[T.addD.wDayOfWeek]<<endl;
	SetConsoleTextAttribute(hConsole, 15);
	cout<<"End time:\t\t\t";
	SetConsoleTextAttribute(hConsole, 14);
	cout<<T.date2.hour<<":"	<<T.date2.min<<"\t"
	<<T.date2.day<<"."<<T.date2.month<<	"."<<
	T.date2.year<<"\t"<<weekDays[T.addD.wDayOfWeek]<<endl<<endl;
	SetConsoleTextAttribute(hConsole, 15);
		
	cout<<"Finish till:\t\t\t";
	SetConsoleTextAttribute(hConsole, 12);
	cout<<T.dl.hour<<":"<<T.dl.min<<"\t"<<T.dl.day<<"."<<T.dl.month
	<<"."<<T.dl.year<<"\t"<<weekDays[T.addD.wDayOfWeek]<<endl;
	SetConsoleTextAttribute(hConsole, 15);	
			
	tleft=(T.dl.year*365*30*24*60+T.dl.month*30*24*60+T.dl.day*24*60+T.dl.hour*60+T.dl.min-
	(lt.wYear*365*30*24*60+lt.wMonth*30*24*60+lt.wDay*24*60+lt.wHour*60+lt.wMinute));
	d=tleft/60/24;
	h=(tleft/60)%24;
	hm = tleft%60;
	cout<<"Time left till deadline:\t";
	SetConsoleTextAttribute(hConsole, 14);
	cout<<d<<" d  "<<h<<" h  "<<hm<<" m"<<endl;
	SetConsoleTextAttribute(hConsole, 15);

	cout<<"Adding time:\t\t\t";
	cout<<T.addD.wHour<<":"<<T.addD.wMinute<<"\t"
	<<T.addD.wDay<<"."<<T.addD.wMonth<<"."<<T.addD.wYear
	<<"\t"<<weekDays[T.addD.wDayOfWeek]<<endl;	
	return;
}

int DDayBook::Add_new_mult()
{	
	if((f_Daybook=fopen(filename, "ab+")) == NULL)
	{
	    cout << "Error occurred while accessing the text file..." << endl;
    	return 1;
	}
	int quantity=0, dl=0;
	cout<<"How much new positions you want to add?  ";
	cin>>quantity;
	fseek(f_Daybook, 0, SEEK_END);
	line(1);
	for(int i=0; i<quantity; i++)
	{	
		cin.ignore();
		printf("Enter category:  ");
		gets(T.cg);
		
		printf("Enter name:  ");
		gets(T.name);
	
		printf ("Enter the details:  ");
		gets(T.text);

		hour1:
			cout<<"Enter starting time (hour minute):  ";
			cin>>T.date1.hour>>T.date1.min;
			if(T.date1.hour<0 || T.date1.hour>=24)
			{
				cout<<"The input is not correct... The day has only 24 hours(^-^)\n Try again:  ";
				goto hour1;
			}
			if(T.date1.min<0 || T.date1.min>=60)
			{
				cout<<"The input is not correct... The hour has only 60 minutes(^-^)\nTry again:  ";
				goto hour1;
			}
			cout<<"Enter starting date (day month year):  ";
		day1:
			cin>>T.date1.day;
			if (T.date1.day<1  || T.date1.day>31)
			{	
				cout<<"The input is not correct... The month has only 31 days or less. \nPlease, try again:  ";
				goto day1;
			}
		mon1:	
			cin>>T.date1.month;
			if (T.date1.month<1 || T.date1.month>12)
			{	
				cout<<"Wrong character, try again:  ";
				goto mon1;
			}
			if (T.date1.month==2 && (T.date1.day==30 || T.date1.day==31 ))
			{	
				cout<<"You entered an unexisting date, try again.";
				goto day1;
			}
				if ((T.date1.month==4 || T.date1.month==6 || T.date1.month==9 || T.date1.month==11 ) && T.date1.day==31 )
			{	
				cout<<"You entered an unexisting date, try again.";
				goto day1;
			}
		year1:
			cin>>T.date1.year;
			if (T.date1.year<2020)
			{
				cout<<"You entered strange year\nTry again:  ";
				goto year1;
			}
	
			cout<<"Enter finishing time (hour minute):  ";
		hour2:
			cin>>T.date2.hour;
			if(T.date2.hour<0 || T.date2.hour>=24)
			{
				cout<<"The input is not correct... The day has only 24 hours(^-^)\n Try again:  ";
				goto hour2;
			}
		min2:
			cin>>T.date2.min;
			if(T.date2.min<0 || T.date2.min>=60)
			{
				cout<<"The input is not correct... The hour has only 60 minutes(^-^)\nTry again:  ";
				goto min2;
			}
			cout<<"Enter finishing date (day):  ";
		day2:
			cin>>T.date2.day;
			if (T.date2.day<1  || T.date2.day>31)
			{	
				cout<<"The input is not correct... The month has only 31 days or less. \nPlease, try again:  ";
				goto day2;
			}
			cout<<"Enter finishing date (month):  ";
		mon2:	
			cin>>T.date2.month;
			if (T.date2.month<1 || T.date2.month>12)
			{	
				cout<<"Wrong character, try again:  ";
				goto mon2;
			}
			if (T.date2.month==2 && (T.date2.day==30 || T.date2.day==31 ))
			{	
				cout<<"You entered an unexisting date, try again.";
				goto day2;
			}
				if ((T.date2.month==4 || T.date2.month==6 || T.date2.month==9 || T.date2.month==11 ) && T.date2.day==31 )
			{	
				cout<<"You entered an unexisting date, try again.";
				goto day2;
			}
			cout<<"Enter finishing date (year):  ";
		year2:
			cin>>T.date2.year;
			if (T.date2.year<2020)
			{
				cout<<"You entered strange year\nTry again:  ";
				goto year2;
			}
			if (T.date2.year<T.date1.year)
			{
				cout<<"The end date is unrealistic, you cannot finish the work, before starting it (>.<)\nTry again:";
				goto hour2;
			}
			else 
			{
				if (T.date2.year==T.date1.year)
				{
					if (T.date2.month<T.date1.month)
					{
						cout<<"The end date is unrealistic, you cannot finish the work, before starting it (>.<)\nTry again:";
						goto hour2;
					}
					else
					{
						if (T.date2.month==T.date1.month)
						{
							if (T.date2.day<T.date1.day)
							{
								cout<<"The end date is unrealistic, you cannot finish the work, before starting it (>.<)\nTry again:";
								goto hour2;
							}
							else
							{
								if (T.date2.day==T.date1.day)
								{
									if (T.date2.hour<T.date1.hour)
									{
										cout<<"The end date is unrealistic, you cannot finish the work, before starting it (>.<)\nTry again:";
										goto hour2;
									}
								}
								else
								{
									if(T.date2.hour==T.date1.hour)
									{
										if (T.date2.min==T.date1.min)
										{
											cout<<"The end date is unrealistic, you cannot finish the work, before starting it (>.<)\nTry again:";
											goto hour2;
										}	
									}
								}	
							}
						}
					}
				}
			}
		GetLocalTime(&T.addD);
		cout<<"Current time:\t "<<T.addD.wHour<<":"<<T.addD.wMinute<<endl;
		cout<<"Current date:\t"<<T.addD.wDay<<"."<<T.addD.wMonth<<"."<<T.addD.wYear<<endl;
		cout<<"Do you want to add a deadline yourself? ;D\nEnter 1 to add deadline by yourself or Enter 0 to set it as default (the finishing date) :  ";
		cin>>dl;
		cout<<endl;
		if(dl==1)
		{
			cout<<"Final deadline:\n";
			cout<<"\tEnter hour:  ";
		dlhour:
			cin>>T.dl.hour;
			if(T.dl.hour<0 || T.dl.hour>=24)
			{
				cout<<"The input is not correct... The day has only 24 hours(^-^)\n Try again:  ";
				goto dlhour;
			}
			cout<<"\tEnter minute:  ";
		dlmin:
			cin>>T.dl.min;
			if(T.dl.min<0 || T.dl.min>=60)
			{
				cout<<"The input is not correct... The hour has only 60 minutes(^-^)\nTry again:  ";
				goto dlmin;
			}
			cout<<"\tEnter day:  ";
		dlday:
			cin>>T.dl.day;
			if (T.dl.day<1  || T.dl.day>31)
			{	
				cout<<"The input is not correct... The month has only 31 days or less. \nPlease, try again:  ";
				goto dlday;
			}
			cout<<"\tEnter month:  ";
		dlmon:	
			cin>>T.dl.month;
			if (T.dl.month<1 || T.dl.month>12)
			{	
				cout<<"You entered an unexisting date, try again:  ";
				goto dlmon;
			}
			if (T.dl.month==2 && (T.dl.day==30 || T.dl.day==31 ))
			{	
				cout<<"You entered an unexisting date, try again.";
				goto dlday;
			}
			if ((T.dl.month==4 || T.dl.month==6 || T.dl.month==9 || T.dl.month==11 ) && T.dl.day==31 )
			{	
				cout<<"You entered an unexisting date, try again.";
				goto dlday;
			}
		cout<<"\tEnter year:  ";
		dlyear:
			cin>>T.dl.year;
			if (T.dl.year<2020)
			{
				cout<<"You entered strange year\nTry again:  ";
				goto dlyear;
			}
		}
		else
		{
			T.dl=T.date2;
			cout<<"Finish till:\t  "<<T.dl.hour<<":"<<T.dl.min<<"\t"<<T.dl.day<<"."<<T.dl.month<<"."<<T.dl.year<<endl;	
		}
	pr:	
		cout<<"Choose the priority (enter the number):"<<endl
		<<"(1.extreme, \n2.high, \n3.normal, \n4.low.)\nThe priority #";
		cin>>T.pr;
		if(T.pr<0 || T.pr>4)
		{
			cout<<"The entered priority # was not defined. Please, follow the instructions (._.)\n";
			goto pr;
		}
 	
		T.duration=(T.date2.month*30*24*60+T.date2.day*24*60+T.date2.hour*60+T.date2.min-(T.date1.month*30*24*60+T.date1.day*24*60+T.date1.hour*60+T.date1.min));
		cout<<"The duration (in minutes) of your task is:  "<<T.duration<<endl;
		cout<<"The duration (in hours) of your task is:  "<<T.duration/60<<endl;
		T.done = false;
		cout<<"Status: To be done.\n";
		fwrite(&T, sizeof(T), 1, f_Daybook);
		line(1);
		cout<<endl;
		Sleep(800);
		system("cls");	
	}
	fclose(f_Daybook);
	return 0;
}

int DDayBook::clear_file()
{	
	fclose(f_Daybook);
	if ((f_Daybook = fopen(filename,"wb+")) == NULL)
 	{	cout << "Unable to open file" << endl;
 		return -1;
	}
	cout<<"All tasks were deleted.\n";
	fclose(f_Daybook);
	Sleep(300);
	return 0;
}

void DDayBook::OutN1(Note No)
{   
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	cout <<"Category:\t\t" << No.cg << endl;
	cout <<"Name:\t\t" << No.name << endl;
    cout <<"Details: \t\t" << No.text << endl;
    SetConsoleTextAttribute(hConsole, 14);
    cout <<"Time of start: \t" << No.date1.hour<<":"<<No.date1.min<<"\t"<<No.date1.day<<"."<<No.date1.month<<"."<<No.date1.year<<endl;
    cout <<"Time of end: \t" << No.date2.hour<<":"<<No.date2.min<<"\t"<<No.date2.day<<"."<<No.date2.month<<"."<<No.date2.year<<endl;
	SetConsoleTextAttribute(hConsole, 15);
	cout <<"Priority: \t\t"<<prior[No.pr]<<endl;
	cout <<"Final deadline: \t\t"<<No.dl.hour<<":"<<No.dl.min<<"\t"<<No.dl.day<<"."<<No.dl.month<<"."<<No.dl.year<<endl;
	cout <<"Durability: \t\t"<<No.duration<<endl<<endl;
	cout <<"Time of adding: \t"<< No.addD.wHour<<":"<<No.addD.wMinute<<"\t"<<No.addD.wDay<<"."<<No.addD.wMonth<<"."<<No.addD.wYear<<endl;
	line (1);
	return;
}

void DDayBook::Out1_short(Note No, int a)
{

	cout << setw(3) << setfill(' ') << right << a << setw(1) << "." << setw(3) << " | " << setw(24) << left << No.name << setw(3) << " | ";
	ShowDate(No, 1);
	cout << setw(3) << " | " << setw(5) << setfill(' ') << " " << setw(4) << No.duration << setw(6) << setfill(' ') << " " << setw(3) << " | " << left << setw(11) << prior[No.pr] << setw(3) << " | " << left << setfill(' ');
	if (No.done == true)
	{
		SetConsoleTextAttribute(hConsole, 10);
		cout << setw(9) << "Done!";
		SetConsoleTextAttribute(hConsole, 15);
	}
	else 
	{
		SetConsoleTextAttribute(hConsole, 12);
		cout << setw(9) <<"Undone!";
		SetConsoleTextAttribute(hConsole, 15);
	}
	cout << endl;	
	line(1);
}

void DDayBook::ShowDate(Note T, int d)
{
	if (d == 1)
	{
		cout << right << setfill('0') << setw(2) << T.date1.hour << setw(1) << ":" << setw(2) << T.date1.min << setw(4) << "  D: " << setw(2) << T.date1.day << setw(1) << "." << setw(2) << T.date1.month << setw(1) << "." << setw(2) << T.date1.year << setfill(' ');
	}
	else if (d == 2)
	{
		cout << right << setfill('0') << setw(2) << T.date2.hour << setw(1) << ":" << setw(2) << T.date2.min << setw(4) << "  D: " << setw(2) << T.date2.day << setw(1) << "." << setw(2) << T.date2.month << setw(1) << "." << setw(2) << T.date2.year << setfill(' ');
	}
	else if (d == 3)
	{
		cout << right << setfill('0') << setw(2) << T.dl.hour << setw(1) << ":" << setw(2) << T.dl.min << setw(4) << "  D: " << setw(2) << T.dl.day << setw(1) << "." << setw(2) << T.dl.month << setw(1) << "." << setw(2) << T.dl.year << setfill(' ');
	}
}

int DDayBook::search_menu()
{
	int s;
	cout<<"You`re in the search menu. Choose from the following list: \n";
	s:	
	cout<<"1. Search tasks by category.\n";
	cout<<"2. Search tasks by name.\n";
	cout<<"3. Search tasks by deadline.\n";
	cout<<"4. To do today...\n";
	cout<<"5. Search tasks by priority.\n";
	cout<<"0. Go back to the main menu\n";
	line(1);
	Sleep(1000);
	cout<<"Press 0-5:\n";
	cin>>s;
	system("cls");
	switch(s)
	{
		case 1:
			search_cg();
			line(2);
		break;
		case 2:
			search_name();
			line(2);
		break;
		case 3:
			search_dl();
			line(2);
		break;
		case 4:
			search_today();
			line(2);
		break;
		case 5:
			search_pr();
			line(2);
		break;
		case 0:
			system ("pause");
			cout<<"Let`s go back to the main menu"<<endl;
			Sleep(1500);
		break;
		default:
			system ("pause");
			cout<<"Sorry, you entered unavailable menu #. Try again (choose from the list):\n";
			goto s;
		break;
	}
	return 0;
}
	
int DDayBook::search_cg()
{	
	if ((f_Daybook=fopen(filename, "rb+")) == NULL)
	{
    	cout << "Error occurred while accessing the file..." << endl;
    	return 1;
	}
	char newcg[30];
	int p=0, r;
	cin.ignore();
	cout << "Enter the category:  ";
	gets(newcg);
	fseek(f_Daybook, 0, SEEK_SET); 
	system ("cls");
	cout<<"All tasks in category:\t"<<newcg<<endl;
	while (!feof(f_Daybook))
	{	
		r = fread(&T, sizeof(T), 1, f_Daybook);
		if (r < 1) 
			{
				cout<<"Error occurred while accessing the file... \n"; 
				break;
			}
		if (strcmp(T.cg, newcg) == 0)
		{
			cout<<p+1<<"."<<endl<<endl;
			Out1(T, p);
			++p;
		}
	}
	if (p == 0) cout << "No note category like that was found." << endl;
	else 
	{
		cout << endl << "Found " << p << " notes."<< endl;
    }
	fclose(f_Daybook);
	return 0;
}

int DDayBook::search_name()
{	
	if ((f_Daybook=fopen(filename, "rb+")) == NULL)
	{
    	cout << "Error occurred while accessing the file..." << endl;
    	return 1;
	}
	char newname[30];
	int p=0, r;
	cin.ignore();
	cout << "Enter the name:  ";
	gets(newname);
	fseek(f_Daybook, 0, SEEK_SET); 
	while (!feof(f_Daybook))
	{	
		r = fread(&T, sizeof(T), 1, f_Daybook);
		if (r < 1) 
			{
				cout<<"Error occurred while accessing the file... \n";
				break; 
			}
		if (strcmp(T.name, newname) == 0)
		{
		cout<<p+1<<"."<<endl;
		Out1(T, p);
		++p;
		}
	}
	if (p == 0) cout << "No note name like that was found." << endl;
	else 
	{
		cout << endl << "Found " << p << " notes."<< endl;
    }
	fclose(f_Daybook);
	return p;
}

int DDayBook::search_pr()
{
	if ((f_Daybook=fopen(filename, "rb+")) == NULL)
	{
    	cout << "Error occurred while accessing the file..." << endl;
    	return 1;
	}
	int newpr=0;
	int p=0, r;
	
	cout << "Enter the priority level:\nChoose from the list (0-none, 1-extreme, 2-high, 3-normal, 4-low)\nPriority #:  ";
	cin>>newpr;
	fseek(f_Daybook, 0, SEEK_SET); 
	while (!feof(f_Daybook))
	{	
		r = fread(&T, sizeof(T), 1, f_Daybook);
		if (r < 1) 
		{
			cout<<"Error occurred while accessing the file... \n"; 
			break;
		}
		if (T.pr==newpr)
		{
			cout<<p+1<<"."<<endl;
			Out1(T, p);
			line(1);
			++p;
		}
	}
	if (p == 0) cout << "No note name like that was found." << endl;
	else 
	{
		cout << endl << "Found " << p << " notes."<< endl;
    }
	fclose(f_Daybook);
	return 0;
}

int DDayBook::search_dl()
{
	if ((f_Daybook=fopen(filename, "rb+")) == NULL)
	{
    	cout << "Error occurred while accessing the file..." << endl;
    	return 1;
	}
	int newday, newmon, newyear;
	int p=0, r;
	cin.ignore();
	cout << "Enter the deadline (day):  ";
	cin >> newday;
	cout << "Enter the deadline (month):  ";
	cin >> newmon;
	cout << "Enter the deadline (year):  ";
	cin >> newyear;
	fseek(f_Daybook, 0, SEEK_SET); 
	Sleep(300);
	system("cls");
	cout << "Here is listed the tasks to be done till "<<newday<<"."<<newmon<<"."<<newyear<<endl;
	while (!feof(f_Daybook))
	{	
		r = fread(&T, sizeof(T), 1, f_Daybook);
		if (r < 1) 
			{
				cout<<"Error occurred while accessing the file... \n";
				break; 
			}
		if (T.dl.day == newday)
			if (T.dl.month == newmon)
				if (T.dl.year == newyear)
				{
					cout<<p+1<<"."<<endl;
					Out1(T, p);
					++p;
				}
	}
	if (p == 0) cout << "No note with such deadline was found." << endl;
	else 
	{
		cout << endl << "Found " << p << " notes."<< endl;
    }
	fclose(f_Daybook);
	return 0;
    
}

int DDayBook::search_today()
{
	GetLocalTime(&lt);
	if ((f_Daybook=fopen(filename, "rb+")) == NULL)
	{
    	cout << "Error occurred while accessing the file..." << endl;
    	return 1;
	}
	int p=0, r;
	fseek(f_Daybook, 0, SEEK_SET); 
	Sleep(300);
	system("cls");
	cout << "Here is listed the tasks to be done on "<<lt.wDay<<"."<<lt.wMonth<<"."<<lt.wYear<<endl;
	while (!feof(f_Daybook))
	{	
		r = fread(&T, sizeof(T), 1, f_Daybook);
		if (r < 1) 
			{
				cout<<"Error occurred while accessing the file... \n";
				break; 
			}
		if (T.date1.day == lt.wDay)
			if (T.date1.month == lt.wMonth)
				if (T.date1.year == lt.wYear)
				{
					cout<<p+1<<"."<<endl;
					Out1(T, p);
					++p;
				}
	}
	if (p == 0) cout << "No tasks to do today were found.(>.<)" << endl;
	else 
	{
		cout << endl << "Found " << p << " notes."<< endl;
    }
	fclose(f_Daybook);
	return 0;
}

void DDayBook::sort_menu()
{
	int s, p;
	cout<<"\nSort by...\n\n";
	cout<<"1. the name\n";
	cout<<"2. the category\n";
	cout<<"3. the deadline\n";
	cout<<"4. the priority\n";
	cout<<"5. the durability\n";
	cout<<"0. Back to the main menu\n";
	line(1);
	Sleep(500);
	cout<<"Press 0-5:\n";
	cin>>s;
	Sleep(300);
	system("cls");
	switch(s) 
	{
		case 1: 
			sort_name6();
			Out1(T, p);
		break;
		case 2: 
			sort_cg6();
			Out1(T, p);
		break;
		case 3: 
			sort_dl6();
			Out1(T, p);
		break;
		case 4:
			sort_pr6();
			Out1(T, p);
		break;
		case 5:
			sort_dur6();
			Out1(T, p);
		break;
		case 0:
			system ("pause");
			cout<<"Let`s go back to the main menu"<<endl;
			Sleep(1500);
		break;
		default:
			cout<<"\n\aError!!!\nTry again...\n"; 
			Sleep(1500);
		break;
	}	
	Sleep(1500);
	line (2);
	fclose(f_Daybook);
	return;
}

int DDayBook::get_el_size(FILE* f)
{
	fseek(f, 0, 2);
	int size=ftell(f)/sizeof(Note);
	fseek(f, 0, 0);
	return size;
}

void DDayBook::sort_pr6()
{
	if ((f_Daybook=fopen(filename, "rb+")) == NULL)
	{
    	cout << "Error occurred while accessing the file..." << endl;
    	return ;
	}
	int n = get_el_size(f_Daybook);
	Note srt;
	e = new Note [n];
	for(int i=0; i<n; i++)
	{
		fread(&(e[i]), sizeof(Note), 1, f_Daybook);
	}	
	for(int j=0; j<n; j++)
	for(int k=0; k<n; k++)
	{
		if(e[j].pr<e[k].pr)
		{
			srt=e[j];
			e[j]=e[k];
			e[k]=srt;
		}
	}
	cout<<"Sorting was successful..."<<endl;
	CountDown();
	return;
}

void DDayBook::sort_cg6()
{
	if ((f_Daybook=fopen(filename, "rb+")) == NULL)
	{
    	cout << "Error occurred while accessing the file..." << endl;
    	return ;
	}
	int n = get_el_size(f_Daybook);
	Note srt;
	e = new Note [n];
	for(int i=0; i<n; i++)
	{
		fread(&(e[i]), sizeof(Note), 1, f_Daybook);
	}	
	for(int j=0; j<n; j++)
	for(int k=0; k<n; k++)
	{
		if(strcmp(e[j].cg,e[k].cg)<0)
		{
			srt=e[j];
			e[j]=e[k];
			e[k]=srt;
		}
	}
	cout<<"Sorting was successful..."<<endl;
	CountDown();
	return;
}

void DDayBook::sort_name6()
{
	if ((f_Daybook=fopen(filename, "rb+")) == NULL)
	{
    	cout << "Error occurred while accessing the file..." << endl;
    	return;
	}
	int n = get_el_size(f_Daybook);
	Note srt;
	e = new Note [n];
	for(int i=0; i<n; i++)
	{
		fread(&(e[i]), sizeof(Note), 1, f_Daybook);
	}	
	for(int j=0; j<n; j++)
	for(int k=0; k<n; k++)
	{
		if(strcmp(e[j].name,e[k].name)<0)
		{
			srt=e[j];
			e[j]=e[k];
			e[k]=srt;
		}
	}
	cout<<"Sorting was successful..."<<endl;
	CountDown();
	return;
}

void DDayBook::sort_dur6()
{
	if ((f_Daybook=fopen(filename, "rb+")) == NULL)
	{
    	cout << "Error occurred while accessing the file..." << endl;
    	return ;
	}
	int n = get_el_size(f_Daybook);
	Note srt;
	e = new Note [n];
	for(int i=0; i<n; i++)
	{
		fread(&(e[i]), sizeof(Note), 1, f_Daybook);
	}	
	for(int j=0; j<n; j++)
	for(int k=0; k<n; k++)
	{
		if(e[j].duration<e[k].duration)
		{
			srt=e[j];
			e[j]=e[k];
			e[k]=srt;
		}
	}
	cout<<"Sorting was successful..."<<endl;
	CountDown();
	return;
}

void DDayBook::sort_dl6()
{
	if ((f_Daybook=fopen(filename, "rb+")) == NULL)
	{
    	cout << "Error occurred while accessing the file..." << endl;
    	return ;
	}
	int n = get_el_size(f_Daybook);
	Note srt;
	e = new Note [n];
	for(int i=0; i<n; i++)
	{
		fread(&(e[i]), sizeof(Note), 1, f_Daybook);
	}
	for(int j=0; j<n; j++)
	for(int k=0; k<n; k++)
	{
		if(e[j].dl.year<e[k].dl.year)
		{
			srt=e[j];
			e[j]=e[k];
			e[k]=srt;
		}
		else 
		if(e[j].dl.year==e[k].dl.year)
		{
			if(e[j].dl.month<e[k].dl.month)
			{
				srt=e[j];
				e[j]=e[k];
				e[k]=srt;
			}
			else
			if(e[j].dl.month==e[k].dl.month)
			{
				if(e[j].dl.day<e[k].dl.day)
				{
					srt=e[j];
					e[j]=e[k];
					e[k]=srt;
				}
				else
				if(e[j].dl.day==e[k].dl.day)
				{
					if(e[j].dl.hour<e[k].dl.hour)
					{
						srt=e[j];
						e[j]=e[k];
						e[k]=srt;
					}
					else
					if(e[j].dl.hour==e[k].dl.hour)
					{
						if(e[j].dl.min<e[k].dl.min)
						{
							srt=e[j];
							e[j]=e[k];
							e[k]=srt;
						}
					}	
				}	
			}		
		}						
	}
	cout<<"Sorting was successful..."<<endl;
	CountDown();
	return;
}

void DDayBook::CountDown()
{
	cout<<"See the result in 3, ";
	Sleep(1000);
	cout<<"2, ";
	Sleep(1000);
	cout<<"1..."<<endl;	
	Sleep(500);
	return;
}

void DDayBook::Out_sort(int l)
{
	int n;
	for(int l=0; l<n; l++)
	{
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		cout <<"Category:\t\t" << e[l].cg << endl;
		cout <<"Name:\t\t" << e[l].name << endl;
	    cout <<"Details to task #"<<l+1<<": \t\t" << e[l].text << endl;
	    SetConsoleTextAttribute(hConsole, 14);
	    cout <<"Time of start: \t" << e[l].date1.hour<<":"<<e[l].date1.min<<"\t"<<e[l].date1.day<<"."<<e[l].date1.month<<"."<<e[l].date1.year<<endl;
	    cout <<"Time of end: \t" << e[l].date2.hour<<":"<<e[l].date2.min<<"\t"<<e[l].date2.day<<"."<<e[l].date2.month<<"."<<e[l].date2.year<<endl;
		SetConsoleTextAttribute(hConsole, 15);
		cout <<"Priority: \t\t"<<prior[e[l].pr]<<endl;
		cout <<"Final deadline: \t\t"<<e[l].dl.hour<<":"<<e[l].dl.min<<"\t"<<e[l].dl.day<<"."<<e[l].dl.month<<"."<<e[l].dl.year<<endl;
		cout <<"Durability: \t\t"<<e[l].duration<<endl<<endl;
		cout <<"Time of adding: \t"<< e[l].addD.wHour<<":"<<e[l].addD.wMinute<<"\t"<<e[l].addD.wDay<<"."<<e[l].addD.wMonth<<"."<<e[l].addD.wYear<<endl;
		line (1);
	}
	system("pause");
	return;
}

void DDayBook::del_one()
{	
	if ((f_Daybook=fopen(filename, "ab+")) == NULL)
	{
    	cout << "Error occurred while accessing the file..." << endl;
    	return;
	}
	int i=0, r, num, k, choice;
	string del;
	fseek(f_Daybook, 0, 0); 
	cout<<"Here is all your tasks: \n";
	while (!feof(f_Daybook)) 
	{
		r = fread(&T, sizeof(T), 1, f_Daybook);
        if (r < 1) break;
        cout<<i+1<<"."<<endl;
		Out1(T, i);
		line(1);
		i++;
	}
	line(2);
	fclose(f_Daybook);
	cout<<"\n Enter the # of the task you want to delete:  ";
	cin>>num;
	Sleep(300);
	system("cls");
	if(num>i+1||num<=0)
	{
		cout<<"There is no # like that. Try again:\n";
		Sleep(500);
		return;
	}
	else
	{
		if ((f_del1 = fopen("f_del_test.bin", "ab+")) == NULL)
		{
    		cout << "Error occurred while accessing the file..." << endl;
    		return;
		}
		k = 0;
		if ((f_Daybook=fopen(filename, "ab+")) == NULL)
		{
    		cout << "Error occurred while accessing the file..." << endl;
    		return;
		}
		fseek(f_Daybook, 0, 0);
		while (!feof(f_Daybook)) 
		{
			r=fread(&T, sizeof(T), 1, f_Daybook);
        	if (r < 1) break;
        	k++;
        	if(k==num) 
			{
				cout<<"Do you really want to delete the task #"<<num<<" with the following info: \n";
				Out1(T, 1);
				Sleep(500);
				cout<<"Do you want to continue the deleting process? (enter \"Yes\" to continue or \"No\" to dismiss)  ";
				cin>>del;
				if (del=="Yes")
				{
					cout<<"\nThe task was successfully deleted\n";
					Sleep(1500);
				}
				else 
				{
					fwrite(&T, sizeof(T), 1, f_del1);
					cout<<"Your task #"<<num<<" is successfully saved (^-^) \n";
					cout<<"Do you want to delete another task? \nChoose this option in the main menu in 3, 2, 1... \n";
					line(1);
					Sleep(3000);
				}
			}
        	else
        	{
			  	fwrite(&T, sizeof(T), 1, f_del1);
			}
		}
		fclose(f_Daybook);
		fclose(f_del1);
		remove(filename);
		rename("f_del_test.bin",filename);
		system("cls");
		Sleep(300);
		return;
	}
}

void DDayBook::main_menu()
{
	cout << "Welcome to the program \"DDayBook\"! In future versions here you`ll be able to read a quote and see your progress at all and certainly today (how many tasks are already done comparing to those left)." << endl;
	while (1)
{

	int m;//����� ��� ������ ������ ����	
	line(1);
	GetLocalTime(&lt);//�������, ��� ������� ���� ��� ��� �� ����'���� 		
	cout<<"\n\t\t\t\t\t\t\t\t\tYour date is "<<lt.wDay<<"."<<lt.wMonth<<"."<<lt.wYear<<endl; 
	cout<<"\t\t\t\t\t\t\t\t\tToday is "<<weekDays[lt.wDayOfWeek]<<endl;
	cout<<"\t\t\t\t\t\t\t\t\tYour time is "<<lt.wHour<<":"<<lt.wMinute<<endl;
	Sleep(300);
	//Beep(783.99, 100);//������� � �������� Windows.h ��� ���������� ��������� �������
	cout << "You`re in the main menu. Please, choose the option from the list: \n";
	cout << "1. Show all tasks \n";//������� ��, �������� � ����, �������� ���������
	cout << "2. Add new tasks \n";//������ ����� ����� ������
	cout << "3. Search a task \n";//������� � ���� ������ �������� ���������
	cout << "4. Show tasks for today \n";
	cout << "5. Sort all tasks \n";//������� � ���� ����������
	cout << "6. Delete a task \n";
	cout << "7. Delete all tasks \n";
	cout << "8. The quote of the day \n";
	cout << "11. Cheaking short out \n";
	cout << "0. Leave the program \n";//����� � ��������
	cout << "Enter the number of the action:  ";
	cin >> m;
	line(2);

	system ("cls");
	switch (m)
	{	case 1:
			List();
		break;
		case 2:
			Add_new_mult();
		break;
		case 3:
			search_menu();
		break;
		case 4:
			search_today();
			MarkAsDone();
		break;
		case 5:
			sort_menu();
		break;
		case 6:
			del_one();
		break;
		case 7:
			clear_file();
		break;
		case 0:
			SetConsoleTextAttribute(hConsole, 11);//������� � �������� Windows.h ��� ������� ������� ������� �� ����
			Beep(523,500);
			cout<<"\t\t\t\tBye-bye, C U L8R (^.^)"<<endl;
			SetConsoleTextAttribute(hConsole, 15);
			system("pause");
		return;
		case 11:
			List_short();
		break;
		default:
			Sleep(300);
			Beep(523,500);
			cout<<"Something went wrong:( Try again!";
		break;
	}
	system ("pause");
	line(2);
	system ("cls");
	cout<<"What do you want to do next? \n";
}
}

void DDayBook::MarkAsDone()
{
	GetLocalTime(&lt);
	if ((f_Daybook = fopen(filename, "rb+")) == NULL)
	{
    	cout << "Error occurred while accessing the file..." << endl;
    	return;
	}
	int n = 0, r, d, nd = 0, rd;//n = amount of tasks for today, r = is used for reading from file, d = the number of a task that will be marked as done, nd = the number of the tasks for marking, rd = the same as "r", but for marking
	fseek (f_Daybook, 0, SEEK_SET); 
	Sleep (300);
	system ("cls");
	cout << "Here is listed the tasks to be done on " << lt.wDay << "." << lt.wMonth << "." << lt.wYear << endl;
	while (!feof(f_Daybook))
	{	
		r = fread(&T, sizeof(T), 1, f_Daybook);
		if (r < 1) 
		{
			cout<<"Error occurred while accessing the file... \n";
			break; 
		}
		if (T.date1.day == lt.wDay && T.date1.month == lt.wMonth && T.date1.year == lt.wYear)
		{
			cout<<n+1<<"."<<endl;
			if (lt.wHour >= T.date1.hour)
			{
				SetConsoleTextAttribute(hConsole, 2);
			}
			Out1(T, n);
			++n;
		}
	}
	if (n == 0) cout << "No tasks to do today were found.(>.<)" << endl;
	else 
	{
		cout << endl << "Found " << n << " notes."<< endl;
    }
    cout << "Which task you want to mark as done?" << endl;
    cin >> d;
    system ("cls");
    fseek (f_Daybook, 0, SEEK_SET); 
    while (!feof(f_Daybook))
	{	
		rd = fread(&T, sizeof(T), 1, f_Daybook);
		if (rd < 1) 
		{
			cout<<"Error occurred while accessing the file... \n";
			break; 
		}
		if (T.date1.day == lt.wDay && T.date1.month == lt.wMonth && T.date1.year == lt.wYear)
		{
			if (lt.wHour > T.date1.hour)
			{
				SetConsoleTextAttribute(hConsole, 2);
			}
			if (d-1 == nd)
			{
				T.done = true;
				cout << "The next task was marked as done! Congrats!" << endl;
			}
			Out1(T, nd);
			++nd;
		}
	}
	fclose(f_Daybook);
	return;
}

void DDayBook::oneMenu(int Task)
{
	int m;
	cout << "The menu of the task:\n";
	cout << "1. Edit.\n";
	cout << "2. Delete.\n";
	cout << "3. Go back to the list.\n";
	cout << "0. Go back to the main menu.\n";
	cout << "Enter the # of the action:  ";
	cin>>m;
	system("cls");
	
	switch(m)
	{
		case 1:
			editMenu(Task);
		break;
		case 2:
			del_one();
		break;
		case 3:
			List_short();
		break;
		case 0:
			return;
		break;
		default:
			cout<<"You`ve entered wrong character, so you`ll be transfered to the List";
			Sleep(300);
		return;
	}
}

void DDayBook::editMenu(int e1)
{
	int m;
while(1)
{
	cout<<"You`re in the editing menu:\n";
	cout<<"What do you want to change?(choose one, you`ll have other options later)\n";
	cout<<"1. Change everything.\n";
	cout<<"2. Category.\n";
	cout<<"3. Name.\n";
	cout<<"4. Details.\n";
	cout<<"5. Date of the start.\n";
	cout<<"6. Date of the finish.\n";
	cout<<"7. Deadline.\n";
	cout<<"8. Priority.\n";
	cout<<"9. Mark as done.\n";
	cout<<"0. Go back to the main menu.\n";
	cout<<"Enter the # of the menu:  ";
	cin >> m;
	system("cls");
	
	switch(m)
	{
		case 1:
			editAll(e1);
		break;
		case 2:
			
		break;
		case 3:
			
		break;
		case 4:
			
		break;
		case 5:
			
		break;
		case 6:
			
		break;
		case 7:
			
		break;
		case 8:
			
		break;
		case 9:
			
		break;
		case 0:
			return;
		//break;
		default:
			cout<<"You`ve entered wrong number of the menu.\nTry again.\n";
		return;	
	}
	
}
}

void DDayBook::editAll(int e1)
{
	FILE *fEdit;
	Note R;//the struct to replace with
	/*int e;//the number of the task to edit
	printf("Enter the nimber of the Task to edit:  ");*/
	e1 -=1;
	int i=0;
	if ((f_Daybook = fopen(filename, "rb")) == NULL)
	{
    	cout << "Error occurred while accessing the file \"DDayBook\"..." << endl;
    	return;
	}
	if ((fEdit = fopen("fEdit_test.bin", "ab+")) == NULL)
	{
    	cout << "Error occurred while accessing the temporary file for Editing..." << endl;
    	return;
	}
	fseek(f_Daybook, 0, 0);
	fseek(fEdit, 0, 0);
	while (!feof(f_Daybook)) 
	{
		int r;
		r = fread(&T, sizeof(T), 1, f_Daybook);
        if (r < 1) break;
    	if (e1 == i)
    	{
			Out1(T, e1);
			
			change:
				
			cout << "Now the data about the task will be changed, you cannot undo this action.\nDo you want to continue? (y/n) ";
			char c[2];
			cin >> c;
			if(strcmpi(c,"y") == 0)
			{
				cin.ignore();
				cout << "The category was: " << T.cg << endl;
				printf("Enter new/edited category:  ");
				gets(T.cg);
				
				cout << "The name was: " << T.name << endl;
				printf("Enter new/edited name:  ");
				gets(T.name);
				
				cout << "The details were: " << T.text << endl;
				printf ("Enter new/edited the details:  ");
				gets(T.text);
				
				cout << "The starting time was: ";
				ShowDate(T, 1);
				cout << endl;
			edhour1:		
				cout << "Enter new/edited starting time (hour minute):  ";
				cin >> T.date1.hour >> T.date1.min;
				if (T.date1.hour<0 || T.date1.hour>=24)
				{
					cout << "The input is not correct... The day has only 24 hours(^-^)\n Try again:  ";
					goto edhour1;
				}
				if (T.date1.min<0 || T.date1.min>=60)
				{
					cout << "The input is not correct... The hour has only 60 minutes(^-^)\nTry again:  ";
					goto edhour1;
				}
				cout << "Enter starting date (day month year):  ";
			edday1:
				cin >> T.date1.day;
				if (T.date1.day<1  || T.date1.day>31)
				{	
					cout << "The input is not correct... The month has only 31 days or less. \nPlease, try again:  ";
					goto edday1;
				}
			edmon1:	
				cin >> T.date1.month;
				if (T.date1.month < 1 || T.date1.month > 12)
				{	
					cout<<"Wrong character, try again(enter month):  ";
					goto edmon1;
				}
				if (T.date1.month == 2 && (T.date1.day == 30 || T.date1.day == 31 ))
				{	
					cout<<"You entered an unexisting date, try again.";
					goto edday1;
				}
					if ((T.date1.month == 4 || T.date1.month == 6 || T.date1.month == 9 || T.date1.month == 11 ) && T.date1.day == 31 )
				{	
					cout<<"You entered an unexisting date, try again.";
					goto edday1;
				}
			edyear1:
				cin >> T.date1.year;
				if (T.date1.year < lt.wYear)
				{
					cout << "You entered strange year\nTry again:  ";
					goto edyear1;
				}
				
				cout << "The time of finishing was: ";
				ShowDate(T, 2);
				cout << endl;
				cout << "Enter finishing time (hour minute):  ";
			edhour2:
				cin >> T.date2.hour;
				if (T.date2.hour < 0 || T.date2.hour >= 24)
				{
					cout << "The input is not correct... The day has only 24 hours(^-^)\n Try again:  ";
					goto edhour2;
				}
			edmin2:
				cin >> T.date2.min;
				if (T.date2.min<0 || T.date2.min>=60)
				{
					cout << "The input is not correct... The hour has only 60 minutes(^-^)\nTry again:  ";
					goto edmin2;
				}
				cout << "Enter finishing date (day month year):  ";
			edday2:
				cin >> T.date2.day;
				if (T.date2.day<1  || T.date2.day>31)
				{	
					cout << "The input is not correct... The month has only 31 days or less. \nPlease, try again:  ";
					goto edday2;
				}
			edmon2:	
				cin >> T.date2.month;
				if (T.date2.month<1 || T.date2.month>12)
				{	
					cout << "Wrong character, try again:  ";
					goto edmon2;
				}
				if (T.date2.month == 2 && (T.date2.day == 30 || T.date2.day == 31 ))
				{	
					cout << "You entered an unexisting date, try again.";
					goto edday2;
				}
				if ((T.date2.month == 4 || T.date2.month == 6 || T.date2.month == 9 || T.date2.month == 11 ) && T.date2.day == 31 )
				{	
					cout << "You entered an unexisting date, try again.";
					goto edday2;
				}
			edyear2:
				cin >> T.date2.year;
				if (T.date2.year < 2020)
				{
					cout << "You entered strange year\nTry again:  ";
					goto edyear2;
				}
				if (T.date2.year < T.date1.year)
				{
					cout << "The end date is unrealistic, you cannot finish the work, before starting it (>.<)\nTry again:";
					goto edhour2;
				}
				else 
				{
					if (T.date2.year == T.date1.year)
					{
						if (T.date2.month < T.date1.month)
						{
							cout << "The end date is unrealistic, you cannot finish the work, before starting it (>.<)\nTry again:";
							goto edhour2;
						}
						else
						{
							if (T.date2.month == T.date1.month)
							{
								if (T.date2.day < T.date1.day)
								{
									cout << "The end date is unrealistic, you cannot finish the work, before starting it (>.<)\nTry again:";
									goto edhour2;
								}
								else
								{
									if (T.date2.day == T.date1.day)
									{
										if (T.date2.hour < T.date1.hour)
										{
											cout << "The end date is unrealistic, you cannot finish the work, before starting it (>.<)\nTry again:";
											goto edhour2;
										}
									}
									else
									{
										if(T.date2.hour == T.date1.hour)
										{
											if (T.date2.min == T.date1.min)
											{
											cout << "The end date is unrealistic, you cannot finish the work, before starting it (>.<)\nTry again:";
											goto edhour2;
											}	
										}
									}	
								}
							}
						}
					}
				}
				GetLocalTime(&T.addD);
				cout << "Current time:\t " << T.addD.wHour << ":" << T.addD.wMinute << endl;
				cout << "Current date:\t" << T.addD.wDay << "." << T.addD.wMonth << "." << T.addD.wYear << endl;
				
				cout << "The previous deadline was: ";
				ShowDate(T, 3);
				cout << endl;
				cout << "Do you want to add a deadline yourself? ;D\nEnter 1 to add deadline by yourself or Enter 0 to set it as default (the finishing date) :  ";
				int dl;
				cin >> dl;
				cout << endl;
				if(dl == 1)
				{
					cout << "Final deadline time (hour minute):\n";
				edlhour:
					cin >> T.dl.hour;
					if (T.dl.hour < 0 || T.dl.hour >= 24)
					{
						cout << "The input is not correct... The day has only 24 hours(^-^)\n Try again:  ";
						goto edlhour;
					}
				edlmin:
					cin >> T.dl.min;
					if (T.dl.min < 0 || T.dl.min >= 60)
					{
						cout << "The input is not correct... The hour has only 60 minutes(^-^)\nTry again:  ";
						goto edlmin;
					}
					cout << "\tEnter deadline date (day month year):  ";
				edlday:
					cin >> T.dl.day;
					if (T.dl.day < 1  || T.dl.day > 31)
					{	
						cout << "The input is incorrect... The month has only 31 days or less. \nPlease, try again:  ";
						goto edlday;
					}
				edlmon:	
					cin >> T.dl.month;
					if (T.dl.month < 1 || T.dl.month > 12)
					{	
						cout << "You entered an unexisting date, try again:  ";
						goto edlmon;
					}
					if (T.dl.month == 2 && (T.dl.day == 30 || T.dl.day == 31 ))
					{	
						cout << "You entered an unexisting date, try again: ";
						goto edlday;
					}
					if ((T.dl.month == 4 || T.dl.month == 6 || T.dl.month == 9 || T.dl.month == 11 ) && T.dl.day == 31 )
					{	
						cout << "You entered an unexisting date, try again: ";
						goto edlday;
					}
				edlyear:
					cin >> T.dl.year;
					if (T.dl.year < 2020)
					{
						cout << "You entered strange year\nTry again:  ";
						goto edlyear;
					}
				}
				else
				{
					T.dl = T.date2;
					cout << "Finish till:  ";
					ShowDate(T, 3);
					cout << endl;	
				}
			edpr:	
				cout << "Choose the priority (enter the number):" << endl
				<< "(1.extreme, \n2.high, \n3.normal, \n4.low.)\nThe priority # ";
				cin >> T.pr;
				if (T.pr < 0 || T.pr > 4 || T.pr != 0 && T.pr != 1 && T.pr != 2 && T.pr != 3 && T.pr != 4)
				{
					cout << "The entered priority # was not defined. Please, follow the instructions (._.)\n";
					goto edpr;
				}
 	
				T.duration = (T.date2.month*30*24*60 + T.date2.day*24*60 + T.date2.hour*60 + T.date2.min - (T.date1.month*30*24*60 + T.date1.day*24*60 + T.date1.hour*60 + T.date1.min));
				cout << "The duration (in minutes) of your task is:  " << T.duration << endl;
				cout << "The duration (in hours) of your task is:  " << T.duration/60 << endl;
				
			edmark:
				cout << "Do you want to mark the task as done? (y/n) ";
				char MarkAsDone[2];
				cin >> MarkAsDone;
				if (strcmpi(MarkAsDone, "y") == 0)
				{
					T.done = true;
					cout << "Status: Done.\n";
				}
				else if (strcmpi(MarkAsDone, "n") == 0)
				{
					T.done = false;
					cout << "Status: To be done.\n";
				}
				else
				{
					cout << "You`ve entered wrong character, try again:\n ";
					goto edmark;
				}
				fwrite(&T, sizeof(T), 1, fEdit);	
			}
			else if (strcmpi(c,"n") == 0)
			{
				cout << "The task won`t be edited.\n";
			}
			else
			{
				cout << "You`ve entered wrong character, try again:\n ";
				goto change;
			}		
		}
		else if (e1 != i)
		{
			fwrite(&T, sizeof(T), 1, fEdit);
		}
		i++;
	}
	fclose(f_Daybook);
	fclose(f_del1);
	if( remove(filename) != 0 )
	{
    	perror( "Error deleting file" );
	}
  	else
  	{
    	puts( "File successfully deleted" );
	}
	int result = rename("fEdit_test.bin", filename);
	if (result == 0)
	{
		printf("Successfully renamed!");
	}
	else 
	{
		printf("Error, could not rename the file.");
	}
	system("pause");
	system("cls");
	return;
}

DDayBook::~DDayBook()
{
	fclose(f_Daybook);
}

