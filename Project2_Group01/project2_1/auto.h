#include"runestone.h"
#define Xsize 6
#define Ysize 5
#define cornerRating 5
#ifndef AUTO_H
#define AUTO_H

struct answer{
    int x;  //起始位置
    int y;
    int step[50];
    int rating; //combo評分
};

int *BestPath( int **attributeMap);
#endif // AUTO_H



