// SnookerPlayerView.h

#ifndef _SNOOKERPLAYERVIEW_H_
#define _SNOOKERPLAYERVIEW_H_

#include "PlayerView.h"

#include "BoardText.h"

#define MAX_BREAK "147"
#define START_SCORE "0"

enum SnookerBalls
{
	miss = 0,
	red = 1,
	yellow = 2,
	green = 3,
	brown = 4,
	blue = 5,
	pink = 6,
	black = 7,
	foul_1 = 8,
	foul_2 = 9,
	foul_3 = 10,
	foul_4 = 11,
	foul_5 = 12,
	foul_6 = 13,
	foul_7 = 14
};

class SnookerPlayerView : public PlayerView
{
private:

	static const uint8_t MAX_BALLS = 64;

	static const uint8_t SERIES_HEIGHT = 65;
	static const uint8_t SERIES_OFFSET = 5;
	static const uint8_t SERIES_SHIFT = 5;
	static const uint8_t SERIES_MAX_CHARS = 33;
	static const uint8_t SERIES_TEXT_SIZE = 2;

	static const uint8_t FOCUS_TEXT_SIZE = 3;
	static const uint8_t FOCUS_OFFSET = 5;
	static const uint8_t FOCUS_HEIGHT = 25;
	static const uint8_t FOCUS_TRIANGLE_HEIGHT = 10;

public:

	SnookerPlayerView(Adafruit_GFX* tft, uint16_t background, uint16_t color, int16_t x, int16_t y, uint16_t w, uint16_t h);

	void reset() override;

	void show() override;

	void clearFocus() override;
	void showFocus() override;

	int16_t getScores() const override;

	uint8_t getMaxTextSize() const override;

	void updateTextSize(uint8_t newTextSize) override;

	void updateMaxScores(uint16_t maxScore);

	void addLastBall(SnookerBalls ball);
	SnookerBalls revokeLastBall();
	SnookerBalls getLastBall() const;

protected:

	void drawFocus(uint16_t color) override;

	void printScores(uint16_t color);
	void printSeries(uint16_t color);

	String getSeries() const;

	uint16_t getCharColor(const char ch) const;

protected:

	SnookerBalls scoredBallsList[MAX_BALLS];

	BoardText scoreText;

	BoardText maxScoreText;
};

SnookerPlayerView::SnookerPlayerView(Adafruit_GFX* tft, uint16_t background, uint16_t color, int16_t x, int16_t y, uint16_t w, uint16_t h) :
	PlayerView(tft, background, color, x, y, w, h),
	scoredBallsList{},
	scoreText(START_SCORE, 0, tft, background, color, x, y + SERIES_HEIGHT + SERIES_OFFSET, w, h - SERIES_HEIGHT - SERIES_OFFSET - FOCUS_HEIGHT - FOCUS_TRIANGLE_HEIGHT),
	maxScoreText(MAX_BREAK, FOCUS_TEXT_SIZE, tft, color, background, x + FOCUS_OFFSET, y + h - FOCUS_OFFSET - FOCUS_HEIGHT, w - FOCUS_OFFSET * 2, FOCUS_HEIGHT)
{
}

void SnookerPlayerView::reset()
{
	PlayerView::reset();

	scoreText.setText(START_SCORE);
	scoreText.setSize(getMaxTextSize());

	maxScoreText.setText(MAX_BREAK);
}

void SnookerPlayerView::show()
{
	PlayerView::show();

	// clear series
	_tft->fillRoundRect(_x + SERIES_OFFSET, _y + SERIES_OFFSET, _w - SERIES_OFFSET - SERIES_OFFSET, SERIES_HEIGHT, SERIES_OFFSET, _color);

	scoreText.show();

	maxScoreText.setColors(_background, _color);
	maxScoreText.show();
}

void SnookerPlayerView::clearFocus()
{
	PlayerView::clearFocus();

	maxScoreText.setColors(_background, _color);
	maxScoreText.show();
}

void SnookerPlayerView::showFocus()
{
	PlayerView::showFocus();

	maxScoreText.setColors(_color, _background);
	maxScoreText.show();
}

int16_t SnookerPlayerView::getScores() const
{
	int16_t scr = 0;
	for (uint8_t i = 0; i < scores; i++)
	{
		scr += static_cast<int16_t>(scoredBallsList[i]);

		switch (scoredBallsList[i])
		{
		case SnookerBalls::foul_1:
		case SnookerBalls::foul_2:
		case SnookerBalls::foul_3:
		case SnookerBalls::foul_4:
		case SnookerBalls::foul_5:
		case SnookerBalls::foul_6:
		case SnookerBalls::foul_7:
			scr -= 7;
			break;
		default:
			break;
		}
	}
	return scr;
}

inline uint8_t SnookerPlayerView::getMaxTextSize() const
{
	int16_t scr = getScores();
	return scr < 10 ? 15 : (scr >= 100 ? 7 : 11);
}

void SnookerPlayerView::updateTextSize(uint8_t newTextSize)
{
	scoreText.updateSize(newTextSize);
}

inline void SnookerPlayerView::updateMaxScores(uint16_t maxScore)
{
	maxScoreText.updateText(String(maxScore));
}

