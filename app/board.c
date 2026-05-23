#include <stdio.h>
#include "stm32f4xx.h"
#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_gpio.h"
#include "stm32f4xx_ll_usart.h"
#include "key.h"
#include "key_desc.h"
#include "led.h"
#include "led_desc.h"

void board_lowlevel_init(void)
{
    LL_AHB1_GRP1_EnableClock(
        LL_AHB1_GRP1_PERIPH_GPIOA |
        LL_AHB1_GRP1_PERIPH_GPIOB |
        LL_AHB1_GRP1_PERIPH_GPIOC |
        LL_AHB1_GRP1_PERIPH_GPIOD |
        LL_AHB1_GRP1_PERIPH_GPIOE |
        LL_AHB1_GRP1_PERIPH_DMA1 |
        LL_AHB1_GRP1_PERIPH_DMA2);
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART3 | LL_APB1_GRP1_PERIPH_TIM6);
}

int fputc(int ch, FILE *f)
{
    (void)f;

    LL_USART_TransmitData8(USART1, (uint8_t)ch);
    while (!LL_USART_IsActiveFlag_TXE(USART1))
        ;
    return ch;
}

static struct led_desc _led1 = {GPIOE, LL_GPIO_PIN_9, GPIO_PIN_RESET, GPIO_PIN_SET};
static struct led_desc _led2 = {GPIOB, LL_GPIO_PIN_0, GPIO_PIN_RESET, GPIO_PIN_SET};
static struct led_desc _led3 = {GPIOB, LL_GPIO_PIN_1, GPIO_PIN_RESET, GPIO_PIN_SET};
led_desc_t led1 = &_led1;
led_desc_t led2 = &_led2;
led_desc_t led3 = &_led3;

static struct key_desc _key1 = {GPIOA, LL_GPIO_PIN_0, LL_GPIO_PULL_DOWN, 1U};
static struct key_desc _key2 = {GPIOC, LL_GPIO_PIN_4, LL_GPIO_PULL_DOWN, 1U};
static struct key_desc _key3 = {GPIOC, LL_GPIO_PIN_5, LL_GPIO_PULL_DOWN, 1U};
key_desc_t key1 = &_key1;
key_desc_t key2 = &_key2;
key_desc_t key3 = &_key3;
