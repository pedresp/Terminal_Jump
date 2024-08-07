#include "Obstacle.h"
#include "Parser.h"
#include <ncurses.h>

#include <memory>
#include <vector>
#include <fstream>

#include <unistd.h>

int main() {
    initscr();
    start_color();
    curs_set(false);
    printw("Welcome to Terminal Jump");

    init_pair(10, COLOR_WHITE, COLOR_GREEN);

    refresh();
    getch();

    std::vector<std::unique_ptr<Obstacle>> scenario;
    std::ifstream input_scenario("../scenario.txt");

    if (read_scenario(input_scenario, scenario) == CORRECT_SCENARIO) {
//    scenario.push_back(std::make_unique<Box>(LINES - 1, COLS, 1, 2));
//    scenario.push_back(std::make_unique<Box>(LINES - 1, COLS + 2, 2, 2));
//    scenario.push_back(std::make_unique<Box>(LINES - 1, COLS + 4, 3, 3));
//    scenario.push_back(std::make_unique<Box>(LINES - 1, COLS + 9, 2, 3));

        int finger = 0, scenario_size = scenario.size();
        while (finger < scenario_size) {
            for (int i = finger; i < scenario_size; i++)
                if (!scenario[i]->advance_1_step())
                    finger++;

            refresh();
            usleep(50 * 1000);
        }
    } else
        mvprintw(LINES/2, 0, "WRONG SCENARIO");

    refresh();
    input_scenario.close();

    getch();
    endwin();

    return 0;
}
