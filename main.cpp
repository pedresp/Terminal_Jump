#include "Obstacle.h"
#include "Parser.h"
#include "Jumper.h"
#include <ncurses.h>

#include <fstream>
#include <memory>
#include <vector>

#include <unistd.h>

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

    Jumper jumper(3, 2);
    mvaddch(LINES-1, 3, 'x');
    refresh();

    char charac;

    if (read_scenario(input_scenario, scenario) == CORRECT_SCENARIO) {
        int finger = 0, scenario_size = scenario.size();
        while (finger < scenario_size) {
            charac = getch();
            if (charac == ERR)
                charac = '\0';
            jumper.step(charac);        

            for (int i = finger; i < scenario_size; i++)
                if (!scenario[i]->advance_1_step())
                    finger++;

            refresh();
            usleep(50 * 1000);
        }
    } else
        mvprintw(LINES / 2, 0, "WRONG SCENARIO");

    refresh();
    input_scenario.close();

    getch();
    endwin();

    return 0;
}
