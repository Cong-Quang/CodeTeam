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

vector<Point> snake; // Danh sách các điểm của rắn
Point fruit; // Vị trí của quả trái cây
Direction dir; // Hướng di chuyển hiện tại của rắn
int score; // Điểm số

void print(const char* s, int x, int y, WORD color = 7) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    printf("%s", s);
}

char readKey() {  // dùng để đọc bàn phím khi đc nhấn 
    if (_kbhit()) {
        return _getch();
    }
    return '\0';
}

void generateFruit() {
    // Tạo vị trí mới cho quả trái cây ngẫu nhiên
    fruit.x = 1 + rand() % (WIDTH - 2); // Phần bên trong của chiều rộng đường biên
    fruit.y = 1 + rand() % (HEIGHT - 2); // Phần bên trong của chiều cao đường biên
}

void update() {
    char input = readKey();
    // Đọc phím người chơi và thiết lập hướng di chuyển
    switch (input) {
        case 'w':
            if (dir != DOWN) // Không thể di chuyển ngược lại với hướng hiện tại
                dir = UP;
            break;
        case 's':
            if (dir != UP)
                dir = DOWN;
            break;
        case 'a':
            if (dir != RIGHT)
                dir = LEFT;
            break;
        case 'd':
            if (dir != LEFT)
                dir = RIGHT;
            break;
    }

    Point newHead = snake.front();
    // Di chuyển đầu của rắn theo hướng đã chọn
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

    // Kiểm tra va chạm với biên
    if (newHead.x < 0 || newHead.x >= WIDTH || newHead.y < 0 || newHead.y >= HEIGHT) {
        print("Game Over! Press any key to exit...", WIDTH / 2 - 7, HEIGHT / 2);
        readKey();
        exit(0);
    }
    // Kiểm tra va chạm với cơ thể của rắn
    for (size_t i = 1; i < snake.size(); ++i) {
        if (newHead.x == snake[i].x && newHead.y == snake[i].y) {
            print("Game Over! Press any key to exit...", WIDTH / 2 - 7, HEIGHT / 2);
            readKey();
            exit(0);
        }
    }

    // Nếu đầu của rắn chạm vào quả trái cây
    if (newHead.x == fruit.x && newHead.y == fruit.y) {
        score++; // Tăng điểm
        generateFruit(); // Tạo quả trái cây mới
    } else {
         Point tailSnake = snake.back(); // Lấy vị trí của phần đuôi cuối cùng của con rắn
        snake.pop_back(); // Xóa phần đuôi của rắn
        print(" ", tailSnake.x, tailSnake.y); // Xóa hiển thị của phần đuôi cũ trên màn hình // fix l
    }
    snake.insert(snake.begin(), newHead); // Thêm đầu mới vào đầu danh sách
}

void render() {
   // system("cls"); // Xóa màn hình
    // Vẽ đường biên
    for (int i = 0; i < WIDTH; ++i) {
        print("#", i, 0); // Đường biên trên
        print("#", i, HEIGHT); // Đường biên dưới
    }
    for (int i = 0; i < HEIGHT; ++i) {  
        print("#", 0, i); // Đường biên trái
        print("#", WIDTH, i); // Đường biên phải
    }
    print("O", snake.front().x, snake.front().y,rand() % 15 + 1); // Vẽ đầu của rắn
    for (size_t i = 1; i < snake.size(); ++i) {
        print("o", snake[i].x, snake[i].y,rand() % 13 + 1); // Vẽ phần thân của rắn
    }
    print("P", fruit.x, fruit.y, rand() % 10 + 1); // Vẽ quả trái cây với màu sắc khác nhau
    char scoreStr[50];
    sprintf(scoreStr, "Score: %d", score);
    print(scoreStr, WIDTH + 5, HEIGHT/2,rand() % 10 + 1); // Hiển thị điểm số
    print("code by", WIDTH + 5, HEIGHT/2+1); // Hiển thị name 
    print("Team A5", WIDTH + 5, HEIGHT/2+2,rand() % 20 + 1); // Hiển thị name 
    print("              ", WIDTH+1, HEIGHT+1); // fix laij điểm ảnh
}

int main() {
    system("cls");
    system("title = snake full color");
    srand(time(0));
    // Khởi tạo rắn ban đầu
    snake.push_back(Point(9, 10));
    snake.push_back(Point(8, 10));
    generateFruit(); // Tạo quả trái cây ban đầu
    score = 0; // Đặt điểm số ban đầu là 0
    dir = RIGHT; // Hướng di chuyển ban đầu của rắn là sang phải
    while (true) {
        update(); // Cập nhật trạng thái của trò chơi
        render(); // Vẽ trạng thái mới của trò chơi
        this_thread::sleep_for(chrono::milliseconds(150)); // Chờ 150ms trước khi cập nhật lại trạng thái
    }

    return 0;
}
