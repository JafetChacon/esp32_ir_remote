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
    //ESP_ERROR_CHECK(rmt_new_ir_nec_encoder(&nec_encoder_cfg, &nec_encoder));
    ESP_LOGI(TAG, "enable RMT TX channel");
    ESP_ERROR_CHECK(rmt_enable(tx_channel));
    
    holis2();

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
