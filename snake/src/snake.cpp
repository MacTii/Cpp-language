#include "snake.h"
#include <cstdlib>
#include <unistd.h>

#define HEAD '*'
#define BODY '+'
#define FOOD '0'

#define HELP_MODE 2
#define PAUSE_MODE 1
#define GAME_MODE 0
#define GAME_OVER -1

#define CPOINT_UP CPoint(0, -1)
#define CPOINT_DOWN CPoint(0, 1)
#define CPOINT_LEFT CPoint(-1, 0)
#define CPOINT_RIGHT CPoint(1, 0)

CSnake::CSnake(CRect r, char _c /*=' '*/): CFramedWindow(r, _c), lastMove(KEY_RIGHT), isFoodCollected(true), level(1), mode(HELP_MODE)
{
    foodPosition = CPoint(geom.size.x/2, geom.size.y/2);
    segments.push_front(CPoint(3, 2));
    segments.push_front(CPoint(4, 2));
    segments.push_front(CPoint(5, 2));

}
void CSnake::paint()
{
    CFramedWindow::paint();
    gotoyx(geom.topleft.y - 1, geom.topleft.x);
    char textLevel[14];
    sprintf(textLevel, "| LEVEL: %d |", level/3);
    printl(textLevel);
    auto i = segments.begin();
    gotoyx(geom.topleft.y + i->y, geom.topleft.x + i->x);
    printc(HEAD); i++;
    for(; i != segments.end(); i++)
    {
        gotoyx(geom.topleft.y + i->y, geom.topleft.x + i->x);
        printc(BODY);
    }
    gotoyx(geom.topleft.y + foodPosition.y, geom.topleft.x + foodPosition.x);
    printc(FOOD);
    if(mode == HELP_MODE)
        helpMenu();
    else if(mode == GAME_OVER)
        deathScore();
}

CPoint CSnake::CPointLastMove(int key)
{
    if(key == KEY_UP)
        return CPOINT_UP;
    else if(key == KEY_DOWN)
        return CPOINT_DOWN;
    else if(key == KEY_LEFT)
        return CPOINT_LEFT;
    else
        return CPOINT_RIGHT;
}

bool CSnake::colision()
{
    if(segments.front() == foodPosition)
    {
        srand(time(NULL)); int check = 1;
        while(check == 1)
        {
            check = 0;
            foodPosition = CPoint(rand()%(geom.size.x-2)+1, rand()%(geom.size.y-2)+1);
            for(auto i = segments.begin(); i != segments.end(); i++)
                if(foodPosition == *i)
                    check = 1;
        }
        insert();
        level++;
        return false;
    }
    else
    {
        auto i = segments.begin(); i++;
        for(; i != segments.end(); i++)
        {
            if (segments.front() == *i)
                return true;
        }
        return false;
    }
}

bool CSnake::handleEvent(int key)
{
    if(key == 'r')
        *this = CSnake(geom, c);
    else if(key == 'p')
    {
        if(mode == GAME_MODE)
            mode = PAUSE_MODE;
        else if(mode == PAUSE_MODE)
            mode = GAME_MODE;
    }
    else if(key == 'h')
    {
        if(mode == HELP_MODE)
            mode = GAME_MODE;
        else if(mode == PAUSE_MODE || mode == GAME_MODE)
            mode = HELP_MODE;
    }
    else if(mode == GAME_MODE)
    {
        switch (key)
        {
            case KEY_UP:
                if(lastMove != KEY_DOWN)
                {
                    move (CPOINT_UP);
                    lastMove = KEY_UP;
                }
                break;
            case KEY_DOWN:
                if(lastMove != KEY_UP)
                {
                    move (CPOINT_DOWN);
                    lastMove = KEY_DOWN;
                }
                break;
            case KEY_RIGHT:
                if(lastMove != KEY_LEFT)
                {
                    move (CPOINT_RIGHT);
                    lastMove = KEY_RIGHT;
                }
                break;
            case KEY_LEFT:
                if(lastMove != KEY_RIGHT)
                {
                    move (CPOINT_LEFT);
                    lastMove = KEY_LEFT;
                }
                break;
            case ERR:
                move(CPointLastMove(lastMove));
                break;
            default:
                return false;
        }
        if(colision())
            mode = GAME_OVER;
        return true;
    }
    else
    {
        switch (key)
        {
            case KEY_UP:
                CView::move(CPOINT_UP);
                return true;
            case KEY_DOWN:
                CView::move(CPOINT_DOWN);
                return true;
            case KEY_RIGHT:
                CView::move(CPOINT_RIGHT);
                return true;
            case KEY_LEFT:
                CView::move(CPOINT_LEFT);
                return true;
            default:
                return false;
        }
    }
}

void CSnake::insert()
{
    CPoint temp = segments.back();
    segments.push_back(temp);
}

void CSnake::helpMenu()
{
    gotoyx(geom.topleft.y + 5, geom.topleft.x + 3);
    printl("h - toggle help information");
    gotoyx(geom.topleft.y + 6, geom.topleft.x + 3);
    printl("p - toggle pause/play mode");
    gotoyx(geom.topleft.y + 7, geom.topleft.x + 3);
    printl("r - restart game");
    gotoyx(geom.topleft.y + 8, geom.topleft.x + 3);
    printl("arrows - move snake (in play mode) or");
    gotoyx(geom.topleft.y + 9, geom.topleft.x + 12);
    printl("move window (in pause mode)");
}

void CSnake::deathScore()
{
    gotoyx(geom.topleft.y + 1, geom.topleft.x + 1);
    char text[22];
    sprintf(text, "GAME OVER, result: %d", level);
    printl(text);

}

void CSnake::move(const CPoint& point)
{
    segments.pop_back();
    CPoint copy = segments.front();
    copy += point;
    if(copy.x < 1)
        copy.x = geom.size.x - 2;
    else if(copy.y < 1)
        copy.y = geom.size.y - 2;
    else if(copy.x > geom.size.x - 2)
        copy.x = 1;
    else if(copy.y > geom.size.y - 2)
        copy.y = 1;
    segments.push_front(copy);
}