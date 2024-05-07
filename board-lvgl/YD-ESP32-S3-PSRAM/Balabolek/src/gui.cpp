#include "gui.h"
#include "gui_main.h"

#include "TaskAudio.h"
#include "TaskInteract.h"

#include "defs.h"

SemaphoreHandle_t gui_mutex = NULL;

SNOOKER_ACTION* historyActions;		// list of actions
uint16_t numberActions = 0;			// number of executed actions

BoardState_Publishing boardPublishing =
{
    .dartsPlayer1name = NULL,
    .dartsPlayer2name = NULL,
    .dartsPlayer3name = NULL,
	.player1name = NULL,
	.player2name = NULL,
	.gamePly1Score = 0,
	.gamePly2Score = 0,
	.gamePlyBreak = LEFT,
	.gamePlyCount = TWO,
	.playerEx1name = NULL,
	.playerEx2name = NULL,
	.playerEx3name = NULL,
	.gameExPly1Score = 0,
	.gameExPly2Score = 0,
	.gameExPly3Score = 0,
	.tvGameScorePly1 = 0,
	.tvGameScorePly2 = 0,
	.tvGameScoreMax = 0,
	.tvFrameScorePly1 = 0,
	.tvFrameScorePly2 = 0,
    .snookerPly1Handicap = 0,
    .snookerPly2Handicap = 0,
    .snookerControlBalls = true,
    .snooker6Red = false,
	.snookerPly1Scores = 0,
    .snookerPly2Scores= 0,
};

BoardState_Settings boardSettings =
{
	.isAPEnabled = false,
	.isWifiEnabled = true,
	.isTelegaEnabled = true,
	.isAudioEnabled = true,
	.audioVolume = 5
};

void gui_init()
{
	lv_display_t *dispp = lv_display_get_default();
	lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
	lv_display_set_theme(dispp, theme);

	LV_EVENT_GET_COMP_CHILD = lv_event_register_id();
	LV_EVENT_SET_COMP_CHILD = lv_event_register_id();
	LV_EVENT_GET_COMP_CALLBACK = lv_event_register_id();
	LV_EVENT_SET_COMP_CALLBACK = lv_event_register_id();

	gui_main_create();

	gui_setPlayerName(DARTS_PLAYER1, "Игрок 1");
	gui_setPlayerName(DARTS_PLAYER2, "Игрок 2");
	gui_setPlayerName(DARTS_PLAYER3, "Игрок 3");
	gui_setPlayerName(PLAYER1, "Нажми");
	gui_setPlayerName(PLAYER2, "Держи");
	gui_setPlayerName(PLAYER_EX1, "Нажми");
	gui_setPlayerName(PLAYER_EX2, "и");
	gui_setPlayerName(PLAYER_EX3, "Держи");

	historyActions = static_cast<SNOOKER_ACTION*>(lv_malloc(sizeof(SNOOKER_ACTION) * MAX_ACTIONS));

	lv_screen_load(ui_ScreenMain);

	if (boardSettings.isWifiEnabled)
	{
		interactMessage_t tMsg =
		{
			.type = I_WIFI_ON,
			.body = { NULL, NULL, NULL, NULL }
		};
		
		sendInteractMessage(tMsg);
	}
	
	if (boardSettings.isAudioEnabled)
	{
		audio_turnOn();
		audio_say(SAY_HELLO);
	}
}


const char* gui_getPlayerName(GAME_PLAYER_NAME player)
{
	switch (player)
	{
	case GAME_PLAYER_NAME::DARTS_PLAYER1:
		return boardPublishing.dartsPlayer1name;
	case GAME_PLAYER_NAME::DARTS_PLAYER2:
		return boardPublishing.dartsPlayer2name;
	case GAME_PLAYER_NAME::DARTS_PLAYER3:
		return boardPublishing.dartsPlayer3name;
	case GAME_PLAYER_NAME::PLAYER1:
		return boardPublishing.player1name;
	case GAME_PLAYER_NAME::PLAYER2:
		return boardPublishing.player2name;
	case GAME_PLAYER_NAME::PLAYER_EX1:
		return boardPublishing.playerEx1name;
	case GAME_PLAYER_NAME::PLAYER_EX2:
		return boardPublishing.playerEx2name;
	case GAME_PLAYER_NAME::PLAYER_EX3:
		return boardPublishing.playerEx3name;
	default:
		return NULL;
	}
}

