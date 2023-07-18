/*
Common messages that are shared between the Arduino and the PC
*/

#pragma once





// message_1_request_t: an integer
typedef struct{
  uint16_t i;
} message_1_request_t;

// message_1_response_t: operations on that integer
typedef struct{
  uint16_t i;
  uint16_t i_plus_one;
  uint16_t i_minus_one;
  uint16_t i_times_two;
  uint16_t i_over_two;
  uint16_t i_shift_l_two;
  uint16_t i_shift_r_two;
} message_1_response_t;

// message_2_request_t: a float
typedef struct{
  float i;
} message_2_request_t;

// message_2_response_t: operations on that float
typedef struct{
  float i;
  float i_plus_one;
  float i_minus_one;
  float i_times_two;
  float i_over_two;
} message_2_response_t;

