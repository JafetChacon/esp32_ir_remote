#ifndef _MAIN_H_
#define _MAIN_H_

#include "freertos/queue.h"

#define LONG_PRESS_TIME         1000000        //uS
#define LONG_KEEP_PRESS_TIME    1000000        //uS
#define CONTINOUS_PRESS_TIMER   200000

const uint8_t button1 = 13,
        button2 = 12,
        button3 = 14,
        button4 = 27,
        button5 = 26,
        button6 = 25;
uint8_t button [6] = {button1, button2, button3, button4, button5, button6 };

const uint8_t seg_A = 21,
        seg_B = 19,
        seg_C = 05,
        seg_D = 04,
        seg_E = 02,
        seg_F = 22,
        seg_G = 23;
uint8_t sevSegPIN [7] = {seg_A, seg_B, seg_C, seg_D, seg_E, seg_F, seg_G};

static const char *TAG_RMT = "RMT";

QueueHandle_t interrutCommandsQueue;
esp_timer_handle_t button_timer_handler [6][3];

uint16_t commands [6][3] = {
                            {   0x0101, 0x0202, 0x0303},
                            {   0x0404, 0x0505, 0x0606},
                            {   0x0707, 0x0808, 0x0909},
                            {   0x0A0A, 0x0B0B, 0X0C0C},
                            {   0X0D0D, 0X0E0E, 0X0F0F},
                            {   0X1010, 0X1111, 0X1212}
};


#endif