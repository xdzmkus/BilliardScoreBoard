// PoolPlayerViewHalf.h

#ifndef _POOLPLAYERVIEWHALF_H_
#define _POOLPLAYERVIEWHALF_H_

#include "PoolPlayerView.h"

class PoolPlayerViewHalf : public PoolPlayerView
{
public:

	PoolPlayerViewHalf(Adafruit_GFX* tft, uint16_t background, uint16_t color, int16_t x, int16_t y, uint16_t w, uint16_t h)
		: PoolPlayerView(tft, background, color, x, y, w, h)
	{
	}

	inline virtual uint8_t getMaxTextSize() const override
	{
		int8_t score = getScores();

		if (score >= 0 && score < 10) return 15;
		if (score >= 100 || score <= -10) return 7;
		return 11;
	}

private:

	PoolPlayerViewHalf(const PoolPlayerViewHalf&) = delete;
	PoolPlayerViewHalf& operator=(const PoolPlayerViewHalf&) = delete;

};

#endif

