/****************************************************************
* Author: T. LUM and R. MARTIN
* CPEG222 DemoProgram2, 8/29/26
* NucleoF466ZE CMSIS STM32F4xx example Demo2 
* Toggle Blue LED (LD2) on Nucleo-F446ZE using USR BTN (PC13)
****************************************************************/
#include "stm32f4xx.h"// Include the STM32F4xx CMSIS header file
#include <stdbool.h> // Include stdbool.h for boolean type
#define LED_PIN 7 // Assuming LED is connected to GPIOB pin 7
#define LED_PORT GPIOB
#define BTN_PIN 13 // Assuming button is connected to GPIOC pin 13
#define BTN_PORT GPIOC
bool LEDstate = false; // Variable to keep track of LED state
bool BTNlock = false; // Variable to implement button debounce

void delay(volatile uint32_t count) { // Simple delay function
  while (count--) {// This function will block for a while, creating a delay
  }
}
int main(void) {
  // 1. Enable clock for GPIO port B and C
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN;
  // 2. Configure GPIO pin 13 (USR BTN on Nucleo-F446ZE) as input
  BTN_PORT->MODER &= ~(0x3 << (BTN_PIN * 2)); // Clear mode bits
  BTN_PORT->MODER |= (0x0 << (BTN_PIN * 2)); // Set as General purpose input mode
  // 3. Configure GPIO pin 7 (LED LD2 on Nucleo-F446ZE) as output
  LED_PORT->MODER &= ~(0x3 << (LED_PIN * 2)); // Clear mode bits
  LED_PORT->MODER |= (0x1 << (LED_PIN * 2)); // Set as General purpose output mode
  while (1) { // Main loop to toggle the LED continuously
    if ((BTN_PORT->IDR & (1 << BTN_PIN)) && !BTNlock) { // Check if button is pressed and not locked
      LEDstate = !LEDstate; // Toggle LED state
      if (LEDstate) {
        LED_PORT->BSRR |= (1 << LED_PIN); // Turn on the LED (LD2)
      } else {
        LED_PORT->BSRR |= (1 << (LED_PIN + 16)); // Turn off the LED (LD2)
      }
      BTNlock = true; // Lock the button to prevent multiple toggles
    } else if (!(BTN_PORT->IDR & (1 << BTN_PIN))) { // Check if button is released
      BTNlock = false; // Unlock the button
    }
  }
  return(0);
}
