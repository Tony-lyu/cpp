#include <ncurses.h>

//Obstacles
//kill the snake if hitten

//Structure to hold properties of obstacle
struct Obstacle {
  int x;
  int y;
  char symbol;
  struct Obstacle* next;
};

typedef struct Obstacle Obstacle;

Obstacle* create_obstacle(int x, int y, int size, bool isHorizontal);
void draw_obstacles(Obstacle *obstacles);
bool obstacle_hitten(Obstacle *obstacles, int x, int y);

