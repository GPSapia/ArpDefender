#include "../include/arp_capture.h"

//
//initialize the capture session
//
void init_pcap (char* requested_nic)
{
    nic = requested_nic;
    init_structures();
    get_interface_ip (local_if_address);
    get_mac_address(my_mac);


    if ((capture_session = pcap_open_live (nic, BUFSIZ, false, 0, error_buffer)) == NULL) {
      printf("%s\n", error_buffer);
      exit(1);
    }

    bpf_u_int32 netmask;
    bpf_u_int32 net;

    if (pcap_lookupnet (requested_nic, &net, &netmask, error_buffer)) {
      printf("%s\n", error_buffer);
      exit(1);
    }

    if (pcap_compile(capture_session, &arp_filter, "arp", true, netmask) == -1) {
        printf("%s\n", pcap_geterr(capture_session));
        exit(1);
    }

    if (pcap_setfilter(capture_session, &arp_filter) == -1) {
        printf("%s\n", pcap_geterr(capture_session));
        exit(1);
    }
}

void handle_packet (u_char *args, const struct pcap_pkthdr *header, const u_char *packet)
{
    struct arp_packet* pckt = (struct ether_arp*)(packet + ARP_ETHERNET_HEADER_LEN);

    //check if it is a request or a response
    unsigned short int opcode = (pckt->header).ar_op;

    //if it is a request coming from the host himself
    if (htons (opcode) == 1 && compare_addresses(pckt->sender_ip_address, local_if_address))
    {
      add_host_request(pckt->target_ip_address);  //Store the requested ip

      //for debugging purposes
       print_all_ips();
    }


    //if it is a response coming from the network
    else if (htons (opcode) == 2 && !compare_addresses(pckt->sender_ip_address, local_if_address))
    {
      //check_and_delete ()
      if (in_host_requests (pckt->sender_ip_address))
      {
        delete_item (&host_requested_ip, pckt->sender_ip_address);
      }
      else
      {
        add_gratouitous_response (pckt->sender_ip_address, pckt->sender_mac_address);
      }
    }
}

void start_capture ()
{
    pcap_loop (capture_session, 4, handle_packet, NULL);                        //putting 4 for debugging purposes, need to put -1
}

void end_capture ()
{
    free_requests();
}
