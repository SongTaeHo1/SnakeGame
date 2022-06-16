#include <ncurses.h>
#include "Snake.h"


void Snake::increaseL(){
  if(isLength < 20){
    int tailRow = isBody[isLength * 2 - 2];
    int tailCol = isBody.back();
    if(isDirection == 'u'){
      tailRow += 1;
    }
    else if(isDirection == 'd'){
      tailRow -= 1;
    }
    else if(isDirection == 'l'){
      tailCol += 1;
    }

    else if(isDirection == 'r'){
      tailCol -= 1;
    }
    isBody.push_back(tailRow);
    isBody.push_back(tailCol);
    isLength++;
  }
}

void Snake::decreaseL(){
  isBody.pop_back();
  isBody.pop_back();
  isLength--;
  if(isLength < 3){
    isDie();
  }
}

void Snake::isDie(){
  isLife = 0;
}

void Snake::changeDirection(int key){
  if (key == KEY_UP){
    isDirection = 'u';
    if(prevDirection == 'd'){
      isDie();
    }
  }
  else if(key == KEY_DOWN){
    isDirection = 'd';
    if(prevDirection == 'u'){
      isDie();
    }
  }
  else if(key == KEY_LEFT){
    isDirection = 'l';
    if(prevDirection == 'r'){
      isDie();
    }
  }
  else if(key == KEY_RIGHT){
    isDirection = 'r';
    if(prevDirection == 'l'){
      isDie();
    }
  }
  /* 겜 종료
  else if(key == 'c'){
    isDie();
  }
  늘리고 줄이고 치트키
  else if(key == 'd'){
    increaseL();
  }
  else if(key == 's'){
    decreaseL();
  }
  */
  prevDirection = isDirection;
}

void Snake::isMove(){
  int headRow = isBody[0];
  int headCol = isBody[1];
  int nextRow = headRow;
  int nextCol = headCol;

  if(isDirection == 'r'){
    nextCol += 1;
  }
  else if(isDirection == 'l'){
    nextCol -= 1;
  }
  else if(isDirection == 'u'){
    nextRow -= 1;
  }
  else{
    nextRow += 1;
  }

  for(int k = 2; k < isLength * 2; k += 2){ //자기몸 충돌 판정
    if(isBody[k] == nextRow && isBody[k+1] == nextCol){
      isDie();
    }
  }

  isBody.push_front(nextCol);
  isBody.push_front(nextRow);
  isBody.pop_back();
  isBody.pop_back();
}
