//
// Created by Will Gulian on 11/8/18.
//

#ifndef HYPERJACKETS_INTERCONNECTS_UDP_HEADER_UTIL_H
#define HYPERJACKETS_INTERCONNECTS_UDP_HEADER_UTIL_H

/*
 * Asserts a struct size. Triggers an `array with negative size error` if the struct doesn't match the given size.
 *
 * Example:
 * struct bob {
 *   uint8_t foo;
 *   // uncomment next line to trigger the assert
 *   // uint16_t bar;
 * };
 *
 * SIZE_CHECK_STRUCT(bob, 8);
 *
 *
 */
#define SIZE_CHECK_STRUCT( sname, maxsize ) typedef char sname ## _size_check_struct [ 1 - 2* !!(sizeof(struct sname) != (maxsize)) ]


#endif //HYPERJACKETS_INTERCONNECTS_UDP_HEADER_UTIL_H
