#include "stm32f401xx.h"

void begin(uint8_t addr) {
    RCC->APB1ENR |= (1 << 14); // Enable the clock for SPI2
    SPI2->CR1 &= ~(1 << 2); // Configure in slave mode
    SPI2->CR1 |= (1 << 9); // Select the slave management mode
    SPI2->CR1 |= (1 << 8); // Initialize the SPI bus
    GPIOB->MODER |= (1 << 26); // Configure the GPIO pins
    SPI2->CR1 |= (1 << 6); // Enables the SPI bus
    SPI2->CR2 |= (1 << 6); // Enables the RXNE interrupt
    SPI2->CR1 |= (1 << 6); // Enables the SPI bus
    SPI2->DR = 0x00; // Clear the data register
}

void end() {
    SPI2->CR1 &= ~(1 << 6); // Disables the SPI bus
}

void SPI2_IRQHandler() {
    if (SPI2->SR & (1 << 0)) {
        uint8_t data = SPI2->DR; // Read the received data
        if (data == 0x01) {
            GPIOB->ODR |= (1 << 13); // Turn on the LED
        } else if (data == 0x00) {
            GPIOB->ODR &= ~(1 << 13); // Turn off the LED
        }
    }
}

int main() {
while(1){
    begin(0x08);


SPI2_IRQHandler()
    end();}
    return 0;
}