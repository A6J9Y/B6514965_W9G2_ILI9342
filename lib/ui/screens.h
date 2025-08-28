#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *tabcontrol;
    lv_obj_t *tab;
    lv_obj_t *sw_pump;
    lv_obj_t *valve_bt;
    lv_obj_t *motor_st;
    lv_obj_t *pwmpercent;
    lv_obj_t *tabmeter;
    lv_obj_t *adc33bar;
    lv_obj_t *adc33val;
    lv_obj_t *adc34meter;
    lv_obj_t *adc34val;
} objects_t;

extern objects_t objects;
extern lv_meter_indicator_t * indicator1;

enum ScreensEnum {
    SCREEN_ID_MAIN = 1,
};

void create_screen_main();
void tick_screen_main();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/