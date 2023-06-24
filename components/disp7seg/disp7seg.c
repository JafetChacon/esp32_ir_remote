#include "disp7seg.h"

static const char *TAG3 = "example";

void printNumTo7Seg(uint8_t num, uint8_t pins[7]){
    bool code [16][7] = {   {1,1,1,1,1,1,0},
                            {0,1,1,0,0,0,0},
                            {1,1,0,1,1,0,1},
                            {1,1,1,1,0,0,1},
                            {0,1,1,0,0,1,1},
                            {1,0,1,1,0,1,1},
                            {1,0,1,1,1,1,1},
                            {1,1,1,0,0,0,0},
                            {1,1,1,1,1,1,1},
                            {1,1,1,1,0,1,1},
                            {1,1,1,0,1,1,1},
                            {0,0,1,1,1,1,1},
                            {1,0,0,1,1,1,0},
                            {0,1,1,1,1,0,1},
                            {1,0,0,1,1,1,1},
                            {1,0,0,0,1,1,1}
                            };
    if (num<=16){
        for (uint8_t i = 0; i < 7; i++) gpio_set_level(pins[i],  (code[num][i])!= 0);
    } else{
        for (uint8_t i = 0; i < 7; i++) gpio_set_level(pins[i],  (code[0][i])!= 0);
    }
}

void holis3(void){
    ESP_LOGI(TAG3, "create RMT TX channel");
}