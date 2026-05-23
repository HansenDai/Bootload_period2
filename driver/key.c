#include <stdbool.h>
#include <stddef.h>
#include "stm32f4xx.h"
#include "stm32f4xx_ll_gpio.h"
#include "key.h"
#include "key_desc.h"

// KEY1: PA0
// KEY2: PC4
// KEY3: PC5

void key_init(key_desc_t key)
{
    LL_GPIO_InitTypeDef gpio_init;

    LL_GPIO_StructInit(&gpio_init);
    gpio_init.Pin = key->pin;
    gpio_init.Mode = LL_GPIO_MODE_INPUT;
    gpio_init.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;
    gpio_init.Pull = key->pull;
    LL_GPIO_Init(key->port, &gpio_init);
}

bool key_read(key_desc_t key)
{
    return (LL_GPIO_IsInputPinSet(key->port, key->pin) != 0U) == (key->press_level != 0U);
}
