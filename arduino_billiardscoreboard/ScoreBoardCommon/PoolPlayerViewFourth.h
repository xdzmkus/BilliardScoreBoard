// PoolPlayerViewFourth.h

#ifndef _POOLPLAYERVIEWFOURTH_H_
#define _POOLPLAYERVIEWFOURTH_H_

#include "PoolPlayerView.h"

class PoolPlayerViewFourth : public PoolPlayerView
{
public:

	PoolPlayerViewFourth(Adafruit_GFX* tft, uint16_t background, uint16_t color, int16_t x, int16_t y, uint16_t w, uint16_t h)
		: PoolPlayerView(tft, background, color, x, y, w, h)
	{
	}

	virtual uint8_t getMaxTextSize() const override
	{
		int8_t score = getScores();

		if (score >= 0 && score < 10) return 10;
		if (score >= 100 || score <= -10) return 6;
		return 8;
	}

private:

	PoolPlayerViewFourth(const PoolPlayerViewFourth&) = delete;
	PoolPlayerViewFourth& operator=(const PoolPlayerViewFourth&) = delete;

};

#endif

