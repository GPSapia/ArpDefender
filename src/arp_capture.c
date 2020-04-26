#include "../include/arp_capture.h"

//
//initialize the capture session
//
void init_pcap (char* requested_nic, char* log_file)
{
    nic = requested_nic;
    init_structures();
    get_interface_ip (local_if_address);
    get_mac_address(my_mac);
    init_packet_fields();
    init_log_file(log_file);

    if ((capture_session = pcap_open_live (nic, BUFSIZ, false, 0, error_buffer)) == NULL)
    {
      printf("%s\n", error_buffer);
      exit(1);
    }

    bpf_u_int32 netmask;
    bpf_u_int32 net;

    if (pcap_lookupnet (requested_nic, &net, &netmask, error_buffer))
    {
      printf("%s\n", error_buffer);
      exit(1);
    }

    if (pcap_compile(capture_session, &arp_filter, "arp", true, netmask) == -1)
    {
        printf("%s\n", pcap_geterr(capture_session));
        exit(1);
    }

    if (pcap_setfilter(capture_session, &arp_filter) == -1)
    {
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
    }


    //if it is a response coming from the network
    else if (htons (opcode) == 2 && !compare_addresses(pckt->sender_ip_address, local_if_address))
    {
      uint8_t mismatching_mac[6];
      //check_and_delete ()
      if (in_host_requests (pckt->sender_ip_address))
      {
        delete_request_item (&host_requested_ip, pckt->sender_ip_address);
      }
      else if (mismatch_found(pckt->sender_ip_address, pckt->sender_mac_address, mismatching_mac))
      {
        fprintf(log_file, "found mismatch for ip: %d.%d.%d.%d\tmac1 is: %02x:%02x:%02x:%02x:%02x:%02x\tmac2 is: %02x:%02x:%02x:%02x:%02x:%02x\n",
                                                                                                                          pckt->sender_ip_address[0], pckt->sender_ip_address[1],
                                                                                                                          pckt->sender_ip_address[2], pckt->sender_ip_address[3],
                                                                                                                          pckt->sender_mac_address[0], pckt->sender_mac_address[1],
                                                                                                                          pckt->sender_mac_address[2], pckt->sender_mac_address[3],
                                                                                                                          pckt->sender_mac_address[4], pckt->sender_mac_address[5],
                                                                                                                          mismatching_mac[0], mismatching_mac[1],
                                                                                                                          mismatching_mac[2], mismatching_mac[3],
                                                                                                                          mismatching_mac[4], mismatching_mac[5]);
      }
      else
      {
        if (!in_gratouitous_responses(pckt->sender_ip_address, pckt->sender_mac_address))
        {
          add_gratouitous_response (pckt->sender_ip_address, pckt->sender_mac_address);
          send_packet(pckt->sender_ip_address);
        }
      }
    }
}

void init_log_file(char* file)
{
    log_file = fopen(file, "a");
    if (log_file == NULL)
    {
      perror("Error while opening log file\n");
      exit(1);
    }
}

void start_capture ()
{
    pcap_loop (capture_session, -1, handle_packet, NULL);
}

void end_capture ()
{
    free_requests();
}
