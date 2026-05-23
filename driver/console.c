#include <stdint.h>
#include "stm32f4xx.h"
#include "stm32f4xx_ll_gpio.h"
#include "stm32f4xx_ll_usart.h"
#include "console.h"

static void console_io_init(void)
{
    LL_GPIO_InitTypeDef gpio_init;

    LL_GPIO_StructInit(&gpio_init);
    gpio_init.Pin = LL_GPIO_PIN_9 | LL_GPIO_PIN_10;
    gpio_init.Mode = LL_GPIO_MODE_ALTERNATE;
    gpio_init.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
    gpio_init.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    gpio_init.Pull = LL_GPIO_PULL_NO;
    gpio_init.Alternate = LL_GPIO_AF_7;
    LL_GPIO_Init(GPIOA, &gpio_init);
}

static void console_usart_init(void)
{
    LL_USART_InitTypeDef usart_init;

    LL_USART_StructInit(&usart_init);
    usart_init.BaudRate = 115200U;
    usart_init.DataWidth = LL_USART_DATAWIDTH_8B;
    usart_init.StopBits = LL_USART_STOPBITS_1;
    usart_init.Parity = LL_USART_PARITY_NONE;
    usart_init.TransferDirection = LL_USART_DIRECTION_TX_RX;
    usart_init.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
    usart_init.OverSampling = LL_USART_OVERSAMPLING_16;

    LL_USART_Disable(USART1);
    LL_USART_Init(USART1, &usart_init);
    LL_USART_ConfigAsyncMode(USART1);
    LL_USART_Enable(USART1);
}

void console_init(void)
{
    console_io_init();
    console_usart_init();
}

void console_write(const char str[], uint32_t length)
{
    for (uint32_t i = 0; i < length; i++)
    {
        while (!LL_USART_IsActiveFlag_TXE(USART1));
        LL_USART_TransmitData8(USART1, (uint8_t)str[i]);
    }
}
