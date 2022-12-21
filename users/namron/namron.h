#pragma once

#include "quantum.h"



// Umlauts
// Use Layout "US international, with dead keys"


/* -------------------------------------------------------------------------- */
/*                                   DEFINES                                  */
/* -------------------------------------------------------------------------- */

/* ---------------------------------- keys ---------------------------------- */
// special keys
#define SP_ATAB LALT(KC_TAB) //ALT+TAB
#define SP_CTAB LCTL(KC_TAB) //CTL+TAB
#define SP_ASPC LALT(KC_SPC) //ALT+SPC
#define SP_MID LSFT(KC_BTN3) //SHIFT+MIDDLEMOUSE

#define SP_SUENT MT(MOD_LGUI,KC_ENT)  //Enter when pressed, Super when hold
//#define SP_ESALT MT(MOD_LALT,KC_ESC)  //Escape when pressed, ALT when hold

#define SP_NAV LT(_NAV,KC_SPC) //SPACE when pressed, _NAV layer when hold

#define SP_ALTESC LOPT_T(KC_ESC) //ESC when pressed, L-ALT (L-OPT) when hold

#define SP_SHBS LSFT_T(KC_BSPC) //Backspace when pressed, Shift when hold

#define SP_CTL TD(TD_CTL) //CTL on press/hold, CTL+SHIFT on double press/hold, CTL+ALT on triple press/hold

#define SP_FN LT(_FN,KC_DEL) //DEL when pressed, _FN when hold


// MAC specific special keys
#define MC_CTLEN MT(MOD_LCTL,KC_ENT)  //Enter when pressed, CTL when hold
#define MC_CMD TD(TDM_CMD) //CMD on press/hold CMD+SHIFT on double press/hold, CMD+OPT on triple press/hold
#define MC_OPT TD(TDM_OPT) //OPT on press/hold OPT+SHIFT on double press/hold, OPT+CTL on triple press/hold

/* --------------------------------- colors --------------------------------- */
#define HSV_MY_PURPLE 191, 255, DEFAULT_BRIGHTNESS
#define HSV_MY_MAGENTA 213, 255, DEFAULT_BRIGHTNESS
#define HSV_MY_ORANGE  28, 255, DEFAULT_BRIGHTNESS
#define HSV_MY_GREEN 90, 255, DEFAULT_BRIGHTNESS
#define HSV_MY_CYAN 187, 56, DEFAULT_BRIGHTNESS
#define HSV_MY_TURQUOISE 120, 240, DEFAULT_BRIGHTNESS

/* -------------------------------------------------------------------------- */
/*                                  FUNCTIONS                                 */
/* -------------------------------------------------------------------------- */
// function to send single tap without modifiers
void tap_code_nomod(int keycode) {
  uint8_t temp_mods = get_mods();
  clear_mods();
  tap_code(keycode);
  set_mods(temp_mods);
}

// function to register keycode without modifiers
void register_code_nomod(int keycode) {
  uint8_t temp_mods = get_mods();
  clear_mods();
  register_code(keycode);
  set_mods(temp_mods);
}

// function to input umlauts on Mac using ALT+U combo
void tap_umlaut_mac(int keycode) {
  uint8_t temp_mods = get_mods();
  clear_mods();
  tap_code16(LOPT(KC_U));
  set_mods(temp_mods);
  tap_code(keycode);
}

enum layer_names {
  _COLEMAK,
  _MAC,
  _NAV,
  _MOUSE,
  _FN,
};

enum custom_keycodes {
  #ifndef NO_CHARYBDIS_KEYCODES
  MOD0 = CHARYBDIS_SAFE_RANGE,
  #else
  MOD0 = SAFE_RANGE,
  #endif // !NO_CHARYBDIS_KEYCODES
  MOD1,
  MOD2,
  MOD3,
  ND_GRV,
  ND_QUOT,
  TG_DFT,
  DE_ae,
  DE_oe,
  DE_ss,
  DE_ue,
  DE_eur,
};

// variables for ALT-TABBING with encoder
#ifdef ENCODER_ENABLE
bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;
#endif

// tap-dance struct
typedef struct {
  bool is_press_action;
  int state;
} tap;

//Define a type for as many tap dance states as you need
enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5, //send two single taps
  TRIPLE_TAP = 6,
  TRIPLE_HOLD = 7
};


//Tap dance enums
enum {
  TD_CTL = 0,
  TDM_CMD,
  TDM_OPT,
};

//Function associated with all tap dances
int cur_dance (qk_tap_dance_state_t *state);

