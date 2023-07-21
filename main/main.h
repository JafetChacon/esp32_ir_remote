#ifndef _MAIN_H_
#define _MAIN_H_

#include "freertos/queue.h"

#define DOUBLE_CLICK_TIME       500000          //uS
#define LONG_PRESS_TIME         300000         //uS
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
                            {   {0xF10E,        1},     {0x00FF,        2},     {0x0003,        3},     {0x0000,        4}},    // Enter (MUTE)
                            {   {0x906F,        1},     {0xA15E,        2},     {0x0007,        3},     {0x0000,        4}},    // Mode
                            {   {0xD24B,        1},     {0x51AE,        2},     {0xD24B,        3},     {0xD24B,        4}},    // Volume +
                            {   {0x21DE,        1},     {0xB14E,        2},     {0X21DE,        3},     {0x21DE,        4}},    // Volume -
                            {   {0X10FE,        1},     {0XD02F,        2},     {0X916E,        3},     {0x0000,        4}},    // Seek +
                            {   {0X11EE,        1},     {0XD12E,        2},     {0X718E,        3},     {0x0000,        4}}     // Seek -
};                      //      Play/Pause              Call                    Mute
                        //      Mode                    Hang                    Power
                        //      Vol +                   Next                    Vol +                   Vol +
                        //      Vol -                   Prev                    Vol -                   Vol -
                        //      Up arrow                Right arrow             USB/SD
                        //      Down arrow              Left arrow              BAND AMD


#endif