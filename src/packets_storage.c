#include "../include/packets_storage.h"
#include <stdlib.h>

void init_structures ()
{
    host_requested_ip = NULL;
    current_last_request = NULL;
}

void add_host_request (uint8_t* ip_address)
{
    printf("%s\n", "AGGIUNGO");
    struct request_item* new_request = (struct request_item*) malloc(sizeof(struct request_item));
    for (size_t i = 0; i < 4; i++)
      new_request->ip_address[i] = ip_address[i];
    new_request->next = NULL;

    if (current_last_request != NULL)
    {
        current_last_request->next = new_request;
    }
    else
    {
        host_requested_ip = new_request;
    }
    current_last_request = new_request;
}


void add_gratouitous_response (uint8_t* ip_address, uint8_t* mac)
{
  struct arp_response* new_response = (struct arp_response*) malloc(sizeof(struct arp_response));
  for (size_t i = 0; i < 4; i++)
    new_response->ip_address[i] = ip_address[i];
  for (size_t i = 0; i < ETHERNET_ADDRESS_LENGTH; i++)
    new_response->mac[i] = mac[i];
  new_response->next = NULL;

  if (current_last_response != NULL)
  {
      current_last_response->next = new_response;
  }
  else
  {
      gratouitous_arp = new_response;
  }
  current_last_response = new_response;
}


//
//for debugging purposes
//
void print_all_ips ()
{
    struct request_item* rq_item = host_requested_ip;

    while (rq_item)
    {
      for (size_t i = 0; i < 4; i++)
        printf("%d.", rq_item->ip_address[i]);
      rq_item = rq_item->next;
      printf("%s\n", "");
    }
}

//
//for debugging purposes
//
void print_responses ()
{
    struct arp_response* rq_item = gratouitous_arp;

    char macStr[18];

    while (rq_item)
    {
      for (size_t i = 0; i < 4; i++)
        printf("%d.", rq_item->ip_address[i]);
      printf("%s\n", "");


      printf("%02X:%02X\n", rq_item->mac[0], rq_item->mac[1]);

      rq_item = rq_item->next;
      printf("%s\n", "");
    }
}

bool in_host_requests (uint8_t* ip_address)
{
    struct request_item* rq_item = host_requested_ip;

    while (rq_item)
    {
      if (compare_addresses (ip_address, rq_item->ip_address))
        return true;
      rq_item = rq_item->next;
    }
    return false;
}

void delete_item (struct request_item** item, uint8_t* ip_address)
{
    struct request_item* tmp = *item;
    struct request_item* previous = NULL;

    if (tmp != NULL && compare_addresses(tmp->ip_address, ip_address))
    {
        *item = tmp->next;
        free (tmp);
        if (*item == NULL) {
          current_last_request = NULL;
        }
        return;
    }

    while (tmp != NULL && !compare_addresses(tmp->ip_address, ip_address))
    {
        previous = tmp;
        tmp = tmp->next;
    }

    previous->next = tmp->next;
    if (tmp->next == NULL)
      current_last_request = previous;
    free(tmp);
    tmp = NULL;
}

void free_requests ()
{
    while (host_requested_ip)
    {
        struct request_item* current = host_requested_ip;
        host_requested_ip = host_requested_ip->next;
        free (current);
    }
}