//Functions associated with individual tap dances
void ctl_finished (qk_tap_dance_state_t *state, void *user_data);
void ctl_reset (qk_tap_dance_state_t *state, void *user_data);
void mac_cmd_finished (qk_tap_dance_state_t *state, void *user_data);
void mac_cmd_reset (qk_tap_dance_state_t *state, void *user_data);
void mac_opt_finished (qk_tap_dance_state_t *state, void *user_data);
void mac_opt_reset (qk_tap_dance_state_t *state, void *user_data);


/* -------------------------------------------------------------------------- */
/*                                  TAPDANCE                                  */
/* -------------------------------------------------------------------------- */


/* --------------------------------- GLOBAL --------------------------------- */

//Determine the current tap dance state
int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed)  return SINGLE_TAP;
    //key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
    else return SINGLE_HOLD;
  }
  else if (state->count == 2) {
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  if (state->count == 3) {
    if (state->interrupted || !state->pressed)  return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return 8; //magic number. At some point this method will expand to work for more presses
}

//Associate our tap dance keys with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_CTL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ctl_finished, ctl_reset),
  [TDM_CMD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, mac_cmd_finished, mac_cmd_reset),
  [TDM_OPT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, mac_opt_finished, mac_opt_reset)
};

/* --------------------------------- TD_CTL --------------------------------- */

//Initialize tap structure associated with tap dance key
static tap ctl_tap_state = {
  .is_press_action = true,
  .state = 0
};

//Functions that control what our tap dance key does
void ctl_finished (qk_tap_dance_state_t *state, void *user_data) {
  ctl_tap_state.state = cur_dance(state);
  switch (ctl_tap_state.state) {
    case SINGLE_TAP:
        set_oneshot_mods(MOD_LCTL);
        break;
    case SINGLE_HOLD:
        register_code(KC_LCTL);
        break;
    case DOUBLE_TAP:
    case DOUBLE_HOLD:
        register_code(KC_LCTL);
        register_code(KC_LSFT);
        break;
    case TRIPLE_TAP:
    case TRIPLE_HOLD:
        register_code(KC_LCTL);
        register_code(KC_LALT);
        break;
  }
}

void ctl_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (ctl_tap_state.state) {
    case SINGLE_TAP:
        break;
    case SINGLE_HOLD:
        unregister_code(KC_LCTL);
        break;
    case DOUBLE_TAP:
    case DOUBLE_HOLD:
        unregister_code(KC_LCTL);
        unregister_code(KC_LSFT);
        break;
    case TRIPLE_TAP:
    case TRIPLE_HOLD:
        unregister_code(KC_LCTL);
        unregister_code(KC_LALT);
        break;
    }
  ctl_tap_state.state = 0;
}


/* -------------------------------- TDM_CMD --------------------------------- */

//Initialize tap structure associated with tap dance key
static tap mac_cmd_tap_state = {
  .is_press_action = true,
  .state = 0
};

//Functions that control what our tap dance key does
void mac_cmd_finished (qk_tap_dance_state_t *state, void *user_data) {
  mac_cmd_tap_state.state = cur_dance(state);
  switch (mac_cmd_tap_state.state) {
    case SINGLE_TAP:
    case SINGLE_HOLD:
        register_code(KC_LCMD);
        break;
    case DOUBLE_TAP:
    case DOUBLE_HOLD:
        register_code(KC_LSFT);
        register_code(KC_LCMD);
        break;
    case TRIPLE_TAP:
    case TRIPLE_HOLD:
         register_code(KC_LOPT);
         register_code(KC_LCMD);
         break;
  }
}

void mac_cmd_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (mac_cmd_tap_state.state) {
    case SINGLE_TAP:
    case SINGLE_HOLD:
        unregister_code(KC_LCMD);
        break;
    case DOUBLE_TAP:
    case DOUBLE_HOLD:
        unregister_code(KC_LSFT);
        unregister_code(KC_LCMD);
        break;
    case TRIPLE_TAP:
    case TRIPLE_HOLD:
        unregister_code(KC_LOPT);
        unregister_code(KC_LCMD);
        break;
    }
  mac_cmd_tap_state.state = 0;
}

/* -------------------------------- TDM_OPT -------------------------------- */

//Initialize tap structure associated with tap dance key
static tap mac_opt_tap_state = {
  .is_press_action = true,
  .state = 0
};

//Functions that control what our tap dance key does
void mac_opt_finished (qk_tap_dance_state_t *state, void *user_data) {
  mac_opt_tap_state.state = cur_dance(state);
  switch (mac_opt_tap_state.state) {
    case SINGLE_TAP:
    case SINGLE_HOLD:
        register_code(KC_ROPT);
        break;
    case DOUBLE_TAP:
    case DOUBLE_HOLD:
        register_code(KC_LSFT);
        register_code(KC_ROPT);
        break;
    case TRIPLE_TAP:
    case TRIPLE_HOLD:
        register_code(KC_ROPT);
        register_code(KC_LCTL);
        break;
  }
}

