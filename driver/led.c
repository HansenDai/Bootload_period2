#include <stdbool.h>
#include <stdint.h>
#include "stm32f4xx_ll_gpio.h"
#include "led_desc.h"
#include "led.h"

static void led_write_state(led_desc_t led, GPIO_PinState state)
{
    if (state == GPIO_PIN_SET)
    {
        LL_GPIO_SetOutputPin(led->Port, led->Pin);
    }
    else
    {
        LL_GPIO_ResetOutputPin(led->Port, led->Pin);
    }
}

void led_init(led_desc_t led)
{
    LL_GPIO_InitTypeDef gpio_init;

    LL_GPIO_StructInit(&gpio_init);
    gpio_init.Pin = led->Pin;
    gpio_init.Mode = LL_GPIO_MODE_OUTPUT;
    gpio_init.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
    gpio_init.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    gpio_init.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(led->Port, &gpio_init);

    led_write_state(led, led->OffState);
}

void led_set(led_desc_t led, bool onoff)
{
    led_write_state(led, onoff ? led->OnState : led->OffState);
}

void led_on(led_desc_t led)
{
    led_write_state(led, led->OnState);
}

void led_off(led_desc_t led)
{
    led_write_state(led, led->OffState);
}
