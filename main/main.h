#ifndef _MAIN_H_
#define _MAIN_H_

#include "freertos/queue.h"

#define LONG_PRESS_TIME         1000000        //uS
#define LONG_KEEP_PRESS_TIME    1000000        //uS
#define CONTINOUS_PRESS_TIMER   200000
#define NUM_OF_BUTTONS          6               //Total num of buttons in main program
#define NUM_OF_TIMERS           3               //Total num of timers for button (NOT MODIFY)
#define TIME_DISPLAYING         2000000         //Tiempo en milisegundos para mantener el valor en el display

const uint8_t button1 = 13,
        button2 = 12,
        button3 = 14,
        button4 = 27,   //27
        button5 = 26,   //26
        button6 = 25;
uint8_t button [NUM_OF_BUTTONS] = {button1, button2, button3, button4, button5, button6 };

const uint8_t seg_A = 21,       //21
        seg_B = 19,             //19
        seg_C = 05,             //05
        seg_D = 04,             //04
        seg_E = 02,             //02
        seg_F = 22,             //22
        seg_G = 23;             //23
uint8_t sevSegPIN [7] = {seg_A, seg_B, seg_C, seg_D, seg_E, seg_F, seg_G};

static const char *TAG_RMT = "RMT";

QueueHandle_t interrutCommandsQueue;
esp_timer_handle_t button_timer_handler [NUM_OF_BUTTONS][3];
esp_timer_handle_t displayTimer_handler;

typedef struct
{
        uint16_t command;
        uint8_t digitDisplay;
} command2send;

/*************COMANDS***********SINGLE-CLICK************DOUBLE-CLICK************LONG-PRESS*************CONTINUOUS-PRESS******/
command2send commands [NUM_OF_BUTTONS][4] = {
                            {   {0x0001,        1},     {0x0002,        2},     {0x0003,        3},     {0x0001,        1}},
                            {   {0x0004,        4},     {0x0005,        5},     {0x0006,        6},     {0x0004,        4}},
                            {   {0x0007,        7},     {0x0008,        8},     {0x0009,        9},     {0x0007,        7}},
                            {   {0x000A,        10},    {0x000B,        11},    {0X000C,        12},    {0x000A,        10}},
                            {   {0X000D,        13},    {0X000E,        14},    {0X000F,        15},    {0x000D,        13}},
                            {   {0X0010,        1},     {0X0011,        2},     {0X0012,        3},     {0x0001,        1}}
};


#endif