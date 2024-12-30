#include "one_wire_read.hpp"

one_wire_read::one_wire_read(int pin)
{
    this->pin = pin;
    pinMode(pin, OUTPUT);
}

byte one_wire_read::read_data()
{
    byte i = 0;
    byte result = 0;
    for (i = 0; i < 8; i++)
    {
        while (digitalRead(pin) == LOW)
            ;                  // wait 50us
        delayMicroseconds(30); // The duration of the high level is judged to determine whether the data is '0' or '1'
        if (digitalRead(pin) == HIGH)
            result |= (1 << (8 - i)); // High in the former, low in the post
        while (digitalRead(pin) == HIGH)
            ; // Data '1', waiting for the next bit of reception
    }
    return result;
}

void one_wire_read::start_read()
{
    digitalWrite(pin, LOW); // Pull down the bus to send the start signal
    delay(30);              // The delay is greater than 18 ms so that DHT 11 can detect the start signal
    digitalWrite(pin, HIGH);
    delayMicroseconds(40); // Wait for DHT11 to respond
    pinMode(pin, INPUT);
    while (digitalRead(pin) == HIGH)
        ;
    delayMicroseconds(80); // The DHT11 responds by pulling the bus low for 80us;

    if (digitalRead(pin) == LOW)
        delayMicroseconds(80);  // DHT11 pulled up after the bus 80us to start sending data;
    for (int i = 0; i < 5; i++) // Receiving temperature and humidity data, check bits are not considered;
        dat[i] = read_data();
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH); // After the completion of a release of data bus, waiting for the host to start the next signal
}

bool one_wire_read::checksum()
{
    if (dat[4] == dat[0] + dat[1] + dat[2] + dat[3])
        return true;
    return false;
}
