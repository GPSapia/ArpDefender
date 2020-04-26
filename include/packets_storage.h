#ifndef _PACKETSTORAGE_H
#define _PACKETSTORAGE_H

#include <stdio.h> //for debug
#include <stdint.h>
#include <stdbool.h>
#include "structures.h"
#include "utils.h"

//
//store the arp request issued by the host as a linked list
//
struct request_item* host_requested_ip;
struct request_item* current_last_request;

//
//store the gratouitous arp packets
//
struct arp_response* gratouitous_arp;
struct arp_response* current_last_response;

//
//store the request made for checking
//
struct request_item* checking_requests;
struct request_item* current_last_checking_requests;

void init_structures ();

struct request_item* checker_requested_ip;

void add_host_request (uint8_t* ip_address);

bool in_host_requests (uint8_t* ip_address);

bool in_gratouitous_responses (uint8_t* ip_address, uint8_t* mac);

bool mismatch_found (uint8_t* ip_address, uint8_t* mac, uint8_t* mismatching_mac);

void delete_request_item (struct request_item**, uint8_t* ip_address);

void delete_response_item (struct arp_response**, uint8_t* ip_address);

void add_gratouitous_response (uint8_t* ip_address, uint8_t* mac);

void free_requests();

#endif
