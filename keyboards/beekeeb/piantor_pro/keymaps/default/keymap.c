#include "info_config.h" // technically not required, but clion produces nice highlights when it is present

#include QMK_KEYBOARD_H

enum layers {
    DEFAULT_LAYER,
    NAV_LAYER,
    SYMBOL_LAYER,
    FN_LAYER,
    MOD_LAYER,
};

enum keycodes {
    // Custom oneshot layer implementation.
    OSL_MOD_LAYER = SAFE_RANGE,

    // Custom oneshot mods implementation.
    OSM_SHFT,
    OSM_CTRL,
    OSM_ALT,
    OSM_GUI,
};


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

        OSL_MOD_LAYER,   MO(NAV_LAYER),   BSPC_OR_DEL,                 KC_SPC, MO(SYMBOL_LAYER), KC_ENT
    ),

    [NAV_LAYER] = LAYOUT_split_3x6_3(
        XXXXXXX,  XXXXXXX,      C(S(KC_TAB)),    KC_UP,      C(KC_TAB),   KC_PGUP,                               XXXXXXX,    XXXXXXX,       XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
        XXXXXXX,  KC_HOME,      KC_LEFT,         KC_DOWN,    KC_RIGHT,    KC_END,                                XXXXXXX,    KC_RSFT,       KC_RCTL,    KC_LALT,    KC_RGUI,    XXXXXXX,
        XXXXXXX,  XXXXXXX,      S(KC_TAB),       KC_APP,     KC_TAB,      KC_PGDN,                               XXXXXXX,    XXXXXXX,       XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,

        XXXXXXX, XXXXXXX, XXXXXXX,                XXXXXXX, MO(FN_LAYER), KC_LEFT_GUI
    ),

    [SYMBOL_LAYER] = LAYOUT_split_3x6_3(
        KC_EXLM,    KC_AT,       KC_7,    KC_8,    KC_9,    KC_AMPR,                             KC_GRV,    KC_LPRN,  KC_RPRN,    KC_LCBR,    KC_RCBR,    KC_PIPE,
        KC_HASH,    KC_DLR,      KC_4,    KC_5,    KC_6,    KC_0,                                KC_QUOT,   KC_LBRC,  KC_RBRC,    KC_LT,      KC_GT,      KC_TILDE,
        KC_PERC,    KC_CIRC,     KC_1,    KC_2,    KC_3,    KC_ASTR,                             KC_DQUO,   KC_UNDS,  KC_PLUS,    KC_EQL,     KC_BSLS,    KC_MINUS,

        XXXXXXX,  MO(FN_LAYER), XXXXXXX,                XXXXXXX, XXXXXXX, XXXXXXX
    ),

    [FN_LAYER] = LAYOUT_split_3x6_3(
        XXXXXXX,            KC_MEDIA_STOP,            XXXXXXX,      XXXXXXX,      KC_MEDIA_PREV_TRACK,    KC_MEDIA_NEXT_TRACK,          KC_F12,    KC_F7,    KC_F8,    KC_F9,    XXXXXXX,    QK_BOOT,
        KC_AUDIO_MUTE,      OSM_GUI,                  OSM_ALT,      OSM_CTRL,     OSM_SHFT,               XXXXXXX,                      KC_F11,    KC_F4,    KC_F5,    KC_F6,    XXXXXXX,    XXXXXXX,
        XXXXXXX,            KC_MEDIA_PLAY_PAUSE,      XXXXXXX,      XXXXXXX,      KC_AUDIO_VOL_DOWN,      KC_AUDIO_VOL_UP,              KC_F10,    KC_F1,    KC_F2,    KC_F3,    XXXXXXX,    XXXXXXX,

        XXXXXXX, XXXXXXX, XXXXXXX,                XXXXXXX, XXXXXXX, XXXXXXX
    ),

    [MOD_LAYER] = LAYOUT_split_3x6_3(
        _______,    _______,    _______,    _______,    _______,    _______,            _______,    _______,    _______,    _______,    _______,    _______,
        _______,    OSM_GUI,    OSM_ALT,    OSM_CTRL,   OSM_SHFT,   _______,            _______,    OSM_SHFT,   OSM_CTRL,   OSM_ALT,    OSM_GUI,    _______,
        _______,    _______,    _______,    _______,    _______,    _______,            _______,    _______,    _______,    _______,    _______,    _______,

        OSL_MOD_LAYER, _______, _______,                _______, _______, _______
    ),
};

// ================

//void keyboard_post_init_user(void) {
//    debug_enable   = true;
//    debug_keyboard = true;
//}

// ================ mostly callum's oneshot mods

typedef enum {
    osm_up_unqueued,
    osm_up_queued,
    osm_down_unused,
    osm_down_used,
} oneshot_mod_state;

oneshot_mod_state osm_shift_state = osm_up_unqueued;
oneshot_mod_state osm_ctrl_state = osm_up_unqueued;
oneshot_mod_state osm_alt_state = osm_up_unqueued;
oneshot_mod_state osm_gui_state = osm_up_unqueued;

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
        case OSL_MOD_LAYER: // cancel on double tap
