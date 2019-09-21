#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

#define MUSIC_MASK (keycode != KC_NO)

/* disable debug */
#define NO_DEBUG

/* disable print */
#define NO_PRINT

// Ver isso aqui
#define PERMISSIVE_HOLD
#define TAPPING_FORCE_HOLD

#define LEADER_TIMEOUT 500
#define LEADER_PER_KEY_TIMING

#define TAPPING_TOGGLE 2

#define TAPPING_TERM 200

// #define COMBO_COUNT 1

#endif
