#include <ncurses.h>

int main() {
    initscr();               
    printw("Welcome to Terminal Jump"); 
    refresh();               
    getch();                 
    endwin();                

    return 0;
}
