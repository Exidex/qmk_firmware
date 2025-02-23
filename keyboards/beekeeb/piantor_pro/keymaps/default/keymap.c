#include "info_config.h" // technically not required, but clion produces nice highlights when it is present

#include QMK_KEYBOARD_H

enum layers {
    DEFAULT_LAYER,
    NAV_LAYER,
    NAV_LAYER_MACOS,
    SYMBOL_LAYER,
    FN_LAYER,
    MOD_MARKER_LAYER,
    MOD_LAYER_LEFT,
    MOD_LAYER_RIGHT,
    MOD_LAYER_MACOS_LEFT,
    MOD_LAYER_MACOS_RIGHT,
};

enum keycodes {
    // Custom oneshot layer implementation.
    OSL_MOD_LAYER = SAFE_RANGE,

    // Custom oneshot mods implementation.
    OSM_SHFT,
    OSM_CTRL,
    OSM_ALT,
    OSM_GUI,

    MACOS_ENABLE,
    MACOS_DISABLE,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEFAULT_LAYER] = LAYOUT_split_3x6_3(
        KC_TAB,      KC_Q,         KC_W,          KC_E,         KC_R,            KC_T,                               KC_Y,    KC_U,         KC_I,         KC_O,         KC_P,            KC_RALT,
        KC_ESCAPE,   KC_A,         KC_S,          KC_D,         KC_F,            KC_G,                               KC_H,    KC_J,         KC_K,         KC_L,         KC_SCLN,         XXXXXXX,
        XXXXXXX,     KC_Z,         KC_X,          KC_C,         KC_V,            KC_B,                               KC_N,    KC_M,         KC_COMM,      KC_DOT,       KC_SLSH,         XXXXXXX,

        OSL_MOD_LAYER, MO(NAV_LAYER), KC_SPC,                 KC_BSPC, MO(SYMBOL_LAYER), KC_ENT
    ),

    [NAV_LAYER] = LAYOUT_split_3x6_3(
        XXXXXXX,  KC_INS,       C(S(KC_TAB)),    KC_UP,      C(KC_TAB),   KC_PGUP,                               XXXXXXX,    XXXXXXX,       XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
        XXXXXXX,  KC_HOME,      KC_LEFT,         KC_DOWN,    KC_RIGHT,    KC_END,                                XXXXXXX,    XXXXXXX,       XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
        XXXXXXX,  XXXXXXX,      S(KC_TAB),       KC_APP,     KC_TAB,      KC_PGDN,                               XXXXXXX,    XXXXXXX,       XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,

        XXXXXXX, XXXXXXX, XXXXXXX,                XXXXXXX, MO(FN_LAYER), XXXXXXX
    ),

    [NAV_LAYER_MACOS] = LAYOUT_split_3x6_3(
        _______,    _______,    _______,    _______,        _______,      _______,            _______,    _______,    _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,        _______,      _______,            _______,    _______,    _______,    _______,    _______,    _______,
        _______,    _______,    _______,    G(KC_ENTER),    _______,      _______,            _______,    _______,    _______,    _______,    _______,    _______,

        _______, _______, _______,                _______, _______, _______
    ),

    [SYMBOL_LAYER] = LAYOUT_split_3x6_3(
        KC_EXLM,    KC_AT,       KC_7,    KC_8,    KC_9,    KC_AMPR,                             KC_GRV,    KC_LPRN,  KC_RPRN,    KC_LCBR,    KC_RCBR,    KC_PIPE,
        KC_HASH,    KC_DLR,      KC_4,    KC_5,    KC_6,    KC_0,                                KC_QUOT,   KC_LBRC,  KC_RBRC,    KC_LT,      KC_GT,      KC_TILDE,
        KC_PERC,    KC_CIRC,     KC_1,    KC_2,    KC_3,    KC_ASTR,                             KC_DQUO,   KC_MINUS, KC_PLUS,    KC_EQL,     KC_BSLS,    KC_UNDS,

        OSL_MOD_LAYER,  MO(FN_LAYER), XXXXXXX,                XXXXXXX, XXXXXXX, XXXXXXX
    ),

    [FN_LAYER] = LAYOUT_split_3x6_3(
        XXXXXXX,   XXXXXXX,     KC_F7,    KC_F8,    KC_F9,    KC_F12,               XXXXXXX,     XXXXXXX,      XXXXXXX,      XXXXXXX,    XXXXXXX,          QK_BOOT,
        XXXXXXX,   XXXXXXX,     KC_F4,    KC_F5,    KC_F6,    KC_F11,               XXXXXXX,     XXXXXXX,      XXXXXXX,      XXXXXXX,    XXXXXXX,          XXXXXXX,
        XXXXXXX,   XXXXXXX,     KC_F1,    KC_F2,    KC_F3,    KC_F10,               XXXXXXX,     XXXXXXX,      XXXXXXX,      XXXXXXX,    MACOS_DISABLE,    MACOS_ENABLE,

        XXXXXXX, XXXXXXX, XXXXXXX,                XXXXXXX, XXXXXXX, XXXXXXX
    ),

    [MOD_MARKER_LAYER] = LAYOUT_split_3x6_3(
        _______,    _______,    _______,    _______,    _______,      _______,            _______,    _______,    _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,    _______,     _______,            _______,    _______,    _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,    _______,      _______,            _______,    _______,    _______,    _______,    _______,    _______,

        OSL_MOD_LAYER, _______, _______,                _______, _______, _______
    ),

    [MOD_LAYER_LEFT] = LAYOUT_split_3x6_3(
        _______,    _______,    _______,    _______,    _______,      _______,            _______,    _______,    _______,    _______,    _______,    _______,
        _______,    OSM_GUI,    OSM_ALT,    OSM_CTRL,   OSM_SHFT,     _______,            _______,    _______,    _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,    _______,      _______,            _______,    _______,    _______,    _______,    _______,    _______,

        _______, _______, _______,                _______, _______, _______
    ),

    [MOD_LAYER_RIGHT] = LAYOUT_split_3x6_3(
        _______,    _______,    _______,    _______,    _______,      _______,            _______,    _______,    _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,    _______,      _______,            _______,    OSM_SHFT,   OSM_CTRL,   OSM_ALT,    OSM_GUI,    _______,
        _______,    _______,    _______,    _______,    _______,      _______,            _______,    _______,    _______,    _______,    _______,    _______,

        _______, _______, _______,                _______, _______, _______
    ),

    [MOD_LAYER_MACOS_LEFT] = LAYOUT_split_3x6_3(
        _______,    _______,    _______,    _______,    _______,      _______,            _______,    _______,    _______,    _______,    _______,    _______,
        _______,    OSM_CTRL,   OSM_ALT,    OSM_GUI,    OSM_SHFT,     _______,            _______,    _______,    _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,    _______,      _______,            _______,    _______,    _______,    _______,    _______,    _______,

        _______, _______, _______,                _______, _______, _______
    ),

    [MOD_LAYER_MACOS_RIGHT] = LAYOUT_split_3x6_3(
        _______,    _______,    _______,    _______,    _______,      _______,            _______,    _______,    _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,    _______,      _______,            _______,    OSM_SHFT,   OSM_GUI,    OSM_ALT,    OSM_CTRL,    _______,
        _______,    _______,    _______,    _______,    _______,      _______,            _______,    _______,    _______,    _______,    _______,    _______,

        _______, _______, _______,                _______, _______, _______
    ),
};

