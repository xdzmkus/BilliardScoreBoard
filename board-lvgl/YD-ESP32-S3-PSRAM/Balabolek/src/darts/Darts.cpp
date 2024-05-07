#include "Dart.h"

String suggest(int16_t scores)
{
	switch (scores)
	{
	case 170: return F("T20 T20 Bull");
	case 167: return F("T20 T19 Bull");
	case 164: return F("T20 T18 Bull");
	case 161: return F("T20 T17 Bull");
	case 160: return F("T20 T20 D20");
	case 158: return F("T20 T20 D19");
	case 157: return F("T20 T19 D20");
	case 156: return F("T20 T20 D18");
	case 155: return F("T20 T19 D19");
	case 154: return F("T20 T18 D20");
	case 153: return F("T20 T19 D18");
	case 152: return F("T20 T20 D16");
	case 151: return F("T20 T17 D20");
	case 150: return F("T20 T18 D18");
	case 149: return F("T20 T19 D16");
	case 148: return F("T20 T16 D20");
	case 147: return F("T20 T17 D18");
	case 146: return F("T20 T18 D16");
	case 145: return F("T20 T15 D20");
	case 144: return F("T20 T20 D12");
	case 143: return F("T20 T17 D16");
	case 142: return F("T20 T14 D20");
	case 141: return F("T20 T15 D18");
	case 140: return F("T20 T20 D10");
	case 139: return F("T20 T19 D11");
	case 138: return F("T20 T18 D12");
	case 137: return F("T20 T19 D10");
	case 136: return F("T20 T20 D8");
	case 135: return F("Bull T15 D20");
	case 134: return F("T20 T14 D16");
	case 133: return F("T20 T19 D8");
	case 132: return F("Bull T14 D20");
	case 131: return F("T20 T13 D16");
	case 130: return F("T20 20 Bull");
	case 129: return F("T19 T16 D12");
	case 128: return F("T18 T18 D10");
	case 127: return F("T20 T17 D8");
	case 126: return F("T19 19 Bull");
	case 125: return F("Bull 25 Bull");
	case 124: return F("T20 T14 D11");
	case 123: return F("T19 T16 D9");
	case 122: return F("T18 T18 D7");
	case 121: return F("T20 T11 D14");
	case 120: return F("T20 20 D20");
	case 119: return F("T19 T12 D13");
	case 118: return F("T20 18 D20");
	case 117: return F("T20 17 D20");
	case 116: return F("T20 16 D20");
	case 115: return F("T20 15 D20");
	case 114: return F("T18 20 D20");
	case 113: return F("T19 16 D20");
	case 112: return F("T20 12 D20");
	case 111: return F("T20 11 D20");
	case 110: return F("T20 Bull");
	case 109: return F("T20 9 D20");
	case 108: return F("T18 14 D20");
	case 107: return F("T19 Bull");
	case 106: return F("T20 14 D16");
	case 105: return F("T20 13 D16");
	case 104: return F("T18 Bull");
	case 103: return F("T19 10 D18");
	case 102: return F("T20 10 D16");
	case 101: return F("T17 Bull");
	case 100: return F("T20 D20");
	case 99: return F("T19 10 D16");
	case 98: return F("T20 D19");
	case 97: return F("T19 D20");
	case 96: return F("T20 D18");
	case 95: return F("T19 D19");
	case 94: return F("T18 D20");
	case 93: return F("T19 D18");
	case 92: return F("T20 D16");
	case 91: return F("T17 D20");
	case 90: return F("T18 D18");
	case 89: return F("T19 D16");
	case 88: return F("T20 D14");
	case 87: return F("T17 D18");
	case 86: return F("T18 D16");
	case 85: return F("T15 D20");
	case 84: return F("T20 D12");
	case 83: return F("T17 D16");
	case 82: return F("T14 D20");
	case 81: return F("T15 D18");
	case 80: return F("T20 D10");
	case 79: return F("T19 D11");
	case 78: return F("T18 D12");
	case 77: return F("T19 D10");
	case 76: return F("T20 D8");
	case 75: return F("T17 D12");
	case 74: return F("T14 D16");
	case 73: return F("T19 D8");
	case 72: return F("T16 D12");
	case 71: return F("T13 D16");
	case 70: return F("T20 D5");
	case 69: return F("T19 D6");
	case 68: return F("T18 D7");
	case 67: return F("T17 D8");
	case 66: return F("T16 D9");
	case 65: return F("T15 D10");
	case 64: return F("T14 D11");
	case 63: return F("T13 D12");
	case 62: return F("T12 D13");
	case 61: return F("T11 D14");
	case 60: return F("20 D20");
	case 59: return F("19 D20");
	case 58: return F("18 D20");
	case 57: return F("17 D20");
	case 56: return F("16 D20");
	case 55: return F("15 D20");
	case 54: return F("14 D20");
	case 53: return F("13 D20");
	case 52: return F("12 D20");
	case 51: return F("11 D20");
	case 50: return F("10 D20");
	case 49: return F("9 D20");
	case 48: return F("8 D20");
	case 47: return F("15 D16");
	case 46: return F("10 D18");
	case 45: return F("13 D16");
	case 44: return F("12 D16");
	case 43: return F("11 D16");
	case 42: return F("10 D16");
	case 41: return F("9 D16");
	case 40: return F("D20");
	case 39: return F("7 D16");
	case 38: return F("D19");
	case 37: return F("5 D16");
	case 36: return F("D18");
	case 35: return F("3 D16");
	case 34: return F("D17");
	case 33: return F("1 D16");
	case 32: return F("D16");
	case 31: return F("7 D12");
	case 30: return F("D15");
	case 29: return F("5 D12");
	case 28: return F("D14");
	case 27: return F("3 D12");
	case 26: return F("D13");
	case 25: return F("1 D12");
	case 24: return F("D12");
	case 23: return F("7 D8");
	case 22: return F("D11");
	case 21: return F("5 D8");
	case 20: return F("D10");
	case 19: return F("3 D8");
	case 18: return F("D9");
	case 17: return F("9 D4");
	case 16: return F("D8");
	case 15: return F("7 D4");
	case 14: return F("D7");
	case 13: return F("5 D4");
	case 12: return F("D6");
	case 11: return F("3 D4");
	case 10: return F("D5");
	case 9: return F("1 D4");
	case 8: return F("D4");
	case 7: return F("3 D2");
	case 6: return F("D3");
	case 5: return F("1 D2");
	case 4: return F("D2");
	case 3: return F("1 D1");
	case 2: return F("D1");
	default:
		return "";
	}
}

Dart::Dart(DartType aType, int16_t aValue) : type(aType), value(aValue)
{
}

DartType Dart::getType() const
{
	return type;
}

int16_t Dart::getScore() const
{
	switch (type)
	{
	case DOUBLE:
		return 2 * value;
	case TRIPLE:
		return 3 * value;
	default:
		return value;
	}
}

String Dart::toString() const
{
	String dartStr = value < 0 ? "-" : "+";

	switch (type)
	{
		case OVERALL:
			dartStr = String("=");
			dartStr += value;
			break;
		case SCORES:
			dartStr += abs(value);
			break;
		case SECTOR:
			dartStr += String("S");
			dartStr += abs(value);
			break;
		case DOUBLE:
			dartStr += String("D");
			dartStr += abs(value);
			break;
		case TRIPLE:
			dartStr += String("T");
			dartStr += abs(value);
			break;
		default:
			break;
	}

	return dartStr;
}


