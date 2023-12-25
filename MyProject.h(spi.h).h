#define SPI_MODE0 0x00000000
#define SPI_MODE1 0x00000001
#define SPI_MODE2 0x00000002
#define SPI_MODE3 0x00000003
#define LSBFIRST 0
#define MSBFIRST 1
#define fpclk1 1
#define fpclk2 2
#define fpclk3 3
#define fpclk4 4
#define fpclk5 5
#define fpclk6 6
#define fpclk7 7
#define etbit  0
#define sxtntbit 1
void setDataMode(int mode, int clockMode);
void begin() ;
void setClockDivider(int freq_divider);
void setBitOrder(int byteOrder);
void transfer(int data);
void end() ;
int beginTransaction(int byteOrder , int dataMode,int baudRate,
int clockMode);
void endTransaction() ;