#ifndef _SCOREBOARD_H_
#define _SCOREBOARD_H_

#include <RTClib.h>

// The control pins for the LCD can be assigned to any digital or
// analog pins...but we'll use the analog pins as this allows us to
// double up the pins with the touch screen (see the TFT paint example).
#define LCD_RESET A6 // Can alternately just connect to Arduino's reset pin
#define LCD_CS A3	 // Chip Select goes to Analog 3
#define LCD_CD A2	 // Command/Data goes to Analog 2
#define LCD_WR A1	 // LCD Write goes to Analog 1
#define LCD_RD A0	 // LCD Read goes to Analog 0

#include <Adafruit_TFTLCD.h> // Hardware-specific library

// Assign human-readable names to some common 16-bit color values:
#define	RED     0xF800
#define	BLACK   0x0000
#define PINK    0xFE19
#define	BLUE    0x001F
#define BROWN   0xCC27
#define	GREEN   0x07E0
#define YELLOW  0xFEA0
#define WHITE   0xFFFF

#include "BoardText.h"

#define SCREEN_W 320  // width screen
#define SCREEN_H 240  // height screen

#define X_OFFSET 10   // shift x position
#define Y_OFFSET 0    // shift y position  

#define TIME_W 140    // width of time slot (hours and minutes)

#include "SnookerPlayerView.h"
#include "SnookerGame.h"

#include "PoolPlayerViewHalf.h"
#include "PoolPlayerViewFourth.h"
#include "PoolGame.h"

#define PLY_GREEN  0
#define	PLY_YELLOW 1
#define	PLY_BLUE   2
#define	PLY_PINK   3
#define PLY_BLACK  0
#define PLY_RED    1

class ScoreBoard
{
private:

	Adafruit_TFTLCD tft;

	enum BOARD_MAJOR_STATE
	{
		S_NOT_INITED,
		S_RESET,
		S_SNOOKER,
		S_POOL2,
		S_POOL4
	}
	boardState;

	DateTime boardTime;

	BoardText lcdTime;


	PlayerView* fourPlayers[4];
	PoolGame poolGame4 = PoolGame(4, fourPlayers);

	PlayerView* twoPlayers[2];
	PoolGame poolGame2 = PoolGame(2, twoPlayers);

	PlayerView* snookerPlayers[2];
	SnookerGame snookerGame = SnookerGame(2, snookerPlayers);

public:

	ScoreBoard();

	void begin();

	const DateTime& getTime() const;
	void setTime(const DateTime& time);
	void adjustTime(int8_t hours, int8_t minutes);

	void update(bool resetState, bool snookerState, bool poolState);

	bool pressedBtnRed(bool withConfigBtn);
	bool pressedBtnBlack(bool withConfigBtn);
	bool pressedBtnPink(bool withConfigBtn);
	bool pressedBtnBlue(bool withConfigBtn);
	bool pressedBtnBrown(bool withConfigBtn);
	bool pressedBtnGreen(bool withConfigBtn);
	bool pressedBtnYellow(bool withConfigBtn);
	bool pressedBtnWhiteRed(bool withConfigBtn);
	bool pressedBtnWhiteBlack(bool withConfigBtn);

	bool clickMasterBtn();
	bool clickTwiceMasterBtn();

protected:

	void showTime();

	void startResetMode();
	void startSnookerMode();
	void startPool2Mode();
	void startPool4Mode();
};

ScoreBoard::ScoreBoard() : 
	tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET),
	boardState(S_NOT_INITED),
	lcdTime(BoardText("ScoreBoard", 5, &tft, BLACK, WHITE, X_OFFSET, Y_OFFSET, SCREEN_W - X_OFFSET, SCREEN_H - Y_OFFSET))
{
	fourPlayers[0] = new PoolPlayerViewFourth(&tft, GREEN, WHITE, 10, 0, 155, 120);
	fourPlayers[1] = new PoolPlayerViewFourth(&tft, YELLOW, WHITE, 165, 0, 155, 120);
	fourPlayers[2] = new PoolPlayerViewFourth(&tft, BLUE, WHITE, 165, 120, 155, 120);
	fourPlayers[3] = new PoolPlayerViewFourth(&tft, PINK, WHITE, 10, 120, 155, 120);

	twoPlayers[0] = new PoolPlayerViewHalf(&tft, BLACK, WHITE, 10, 0, 155, 240);
	twoPlayers[1] = new PoolPlayerViewHalf(&tft, RED, WHITE, 165, 0, 155, 240);

	snookerPlayers[0] = new SnookerPlayerView(&tft, BLACK, WHITE, 10, 0, 155, 240);
	snookerPlayers[1] = new SnookerPlayerView(&tft, RED, WHITE, 165, 0, 155, 240);

	poolGame4.reset();
	poolGame2.reset();
	snookerGame.reset();
}

