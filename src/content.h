#ifndef CONTENT_H
#define CONTENT_H

#ifdef _WIN32
    #define PATH_SEP "\\"
#else
    #define PATH_SEP "/"
#endif

// Filepath join concatenate args with path separator.

#define FPJOIN(a, b)             a PATH_SEP b

// Path to a directory of various content types.

#define CONTENT_PATH             FPJOIN("..", "content")
#define AUDIO_PATH               FPJOIN(CONTENT_PATH, "audio")
#define GAME_PATH                FPJOIN(CONTENT_PATH, "game")
#define L10N_PATH                FPJOIN(CONTENT_PATH, "localization")
#define SCRIPT_PATH              FPJOIN(CONTENT_PATH, "script")

// Audio contents filepath definition.

#define AUDIO_BGM_PATH           FPJOIN(AUDIO_PATH, "bgm.wav")
#define AUDIO_BGM_PATH           FPJOIN(AUDIO_PATH, "bgm.wav")
#define AUDIO_BGM_PATH           FPJOIN(AUDIO_PATH, "bgm.wav")

// End Audio

// Game contents filepath definition.

#define GAME_SPRITE_PATH         FPJOIN(GAME_PATH, "sprite.png")
#define GAME_SPRITE_PATH         FPJOIN(GAME_PATH, "sprite.png")
#define GAME_SPRITE_PATH         FPJOIN(GAME_PATH, "sprite.png")

// End Game

// Localization contents filepath definition.

#define L10N_ID_PATH             FPJOIN(L10N_PATH, "id.csv")
#define L10N_EN_US_PATH          FPJOIN(L10N_PATH, "en-us.csv")
#define L10N_DE_DE_PATH          FPJOIN(L10N_PATH, "de-de.csv")

// End Localization

// Script contents filepath definition.

#define SCRIPT_ENTITY_PATH       FPJOIN(SCRIPT_PATH, "entity.lua")
#define SCRIPT_ENTITY_PATH       FPJOIN(SCRIPT_PATH, "entity.lua")
#define SCRIPT_ENTITY_PATH       FPJOIN(SCRIPT_PATH, "entity.lua")

// End Script

#endif