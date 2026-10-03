#ifndef DAYBOOK1_H_INCLUDED
#define DAYBOOK1_H_INCLUDED
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <conio.h>
#include <ctime>
#include <Windows.h>
using namespace std;

class DDayBook
{
	public:
	DDayBook();
	~DDayBook();

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	FILE *f_Daybook, *f_del1;
	SYSTEMTIME lt;
	struct date //struct for date
	{
   		int hour, min, day, month, year; 
	};

	struct Note
	{	
		char cg[20], name[30], text[200];
		date date1; //reserved starting time	
		date date2; //reserved time of the end
		date dl; //deadline
		SYSTEMTIME addD;// the time of adding a task.
		int pr;//priority # of the task 
		int duration;//time reserved for the execution of the task.
		bool done;//the flag to mark tasks as already done
	}T, *e;

	
	void main_menu();
	void line(int x);
	int List();
	void List_short();
	void Out1(Note T, int k);
	void ShowDate(Note T, int d);
	int Add_new_mult();
	int clear_file();
	void OutN1(Note No);
	void del_one();
	int search_menu();
	int search_name();
	int search_cg();
	int search_dl();
	int search_today();
	int search_pr();
	void sort_menu();
	void sort_name6();
	void sort_cg6();
	void sort_pr6();
	void sort_dur6();
	void sort_dl6();
	int get_el_size(FILE* f);
	void Out_sort(int l);
	void CountDown();
	void Out1_short(Note No, int a);
	void MarkAsDone();
	void oneMenu(int Task);
	void editMenu(int e1);
	void editAll(int e1);
};

#endif // DAYBOOK_H_INCLUDED
