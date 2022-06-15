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
  if(isSnakeHere(wherePotal[0],wherePotal[1]) == 0 && isSnakeHere(wherePotal[2],wherePotal[3]) == 0 ){
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
  resize_term(100,100);

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
        plusNum++;
        totalPlus++;
      }
      if(isPoisonHere(i,j) == 1 && isSnakeHere(i,j) == 1){
        s.decreaseL();
        delPoison(i,j);
        minusNum++;
        totalMinus++;
      }
    }
  }
}

void Map::potalMove(){
  char di;
  if(anoRow == 0){
    di = 'd';
    s.isBody.push_front(anoCol);
    s.isBody.push_front(anoRow+1);
  }
  else if(anoRow == 39){
    di = 'u';
    s.isBody.push_front(anoCol);
    s.isBody.push_front(anoRow-1);
  }
  else if(anoCol == 0){
    di = 'r';
    s.isBody.push_front(anoCol+1);
    s.isBody.push_front(anoRow);
  }
  else if(anoCol == 49){
    di = 'l';
    s.isBody.push_front(anoCol-1);
    s.isBody.push_front(anoRow);
  }
  s.isDirection = di;

  s.isBody.pop_back();
  s.isBody.pop_back();

}

void Map::setGate(){
  if(setPotal == 0){
    if(isSnakeHere(wherePotal[0],wherePotal[1]) == 1){
      anoRow = wherePotal[2];
      anoCol = wherePotal[3];
    }
    else{
      anoRow = wherePotal[0];
      anoCol = wherePotal[1];
    }
    setPotal = 1;
    GateNum++;
    totalGate++;
  }
}

void Map::makeScore(){

  init_pair(9,COLOR_WHITE,COLOR_BLACK);

  attron(COLOR_PAIR(9));
  mvprintw(4,55,"Score Board");
  mvprintw(6,55,"Length / Max : %d / %d",s.isLength,20);
  mvprintw(7,55,"+ : %d",plusNum);
  mvprintw(8,55,"- : %d",minusNum);
  mvprintw(9,55,"Gate : %d",GateNum);
  mvprintw(10,55,"MaxLength : %d",maxLength);
  timeS = clock()/1000 - startT/1000;
  mvprintw(11,55,"Time : %d",timeS);

  attroff(COLOR_PAIR(9));

}

void Map::makeMission(){
  init_pair(9,COLOR_WHITE,COLOR_BLACK);

  attron(COLOR_PAIR(9));
  mvprintw(14,55,"Mission Board");
  mvprintw(16,55,"B : %d",targetL);
  if(maxLength >= targetL){
    mvprintw(16,65," ( V )");
  }
  else{
    mvprintw(16,65," (   )");
  }
  mvprintw(17,55,"+ : %d",targetP);
  if(plusNum >= targetP){
    mvprintw(17,65," ( V )");
  }
  else{
    mvprintw(17,65," (   )");
  }
  mvprintw(18,55,"- : %d",targetM);
  if(minusNum >= targetM){
    mvprintw(18,65," ( V )");
  }
  else{
    mvprintw(18,65," (   )");
  }
  mvprintw(19,55,"G : %d",targetG);
  if(GateNum >= targetG){
    mvprintw(19,65," ( V )");
  }
  else{
    mvprintw(19,65," (   )");
  }
  attroff(COLOR_PAIR(9));
}

void Map::mapLevelUp(){
  for(int i = 0; i< 40; i++){
    for(int j = 0; j < 50; j++){
      mapArray[i][j] = mapStage[mapLevel][i][j];
    }
  }

  GrowItem = 0;
  PoisonItem = 0;
  PotalON = 0;
  whereGrow.clear();
  wherePotal.clear();
  wherePoison.clear();

  setPotal = 0; // 게이트 설정 여부
  anoRow = 0; //다른 게이트 행
  anoCol = 0; //다른 게이트 열

  plusNum = 0;
  minusNum = 0;
  GateNum = 0;

  s.isBody = {4,4,4,3,4,2};
  s.isDirection = 'r';
  s.prevDirection = 'r';
  s.isLength = 3;
  s.isLife = 1;

  mapLevel += 1;
  if(mapLevel == 3){
    mapLevel = 0;
  }
}

void Map::updateMap(){
  clear();
  if(isSnakeHere(wherePotal[0],wherePotal[1]) == 0 && isSnakeHere(wherePotal[2],wherePotal[3]) == 0 ){
    s.isMove();
    setPotal = 0;
  }
  else{
    setGate();
    potalMove();
  }
  isCrash();
  isItem();
  start_color();

  init_pair(1,COLOR_YELLOW,COLOR_YELLOW);
  init_pair(2,COLOR_BLACK,COLOR_BLACK);
  init_pair(3,COLOR_GREEN,COLOR_GREEN);
  init_pair(4,COLOR_RED,COLOR_RED);
  init_pair(5,COLOR_BLUE,COLOR_BLUE);
  init_pair(6,COLOR_MAGENTA,COLOR_MAGENTA);
  init_pair(9,COLOR_WHITE,COLOR_BLACK);

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
  if(maxLength < s.isLength){
    maxLength = s.isLength;
  }
  makeScore();
  makeMission();

  if(GrowItem < 1){
    createGrow();
  }
  if(PoisonItem < 1){
    createPoison();
  }
  if(PotalON == 0){
    createPotal();
  }

  if((maxLength >= targetL) && (plusNum >= targetP) && (minusNum >= targetM) && (GateNum >= targetG) ){
    mapLevelUp();
  }


  refresh();

}