void ScoreBoard::begin()
{
	tft.reset();
	tft.begin(tft.readID());
	tft.setRotation(1);
	tft.setTextWrap(false);
	tft.fillScreen(BLACK);
	lcdTime.show();
	lcdTime.setSize(10);
}

void ScoreBoard::showTime()
{
	char newTime[6] = { '0', '0' ,':', '0', '0' };

	newTime[0] += (boardTime.hour() / 10);
	newTime[1] += (boardTime.hour() % 10);
//	newTime[2] = boardTime.second() % 2 ? ' '  : ':';
	newTime[3] += (boardTime.minute() / 10);
	newTime[4] += (boardTime.minute() % 10);

	if (boardState == S_RESET)
	{
		lcdTime.updateText(newTime);
	}
	else
	{
		lcdTime.setText(newTime);
	}
}

inline const DateTime& ScoreBoard::getTime() const
{
	return boardTime;
}

inline void ScoreBoard::setTime(const DateTime &time)
{
	boardTime = time;
	showTime();
}

inline void ScoreBoard::adjustTime(int8_t hours, int8_t minutes)
{
	boardTime = boardTime + TimeSpan(0, hours, minutes, 0);
	showTime();
}

void ScoreBoard::update(bool resetState, bool snookerState, bool poolState)
{
	BOARD_MAJOR_STATE newState;

	if (resetState)
	{
		newState = S_RESET;
	}
	else if (snookerState)
	{
		newState = S_SNOOKER;
	}
	else if (poolState)
	{
		newState = S_POOL2;
	}
	else
	{
		newState = S_POOL4;
	}

	if (newState == boardState)
		return;

	boardState = newState;

	switch (boardState)
	{
	case ScoreBoard::S_RESET:
		startResetMode();
		break;
	case ScoreBoard::S_SNOOKER:
		startSnookerMode();
		break;
	case ScoreBoard::S_POOL2:
		startPool2Mode();
		break;
	case ScoreBoard::S_POOL4:
		startPool4Mode();
		break;
	default:
		break;
	}
}

bool ScoreBoard::pressedBtnRed(bool withConfigBtn)
{
	switch (boardState)
	{
	case ScoreBoard::S_SNOOKER:
		return snookerGame.ballInPocket(withConfigBtn ? SnookerBalls::foul_1 : SnookerBalls::red);
	case ScoreBoard::S_POOL2:
		poolGame2.changeScores(PLY_RED, withConfigBtn ? -1 : 1);
		poolGame2.shiftFocus();
		return true;
	default:
		break;
	}
	return false;
}

bool ScoreBoard::pressedBtnBlack(bool withConfigBtn)
{
	switch (boardState)
	{
	case ScoreBoard::S_SNOOKER:
		return snookerGame.ballInPocket(withConfigBtn ? SnookerBalls::foul_7 : SnookerBalls::black);
	case ScoreBoard::S_POOL2:
		poolGame2.changeScores(PLY_BLACK, withConfigBtn ? -1 : 1);
		poolGame2.shiftFocus();
		return true;
	default:
		break;
	}
	return false;
}

bool ScoreBoard::pressedBtnPink(bool withConfigBtn)
{
	switch (boardState)
	{
	case S_RESET:
		adjustTime(1, 0);
		return true;
	case ScoreBoard::S_SNOOKER:
		return snookerGame.ballInPocket(withConfigBtn ? SnookerBalls::foul_6 : SnookerBalls::pink);
	case ScoreBoard::S_POOL4:
		poolGame4.changeScores(PLY_PINK, withConfigBtn ? -1 : 1);
		poolGame4.shiftFocus(PLY_PINK);
		return true;
	default:
		break;
	}
	return false;
}

