#include "../include/popup.h"
#include "../include/customColors.h"
#include "../include/export.h"
#include <form.h>
#include <ncurses.h>
#include <stdlib.h>

int confirmWin(win *window) {
  int h = 3;
  int w = 100;

  int y = (window->rows - h) / 2;
  int x = (window->cols - w) / 2;

  int yx = w * 0.25;
  int nx = w - yx * 2;

  window->popup = newwin(h, w, y, x);

  wbkgd(window->popup, COLOR_PAIR(primaryBg));
  wattron(window->popup, COLOR_PAIR(border));
  box(window->popup, 0, 0);
  wattroff(window->popup, COLOR_PAIR(border));

  wattron(window->popup, COLOR_PAIR(primaryText));
  mvwprintw(window->popup, 0, 2, " Would you like to extract the cords? ");

  mvwprintw(window->popup, 2, yx, " Y : Yes ");

  mvwprintw(window->popup, 2, nx, " N : No ");
  wattroff(window->popup, COLOR_PAIR(primaryText));

  wrefresh(window->popup);

  int ch;
  while (1) {
    ch = getch();
    if (ch == 'n') {

      werase(window->popup);
      wrefresh(window->popup);
      delwin(window->popup);

      touchwin(window->root);

      wrefresh(window->root);
      wrefresh(window->win1.window);
      wrefresh(window->win2.win);
      wrefresh(window->win4);

      return 0;
    }
    if (ch == 'y') {
      exportCoords(window);
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

int infoWin(win *window) {
  int h = 20;
  int w = 100;

  int y = (window->rows - h) / 2;
  int x = (window->cols - w) / 2;

  int yx = w * 0.25;
  int nx = w - yx * 2;

  window->infoPopup = newwin(h, w, y, x);

  wbkgd(window->infoPopup, COLOR_PAIR(primaryBg));

  wattron(window->infoPopup, COLOR_PAIR(bordr));
  box(window->infoPopup, 0, 0);
  wattroff(window->infoPopup, COLOR_PAIR(bordr));

  wattron(window->infoPopup, COLOR_PAIR(primaryText) | A_BOLD);
  mvwprintw(window->infoPopup, 0, 2, "Key bindings");

  mvwprintw(window->infoPopup, 1, 2, "Movement");
  mvwprintw(window->infoPopup, 3, 2, "H: left");
  mvwprintw(window->infoPopup, 4, 2, "J: down");
  mvwprintw(window->infoPopup, 5, 2, "L: right ");
  mvwprintw(window->infoPopup, 6, 2, "K: up");

  mvwprintw(window->infoPopup, 8, 2, "Resize");

  mvwprintw(window->infoPopup, 10, 2, "R: reset");
  mvwprintw(window->infoPopup, 11, 2, "Left Key: reduce widht");
  mvwprintw(window->infoPopup, 12, 2, "Down Key: increase height");
  mvwprintw(window->infoPopup, 13, 2, "Right Key: increase width");
  mvwprintw(window->infoPopup, 14, 2, "Up Key: reduce height");

  wattroff(window->infoPopup, COLOR_PAIR(primaryText) | A_BOLD);

  wrefresh(window->infoPopup);

  int ch;
  while (1) {
    ch = getch();
    if (ch == 'q') {

      werase(window->infoPopup);
      wrefresh(window->infoPopup);
      delwin(window->infoPopup);

      touchwin(window->root);

      wrefresh(window->root);
      wrefresh(window->win1.window);
      wrefresh(window->win2.win);
      wrefresh(window->win4);

      return 0;
    }
  }
};
