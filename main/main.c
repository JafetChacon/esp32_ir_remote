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
#include "main.h"

void displayTimer_callback(void *param){        //Función para borrar el display
    printNumTo7Seg(17, sevSegPIN);
}
void button0_timer0_callback(void *param){
    if (!gpio_get_level(button[0])) ESP_ERROR_CHECK(esp_timer_start_once(button_timer_handler[0][1], LONG_PRESS_TIME));
    if ( gpio_get_level(button[0])) xQueueSendFromISR(interrutCommandsQueue, &commands[0][0], NULL);                            /*Single click command*/
}
void button0_timer1_callback(void *param){
    if (!gpio_get_level(button[0])) ESP_ERROR_CHECK(esp_timer_start_once(button_timer_handler[0][2], CONTINOUS_PRESS_TIMER));
    xQueueSendFromISR(interrutCommandsQueue, &commands[0][2], NULL);                            /*Long press command*/
}
void button0_timer2_callback(void *param){
    //xQueueSendFromISR(interrutCommandsQueue, &commands[0][3], NULL);                            /*Keep pressed command*/
    if (!gpio_get_level(button[0])) ESP_ERROR_CHECK(esp_timer_start_once(button_timer_handler[0][2], CONTINOUS_PRESS_TIMER));
}
void button1_timer0_callback(void *param){
    if (!gpio_get_level(button[1])) ESP_ERROR_CHECK(esp_timer_start_once(button_timer_handler[1][1], LONG_PRESS_TIME));
    if ( gpio_get_level(button[1])) xQueueSendFromISR(interrutCommandsQueue, &commands[1][0], NULL);                            /*Single click command*/
}
void button1_timer1_callback(void *param){
    if (!gpio_get_level(button[1])) ESP_ERROR_CHECK(esp_timer_start_once(button_timer_handler[1][2], CONTINOUS_PRESS_TIMER));
    xQueueSendFromISR(interrutCommandsQueue, &commands[1][2], NULL);                                                            /*Long press command*/
}
void button1_timer2_callback(void *param){
    //xQueueSendFromISR(interrutCommandsQueue, &commands[1][3], NULL);                                                            /*Keep pressed command*/
    if (!gpio_get_level(button[1])) ESP_ERROR_CHECK(esp_timer_start_once(button_timer_handler[1][2], CONTINOUS_PRESS_TIMER));
}
void button2_timer0_callback(void *param){
    if (!gpio_get_level(button[2])) ESP_ERROR_CHECK(esp_timer_start_once(button_timer_handler[2][1], LONG_PRESS_TIME));
    if ( gpio_get_level(button[2])) xQueueSendFromISR(interrutCommandsQueue, &commands[2][0], NULL);                            /*Single click command*/
}
void button2_timer1_callback(void *param){
    if (!gpio_get_level(button[2])) ESP_ERROR_CHECK(esp_timer_start_once(button_timer_handler[2][2], CONTINOUS_PRESS_TIMER));
    xQueueSendFromISR(interrutCommandsQueue, &commands[2][2], NULL);                                                            /*Long press command*/
}
void button2_timer2_callback(void *param){
    xQueueSendFromISR(interrutCommandsQueue, &commands[2][3], NULL);                                                            /*Keep pressed command*/
    if (!gpio_get_level(button[2])) ESP_ERROR_CHECK(esp_timer_start_once(button_timer_handler[2][2], CONTINOUS_PRESS_TIMER));
}
void button3_timer0_callback(void *param){
    if (!gpio_get_level(button[3])) ESP_ERROR_CHECK(esp_timer_start_once(button_timer_handler[3][1], LONG_PRESS_TIME));
    if ( gpio_get_level(button[3])) xQueueSendFromISR(interrutCommandsQueue, &commands[3][0], NULL);                            /*Single click command*/
}
void button3_timer1_callback(void *param){
    if (!gpio_get_level(button[3])) ESP_ERROR_CHECK(esp_timer_start_once(button_timer_handler[3][2], CONTINOUS_PRESS_TIMER));
    xQueueSendFromISR(interrutCommandsQueue, &commands[3][2], NULL);                                                            /*Long press command*/
}
void button3_timer2_callback(void *param){
    xQueueSendFromISR(interrutCommandsQueue, &commands[3][3], NULL);                                                            /*Keep pressed command*/
    if (!gpio_get_level(button[3])) ESP_ERROR_CHECK(esp_timer_start_once(button_timer_handler[3][2], CONTINOUS_PRESS_TIMER));
}
void button4_timer0_callback(void *param){
    if (!gpio_get_level(button[4])) ESP_ERROR_CHECK(esp_timer_start_once(button_timer_handler[4][1], LONG_PRESS_TIME));
    if ( gpio_get_level(button[4])) xQueueSendFromISR(interrutCommandsQueue, &commands[4][0], NULL);                            /*Single click command*/
}
void button4_timer1_callback(void *param){
    if (!gpio_get_level(button[4])) ESP_ERROR_CHECK(esp_timer_start_once(button_timer_handler[4][2], CONTINOUS_PRESS_TIMER));
    xQueueSendFromISR(interrutCommandsQueue, &commands[4][2], NULL);                                                            /*Long press command*/
}
void button4_timer2_callback(void *param){
    //xQueueSendFromISR(interrutCommandsQueue, &commands[4][3], NULL);                                                            /*Keep pressed command*/
    if (!gpio_get_level(button[4])) ESP_ERROR_CHECK(esp_timer_start_once(button_timer_handler[4][2], CONTINOUS_PRESS_TIMER));
}
void button5_timer0_callback(void *param){
    if (!gpio_get_level(button[5])) ESP_ERROR_CHECK(esp_timer_start_once(button_timer_handler[5][1], LONG_PRESS_TIME));
    if ( gpio_get_level(button[5])) xQueueSendFromISR(interrutCommandsQueue, &commands[5][0], NULL);                            /*Single click command*/
}
void button5_timer1_callback(void *param){
    if (!gpio_get_level(button[5])) ESP_ERROR_CHECK(esp_timer_start_once(button_timer_handler[5][2], CONTINOUS_PRESS_TIMER));
    xQueueSendFromISR(interrutCommandsQueue, &commands[5][2], NULL);                                                            /*Long press command*/
}
void button5_timer2_callback(void *param){
    //xQueueSendFromISR(interrutCommandsQueue, &commands[5][3], NULL);                                                            /*Keep pressed command*/
    if (!gpio_get_level(button[5])) ESP_ERROR_CHECK(esp_timer_start_once(button_timer_handler[5][2], CONTINOUS_PRESS_TIMER));
}