bool ScoreBoard::pressedBtnBlue(bool withConfigBtn)
{
	switch (boardState)
	{
	case S_RESET:
		adjustTime(0, 1);
		return true;
	case ScoreBoard::S_SNOOKER:
		return snookerGame.ballInPocket(withConfigBtn ? SnookerBalls::foul_5 : SnookerBalls::blue);
	case ScoreBoard::S_POOL4:
		poolGame4.changeScores(PLY_BLUE, withConfigBtn ? -1 : 1);
		poolGame4.shiftFocus(PLY_BLUE);
		return true;
	default:
		break;
	}
	return false;
}

bool ScoreBoard::pressedBtnBrown(bool withConfigBtn)
{
	switch (boardState)
	{
	case ScoreBoard::S_SNOOKER:
		return snookerGame.ballInPocket(withConfigBtn ? SnookerBalls::foul_4 : SnookerBalls::brown);
	default:
		break;
	}
	return false;
}

bool ScoreBoard::pressedBtnGreen(bool withConfigBtn)
{
	switch (boardState)
	{
	case S_RESET:
		adjustTime(3, 0);
		return true;
	case ScoreBoard::S_SNOOKER:
		return snookerGame.ballInPocket(withConfigBtn ? SnookerBalls::foul_3 : SnookerBalls::green);
	case ScoreBoard::S_POOL4:
		poolGame4.changeScores(PLY_GREEN, withConfigBtn ? -1 : 1);
		poolGame4.shiftFocus(PLY_GREEN);
		return true;
	default:
		break;
	}
	return false;
}

bool ScoreBoard::pressedBtnYellow(bool withConfigBtn)
{
	switch (boardState)
	{
	case S_RESET:
		adjustTime(0, 5);
		return true;
	case ScoreBoard::S_SNOOKER:
		return snookerGame.ballInPocket(withConfigBtn ? SnookerBalls::foul_2 : SnookerBalls::yellow);
	case ScoreBoard::S_POOL4:
		poolGame4.changeScores(PLY_YELLOW, withConfigBtn ? -1 : 1);
		poolGame4.shiftFocus(PLY_YELLOW);
		return true;
	default:
		break;
	}
	return false;
}

bool ScoreBoard::pressedBtnWhiteRed(bool withConfigBtn)
{
	switch (boardState)
	{
	case ScoreBoard::S_SNOOKER:
		snookerGame.shiftFocus(PLY_RED);
		return true;
	default:
		break;
	}
	return false;
}

bool ScoreBoard::pressedBtnWhiteBlack(bool withConfigBtn)
{
	switch (boardState)
	{
	case ScoreBoard::S_SNOOKER:
		snookerGame.shiftFocus(PLY_BLACK);
		return true;
	default:
		break;
	}
	return false;
}

bool ScoreBoard::clickMasterBtn()
{
	switch (boardState)
	{
	case ScoreBoard::S_SNOOKER:
		snookerGame.shiftFocus();
		return true;
	case ScoreBoard::S_POOL2:
		poolGame2.shiftFocus();
		return true;
	case ScoreBoard::S_POOL4:
		poolGame4.shiftFocus();
		return true;
	default:
		return false;
	}
}

bool ScoreBoard::clickTwiceMasterBtn()
{
	switch (boardState)
	{
	case ScoreBoard::S_SNOOKER:
		snookerGame.revokeLastBall();
		return false;
	default:
		return true;
	}
}

void ScoreBoard::startResetMode()
{
	tft.fillScreen(BLACK);

	lcdTime.show();

	poolGame2.reset();
	poolGame4.reset();
}

void ScoreBoard::startSnookerMode()
{
	snookerGame.reset();
	snookerGame.show();
}

void ScoreBoard::startPool2Mode()
{
	poolGame2.show();
}

void ScoreBoard::startPool4Mode()
{
	poolGame4.show();
}

#endif

