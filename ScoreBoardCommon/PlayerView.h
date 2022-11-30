// PlayerView.h

#ifndef _PLAYERVIEW_H_
#define _PLAYERVIEW_H_

#include <Adafruit_GFX.h>

class PlayerView
{
public:

	PlayerView(Adafruit_GFX* tft, uint16_t background, uint16_t color, int16_t x, int16_t y, uint16_t w, uint16_t h);

	virtual void reset();

	virtual void show();

	virtual void clearFocus();
	virtual void showFocus();

	virtual uint8_t getMaxTextSize() const = 0;

	virtual void updateTextSize(uint8_t newTextSize) = 0;

	virtual int16_t getScores() const;

protected:

	virtual void drawFocus(uint16_t color) = 0;

protected:

	Adafruit_GFX* _tft;

	const uint16_t _background;
	const uint16_t _color;

	const int16_t  _x;
	const int16_t  _y;
	const uint16_t _w;
	const uint16_t _h;

	int16_t scores;

private:

	PlayerView(const PlayerView&) = delete;
	PlayerView& operator=(const PlayerView&) = delete;

};

PlayerView::PlayerView(Adafruit_GFX* tft, uint16_t background, uint16_t color, int16_t x, int16_t y, uint16_t w, uint16_t h)
	: _tft(tft), _background(background), _color(color), _x(x), _y(y), _w(w), _h(h), scores(0)
{
}

inline void PlayerView::reset()
{
	scores = 0;
}

inline void PlayerView::show()
{
	_tft->fillRect(_x, _y, _w, _h, _background);
}


inline void PlayerView::clearFocus()
{
	drawFocus(_background);
}

inline void PlayerView::showFocus()
{
	drawFocus(_color);
}

inline int16_t PlayerView::getScores() const
{
	return scores;
}

#endif
