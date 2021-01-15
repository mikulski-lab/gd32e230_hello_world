#ifndef _METADATA_H_
#define _METADATA_H_

#include <stdint.h>

#define INFOA __attribute__((__used__, section(".meta_info.INFO")))
#define VERSIONA __attribute__((__used__, section(".meta_info.VERSION")))

VERSIONA const uint8_t VERSION[] = {0x01, 0x00, 0x01};
INFOA const char INFO[] = {"TAPECART SD ARM'ED"};

#endif /*_METADATA_H_*/