void gui_setPlayerName(GAME_PLAYER_NAME dst, const char* src)
{
	char **player;

	// get pointer to variable with allocated memory
	switch (dst)
	{
	case GAME_PLAYER_NAME::DARTS_PLAYER1:
		player = &(boardPublishing.dartsPlayer1name);
		break;
	case GAME_PLAYER_NAME::DARTS_PLAYER2:
		player = &(boardPublishing.dartsPlayer2name);
		break;
	case GAME_PLAYER_NAME::DARTS_PLAYER3:
		player = &(boardPublishing.dartsPlayer3name);
		break;
	case GAME_PLAYER_NAME::PLAYER1:
		player = &(boardPublishing.player1name);
		break;
	case GAME_PLAYER_NAME::PLAYER2:
		player = &(boardPublishing.player2name);
		break;
	case GAME_PLAYER_NAME::PLAYER_EX1:
		player = &(boardPublishing.playerEx1name);
		break;
	case GAME_PLAYER_NAME::PLAYER_EX2:
		player = &(boardPublishing.playerEx2name);
		break;
	case GAME_PLAYER_NAME::PLAYER_EX3:
		player = &(boardPublishing.playerEx3name);
		break;
	default:
		return;
	}

	// if source is NULL - set empty string
	if (src == NULL)
	{
		if (*player != NULL)
			lv_free(*player);
		*player = (char *)lv_malloc(sizeof(char));
		if (*player != NULL)
			(*player)[0] = '\0';
	}
	// if strings are not equals - copy new string
	else
	{
		if (*player != NULL && strcmp(src, *player) == 0)
			return; // string are equal

		size_t textLenght = strlen(src);

		lv_free(*player);

		*player = (char *)lv_malloc(sizeof(char) * (textLenght + 1));

		if (*player != NULL)
		{
			lv_memcpy(*player, src, textLenght);
			(*player)[textLenght] = '\0';
		}
	}
}


void gui_turnAP(boolean state)
{
	boardSettings.isAPEnabled = state;
}

void gui_turnWiFi(boolean state)
{
	boardSettings.isWifiEnabled = state;

	if (state)
	{
		interactMessage_t tMsg = 
		{
			.type = I_WIFI_ON,
			.body = { NULL, NULL, NULL, NULL }
		};
		
		sendInteractMessage(tMsg);
	}
	else
	{
		interactMessage_t tMsg =
		{
			.type = I_WIFI_OFF,
			.body = { NULL, NULL, NULL, NULL }
		};

		sendInteractMessage(tMsg);
	}
}

void gui_turnTelegram(boolean state)
{
	boardSettings.isTelegaEnabled = state;
}

void gui_turnAudio(boolean state)
{
	boardSettings.isAudioEnabled = state;

	if (state)
	{
		audio_turnOn();
		audio_say(SAY_HELLO);
	}
	else
	{
		audio_turnOff();
	}
}

void gui_setVolume(uint8_t volume)
{
	boardSettings.audioVolume = volume;
	audio_reset();
	audio_say(SAY_HELLO);
}

float gui_getVolumeInRange(float out_min, float out_max)
{
	uint8_t in_min = 1;
	uint8_t in_max = 10;

	// Преобразуем значение из одного диапазона в нормализованное значение (от 0 до 1)
	float normalized_value = (float)(boardSettings.audioVolume - in_min) / (in_max - in_min);

	// Преобразуем нормализованное значение в новый диапазон
	float mapped_value = (normalized_value * (out_max - out_min)) + out_min;

	return mapped_value;
}


bool gui_wifiIsEnabledAndConnected()
{
	return boardSettings.isWifiEnabled && isWifiConnected();
}

bool gui_stateAwaiting()
{
	return isWaitingHistory();
}

void gui_stateRequest()
{
	interactMessage_t tMsg = {
		.type = I_MQTT_SUB,
		.body = { NULL, NULL, NULL, NULL }
	};

	sendInteractMessage(tMsg);
}

void gui_stateRevoke()
{
	interactMessage_t tMsg = {
		.type = I_MQTT_UNSUB,
		.body = { NULL, NULL, NULL, NULL }
	};

	sendInteractMessage(tMsg);
}


