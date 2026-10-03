#include <iostream>
#include <fstream>
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <tchar.h>
#include <ctime>
#include <strsafe.h>
#include <stdlib.h>
#include "DDB.h"
using namespace std;

DDayBook a;//оголошення класової змінної 

int Title(STRSAFE_LPCSTR titlename, const char* titletext)
{
   TCHAR szOldTitle[MAX_PATH];
   TCHAR szNewTitle[MAX_PATH];

   // Збереження актуальної назви консолі.

   if( GetConsoleTitle(szOldTitle, MAX_PATH) )
   {
      // Створення нового string назви консолі.

      StringCchPrintf(szNewTitle, MAX_PATH, TEXT(titlename));

      // Заміна назви консолі новою назвою консолі
      if( !SetConsoleTitle(szNewTitle) )
      {
         _tprintf(TEXT("SetConsoleTitle failed (%d)\n"), GetLastError());
         return 1;
      }
      else
      {
         _tprintf(TEXT(titletext));
      }
   }
   return 0;
}

STRSAFE_LPCSTR version = "DDayBook v.1.0";

int main()
{	
	Title( version, "Hi there!");
	setlocale(LC_CTYPE, "ukr");
	a.main_menu();//вивід меню програми
	return 0;
}

