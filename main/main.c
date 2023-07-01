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
#include "freertos/queue.h"

#define TIME_FOR_LONG_PRESS         500000        //uS
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

QueueHandle_t interrutCommandsQueue;
esp_timer_handle_t button0_timer0_handler;
esp_timer_handle_t button0_timer1_handler;
esp_timer_handle_t button0_timer2_handler;
esp_timer_handle_t button1_timer0_handler;
esp_timer_handle_t button1_timer1_handler;
esp_timer_handle_t button1_timer2_handler;
esp_timer_handle_t button2_timer0_handler;
esp_timer_handle_t button2_timer1_handler;
esp_timer_handle_t button2_timer2_handler;

static const char *TAG_RMT = "RMT";

void button0_timer0_callback(void *param){
    ESP_ERROR_CHECK(esp_timer_start_once(button0_timer1_handler, 1000000));
    uint16_t command = 0x2002;
    xQueueSendFromISR(interrutCommandsQueue, &command, NULL);
    //ESP_LOGI(TAG_RMT, "SEND COMMAND 2");
    printNumTo7Seg(2, sevSegPIN);
}

void button0_timer1_callback(void *param){
    ESP_ERROR_CHECK(esp_timer_start_once(button0_timer2_handler, 100000));
    uint16_t command = 0x3003;
    xQueueSendFromISR(interrutCommandsQueue, &command, NULL);
    //ESP_LOGI(TAG_RMT, "SEND COMMAND 3");
    printNumTo7Seg(3, sevSegPIN);
}

void button0_timer2_callback(void *param){
    //ESP_LOGI(TAG_RMT, "SEND COMMAND 3");
    uint16_t command = 0x3003;
    xQueueSendFromISR(interrutCommandsQueue, &command, NULL);
    printNumTo7Seg(3, sevSegPIN);
    if (!gpio_get_level(button[0])) ESP_ERROR_CHECK(esp_timer_start_once(button0_timer2_handler, 200000));
}

void button1_timer0_callback(void *param){
    ESP_ERROR_CHECK(esp_timer_start_once(button1_timer1_handler, 1000000));
    uint16_t command = 0x5005;
    xQueueSendFromISR(interrutCommandsQueue, &command, NULL);
    //ESP_LOGI(TAG_RMT, "SEND COMMAND 2");
    printNumTo7Seg(2, sevSegPIN);
}

void button1_timer1_callback(void *param){
    ESP_ERROR_CHECK(esp_timer_start_once(button1_timer2_handler, 100000));
    uint16_t command = 0x6006;
    xQueueSendFromISR(interrutCommandsQueue, &command, NULL);
    //ESP_LOGI(TAG_RMT, "SEND COMMAND 3");
    printNumTo7Seg(3, sevSegPIN);
}

void button1_timer2_callback(void *param){
    //ESP_LOGI(TAG_RMT, "SEND COMMAND 3");
    uint16_t command = 0x6006;
    xQueueSendFromISR(interrutCommandsQueue, &command, NULL);
    printNumTo7Seg(3, sevSegPIN);
    if (!gpio_get_level(button[1])) ESP_ERROR_CHECK(esp_timer_start_once(button1_timer2_handler, 200000));
}

void button2_timer0_callback(void *param){
    ESP_ERROR_CHECK(esp_timer_start_once(button2_timer1_handler, 1000000));
    uint16_t command = 0x8008;
    xQueueSendFromISR(interrutCommandsQueue, &command, NULL);
    //ESP_LOGI(TAG_RMT, "SEND COMMAND 2");
    printNumTo7Seg(8, sevSegPIN);
}

void button2_timer1_callback(void *param){
    ESP_ERROR_CHECK(esp_timer_start_once(button2_timer2_handler, 100000));
    uint16_t command = 0x9009;
    xQueueSendFromISR(interrutCommandsQueue, &command, NULL);
    //ESP_LOGI(TAG_RMT, "SEND COMMAND 3");
    printNumTo7Seg(9, sevSegPIN);
}

void button2_timer2_callback(void *param){
    //ESP_LOGI(TAG_RMT, "SEND COMMAND 3");
    uint16_t command = 0x9009;
    xQueueSendFromISR(interrutCommandsQueue, &command, NULL);
    printNumTo7Seg(9, sevSegPIN);
    if (!gpio_get_level(button[2])) ESP_ERROR_CHECK(esp_timer_start_once(button2_timer2_handler, 200000));
}

