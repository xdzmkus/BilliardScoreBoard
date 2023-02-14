#ifndef _POOLGAME_H_
#define _POOLGAME_H_

#include "GameView.h"

class PoolGame : public GameView
{
public:

    PoolGame(uint8_t count, PlayerView** playerViews);

    void changeScores(uint8_t idx, int8_t delta);
};

PoolGame::PoolGame(uint8_t count, PlayerView** playerViews) :
    GameView(count, playerViews)
{
}

void PoolGame::changeScores(uint8_t idx, int8_t delta)
{
    ((PoolPlayerView*)players[idx])->changeScores(delta);

    updateTextSize();
}

#endif
