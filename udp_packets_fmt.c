//
// Created by Will Gulian on 11/10/18.
//

#include <stdio.h>

#include "udp_packets_fmt.h"


void print_info_packet(struct info_packet *packet) {

    if (packet->magic_number == MAGIC_INFO_PACKET) {
        printf("Info Packet:\n");
    } else {
        printf("Info Packet: [invalid magic number: 0x%x]\n", packet->magic_number);
    }

    printf("    Status: ");
    switch (packet->pod_status) {
        case STATUS_FAULT:
            printf("FAULT\n");
            break;
        case STATUS_IDLE:
            printf("IDLE\n");
            break;
        case STATUS_READY:
            printf("READY\n");
            break;
        case STATUS_ACCELERATING:
            printf("ACCELERATING\n");
            break;
        case STATUS_COAST:
            printf("COAST\n");
            break;
        case STATUS_BRAKING:
            printf("BRAKING\n");
            break;
        default:
            printf("UNKNOWN (0x%x)\n", packet->pod_status);
            break;
    }

    printf("    Timestamp: %d ms\n", packet->timestamp);

    printf("    Physical:\n");

    printf("        Velocity: %d cm/s\n", packet->velocity);
    printf("        Acceleration: %d cm/s^2\n", packet->acceleration);

    printf("    Battery:\n");

    printf("        Voltage: %.3f volts\n", packet->battery_voltage / 1000.0);

    printf("    Temperature:\n");

    printf("        Pod: %.1f C\n", packet->pod_temp / 10.0);
    printf("        Battery: %.1f C\n", packet->battery_temp / 10.0);

    printf("    Pressure:\n");

    printf("        Tank: %.3f bar\n", packet->tank_pressure / 1000.0);
    printf("        Left Brakes: %.3f bar\n", packet->left_brake_pressure / 1000.0);
    printf("        Right Brakes: %.3f bar\n", packet->right_brake_pressure / 1000.0);

    printf("\n");
}


void print_control_packet(struct control_packet *packet) {

    if (packet->magic_number == MAGIC_CONTROL_PACKET) {
        printf("Control Packet:\n");
    } else {
        printf("Control Packet: [invalid magic number: 0x%x]\n", packet->magic_number);
    }

    printf("    Status: ");
    switch (packet->command) {
        case COMMAND_START:
            printf("START\n");
            break;
        case COMMAND_STOP:
            printf("STOP\n");
            break;
        case COMMAND_EMERGENCY_STOP:
            printf("EMERGENCY_STOP\n");
            break;
        case COMMAND_CRAWL:
            printf("CRAWL\n");
            break;
        default:
            printf("UNKNOWN (0x%x)\n", packet->command);
            break;
    }

    printf("    Timestamp: %d ms\n", packet->timestamp);

    printf("\n");
}




