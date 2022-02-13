#include <stdint.h>
#include <string>
#include "wireless.h"

#ifndef FRAME_H
#define FRAME_H


struct Frame
{
    uint8_t buf[256];
    int size;

    void set_radiotap_header(int length);
    void set_beaconframe(void);
    void set_ssid(std::string& ssid);
    void randomize_bssid(void);
};

#endif // FRAME_H
