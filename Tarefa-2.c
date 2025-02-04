#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

#define BLUE_LED 11   // GPIO para LED Azul
#define RED_LED 12    // GPIO para LED Vermelho
#define GREEN_LED 13  // GPIO para LED Verde
#define BUTTON 5      // GPIO para o botão

volatile bool led_sequence_active = false; // Indica se a sequência está em andamento

// Callback final para desligar o último LED (verde) e permitir nova ativação
int final_stage_callback(alarm_id_t id, void *user_data) {
    gpio_put(GREEN_LED, 0);
    printf("Todos os LEDs desligados. Pronto para nova ativação.\n");
    led_sequence_active = false;
    return 0;
}

// Callback para desligar o segundo LED (vermelho)
int second_stage_callback(alarm_id_t id, void *user_data) {
    gpio_put(RED_LED, 0);
    printf("Apenas o LED Verde permanece ligado\n");
    add_alarm_in_ms(3000, final_stage_callback, NULL, false);
    return 0;
}

// Callback para desligar o primeiro LED (azul)
int first_stage_callback(alarm_id_t id, void *user_data) {
    gpio_put(BLUE_LED, 0);
    printf("Apenas os LEDs Vermelho e Verde permanecem ligados\n");
    add_alarm_in_ms(3000, second_stage_callback, NULL, false);
    return 0;
}

// Callback inicial para acionar os LEDs e iniciar a sequência
void button_pressed_callback(uint gpio, uint32_t events) {
    if (!led_sequence_active) {
        led_sequence_active = true;
        gpio_put(BLUE_LED, 1);
        gpio_put(RED_LED, 1);
        gpio_put(GREEN_LED, 1);
        printf("Todos os LEDs ligados!\n");
        add_alarm_in_ms(3000, first_stage_callback, NULL, false);
    }
}

// Callback para debounce do botão
bool debounce_callback(struct repeating_timer *t) {
    static bool last_state = true;
    bool current_state = !gpio_get(BUTTON);
    if (current_state && !last_state) {
        button_pressed_callback(BUTTON, 0);
    }
    last_state = current_state;
    return true;
}

int main() {
    stdio_init_all();
    
    gpio_init(BLUE_LED);
    gpio_set_dir(BLUE_LED, GPIO_OUT);
    gpio_put(BLUE_LED, 0);
    gpio_init(RED_LED);
    gpio_set_dir(RED_LED, GPIO_OUT);
    gpio_put(RED_LED, 0);
    gpio_init(GREEN_LED);
    gpio_set_dir(GREEN_LED, GPIO_OUT);
    gpio_put(GREEN_LED, 0);
    gpio_init(BUTTON);
    gpio_set_dir(BUTTON, GPIO_IN);
    gpio_pull_up(BUTTON);
    
    struct repeating_timer timer;
    add_repeating_timer_ms(50, debounce_callback, NULL, &timer);
    
    while (1) {
        tight_loop_contents();
    }
}