static void IRAM_ATTR button0_interrupt_handler(void *args)
{
    if (!gpio_get_level(button[0])){        //Flanco de bajada (Cuando se presiona el botón)
        if (esp_timer_is_active((button_timer_handler[0][0]))){
            ESP_ERROR_CHECK(esp_timer_stop(button_timer_handler[0][0]));
            xQueueSendFromISR(interrutCommandsQueue, &commands[0][1], NULL);                        /*Enviar comando de doble click*/
        } else {
            ESP_ERROR_CHECK(esp_timer_start_once(button_timer_handler[0][0], DOUBLE_CLICK_TIME));
        }
    } else {                                //Flanco de subida (Cuando se suelta el botón)
        if (esp_timer_is_active((button_timer_handler[0][2]))) ESP_ERROR_CHECK(esp_timer_stop(button_timer_handler[0][2]));
        if (esp_timer_is_active((button_timer_handler[0][1]))) ESP_ERROR_CHECK(esp_timer_stop(button_timer_handler[0][1]));
    }
}
static void IRAM_ATTR button1_interrupt_handler(void *args)
{
    if (!gpio_get_level(button[1])){        //Flanco de bajada (Cuando se presiona el botón)
        if (esp_timer_is_active((button_timer_handler[1][0]))){
            ESP_ERROR_CHECK(esp_timer_stop(button_timer_handler[1][0]));
            xQueueSendFromISR(interrutCommandsQueue, &commands[1][1], NULL);                        /*Enviar comando de doble click*/
        } else {
            ESP_ERROR_CHECK(esp_timer_start_once(button_timer_handler[1][0], DOUBLE_CLICK_TIME));
        }
    } else {                                //Flanco de subida (Cuando se suelta el botón)
        if (esp_timer_is_active((button_timer_handler[1][2]))) ESP_ERROR_CHECK(esp_timer_stop(button_timer_handler[1][2]));
        if (esp_timer_is_active((button_timer_handler[1][1]))) ESP_ERROR_CHECK(esp_timer_stop(button_timer_handler[1][1]));
    }
}
static void IRAM_ATTR button2_interrupt_handler(void *args)
{
    if (!gpio_get_level(button[2])){        //Flanco de bajada (Cuando se presiona el botón)
        if (esp_timer_is_active((button_timer_handler[2][0]))){
            ESP_ERROR_CHECK(esp_timer_stop(button_timer_handler[2][0]));
            xQueueSendFromISR(interrutCommandsQueue, &commands[2][1], NULL);                        /*Enviar comando de doble click*/
        } else {
            ESP_ERROR_CHECK(esp_timer_start_once(button_timer_handler[2][0], DOUBLE_CLICK_TIME));
        }
    } else {                                //Flanco de subida (Cuando se suelta el botón)
        if (esp_timer_is_active((button_timer_handler[2][2]))) ESP_ERROR_CHECK(esp_timer_stop(button_timer_handler[2][2]));
        if (esp_timer_is_active((button_timer_handler[2][1]))) ESP_ERROR_CHECK(esp_timer_stop(button_timer_handler[2][1]));
    }
}
static void IRAM_ATTR button3_interrupt_handler(void *args)
{
    if (!gpio_get_level(button[3])){        //Flanco de bajada (Cuando se presiona el botón)
        if (esp_timer_is_active((button_timer_handler[3][0]))){
            ESP_ERROR_CHECK(esp_timer_stop(button_timer_handler[3][0]));
            xQueueSendFromISR(interrutCommandsQueue, &commands[3][1], NULL);                        /*Enviar comando de doble click*/
        } else {
            ESP_ERROR_CHECK(esp_timer_start_once(button_timer_handler[3][0], DOUBLE_CLICK_TIME));
        }
    } else {                                //Flanco de subida (Cuando se suelta el botón)
        if (esp_timer_is_active((button_timer_handler[3][2]))) ESP_ERROR_CHECK(esp_timer_stop(button_timer_handler[3][2]));
        if (esp_timer_is_active((button_timer_handler[3][1]))) ESP_ERROR_CHECK(esp_timer_stop(button_timer_handler[3][1]));
    }
}
static void IRAM_ATTR button4_interrupt_handler(void *args)
{
    if (!gpio_get_level(button[4])){        //Flanco de bajada (Cuando se presiona el botón)
        if (esp_timer_is_active((button_timer_handler[4][0]))){
            ESP_ERROR_CHECK(esp_timer_stop(button_timer_handler[4][0]));
            xQueueSendFromISR(interrutCommandsQueue, &commands[4][1], NULL);                        /*Enviar comando de doble click*/
        } else {
            ESP_ERROR_CHECK(esp_timer_start_once(button_timer_handler[4][0], DOUBLE_CLICK_TIME));
        }
    } else {                                //Flanco de subida (Cuando se suelta el botón)
        if (esp_timer_is_active((button_timer_handler[4][2]))) ESP_ERROR_CHECK(esp_timer_stop(button_timer_handler[4][2]));
        if (esp_timer_is_active((button_timer_handler[4][1]))) ESP_ERROR_CHECK(esp_timer_stop(button_timer_handler[4][1]));
    }
}
static void IRAM_ATTR button5_interrupt_handler(void *args)
{
    if (!gpio_get_level(button[5])){        //Flanco de bajada (Cuando se presiona el botón)
        if (esp_timer_is_active((button_timer_handler[5][0]))){
            ESP_ERROR_CHECK(esp_timer_stop(button_timer_handler[5][0]));
            xQueueSendFromISR(interrutCommandsQueue, &commands[5][1], NULL);                        /*Enviar comando de doble click*/
        } else {
            ESP_ERROR_CHECK(esp_timer_start_once(button_timer_handler[5][0], DOUBLE_CLICK_TIME));
        }
    } else {                                //Flanco de subida (Cuando se suelta el botón)
        if (esp_timer_is_active((button_timer_handler[5][2]))) ESP_ERROR_CHECK(esp_timer_stop(button_timer_handler[5][2]));
        if (esp_timer_is_active((button_timer_handler[5][1]))) ESP_ERROR_CHECK(esp_timer_stop(button_timer_handler[5][1]));
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
        .address = 0x00FF,
        .command = 0x0000,
    };

    command2send command;
    while (true){
        //printNumTo7Seg(0, sevSegPIN);
        if (xQueueReceive(interrutCommandsQueue, &command, portMAX_DELAY)){
            scan_code.command = (uint16_t)command.command;
            ESP_ERROR_CHECK(rmt_transmit(tx_channel, nec_encoder, &scan_code, sizeof(scan_code), &transmit_config));
            ESP_LOGI(TAG_RMT, "Command sent: 0x%04X%04X", (int)scan_code.address, (int)scan_code.command);
            printNumTo7Seg(command.digitDisplay, sevSegPIN);
            if(!esp_timer_is_active((displayTimer_handler))){
                ESP_ERROR_CHECK(esp_timer_start_once(displayTimer_handler, TIME_DISPLAYING));
            } else {
                ESP_ERROR_CHECK(esp_timer_restart(displayTimer_handler, TIME_DISPLAYING));
            }
        }
    }
    
}

