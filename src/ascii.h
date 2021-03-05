#ifndef __LOOKUP_H__
#define __LOOKUP_H__
#include <stdint.h>
uint8_t ascii[120][5] = {
                {0x08, 0x71, 0xee, 0x7f, 0x00},
                {0xc0, 0xff, 0xce, 0x11, 0x02},
                {0x10, 0x73, 0xcf, 0x31, 0x04},
                {0x84, 0x71, 0xde, 0x19, 0x01},
                {0x00, 0x55, 0x45, 0x51, 0x00},
                {0x40, 0x51, 0x54, 0x15, 0x00},
                {0xf6, 0xde, 0x7b, 0xef, 0x0d},
                {0x80, 0x73, 0xce, 0x39, 0x00},
                {0x00, 0x00, 0x00, 0x00, 0x00},
                {0x42, 0x08, 0x21, 0x84, 0x00},
                {0xc6, 0x18, 0x63, 0x8c, 0x01},
                {0xce, 0x39, 0xe7, 0x9c, 0x03},
                {0xde, 0x7b, 0xef, 0xbd, 0x07},
                {0xfe, 0xff, 0xff, 0xff, 0x0f},
                {0xc0, 0xff, 0xff, 0xff, 0x0f},
                {0x00, 0xf8, 0xff, 0xff, 0x0f},
                {0x00, 0x00, 0xff, 0xff, 0x0f},
                {0x00, 0x00, 0xe0, 0xff, 0x0f},
                {0x00, 0x00, 0x00, 0xfc, 0x0f},
                {0x00, 0x00, 0x00, 0x80, 0x0f},
                {0x00, 0x00, 0x00, 0x00, 0x00},
                {0xaa, 0xaa, 0xaa, 0xaa, 0x0a},
                {0x54, 0x55, 0x55, 0x55, 0x05},
                {0x00, 0x71, 0xff, 0x3b, 0x02},
                {0x00, 0x00, 0x00, 0x00, 0x00},
                {0x08, 0x21, 0x04, 0x00, 0x02},
                {0x94, 0x52, 0x00, 0x00, 0x00},
                {0x94, 0xfa, 0xea, 0x2b, 0x05},
                {0x88, 0x13, 0x0e, 0x39, 0x02},
                {0xc6, 0x44, 0x44, 0x64, 0x0c},
                {0x4c, 0x2a, 0xa2, 0x26, 0x0b},
                {0x0c, 0x11, 0x00, 0x00, 0x00},
                {0x10, 0x11, 0x42, 0x10, 0x04},
                {0x04, 0x41, 0x08, 0x11, 0x01},
                {0x00, 0xa9, 0xae, 0x12, 0x00},
                {0x00, 0x21, 0x9f, 0x10, 0x00},
                {0x00, 0x00, 0xc0, 0x10, 0x01},
                {0x00, 0x00, 0x1f, 0x00, 0x00},
                {0x00, 0x00, 0x00, 0x18, 0x03},
                {0x00, 0x80, 0x88, 0x88, 0x00},
                {0x5c, 0xcc, 0x75, 0x46, 0x07},
                {0x88, 0x21, 0x84, 0x10, 0x07},
                {0x5c, 0x84, 0x88, 0x88, 0x0f},
                {0x3e, 0x22, 0x08, 0x46, 0x07},
                {0x10, 0x53, 0xe9, 0x23, 0x04},
                {0x7e, 0x78, 0x10, 0x46, 0x07},
                {0x98, 0x08, 0x2f, 0x46, 0x07},
                {0x3e, 0x84, 0x88, 0x10, 0x02},
                {0x5c, 0x8c, 0x2e, 0x46, 0x07},
                {0x5c, 0x8c, 0x1e, 0x22, 0x03},
                {0x80, 0x31, 0xc0, 0x18, 0x00},
                {0x80, 0x31, 0xc0, 0x10, 0x01},
                {0x10, 0x11, 0x41, 0x10, 0x04},
                {0x00, 0xf8, 0xe0, 0x03, 0x00},
                {0x04, 0x41, 0x10, 0x11, 0x01},
                {0x5c, 0x84, 0x88, 0x00, 0x02},
                {0x5c, 0x84, 0xb6, 0x56, 0x07},
                {0x5c, 0x8c, 0xf1, 0xc7, 0x08},
                {0x5e, 0x8c, 0x2f, 0xc6, 0x07},
                {0x5c, 0x0c, 0x21, 0x44, 0x07},
                {0x4e, 0x8a, 0x31, 0xa6, 0x03},
                {0x7e, 0x08, 0x2f, 0x84, 0x0f},
                {0x7e, 0x08, 0x2f, 0x84, 0x00},
                {0x5c, 0x0c, 0x3d, 0x46, 0x07},
                {0x62, 0x8c, 0x3f, 0xc6, 0x08},
                {0x1c, 0x21, 0x84, 0x10, 0x07},
                {0x38, 0x42, 0x08, 0x25, 0x03},
                {0x62, 0x2a, 0xa3, 0xa4, 0x08},
                {0x42, 0x08, 0x21, 0x84, 0x0f},
                {0xe2, 0xae, 0x35, 0xc6, 0x08},
                {0x62, 0x9c, 0x35, 0xc7, 0x08},
                {0x5c, 0x8c, 0x31, 0x46, 0x07},
                {0x5e, 0x8c, 0x2f, 0x84, 0x00},
                {0x5c, 0x8c, 0xb1, 0x26, 0x0b},
                {0x5e, 0x8c, 0xaf, 0xa4, 0x08},
                {0x5c, 0x0c, 0x0e, 0x46, 0x07},
                {0x3e, 0x21, 0x84, 0x10, 0x02},
                {0x62, 0x8c, 0x31, 0x46, 0x07},
                {0x62, 0x8c, 0x31, 0x2a, 0x02},
                {0x62, 0x8c, 0xb5, 0x56, 0x05},
                {0x62, 0x54, 0x44, 0xc5, 0x08},
                {0x62, 0x54, 0x84, 0x10, 0x02},
                {0x3e, 0x44, 0x44, 0x84, 0x0f},
                {0x9c, 0x10, 0x42, 0x08, 0x07},
                {0x40, 0x10, 0x04, 0x41, 0x00},
                {0x1c, 0x42, 0x08, 0x21, 0x07},
                {0x88, 0x8a, 0x00, 0x00, 0x00},
                {0x00, 0x00, 0x00, 0x80, 0x0f},
                {0x04, 0x41, 0x00, 0x00, 0x00},
                {0x00, 0x70, 0xd0, 0x47, 0x0f},
                {0x42, 0x68, 0x33, 0xc6, 0x07},
                {0x00, 0x70, 0x21, 0x44, 0x07},
                {0x20, 0xb4, 0x39, 0x46, 0x07},
                {0x00, 0x70, 0xf1, 0x07, 0x07},
                {0x00, 0x93, 0xe2, 0x08, 0x01},
                {0x80, 0x8f, 0xd1, 0x43, 0x07},
                {0x42, 0x68, 0x33, 0xc6, 0x08},
                {0x08, 0x30, 0x84, 0x10, 0x07},
                {0x10, 0x60, 0x08, 0x25, 0x03},
                {0x42, 0x48, 0x65, 0x94, 0x04},
                {0x0c, 0x21, 0x84, 0x10, 0x07},
                {0x00, 0x58, 0xb5, 0xc6, 0x08},
                {0x00, 0x68, 0x33, 0xc6, 0x08},
                {0x00, 0x70, 0x31, 0x46, 0x07},
                {0x00, 0x78, 0xf1, 0x85, 0x00},
                {0x00, 0xb0, 0xd9, 0x43, 0x08},
                {0x00, 0x68, 0x33, 0x84, 0x00},
                {0x00, 0x70, 0xc1, 0xc1, 0x07},
                {0x84, 0x38, 0x42, 0x48, 0x06},
                {0x00, 0x88, 0x31, 0x66, 0x0b},
                {0x00, 0x88, 0x31, 0x2a, 0x02},
                {0x00, 0x88, 0xb1, 0x56, 0x05},
                {0x00, 0x88, 0x8a, 0xa8, 0x08},
                {0x00, 0x88, 0xd1, 0x43, 0x07},
                {0x00, 0xf8, 0x88, 0x88, 0x0f},
                {0x10, 0x21, 0x82, 0x10, 0x04},
                {0x08, 0x21, 0x80, 0x10, 0x02},
                {0x04, 0x21, 0x88, 0x10, 0x01},
                {0x00, 0x10, 0x15, 0x01, 0x00},
                {0x00, 0x00, 0x00, 0x00, 0x00},
                };
const uint8_t digitLookUp[]=
{
    0b11101110,
    0b00100100,
    0b11010110,
    0b10110110,
    0b00111100,
    0b10111010,
    0b11111010,
    0b00100110,
    0b11111110,
    0b10111110,
    0b00000000
};
#endif