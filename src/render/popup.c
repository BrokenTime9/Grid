#include "../../include/render/popup.h"
#include "../../include/lib/export.h"
#include "../../include/themes/customColors.h"
#include <form.h>
#include <ncurses.h>
#include <stdlib.h>

int confirmWin(win *w) {
  int h = 3;
  int wd = 100;

  int y = (w->rows - h) / 2;
  int x = (w->cols - wd) / 2;

  int yx = wd * 0.25;
  int nx = wd - yx * 2;

  w->win[POPUP] = newwin(h, wd, y, x);

  wbkgd(w->win[POPUP], COLOR_PAIR(primaryBg));

  wattron(w->win[POPUP], COLOR_PAIR(bordr));
  box(w->win[POPUP], 0, 0);
  wattroff(w->win[POPUP], COLOR_PAIR(bordr));

  wattron(w->win[POPUP], COLOR_PAIR(primaryText));
  mvwprintw(w->win[POPUP], 0, 2, " Would you like to extract the cords? ");

  mvwprintw(w->win[POPUP], 2, yx, " Y : Yes ");

  mvwprintw(w->win[POPUP], 2, nx, " N : No ");
  wattroff(w->win[POPUP], COLOR_PAIR(primaryText));

  wrefresh(w->win[POPUP]);

  int ch;
  while (1) {
    ch = getch();
    if (ch == 'n') {

      werase(w->win[POPUP]);
      wrefresh(w->win[POPUP]);
      delwin(w->win[POPUP]);

      touchwin(w->win[ROOT]);

      wrefresh(w->win[ROOT]);
      wrefresh(w->win[GRID]);
      wrefresh(w->win[SIDEBAR]);
      wrefresh(w->win[INFO]);

      return 0;
    }
    if (ch == 'y') {
      exportCoords(w);
      return 1;
    }
  }
};

int valueSetter(win *window) {
  int ch;
  int h = 7;
  int w = 15;

  int y = (window->rows - h) / 2;
  int x = (window->cols / 2) - w;

  int fieldx = x + 15;

  keypad(stdscr, TRUE);

  FIELD *field[5];
  FORM *my_form;
  curs_set(2);

  field[0] = new_field(1, 10, y + 1, fieldx, 0, 0);
  field[1] = new_field(1, 10, y + 3, fieldx, 0, 0);
  field[2] = new_field(1, 10, y + 5, fieldx, 0, 0);
  field[3] = new_field(1, 10, y + 7, fieldx, 0, 0);
  field[4] = NULL;

  int max_wid = window->cols * 0.75 - 2;
  int max_hgt = window->rows - 2;
  window->win1.maxh = max_hgt;
  window->win1.maxw = max_wid;

  set_field_type(field[0], TYPE_INTEGER, 0, 1, max_wid);
  set_field_back(field[0], A_UNDERLINE);
  field_opts_off(field[0], O_AUTOSKIP);

  set_field_type(field[1], TYPE_INTEGER, 0, 1, max_hgt);
  set_field_back(field[1], A_UNDERLINE);
  field_opts_off(field[1], O_AUTOSKIP);

  set_field_type(field[2], TYPE_INTEGER, 0, 1, 100);
  set_field_back(field[2], A_UNDERLINE);
  field_opts_off(field[2], O_AUTOSKIP);

  set_field_type(field[3], TYPE_INTEGER, 0, 1, 100);
  set_field_back(field[3], A_UNDERLINE);
  field_opts_off(field[3], O_AUTOSKIP);

  my_form = new_form(field);

  post_form(my_form);
  refresh();

  wattron(stdscr, primaryText);
  mvprintw(y + 1, x, "Cell width :");
  mvprintw(y + 3, x, "Cell height :");
  mvprintw(y + 5, x, "Columns :");
  mvprintw(y + 7, x, "Rows :");

  mvprintw(LINES - 4, 0, "-> Use ENTER key to switch between fields");
  mvprintw(LINES - 3, 0, "-> Max Height %d ", max_hgt);
  mvprintw(LINES - 2, 0, "-> Max Widht %d ", max_wid);
  mvprintw(LINES - 1, 0, "-> Use Y key to proceed to the next menu ");

  wattroff(stdscr, primaryText);

  refresh();

  while ((ch = wgetch(stdscr))) {
    switch (ch) {
    case KEY_DOWN:
      form_driver(my_form, REQ_NEXT_FIELD);
      form_driver(my_form, REQ_END_LINE);
      break;
    case 10:
      form_driver(my_form, REQ_NEXT_FIELD);
      form_driver(my_form, REQ_END_LINE);

      if (field_status(field[0]) && field_status(field[1]) &&
          field_status(field[2]) && field_status(field[3])) {

        form_driver(my_form, REQ_VALIDATION);

        int wt = atoi(field_buffer(field[0], 0));
        int ht = atoi(field_buffer(field[1], 0));
        int colt = atoi(field_buffer(field[2], 0));
        int rowt = atoi(field_buffer(field[3], 0));

        window->win1.info.w = atoi(field_buffer(field[0], 0));
        window->win1.info.h = atoi(field_buffer(field[1], 0));
        window->win1.info.cols = atoi(field_buffer(field[2], 0));
        window->win1.info.rows = atoi(field_buffer(field[3], 0));

        unpost_form(my_form);
        free_form(my_form);
        free_field(field[0]);
        free_field(field[1]);
        free_field(field[2]);
        free_field(field[3]);

        return 0;
      }
      break;
    case KEY_UP:
      form_driver(my_form, REQ_PREV_FIELD);
      form_driver(my_form, REQ_END_LINE);
      break;

    case KEY_BACKSPACE:
      form_driver(my_form, REQ_DEL_PREV);
      break;

    case 'q':
      unpost_form(my_form);
      free_form(my_form);
      free_field(field[0]);
      free_field(field[1]);
      free_field(field[2]);
      free_field(field[3]);

      endwin();

      return 1;

    case KEY_DC:
      form_driver(my_form, REQ_DEL_CHAR);
      break;

    case 'y':
      form_driver(my_form, REQ_NEXT_FIELD);
      form_driver(my_form, REQ_END_LINE);

      if (field_status(field[0]) && field_status(field[1]) &&
          field_status(field[2]) && field_status(field[3])) {
        form_driver(my_form, REQ_VALIDATION);

        int wt = atoi(field_buffer(field[0], 0));
        int ht = atoi(field_buffer(field[1], 0));
        int colt = atoi(field_buffer(field[2], 0));
        int rowt = atoi(field_buffer(field[3], 0));

        window->win1.info.w = atoi(field_buffer(field[0], 0));
        window->win1.info.h = atoi(field_buffer(field[1], 0));
        window->win1.info.cols = atoi(field_buffer(field[2], 0));
        window->win1.info.rows = atoi(field_buffer(field[3], 0));

        unpost_form(my_form);
        free_form(my_form);
        free_field(field[0]);
        free_field(field[1]);
        free_field(field[2]);
        free_field(field[3]);

        return 0;
      } else {

        mvprintw(y + 10, x, "**Please ENTER All values to proceed**");
      }

      break;

    default:
      if ((ch >= '0' && ch <= '9'))
        form_driver(my_form, ch);
      break;
    }
  }

  return 0;
};

