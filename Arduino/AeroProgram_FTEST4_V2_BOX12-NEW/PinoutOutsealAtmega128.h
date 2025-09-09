#ifndef PINOUTOUTSEALATMEGA128_H
#define PINOUTOUTSEALATMEGA128_H
// OUTPUT
#define R1 PIN_PA0
#define R2 PIN_PA1
#define R3 PIN_PA2
#define R4 PIN_PA3
#define R5 PIN_PA4
#define R6 PIN_PA5
#define R7 PIN_PG1
#define R8 PIN_PE3
#define R9 PIN_PC0
#define R10 PIN_PC1
#define R11 PIN_PC2
#define R12 PIN_PC3
#define R13 PIN_PC4
#define R14 PIN_PC5
#define R15 PIN_PC6
#define R16 PIN_PC7

// DIGITAL INPUT
#define S5 PIN_PD5
#define S6 PIN_PE4
#define S9 PIN_PA7
#define S10 PIN_PB7
#define S11 PIN_PE5
#define S12 PIN_PG0
#define S13 PIN_PE7
#define S14 PIN_PB4
#define S15 PIN_PA6
#define S16 PIN_PB6

// DIGITAL OUTPUT
#define S1 PIN_PF7
#define S2 PIN_PF6
#define S3 PIN_PF5
#define S4 PIN_PF4
#define S7 PIN_PF3
#define S8 PIN_PF2
#define A1 PIN_PF0
#define A2 PIN_PF1

// PIN LAIN
//komunikasi
#define SCL PIN_PD0
#define SDA PIN_PD1
#define SS PIN_PB0
#define SCK PIN_PB1
#define MOSI PIN_PB2
#define MISO PIN_PB3

#define PWM PIN_PB5 //pwm pin
#define HSC PIN_PE6

//err pin
#define ERR1 PIN_PD6
#define ERR2 PIN_PD7
#define B4 PIN_PG2
#define B3 PIN_PG3
#define B2 PIN_PG4


//KOMUNIKASI RX TX MASTER
#define RM PIN_PD2
#define TM PIN_PD3
#define DM PIN_PD4

// KOMUNIKASI RX TX SLAVE
#define RS PIN_PE0
#define TS PIN_PE1
#define DS PIN_PE2


#endif