static void IRAM_ATTR button0_interrupt_handler(void *args)
{
    //uint8_t _button = (uint8_t)args;
    if (!gpio_get_level(button[0])){        //Flanco de bajada (Cuando se presiona el botón)
        ESP_ERROR_CHECK(esp_timer_start_once(button0_timer0_handler, 1000000));
    } else {                                //Flanco de subida (Cuando se suelta el botón)
        if(esp_timer_is_active((button0_timer1_handler))) ESP_ERROR_CHECK(esp_timer_stop(button0_timer1_handler));
        if(esp_timer_is_active((button0_timer2_handler))) ESP_ERROR_CHECK(esp_timer_stop(button0_timer2_handler));
        if (esp_timer_is_active((button0_timer0_handler))){
            uint16_t command = 0x1001;
            xQueueSendFromISR(interrutCommandsQueue, &command, NULL);
            printNumTo7Seg(1, sevSegPIN);
            //ESP_LOGI(TAG_RMT, "SEND COMMAND 1");
            ESP_ERROR_CHECK(esp_timer_stop(button0_timer0_handler));
        }
    }
    //int pinNumber = (int)args;
    //xQueueSendFromISR(interputQueue, &pinNumber, NULL);
}

static void IRAM_ATTR button1_interrupt_handler(void *args)
{
    if (!gpio_get_level(button[1])){        //Flanco de bajada (Cuando se presiona el botón)
        ESP_ERROR_CHECK(esp_timer_start_once(button1_timer0_handler, 1000000));
    } else {                                //Flanco de subida (Cuando se suelta el botón)
        if(esp_timer_is_active((button1_timer1_handler))) ESP_ERROR_CHECK(esp_timer_stop(button1_timer1_handler));
        if(esp_timer_is_active((button1_timer2_handler))) ESP_ERROR_CHECK(esp_timer_stop(button1_timer2_handler));
        if (esp_timer_is_active((button1_timer0_handler))){
            uint16_t command = 0x4004;
            xQueueSendFromISR(interrutCommandsQueue, &command, NULL);
            printNumTo7Seg(4, sevSegPIN);
            ESP_ERROR_CHECK(esp_timer_stop(button1_timer0_handler));
        }
    }
}

static void IRAM_ATTR button2_interrupt_handler(void *args)
{
    if (!gpio_get_level(button[2])){        //Flanco de bajada (Cuando se presiona el botón)
        ESP_ERROR_CHECK(esp_timer_start_once(button2_timer0_handler, 1000000));
    } else {                                //Flanco de subida (Cuando se suelta el botón)
        if(esp_timer_is_active((button2_timer1_handler))) ESP_ERROR_CHECK(esp_timer_stop(button2_timer1_handler));
        if(esp_timer_is_active((button2_timer2_handler))) ESP_ERROR_CHECK(esp_timer_stop(button2_timer2_handler));
        if (esp_timer_is_active((button2_timer0_handler))){
            uint16_t command = 0x7007;
            xQueueSendFromISR(interrutCommandsQueue, &command, NULL);
            printNumTo7Seg(7, sevSegPIN);
            ESP_ERROR_CHECK(esp_timer_stop(button2_timer0_handler));
        }
    }
}

void rmtControl(void *params)
{
    /*********************************************Configuración RMT*************************************************************/
    ESP_LOGI(TAG_RMT, "create RMT TX channel");
    rmt_tx_channel_config_t tx_channel_cfg = {
        .clk_src = RMT_CLK_SRC_DEFAULT,
        .resolution_hz = EXAMPLE_IR_RESOLUTION_HZ,
        .mem_block_symbols = 64, // amount of RMT symbols that the channel can store at a time
        .trans_queue_depth = 4,  // number of transactions that allowed to pending in the background, this example won't queue multiple transactions, so queue depth > 1 is sufficient
        .gpio_num = EXAMPLE_IR_TX_GPIO_NUM,
    };
    rmt_channel_handle_t tx_channel = NULL;
    ESP_ERROR_CHECK(rmt_new_tx_channel(&tx_channel_cfg, &tx_channel));
    ESP_LOGI(TAG_RMT, "modulate carrier to TX channel");
    rmt_carrier_config_t carrier_cfg = {
        .duty_cycle = 0.33,
        .frequency_hz = 38000, // 38KHz
    };
    ESP_ERROR_CHECK(rmt_apply_carrier(tx_channel, &carrier_cfg));
    // this example won't send NEC frames in a loop
    rmt_transmit_config_t transmit_config = {
        .loop_count = 0, // no loop
    };
    ESP_LOGI(TAG_RMT, "install IR NEC encoder");
    ir_nec_encoder_config_t nec_encoder_cfg = {
        .resolution = EXAMPLE_IR_RESOLUTION_HZ,
    };
    rmt_encoder_handle_t nec_encoder = NULL;
    ESP_ERROR_CHECK(rmt_new_ir_nec_encoder(&nec_encoder_cfg, &nec_encoder));
    ESP_LOGI(TAG_RMT, "enable RMT TX channel");
    ESP_ERROR_CHECK(rmt_enable(tx_channel));
    
    ir_nec_scan_code_t scan_code = {
        .address = 0xFF00,
        .command = 0xC0C0,
    };

    int command = 0;
    while (true){
        printNumTo7Seg(0, sevSegPIN);
        if (xQueueReceive(interrutCommandsQueue, &command, portMAX_DELAY)){
            scan_code.command = (uint16_t)command;
            ESP_ERROR_CHECK(rmt_transmit(tx_channel, nec_encoder, &scan_code, sizeof(scan_code), &transmit_config));
            ESP_LOGI(TAG_RMT, "Command sent: 0x%04X%04X", (int)scan_code.address, (int)scan_code.command);
            printNumTo7Seg(0, sevSegPIN);
        }
    }
    
}

