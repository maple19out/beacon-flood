#include <stdint.h>
#include <string>
#include "wireless.h"

#ifndef FRAME_H
#define FRAME_H

struct Frame
{
    struct ieee80211_radiotap_header radio;
    struct ieee80211_beacon_frame_header beacon_header;
    struct ieee80211_beacon_frame_body beacon_body;
    uint8_t tagged_buf[128];
    int size;

    void set_radiotap_header();
    void set_beaconframe();
    void set_ssid(std::string& ssid);
    void randomize_bssid();
};

#endif // FRAME_H
