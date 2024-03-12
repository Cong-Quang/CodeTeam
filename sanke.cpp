#include <cstdio>
#include <Windows.h>

typedef struct COLOR
{
    char name;
    WORD value; 
}color;
void print(const char* s, int x, int y) // in ra 1 chuỗi s ở vị trí x y trên màn hình
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    printf("%s\n", s);
}
void print(const char* s, int x, int y, WORD color) // in ra 1 chuỗi s ở vị trí x y trên màn hình có màu tương ứng
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    printf("%s\n", s);
}

int main() {
    for (int i = 0; i < 10; i++)
    {
        Sleep(1000); // 1000 milliseconds = 1 second
        print(" . ", i, i,FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    }


    
    scanf("%d");
    return 0;
}