void app_main(void)
{
    /*********************************************Configuración Timer***********************************************************/
    const esp_timer_create_args_t button0_timer0_args = {
        .callback = &button0_timer0_callback,
        .name = "Button 0 Timer 0"};
    const esp_timer_create_args_t button0_timer1_args = {
        .callback = &button0_timer1_callback,
        .name = "Button 0 Timer 1"};
    const esp_timer_create_args_t button0_timer2_args = {
        .callback = &button0_timer2_callback,
        .name = "Button 0 Timer 2"};
    const esp_timer_create_args_t button1_timer0_args = {
        .callback = &button1_timer0_callback,
        .name = "Button 1 Timer 0"};
    const esp_timer_create_args_t button1_timer1_args = {
        .callback = &button1_timer1_callback,
        .name = "Button 1 Timer 1"};
    const esp_timer_create_args_t button1_timer2_args = {
        .callback = &button1_timer2_callback,
        .name = "Button 1 Timer 2"};
    const esp_timer_create_args_t button2_timer0_args = {
        .callback = &button2_timer0_callback,
        .name = "Button 2 Timer 0"};
    const esp_timer_create_args_t button2_timer1_args = {
        .callback = &button2_timer1_callback,
        .name = "Button 2 Timer 1"};
    const esp_timer_create_args_t button2_timer2_args = {
        .callback = &button2_timer2_callback,
        .name = "Button 2 Timer 2"};
    
    ESP_ERROR_CHECK(esp_timer_create(&button0_timer0_args, &button0_timer0_handler));
    ESP_ERROR_CHECK(esp_timer_create(&button0_timer1_args, &button0_timer1_handler));
    ESP_ERROR_CHECK(esp_timer_create(&button0_timer2_args, &button0_timer2_handler));
    ESP_ERROR_CHECK(esp_timer_create(&button1_timer0_args, &button1_timer0_handler));
    ESP_ERROR_CHECK(esp_timer_create(&button1_timer1_args, &button1_timer1_handler));
    ESP_ERROR_CHECK(esp_timer_create(&button1_timer2_args, &button1_timer2_handler));
    ESP_ERROR_CHECK(esp_timer_create(&button2_timer0_args, &button2_timer0_handler));
    ESP_ERROR_CHECK(esp_timer_create(&button2_timer1_args, &button2_timer1_handler));
    ESP_ERROR_CHECK(esp_timer_create(&button2_timer2_args, &button2_timer2_handler));
    
    /*****************************************Configuración 7 segmentos*********************************************************/
    for (uint8_t i = 0; i < 7; i++){
        gpio_set_direction(sevSegPIN[i], GPIO_MODE_OUTPUT);
    }
    for (uint8_t i = 0; i < 6; i++){
        gpio_set_direction(button[i], GPIO_MODE_INPUT);
        gpio_set_pull_mode(button[i], GPIO_PULLUP_ONLY);
        //gpio_pulldown_dis(button[i]);
        //gpio_pullup_en(button[i]);
        gpio_set_intr_type(button[i], GPIO_INTR_ANYEDGE);  
    }
    interrutCommandsQueue = xQueueCreate(10, sizeof(int));
    gpio_install_isr_service(0);
    gpio_isr_handler_add(button[0], button0_interrupt_handler, (void *)button[0]);
    gpio_isr_handler_add(button[1], button1_interrupt_handler, (void *)button[1]);
    gpio_isr_handler_add(button[2], button2_interrupt_handler, (void *)button[2]);
    
    //Prueba de display//
    for (uint8_t i = 0; i < 7; i++){
        gpio_set_level(sevSegPIN[i], 1);
        vTaskDelay(200/ portTICK_PERIOD_MS);
        gpio_set_level(sevSegPIN[i], 0);
    }
    printNumTo7Seg(8, sevSegPIN);
    vTaskDelay(1000/ portTICK_PERIOD_MS);

    

    /*********************************************Configuración Task 1**********************************************************/
    //interputQueue = xQueueCreate(10, sizeof(int));
    xTaskCreate(rmtControl, "Administrador de RMT", 2048, NULL, 1, NULL);


    while (true)
    {
        vTaskDelay(1000/ portTICK_PERIOD_MS);
    }
    
}
