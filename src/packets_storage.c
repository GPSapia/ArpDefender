#include "../include/packets_storage.h"
#include <stdlib.h>

void init_structures ()
{
    host_requested_ip = NULL;
    current_last_request = NULL;
}

void add_host_request (uint8_t* ip_address)
{
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

bool in_gratouitous_responses (uint8_t* ip_address, uint8_t* mac)
{
  struct arp_response* arp_item = gratouitous_arp;

  while (arp_item)
  {
    if (compare_addresses (ip_address, arp_item->ip_address) && compare_mac(mac, arp_item->mac))
      return true;
    arp_item = arp_item->next;
  }
  return false;
}

bool mismatch_found (uint8_t* ip_address, uint8_t* mac, uint8_t* mismatching_mac)
{
  struct arp_response* arp_item = gratouitous_arp;

  while (arp_item)
  {
    if (compare_addresses (ip_address, arp_item->ip_address))
    {
      if (!compare_mac(mac, arp_item->mac))
      {
        for (size_t i = 0; i < 6; i++)
        mismatching_mac[i] = arp_item->mac[i];
        delete_response_item(&gratouitous_arp, arp_item->ip_address);
        return true;
      }
      else
      {
        delete_response_item(&gratouitous_arp, arp_item->ip_address);
        return false;
      }
    }
    arp_item = arp_item->next;
  }
  return false;
}

void delete_response_item (struct arp_response** item, uint8_t* ip_address)
{
  struct arp_response* tmp = *item;
  struct arp_response* previous = NULL;

  if (tmp != NULL && compare_addresses(tmp->ip_address, ip_address))
  {
      *item = tmp->next;
      free (tmp);
      if (*item == NULL) {
        current_last_response = NULL;
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
    current_last_response = previous;
  free(tmp);
  tmp = NULL;
}

void delete_request_item (struct request_item** item, uint8_t* ip_address)
{
    struct request_item* tmp = *item;
    struct request_item* previous = NULL;

    if (tmp != NULL && compare_addresses(tmp->ip_address, ip_address))
    {
        *item = tmp->next;
        free (tmp);
        if (*item == NULL)
        {
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