void gui_publishCurrentState()
{
	interactMessage_t tMsg = {
		.type = I_MQTT_PUB,
		.body = { NULL, NULL, NULL, NULL }
	};

	const char delimiter[] = "~";

	String msg;

	msg += gui_getPlayerName(PLAYER1); // idx = 0
	msg += delimiter;

	msg += gui_getPlayerName(PLAYER2); // idx = 1
	msg += delimiter;

	msg += boardPublishing.gamePly1Score; // idx = 2
	msg += delimiter;

	msg += boardPublishing.gamePly2Score; // idx = 3
	msg += delimiter;

	msg += boardPublishing.gamePlyBreak; // idx = 4
	msg += delimiter;

	msg += boardPublishing.gamePlyCount; // idx = 5
	msg += delimiter;

	msg += gui_getPlayerName(PLAYER_EX1); // idx = 6
	msg += delimiter;

	msg += gui_getPlayerName(PLAYER_EX2); // idx = 7
	msg += delimiter;

	msg += gui_getPlayerName(PLAYER_EX3); // idx = 8
	msg += delimiter;

	msg += boardPublishing.gameExPly1Score; // idx = 9
	msg += delimiter;

	msg += boardPublishing.gameExPly2Score; // idx = 10
	msg += delimiter;

	msg += boardPublishing.gameExPly3Score; // idx = 11
	msg += delimiter;

	msg += boardPublishing.tvGameScorePly1; // idx = 12
	msg += delimiter;

	msg += boardPublishing.tvGameScorePly2; // idx = 13
	msg += delimiter;

	msg += boardPublishing.tvGameScoreMax; // idx = 14
	msg += delimiter;

	msg += boardPublishing.tvFrameScorePly1; // idx = 15
	msg += delimiter;

	msg += boardPublishing.tvFrameScorePly2; // idx = 16
	msg += delimiter;

	msg += boardPublishing.snookerPly2Handicap; // idx = 17
	msg += delimiter;

	msg += boardPublishing.snookerPly2Handicap; // idx = 18
	msg += delimiter;

	msg += boardPublishing.snookerControlBalls; // idx = 19
	msg += delimiter;

	msg += boardPublishing.snooker6Red; // idx = 20
	msg += delimiter;

	msg += boardPublishing.snookerPly1Scores; // idx = 21
	msg += delimiter;

	msg += boardPublishing.snookerPly2Scores; // idx = 22
	msg += delimiter;

	msg += numberActions; // idx = 23
	msg += delimiter;

	for (uint8_t idx = 0; idx < numberActions; idx++)
	{
		msg += historyActions[idx]; // idx = 24...
		msg += delimiter;
	}

	tMsg.body.msg = static_cast<char*>(CUSTOM_MALLOC(msg.length() + 1));
	if(tMsg.body.msg) strcpy(tMsg.body.msg, msg.c_str());

	sendInteractMessage(tMsg);
}

void gui_restoreCurrentState(char* state)
{
	const char delimiter[] = "~";

	const char* value = strtok(state, delimiter);
 
 	uint16_t idx = 0;

	while (value != NULL)
	{
		switch (idx)
		{
		case 0:
			gui_setPlayerName(PLAYER1, value);
			break;
		case 1:
			gui_setPlayerName(PLAYER2, value);
			break;
		case 2:
			boardPublishing.gamePly1Score = atoi(value);
			break;
		case 3:
			boardPublishing.gamePly2Score = atoi(value);
			break;
		case 4:
			boardPublishing.gamePlyBreak = static_cast<GAME_PLAYER_BREAK>(atoi(value));
			break;
		case 5:
			boardPublishing.gamePlyCount = static_cast<GAME_PLAYER_COUNT>(atoi(value));
			break;
		case 6:
			gui_setPlayerName(PLAYER_EX1, value);
			break;
		case 7:
			gui_setPlayerName(PLAYER_EX2, value);
			break;
		case 8:
			gui_setPlayerName(PLAYER_EX3, value);
			break;
		case 9:
			boardPublishing.gameExPly1Score = atoi(value);
			break;
		case 10:
			boardPublishing.gameExPly2Score = atoi(value);
			break;
		case 11:
			boardPublishing.gameExPly3Score = atoi(value);
			break;
		case 12:
			boardPublishing.tvGameScorePly1 = atoi(value);
			break;
		case 13:
			boardPublishing.tvGameScorePly2 = atoi(value);
			break;
		case 14:
			boardPublishing.tvGameScoreMax = atoi(value);
			break;
		case 15:
			boardPublishing.tvFrameScorePly1 = atoi(value);
			break;
		case 16:
			boardPublishing.tvFrameScorePly2 = atoi(value);
			break;
		case 17:
			boardPublishing.snookerPly1Handicap = atoi(value);
			break;
		case 18:
			boardPublishing.snookerPly2Handicap = atoi(value);
			break;
		case 19:
			boardPublishing.snookerControlBalls = atoi(value);
			break;
		case 20:
			boardPublishing.snooker6Red = atoi(value);
			break;
		case 21:
			boardPublishing.snookerPly1Scores = atoi(value);
			break;
		case 22:
			boardPublishing.snookerPly2Scores = atoi(value);
			break;
		case 23:
			numberActions = 0;
			break;
		default:
			historyActions[numberActions++] = static_cast<SNOOKER_ACTION>(atoi(value));
			break;
		}

		++idx;
		value = strtok (NULL, delimiter);
	}
}


