#include "event.h"
#include <Arduino.h>

void event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);
    int *pLED1 = (int *)lv_event_get_user_data(e);
    // int *pLED2 = (int *)lv_event_get_user_data(e);

    if (obj == objects.valve_bt && code == LV_EVENT_PRESSED)
    {
        gpio_set_level((gpio_num_t)*pLED1, 1);
    }
    else if (obj == objects.valve_bt && code == LV_EVENT_RELEASED)
    {
        gpio_set_level((gpio_num_t)*pLED1, 0);
    }
    else if (obj == objects.sw_pump)
    {
        if (lv_obj_has_state(objects.sw_pump,LV_STATE_CHECKED))
        {
            char buf[32];
            lv_roller_get_selected_str(objects.pwmpercent, buf, sizeof(buf));
            int pwmpercent = String(buf).toInt();
            int pwmval = pwmpercent*255/100;
            analogWrite(22,pwmval);
            Serial.println(pwmval);
        }
        else{
            analogWrite(22,0);
            // Serial.println("OFF");
        }
    }
}
void update_adc34_meter(lv_timer_t *timer)
{
    LV_UNUSED(timer);
    int adc34_val = analogRead(34);
    int k34 = (adc34_val*100)/4095.0;
    lv_meter_set_indicator_value(objects.adc34meter, indicator1, k34);
    lv_label_set_text(objects.adc34val, String(k34).c_str());
}

void update_adc33_meter(lv_timer_t *timer)
{
    LV_UNUSED(timer);
    int adc33_val = analogRead(33);
    int k33 = (adc33_val*100)/4095.0;
    lv_slider_set_value(objects.adc33bar, k33, LV_ANIM_OFF);
    char buf[32];
    lv_label_set_text(objects.adc33val, buf);
}

void get_sw_state(lv_timer_t * timer) {
    int *pSW = (int *) timer->user_data;   
    int state = digitalRead(*pSW);         

    if (state == 0) {
        lv_led_on(objects.motor_st);
    } else {
       lv_led_off(objects.motor_st);
    }
}