#include "frame.h"
#include <string.h>
#include <stdlib.h>

/* sample beacon flooded packet captured from wireshark */
static const uint8_t tagged_param[] = {
    0x01, 0x04, 0x82, 0x84, 0x8b, 0x96, 0x03, 0x01,
    0x08, 0x04, 0x06, 0x01, 0x02, 0x00, 0x00, 0x00,
    0x00, 0x05, 0x04, 0x00, 0x01, 0x00, 0x00
};

void Frame::set_radiotap_header()
{
    radio.it_pad = radio.it_present = radio.it_version = 0;
    radio.it_len = 0x8;
    size += radio.it_len;
}

void Frame::set_beaconframe()
{
    beacon_header.frame_control = 0x0080;
    beacon_header.duration = 0;
    beacon_header.DA[0] = 0xff;
    beacon_header.DA[1] = 0xff;
    beacon_header.DA[2] = 0xff;
    beacon_header.DA[3] = 0xff;
    beacon_header.DA[4] = 0xff;
    beacon_header.DA[5] = 0xff;

    size += sizeof(beacon_header);

    beacon_body.Timestamp = 0;
    beacon_body.Beacon_interval = 0x64;
    beacon_body.Capability_Info = 0x0001;

    /* size of Timestamp(8) + Beacon_interval(2) + Capability_Info(2) */
    size += 12;
}

void Frame::set_ssid(std::string &ssid)
{
    int length = 0;
    tagged_buf[length++] = 0;
    tagged_buf[length++] = ssid.length();

    memcpy(tagged_buf + length, ssid.c_str(), ssid.length());
    length += ssid.length();

    memcpy(tagged_buf + length, tagged_param, sizeof(tagged_param));
    length += sizeof(tagged_param);
    size += length;
}

void Frame::randomize_bssid(void)
{
    for (int i = 0; i < 6; i++)
        beacon_header.BSS_ID[i] = beacon_header.SA[i] = rand() % 0x100;
}