// ================

//void keyboard_post_init_user(void) {
//    debug_enable   = true;
//    debug_keyboard = true;
//}

// ================ mostly callum's oneshot mods

typedef enum {
    osl_up_unqueued, // default, waiting for layer to be pressed
    osl_up_queued, // layer pressed and released without pressing mod key, next modifier press will have layer enabled, on all mod release layer will be disabled
    osl_up_pending_used, // layer was pressed but released when some mods were still held, on all mod release layer will be disabled
    osl_down_unused, // layer pressed and held, all mod presses will have layer enabled, until all mods are released
    osl_down_pending_used, // layer pressed and held, some mods are still pressed
    osl_down_used, // mods were pressed but layer is still held, on layer release layer will be disabled
} oneshot_layer_state;

typedef enum {
    osm_up_unqueued, // default, waiting for mod to be pressed
    osm_down_unused, // mod pressed and held, all other presses will be with this modifier enabled, until mod released
    osm_down_used, // other key pressed while mod is held, on mod release modifier will be disabled
    osm_up_queued, // mod pressed and released without pressing other key, next press will have modifier enabled
    osm_up_queued_with_layer, // other key pressed abd released while layer and mod are active, next presses will have modifier enabled until layer is released
} oneshot_mod_state;

oneshot_mod_state osm_shift_state = osm_up_unqueued;
oneshot_mod_state osm_ctrl_state = osm_up_unqueued;
oneshot_mod_state osm_alt_state = osm_up_unqueued;
oneshot_mod_state osm_gui_state = osm_up_unqueued;

bool macos_modifiers = false;

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
        case MO(NAV_LAYER):
        case MO(FN_LAYER):
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

