/* snake.cpp -------
 *
 * Filename: snake.cpp
 * Description:
 * Author: Adeel Bhutta
 * Maintainer:
 * Created: Sun Sep 13 9:12:30 2022
 * Last-Updated: September 13 22:40 2022
 *
 */

/* Commentary:
 *
 *
 *
 */

/* Change log:
 *
 *
 */

/* Copyright (c) 2022 Adeel Bhutta
 *
 * All rights reserved.
 *
 * Additional copyrights may follow
 */

#include <cstring>
#include <cstdbool>
#include <cstdlib>
#include "snake.hpp"
#include "key.hpp"
#include <ncurses.h>

// Initialize snake
Snake *init_snake(int x, int y)
{
  Snake *head = create_tail(x, y);
  Snake *tail1 = create_tail(x - 1, y);
  Snake *tail2 = create_tail(x - 2, y);
  tail1->next = tail2;
  head->next = tail1;
  return head;
}

// Creates one tail
Snake *create_tail(int x, int y)
{
  Snake *snake = new Snake;
  snake->color[0] = 0;
  snake->color[1] = 0;
  snake->color[2] = 255;
  /* snake->color = {0, 0, 255}; */
  snake->symbol = '#';
  snake->next = NULL;
  snake->x = x;
  snake->y = y;
  return snake;
}

// Moves the snake in the input direction
Snake *move_snake(Snake *snake, int direction)
{
  int new_x = snake->x;
  int new_y = snake->y;

  // Set the new head to have the x and y coordinates as the existing head of the snake

  switch (direction)
  {
  case UP:
    new_y--;
    break;
  case DOWN:
    new_y++;
    break;
  case RIGHT:
    new_x++;
    break;
  case LEFT:
    new_x--;
    break;
  }
  Snake* new_head = create_tail(new_x, new_y);
  new_head->next = snake;
  snake = remove_tail(snake);

  return new_head;
}

Snake *remove_tail(Snake *snake)
{
  Snake *end = snake;
  while (end->next->next)
    end = end->next;
  free(end->next);
  end->next = NULL;
  return snake;
}

// draws the snake on the board
void draw_snake(Snake *snake)
{
  attron(COLOR_PAIR(1));
  while (snake)
  {
    mvprintw(snake->y, snake->x, "%c", snake->symbol);
    snake = snake->next;
  }
  attroff(COLOR_PAIR(1));
}

// checks if it eats itself, if it does, then return true
bool eat_itself(Snake *snake)
{
  int x = snake->x;
  int y = snake->y;
  Snake *s = snake->next;
  while (s->next) {
    if (s->x == x && s->y == y) {
      return true;
    }
    s = s->next;
  }
  return false;
}

// increase snake length by 1
void grow_snake(Snake *snake) {
    Snake *end = snake;
    // get the second to the last segment of snake
    while (end->next->next)  
      end = end->next;
    int x,y;
    // calculate moving direction of snake
    x = end->x - end->next->x; 
    y = end->y - end->next->y;
    // make new segment at tail, based on the moving direction
    Snake *newtail = create_tail(end->next->x - x, end->next->y - y);
    // add segment to snake
    end->next->next = newtail;
}

// decrease snake length by 1
void shrink_snake(Snake *snake) {
    snake = remove_tail(snake);
}

//return length of snake
int len(Snake *snake) {
    int length = 0;
    while (snake) {
      length++;
      snake = snake->next;
    }
    return length;
}

// checks if the body of snake is on position x,y
bool snake_occupies(Snake *snake, int x, int y) {
    while (snake) {
        if (snake->x == x && snake->y == y) return true;
        snake = snake->next;
    }
    return false;
}