//
// Created by Will Gulian on 10/10/18.
//

#include <netinet/in.h>

#include "udp_packets.h"



bool is_info_packet_valid(struct info_packet *packet) {
    return packet->magic_number == MAGIC_INFO_PACKET;
}

bool is_raw_info_packet_valid(void *raw_data) {
    struct info_packet *network_packet = (struct info_packet *) raw_data;

    return network_packet->magic_number == htonl(MAGIC_INFO_PACKET);
}

bool encode_info_packet(struct info_packet *packet, void *raw_data) {

    struct info_packet *network_packet = (struct info_packet *) raw_data;

    network_packet->magic_number = htonl(packet->magic_number);
    network_packet->pod_status = htonl(packet->pod_status);
    network_packet->timestamp = htonl(packet->timestamp);
    network_packet->acceleration = htonl(packet->acceleration);
    network_packet->velocity = htonl(packet->velocity);
    network_packet->battery_voltage = htonl(packet->battery_voltage);
    network_packet->battery_temp = htonl(packet->battery_temp);
    network_packet->pod_temp = htonl(packet->pod_temp);
    
    network_packet->tank_pressure = htonl(packet->tank_pressure);
    network_packet->left_brake_pressure = htonl(packet->left_brake_pressure);
    network_packet->right_brake_pressure = htonl(packet->right_brake_pressure);

    return true;
}

bool decode_info_packet(void *raw_data, struct info_packet *packet) {

    struct info_packet *network_packet = (struct info_packet *) raw_data;

    packet->magic_number = ntohl(network_packet->magic_number);
    packet->pod_status = ntohl(network_packet->pod_status);
    packet->timestamp = ntohl(network_packet->timestamp);
    packet->acceleration = ntohl(network_packet->acceleration);
    packet->velocity = ntohl(network_packet->velocity);
    packet->battery_voltage = ntohl(network_packet->battery_voltage);
    packet->battery_temp = ntohl(network_packet->battery_temp);
    packet->pod_temp = ntohl(network_packet->pod_temp);

    packet->tank_pressure = ntohl(network_packet->tank_pressure);
    packet->left_brake_pressure = ntohl(network_packet->left_brake_pressure);
    packet->right_brake_pressure = ntohl(network_packet->right_brake_pressure);

    return true;
}





bool is_control_packet_valid(struct control_packet *packet) {
    return packet->magic_number == MAGIC_CONTROL_PACKET;
}

bool is_raw_control_packet_valid(void *raw_data) {
    struct control_packet *network_packet = (struct control_packet *) raw_data;

    return network_packet->magic_number == htonl(MAGIC_CONTROL_PACKET);
}

bool encode_control_packet(struct control_packet *packet, void *raw_data) {

    struct control_packet *network_packet = (struct control_packet *) raw_data;

    network_packet->magic_number = htonl(packet->magic_number);
    network_packet->command = htonl(packet->command);
    network_packet->timestamp = htonl(packet->timestamp);

    return true;
}

bool decode_control_packet(void *raw_data, struct control_packet *packet) {

    struct control_packet *network_packet = (struct control_packet *) raw_data;

    packet->magic_number = ntohl(network_packet->magic_number);
    packet->command = ntohl(network_packet->command);
    packet->timestamp = ntohl(network_packet->timestamp);

    return true;
}


bool is_hyperloop_telemetry_packet_valid(struct hyperloop_telemetry_packet *packet) {
    return true;
}

bool encode_hyperloop_telemetry_packet(struct hyperloop_telemetry_packet *packet, void *raw_data) {

    struct hyperloop_telemetry_packet *network_packet = (struct hyperloop_telemetry_packet *) raw_data;
    
    network_packet->team_id = packet->team_id;
    network_packet->status = packet->status;

    network_packet->position = htonl(packet->position);
    network_packet->velocity = htonl(packet->velocity);
    network_packet->acceleration = htonl(packet->acceleration);
    
    network_packet->battery_voltage = htonl(packet->battery_voltage);
    network_packet->battery_current = htonl(packet->battery_current);
    network_packet->battery_temp = htonl(packet->battery_temp);
    network_packet->pod_temp = htonl(packet->pod_temp);
    
    network_packet->stripe_count = htonl(packet->stripe_count);
    
    return true;
}

bool decode_hyperloop_telemetry_packet(void *raw_data, struct hyperloop_telemetry_packet *packet) {

    struct hyperloop_telemetry_packet *network_packet = (struct hyperloop_telemetry_packet *) raw_data;

    packet->team_id = network_packet->team_id;
    packet->status = network_packet->status;

    packet->position = ntohl(network_packet->position);
    packet->velocity = ntohl(network_packet->velocity);
    packet->acceleration = ntohl(network_packet->acceleration);

    packet->battery_voltage = ntohl(network_packet->battery_voltage);
    packet->battery_current = ntohl(network_packet->battery_current);
    packet->battery_temp = ntohl(network_packet->battery_temp);
    packet->pod_temp = ntohl(network_packet->pod_temp);

    packet->stripe_count = ntohl(network_packet->stripe_count);
    
    return true;
}



