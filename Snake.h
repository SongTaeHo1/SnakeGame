#pragma once
#include <iostream>
#include <deque>

using namespace std;

class Snake{

    public:
        char isDirection = 'r';
        char prevDirection = 'r';
        int isLength = 3;
        int isLife = 1;
        void isDie();
        void isMove();
        void changeDirection(int key);
        deque<int> isBody = {4,4,4,3,4,2};

        int getL(){return isLength;}
        int getD(){return isDirection;}
};
