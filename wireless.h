#include <stdint.h>

#ifndef WIRELESS_H
#define WIRELESS_H

#pragma pack(push, 1)
struct ieee80211_radiotap_header {
    uint8_t it_version;
    uint8_t it_pad;
    uint16_t it_len;
    uint32_t it_present;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct ieee80211_beacon_frame_header {
    uint16_t frame_control;
    uint16_t duration;
    uint8_t DA[6];
    uint8_t SA[6];
    uint8_t BSS_ID[6];
    uint16_t seq_ctl;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct ieee80211_beacon_frame_body {
    uint64_t Timestamp;
    uint16_t Beacon_interval;
    uint16_t Capability_Info;
};
#pragma pack(pop)

#endif // WIRELESS_H
