cmake_minimum_required(VERSION 3.12)
project(hyperjackets_interconnects_udp C)

set(CMAKE_C_STANDARD 99)

add_executable(hyperjackets_interconnects_udp udp_packets.c main.c header_util.h udp_packets_fmt.c udp_packets_fmt.h)