// SnookerPlayer.h

#ifndef _SNOOKERPLAYER_H_
#define _SNOOKERPLAYER_H_

enum class SnookerBalls
{
	red = 1,
	yellow = 2,
	green = 3,
	brown = 4,
	blue = 5,
	pink = 6,
	black = 7
};

class SnookerPlayer
{
protected:

	uint8_t scores = 0;

	uint8_t wonFrames = 0;
	uint8_t lostFrames = 0;

	bool extensionAvailable = true;

public:

	void reset()
	{
		resetScores();
		resetFrames();
		extensionAvailable = true;
	}

	void resetScores()
	{
		scores = 0;
	}

	void resetFrames()
	{
		wonFrames = 0;
		lostFrames = 0;
	}

	uint8_t getScores() const
	{
		return scores;
	}

	uint8_t getWonFrames() const
	{
		return wonFrames;
	}

	uint8_t getLostFrames() const
	{
		return lostFrames;
	}

	void wonFrame()
	{
		++wonFrames;
		extensionAvailable = true;
	}

	void lostFrame()
	{
		++lostFrames;
		extensionAvailable = true;
	}

	bool isExtensionAvailable() const
	{
		return extensionAvailable;
	}

	bool takeExtension()
	{
		if (extensionAvailable)
		{
			extensionAvailable = false;
			return true;
		}
		return false;
	}

	void restoreExtension()
	{
		extensionAvailable = true;
	}

	void pocketBall(SnookerBalls ball)
	{
		scores += static_cast<uint8_t>(ball);
	}
};

#endif
