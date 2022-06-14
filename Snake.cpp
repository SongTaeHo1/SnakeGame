#include <ncurses.h>
#include "Snake.h"

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
  else if(key == 'c'){
    isDie(); // 겜 종료
  }
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

  isBody.push_front(nextCol);
  isBody.push_front(nextRow);
  isBody.pop_back();
  isBody.pop_back();
}
