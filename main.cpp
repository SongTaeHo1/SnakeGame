#include <iostream>
#include <ncurses.h>
#include <thread>
#include "Map.h"
#include "Snake.h"

using namespace std;

int main(){
  Map m = Map();

  int randT = 0;
  int randD = 0;
  int randP = 0;
  m.initMap();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  srand(time(NULL));
  while(TRUE){
    std::this_thread::sleep_for(250ms);

    randT += rand() % 5;
    if(randT > 50){
      if(m.GrowItem == 3){
        m.delGrow();
      }
      m.createGrow();
      randT = 0;
    }
    randD += rand() % 5;
    if(randD > 50){
      if(m.PoisonItem == 3){
        m.delPoison();
      }
      m.createPoison();
      randD = 0;
    }
    randP += rand() % 3;
    if(randP > 70){
      m.createPotal();
      randP = 0;
    }

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
  printw("\nYOU DIE\nEnter Any Key to Game End");
  attroff(COLOR_PAIR(9));
  getch();
  refresh();

  clear();
  endwin();
  return 0;
}
