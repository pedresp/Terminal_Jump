#ifndef __CMS_HEADER__
#define __CMS_HEADER__

#include <ncurses.h>
#include <menu.h>

#include <string>
#include <vector>

namespace cms {
int centered_menu(const std::string& title, const std::vector<std::string>& options);
}

#endif