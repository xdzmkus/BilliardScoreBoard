#ifndef _GAMEVIEW_H_
#define _GAMEVIEW_H_

#include "PlayerView.h"

#include "LoopIndex.h"

class GameView
{
public:

    GameView(uint8_t count, PlayerView** playerViews);

    virtual void reset();

    virtual void show();

    virtual void shiftFocus();
    virtual void shiftFocus(uint8_t idx);

protected:

    void updateTextSize();

    LoopIndex plyIdx;

    PlayerView** players;
};

GameView::GameView(uint8_t count, PlayerView** playerViews) :
    plyIdx(0, count - 1), players(playerViews)
{
}

void GameView::reset()
{
    plyIdx.set(0);

    for (uint8_t i = plyIdx.getMin(); i <= plyIdx.getMax(); ++i)
    {
        players[i]->reset();
    }
}

void GameView::show()
{
    for (uint8_t i = plyIdx.getMin(); i <= plyIdx.getMax(); ++i)
        players[i]->show();

    players[plyIdx]->showFocus();
}

void GameView::shiftFocus()
{
    players[plyIdx++]->clearFocus();
    players[plyIdx]->showFocus();
}

void GameView::shiftFocus(uint8_t idx)
{
    players[plyIdx]->clearFocus();
    plyIdx.set(idx);
    players[plyIdx]->showFocus();
}

void GameView::updateTextSize()
{
    uint8_t minTextSize = -1;

    for (uint8_t i = plyIdx.getMin(); i <= plyIdx.getMax(); ++i)
    {
        uint8_t maxTextSize = players[i]->getMaxTextSize();
        if (maxTextSize < minTextSize)
            minTextSize = maxTextSize;
    }

    for (uint8_t i = plyIdx.getMin(); i <= plyIdx.getMax(); ++i)
    {
        players[i]->updateTextSize(minTextSize);
    }
}


#endif
