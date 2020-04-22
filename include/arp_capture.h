#ifndef _ARPCAPTURE_H
#define _ARPCAPTURE_H

#include "structures.h"
#include "packets_storage.h"
#include "utils.h"
#include <stdbool.h>
#include <pcap.h>
#include <string.h>

char* nic;
char error_buffer [PCAP_ERRBUF_SIZE];

//handler for the capture session
pcap_t* capture_session;

struct bpf_program arp_filter;

void init_pcap (char* requested_nic);
void handle_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *packet);
void start_capture();
void end_capture();

#endif
