/*

*/

#include "shared/TinySerializer.hpp"
#include "shared/messages.hpp"

#define SERIAL_BAUD_RATE 9600


// Integers
void respond_to_message_1(uint8_t incoming_data){

  static message_1_request_t  request_1;
  static message_1_response_t response_1;
  static serializer::Deserializer<message_1_request_t> deserializer_1(1);
  static serializer::Serializer  <message_1_response_t>  serializer_1(1);

  // Wait until we get a valid message
  if(!deserializer_1.deserialize(incoming_data, &request_1)) return;

  Serial.write(incoming_data);

  // A visual indicator that we received a message
  digitalWrite(LED_BUILTIN, HIGH);

  // Do some math on it and return the result
  response_1.i              = request_1.i;
  response_1.i_plus_one     = request_1.i +  1;
  response_1.i_minus_one    = request_1.i -  1;
  response_1.i_times_two    = request_1.i *  2;
  response_1.i_over_two     = request_1.i /  2;
  response_1.i_shift_l_two  = request_1.i << 2;
  response_1.i_shift_r_two  = request_1.i >> 2;

  // Ship the result back to the host
  serializer_1.serialize(response_1, Serial, &HardwareSerial::write);
}


// Floats
void respond_to_message_2(uint8_t incoming_data){

  static message_2_request_t  request_2;
  static message_2_response_t response_2;
  static serializer::Deserializer<message_2_request_t> deserializer_2(2);
  static serializer::Serializer  <message_2_response_t>  serializer_2(2);

  // Wait until we get a valid message
  if(!deserializer_2.deserialize(incoming_data, &request_2)) return;

  Serial.write(incoming_data);

  // A visual indicator that we received a message
  digitalWrite(LED_BUILTIN, HIGH);

  // Do some math on it and return the result
  response_2.i              = request_2.i;
  response_2.i_plus_one     = request_2.i +  1;
  response_2.i_minus_one    = request_2.i -  1;
  response_2.i_times_two    = request_2.i *  2;
  response_2.i_over_two     = request_2.i /  2;

  // Ship the result back to the host
  serializer_2.serialize(response_2, Serial, &HardwareSerial::write);
}

void setup() {
  // Turn off the builtin LED
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  // Start the serial connection
  Serial.begin(SERIAL_BAUD_RATE);
  Serial.write(7);
}


void loop() {
  while(Serial.available()){
    uint8_t incoming_byte = Serial.read();
    respond_to_message_1(incoming_byte);
    respond_to_message_2(incoming_byte);
  }

  // Send a heartbeat over the connection so let the host know we're still alive
  static long last_millis = millis();
  if(millis() - last_millis > 1000){
    Serial.write(8);
    last_millis = millis();
  }
}
