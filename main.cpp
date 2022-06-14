#include <iostream>
#include <ncurses.h>
#include <thread>
#include "Map.h"
#include "Snake.h"

using namespace std;

int main(){
  Map m = Map();

  m.initMap();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  while(TRUE){
    std::this_thread::sleep_for(300ms);
    m.updateMap();
    int key;
    key = getch();
    m.s.changeDirection(key);
    if(m.s.isLife != 1){
      break;
    }
  }
  nodelay(stdscr, FALSE);

  init_pair(9,COLOR_WHITE,COLOR_BLACK);
  attron(COLOR_PAIR(9));
  printw("\nYOU DIE");
  attroff(COLOR_PAIR(9));
  getch();
  refresh();

  clear();
  endwin();
  return 0;
}
