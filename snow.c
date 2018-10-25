#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[])
{
    int rows, cols;

    srand(time(NULL));

    initscr();
    noecho();
    cbreak();
    curs_set(FALSE);
    nodelay(stdscr, TRUE);

    getmaxyx(stdscr, rows, cols);

    char *snow = malloc(rows * cols + 1);
    char *updt = malloc(rows * cols);
    memset(snow, ' ', rows * cols);
    memset(updt, 0, rows * cols);
    snow[rows * cols] = '\0';

    int ch;
    while ((ch = getch()) != 113) {
        for (int i = rows - 2; i >= 0; --i) {
            for (int j = i * cols; j < (i + 1) * cols; ++j) {
                if (snow[j] == '*') {
                    if (updt[j] == 0) {
                        if (snow[j + cols] == ' ') {
                            snow[j + cols] = '*';
                            snow[j] = ' ';
                            updt[j + cols] = rand() % 3 + 1;
                        } else if (j != i * cols && snow[j + cols - 1] == ' ') {
                            snow[j + cols - 1] = '*';
                            snow[j] = ' ';
                            updt[j + cols - 1] = rand() % 3 + 1;
                        } else if (j != (i + 1) * cols - 1 && snow[j + cols + 1] == ' ') {
                            snow[j + cols + 1] = '*';
                            snow[j] = ' ';
                            updt[j + cols + 1] = rand() % 3 + 1;
                        }
                    } else {
                        updt[j]--;
                    }
                }
            }
        }

        for (int i = 0; i < cols; ++i) {
            if ((double) rand() / RAND_MAX < 0.002) {
                snow[i] = '*';
            }
        }

        mvprintw(0, 0, "%s", snow);

        refresh();

        usleep(50000);
    }

    endwin();

    free(snow);
    free(updt);

    return 0;
}
