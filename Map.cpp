#include "Map.h"

int Map::isSnakeHere(int i, int j){
  for(int k = 0; k < s.getL()*2; k += 2){
    if((s.isBody[k] == i) && (s.isBody[k+1] == j)){
      return 1;
    }
  }
  return 0;
}

void Map::initMap(){
  initscr();
  resize_term(70,70);

  curs_set(0);
  noecho();

  start_color();
  init_pair(1,COLOR_YELLOW,COLOR_YELLOW);
  init_pair(2,COLOR_BLACK,COLOR_BLACK);
  init_pair(3,COLOR_GREEN,COLOR_GREEN);

  for(int i = 0; i <40; i++){
    for(int j = 0; j <50; j++){
      if(mapArray[i][j]== 1 || mapArray[i][j] == 2){
          attron(COLOR_PAIR(1));
          printw(" ");
          attroff(COLOR_PAIR(1));
      }
      else if(isSnakeHere(i,j) == 1){
        attron(COLOR_PAIR(3));
        printw(" ");
        attroff(COLOR_PAIR(3));
      }
      else{
        attron(COLOR_PAIR(2));
        printw(" ");
        attroff(COLOR_PAIR(2));
      }
    }
    printw("\n");
  }
  refresh();

}
void Map::isCrash(){ //벽 충돌 판정
  for(int i = 0; i < 40; i++){
    for(int j = 0; j < 50; j++){
      if(mapArray[i][j] == 1 && isSnakeHere(i,j) == 1){
        s.isDie();
      }
    }
  }
}

void Map::updateMap(){
  clear();
  s.isMove();
  isCrash();
  start_color();
  init_pair(1,COLOR_YELLOW,COLOR_YELLOW);
  init_pair(2,COLOR_BLACK,COLOR_BLACK);
  init_pair(3,COLOR_GREEN,COLOR_GREEN);

  for(int i = 0; i <40; i++){
    for(int j = 0; j <50; j++){
      if(mapArray[i][j]== 1 || mapArray[i][j] == 2){
          attron(COLOR_PAIR(1));
          printw(" ");
          attroff(COLOR_PAIR(1));
      }
      else if(isSnakeHere(i,j) == 1){
        attron(COLOR_PAIR(3));
        printw(" ");
        attroff(COLOR_PAIR(3));
      }
      else{
        attron(COLOR_PAIR(2));
        printw(" ");
        attroff(COLOR_PAIR(2));
      }
    }
    printw("\n");
  }
  refresh();

}
