#include <thread>
#include <chrono>
#include <vector>
#include <cstdio>
#include <conio.h>
#include <Windows.h>

using namespace std;

const int WIDTH = 40;
const int HEIGHT = 20;

struct Point {
    int x, y;
    Point(int _x = 0, int _y = 0) : x(_x), y(_y) {}
};

enum Direction { UP, DOWN, LEFT, RIGHT };

vector<Point> snake;
Point fruit;
Direction dir;
int score;

void print(const char* s, int x, int y, WORD color = 7) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    printf("%s", s);
}

char readKey() { 
    if (_kbhit()) {
        return _getch();
    }
    return '\0';
}

void generateFruit() {
    fruit.x = rand() % WIDTH;
    fruit.y = rand() % HEIGHT;
}

void update() {
    char input = readKey();
    switch (input) {
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
    }

    Point newHead = snake.front();
    switch (dir) {
        case UP:
            newHead.y--;
            break;
        case DOWN:
            newHead.y++;
            break;
        case LEFT:
            newHead.x--;
            break;
        case RIGHT:
            newHead.x++;
            break;
    }

    if (newHead.x < 0 || newHead.x >= WIDTH || newHead.y < 0 || newHead.y >= HEIGHT) {
        print("Game Over! Press any key to exit...", WIDTH / 2 - 7, HEIGHT / 2);
        readKey();
        exit(0);
    }
    for (size_t i = 1; i < snake.size(); ++i) {
        if (newHead.x == snake[i].x && newHead.y == snake[i].y) {
            print("Game Over! Press any key to exit...", WIDTH / 2 - 7, HEIGHT / 2);
            readKey();
            exit(0);
        }
    }

    if (newHead.x == fruit.x && newHead.y == fruit.y) {
        score++;
        generateFruit();
    } else {
        snake.pop_back();
    }

    snake.insert(snake.begin(), newHead);
}

void render() {
    system("cls");
    print("O", snake.front().x, snake.front().y);
    for (size_t i = 1; i < snake.size(); ++i) {
        print("o", snake[i].x, snake[i].y);
    }
    print("X", fruit.x, fruit.y, 12);
    char scoreStr[50];
    sprintf(scoreStr, "Score: %d", score);
    print(scoreStr, 0, HEIGHT + 1);
}

int main() {
    srand(time(0));
    snake.push_back(Point(10, 10));
    snake.push_back(Point(9, 10));
    snake.push_back(Point(8, 10));
    generateFruit();
    score = 0;
    dir = RIGHT;

    while (true) {
        update();
        render();
        this_thread::sleep_for(chrono::milliseconds(100));
    }

    return 0;
}