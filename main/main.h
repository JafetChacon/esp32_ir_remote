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
                            {   {0xE01F,        1},     {0xFF00,        2},     {0xFC03,        3},     {0x0000,        4}},    // Enter (MUTE)
                            {   {0xF609,        1},     {0xE51A,        2},     {0xEF10,        3},     {0x0000,        4}},    // Mode
                            {   {0xB42D,        1},     {0xEA15,        2},     {0xB42D,        3},     {0xB42D,        4}},    // Volume +
                            {   {0xED12,        1},     {0xE41B,        2},     {0XED12,        3},     {0xED12,        4}},    // Volume -
                            {   {0XEF01,        1},     {0XF20D,        2},     {0XE619,        3},     {0x0000,        4}},    // Seek +
                            {   {0XEE11,        1},     {0XE21D,        2},     {0XE817,        3},     {0x0000,        4}}     // Seek -
};                      //      Play/Pause              Call                    Mute
                        //      Mode                    Hang                    Power
                        //      Vol +                   Next                    Vol +                   Vol +
                        //      Vol -                   Prev                    Vol -                   Vol -
                        //      Up arrow                Right arrow             USB/SD
                        //      Down arrow              Left arrow              BAND AMD


#endif