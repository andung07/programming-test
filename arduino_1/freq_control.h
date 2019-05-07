#ifndef FREQ_CONTROL
#define FREQ_CONTROL

/*
Reference:
Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf, page 33
Assume a 16MHz clock is used
Valid parameter: 1 - 16
*/

#define MAX_FREQ 16

typedef enum _clock_freq
{
  CLOCK_1MHz = 1,
  CLOCK_2MHz = 2,
  CLOCK_4MHz = 4,
  CLOCK_8MHz = 8,
  CLOCK_16MHz = 16,
  CLOCK_32MHz = 32
} clock_freq;

inline int SetFreq(clock_freq target_freq)
{
  int return_value = 0;

  // Disabling interrupt
  cli();

  uint8_t target_scale = MAX_FREQ / target_freq;

  if (target_scale <= MAX_FREQ)
  {
    // _BV(n) => 1 << n
    // CLKPR = Clock Prescale Register

    // Enabling change by setting CKLPCE to 1
    CLKPR = _BV(CLKPCE);

    // Set the CLKPS3..0 values
    CLKPR = target_scale;

    // CLKPCE will be cleared automatically

    return_value = 0;
  }

  else
  {
    return_value = -1;
  }

  // Enabling interrupt
  sei();

  return return_value;
}

#endif
