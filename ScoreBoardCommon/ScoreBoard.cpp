#include "ScoreBoard.h"

void ScoreBoard::reset()
{
    ply1.reset();
    ply2.reset();
    activePlayer = PLAYER1;
    startedPlayer = PLAYER1;
    shotIsStarted = false;
}

void ScoreBoard::resetScores()
{
    ply1.resetScores();
    ply2.resetScores();
}

BoardPlayers ScoreBoard::whoIsStarted() const
{
    return startedPlayer;
}

void ScoreBoard::swapStartedPlayer()
{
    if (startedPlayer == PLAYER1)
    {
        startedPlayer = PLAYER2;
    }
    else
    {
        startedPlayer = PLAYER1;
    }
}

BoardPlayers ScoreBoard::whoIsActive() const
{
    return activePlayer;
}

void ScoreBoard::setActivePlayer(BoardPlayers player)
{
    activePlayer = player;
}

void ScoreBoard::swapActivePlayer()
{
    if (activePlayer == PLAYER1)
    {
        activePlayer = PLAYER2;
    }
    else
    {
        activePlayer = PLAYER1;
    }
}

void ScoreBoard::addWonFrame(BoardPlayers player)
{
    if (player == PLAYER1)
    {
        ply1.wonFrame();
        ply2.lostFrame();
    }
    else
    {
        ply2.wonFrame();
        ply1.lostFrame();
    }
}

void ScoreBoard::ballInPocket(SnookerBalls ball)
{
    if (activePlayer == PLAYER1)
    {
        ply1.pocketBall(ball);
    }
    else
    {
        ply2.pocketBall(ball);
    }
}

uint8_t ScoreBoard::getHighestScore() const
{
    return max(ply1.getScores(), ply2.getScores());
}

uint8_t ScoreBoard::getHighestFrames() const
{
    return max(ply1.getWonFrames(), ply2.getWonFrames());
}

uint8_t ScoreBoard::getPlayerScore(BoardPlayers player) const
{
    if (player == PLAYER1)
    {
        return ply1.getScores();
    }
    else
    {
        return ply2.getScores();
    }
}

uint8_t ScoreBoard::getPlayerFrames(BoardPlayers player) const
{
    if (player == PLAYER1)
    {
        return ply1.getWonFrames();
    }
    else
    {
        return ply2.getWonFrames();
    }
}

bool ScoreBoard::getPlayerExtensionAvailable(BoardPlayers player) const
{
    if (player == PLAYER1)
    {
        return ply1.isExtensionAvailable();
    }
    else
    {
        return ply2.isExtensionAvailable();
    }
}

bool ScoreBoard::isShotStarted() const
{
    return shotIsStarted;
}

void ScoreBoard::startShot()
{
    shotIsStarted = true;
    timerValue = getTimerMaxValue();
}

void ScoreBoard::stopShot()
{
    shotIsStarted = false;
    if (timerValue >= getTimerMaxValue())
    {
        if (activePlayer == PLAYER1)
        {
            ply1.restoreExtension();
        }
        else
        {
            ply2.restoreExtension();
        }
    }
    timerValue = 0;
}

bool ScoreBoard::extendShot()
{
    if (!shotIsStarted) return false;

    bool isExtension = false;

    if (activePlayer == PLAYER1)
    {
        isExtension = ply1.takeExtension();
    }
    else
    {
        isExtension = ply2.takeExtension();
    }

    if (isExtension)
    {
        timerValue += getTimerMaxValue();
        return true;
    }

    return false;
}

void ScoreBoard::tickShot()
{
    if (!shotIsStarted || timerValue == 0) return;
    --timerValue;
}

uint8_t ScoreBoard::getShotRemainder() const
{
    return timerValue;
}

uint8_t ScoreBoard::getTimerMaxValue() const
{
    return timerValues[timerValueIdx];
}

void ScoreBoard::setTimerNextMaxValue()
{
    if (++timerValueIdx >= timerValuesNum) timerValueIdx = 0;
}

bool ScoreBoard::getResetMode() const
{
    return modeReset;
}

void ScoreBoard::setResetMode(bool mode)
{
    if (mode == modeReset) return;

    modeReset = mode;
}

bool ScoreBoard::getTimerMode() const
{
    return modeTimer;
}

void ScoreBoard::setTimerMode(bool mode)
{
    if (mode == modeTimer) return;

    modeTimer = mode;
}

bool ScoreBoard::getSnookerMode() const
{
    return modeSnooker;
}

void ScoreBoard::setSnookerMode(bool mode)
{
    if (mode == modeSnooker) return;

    modeSnooker = mode;
}
