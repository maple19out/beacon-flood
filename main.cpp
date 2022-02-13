#include <cstdio>
#include <pcap.h>
#include <list>
#include <string>
#include <cstring>
#include <unistd.h>
#include "wireless.h"
#include "frame.h"

using namespace std;

void usage() {
    printf("syntax : beacon-flood <interface> <ssid-list-file>\n");
    printf("sample : beacon-flood mon0 ssid-list.txt\n");
}

struct Param {
    char* dev_;
    char* ssid_list_;
};

Param param {
    .dev_ = NULL, .ssid_list_= NULL
};

bool parse(Param* param, int argc, char* argv[]) {
    if (argc != 3) {
        usage();
        return false;
    }
    param->dev_ = argv[1];
    param->ssid_list_ = argv[2];
    return true;
}

void extract_ssid_list(list<string>& ssidList) {
    FILE* fp = fopen(param.ssid_list_, "r");

    char buf[256];
    while (fgets(buf, 256, fp)) {
        buf[strlen(buf) - 1] = '\0';

        string ssid(buf);
        ssidList.push_back(ssid);
    }

    fclose(fp);
}

int main(int argc, char* argv[]) {
    if (!parse(&param, argc, argv))
        return -1;

    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t* pcap = pcap_open_live(param.dev_, BUFSIZ, 1, 1000, errbuf);
    if (pcap == NULL) {
        fprintf(stderr, "pcap_open_live(%s) return null - %s\n", param.dev_, errbuf);
        return -1;
    }

    list<string> ssidList;
    extract_ssid_list(ssidList);

    Frame frame;
    memset(frame.buf, 0, sizeof(frame.buf));
    frame.size = 0;
    frame.set_radiotap_header(12);
    frame.set_beaconframe();

    /* To Do */
    int prev_size = frame.size;
    while (true) {
        for(list<string>::iterator it = ssidList.begin(); it != ssidList.end(); it++) {
            frame.size = prev_size;
            frame.set_ssid((*it));
            printf("sending [%s] beacon frame...\n", (*it).c_str());
            pcap_sendpacket(pcap, frame.buf, frame.size);
        }
        usleep(5000);
    }
    pcap_close(pcap);

    return 0;
}
