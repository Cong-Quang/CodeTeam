#include <cstdio> // thay vì stdio.h thì mình dùng cstdio c++ cho mượt
#include <conio.h> // thực hiện đọc bàn phím
#include <Windows.h>// các hàm liên quan tới console
#include <pthread.h> // thực hiện tạo thread
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
char readKey() { // readkey từ bàn phím
    if (_kbhit()) {
        return _getch();
    }
    return '\0';
}
// Hàm thực thi của luồng
void* threadFunction(void* arg) {
    int thread_id = *((int*)arg);
    printf("Thread %d is running\n", thread_id);
    // Do something in the thread 
    printf("Thread %d is done\n", thread_id);
    return NULL;
}
int main() {

    return 0;
}
