#ifndef _SNOOKERGAME_H_
#define _SNOOKERGAME_H_

#include "GameView.h"
#include "SnookerPlayerView.h"

class SnookerGame : public GameView
{
public:

	SnookerGame(uint8_t count, PlayerView** playerViews);

    void reset() override;
    void show() override;

    void shiftFocus() override;
    void shiftFocus(uint8_t idx) override;

    bool ballInPocket(SnookerBalls ball);
    void revokeLastBall();

protected:

    void updateMaxBreak();

private:

    union TABLE
    {
        uint16_t sumBalls;
        struct BALLS
        {
            uint8_t reds : 4;
            bool yellow : 1;
            bool green : 1;
            bool brown : 1;
            bool blue : 1;
            bool pink : 1;
            bool black : 1;
        } balls;
    }
    ballsOnTable;

    enum BALL_FLAG
    {
        B_FULL = 0x3FF,
        B_YELLOW = 0x3F0,
        B_GREEN = 0x3E0,
        B_BROWN = 0x3C0,
        B_BLUE = 0x380,
        B_PINK = 0x300,
        B_BLACK = 0x200
    };
};


SnookerGame::SnookerGame(uint8_t count, PlayerView** playerViews)
  : GameView(count, playerViews), ballsOnTable({B_FULL})
{
}

void SnookerGame::reset()
{
    GameView::reset();
    ballsOnTable = { B_FULL };
}

void SnookerGame::show()
{
    GameView::show();
    updateMaxBreak();
}

void SnookerGame::shiftFocus()
{
    ((SnookerPlayerView*)players[plyIdx])->addLastBall(SnookerBalls::miss);

    GameView::shiftFocus();

    updateMaxBreak();
}

void SnookerGame::shiftFocus(uint8_t idx)
{
    ((SnookerPlayerView*)players[plyIdx])->addLastBall(SnookerBalls::miss);
 
    GameView::shiftFocus(idx);

    updateMaxBreak();
}

bool SnookerGame::ballInPocket(SnookerBalls ball)
{
    SnookerBalls lastBall = ((SnookerPlayerView*)players[plyIdx])->getLastBall();

    bool afterFoul = lastBall == SnookerBalls::foul_4 || lastBall == SnookerBalls::foul_5 || lastBall == SnookerBalls::foul_6 || lastBall == SnookerBalls::foul_7;

    if (ballsOnTable.balls.reds != 0)
    {
        // red balls still available
        switch (ball)
        {
        case SnookerBalls::red:
            --(ballsOnTable.balls.reds);
            break;
        case SnookerBalls::yellow:
        case SnookerBalls::green:
        case SnookerBalls::brown:
        case SnookerBalls::blue:
        case SnookerBalls::pink:
        case SnookerBalls::black:
            if (lastBall != SnookerBalls::red && lastBall != SnookerBalls::foul_1) return false; // color ball follows after red or free ball only
            break;
        case SnookerBalls::foul_1:
            if (!afterFoul) return false; // red free ball follows foul
            break;
        case SnookerBalls::foul_2:
        case SnookerBalls::foul_3:
            return false;   // color free ball not possible while red available
        default:
            break;
        }
    }
    else if (lastBall == SnookerBalls::red)
    {
        // last red ball
        switch (ball)
        {
        case SnookerBalls::miss:
        case SnookerBalls::yellow:
        case SnookerBalls::green:
        case SnookerBalls::brown:
        case SnookerBalls::blue:
        case SnookerBalls::pink:
        case SnookerBalls::black:
        case SnookerBalls::foul_4:
        case SnookerBalls::foul_5:
        case SnookerBalls::foul_6:
        case SnookerBalls::foul_7:
            break;
        default:
            return false;
        }
    }
    else if (ball == SnookerBalls::foul_2)
    {
        // free yellow follows after foul only
        if (ballsOnTable.sumBalls != B_YELLOW || !afterFoul)
            return false;
    }
    else if (ball == SnookerBalls::foul_3)
    {
        // free green follows after foul only
        if (ballsOnTable.sumBalls != B_GREEN || !afterFoul)
             return false;
    }
    else
    {
        // colors remained
        switch (ball)
        {
        case SnookerBalls::miss:
            break;
        case SnookerBalls::yellow:
            if (ballsOnTable.sumBalls != B_YELLOW) return false;
            ballsOnTable.balls.yellow = false;
            break;
        case SnookerBalls::green:
            if (ballsOnTable.sumBalls != B_GREEN) return false;
            ballsOnTable.balls.green = false;
            break;
        case SnookerBalls::brown:
            if (ballsOnTable.sumBalls != B_BROWN) return false;
            ballsOnTable.balls.brown = false;
            break;
        case SnookerBalls::blue:
            if (ballsOnTable.sumBalls != B_BLUE) return false;
            ballsOnTable.balls.blue = false;
            break;
        case SnookerBalls::pink:
            if (ballsOnTable.sumBalls != B_PINK) return false;
            ballsOnTable.balls.pink = false;
            break;
        case SnookerBalls::black:
            if (ballsOnTable.sumBalls != B_BLACK) return false;
            ballsOnTable.balls.black = false;
            break;
        case  SnookerBalls::foul_4:
            if (ballsOnTable.sumBalls < B_BROWN) return false;
            break;
        case  SnookerBalls::foul_5:
            if (ballsOnTable.sumBalls < B_BLUE) return false;
            break;
        case  SnookerBalls::foul_6:
            if (ballsOnTable.sumBalls < B_PINK) return false;
            break;
        case  SnookerBalls::foul_7:
            if (ballsOnTable.sumBalls < B_BLACK) return false;
            break;
        default:
            return false;
        }
    }

    ((SnookerPlayerView*)players[plyIdx])->addLastBall(ball);

    updateTextSize();

    updateMaxBreak();

    return true;
}

