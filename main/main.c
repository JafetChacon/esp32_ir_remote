#include <stdio.h>
#include "../components/disp7seg/disp7seg.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

void app_main(void)
{
    uint8_t seg_A = 21,
            seg_B = 19,
            seg_C = 05,
            seg_D = 04,
            seg_E = 02,
            seg_F = 22,
            seg_G = 23;
    uint8_t sevSegPIN [7] = {seg_A, seg_B, seg_C, seg_D, seg_E, seg_F, seg_G};
    for (uint8_t i = 0; i < 7; i++){
        gpio_set_direction(sevSegPIN[i], GPIO_MODE_OUTPUT);
    }
    printNumTo7Seg(8, sevSegPIN);
    vTaskDelay(1000/ portTICK_PERIOD_MS);
    
    while(1){
        for (uint8_t i = 0; i < 16; i++){
            printNumTo7Seg(i, sevSegPIN);
            vTaskDelay(1000/ portTICK_PERIOD_MS);
        }
    }
}
