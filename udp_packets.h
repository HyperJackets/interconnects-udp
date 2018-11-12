//
// Created by Will Gulian on 10/10/18.
//

#ifndef HYPERJACKETS_INTERCONNECTS_UDP_UDP_PACKETS_H
#define HYPERJACKETS_INTERCONNECTS_UDP_UDP_PACKETS_H

#include <stdint.h>
#include <stdbool.h>

#define COMMAND_START 1
#define COMMAND_STOP 2
#define COMMAND_EMERGENCY_STOP 4
#define COMMAND_CRAWL 8

#define STATUS_FAULT 0
#define STATUS_IDLE 1
#define STATUS_READY 2
#define STATUS_ACCELERATING 3
#define STATUS_COAST 4
#define STATUS_BRAKING 5


// See Page 15 of the 2018 Track and Pod Specification
#define TELEMETRY_STATUS_FAULT 0
#define TELEMETRY_STATUS_SAFE_TO_APPROACH 1
#define TELEMETRY_STATUS_READY_TO_LAUNCH 2
#define TELEMETRY_STATUS_LAUNCHING 3
#define TELEMETRY_STATUS_COASTING 4
#define TELEMETRY_STATUS_BRAKING 5
#define TELEMETRY_STATUS_CRAWLING 6

#define MAGIC_INFO_PACKET 0x1ae91a5b
#define MAGIC_CONTROL_PACKET 0xfc9d8e40


struct info_packet {

    uint32_t magic_number;
    int32_t pod_status; // One of STATUS_ macros.
    uint32_t timestamp; // milliseconds since pod powered on
    int32_t acceleration; // cm^2/s
    int32_t velocity; // cm^2/s
    int32_t battery_voltage; // millivolts
    int32_t battery_temp; // tenths of a degree celsius
    int32_t pod_temp; // tenths of a degree celsius

    int32_t tank_pressure; // millibar
    int32_t left_brake_pressure; // millibar
    int32_t right_brake_pressure; // millibar

} __attribute__((packed));

struct control_packet {

    uint32_t magic_number;
    uint32_t command;
    uint32_t timestamp; // milliseconds since fixed epoch

} __attribute__((packed));

struct hyperloop_telemetry_packet {

    uint8_t team_id; // Identifier for the team, assigned by SpaceX
    uint8_t status; // Pod status enumeration, one of TELEMETRY_STATUS_ macros
    int32_t position; // Pod position estimation in centimeters from starting position
    int32_t velocity; // Pod velocity estimation in cm/s
    int32_t acceleration; // Pod acceleration estimation cm/s^2

    int32_t battery_voltage; // millivolts
    int32_t battery_current; // milliamps
    int32_t battery_temp; // tenths of a degree celsius
    int32_t pod_temp; // tenths of a degree celsius

    uint32_t stripe_count; // Count of optical navigation stripes detected in tube

} __attribute__((packed));

_Static_assert(sizeof(struct hyperloop_telemetry_packet) == 34,
               "Hyperloop packet spec expects 34 byte telemetry packet.");

bool is_info_packet_valid(struct info_packet *packet);

bool is_raw_info_packet_valid(void *raw_data);

bool encode_info_packet(struct info_packet *packet, void *raw_data);

bool decode_info_packet(void *raw_data, struct info_packet *packet);


bool is_control_packet_valid(struct control_packet *packet);

bool is_raw_control_packet_valid(void *raw_data);

bool encode_control_packet(struct control_packet *packet, void *raw_data);

bool decode_control_packet(void *raw_data, struct control_packet *packet);


bool is_hyperloop_telemetry_packet_valid(struct hyperloop_telemetry_packet *packet);

bool encode_hyperloop_telemetry_packet(struct hyperloop_telemetry_packet *packet, void *raw_data);

bool decode_hyperloop_telemetry_packet(void *raw_data, struct hyperloop_telemetry_packet *packet);


#endif //HYPERJACKETS_INTERCONNECTS_UDP_UDP_PACKETS_H
