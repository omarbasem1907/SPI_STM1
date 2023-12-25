#include "stm32f4xx.h"
#include "spi.h"
uint8_t data=0x0222;
void begin() {
     RCC->AHB1ENR |= (1<<0);   // Enable  gpioa
    RCC->APB2ENR |= (1 << 12); // Enable the clock for SPI1
    SPI1->CR1 |= (1 << 2); // Configure in master mode
    SPI1->CR1 |= (1 << 9); // Select the slave management mode
    SPI1->CR1 |= (1 << 8); // Initialize the SPI bus

    GPIOA->MODER |= (2 << 10) | (2 << 12) | (2 << 14); // Configure the GPIO pins
   GPIOA->AFR[0] |= (5<<20)|(5<<24)|(5<<28);   // AF5(SPI1) for PA5, PA6, PA7
   SPI1->CR1 &= ~(1<<10);  // RXONLY = 0, full-duplex
    GPIOA->BSRRL |= (1<<9)<<16;
    SPI1->CR1 |= (1 << 6);
}

void setDataMode(int mode, int clockMode) {

    SPI1->CR1 &= ~(1 << 1 | 1 << 0); // Clear the bits
    SPI1->CR1 |= (clockMode << 0); // Set the clock polarity and phase
    SPI1->CR1 |= (mode << 11); // Select data frame format
}

void setClockDivider(int freq_divider) {
    SPI1->CR1 &= ~(7 << 3); // Clear the bits
    SPI1->CR1 |= (freq_divider  << 3); // Change the clock frequency divider
}

void setBitOrder(int byteOrder) {

    SPI1->CR1 &= ~(1 << 7); // Clear the bit
   if (byteOrder == LSBFIRST){
    SPI1->CR1 |= (1 << 7); // Set the byte order
   }
   else
   { SPI1->CR1 &= ~(1 << 7); // Set the byte order

      }
}

void transfer(int data) {
    while (!(SPI1->SR & (1 << 1))); // Wait until TXE is set
    SPI1->DR = data; // Send the data
    while (!(SPI1->SR & (1 << 0))); // Wait until RXNE is set
    return SPI1->DR; // Return the received data
}

void end() {
    SPI1->CR1 &= ~(1 << 6); // Disables the SPI bus
}

int beginTransaction(int byteOrder , int dataMode, int baudRate,int clockMode) {
   while(1){

    setBitOrder(byteOrder);
    setDataMode(dataMode, clockMode);
    setClockDivider(baudRate);
      transfer(data);

   }
}
void endTransaction(){

   }
int main(){
while(1){
      begin();
   beginTransaction(MSBFIRST,sxtntbit,fpclk4,SPI_MODE3);
      transfer(data);
   endTransaction();
      end();
   }}