void gui_sendTelegaPollMessage(GAME_PLAYER_COUNT cnt)
{
	if (!boardSettings.isTelegaEnabled) return;

	const char pollMsg[] = "И кто же победит?";

	interactMessage_t tMsg;

	tMsg.type = I_TELEGA_POLL;

	tMsg.body.msg = static_cast<char*>(CUSTOM_MALLOC(sizeof(pollMsg)));
	if(tMsg.body.msg) strcpy(tMsg.body.msg, pollMsg);

	size_t optLen;
	
	if(cnt == GAME_PLAYER_COUNT::TWO)
	{
		optLen = strlen(gui_getPlayerName(PLAYER1));
		tMsg.body.opt1 = static_cast<char*>(CUSTOM_MALLOC(optLen + 1));
		if(tMsg.body.opt1) strcpy(tMsg.body.opt1, gui_getPlayerName(PLAYER1));

		optLen = strlen(gui_getPlayerName(PLAYER2));
		tMsg.body.opt2 = static_cast<char*>(CUSTOM_MALLOC(optLen + 1));
		if(tMsg.body.opt2) strcpy(tMsg.body.opt2, gui_getPlayerName(PLAYER2));

		tMsg.body.opt3 = NULL;
	}
	else if(cnt == GAME_PLAYER_COUNT::THREE)
	{
		optLen = strlen(gui_getPlayerName(PLAYER_EX1));
		tMsg.body.opt1 = static_cast<char*>(CUSTOM_MALLOC(optLen + 1));
		if(tMsg.body.opt1) strcpy(tMsg.body.opt1, gui_getPlayerName(PLAYER_EX1));

		optLen = strlen(gui_getPlayerName(PLAYER_EX2));
		tMsg.body.opt2 = static_cast<char*>(CUSTOM_MALLOC(optLen + 1));
		if(tMsg.body.opt2) strcpy(tMsg.body.opt2, gui_getPlayerName(PLAYER_EX2));

		optLen = strlen(gui_getPlayerName(PLAYER_EX3));
		tMsg.body.opt3 = static_cast<char*>(CUSTOM_MALLOC(optLen + 1));
		if(tMsg.body.opt3) strcpy(tMsg.body.opt3, gui_getPlayerName(PLAYER_EX3));
	}

	sendInteractMessage(tMsg);
}

void gui_sendTelegaGameScoreMessage(GAME_PLAYER_COUNT cnt)
{
	if (!boardSettings.isTelegaEnabled) return;

	interactMessage_t tMsg;

	tMsg.type = I_TELEGA_MSG_NEW;

	String msg = F("Матч:\n");

	if(cnt == GAME_PLAYER_COUNT::TWO)
	{
		msg += boardPublishing.gamePly1Score;
		msg += F(" - ");
		msg += gui_getPlayerName(PLAYER1);

		msg += F("\n");

		msg += boardPublishing.gamePly2Score;
		msg += F(" - ");
		msg += gui_getPlayerName(PLAYER2);
	}
	else if(cnt == GAME_PLAYER_COUNT::THREE)
	{
		msg += boardPublishing.gameExPly1Score;
		msg += F(" - ");
		msg += gui_getPlayerName(PLAYER_EX1);

		msg += F("\n");

		msg += boardPublishing.gameExPly2Score;
		msg += F(" - ");
		msg += gui_getPlayerName(PLAYER_EX2);

		msg += F("\n");

		msg += boardPublishing.gameExPly3Score;
		msg += F(" - ");
		msg += gui_getPlayerName(PLAYER_EX3);
	}

	tMsg.body.msg = static_cast<char*>(CUSTOM_MALLOC(msg.length() + 1));
	if(tMsg.body.msg) strcpy(tMsg.body.msg, msg.c_str());

	tMsg.body.opt1 = NULL;
	tMsg.body.opt2 = NULL;
	tMsg.body.opt3 = NULL;

	sendInteractMessage(tMsg);
}

