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
                            {   0x0001, 0x0002, 0x0003},
                            {   0x0004, 0x0005, 0x0006},
                            {   0x0007, 0x0008, 0x0009},
                            {   0x000A, 0x000B, 0X000C},
                            {   0X000D, 0X000E, 0X000F},
                            {   0X0010, 0X0011, 0X0012}
};


#endif