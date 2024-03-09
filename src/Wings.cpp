#include "pros/adi.hpp"
#include "Wings.hpp"

Wings::Wings(uint8_t const wingsPort1, uint8_t const wingsPort2, uint8_t const hangPort, uint8_t const hangPort2) 
: wings1 {wingsPort1} 
, wings2 {wingsPort2}
, hang(hangPort)
, hang2(hangPort2)
{}

void Wings::activateWings (bool wingsActive) {
    wings1.set_value(wingsActive);
    wings2.set_value(wingsActive);
}

void Wings::activateHang (bool hangActive) {
    hang.set_value(hangActive);
    hang2.set_value(hangActive);
}