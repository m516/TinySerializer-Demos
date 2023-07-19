#include <serial/serial.h>
#include "shared/messages.hpp"
#include "shared/TinySerializer.hpp"
#include <iostream>
#include <thread>


namespace connection{
    // Open a serial connection
    serial::Serial my_serial("/dev/ttyACM0", 9600, serial::Timeout::simpleTimeout(100000));
    void write_byte(uint8_t byte){
        my_serial.write(&byte, 1);
        // std::cout << "Wrote byte: " << (int)byte << std::endl;
    }
    void wait_until_awake(){
        // Let the Arduino wake up
        std::cout << "Waiting for the Arduino to wake up..." << std::endl;
        // Wait for the Arduino to give its startup message
        while(true){
            uint8_t incoming_byte = 0;
            my_serial.read(&incoming_byte, 1);
            if(incoming_byte==7) break;
            else                 std::cout << ".";
        }
    }
}


void test_message_1(){
    using namespace connection;


    // Send an integer to the Arduino
    message_1_request_t  request_1;
    message_1_response_t response_1;
    serializer::Serializer   <message_1_request_t>   serializer_1(1);
    serializer::Deserializer<message_1_response_t> deserializer_1(1);

    // Set the request payload
    request_1.i = 42;
    std::cout << "Sending request 1 (uint16_t): " << std::endl
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

}

void test_message_2(){
    using namespace connection;
    // Send a float to the Arduino
    message_2_request_t  request_2;
    message_2_response_t response_2;
    serializer::Serializer   <message_2_request_t>   serializer_2(2);
    serializer::Deserializer<message_2_response_t> deserializer_2(2);

    // Set the request payload
    request_2.i = 3.14;
    std::cout << "Sending request 2 (float): " << std::endl
              << "  i:             " << request_2.i << std::endl;
    
    // Send the request
    serializer_2.serialize<void>(request_2, &write_byte);

    // Wait until we get a valid response object from the peripheral
    uint8_t incoming_byte;
    do {
        my_serial.read(&incoming_byte, 1);
        // std::cout << "Read byte: " << (int)incoming_byte << std::endl;
    }
    while(!deserializer_2.deserialize(incoming_byte, &response_2));

    // Print the result
    std::cout << "Received response: " << std::endl
              << "  i:             " << response_2.i << std::endl
              << "  i_plus_one:    " << response_2.i_plus_one << std::endl
              << "  i_minus_one:   " << response_2.i_minus_one << std::endl
              << "  i_times_two:   " << response_2.i_times_two << std::endl
              << "  i_over_two:    " << response_2.i_over_two << std::endl;
}

int main(){
    using namespace connection;

    // Wake up
    wait_until_awake();

    // Test integers
    test_message_1();

    // Test floats
    test_message_2();

    // Close the serial connection
    my_serial.close();
    return 0;
}