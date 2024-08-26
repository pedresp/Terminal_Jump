#include "Jumper.h"
#include "Obstacle.h"
#include "Parser.h"
#include "CenteredMenu.h"
#include <ncurses.h>

#include <fstream>
#include <memory>
#include <vector>
#include <filesystem>

#include <unistd.h>

int JUMPER_X = 3;
int JUMP_HEIGHT = 2;

std::vector<std::string> list_files(std::string route = "."){
    std::vector<std::string> ldir;

    for (const auto& file : std::filesystem::directory_iterator(route))
        if (std::filesystem::is_regular_file(file.path()))
            ldir.push_back(file.path());

    return ldir;
}

bool launch_scenario(std::ifstream& input_scenario, std::vector<std::unique_ptr<Obstacle>>& scenario, Jumper& jumper){
    char charac;
    if (read_scenario(input_scenario, scenario) == CORRECT_SCENARIO) {
        int finger = 0, scenario_size = scenario.size();
        Obstacle* obstacle_on_jumper_coordinates;

        bool game_over = true;
        while (game_over) {
            sleep(1);

            erase();
            mvprintw(0, 0, "Welcome to Terminal Jump");

            jumper.restart();
            jumper.draw();
            for (auto i = scenario.begin(); i < scenario.end(); i++) {
                (*i)->restart();
                (*i)->draw();
            }
            refresh();

            finger = 0;
            game_over = false;
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
                usleep(60 * 1000);
            }

            // decide final screen (game over or victory)
            if (game_over)
                mvprintw(LINES / 2, COLS / 2, "GAME OVER !!");
            else
                mvprintw(LINES / 2, COLS / 2, "VICTORY !!");
            refresh();
        }

        return true;
    } else
        return false;
}

int main() {
    initscr();
    start_color();
    curs_set(false);
    nodelay(stdscr, 1);
    noecho();
    printw("Welcome to Terminal Jump");

    init_pair(10, COLOR_WHITE, COLOR_GREEN);

    refresh();
    getch();

    //scenario variables
    std::vector<std::unique_ptr<Obstacle>> scenario;
    Jumper jumper(JUMPER_X, JUMP_HEIGHT);

    std::string prefix = "../scenarios/";
    std::vector<std::string> available_scenarios, files_list = list_files(prefix);
    for (int i = 0; i < (int)files_list.size(); ++i)
        available_scenarios.push_back(files_list[i].substr(prefix.size()));

    //select scenario via cms
    std::ifstream input_scenario(files_list[cms::centered_menu("TERMINAL JUMP", available_scenarios)]);

    if (launch_scenario(input_scenario, scenario, jumper) == false)
        mvprintw(LINES / 2, 0, "WRONG SCENARIO");

    refresh();
    input_scenario.close();

    nodelay(stdscr, 0);
    getch();
    endwin();

    return 0;
}
