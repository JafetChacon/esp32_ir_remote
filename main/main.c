#include "main.h"
#include <stdio.h>
#include "../components/disp7seg/disp7seg.h"
#include "../components/ir_nec_encoder/ir_nec_encoder.h"
#include "../components/rmt_nec_init/rmt_nec_init.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_timer.h"
#include "driver/rmt_tx.h"
#include "esp_log.h"

#define TIME_FOR_LONG_PRESS         500000        //uS
bool long_pressed = false;

static const char *TAG = "example";

void timer_callback(void *param){
    long_pressed = true;
}

void app_main(void)
{
    
    /*Configuración RMT*/
    ESP_LOGI(TAG, "create RMT TX channel");
    rmt_tx_channel_config_t tx_channel_cfg = {
        .clk_src = RMT_CLK_SRC_DEFAULT,
        .resolution_hz = EXAMPLE_IR_RESOLUTION_HZ,
        .mem_block_symbols = 64, // amount of RMT symbols that the channel can store at a time
        .trans_queue_depth = 4,  // number of transactions that allowed to pending in the background, this example won't queue multiple transactions, so queue depth > 1 is sufficient
        .gpio_num = EXAMPLE_IR_TX_GPIO_NUM,
    };
    rmt_channel_handle_t tx_channel = NULL;
    ESP_ERROR_CHECK(rmt_new_tx_channel(&tx_channel_cfg, &tx_channel));
    ESP_LOGI(TAG, "modulate carrier to TX channel");
    rmt_carrier_config_t carrier_cfg = {
        .duty_cycle = 0.33,
        .frequency_hz = 38000, // 38KHz
    };
    ESP_ERROR_CHECK(rmt_apply_carrier(tx_channel, &carrier_cfg));
    // this example won't send NEC frames in a loop
    rmt_transmit_config_t transmit_config = {
        .loop_count = 0, // no loop
    };
    ESP_LOGI(TAG, "install IR NEC encoder");
    ir_nec_encoder_config_t nec_encoder_cfg = {
        .resolution = EXAMPLE_IR_RESOLUTION_HZ,
    };
    rmt_encoder_handle_t nec_encoder = NULL;
    ESP_ERROR_CHECK(rmt_new_ir_nec_encoder(&nec_encoder_cfg, &nec_encoder));
    ESP_LOGI(TAG, "enable RMT TX channel");
    ESP_ERROR_CHECK(rmt_enable(tx_channel));

    /*Configuración Timer*/
    const esp_timer_create_args_t my_timer_args = {
        .callback = &timer_callback,
        .name = "PinchePutoPerroTimer"};
    esp_timer_handle_t timer_handler;
    ESP_ERROR_CHECK(esp_timer_create(&my_timer_args, &timer_handler));
    
    //holis();
    //holis2();
    //holis3();

    /*Configuración 7 segmentos*/
    //bool longAction = false;
    uint8_t seg_A = 21,
            seg_B = 19,
            seg_C = 05,
            seg_D = 04,
            seg_E = 02,
            seg_F = 22,
            seg_G = 23;
    uint8_t sevSegPIN [7] = {seg_A, seg_B, seg_C, seg_D, seg_E, seg_F, seg_G};
    uint8_t button1 = 13,   //Mode
            button2 = 12,   //
            button3 = 14,
            button4 = 27,
            button5 = 26,
            button6 = 25;
    uint8_t button [6] = {button1, button2, button3, button4, button5, button6 };
    for (uint8_t i = 0; i < 7; i++){
        gpio_set_direction(sevSegPIN[i], GPIO_MODE_OUTPUT);
    }
    for (uint8_t i = 0; i < 6; i++){
        gpio_set_direction(button[i], GPIO_MODE_INPUT);
        gpio_set_pull_mode(button[i], GPIO_PULLUP_ONLY);  
    }
    //Prueba de display
    for (uint8_t i = 0; i < 7; i++){
        gpio_set_level(sevSegPIN[i], 1);
        vTaskDelay(200/ portTICK_PERIOD_MS);
        gpio_set_level(sevSegPIN[i], 0);
    }
    printNumTo7Seg(8, sevSegPIN);
    vTaskDelay(1000/ portTICK_PERIOD_MS);

    ir_nec_scan_code_t scan_code = {
        .address = 0xFF00,
        .command = 0xC0C0,
    };
    while (1) {
            scan_code.address = 0x0E0E;
            scan_code.command = 0x0000;
            if (gpio_get_level(button[0]) == 0) {  // If button is pressed
                ESP_ERROR_CHECK(esp_timer_start_once(timer_handler, TIME_FOR_LONG_PRESS)); //Valor en microsegundos
                vTaskDelay(10/ portTICK_PERIOD_MS);
                while (gpio_get_level(button[0]) == 0) if (long_pressed) break;
                if(!long_pressed){                          //Acción para presionado corto
                    printNumTo7Seg(1, sevSegPIN);
                    scan_code.command = 0x9E61;
                } else {                                    //Acción para presionado largo
                    printNumTo7Seg(10, sevSegPIN);
                    scan_code.command = 0xFB04;
                }
            } else if (gpio_get_level(button[1]) == 0) {  // If button is pressed
                ESP_ERROR_CHECK(esp_timer_start_once(timer_handler, TIME_FOR_LONG_PRESS)); //Valor en microsegundos
                vTaskDelay(10/ portTICK_PERIOD_MS);
                while (gpio_get_level(button[1]) == 0) if (long_pressed) break;
                if(!long_pressed){                          //Acción para presionado corto
                    printNumTo7Seg(2, sevSegPIN);
                    scan_code.command = 0x9F60;
                } else {                                    //Acción para presionado largo
                    printNumTo7Seg(11, sevSegPIN);
                    scan_code.command = 0x9768;
                }
            } else if (gpio_get_level(button[2]) == 0) {  // If button is pressed
                ESP_ERROR_CHECK(esp_timer_start_once(timer_handler, TIME_FOR_LONG_PRESS)); //Valor en microsegundos
                vTaskDelay(10/ portTICK_PERIOD_MS);
                while (gpio_get_level(button[2]) == 0) if (long_pressed) break;
                if(!long_pressed){                          //Acción para presionado corto
                    printNumTo7Seg(3, sevSegPIN);
                    scan_code.command = 0X9B64;
                } else {                                    //Acción para presionado largo
                    printNumTo7Seg(12, sevSegPIN);
                    scan_code.command = 0X956A;
                }
            } else if (gpio_get_level(button[3]) == 0) {  // If button is pressed
                ESP_ERROR_CHECK(esp_timer_start_once(timer_handler, TIME_FOR_LONG_PRESS)); //Valor en microsegundos
                vTaskDelay(10/ portTICK_PERIOD_MS);
                while (gpio_get_level(button[3]) == 0) if (long_pressed) break;
                if(!long_pressed){                          //Acción para presionado corto
                    printNumTo7Seg(4, sevSegPIN);
                    scan_code.command = 0x5EA1;
                } else {                                    //Acción para presionado largo
                    printNumTo7Seg(13, sevSegPIN);
                    scan_code.command = 0x16E9;
                }
            } else if (gpio_get_level(button[4]) == 0) {  // If button is pressed
                ESP_ERROR_CHECK(esp_timer_start_once(timer_handler, TIME_FOR_LONG_PRESS)); //Valor en microsegundos
                vTaskDelay(10/ portTICK_PERIOD_MS);
                while (gpio_get_level(button[4]) == 0) if (long_pressed) break;
                if(!long_pressed){                          //Acción para presionado corto
                    printNumTo7Seg(5, sevSegPIN);
                    scan_code.command = 0x7B84;
                } else {                                    //Acción para presionado largo
                    printNumTo7Seg(14, sevSegPIN);
                    scan_code.command = 0x7F80;
                }
            } else if (gpio_get_level(button[5]) == 0) {  // If button is pressed
                ESP_ERROR_CHECK(esp_timer_start_once(timer_handler, TIME_FOR_LONG_PRESS)); //Valor en microsegundos
                vTaskDelay(10/ portTICK_PERIOD_MS);
                while (gpio_get_level(button[5]) == 0) if (long_pressed) break;
                if(!long_pressed){                          //Acción para presionado corto
                    printNumTo7Seg(6, sevSegPIN);
                    scan_code.command = 0xF10E;
                } else {                                    //Acción para presionado largo
                    printNumTo7Seg(15, sevSegPIN);
                    scan_code.command = 0xF20D;
                }
            }
            else {
                printNumTo7Seg(0, sevSegPIN);
                scan_code.command = 0x0000;
            }
            if (scan_code.command!=0x0000){
                ESP_ERROR_CHECK(rmt_transmit(tx_channel, nec_encoder, &scan_code, sizeof(scan_code), &transmit_config));
                printf("Address=%04X, Command=%04X\r\n\r\n", scan_code.address, scan_code.command);
                vTaskDelay(100/ portTICK_PERIOD_MS);
            }
            long_pressed = false;
            esp_timer_stop(timer_handler);
            
        vTaskDelay(200/ portTICK_PERIOD_MS);
    }
}