void SnookerGame::revokeLastBall()
{
    SnookerBalls lastBall = ((SnookerPlayerView*)players[plyIdx])->revokeLastBall();

    switch (lastBall)
    {
    case SnookerBalls::red:
        ++(ballsOnTable.balls.reds);
        break;
    case SnookerBalls::yellow:
        ballsOnTable.balls.yellow = true;
        break;
    case SnookerBalls::green:
        ballsOnTable.balls.green = true;
        break;
    case SnookerBalls::brown:
        ballsOnTable.balls.brown = true;
        break;
    case SnookerBalls::blue:
        ballsOnTable.balls.blue = true;
        break;
    case SnookerBalls::pink:
        ballsOnTable.balls.pink = true;
        break;
    case SnookerBalls::black:
        ballsOnTable.balls.black = true;
        break;
    default:
        break;
    }

    updateTextSize();

    updateMaxBreak();
}

void SnookerGame::updateMaxBreak()
{
    SnookerPlayerView* player = ((SnookerPlayerView*)players[plyIdx]);

    uint16_t scoreOnTable = ballsOnTable.balls.reds * 8;

    if (ballsOnTable.balls.yellow) scoreOnTable += 2;
    if (ballsOnTable.balls.green) scoreOnTable += 3;
    if (ballsOnTable.balls.brown) scoreOnTable += 4;
    if (ballsOnTable.balls.blue) scoreOnTable += 5;
    if (ballsOnTable.balls.pink) scoreOnTable += 6;
    if (ballsOnTable.balls.black) scoreOnTable += 7;

    // update active player
    uint16_t maxScores = scoreOnTable + player->getScores();
    SnookerBalls lastBall = player->getLastBall();
    if (lastBall == SnookerBalls::red || lastBall == SnookerBalls::foul_1) maxScores += 7;
    player->updateMaxScores(maxScores);

    // update another player
    maxScores = scoreOnTable + players[++plyIdx]->getScores();
    ((SnookerPlayerView*)players[plyIdx++])->updateMaxScores(maxScores);
}


#endif