//        case MO(SYMBOL_LAYER):
//        case MO(NAV_LAYER):
//        case BSPC_OR_DEL:
//        case KC_SPC:
//        case KC_ENT:
            return true;
        default:
            return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
        case OSL_MOD_LAYER:
        case OSM_SHFT:
        case OSM_CTRL:
        case OSM_ALT:
        case OSM_GUI:
            return true;
        default:
            return false;
    }
}

void update_oneshot(
    oneshot_mod_state *state,
    uint16_t mod,
    uint16_t trigger,
    uint16_t keycode,
    keyrecord_t *record
) {
    if (keycode == trigger) {
        if (record->event.pressed) {
            // Trigger keydown
            if (*state == osm_up_unqueued) {
                register_code(mod);
            }
            *state = osm_down_unused;
        } else {
            // Trigger keyup
            switch (*state) {
                case osm_down_unused:
                    // If we didn't use the mod while trigger was held, queue it.
                    *state = osm_up_queued;
                    break;
                case osm_down_used:
                    // If we did use the mod while trigger was held, unregister it.
                    *state = osm_up_unqueued;
                    unregister_code(mod);
//                    uprintf("0x%04X unregister_code up trigger\n", keycode);
                    break;
                default:
                    break;
            }
        }
    } else {
        if (record->event.pressed) {
            if (is_oneshot_cancel_key(keycode) && *state != osm_up_unqueued) {
                // Cancel oneshot on designated cancel keydown.
                *state = osm_up_unqueued;
                unregister_code(mod);
//                uprintf("0x%04X unregister_code down non-trigger\n", keycode);
            }
        } else {
            if (!is_oneshot_ignored_key(keycode)) {
                // On non-ignored keyup, mark the oneshot as used.
                switch (*state) {
                    case osm_down_unused:
                        *state = osm_down_used;
                        break;
                    case osm_up_queued:
                        *state = osm_up_unqueued;
                        unregister_code(mod);
//                        uprintf("0x%04X unregister_code up non-trigger\n", keycode);
                        break;
                    default:
                        break;
                }
            }
        }
    }
}

// ================ my oneshot layers

typedef enum {
    osl_up,
    osl_down,
} oneshot_layer_state;

oneshot_layer_state osl_sym_state = osl_up;
oneshot_layer_state osl_num_state = osl_up;
oneshot_layer_state osl_fn_state = osl_up;

uint16_t pressed_one_shot_mods = 0;

#define CUSTOM_ONE_SHOT_MOD_GET_MODS(kc) ((kc)&0x1F)

bool is_oneshot_mod_key(uint16_t keycode) {
    switch (keycode) {
        case OSM_SHFT:
        case OSM_CTRL:
        case OSM_ALT:
        case OSM_GUI:
            return true;
        default:
            return false;
    }
}

void update_oneshot_layer(
    oneshot_layer_state *state,
    uint16_t trigger,
    uint16_t layer,
    uint16_t keycode,
    keyrecord_t *record
) {
    if (keycode == trigger) {
        if (record->event.pressed) {
            // enable layer
            layer_on(layer);
            *state = osl_down;
//            uprintf("0x%04X layer_on\n", keycode);
        } else {
            // remember state
            *state = osl_up;
        }
    } else {
        if (record->event.pressed) {
            // remember pressed mods
            if (is_oneshot_mod_key(keycode)) {
                pressed_one_shot_mods |= CUSTOM_ONE_SHOT_MOD_GET_MODS(keycode);
            }
        } else {
            if (IS_LAYER_ON(layer)) {
                if (is_oneshot_mod_key(keycode)) {
                    // if mod
                    // track pressed and released mods
                    pressed_one_shot_mods &= CUSTOM_ONE_SHOT_MOD_GET_MODS(~(CUSTOM_ONE_SHOT_MOD_GET_MODS(keycode)));

                    if (pressed_one_shot_mods) {
                        // ignore
                    } else {
                        // wait until last (in a chord) mod is release
                        layer_off(layer);
//                        uprintf("0x%04X layer_off mods\n", keycode);
                    }
                } else {
                    // if non-mod, disable layer if key is up
                    if (*state == osl_up) {
                        layer_off(layer);
//                        uprintf("0x%04X layer_off non-mods\n", keycode);
                    }
                }
            }
        }
    }
}

// ==============

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//    uprintf("keycode 0x%04X pressed: %d\n", keycode, record->event.pressed);

    update_oneshot(
        &osm_shift_state,
        KC_LSFT,
        OSM_SHFT,
        keycode,
        record
    );
    update_oneshot(
        &osm_ctrl_state,
        KC_LCTL,
        OSM_CTRL,
        keycode,
        record
    );
    update_oneshot(
        &osm_alt_state,
        KC_LALT,
        OSM_ALT,
        keycode,
        record
    );
    update_oneshot(
        &osm_gui_state,
        KC_LCMD,
        OSM_GUI,
        keycode,
        record
    );

    update_oneshot_layer(
        &osl_sym_state,
        OSL_MOD_LAYER,
        MOD_LAYER,
        keycode,
        record
    );

    return true;
}
