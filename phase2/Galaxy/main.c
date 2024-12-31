#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#define WIN_SCORE 10
#define EASY_ITEMS 5
#define MEDIUM_ITEMS 10
#define HARD_ITEMS 15
#define EASY_TIME 40
#define MEDIUM_TIME 30
#define HARD_TIME 20

typedef struct
{
    int x, y;
} Pos;

typedef struct
{
    Pos player;
    Pos *items;
    int score;
    int max_items;
    int time_limit;
    time_t start_time;
    char password[51];
} Game;

void init_game(Game *g);
void draw_game(Game *g);
void draw_timeline(Game *g);
void handle_movement(int ch, Pos *p);
void update_items(Game *g);
int check_game_status(Game *g);
void random_colors();
void get_player_info(Game *g);
void show_msg(const char *msg);
void draw_menu_border();
void draw_win_loss_screen(const char *msg);

int main()
{
    Game g;
    srand(time(0));
    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    start_color();

    if (!can_change_color())
    {
        endwin();
        printf("Your terminal does not support color changes.\n");
        return 1;
    }

    random_colors();
    get_player_info(&g);
    init_game(&g);

    timeout(100);
    while (1)
    {
        draw_game(&g);
        int ch = getch();
        handle_movement(ch, &g.player);
        update_items(&g);
        if (check_game_status(&g))
            break;
    }

    free(g.items);
    endwin();
    return 0;
}

void init_game(Game *g)
{
    g->score = 0;
    g->start_time = time(NULL);
    g->player.x = COLS / 2;
    g->player.y = LINES / 2;
    g->items = malloc(g->max_items * sizeof(Pos));

    for (int i = 0; i < g->max_items; ++i)
    {
        g->items[i].x = rand() % COLS;
        g->items[i].y = rand() % LINES;
    }
}

void draw_game(Game *g)
{
    clear();
    mvprintw(0, 0, "Score: %d", g->score);
    //mvprintw(0, COLS - strlen(g->name) - 1, "%s", g->name);

    draw_timeline(g);

    attron(COLOR_PAIR(1));
    mvprintw(g->player.y, g->player.x, "@");
    attroff(COLOR_PAIR(1));

    for (int i = 0; i < g->max_items; ++i)
    {
        attron(COLOR_PAIR((i % 7) + 2));
        mvprintw(g->items[i].y, g->items[i].x, "*");
        attroff(COLOR_PAIR((i % 7) + 2));
    }

    refresh();
}

void draw_timeline(Game *g)
{
    time_t elapsed = time(NULL) - g->start_time;
    int remaining = g->time_limit - elapsed;
    float fraction = (float)remaining / g->time_limit;
    int width = (COLS / 3 - 1) * fraction;

    mvprintw(2, 0, "[");
    attron(COLOR_PAIR(3));
    for (int i = 1; i <= width; ++i)
        mvprintw(2, i, "#");
    attroff(COLOR_PAIR(3));

    attron(COLOR_PAIR(2));
    for (int i = width + 1; i <= COLS / 3 - 1; ++i)
        mvprintw(2, i, ".");
    attroff(COLOR_PAIR(2));

    mvprintw(2, COLS / 3, "]");
    mvprintw(1, 0, "Time: %d", remaining);
}

void handle_movement(int ch, Pos *p)
{
    switch (ch)
    {
    case KEY_UP:
        if (p->y > 0)
            --p->y;
        break;
    case KEY_DOWN:
        if (p->y < LINES - 1)
            ++p->y;
        break;
    case KEY_LEFT:
        if (p->x > 0)
            --p->x;
        break;
    case KEY_RIGHT:
        if (p->x < COLS - 1)
            ++p->x;
        break;
    case 'q':
        endwin();
        exit(0);
    }
}

void update_items(Game *g)
{
    for (int i = 0; i < g->max_items; ++i)
    {
        if (g->player.x == g->items[i].x && g->player.y == g->items[i].y)
        {
            g->items[i].x = rand() % COLS;
            g->items[i].y = rand() % LINES;
            ++g->score;
        }
    }
}

int check_game_status(Game *g)
{
    if (g->score >= WIN_SCORE)
    {
        draw_win_loss_screen("You Win!");
        return 1;
    }

    if (time(NULL) - g->start_time >= g->time_limit)
    {
        draw_win_loss_screen("You Lose!");
        return 1;
    }

    return 0;
}

void random_colors()
{
    for (int i = 1; i <= 7; ++i)
    {
        int r = rand() % 1001;
        int g = rand() % 1001;
        int b = rand() % 1001;
        init_color(i, r, g, b);
        init_pair(i, i, COLOR_BLACK);
    }
}

void get_player_info(Game *g)
{
    char password[51] = "ASM{RAW_PASSWORD}";
    echo();
    draw_menu_border();
    mvprintw(LINES / 2 - 2, COLS / 2 - 15, "Enter password: ");
    getnstr(g->password, 50);
    noecho();
    clear();

    if(strcmp(g->password, password) != 0)
    {
        draw_win_loss_screen("Wrong Password!");
        exit(0);
    }

    const char *levels[] = {"Easy", "Medium", "Hard"};
    int choice = 0;

    while (1)
    {
        draw_menu_border();
        mvprintw(1, 1, "Select Difficulty:");
        for (int i = 0; i < 3; ++i)
        {
            if (i == choice)
                attron(A_REVERSE);
            mvprintw(4 + i, 3, "%s", levels[i]);
            if (i == choice)
                attroff(A_REVERSE);
        }

        int ch = getch();
        if (ch == KEY_UP)
            choice = (choice == 0) ? 2 : choice - 1;
        else if (ch == KEY_DOWN)
            choice = (choice == 2) ? 0 : choice + 1;
        else if (ch == 10)
            break;
    }

    switch (choice)
    {
    case 0:
        g->max_items = EASY_ITEMS;
        g->time_limit = EASY_TIME;
        break;
    case 1:
        g->max_items = MEDIUM_ITEMS;
        g->time_limit = MEDIUM_TIME;
        break;
    case 2:
        g->max_items = HARD_ITEMS;
        g->time_limit = HARD_TIME;
        break;
    }
    clear();
}

void draw_menu_border()
{
    clear();
    for (int x = 0; x < COLS; ++x)
    {
        mvprintw(0, x, "-");
        mvprintw(LINES - 1, x, "-");
    }
    for (int y = 0; y < LINES; ++y)
    {
        mvprintw(y, 0, "|");
        mvprintw(y, COLS - 1, "|");
    }
}

void draw_win_loss_screen(const char *msg)
{
    clear();
    attron(COLOR_PAIR(1));
    mvprintw(LINES / 2 - 2, (COLS - strlen(msg)) / 2, "%s", msg);
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(2));
    mvprintw(LINES / 2, (COLS - 25) / 2, "Press any key to exit...");
    attroff(COLOR_PAIR(2));
    refresh();
    sleep(3);
    timeout(-1);
    getch();
}

