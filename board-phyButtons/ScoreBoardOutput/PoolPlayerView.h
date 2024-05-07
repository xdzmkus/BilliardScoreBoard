// PoolPlayerView.h

#ifndef _POOLPLAYERVIEW_H_
#define _POOLPLAYERVIEW_H_

#include "PlayerView.h"

#include "BoardText.h"

#define START_SCORE "0"

class PoolPlayerView : public PlayerView
{
public:

	PoolPlayerView(Adafruit_GFX* tft, uint16_t background, uint16_t color, int16_t x, int16_t y, uint16_t w, uint16_t h);

	void reset() override;

	void show() override;

	void updateTextSize(uint8_t newTextSize) override;

	void changeScores(int8_t delta);

protected:

	void drawFocus(uint16_t color) override;

protected:

	BoardText scoreText;

private:

	static const uint8_t FOCUS_HEIGHT = 20;

private:

	PoolPlayerView(const PoolPlayerView&) = delete;
	PoolPlayerView& operator=(const PoolPlayerView&) = delete;

};

PoolPlayerView::PoolPlayerView(Adafruit_GFX* tft, uint16_t background, uint16_t color, int16_t x, int16_t y, uint16_t w, uint16_t h) :
	PlayerView(tft, background, color, x, y, w, h),
	scoreText(START_SCORE, 0, tft, background, color, x, y, w, h)
{
}

inline void PoolPlayerView::reset()
{
	PlayerView::reset();

	scoreText.setText(START_SCORE);
	scoreText.setSize(getMaxTextSize());
}

void PoolPlayerView::show()
{
	PlayerView::show();

	scoreText.show();
}

inline void PoolPlayerView::updateTextSize(uint8_t newTextSize)
{
	scoreText.updateSize(newTextSize);
}

void PoolPlayerView::changeScores(int8_t delta)
{
	scores += delta;

	scoreText.clear();

	uint8_t maxTextSize = getMaxTextSize();
	if (scoreText.getSize() > maxTextSize)	scoreText.setSize(maxTextSize);

	scoreText.setText(String(scores));
	scoreText.show();
}

inline void PoolPlayerView::drawFocus(uint16_t color)
{
	_tft->fillTriangle(_x, _y + _h, _x + _w, _y + _h, _x + _w / 2, _y + _h - FOCUS_HEIGHT, color);
}

#endif
