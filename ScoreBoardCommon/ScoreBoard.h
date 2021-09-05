#ifndef _SCOREBOARD_H_
#define _SCOREBOARD_H_

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "SnookerPlayer.h"

enum BoardPlayers
{
	PLAYER1,
	PLAYER2
};

class ScoreBoard
{
private:

	SnookerPlayer ply1;
	SnookerPlayer ply2;

	BoardPlayers activePlayer = PLAYER1;
	BoardPlayers startedPlayer = PLAYER1;

public:

	void reset();
	void resetScores();

	BoardPlayers whoIsStarted() const;
	void swapStartedPlayer();

	BoardPlayers whoIsActive() const;
	void setActivePlayer(BoardPlayers player);
	void swapActivePlayer();

	void addWonFrame(BoardPlayers player);

	void ballInPocket(SnookerBalls ball);

	uint8_t getHighestScore() const;
	uint8_t getHighestFrames() const;

	uint8_t getPlayerScore(BoardPlayers player) const;
	uint8_t getPlayerFrames(BoardPlayers player) const;
	bool getPlayerExtensionAvailable(BoardPlayers player) const;

private:
	
	bool shotIsStarted = false;

	static const uint8_t timerValuesNum = 4;
	const uint8_t timerValues[timerValuesNum] = { 60, 45, 35, 30 };
	uint8_t timerValueIdx = 0;
	uint8_t timerValue = 0;

public:

	bool isShotStarted() const;
	void startShot();
	void stopShot();
	bool extendShot();
	void tickShot();
	uint8_t getShotRemainder() const;
	uint8_t getTimerMaxValue() const;
	void setTimerNextMaxValue();

private:

	 bool modeReset = true;
	 bool modeTimer = false;
	 bool modeSnooker = false;

public:

	 bool getResetMode() const;
	 void setResetMode(bool mode);

	 bool getTimerMode() const;
	 void setTimerMode(bool mode);

	 bool getSnookerMode() const;
	 void setSnookerMode(bool mode);

};

#endif

