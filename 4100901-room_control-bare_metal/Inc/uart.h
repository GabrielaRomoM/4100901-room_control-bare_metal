// uart.h
#include <stdint.h>
#include "gpio.h" // Librería GPIO existente
#include "rcc.h"  // Librería RCC existente

// Definición de la estructura USART 
typedef struct {
    volatile uint32_t CR1; // Registro de control 1: habilitación de USART, TX, RX, interrupciones, paridad, tamaño de palabra, etc.
    volatile uint32_t CR2; // Registro de control 2: configuración de bits de parada, modo síncrono, LIN, etc.
    volatile uint32_t CR3; // Registro de control 3: control adicional (DMA, control de flujo CTS/RTS, Smartcard, etc.)
    volatile uint32_t BRR; // Baud Rate Register: define el divisor de reloj para generar la velocidad en baudios
    volatile uint32_t GTPR; // Guard time & Prescaler: usado en Smartcard y configuraciones especiales.
    volatile uint32_t RTOR; // Receiver Timeout: define un tiempo de espera máximo para recepción.
    volatile uint32_t RQR; // Request Register: permite solicitar ciertas operaciones (ej: reset RX, reset TX).
    volatile uint32_t ISR; // Interrupt & Status Register: contiene banderas de estado e interrupción (TXE, RXNE, ORE, etc.).
    volatile uint32_t ICR; // Interrupt flag Clear Register: permite limpiar banderas de error o interrupción.
    volatile uint32_t RDR; // Receive Data Register: contiene el dato recibido (se lee aquí cuando RXNE está activo).
    volatile uint32_t TDR; // Transmit Data Register: aquí se escribe el dato a enviar (cuando TXE está disponible).
} USART_TypeDef;

#define USART1 ((USART_TypeDef *)0x40013800U)
#define USART2 ((USART_TypeDef *)0x40004400U)
#define USART3 ((USART_TypeDef *)0x40004800U)

// Constantes
#define BAUD_RATE     115200U
#define HSI_FREQ      4000000U

// Prototipos de funciones
void init_gpio_uart(void);
void init_uart(void);
void uart_send(char c);
char uart_receive(void);
void uart_send_string(const char *str);

// Direcciones base comunes



