#include "stm32f4xx.h"
#include "spi.h"
uint8_t data=0x22;
void begin() {
     RCC->AHB1ENR |= (1<<0);
    RCC->APB2ENR |= (1 << 12); // Enable the clock for SPI1
    SPI1->CR1 |= (1 << 2); // Configure in master mode
    SPI1->CR1 |= (1 << 9); // Select the slave management mode
    SPI1->CR1 |= (1 << 8); // Initialize the SPI bus

    GPIOA->MODER |= (2 << 10) | (2 << 12) | (2 << 14); // Configure the GPIO pins
   GPIOA->AFR[0] |= (5<<20)|(5<<24)|(5<<28);   // AF5(SPI1) for PA5, PA6, PA7
   SPI1->CR1 &= ~(1<<10);  // RXONLY = 0, full-duplex
    GPIOA->BSRRL |= (1<<9)<<16;
  SPI1->CR1 &= ~(1<<11);  // DFF=0, 8 bit data
}

void setDataMode(int mode, int clockMode) {

    SPI1->CR1 &= ~(1 << 1 | 1 << 0); // Clear the bits
    SPI1->CR1 |= (clockMode << 0); // Set the clock polarity and phase
    SPI1->CR1 |= (mode << 6); // Select data frame format
}

void setClockDivider(int freq_divider) {
    SPI1->CR1 &= ~(7 << 3); // Clear the bits
    SPI1->CR1 |= ((freq_divider - 1) << 3); // Change the clock frequency divider
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

int beginTransaction(int byteOrder , int dataMode, int baudRate,int
clockMode) {
   while(1){

    setBitOrder(byteOrder);
    setDataMode(dataMode, clockMode);
    setClockDivider(baudRate);
      transfer(data);

   }
}
endTransaction()
{}void delay(int time) {
    int i;
    for (i = 0; i < time; i++);
}


int main(){
while(1){
      begin();
   beginTransaction(1,1,4,SPI_MODE3);
      transfer(0x01); // Turn on the LED
delay(3000000); // Delay for 3 seconds
transfer(0x00); // Turn off the LED
 delay(3000000); // Delay for 3 seconds
   endTransaction();
      end();
   }}