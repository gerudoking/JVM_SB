#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <stdint.h>

typedef uint8_t u1;
typedef uint16_t u2;
typedef uint32_t u4;

struct attribute_info{
	u2 attribute_name_index;
	u4 attribute_length;
	u1 info[attribute_length];
};
typedef struct attribute_info attribute_info;

struct field_info{
	u2 access_flags;
	u2 name_index;
	u2 descriptor_index;
	u2 attributes_count;
	attribute_info attributes[attributes_count];
};
typedef struct field_info field_info;

struct method_info{
	u2 access_flags;
	u2 name_index;
	u2 descriptor_index;
	u2 attributes_count;
	attribute_info attributes[attributes_count];
};
typedef struct method_info method_info;
#endif