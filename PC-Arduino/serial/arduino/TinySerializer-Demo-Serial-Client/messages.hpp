/*
Common messages that are shared between the Arduino and the PC
*/

#pragma once





// message_1_request_t: an integer
typedef struct{
  uint16_t i;
} message_1_request_t;

// message_1_response_t: an integer
typedef struct{
  uint16_t i;
  uint16_t i_plus_one;
  uint16_t i_minus_one;
  uint16_t i_times_two;
  uint16_t i_over_two;
  uint16_t i_shift_l_two;
  uint16_t i_shift_r_two;
} message_1_response_t;

