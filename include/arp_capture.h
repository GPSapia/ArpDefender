#ifndef _ARPCAPTURE_H
#define _ARPCAPTURE_H

#include "structures.h"
#include "packets_storage.h"
#include "utils.h"
#include <stdbool.h>
#include <pcap.h>
#include <string.h>
#include "arp_sender.h"

char* nic;
uint8_t local_if_address[4];
char my_mac[6];

char error_buffer [PCAP_ERRBUF_SIZE];

//handler for the capture session
pcap_t* capture_session;

struct bpf_program arp_filter;

char* log_file;

void init_pcap (char* requested_nic, char* log_file);
void init_log_file (char* log_file);
void handle_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *packet);
void start_capture();
void end_capture();

#endif
