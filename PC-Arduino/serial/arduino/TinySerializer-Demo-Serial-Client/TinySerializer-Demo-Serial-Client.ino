/*

*/

#include "TinySerializer.hpp"
#include "messages.hpp"

#define SERIAL_BAUD_RATE 9600

message_1_request_t  request_1;
message_1_response_t response_1;
serializer::Deserializer<message_1_request_t> deserializer_1(1);
serializer::Serializer  <message_1_response_t>  serializer_1(1);

void setup() {
  // Turn off the builtin LED
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  // Start the serial connection
  Serial.begin(SERIAL_BAUD_RATE);
  // Print something to let the host know we're alive
  Serial.write(42);

  // Wait until we get a valid request object from the host
  for(int i = 0; i < sizeof(message_1_request_t)+1024; i++) {
    if(deserializer_1.deserialize(Serial.read(), &request_1)){
      // Use the LED to notify us if the message has been understood correctly
      digitalWrite(LED_BUILTIN, HIGH);
      break;
    }
    while(!Serial.available());
  }

  // Simpler than the block above but blocks forever
  // while(!deserializer_1.deserialize(Serial.read(), &request_1));
  


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

void loop() {
}
