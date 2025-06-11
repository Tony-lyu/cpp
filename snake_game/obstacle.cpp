#include <cstdlib>
#include <ncurses.h>
#include <cstdbool>
#include "obstacle.hpp"

// create new obstacle
Obstacle* create_obstacle(int x, int y, int size, bool isHorizontal) {
    Obstacle* obstacles = new Obstacle{x, y, '/', NULL};
    Obstacle* current = obstacles;
    for(int i = 1; i < size; i++) {
        if(isHorizontal) {
            current->next = new Obstacle{x + i, y, '/', NULL};
        } else {
            current->next = new Obstacle{x, y + i, '/', NULL};
        }
        current = current->next;
    }
    return obstacles;
}

// draw obstacles on the gameboard
void draw_obstacles(Obstacle *obstacles) {
    Obstacle* current = obstacles;
    while(current != NULL) {
        attron(COLOR_PAIR(4));
        mvprintw(current->y, current->x, "%c", current->symbol);
        current = current->next;
    }
    attroff(COLOR_PAIR(4));
}

// check if obstacle in hitten
bool obstacle_hitten(Obstacle *obstacles, int x, int y) {
    while(obstacles != NULL) {
        if(x == obstacles->x && y == obstacles->y) {
            return true;
        }
        obstacles = obstacles->next;
    }
    return false;
}


