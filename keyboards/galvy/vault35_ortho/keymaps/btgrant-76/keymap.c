#include QMK_KEYBOARD_H
#include "btgrant-76.h"

#ifdef COMBO_ENABLE
#   include "combos.h"
#endif

/*
TODO
 - verify all includes are needed
 - replace encoder_update_user with ENCODER_MAP
 - verify achordion_chord_keymap

 x replace middle column with trans
*/
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_btgrant(
  //|--------------------------------------------|--------|--------------------------------------------|
                                  ___5BASE_1_L___, KC_MUTE,                             ___5BASE_1_R___,
  //|--------+--------+--------+--------+--------|--------|--------+--------+--------+--------+--------|
                                  ___5BASE_2_L___, RGB_TOG,                             ___5BASE_2_R___,
  //|--------+--------+--------+--------+--------|--------|--------+--------+--------+--------+--------|
                                  ___5BASE_3_L___, RGB_MOD,                             ___5BASE_3_R___,
  //|--------+--------+--------+--------+--------|--------|--------+--------+--------+--------+--------|
                               ___BASE_THUMB_L___, XXXXXXX,        ___BASE_THUMB_R___
                    //|--------+--------+--------+--------+--------+--------+--------|
  ),
  [_NUM] = LAYOUT_btgrant(
  //|--------------------------------------------|--------|--------------------------------------------|
                                   ___5NUM_1_L___, KC_HOME,                              ___5NUM_1_R___,
  //|--------+--------+--------+--------+--------|--------|--------+--------+--------+--------+--------|
                                   ___5NUM_2_L___, _______,                              ___5NUM_2_R___,
  //|--------+--------+--------+--------+--------|--------|--------+--------+--------+--------+--------|
                                   ___5NUM_3_L___, _______,                              ___5NUM_3_R___,
  //|--------+--------+--------+--------+--------|--------|--------+--------+--------+--------+--------|
                                ___NUM_THUMB_L___, _______,         ___NUM_THUMB_R___
                    //|--------+--------+--------+--------+--------+--------+--------|
  ),
  [_SYM] = LAYOUT_btgrant(
  //|--------------------------------------------|--------|--------------------------------------------|
                                   ___5SYM_1_L___, KC_MPLY,                              ___5SYM_1_R___,
  //|--------+--------+--------+--------+--------|--------|--------+--------+--------+--------+--------|
                                   ___5SYM_2_L___, _______,                              ___5SYM_2_R___,
  //|--------+--------+--------+--------+--------|--------|--------+--------+--------+--------+--------|
                                   ___5SYM_3_L___, _______,                              ___5SYM_3_R___,
  //|--------+--------+--------+--------+--------|--------|--------+--------+--------+--------+--------|
                                ___SYM_THUMB_L___, _______,         ___SYM_THUMB_R___
                    //|--------+--------+--------+--------+--------+--------+--------|
  ),
  [_NAV] = LAYOUT_btgrant(
  //|--------------------------------------------|--------|--------------------------------------------|
                                  ___5NAV_1_L___, _______,                             ___5NAV_1_R___,
  //|--------+--------+--------+--------+--------|--------|--------+--------+--------+--------+--------|
                                  ___5NAV_2_L___, _______,                             ___5NAV_2_R___,
  //|--------+--------+--------+--------+--------|--------|--------+--------+--------+--------+--------|
                                  ___5NAV_3_L___, _______,                             ___5NAV_3_R___,
  //|--------+--------+--------+--------+--------|--------|--------+--------+--------+--------+--------|
                               ___NAV_THUMB_L___, _______,          ___NAV_THUMB_R___
                    //|--------+--------+--------+--------+--------+--------+--------|
  ),
  [_FUN] = LAYOUT_btgrant(
  //|--------------------------------------------|--------|--------------------------------------------|
                                  ___5FUN_1_L___, _______,                             ___5FUN_1_R___,
  //|--------+--------+--------+--------+--------|--------|--------+--------+--------+--------+--------|
                                  ___5FUN_2_L___, _______,                             ___5FUN_2_R___,
  //|--------+--------+--------+--------+--------|--------|--------+--------+--------+--------+--------|
                                  ___5FUN_3_L___, _______,                             ___5FUN_3_R___,
  //|--------+--------+--------+--------+--------|--------|--------+--------+--------+--------+--------|
                               ___FUN_THUMB_L___, _______,          ___FUN_THUMB_R___
                    //|--------+--------+--------+--------+--------+--------+--------|
  ),
  [_MSE] = LAYOUT_btgrant(
  //|--------------------------------------------|--------|--------------------------------------------|
                                  ___5MSE_1_L___, _______,                             ___5MSE_1_R___,
  //|--------+--------+--------+--------+--------|--------|--------+--------+--------+--------+--------|
                                  ___5MSE_2_L___, _______,                             ___5MSE_2_R___,
  //|--------+--------+--------+--------+--------|--------|--------+--------+--------+--------+--------|
                                  ___5MSE_3_L___,MISS_CTL,                             ___5MSE_3_R___,
  //|--------+--------+--------+--------+--------|--------|--------+--------+--------+--------+--------|
                               ___MSE_THUMB_L___, _______,          ___MSE_THUMB_R___
                    //|--------+--------+--------+--------+--------+--------+--------|
  ),
  [_ADD] = LAYOUT_btgrant(
  //|--------------------------------------------|--------|--------------------------------------------|
                                  ___5ADD_1_L___, QK_BOOT,                             ___5ADD_1_R___,
  //|--------+--------+--------+--------+--------|--------|--------+--------+--------+--------+--------|
                                  ___5ADD_2_L___, _______,                             ___5ADD_2_R___,
  //|--------+--------+--------+--------+--------|--------|--------+--------+--------+--------+--------|
                                  ___5ADD_3_L___, _______,                             ___5ADD_3_R___,
  //|--------+--------+--------+--------+--------|--------|--------+--------+--------+--------+--------|
                               ___ADD_THUMB_L___, _______,          ___ADD_THUMB_R___
                    //|--------+--------+--------+--------+--------+--------+--------|
  )
};

bool achordion_chord_keymap(uint16_t tap_hold_keycode,
                            keyrecord_t* tap_hold_record,
                            uint16_t other_keycode,
                            keyrecord_t* other_record) {

  return tap_hold_record->event.key.row == 3;
}

#ifdef RGBLIGHT_ENABLE
void keyboard_post_init_keymap(void) {
    rgblight_enable();
    rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL);
    rgblight_step();
    rgblight_step();
    rgblight_step();
    rgblight_step();
    rgblight_step();

    return;
}
#endif

#ifdef ENCODER_MAP_ENABLE
    const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
        [_BASE] = { ENCODER_CCW_CW(KC_VOLU,  KC_VOLD) },
        [_NUM]  = { ENCODER_CCW_CW(KC_PGUP,  KC_PGDN) },
        [_SYM]  = { ENCODER_CCW_CW(KC_MNXT,  KC_MPRV) },
        [_NAV]  = { ENCODER_CCW_CW(FWD,     BACK) },
        [_FUN]  = { ENCODER_CCW_CW(KC_BRIU,  KC_BRID) },
        [_MSE]  = { ENCODER_CCW_CW(RGHT_SPC, LEFT_SPC) },
        [_ADD]  = { ENCODER_CCW_CW(XXXXXXX,  XXXXXXX) },
        [_NRM] =  { ENCODER_CCW_CW(KC_VOLU,  KC_VOLD) }
    };
#endif
