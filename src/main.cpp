
#define _XOPEN_SOURCE_EXTENDED 1
#include <functional>
#include <locale.h>
#include <ncurses.h>
#include <stdlib.h>  // For exit()
#include <string.h>
#include <unistd.h>
#include <wchar.h>

namespace mdn {
    constexpr int MENU_HEIGHT = 10, MENU_WIDTH = 40;
    cchar_t       hline, vline, rounded_ul, rounded_ur, rounded_ll, rounded_lr;
    bool          exitApp;

    enum class Color {
        MUTE = 8,
        HIGHLIGHT,
    };

    enum class Pair {
        MUTE = 1,
        HIGHLIGHT,
    };

    struct MenuItem {
        const char          *title;
        std::function<int()> callable;
    };

    int
    run_cli() {
        return 0;
    }

    int
    run_gui() {
        mvprintw(LINES - 1, 0, "Option currently unavailable");
        refresh();

        return 0;
    }

    MenuItem mainMenu[] = {
        // Menu items
        {"CLI",  run_cli  },
        {"GUI",  run_gui  },
        {"Exit", []() {
             mdn::exitApp = true;
             return 0;
         }},
    };
    int mainMenuLen = sizeof(mainMenu) / sizeof(*mainMenu);  // Number of menu items

    void
    init_characters() {
        setcchar(&hline, L"─", A_NORMAL, 0, NULL);
        setcchar(&vline, L"│", A_NORMAL, 0, NULL);
        setcchar(&rounded_ul, L"╭", A_NORMAL, 0, NULL);  // Top-left rounded
        setcchar(&rounded_ur, L"╮", A_NORMAL, 0, NULL);  // Top-right rounded
        setcchar(&rounded_ll, L"╰", A_NORMAL, 0, NULL);  // Bottom-left rounded
        setcchar(&rounded_lr, L"╯", A_NORMAL, 0, NULL);  // Bottom-right rounded
    }

    short
    to_ncurses_color(int hex_component) {
        return (short)(((double)hex_component / 255.0) * 1000.0);
    }

    void
    init_colors() {
        init_color(static_cast<short>(mdn::Color::MUTE), to_ncurses_color(0xA0), to_ncurses_color(0xA0), to_ncurses_color(0xA0));
        init_color(static_cast<short>(mdn::Color::HIGHLIGHT), to_ncurses_color(0xFF), to_ncurses_color(0xFF), to_ncurses_color(0xFF));

        init_pair(static_cast<short>(mdn::Pair::MUTE), static_cast<short>(mdn::Color::MUTE), COLOR_BLACK);
        init_pair(static_cast<short>(mdn::Pair::HIGHLIGHT), static_cast<short>(mdn::Color::HIGHLIGHT), COLOR_BLACK);
    }

    void
    print_main_menu(WINDOW *menu_win, int highlight) {
        int offsetX, offsetY;

        offsetX = 2;
        offsetY = 2;
        wattrset(menu_win, COLOR_PAIR(static_cast<short>(mdn::Pair::MUTE)));
        wborder_set(menu_win,
                    &mdn::vline,
                    &mdn::vline,
                    &mdn::hline,
                    &mdn::hline,
                    &mdn::rounded_ul,
                    &mdn::rounded_ur,
                    &mdn::rounded_ll,
                    &mdn::rounded_lr);

        for (int i = 0; i < mainMenuLen; ++i) {
            if (highlight == i + 1) {
                wattrset(menu_win, COLOR_PAIR(static_cast<short>(mdn::Pair::HIGHLIGHT)));
            } else {
                wattrset(menu_win, COLOR_PAIR(static_cast<short>(mdn::Pair::MUTE)));
            }
            mvwprintw(menu_win, offsetY + i, offsetX, "%s", mainMenu[i].title);
        }
        wrefresh(menu_win);
    }
}  // namespace mdn

int
main(int argc, char *argv[]) {
    WINDOW *menu_win;
    int     status    = 0;
    int     highlight = 1;  // Current highlighted menu item (1-indexed)
    int     choice    = 0;  // User's final choice
    int     c;              // Character input

    (void)argc;
    (void)argv;

    // Initialize ncurses
    setlocale(LC_ALL, "");
    initscr();
    start_color();
    clear();
    noecho();
    cbreak();
    curs_set(0);
    keypad(stdscr, TRUE);
    mdn::init_characters();
    mdn::init_colors();

    // Print instructions
    refresh();

    // Create a new window for the menu
    menu_win = newwin(mdn::MENU_HEIGHT, mdn::MENU_WIDTH, (LINES - mdn::MENU_HEIGHT) / 2, (COLS - mdn::MENU_WIDTH) / 2);
    keypad(menu_win, TRUE);  // Enable special keys for the menu window

    // Loop to handle menu interaction
    while (!mdn::exitApp) {
        mdn::print_main_menu(menu_win, highlight);  // Display the menu
        c = wgetch(menu_win);                       // Get character input from the menu window

        switch (c) {
            case KEY_UP:
                if (highlight == 1) {
                    highlight = mdn::mainMenuLen;
                } else {
                    --highlight;
                }
                break;
            case KEY_DOWN:
                if (highlight == mdn::mainMenuLen) {
                    highlight = 1;
                } else {
                    ++highlight;
                }
                break;
            case '\n':  // Enter key
                choice = highlight;
                break;
            case 'q':  // 'q' to quit
                mdn::exitApp = true;
                break;
            default:
                // Handle other inputs if needed
                break;
        }

        if (choice != 0) {  // If a choice has been made
            status = mdn::mainMenu[choice - 1].callable();
            choice = 0;     // Reset choice for next interaction
        }
    }

    // Clear the message before exiting
    mvprintw(LINES - 2, 0, "                                      ");
    mvprintw(LINES - 1, 0, "Exiting program. Goodbye!");
    refresh();
    sleep(1);  // Pause for a moment

    endwin();

    return status;
}
