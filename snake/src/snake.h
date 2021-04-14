#ifndef __SNAKE_H__
#define __SNAKE_H__

#include "winsys.h"
#include "screen.h"
#include <ctime>

class CSnake:public CFramedWindow
{
    int lastMove;
    int level;
    int mode;
    bool isFoodCollected;
    CPoint foodPosition;
    list<CPoint> segments;
public:
  CSnake(CRect r, char _c = ' ');
  void paint();
    bool handleEvent(int key);
  void move(const CPoint& point);

  CPoint CPointLastMove(int key);
  void insert();
  bool colision();
  void helpMenu();
  void deathScore();
};

#endif
