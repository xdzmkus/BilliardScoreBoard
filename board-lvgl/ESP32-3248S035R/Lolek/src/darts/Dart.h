#ifndef _DART_h
#define _DART_h

#include <Arduino.h>

String suggest(int16_t scores);

typedef enum
{
	OVERALL,
	SCORES,
	SECTOR,
	DOUBLE,
	TRIPLE
} DartType;

class Dart
{
protected:

	const DartType type;
	const int16_t value;

public:

	Dart(DartType aType, int16_t aValue);

	DartType getType() const;

	int16_t getScore() const;

	String toString() const;
};


#endif