int infoWin(win *w) {
  int h = 20;
  int wd = 100;

  int y = (w->rows - h) / 2;
  int x = (w->cols - wd) / 2;

  int yx = wd * 0.25;
  int nx = wd - yx * 2;

  w->win[INFOPOPUP] = newwin(h, wd, y, x);

  wbkgd(w->win[INFOPOPUP], COLOR_PAIR(primaryBg));

  wattron(w->win[INFOPOPUP], COLOR_PAIR(bordr));
  box(w->win[INFOPOPUP], 0, 0);
  wattroff(w->win[INFOPOPUP], COLOR_PAIR(bordr));

  wattron(w->win[INFOPOPUP], COLOR_PAIR(primaryText) | A_BOLD);
  mvwprintw(w->win[INFOPOPUP], 0, 2, "Key bindings");

  mvwprintw(w->win[INFOPOPUP], 1, 2, "Movement");
  mvwprintw(w->win[INFOPOPUP], 3, 2, "H: left");
  mvwprintw(w->win[INFOPOPUP], 4, 2, "J: down");
  mvwprintw(w->win[INFOPOPUP], 5, 2, "L: right ");
  mvwprintw(w->win[INFOPOPUP], 6, 2, "K: up");

  mvwprintw(w->win[INFOPOPUP], 8, 2, "Resize");

  mvwprintw(w->win[INFOPOPUP], 10, 2, "R: reset");
  mvwprintw(w->win[INFOPOPUP], 11, 2, "Left Key: reduce widht");
  mvwprintw(w->win[INFOPOPUP], 12, 2, "Down Key: increase height");
  mvwprintw(w->win[INFOPOPUP], 13, 2, "Right Key: increase width");
  mvwprintw(w->win[INFOPOPUP], 14, 2, "Up Key: reduce height");

  wattroff(w->win[INFOPOPUP], COLOR_PAIR(primaryText) | A_BOLD);

  wrefresh(w->win[INFOPOPUP]);

  int ch;
  while (1) {
    ch = getch();
    if (ch == 'q') {

      werase(w->win[INFOPOPUP]);
      wrefresh(w->win[INFOPOPUP]);
      delwin(w->win[INFOPOPUP]);

      touchwin(w->win[ROOT]);

      wrefresh(w->win[ROOT]);
      wrefresh(w->win[GRID]);
      wrefresh(w->win[SIDEBAR]);
      wrefresh(w->win[INFO]);

      return 0;
    }
  }
};
