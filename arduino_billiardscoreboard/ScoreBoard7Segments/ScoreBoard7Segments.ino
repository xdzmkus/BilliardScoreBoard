#include "avr/power.h"

#define A_SEG 13
#define B_SEG 12
#define C_SEG A0
#define D_SEG A2
#define E_SEG A1
#define F_SEG A3
#define G_SEG 11
#define P_SEG 10

#define SEG_1 A4 
#define SEG_2 A5
#define SEG_3 9
#define SEG_4 8

#define PLY1_BTN_PIN 2      // left player touch button
#define PLY2_BTN_PIN 3      // right player touch button

#include <ArduinoDebounceButton.h>
ArduinoDebounceButton ply1Btn(PLY1_BTN_PIN, BUTTON_CONNECTED::VCC, BUTTON_NORMAL::OPEN);
ArduinoDebounceButton ply2Btn(PLY2_BTN_PIN, BUTTON_CONNECTED::VCC, BUTTON_NORMAL::OPEN);

uint8_t scorePly1 = 0;
uint8_t scorePly2 = 0;

bool ply1Break = true;	// show point if Player's break

typedef struct _7SegmentDigit
{
	bool A : 1;
	bool B : 1;
	bool C : 1;
	bool D : 1;
	bool E : 1;
	bool F : 1;
	bool G : 1;
};

_7SegmentDigit segmentDigits[] =
{
	{ 0, 0, 0, 0, 0, 0, 1 }, // 0
	{ 1, 0, 0, 1, 1, 1, 1 }, // 1
	{ 0, 0, 1, 0, 0, 1, 0 }, // 2
	{ 0, 0, 0, 0, 1, 1, 0 }, // 3
	{ 1, 0, 0, 1, 1, 0, 0 }, // 4
	{ 0, 1, 0, 0, 1, 0, 0 }, // 5
	{ 0, 1, 0, 0, 0, 0, 0 }, // 6
	{ 0, 0, 0, 1, 1, 1, 1 }, // 7
	{ 0, 0, 0, 0, 0, 0, 0 }, // 8
	{ 0, 0, 0, 0, 1, 0, 0 }, // 9
};

void drawDigit(uint8_t digit, bool withoutPoint)
{	
	if (digit <= 9)
	{
		digitalWrite(A_SEG, segmentDigits[digit].A);
		digitalWrite(B_SEG, segmentDigits[digit].B);
		digitalWrite(C_SEG, segmentDigits[digit].C);
		digitalWrite(D_SEG, segmentDigits[digit].D);
		digitalWrite(E_SEG, segmentDigits[digit].E);
		digitalWrite(F_SEG, segmentDigits[digit].F);
		digitalWrite(G_SEG, segmentDigits[digit].G);
	}
	else
	{
		drawSpace();
	}

	digitalWrite(P_SEG, withoutPoint); // LOW(false) - point shown
}

void drawSpace()
{
	digitalWrite(A_SEG, HIGH);
	digitalWrite(B_SEG, HIGH);
	digitalWrite(C_SEG, HIGH);
	digitalWrite(D_SEG, HIGH);
	digitalWrite(E_SEG, HIGH);
	digitalWrite(F_SEG, HIGH);
	digitalWrite(G_SEG, HIGH);
}

void showOnly1Segment(uint8_t digit, bool withoutPoint)
{
	// turn off others
	digitalWrite(SEG_2, HIGH);
	digitalWrite(SEG_3, HIGH);
	digitalWrite(SEG_4, HIGH);

	drawDigit(digit, withoutPoint);

	// turn on segment
	digitalWrite(SEG_1, LOW);
}

void showOnly2Segment(uint8_t digit, bool withoutPoint)
{
	// turn off others
	digitalWrite(SEG_1, HIGH);
	digitalWrite(SEG_3, HIGH);
	digitalWrite(SEG_4, HIGH);

	drawDigit(digit, withoutPoint);

	// turn on segment
	digitalWrite(SEG_2, LOW);
}

void showOnly3Segment(uint8_t digit, bool withoutPoint)
{
	// turn off others
	digitalWrite(SEG_1, HIGH);
	digitalWrite(SEG_2, HIGH);
	digitalWrite(SEG_4, HIGH);

	drawDigit(digit, withoutPoint);

	// turn on segment
	digitalWrite(SEG_3, LOW);
}

void showOnly4Segment(uint8_t digit, bool withoutPoint)
{
	// turn off others
	digitalWrite(SEG_1, HIGH);
	digitalWrite(SEG_2, HIGH);
	digitalWrite(SEG_3, HIGH);

	drawDigit(digit, withoutPoint);

	// turn on segment
	digitalWrite(SEG_4, LOW);
}

void handlePLYButtonEvent(const DebounceButton* button, BUTTON_EVENT eventType)
{
	switch (eventType)
	{
	case BUTTON_EVENT::Clicked:
		if (button->getPin() == PLY1_BTN_PIN)
		{
			if (scorePly1 == 99)
			{
				scorePly1 = 0;
			}
			else
			{
				++scorePly1;
			}
		}
		else
		{
			if (scorePly2 == 99)
			{
				scorePly2 = 0;
			}
			else
			{
				++scorePly2;
			}
		}
		ply1Break = !ply1Break;
		break;
	case BUTTON_EVENT::DoubleClicked:
		ply1Break = !ply1Break;
		break;
	case BUTTON_EVENT::LongPressed:
		if (button->getPin() == PLY1_BTN_PIN)
		{
			scorePly1 = 0;
		}
		else
		{
			scorePly2 = 0;
		}
		break;
	default:
		break;
	}
}

void setup()
{
	power_all_disable();
	power_timer0_enable();

	pinMode(A_SEG, OUTPUT);
	pinMode(B_SEG, OUTPUT);
	pinMode(C_SEG, OUTPUT);
	pinMode(D_SEG, OUTPUT);
	pinMode(E_SEG, OUTPUT);
	pinMode(F_SEG, OUTPUT);
	pinMode(G_SEG, OUTPUT);
	pinMode(P_SEG, OUTPUT);

	pinMode(SEG_1, OUTPUT);
	pinMode(SEG_2, OUTPUT);
	pinMode(SEG_3, OUTPUT);
	pinMode(SEG_4, OUTPUT);

	ply1Btn.initPin();
	ply1Btn.setEventHandler(handlePLYButtonEvent);

	ply2Btn.initPin();
	ply2Btn.setEventHandler(handlePLYButtonEvent);
}

void loop()
{
	ply1Btn.check();
	ply2Btn.check();

	if (scorePly1 <= 9)
	{
		showOnly1Segment(255, true); // show space
	}
	else
	{
		showOnly1Segment(scorePly1 / 10, true);   // show decade
	}
	showOnly2Segment(scorePly1 % 10, !ply1Break); // show remains

	if (scorePly2 <= 9)
	{
		showOnly3Segment(scorePly2 % 10, false); // show decade
		showOnly4Segment(255, ply1Break);		 // show remains
	}
	else
	{
		showOnly3Segment(scorePly2 / 10, false);	 // show decade
		showOnly4Segment(scorePly2 % 10, ply1Break); // show remains
	}
}
