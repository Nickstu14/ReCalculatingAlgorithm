#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_


enum GameState {
	GS_NULL = 0,
	GS_COSTSETUP,
	GS_SCAN,
	GS_RESCAN,
	GS_PLAY,
	GS_CLEAN,
	GS_DYNAMIC_RESCAN,
	GS_RESET
	
};

#endif