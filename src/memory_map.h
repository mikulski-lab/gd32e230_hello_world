#ifndef _MEMORY_MAP_H_
#define _MEMORY_MAP_H_

#include <stdint.h>

#define INFOA __attribute__((__used__, section(".meta_info.INFO")))
#define VERSIONA __attribute__((__used__, section(".meta_info.VERSION")))

VERSIONA const uint8_t VERSION[] = {0x01, 0x02, 0x03};
INFOA const char INFO[] = {"LOCATION displays text test:" __FILE__ ", " __DATE__ ", " __TIME__ ".\r\n"};

extern uint32_t * _eflash;
extern uint32_t * _emetadata;

typedef struct {
    uint8_t major;
    uint8_t minor;
    uint8_t revision;
} METADATA_t;

METADATA_t const * const METADATA = (METADATA_t *)&_emetadata;

#endif /*_MEMORY_MAP_H_*/