void update_oneshot_mod(
    oneshot_layer_state *layer_state,
    oneshot_mod_state *mod_state,
    uint16_t mod,
    uint16_t trigger,
    uint16_t keycode,
    keyrecord_t *record
) {
    if (keycode == trigger) {
        if (record->event.pressed) {
            // Trigger keydown
            if (*mod_state == osm_up_unqueued) {
                register_code(mod);
            }
            *mod_state = osm_down_unused;
        } else {
            // Trigger keyup
            switch (*mod_state) {
                case osm_down_unused:
                    // If we didn't use the mod while trigger was held, queue it.
                    *mod_state = osm_up_queued;
                    break;
                case osm_down_used:
                    // If we did use the mod while trigger was held, unregister it.
                    *mod_state = osm_up_unqueued;
                    unregister_code(mod);
//                    uprintf("0x%04X unregister_code up trigger\n", keycode);
                    break;
                default:
                    break;
            }
        }
    } else {
        if (record->event.pressed) {
            if (is_oneshot_cancel_key(keycode) && *mod_state != osm_up_unqueued) {
                // Cancel oneshot on designated cancel keydown.
                *mod_state = osm_up_unqueued;
                unregister_code(mod);
//                uprintf("0x%04X unregister_code down non-trigger\n", keycode);
            }
        } else {
            if (!is_oneshot_ignored_key(keycode)) {
                // On non-ignored keyup, mark the oneshot as used.
                switch (*mod_state) {
                    case osm_down_unused:
                        *mod_state = osm_down_used;
                        break;
                    case osm_up_queued:
                        switch (*layer_state) {
                            case osl_up_pending_used: // because some other mod is still pressed
                            case osl_down_unused:
                            case osl_down_pending_used:
                            case osl_down_used:
                                *mod_state = osm_up_queued_with_layer;
                                break;
                            default:
                                *mod_state = osm_up_unqueued;
                                unregister_code(mod);
                                break;
                        }
                        break;
                    default:
                        break;
                }
            }
        }
    }
}

// ================ my oneshot layers

oneshot_layer_state osl_mod_state = osl_up_unqueued;

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
    oneshot_layer_state *layer_state,
    oneshot_mod_state *shift_state,
    oneshot_mod_state *ctrl_state,
    oneshot_mod_state *alt_state,
    oneshot_mod_state *gui_state,
    uint16_t trigger,
    uint16_t layer,
    uint16_t keycode,
    keyrecord_t *record
) {
    if (keycode == trigger) {
        if (record->event.pressed) {
            if (*layer_state == osl_up_unqueued) {
                layer_on(layer);
            }
            *layer_state = osl_down_unused;
        } else {
            switch (*layer_state) {
                case osl_down_unused:
                    *layer_state = osl_up_queued;
                    break;
                case osl_down_used:
                    *layer_state = osl_up_unqueued;
                    layer_off(layer);

                    {
                        if (*shift_state == osm_up_queued_with_layer) {
                            *shift_state = osm_up_unqueued;
                            unregister_code(KC_LSFT);
                        }
                        if (*ctrl_state == osm_up_queued_with_layer) {
                            *ctrl_state = osm_up_unqueued;
                            unregister_code(KC_LCTL);
                        }
                        if (*alt_state == osm_up_queued_with_layer) {
                            *alt_state = osm_up_unqueued;
                            unregister_code(KC_LALT);
                        }
                        if (*gui_state == osm_up_queued_with_layer) {
                            *gui_state = osm_up_unqueued;
                            unregister_code(KC_LGUI);
                        }
                    }

                    break;
                case osl_down_pending_used:
                    *layer_state = osl_up_pending_used;
                    break;
                default:
                    break;
            }
        }
    } else {
        if (record->event.pressed) {
            if (is_oneshot_mod_key(keycode)) {
                pressed_one_shot_mods |= CUSTOM_ONE_SHOT_MOD_GET_MODS(keycode);
            }
        } else {
            if (is_oneshot_mod_key(keycode)) {
                pressed_one_shot_mods &= CUSTOM_ONE_SHOT_MOD_GET_MODS(~(CUSTOM_ONE_SHOT_MOD_GET_MODS(keycode)));
            }

            switch (*layer_state) {
                case osl_down_pending_used:
                case osl_down_unused:
                    if (is_oneshot_mod_key(keycode)) {
                        if (pressed_one_shot_mods) {
                            *layer_state = osl_down_pending_used;
                        } else {
                            *layer_state = osl_down_used;
                            layer_off(layer);
                        }
                    }
                    break;
                case osl_up_queued:
                case osl_up_pending_used:
                    if (is_oneshot_mod_key(keycode)) {
                        if (pressed_one_shot_mods) {
                            *layer_state = osl_up_pending_used;
                        } else {
                            *layer_state = osl_up_unqueued;
                            layer_off(layer);
                        }
                    }
                    break;
                default:
                    break;
            }
        }
    }
}

