#ifndef _BOARDTEXT_H_
#define _BOARDTEXT_H_

#include <Adafruit_GFX.h>

class BoardText
{
public:

	BoardText(const String& text, uint8_t size, Adafruit_GFX* tft, uint16_t background, uint16_t color, int16_t x, int16_t y, uint16_t w, uint16_t h)
		: _tft(tft), _background(background), _color(color), _x(x), _y(y), _w(w), _h(h), _text(text), _size(size)
	{
	};

	void clear();
	void show();

	uint8_t getSize();

	void setText(const String& text);
	void setSize(uint8_t size);
	void setColors(uint16_t background, uint16_t color);

	void updateText(const String& text);
	void updateSize(uint8_t size);

protected:

	void draw(uint16_t color);

protected:

	Adafruit_GFX* _tft;

	uint16_t _background;
	uint16_t _color;

	int16_t _x;
	int16_t _y;
	uint16_t _w;
	uint16_t _h;

	String _text;
	uint8_t _size;

};

inline void BoardText::clear()
{
	draw(_background);
}

inline void BoardText::show()
{
	draw(_color);
}

inline uint8_t BoardText::getSize()
{
	return _size;
}

inline void BoardText::setText(const String& text)
{
	_text = text;
}

inline void BoardText::setSize(uint8_t size)
{
	_size = size;
}

inline void BoardText::setColors(uint16_t background, uint16_t color)
{
	_background = background;
	_color = color;
}

void BoardText::updateText(const String& text)
{
	if (_text == text) return;

	draw(_background);

	_text = text;

	draw(_color);
}

void BoardText::updateSize(uint8_t size)
{
	if (_size == size) return;

	draw(_background);

	_size = size;

	draw(_color);
}

void BoardText::draw(uint16_t color)
{
	_tft->setTextSize(_size);

	int16_t x1, y1;
	uint16_t h1, w1;

	_tft->getTextBounds(_text, 0, 0, &x1, &y1, &w1, &h1);
	_tft->setCursor(5 + _x + (_w - w1) / 2, _y + (_h - h1) / 2);

	_tft->setTextColor(color);

	_tft->print(_text);
}


#endif
