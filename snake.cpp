#include "upc.h"

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

using namespace std;

struct Apple {
  int x;
  int y;
  char c;
  int color;
};

struct Snake {
  int *x;
  int *y;
  int *color;
  char tail;
  char body;
  char head;
  int start;
  int length;
  int dir;
  int MAX;
};

Apple *newApple() {
  Apple *apple = new Apple;
  apple->color = BRIGHT_RED;
  apple->c = '%';
  return apple;
}

void createApple(Apple *apple, ConsoleInfo *ci) {
  apple->x = randint(0, ci->boxCols);
  apple->y = randint(0, ci->boxRows);
  apple->color = randint(DARK_RED, WHITE + 1);
}

void drawApple(Apple *apple, ConsoleInfo *ci) {
  gotoxy(ci->left + apple->x, ci->top + apple->y);
  color(apple->color);
  cout << apple->c;
  clearColor();
  cout << endl;
}

Snake *newSnake(ConsoleInfo *ci) {
  Snake *snake = new Snake;
  snake->MAX = ci->boxRows * ci->boxCols;
  snake->x = new int[snake->MAX];
  snake->y = new int[snake->MAX];
  snake->color = new int[snake->MAX];
  for (int i = 0; i < snake->MAX; ++i) {
    snake->x[i] = 0;
    snake->y[i] = 0;
    snake->color[i] = 0;
  }
  snake->tail = '*';
  snake->body = 'o';
  snake->head = '@';
  return snake;
}

void resetSnake(Snake *&snake, ConsoleInfo *ci) {
  snake->start = 3;
  snake->length = 4;
  snake->dir = RIGHT;
  for (int i = 0; i < snake->length; ++i) {
    snake->x[i] = 2 + i;
    snake->y[i] = 2;
    snake->color[i] = BRIGHT_GREEN;
  }
}

void byeSnake(Snake *snake) {
  delete[] snake->x;
  delete[] snake->y;
  delete[] snake->color;
  delete snake;
}

void drawSnake(Snake *snake, ConsoleInfo *ci) {
  for (int i = 0; i <= snake->length; ++i) {
    gotoxy(ci->left + snake->x[(snake->MAX + snake->start - i) % snake->MAX],
           ci->top + snake->y[(snake->MAX + snake->start - i) % snake->MAX]);
    color(snake->color[i]);
    if (i == 0) {
      cout << snake->head;
    } else if (i < snake->length - 1) {
      cout << snake->body;
    } else if (i == snake->length - 1) {
      cout << snake->tail;
    } else {
      cout << " ";
    }
  }
  clearColor();
  cout << endl;
}

bool updateSnake(Snake *snake, ConsoleInfo *ci) {
  int x = snake->x[snake->start];
  int y = snake->y[snake->start];
  snake->start++;
  switch (snake->dir) {
  case UP:
    snake->x[snake->start] = x;
    snake->y[snake->start] = (ci->boxRows + y - 1) % ci->boxRows;
    break;
  case RIGHT:
    snake->x[snake->start] = (x + 1) % ci->boxCols;
    snake->y[snake->start] = y;
    break;
  case DOWN:
    snake->x[snake->start] = x;
    snake->y[snake->start] = (y + 1) % ci->boxRows;
    break;
  case LEFT:
    snake->x[snake->start] = (ci->boxCols + x - 1) % ci->boxCols;
    snake->y[snake->start] = y;
    break;
  }
  return true;
}

bool eatApple(Snake *snake, Apple *apple) {
  int x = snake->x[snake->start];
  int y = snake->y[snake->start];
  if (apple->x == x && apple->y == y) {
    snake->color[snake->length] = BRIGHT_GREEN;
    snake->color[snake->length - 1] = apple->color;
    snake->length++;
    return true;
  }
  return false;
}

void frame(ConsoleInfo *ci) {
  gotoxy(ci->left - 1, ci->top - 1);
  color(DARK_MAGENTA);
  for (int i = ci->left - 1; i <= ci->right + 1; ++i) {
    cout << "#";
  }
  clearColor();
  for (int i = ci->top; i <= ci->bottom; ++i) {
    gotoxy(ci->left - 1, i);
    color(DARK_MAGENTA);
    cout << "#";
    clearColor();
    gotoxy(ci->right + 1, i);
    color(DARK_MAGENTA);
    cout << "#";
    clearColor();
  }
  gotoxy(ci->left - 1, ci->bottom + 1);
  color(DARK_MAGENTA);
  for (int i = ci->left - 1; i <= ci->right + 1; ++i) {
    cout << "#";
  }
  clearColor();
  cout << endl;
}

int main() {
  srand(time(nullptr));
  ConsoleInfo *ci = new ConsoleInfo;
  bool leave;

  getConsoleInfo(ci, 4, 20, 4, 35);
  clear();
  frame(ci);
  Snake *snake = newSnake(ci);
  Apple *apple = newApple();
  resetSnake(snake, ci);

  noecho();
  hideCursor();
  leave = false;
  createApple(apple, ci);
  while (!leave) {
    drawApple(apple, ci);
    drawSnake(snake, ci);
    updateSnake(snake, ci);
    if (eatApple(snake, apple)) {
      createApple(apple, ci);
    }
    if (_kbhit()) {
      char c = _getch();
      c = tolower(c);
      switch (c) {
      case 'w':
        snake->dir = UP;
        break;
      case 'a':
        snake->dir = LEFT;
        break;
      case 's':
        snake->dir = DOWN;
        break;
      case 'd':
        snake->dir = RIGHT;
        break;
      case 'x':
        leave = true;
        break;
      }
    }
    sleep4(100);
  }
  byeSnake(snake);
  delete apple;
  resetAll();

  return 0;
}
