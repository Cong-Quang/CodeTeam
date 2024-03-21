#include <thread>
#include <chrono>
#include <vector>
#include <cstdio>
#include <conio.h>
#include <Windows.h>

void print(const char* s, int x, int y, WORD color = 7) {
   // trp SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    printf("%s", s);
}
int main() {
    system("cls");
   int n=13;
      for(int i=0;i<=n;i++){
        print("*",0,i,i);
        print("*",n+n,i,i);
        print("*",i+i,0,i);
        print("*",i+i,n,i);
        print("*",i+i,i,i);
    } 
    
    return 0;
}