// ==============

//const char* oneshot_layer_state_string(oneshot_layer_state value) {
//    switch (value) {
//        case osl_up_unqueued: return "osl_up_unqueued";
//        case osl_up_queued: return "osl_up_queued";
//        case osl_up_pending_used: return "osl_up_pending_used";
//        case osl_down_unused: return "osl_down_unused";
//        case osl_down_pending_used: return "osl_down_pending_used";
//        case osl_down_used: return "osl_down_used";
//        default: return "-----";
//    }
//}
//
//const char* oneshot_mod_state_string(oneshot_mod_state value) {
//    switch (value) {
//        case osm_up_unqueued: return "osm_up_unqueued";
//        case osm_down_unused: return "osm_down_unused";
//        case osm_down_used: return "osm_down_used";
//        case osm_up_queued: return "osm_up_queued";
//        case osm_up_queued_with_layer: return "osm_up_queued_with_layer";
//        default: return "-----";
//    }
//}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//    uprintf("\n");
//    uprintf("\n");
//
//    uprintf("%s %s %s %s %s \n", oneshot_layer_state_string(osl_mod_state), oneshot_mod_state_string(osm_shift_state), oneshot_mod_state_string(osm_ctrl_state), oneshot_mod_state_string(osm_alt_state), oneshot_mod_state_string(osm_gui_state));

    if (keycode == MACOS_ENABLE && record->event.pressed) {
        macos_modifiers = true;
    }

    if (keycode == MACOS_DISABLE && record->event.pressed) {
        macos_modifiers = false;
    }

    update_oneshot_mod(
        &osl_mod_state,
        &osm_shift_state,
        KC_LSFT,
        OSM_SHFT,
        keycode,
        record
    );

    update_oneshot_mod(
        &osl_mod_state,
        &osm_ctrl_state,
        KC_LCTL,
        OSM_CTRL,
        keycode,
        record
    );

    update_oneshot_mod(
        &osl_mod_state,
        &osm_alt_state,
        KC_LALT,
        OSM_ALT,
        keycode,
        record
    );

    update_oneshot_mod(
        &osl_mod_state,
        &osm_gui_state,
        KC_LGUI,
        OSM_GUI,
        keycode,
        record
    );


    update_oneshot_layer(
        &osl_mod_state,
        &osm_shift_state,
        &osm_ctrl_state,
        &osm_alt_state,
        &osm_gui_state,
        OSL_MOD_LAYER,
        MOD_MARKER_LAYER,
        keycode,
        record
    );

//    uprintf("%s %s %s %s %s \n", oneshot_layer_state_string(osl_mod_state), oneshot_mod_state_string(osm_shift_state), oneshot_mod_state_string(osm_ctrl_state), oneshot_mod_state_string(osm_alt_state), oneshot_mod_state_string(osm_gui_state));

    return true;
}

layer_state_t set_layer_state(layer_state_t state, bool check, uint8_t layer) {
    layer_state_t mask = (layer_state_t) 1 << layer;
    return check ? (state | mask) : (state & ~mask);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    layer_state_t new_state = state;

    bool right = IS_LAYER_ON_STATE(state, MOD_MARKER_LAYER) || IS_LAYER_ON_STATE(state, FN_LAYER) || IS_LAYER_ON_STATE(state, NAV_LAYER);
    bool left = IS_LAYER_ON_STATE(state, MOD_MARKER_LAYER);

    if (macos_modifiers) {
        // reset
        new_state = set_layer_state(new_state, false, MOD_LAYER_RIGHT);
        new_state = set_layer_state(new_state, false, MOD_LAYER_LEFT);

        new_state = set_layer_state(new_state, right, MOD_LAYER_MACOS_RIGHT);
        new_state = set_layer_state(new_state, left, MOD_LAYER_MACOS_LEFT);
    } else {
        // reset
        new_state = set_layer_state(new_state, false, MOD_LAYER_MACOS_RIGHT);
        new_state = set_layer_state(new_state, false, MOD_LAYER_MACOS_LEFT);

        new_state = set_layer_state(new_state, right, MOD_LAYER_RIGHT);
        new_state = set_layer_state(new_state, left, MOD_LAYER_LEFT);
    }

    if (macos_modifiers) {
        bool nav  = IS_LAYER_ON_STATE(state, NAV_LAYER);
        new_state = set_layer_state(new_state, nav, NAV_LAYER_MACOS);
    } else {
        new_state = set_layer_state(new_state, false, NAV_LAYER_MACOS);
    }

    return new_state;
}
