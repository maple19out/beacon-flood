#include "frame.h"
#include <string.h>
#include <stdlib.h>

static const uint8_t tagged_param[] = {
    0x01, 0x04, 0x82, 0x84, 0x8b, 0x96, 0x03, 0x01,
    0x08, 0x04, 0x06, 0x01, 0x02, 0x00, 0x00, 0x00,
    0x00, 0x05, 0x04, 0x00, 0x01, 0x00, 0x00
};

void Frame::set_radiotap_header(int length)
{
    ieee80211_radiotap_header radiotap_header;
    memset(&radiotap_header, 0, sizeof(radiotap_header));
    radiotap_header.it_len = length;
    radiotap_header.it_present = 0x00008004;

    memcpy(buf, &radiotap_header, length);
    buf[8] = 0x2; buf[9] = 0x0; buf[10] = 0x18; buf[11] = 0x0;
    size += length;
}

void Frame::set_beaconframe()
{
    ieee80211_beacon_frame_header beacon_header;
    beacon_header.frame_control = 0x0080;
    beacon_header.duration = 0;
    beacon_header.DA[0] = 0xff;
    beacon_header.DA[1] = 0xff;
    beacon_header.DA[2] = 0xff;
    beacon_header.DA[3] = 0xff;
    beacon_header.DA[4] = 0xff;
    beacon_header.DA[5] = 0xff;

    memcpy(buf + size, &beacon_header, sizeof(beacon_header));
    size += sizeof(beacon_header);

    ieee80211_beacon_frame_body beacon_body;
    beacon_body.Timestamp = 0;
    beacon_body.Beacon_interval = 0x64;
    beacon_body.Capability_Info = 0x0001;

    memcpy(buf + size, &beacon_body, 12);
    size += 12;
}

void Frame::set_ssid(std::string &ssid)
{
    buf[size++] = 0;
    buf[size++] = ssid.length();

    memcpy(buf + size, ssid.c_str(), ssid.length());
    size += ssid.length();

    memcpy(buf + size, tagged_param, sizeof(tagged_param));
    size += sizeof(tagged_param);
}

void Frame::randomize_bssid(void)
{
    for (int i = 0; i < 6; i++)
        buf[i + 0x16] = buf[i + 0x16 + 6] = rand() % 0x100;
}
