/*game.cpp -------
*
* Filename: game.cpp
* Description:
* Author: Adeel Bhutta
* Maintainer:
* Created: Sat Sep 12 13:16:12 2022
* Last-Updated: September 12 16:51 2022
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

/*Copyright (c) 2022 Adeel Bhutta
*
* All rights reserved.
*
* Additional copyrights may follow
*/
#include <ncurses.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
#include <algorithm>
#include "snake.hpp"
#include "food.hpp"
#include "game_window.hpp"
#include "key.hpp"
#include "game.hpp"
#include "obstacle.hpp"
using namespace std;

Direction snakeDirection;
void generate_points(int *food_x, int *food_y, int width, int height, int x_offset, int y_offset){
    *food_x = rand() % width + x_offset;
    *food_y = rand() % height + y_offset;
}
void initial_direction() {
    // Init direction
    int initialDirection = rand() % 2; // 0 for left, 1 for right
    if (initialDirection == 0) {
        snakeDirection = LEFT;
    } else {
        snakeDirection = RIGHT;
    }
}
void display_start_screen() {
    clear(); // Clear the screen
    mvprintw(8, 10, "Welcome to the Snake Game!");
    mvprintw(10, 10, "Overview: Navigate the snake via up, down, left, and right button");
    mvprintw(11, 10, "to eat food and grow longer.");
    mvprintw(12, 10, "Scoring: Each food eaten increases your score.");
    mvprintw(13, 10, "Controls: Use arrow keys to control the snake.");
    mvprintw(14, 10, "Press 'S' or 's' to start the game.");
    mvprintw(15, 10, "Press 'P' or 'p' to pause the game.");
    mvprintw(16, 10, "Press 'F' or 'f' to speed up the game.");
    mvprintw(17, 10, "Press 'D' or 'd' to slow down the game.");
    mvprintw(18, 10, "Press 'E' or 'e' to start the game in Easy mode.");
    mvprintw(19, 10, "Press 'H' or 'h' to start the game in Hard mode.");
    mvprintw(20, 10, "Press 'A' or 'a' to start the game in Advanced mode.");
    refresh(); // Refresh the screen to update the display
    }
void display_pause_screen(int score) {
    clear(); // Clear the screen
    mvprintw(8, 10, "Game paused!");
    mvprintw(12, 10, "Score: %d", score);
    refresh(); // Refresh the screen to update the display
    }
void display_dead_screen(int score) {
    clear(); // Clear the screen
    mvprintw(8, 10, "Game over!");
    mvprintw(12, 10, "Score: %d", score);
    refresh(); // Refresh the screen to update the display
    }
