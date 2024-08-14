#include "Jumper.h"
#include "Obstacle.h"
#include "Parser.h"
#include <ncurses.h>

#include <fstream>
#include <memory>
#include <vector>

#include <unistd.h>

int JUMPER_X = 3;

int main() {
    initscr();
    start_color();
    curs_set(false);
    nodelay(stdscr, 1);
    printw("Welcome to Terminal Jump");

    init_pair(10, COLOR_WHITE, COLOR_GREEN);

    refresh();
    getch();

    std::vector<std::unique_ptr<Obstacle>> scenario;
    std::ifstream input_scenario("../scenario.txt");

    Jumper jumper(JUMPER_X, 2);
    mvaddch(LINES - 1, 3, 'x');
    refresh();

    char charac;

    if (read_scenario(input_scenario, scenario) == CORRECT_SCENARIO) {
        int finger = 0, scenario_size = scenario.size();
        Obstacle* obstacle_on_jumper_coordinates;

        for (auto i = scenario.begin(); i < scenario.end(); i++)
            (*i)->draw();
        refresh();

        bool game_over = false;
        while (!game_over && finger < scenario_size) {
            charac = getch();
            obstacle_on_jumper_coordinates = nullptr;

            for (int i = finger; i < scenario_size; i++) {
                if (!scenario[i]->advance_1_step())
                    finger++;

                if (JUMPER_X >= scenario[i]->getX() && JUMPER_X < scenario[i]->getX() + scenario[i]->getWidth())
                    obstacle_on_jumper_coordinates = scenario[i].get();
            }

            if (charac == ERR)
                charac = '\0';
            jumper.step(charac);

            jumper.resetFloor();

            // check if there is a collision or touch between jumper and obstacles
            if (obstacle_on_jumper_coordinates != nullptr) {
                mvprintw(13, 0, "LANDED: %d", !jumper.getUp() && LINES - jumper.getY() - 1 == obstacle_on_jumper_coordinates->getHeight());
                if (LINES - jumper.getY() <= obstacle_on_jumper_coordinates->getHeight())
                    game_over = true;
                else if (!jumper.getUp() && LINES - jumper.getY() - 1 == obstacle_on_jumper_coordinates->getHeight())
                    jumper.landed();
            }

            refresh();
            usleep(50 * 1000);
        }

        // decide final screen (game over or victory)
        if (game_over)
            mvprintw(LINES / 2, COLS / 2, "GAME OVER !!");
        else
            mvprintw(LINES / 2, COLS / 2, "VICTORY !!");

    } else
        mvprintw(LINES / 2, 0, "WRONG SCENARIO");

    refresh();
    input_scenario.close();

    nodelay(stdscr, 0);
    getch();
    endwin();

    return 0;
}