void SnookerPlayerView::addLastBall(SnookerBalls ball)
{
	if (scores == MAX_BALLS) return;

	if (ball == SnookerBalls::miss && scores != 0 && scoredBallsList[scores - 1] == SnookerBalls::miss)
		return; // do not duplicate misses

	scoreText.clear();

	printSeries(_color);

	scoredBallsList[scores++] = ball;

	printSeries(_background);

	uint8_t maxTextSize = getMaxTextSize();
	if (scoreText.getSize() > maxTextSize)
		scoreText.setSize(maxTextSize);

	scoreText.setText(String(getScores()));
	scoreText.show();
}

SnookerBalls SnookerPlayerView::revokeLastBall()
{
	scoreText.clear();

	printSeries(_color);

	SnookerBalls ball = (scores != 0) ? scoredBallsList[--scores] : SnookerBalls::miss;

	printSeries(_background);

	scoreText.setText(String(getScores()));
	scoreText.show();

	return ball;
}

SnookerBalls SnookerPlayerView::getLastBall() const
{
	if (scores != 0) 
		return scoredBallsList[scores - 1]; 
	
	return SnookerBalls::miss;
}

void SnookerPlayerView::drawFocus(uint16_t color)
{
	const int16_t FOCUS_WIDTH = _w - FOCUS_OFFSET - FOCUS_OFFSET;

	const int16_t FOCUS_X = _x + FOCUS_OFFSET;
	const int16_t FOCUS_Y = _y + _h - FOCUS_OFFSET - FOCUS_HEIGHT;

	const int16_t FOCUS_X1 = FOCUS_X + FOCUS_OFFSET;
	const int16_t FOCUS_X2 = FOCUS_X + FOCUS_WIDTH - FOCUS_OFFSET / 2;
	const int16_t FOCUS_X3 = FOCUS_X + FOCUS_OFFSET + FOCUS_WIDTH / 2 - FOCUS_OFFSET;

	_tft->fillRoundRect(FOCUS_X, FOCUS_Y, FOCUS_WIDTH, FOCUS_HEIGHT, FOCUS_OFFSET, color);
	_tft->fillTriangle(FOCUS_X1, FOCUS_Y, FOCUS_X2, FOCUS_Y, FOCUS_X3, FOCUS_Y - FOCUS_TRIANGLE_HEIGHT, color);
}

void SnookerPlayerView::printSeries(uint16_t color)
{
	_tft->setTextSize(SERIES_TEXT_SIZE);

	_tft->setCursor(_x + SERIES_OFFSET + SERIES_SHIFT, _y + SERIES_OFFSET + SERIES_SHIFT);

	String _series = getSeries();

	for (unsigned int idx = _series.length() > SERIES_MAX_CHARS ? _series.length() - SERIES_MAX_CHARS : 0; idx < _series.length(); ++idx)
	{
		char ch = _series[idx];

		_tft->setTextColor(color == _background ? getCharColor(ch) : color);

		int16_t x1, y1;
		uint16_t h1, w1;

		// calculate bounds for next char
		_tft->getTextBounds(String(ch), _tft->getCursorX(), _tft->getCursorY(), &x1, &y1, &w1, &h1);

		// new line if overrides
		if (x1 + w1 > _x + _w - SERIES_OFFSET - SERIES_SHIFT)
		{
			_tft->setCursor(_x + SERIES_OFFSET + SERIES_SHIFT, y1 + h1 + SERIES_SHIFT);
		}

		_tft->print(ch);
	}
}

String SnookerPlayerView::getSeries() const
{
	String series;

	for (uint8_t i = 0; i < scores; i++)
	{
		switch (scoredBallsList[i])
		{
		case SnookerBalls::foul_1:
		case SnookerBalls::foul_2:
		case SnookerBalls::foul_3:
		case SnookerBalls::foul_4:
		case SnookerBalls::foul_5:
		case SnookerBalls::foul_6:
		case SnookerBalls::foul_7:
			if (series.endsWith("-"))
				series.setCharAt(series.length() - 1, '+');
			else
				series += '+';
		default:
			break;
		}

		switch (scoredBallsList[i])
		{
		case SnookerBalls::miss:
			if (i != 0) series += '-';	break; // do not show first miss
		case SnookerBalls::foul_1:
		case SnookerBalls::red:
			series += '1';	break;
		case SnookerBalls::foul_2:
		case SnookerBalls::yellow:
			series += '2';	break;
		case SnookerBalls::foul_3:
		case SnookerBalls::green:
			series += '3';	break;
		case SnookerBalls::foul_4:
		case SnookerBalls::brown:
			series += '4';	break;
		case SnookerBalls::foul_5:
		case SnookerBalls::blue:
			series += '5';	break;
		case SnookerBalls::foul_6:
		case SnookerBalls::pink:
			series += '6';	break;
		case SnookerBalls::foul_7:
		case SnookerBalls::black:
			series += '7';	break;
			break;
		default:
			break;
		}
	}
	return series;
}

uint16_t SnookerPlayerView::getCharColor(const char ch) const
{
	switch (ch)
	{
	case '1':
		return RED;
	case '2':
		return YELLOW;
	case '3':
		return GREEN;
	case '4':
		return BROWN;
	case '5':
		return BLUE;
	case '6':
		return PINK;
	default:
		return BLACK;
	}
}


#endif