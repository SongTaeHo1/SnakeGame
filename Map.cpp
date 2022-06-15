#include "Map.h"

int Map::isSnakeHere(int i, int j){
  for(int k = 0; k < s.getL()*2; k += 2){
    if((s.isBody[k] == i) && (s.isBody[k+1] == j)){
      return 1;
    }
  }
  return 0;
}

void Map::createGrow(){
  if(GrowItem < 3){
    int flag = 1;
    int row,col;

    while(flag){
      row = rand() % 40;
      col = rand() % 50;
      if(isSnakeHere(row,col) == 0 && mapArray[row][col] == 0 && isPoisonHere(row,col) == 0){
        flag = 0;
      }
    }
    whereGrow.push_back(row);
    whereGrow.push_back(col);
    GrowItem++;
  }
}

void Map::delGrow(int i, int j){
  for(int k = 0; k < GrowItem * 2; k += 2){
    if(whereGrow[k] == i && whereGrow[k+1] == j){
      whereGrow.erase(whereGrow.begin()+k,whereGrow.begin()+k+2);
      GrowItem--;
    }
  }
}

void Map::delGrow(){
  whereGrow.pop_front();
  whereGrow.pop_front();
  GrowItem--;
}

int Map::isGrowHere(int i,int j){
  for(int k = 0; k < GrowItem * 2; k += 2){
    if(whereGrow[k] == i && whereGrow[k+1] == j){
      return 1;
    }
  }
  return 0;
}

void Map::createPoison(){
  if(PoisonItem < 3){
    int flag = 1;
    int row,col;

    while(flag){
      row = rand() % 40;
      col = rand() % 50;
      if(isSnakeHere(row,col) == 0 && mapArray[row][col] == 0 && isGrowHere(row,col) == 0){
        flag = 0;
      }
    }
    wherePoison.push_back(row);
    wherePoison.push_back(col);
    PoisonItem++;
  }
}

void Map::delPoison(int i,int j){
  for(int k = 0; k < PoisonItem * 2; k += 2){
    if(wherePoison[k] == i && wherePoison[k+1] == j){
      wherePoison.erase(wherePoison.begin()+k,wherePoison.begin()+k+2);
      PoisonItem--;
    }
  }
}

void Map::delPoison(){
  wherePoison.pop_front();
  wherePoison.pop_front();
  PoisonItem--;
}

int Map::isPoisonHere(int i,int j){
  for(int k = 0; k < PoisonItem * 2; k += 2){
    if(wherePoison[k] == i && wherePoison[k+1] == j){
      return 1;
    }
  }
  return 0;
}

void Map::createPotal(){
  wherePotal.clear();

  int rowOne,colOne;
  int rowTwo,colTwo;
  int flag = 1;
  while(flag){
    rowOne = rand() % 40;
    colOne = rand() % 50;
    if(mapArray[rowOne][colOne] == 1){
      flag = 0;
    }
  }
  flag = 1;
  while(flag){
    rowTwo = rand() % 40;
    colTwo = rand() % 50;
    if(mapArray[rowTwo][colTwo] == 1 && rowOne != rowTwo && colOne != colTwo){
      flag = 0;
    }
  }
  wherePotal.push_back(rowOne);
  wherePotal.push_back(colOne);
  wherePotal.push_back(rowTwo);
  wherePotal.push_back(colTwo);
  PotalON = 1;
}

int Map::isPotalHere(int i, int j){
  for(int k = 0; k < 3; k += 2){
    if(wherePotal[k] == i && wherePotal[k+1] == j){
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

  whereGrow.clear();
  wherePoison.clear();


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
      if(mapArray[i][j] == 1 && isSnakeHere(i,j) == 1 && isPotalHere(i,j) == 0){
        s.isDie();
      }
    }
  }
}

void Map::isItem(){
  for(int i = 0; i < 40; i++){
    for(int j = 0; j < 50; j++){
      if(isGrowHere(i,j) == 1 && isSnakeHere(i,j) == 1){
        s.increaseL();
        delGrow(i,j);
      }
      if(isPoisonHere(i,j) == 1 && isSnakeHere(i,j) == 1){
        s.decreaseL();
        delPoison(i,j);
      }
    }
  }
}

void Map::updateMap(){
  clear();
  s.isMove();
  isCrash();
  isItem();
  start_color();

  init_pair(1,COLOR_YELLOW,COLOR_YELLOW);
  init_pair(2,COLOR_BLACK,COLOR_BLACK);
  init_pair(3,COLOR_GREEN,COLOR_GREEN);
  init_pair(4,COLOR_RED,COLOR_RED);
  init_pair(5,COLOR_BLUE,COLOR_BLUE);
  init_pair(6,COLOR_MAGENTA,COLOR_MAGENTA);

  for(int i = 0; i <40; i++){
    for(int j = 0; j <50; j++){

      if(isPotalHere(i,j)){
        attron(COLOR_PAIR(6));
        printw(" ");
        attroff(COLOR_PAIR(6));
      }
      else if(mapArray[i][j]== 1 || mapArray[i][j] == 2){
          attron(COLOR_PAIR(1));
          printw(" ");
          attroff(COLOR_PAIR(1));
      }
      else if(isSnakeHere(i,j) == 1){
        attron(COLOR_PAIR(3));
        printw(" ");
        attroff(COLOR_PAIR(3));
      }
      else if(isGrowHere(i,j)){
        attron(COLOR_PAIR(5));
        printw(" ");
        attroff(COLOR_PAIR(5));
      }
      else if(isPoisonHere(i,j)){
        attron(COLOR_PAIR(4));
        printw(" ");
        attroff(COLOR_PAIR(4));
      }
      else{
        attron(COLOR_PAIR(2));
        printw(" ");
        attroff(COLOR_PAIR(2));
      }
    }
    printw("\n");
  }

  if(GrowItem < 1){
    createGrow();
  }
  if(PoisonItem < 1){
    createPoison();
  }
  if(PotalON == 0){
    createPotal();
  }

  refresh();

}
