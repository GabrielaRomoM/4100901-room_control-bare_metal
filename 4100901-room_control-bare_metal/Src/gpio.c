#include "gpio.h"

/*
 * @brief Inicializa un pin de un puerto GPIO con la configuración indicada.
 * 
 * @param GPIO           Puerto GPIO (ej. GPIOA, GPIOB...).
 * @param pin            Número de pin (0 - 15).
 * @param mode           Modo del pin (00 = entrada, 01 = salida, 10 = alterno, 11 = analógico).
 * @param type           Tipo de salida (0 = push-pull, 1 = open-drain).
 * @param speed          Velocidad de conmutación (00 = baja, 01 = media, 10 = rápida, 11 = muy rápida).
 * @param pupd           Configuración de resistencias (00 = ninguna, 01 = pull-up, 10 = pull-down).
 * @param initial_value  Valor inicial del pin (0 = bajo, 1 = alto).
 */
void init_gpio(GPIO_TypeDef_t *GPIO, uint8_t pin, uint8_t mode, uint8_t type,
               uint8_t speed, uint8_t pupd, uint8_t initial_value)
{
    // Configuración del modo del pin (entrada, salida, alterno, analógico)
    GPIO->MODER &= ~( 3 << (pin*2)); // Limpia los 2 bits correspondientes al pin
    GPIO->MODER |=(mode << (pin*2)); // Escribe el nuevo modo

    // Configuración del tipo de salida (push pull, open-drain)
    GPIO->TYPER &= ~(1 << pin); // Limpia el bit correspondiente al pin
    GPIO->TYPER |= (type << pin); // Escribe el tipo deseado

    // Configuración de la velocidad de salida
    GPIO->SPEEDR &= ~(3 << (pin*2)); // Limpia los 2 bits correspondientes al pin
    GPIO->SPEEDR |= (speed << (pin*2)); // Escribe la velocidad

    // Configuración de resistencias pull-up/pull-down
    GPIO->PUPDR &= ~(3 << (pin*2)); // Limpia los 2 bits correspondientes al pin
    GPIO->PUPDR |= (pupd << (pin*2)); // Escribe la configuración deseada

    // Valor inicial del pin (solo aplica si es salida)
    GPIO->ODR &= ~(1 << pin); // Limpia el bit correspondiente
    GPIO->ODR |= (initial_value << pin); // Escribe el valor inicial
}

/*
 * @brief Pone en alto un pin (valor lógico 1).
 * 
 * @param GPIOx Puerto GPIO.
 * @param pin   Número de pin (0 - 15).
*/
void set_gpio(GPIO_TypeDef_t *GPIOx, uint8_t pin)
{
    GPIOx->ODR |= (1 << pin); // Coloca 1 en el bit correspondiente
}

/*
 * @brief Pone en bajo un pin (valor lógico 0).
 * 
 * @param GPIOx Puerto GPIO.
 * @param pin   Número de pin (0 - 15).
*/
void clear_gpio(GPIO_TypeDef_t *GPIOx, uint8_t pin)
{
    GPIOx ->ODR &= ~(1 << pin); // Coloca en 0 el bit correspondiente
}

/*
 * @brief Lee el estado de un pin (entrada digital).
 * 
 * @param GPIOx Puerto GPIO.
 * @param pin   Número de pin (0 - 15).
 * @return uint8_t Retorna 1 si el pin está en nivel alto, 0 si está en nivel bajo.
*/
uint8_t read_gpio(GPIO_TypeDef_t *GPIOx, uint8_t pin)
{
    if((GPIOx -> IDR & (1<< pin)) == 0){ 
        // Si el bit leído es 0 -> retorna 1
        return 1;
    }
    // Si el bit leído es distinto de 0 -> retorna 0
    return 0;
}

void gpio_setup_pin(GPIO_TypeDef_t *GPIOx, uint8_t pin, uint8_t mode, uint8_t af)
{
    // Configurar modo del pin (00 entrada, 01 salida, 10 alterno, 11 analógico)
    GPIOx->MODER &= ~(0x3U << (pin * 2));
    GPIOx->MODER |=  (mode & 0x3U) << (pin * 2);

    // Si el modo es alterno (10 = 2), configurar AFRL o AFRH
    if (mode == 0x2) {
        if (pin < 8) {
            GPIOx->AFRL &= ~(0xFU << (pin * 4));
            GPIOx->AFRL |=  (af & 0xFU) << (pin * 4);
        } else {
            GPIOx->AFRH &= ~(0xFU << ((pin - 8) * 4));
            GPIOx->AFRH |=  (af & 0xFU) << ((pin - 8) * 4);
        }
    }
}