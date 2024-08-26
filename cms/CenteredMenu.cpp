#include "CenteredMenu.h"
#include <algorithm>

char* centered_string(int screen_x, const std::string& string){
    char* centered_string = new char[screen_x + 1];
    int starting_point = screen_x/2 - string.size()/2; 

    //fill with blank spaces
    std::fill(centered_string, centered_string + screen_x, ' ');
    
    //define string starting point
    if (starting_point < 0) {
        std::copy(string.begin(), string.begin() + screen_x, centered_string);
        if (screen_x > 5)
            std::fill(centered_string + screen_x - 3, centered_string + screen_x, '.');
    } else
        std::copy(string.begin(), string.end(), centered_string + starting_point);

    //add null terminator
    centered_string[screen_x] = '\0';
    return centered_string;
}

int cms::centered_menu(const std::string& title, const std::vector<std::string>& options){
    //disable echo and cursor
    noecho();
    curs_set(FALSE);

    //method variables
    int option_selected = 0, menux = COLS/2, menuy = LINES/2, submenux = menux - 2, submenuy = menuy - 4;
    bool pressed_enter = false;
    ITEM** items;
    MENU* my_menu;
    WINDOW* menu_window, *menu_subwindow;
    std::vector<char*> centered_cstrings;

    //items and menu creation
    items = new ITEM*[options.size() + 1];
    for (int i = 0; i < (int)options.size(); i++){
        centered_cstrings.push_back(centered_string(submenux, options[i]));
        items[i] = new_item(centered_cstrings.back(), "");
    }
    items[options.size()] = (ITEM*)NULL;
    my_menu = new_menu((ITEM**)items);
    
    //mvprintw(LINES - 1, 0, "Prees ESC to Exit");

    //window creation
    menu_window = newwin(menuy, menux, menuy/2, menux/2);
    werase(menu_window);
    box(menu_window, 0, 0);
    keypad(menu_window, TRUE);
    menu_subwindow = derwin(menu_window, submenuy, submenux, 3, 1);

    //setting menu
    set_menu_win(my_menu, menu_window);
    set_menu_sub(my_menu, menu_subwindow);
    set_menu_format(my_menu, submenuy, 1);

    set_menu_mark(my_menu, "");
    mvwprintw(menu_window, 1, menux/2 - title.size()/2, "%s", title.c_str());

    post_menu(my_menu);
    refresh();

    // menu's main loop
    int c;
    while (!pressed_enter && (c = wgetch(menu_window)) != 27)
    {
        switch (c)
        {
        case KEY_DOWN:
            if (option_selected != (int)options.size() - 1)
                ++option_selected;
            menu_driver(my_menu, REQ_DOWN_ITEM);
            break;
        case KEY_UP:
            if (option_selected)
                --option_selected;
            menu_driver(my_menu, REQ_UP_ITEM);
            break;
        case 10:
            pressed_enter = true;
            break;            
        default:
            break;
        }
        wrefresh(menu_window);
    }
    
    //erase window content
    werase(menu_window);
    werase(menu_subwindow);
    wrefresh(menu_window);
    wrefresh(menu_subwindow);
    
    //free resources
    delwin(menu_window);
    unpost_menu(my_menu);
    free_menu(my_menu);

    for (int i = 0; i < (int)options.size(); i++){
        free_item(items[i]);
        delete[] centered_cstrings[i];
    }

    delete[] items;

    return pressed_enter?option_selected:-1;
}
