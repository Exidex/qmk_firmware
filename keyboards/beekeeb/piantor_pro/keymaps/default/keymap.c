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

const uint16_t PROGMEM combo_cut[] = {KC_E, KC_R, COMBO_END};
const uint16_t PROGMEM combo_copy[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM combo_paste[] = {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM copy_undo[] = {KC_W, KC_E, COMBO_END};
combo_t key_combos[] = {
    COMBO(combo_copy, LCTL(KC_C)),
    COMBO(combo_cut, LCTL(KC_X)),
    COMBO(combo_paste, LCTL(KC_V)),
    COMBO(copy_undo, LCTL(KC_Z)),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEFAULT_LAYER] = LAYOUT_split_3x6_3(
        KC_TAB,      KC_Q,         KC_W,          KC_E,         KC_R,            KC_T,                               KC_Y,    KC_U,         KC_I,         KC_O,         KC_P,            KC_RALT,
        KC_ESCAPE,   LGUI_T(KC_A), LALT_T(KC_S),  LCTL_T(KC_D), LSFT_T(KC_F),    KC_G,                               KC_H,    RSFT_T(KC_J), RCTL_T(KC_K), LALT_T(KC_L), RGUI_T(KC_SCLN), KC_INS,
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
        KC_NO,     KC_EXLM,    KC_AT,     KC_HASH,   KC_DLR,    KC_PERC,                         KC_CIRC,   KC_AMPR,  KC_ASTR,    KC_UNDS,    KC_PLUS,   KC_NO,
        KC_NO,     KC_GRV,     KC_TILDE,  KC_LBRC,   KC_RBRC,   KC_BSLS,                         KC_QUOT,   KC_LPRN,  KC_RPRN,    KC_EQL,     KC_MINUS,  KC_NO,
        KC_NO,     KC_NO,      KC_NO,     KC_LT,     KC_GT,     KC_PIPE,                         KC_DQUO,   KC_LCBR,  KC_RCBR,    KC_NO,      KC_NO,     KC_NO,
                                                           KC_NO, KC_NO, KC_NO,           KC_NO, KC_NO, MO(FN_LAYER)
    ),

    [NUM_LAYER] = LAYOUT_split_3x6_3(
        KC_AUDIO_MUTE,        KC_NO,    KC_NO,    KC_NO,    KC_MEDIA_NEXT_TRACK,    KC_AUDIO_VOL_UP,                              KC_NO,    KC_7,    KC_8,    KC_9,    KC_NO,    KC_NO,
        KC_MEDIA_STOP,        KC_NO,    KC_NO,    KC_NO,    KC_MEDIA_PREV_TRACK,    KC_AUDIO_VOL_DOWN,                            KC_0,     KC_4,    KC_5,    KC_6,    KC_NO,    KC_NO,
        KC_MEDIA_PLAY_PAUSE,  KC_NO,    KC_NO,    KC_NO,    KC_NO,                  KC_NO,                                        KC_NO,    KC_1,    KC_2,    KC_3,    KC_NO,    KC_NO,
                                                                                   MO(FN_LAYER), KC_NO, KC_NO,               KC_NO, KC_NO, KC_NO
    ),

    [FN_LAYER] = LAYOUT_split_3x6_3(
        KC_NO,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,                               KC_F12,    KC_F7,    KC_F8,    KC_F9,    KC_NO,    QK_BOOT,
        KC_NO,  KC_LGUI,  KC_LALT,  KC_LCTL,  KC_LSFT,  KC_NO,                               KC_F11,    KC_F4,    KC_F5,    KC_F6,    KC_NO,    KC_NO,
        KC_NO,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,                               KC_F10,    KC_F1,    KC_F2,    KC_F3,    KC_NO,    KC_NO,
                                                   KC_NO, KC_NO, KC_NO,            KC_NO, KC_NO, KC_NO
    ),

};
