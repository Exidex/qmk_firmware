#include "info_config.h" // technically not required, but clion produces nice highlights when it is present

#include QMK_KEYBOARD_H

#define DEFAULT_LAYER (0)
#define NAV_LAYER (1)
#define SYMBOL_LAYER (2)
#define NUM_LAYER (3)
#define FN_LAYER (4)

#define BSPC_OR_DEL (KC_BSPC) // key code + key override
const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);

const key_override_t **key_overrides = (const key_override_t *[]){
    &delete_key_override,
    NULL // terminate the array
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEFAULT_LAYER] = LAYOUT_split_3x6_3(
        KC_TAB,      KC_Q,         KC_W,          KC_E,         KC_R,            KC_T,                               KC_Y,    KC_U,         KC_I,         KC_O,         KC_P,            KC_RALT,
        KC_ESCAPE,   KC_A,         KC_S,          KC_D,         KC_F,            KC_G,                               KC_H,    KC_J,         KC_K,         KC_L,         KC_SCLN,         KC_INS,
        KC_LSFT,     KC_Z,         KC_X,          KC_C,         KC_V,            KC_B,                               KC_N,    KC_M,         KC_COMM,      KC_DOT,       KC_SLSH,         KC_RSFT,
                                                MO(SYMBOL_LAYER),   MO(NAV_LAYER),   BSPC_OR_DEL,                 KC_SPC, KC_ENT, MO(NUM_LAYER)
    ),

    [NAV_LAYER] = LAYOUT_split_3x6_3(
        KC_NO,  KC_NO,      C(S(KC_TAB)),    KC_UP,      C(KC_TAB),   KC_PGUP,                               KC_NO,    KC_NO,      KC_NO,    KC_NO,    KC_NO,    KC_NO,
        KC_NO,  KC_HOME,    KC_LEFT,         KC_DOWN,    KC_RIGHT,    KC_END,                                KC_NO,    KC_RSFT,    KC_RCTL,  KC_LALT,  KC_RGUI,  KC_NO,
        KC_NO,  KC_NO,      S(KC_TAB),       KC_APP,     KC_TAB,      KC_PGDN,                               KC_NO,    KC_NO,      KC_NO,    KC_NO,    KC_NO,    KC_NO,
                                                                 KC_NO, KC_NO, KC_NO,                KC_NO, KC_LEFT_GUI, KC_NO
    ),

    [SYMBOL_LAYER] = LAYOUT_split_3x6_3(
        KC_NO,     KC_EXLM,         KC_AT,           KC_LBRC,        KC_RBRC,         KC_PERC,                     KC_CIRC,   KC_LPRN,  KC_RPRN,    KC_UNDS,    KC_PLUS,   KC_NO,
        KC_NO,   OSM(MOD_LGUI),   OSM(MOD_LALT),   OSM(MOD_LCTL),  OSM(MOD_LSFT),   KC_BSLS,                     KC_QUOT,   KC_AMPR,  KC_ASTR,    KC_EQL,     KC_MINUS,  KC_NO,
        KC_NO,      KC_HASH,         KC_DLR,          KC_LT,          KC_GT,           KC_PIPE,                     KC_DQUO,   KC_LCBR,  KC_RCBR,    KC_GRV,      KC_TILDE,     KC_NO,
                                                                                 KC_NO, KC_NO, KC_NO,           KC_NO, KC_NO, MO(FN_LAYER)
    ),

    [NUM_LAYER] = LAYOUT_split_3x6_3(
        KC_NO,        KC_NO,    KC_7,    KC_8,    KC_9,    KC_NO,                           KC_NO,    KC_NO,         KC_NO,          KC_NO,          KC_NO,           KC_NO,
        KC_NO,        KC_NO,    KC_4,    KC_5,    KC_6,    KC_0,                            KC_NO,    OSM(MOD_RSFT), OSM(MOD_RCTL),  OSM(MOD_LALT),  OSM(MOD_RGUI),   KC_NO,
        KC_NO,        KC_NO,    KC_1,    KC_2,    KC_3,    KC_NO,                           KC_NO,    KC_NO,         KC_NO,          KC_NO,          KC_NO,           KC_NO,
                                                    MO(FN_LAYER), KC_NO, KC_NO,           KC_NO, KC_NO, KC_NO
    ),

    [FN_LAYER] = LAYOUT_split_3x6_3(
        KC_NO,            KC_MEDIA_STOP,            KC_NO,            KC_NO,           KC_MEDIA_PREV_TRACK,    KC_MEDIA_NEXT_TRACK,          KC_F12,    KC_F7,    KC_F8,    KC_F9,    KC_NO,    QK_BOOT,
        KC_AUDIO_MUTE,    OSM(MOD_LGUI),            OSM(MOD_LALT),    OSM(MOD_LCTL),   OSM(MOD_LSFT),          KC_NO,                        KC_F11,    KC_F4,    KC_F5,    KC_F6,    KC_NO,    KC_NO,
        KC_NO,            KC_MEDIA_PLAY_PAUSE,      KC_NO,            KC_NO,           KC_AUDIO_VOL_DOWN,      KC_AUDIO_VOL_UP,              KC_F10,    KC_F1,    KC_F2,    KC_F3,    KC_NO,    KC_NO,
                                                                                                             KC_NO, KC_NO, KC_NO,            KC_NO, KC_NO, KC_NO
    ),

};