void app_main(void)
{
    /*********************************************Configuración Timers**********************************************************/
    const esp_timer_create_args_t displayTimer_args= {
                                    .callback = &displayTimer_callback,  .name = "Timer for display digit at 7seg Display"};
    const esp_timer_create_args_t button_timer_args [NUM_OF_BUTTONS][3] = {
        {{.callback = &button0_timer0_callback,  .name = "Button 0 Timer 0"},
            {.callback = &button0_timer1_callback,  .name = "Button 0 Timer 1"},
                {.callback = &button0_timer2_callback,  .name = "Button 0 Timer 2"}},
        {{.callback = &button1_timer0_callback,  .name = "Button 1 Timer 0"},
            {.callback = &button1_timer1_callback,  .name = "Button 1 Timer 1"},
                {.callback = &button1_timer2_callback,  .name = "Button 1 Timer 2"}},
        {{.callback = &button2_timer0_callback,  .name = "Button 2 Timer 0"},
            {.callback = &button2_timer1_callback,  .name = "Button 2 Timer 1"},
                {.callback = &button2_timer2_callback,  .name = "Button 2 Timer 2"}},
        {{.callback = &button3_timer0_callback,  .name = "Button 3 Timer 0"},
            {.callback = &button3_timer1_callback,  .name = "Button 3 Timer 1"},
                {.callback = &button3_timer2_callback,  .name = "Button 3 Timer 2"}},
        {{.callback = &button4_timer0_callback,  .name = "Button 4 Timer 0"},
            {.callback = &button4_timer1_callback,  .name = "Button 4 Timer 1"},
                {.callback = &button4_timer2_callback,  .name = "Button 4 Timer 2"}},
        {{.callback = &button5_timer0_callback,  .name = "Button 5 Timer 0"},
            {.callback = &button5_timer1_callback,  .name = "Button 5 Timer 1"},
                {.callback = &button5_timer2_callback,  .name = "Button 5 Timer 2"}}
    };
    ESP_ERROR_CHECK(esp_timer_create(&displayTimer_args, &displayTimer_handler));
    for (uint8_t i = 0; i < NUM_OF_BUTTONS; i++)
        for (uint8_t j = 0; j < NUM_OF_TIMERS; j++)
            ESP_ERROR_CHECK(esp_timer_create(&button_timer_args[i][j], &button_timer_handler[i][j]));
    
    /*************************************Configuración Interrupciones GPIO*****************************************************/
    for (uint8_t i = 0; i < NUM_OF_BUTTONS; i++){
        gpio_set_direction(button[i], GPIO_MODE_INPUT);
        gpio_set_pull_mode(button[i], GPIO_PULLUP_ONLY);
        gpio_set_intr_type(button[i], GPIO_INTR_ANYEDGE);  
    }
    interrutCommandsQueue = xQueueCreate(10, sizeof(command2send));
    gpio_install_isr_service(0);
    gpio_isr_handler_add(button[0], button0_interrupt_handler, (void *)button[0]);
    gpio_isr_handler_add(button[1], button1_interrupt_handler, (void *)button[1]);
    gpio_isr_handler_add(button[2], button2_interrupt_handler, (void *)button[2]);
    gpio_isr_handler_add(button[3], button3_interrupt_handler, (void *)button[3]);
    gpio_isr_handler_add(button[4], button4_interrupt_handler, (void *)button[4]);
    gpio_isr_handler_add(button[5], button5_interrupt_handler, (void *)button[5]);
    /*****************************************Configuración 7 segmentos*********************************************************/
    for (uint8_t i = 0; i < 7; i++) gpio_set_direction(sevSegPIN[i], GPIO_MODE_OUTPUT);
    //Prueba de display//
    for (uint8_t i = 0; i < 7; i++){
        gpio_set_level(sevSegPIN[i], 1);
        vTaskDelay(200/ portTICK_PERIOD_MS);
        gpio_set_level(sevSegPIN[i], 0);
    }
    printNumTo7Seg(0, sevSegPIN);
    if(!esp_timer_is_active((displayTimer_handler))){
        ESP_ERROR_CHECK(esp_timer_start_once(displayTimer_handler, TIME_DISPLAYING));
    } else {
        ESP_ERROR_CHECK(esp_timer_restart(displayTimer_handler, TIME_DISPLAYING));
    }
    /*********************************************Configuración Task 1**********************************************************/
    xTaskCreate(rmtControl, "Administrador de RMT", 2048, NULL, 1, NULL);
    while (true)
    {
        vTaskDelay(1000/ portTICK_PERIOD_MS);
    }
}
