#include "../include/utils.h"


void get_interface_ip(uint8_t* iface_address)
{
    pcap_if_t *devices;
    char* addr = NULL;
    int i = 0;

    if (pcap_findalldevs(&devices, error_buffer) != 0)
    {
      //handle error
      exit(1);
    }

    for(pcap_if_t* d = devices; d != NULL; d = d->next)
    {
       if(!strcmp(d->name, nic))
       {
           for(pcap_addr_t *a=d->addresses; a!=NULL; a=a->next)
           {
               if(a->addr->sa_family == AF_INET)
                   addr = inet_ntoa(((struct sockaddr_in*)a->addr)->sin_addr);
           }
       }
    }

   char* octet = strtok (addr, ".");

   while (octet)
   {
      iface_address[i] = atoi(octet);
      octet = strtok (NULL, ".");
      i++;
   }
}

//
//getting interface mac address from /sys/class/net/iface_nam/address file
//
void get_mac_address(char* mac)
{
    char tmp_mac_buffer[17];
    size_t i = 0;

    char file_name[255];
    strcpy (file_name, "/sys/class/net/");
    strcat (file_name, nic);
    strcat (file_name, "/address");
    FILE* mac_file = fopen(file_name, "r");

    if (mac_file == NULL)
    {
      perror("Error while opening mac file\n");
      exit(1);
    }
    fgets (tmp_mac_buffer, 18, mac_file);

    char* octet = strtok (tmp_mac_buffer, ":");

    while (octet)
    {
        mac[i] = (unsigned char)strtol(octet, NULL, 16);
        octet = strtok (NULL, ":");
        i++;
    }

    fclose(mac_file);
}

bool compare_addresses (uint8_t* first_address, uint8_t* second_address)
{
  for (size_t i = 0; i < 4; i++)
  {
      if (first_address[i] != second_address[i])
        return false;
  }
  return true;
}

bool compare_mac (uint8_t* first_mac, uint8_t* second_mac)
{
  for (size_t i = 0; i < 6; i++)
  {
      if (first_mac[i] != second_mac[i])
        return false;
  }
  return true;
}
