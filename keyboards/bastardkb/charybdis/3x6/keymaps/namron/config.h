//number of times a modifier has to be pressed to toggle a layer
#define TAPPING_TOGGLE 2

//timeout for tap dance
#define TAPPING_TERM 150

//Time (in ms) before the one shot key is released
#define ONESHOT_TIMEOUT 2000
//Tapping this number of times holds the key until tapped once again
#define ONESHOT_TAP_TOGGLE 3

// Auto-mouse-layer https://github.com/qmk/qmk_firmware/pull/17962
#define POINTING_DEVICE_AUTO_MOUSE_ENABLE

//natural scrolling
#define CHARYBDIS_DRAGSCROLL_REVERSE_Y

#define MOUSE_EXTENDED_REPORT


#undef RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 400U

// RGB Matrix

#undef RGB_MATRIX_MAXIMUM_BRIGHTNESS
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 100
// #undef RGB_MATRIX_STARTUP_MODE
// #define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_BREATHING
// #undef RGB_MATRIX_STARTUP_HSV
// #define RGB_MATRIX_STARTUP_HSV

// sync layer state for layer indication
#define SPLIT_LAYER_STATE_ENABLE
// #define SPLIT_TRANSPORT_MIRROR
