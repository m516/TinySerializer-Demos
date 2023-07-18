#include <serial/serial.h>
#include "messages.hpp"
#include "TinySerializer.hpp"
#include <iostream>
#include <thread>


namespace connection{
    // Open a serial connection
    serial::Serial my_serial("/dev/ttyACM0", 9600, serial::Timeout::simpleTimeout(10000));
    void write_byte(uint8_t byte){
        my_serial.write(&byte, 1);
        // std::cout << "Wrote byte: " << (int)byte << std::endl;
    }
}

int main(){
    using namespace connection;

    // Let the Arduino wake up
    std::cout << "Waiting for the Arduino to wake up..." << std::endl;
    while(!my_serial.available()) std::this_thread::sleep_for(std::chrono::milliseconds(10));

    // Send an integer to the Arduino
    message_1_request_t  request_1;
    message_1_response_t response_1;
    serializer::Serializer   <message_1_request_t>   serializer_1(1);
    serializer::Deserializer<message_1_response_t> deserializer_1(1);

    // Set the request payload
    request_1.i = 42;
    std::cout << "Sending request: " << std::endl
              << "  i:             " << request_1.i << std::endl;
    
    // Send the request
    serializer_1.serialize<void>(request_1, &write_byte);

    // Wait until we get a valid response object from the peripheral
    uint8_t incoming_byte;
    do {
        my_serial.read(&incoming_byte, 1);
        // std::cout << "Read byte: " << (int)incoming_byte << std::endl;
    }
    while(!deserializer_1.deserialize(incoming_byte, &response_1));

    // Print the result
    std::cout << "Received response: " << std::endl
              << "  i:             " << response_1.i << std::endl
              << "  i_plus_one:    " << response_1.i_plus_one << std::endl
              << "  i_minus_one:   " << response_1.i_minus_one << std::endl
              << "  i_times_two:   " << response_1.i_times_two << std::endl
              << "  i_over_two:    " << response_1.i_over_two << std::endl
              << "  i_shift_l_two: " << response_1.i_shift_l_two << std::endl
              << "  i_shift_r_two: " << response_1.i_shift_r_two << std::endl;

    // Close the serial connection
    my_serial.close();

    return 0;
}