void change_direction(enum Direction c) {
    switch(c) {
        case LEFT:
            if (snakeDirection != RIGHT) snakeDirection = c;
            break;
        case RIGHT: 
            if (snakeDirection != LEFT) snakeDirection = c;
            break;
        case UP: 
            if (snakeDirection != DOWN) snakeDirection = c;
            break;
        case DOWN: 
            if (snakeDirection != UP) snakeDirection = c; 
            break; 
        default:
            break;                     
    }
}
void add_obstacles(Obstacle*& obstacles, int count, int width, int height, int x_offset, int y_offset) {
    for(int i = 0; i < count; i++) {
        int size = rand() % 3 + 3; // Size between 3 and 5
        bool isHorizontal = rand() % 2; // 0 for vertical, 1 for horizontal
        int x = rand() % (width - size) + x_offset + 1;
        int y = rand() % (height - size) + y_offset + 1;
        Obstacle* new_obstacle = create_obstacle(x, y, size, isHorizontal);
        if(obstacles == NULL) {
            obstacles = new_obstacle;
        } else {
            Obstacle* temp = obstacles;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = new_obstacle; 
        }
    }
}
void game(){
    enum State state = START_SCREEN; // Set the initial state
    static int x_max, y_max; //Max screen size variables
    static int x_offset, y_offset; // distance between the top left corner of your screen and the start of the board
    gamewindow_t *window; // Name of the board
    Snake *snake; // The snake
    Food *foods,*new_food; // List of foods (Not an array)
    Obstacle *obstacles; // List of obstacles
    int score = 0;
    int ob_count = rand() % 8 + 3; // obstacle count

    const int height = 30; 
    const int width = 70;
    char ch;
    int food_count = 20;

    struct timespec timeret;
    timeret.tv_sec = 0;
    timeret.tv_nsec = 999999999/4;
    initscr();
    if (has_colors) {
        start_color();		
	    init_pair(1, COLOR_WHITE, COLOR_BLACK);
        init_pair(2, COLOR_RED, COLOR_BLACK);
        init_pair(3, COLOR_GREEN, COLOR_BLACK);
        init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    }
    initial_direction();
    start_color();
    nodelay(stdscr, TRUE); //Dont wait for char
    noecho(); // Don't echo input chars
    getmaxyx(stdscr, y_max, x_max);
    keypad(stdscr, TRUE); // making keys work
    curs_set(0); // hide cursor
    timeout(100);

    int live = 3; // starts with 3 lives

    while(state != EXIT){
        switch(state){
        case START_SCREEN:
            nodelay(stdscr, FALSE);
            display_start_screen();
            ch = getch(); // Use getch() to wait for a key press
            if (ch == 's' || ch == 'S') {
                nodelay(stdscr, TRUE);
                state = INIT; // Change state to INIT to start the game
                break;
            }
            if (ch == 'E' || ch == 'e') {
                nodelay(stdscr, TRUE);
                food_count = 10;
                state = INIT;
                break;
            }
            if (ch == 'H' || ch == 'h') {
                nodelay(stdscr, TRUE);
                timeret.tv_nsec = (timeret.tv_nsec / 2);
                state = INIT;
                break;
            }
            if (ch == 'A' || ch == 'a') {
                nodelay(stdscr, TRUE);
                timeret.tv_nsec = (timeret.tv_nsec / 4);
                food_count = 30;
                state = INIT;
                break;
            }
            
        case INIT:
            // Setting height and width of the board
            x_offset = (x_max / 2) - (width / 2);
            y_offset = (y_max / 2) - (height / 2);
            
            //Init board
            window = init_GameWindow(x_offset, y_offset, width, height);
            draw_Gamewindow(window);
            display_start_screen();
            snake = init_snake(x_offset + (width / 2), y_offset + (height / 2));
            
            // Init foods
            int food_x, food_y, i;
            enum Type type;

            //Generate 10 foods
            generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
            type = (rand() > RAND_MAX/2) ? Increase : Decrease; // Randomly deciding type of food
            foods = create_food(food_x, food_y, type);
            for(i = 1; i < food_count; i++){
                generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
                while (food_exists(foods,food_x, food_y))
                generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
                type = (rand() > RAND_MAX/2) ? Increase : Decrease;
                new_food = create_food(food_x, food_y, type);
                add_new_food(foods, new_food);
            }
            obstacles = NULL;
            add_obstacles(obstacles, ob_count, width, height, x_offset, y_offset);

            state = ALIVE;
            break;
        case ALIVE:
            ch = get_char();
            // change direction
            if (ch == UP || ch == DOWN || ch == LEFT || ch == RIGHT) {
                change_direction(static_cast<Direction>(ch));
                //clear();
                //mvprintw(21,20, "Direction changed: %c", ch);
                break;
            }
            // check if player wants to quit
            if (ch == 'q' || ch == 'Q') {
                state = DEAD;
                break;
            }
            // check if player wants to pause
            if (ch == 'P' || ch == 'p') {
                state = FREEZE;
                break;
            }
            // slow down the snake
            if (ch == 'd' || ch == 'D') {
                timeret.tv_nsec = (timeret.tv_nsec * 1.5);
                break;
            }
            // speed up the snake
            if (ch == 'F' || ch == 'f') {
                timeret.tv_nsec = (timeret.tv_nsec * 2 / 3);
                break;
            }
            // snake dies when hitting it self
            if (eat_itself(snake)) {
                state = DEAD;
                break;
            }
            // snake dies when hitting obstacles
            if (obstacle_hitten(obstacles, snake->x, snake->y)) {
                state = DEAD;
                break;
            }
            // snake dies when hitting walls
            if (snake->x <= x_offset || snake->x >= x_offset + width 
            || snake->y <= y_offset || snake-> y >= y_offset + height) {
                state = DEAD;
                break;
            }

            
            // check snake head at food
            if (food_exists(foods, snake->x, snake->y)) {
                Type foodType = food_type(foods, snake->x, snake->y); 
                // remove the food 
                remove_eaten_food(foods, snake->x, snake->y);
                // Spawn a new food
                int new_food_x, new_food_y;
                generate_points(&new_food_x, &new_food_y, width, height, x_offset, y_offset);
                while (food_exists(foods, new_food_x, new_food_y) || snake_occupies(snake, new_food_x, new_food_y)) {
                    generate_points(&new_food_x, &new_food_y, width, height, x_offset, y_offset);
                }
                Type newFoodType = (rand() > RAND_MAX/2) ? Increase : Decrease;
                Food* newFood = create_food(new_food_x, new_food_y, newFoodType);
                add_new_food(foods, newFood);

                if (foodType == Increase) {// Grow the snake
                    score++;
                    grow_snake(snake); 
                    break;
                } else if (foodType == Decrease) {
                    score--;
                    if (len(snake) > 2) {
                        shrink_snake(snake); // shrink the snake
                        break;
                    } else {
                        state = DEAD;
                        break;
                    }
                    break;
                }
                break;
            }   
                
            
			// Draw everything on the screen
            clear();
            mvprintw(2,14, "Score: %d", score);
            mvprintw(1,14, "Live: %d", live);
            snake = move_snake(snake, snakeDirection);
            draw_Gamewindow(window);
            draw_snake(snake);
            draw_food(foods);
            draw_obstacles(obstacles);
            break;
        case FREEZE:
            ch = get_char();
            clear();
            display_pause_screen(score);
            if (ch == 'P' || ch == 'p') {
                state = ALIVE;
                break;
            }
        case DEAD:
            live = live - 1;
            // game end
            if (live == 0) {
                clear();
                display_dead_screen(score);
                refresh();
                // read leaderboard scores, save in a vector
                vector<int> scores;
                ifstream read("Leaderboard.txt");
                int temp;
                while (read >> temp) {
                    scores.push_back(temp);
                }
                read.close();
                scores.push_back(score);
                //sort scores
                sort(scores.begin(), scores.end(), greater<int>());
                //keep the 10 high score
                if (scores.size() > 10) {
                    scores.resize(10);
                }
                // overwrite current high score
                ofstream write("Leaderboard.txt", ios::trunc); 
                for (int s : scores) {
                    write << s << endl;
                }
                write.close();

                napms(5000); // wait 5 s before exiting
                endwin();
                exit(0);
            } else {
                // restart game
                snake = init_snake(x_offset + (rand() % (width / 2)),
                 y_offset + (rand() % (height / 2)));
                state = ALIVE;
                break;
            }
        }
        refresh();
        nanosleep(&timeret, NULL);
    }
}
