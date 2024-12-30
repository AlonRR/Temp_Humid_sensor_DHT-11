#include <Arduino.h>

struct one_wire_read
{
private:
    /* data */
    byte dat[5];
    int pin;

public:
    one_wire_read(int pin);
    byte read_data();
    void start_read();
    bool checksum();
    byte operator[](int i) { return dat[i]; }
};