void gui_sendTelegaFrameScoreMessage(bool update)
{
	if (!boardSettings.isTelegaEnabled) return;

	interactMessage_t tMsg;
	tMsg.type = update ? I_TELEGA_MSG_UPD : I_TELEGA_MSG_NEW;

	String msg = F("Партия:\n");

	msg += boardPublishing.snookerPly1Scores;
	msg += F(" - ");
	msg += gui_getPlayerName(PLAYER1);

	msg += F("\n");

	msg += boardPublishing.snookerPly2Scores;
	msg += F(" - ");
	msg += gui_getPlayerName(PLAYER2);

	tMsg.body.msg = static_cast<char*>(CUSTOM_MALLOC(msg.length() + 1));
	if(tMsg.body.msg) strcpy(tMsg.body.msg, msg.c_str());

	tMsg.body.opt1 = NULL;
	tMsg.body.opt2 = NULL;
	tMsg.body.opt3 = NULL;

	sendInteractMessage(tMsg);
}

void gui_sendTelegaTVGameScoreMessage()
{
	if (!boardSettings.isTelegaEnabled) return;

	interactMessage_t tMsg;

	tMsg.type = I_TELEGA_MSG_NEW;

	String msg = F("Матч:\n");

	msg += boardPublishing.tvGameScorePly1;
	msg += F(" - ");
	msg += gui_getPlayerName(PLAYER1);

	msg += F("\n");

	msg += boardPublishing.tvGameScorePly2;
	msg += F(" - ");
	msg += gui_getPlayerName(PLAYER2);

	tMsg.body.msg = static_cast<char*>(CUSTOM_MALLOC(msg.length() + 1));
	if(tMsg.body.msg) strcpy(tMsg.body.msg, msg.c_str());

	tMsg.body.opt1 = NULL;
	tMsg.body.opt2 = NULL;
	tMsg.body.opt3 = NULL;

	sendInteractMessage(tMsg);
}

void gui_sendTelegaTVFrameScoreMessage(bool update)
{
	if (!boardSettings.isTelegaEnabled) return;

	interactMessage_t tMsg;
	tMsg.type = update ? I_TELEGA_MSG_UPD : I_TELEGA_MSG_NEW;

	String msg = F("Партия:\n");

	msg += boardPublishing.tvFrameScorePly1;
	msg += F(" - ");
	msg += gui_getPlayerName(PLAYER1);

	msg += F("\n");

	msg += boardPublishing.tvFrameScorePly2;
	msg += F(" - ");
	msg += gui_getPlayerName(PLAYER2);

	tMsg.body.msg = static_cast<char*>(CUSTOM_MALLOC(msg.length() + 1));
	if(tMsg.body.msg) strcpy(tMsg.body.msg, msg.c_str());

	tMsg.body.opt1 = NULL;
	tMsg.body.opt2 = NULL;
	tMsg.body.opt3 = NULL;

	sendInteractMessage(tMsg);
}


void gui_sayLot(uint8_t lot)
{
	audio_reset();
	audio_say(lot);
}

void gui_sayGameResult(GAME_PLAYER_COUNT cnt)
{
	audio_reset();
	audio_say(SAY_GAME);

	if(cnt == TWO)
	{
		audio_say(boardPublishing.gamePly1Score);
		audio_say(boardPublishing.gamePly2Score);
	}
	else
	{
		audio_say(boardPublishing.gameExPly1Score);
		audio_say(boardPublishing.gameExPly2Score);
		audio_say(boardPublishing.gameExPly3Score);
	}
}

void gui_sayFrameResult()
{
	audio_reset();
	audio_say(boardPublishing.snookerPly1Scores);
	audio_say(boardPublishing.snookerPly2Scores);
}

void gui_sayTVGameResult()
{
	audio_reset();
	audio_say(SAY_GAME);
	audio_say(boardPublishing.tvGameScorePly1);
	audio_say(boardPublishing.tvGameScorePly2);
}

void gui_sayTVFrameResult()
{
	audio_reset();
	audio_say(boardPublishing.tvFrameScorePly1);
	audio_say(boardPublishing.tvFrameScorePly2);
}