void mac_opt_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (mac_opt_tap_state.state) {
    case SINGLE_TAP:
    case SINGLE_HOLD:
        unregister_code(KC_ROPT);
        break;
    case DOUBLE_TAP:
    case DOUBLE_HOLD:
        unregister_code(KC_LSFT);
        unregister_code(KC_ROPT);
        break;
    case TRIPLE_TAP:
    case TRIPLE_HOLD:
         unregister_code(KC_ROPT);
         unregister_code(KC_LCTL);
         break;
    }
  mac_opt_tap_state.state = 0;
}

/* -------------------------------------------------------------------------- */
/*                                INIT/WAKEUP                                 */
/* -------------------------------------------------------------------------- */


void suspend_wakeup_init_kb(void)
{
  // re-enable rgb matrix on wakeup
     #ifdef RGB_MATRIX_ENABLE
          rgb_matrix_set_suspend_state(false);
     #endif
}

void pointing_device_init_user(void) {
    set_auto_mouse_layer(_MOUSE); // only required if AUTO_MOUSE_DEFAULT_LAYER is not set to index of <mouse_layer>
    set_auto_mouse_enable(true);         // always required before the auto mouse feature will work
}



// sync layer_state and default_layer_state (from EEPORM) on init
void matrix_init_user(void) {
  layer_state_set(default_layer_state);
}

/* -------------------------------------------------------------------------- */
/*                                  SHUTDOWN                                  */
/* -------------------------------------------------------------------------- */
void suspend_power_down_kb(void)
{
     #ifdef RGB_MATRIX_ENABLE
          rgb_matrix_set_suspend_state(true);
     #endif
}

/* -------------------------------------------------------------------------- */
/*                                 USER INPUT                                 */
/* -------------------------------------------------------------------------- */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_NO:
      /* Always cancel one-shot layer when another key gets pressed */
      if (record->event.pressed && is_oneshot_layer_active())
      clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
      return true;
    case MOD0:
      if (record->event.pressed) {
        set_single_persistent_default_layer(0);
      }
      return false;
      break;

    // Toggle default layers between _COLEMAK and _MAC
    case TG_DFT:
      if (record->event.pressed) {
        if ( IS_LAYER_OFF(_MAC)) {
          layer_on(_MAC);
          set_single_persistent_default_layer(_MAC);
        }
        else if (IS_LAYER_ON(_MAC)) {
          layer_off(_MAC);
          set_single_persistent_default_layer(0);
        }
      }
      return false;
      break;

    // Tap Space after international layout dead keys, to use them like regular keys
    case ND_GRV:
      if (record->event.pressed) {
        tap_code(KC_GRV);
        tap_code_nomod(KC_SPC);
      } else {
        //
      }
      return false;
      break;
    case ND_QUOT:
      if (record->event.pressed) {
        tap_code(KC_QUOT);
        tap_code_nomod(KC_SPC);
      } else {
        //
      }
      return false;
      break;
    case KC_6:
      if (record->event.pressed) {
        if (get_mods() & MOD_MASK_SHIFT) { //send space after keycode if SHIFT is pressed, to avoid dead key for ^
            tap_code(KC_6);
            tap_code_nomod(KC_SPC);
        } else {
            tap_code(KC_6);
        }
      } else {
        //
      }
      return false;
      break;
    case DE_ae:
      if (record->event.pressed) {
        if (IS_LAYER_ON(_MAC)) {
          tap_umlaut_mac(KC_A);
        } else {
          tap_code16(RALT(KC_Q));
        }
      }
      return false;
      break;
    case DE_oe:
      if (record->event.pressed) {
        if (IS_LAYER_ON(_MAC)) {
          tap_umlaut_mac(KC_O);
        } else {
          tap_code16(RALT(KC_P));
        }
      }
      return false;
      break;
    case DE_ue:
      if (record->event.pressed) {
        if (IS_LAYER_ON(_MAC)) {
          tap_umlaut_mac(KC_U);
        } else {
          tap_code16(RALT(KC_Y));
        }
      }
      return false;
      break;
    case DE_ss:
      if (record->event.pressed) {
        tap_code16(RALT(KC_S));
      }
      return false;
      break;
    case DE_eur:
      if (record->event.pressed) {
        if (IS_LAYER_ON(_MAC)) {
          tap_code16(LSFT(RALT(KC_2)));
        } else {
        tap_code16(RALT(KC_5));
        }
      }
      return false;
      break;
    }
  return true;
}


