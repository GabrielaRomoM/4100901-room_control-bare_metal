// gpio.h
#ifndef GPIO_H
#define GPIO_H
#include <stdint.h>

// --- Definición de GPIO ----------------------------------------------

// Estructura que representa los registros de un puerto GPIO
typedef struct {
    volatile uint32_t MODER; // Registro de configuración de modo (entrada, salida, analógico)
    volatile uint32_t TYPER; // Registro de tipo de salida (push-pull u open drain)
    volatile uint32_t SPEEDR; // Registro de velocidad de salida (baja, media, alta, muy alta)
    volatile uint32_t PUPDR; // Registro de resistencias pull-up, pull-down
    volatile uint32_t IDR; // Registro de entrada (lectura de estado de pines)
    volatile uint32_t ODR; // Registro de salida (escritura de estado de pines)
    volatile uint32_t AFRL; // Registro de función alternativa para pines 0-7
    volatile uint32_t AFRH; // Registro de función alternativa para pines 8-15
} GPIO_TypeDef_t;

// --- Direcciones base de los GPIOs ----------------------------------

// Cada puerto GPIO está ubicado en una dirección de memoria específica (mapeo de memoria del MCU)
#define GPIOA ((GPIO_TypeDef_t *)0x48000000U)
#define GPIOB ((GPIO_TypeDef_t *)0x48000400U)
#define GPIOC ((GPIO_TypeDef_t *)0x48000800U)
#define GPIOD ((GPIO_TypeDef_t *)0x48000C00U)
#define GPIOE ((GPIO_TypeDef_t *)0x48001000U)
#define GPIOF ((GPIO_TypeDef_t *)0x48001400U)
#define GPIOG ((GPIO_TypeDef_t *)0x48001800U)
#define GPIOH ((GPIO_TypeDef_t *)0x48001C00U)

#define LD2_PIN     5U  // Pin PA5 (LED)
#define B1_PIN      13U   

void init_gpio(GPIO_TypeDef_t *GPIOx,
               uint8_t pin,
               uint8_t mode,
               uint8_t type,
               uint8_t speed,
               uint8_t pupd,
               uint8_t initial_value);

void set_gpio(GPIO_TypeDef_t *GPIOx, uint8_t pin);
void clear_gpio(GPIO_TypeDef_t *GPIOx, uint8_t pin);
uint8_t read_gpio(GPIO_TypeDef_t *GPIOx, uint8_t pin);
void gpio_setup_pin(GPIO_TypeDef_t *GPIOx, uint8_t pin, uint8_t mode, uint8_t af);

#endif