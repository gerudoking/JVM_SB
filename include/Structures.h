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

struct ClassFile{
	u4 magic;
	u2 minor_version;
	u2 major_version;
	u2 constant_pool_count;
	void **constant_pool;
	u2 access_flags;
	u2 this_class;
	u2 super_class;
	u2 interfaces_count;
	u2 *interfaces;
	u2 fields_count;
	field_info *fields;
	u2 methods_count;
	method_info *methods;
	u2 attributes_count;
	void **attributes;
};
typedef struct ClassFile ClassFile;

struct static_struct{
	u1 *class_name;
	u2 fields_count;  
	u8 *value;
};
typedef struct static_struct static_struct;

struct CONSTANT_Pool_info{
	u1 tag;
	u1 *info;
} 
typedef struct CONSTANT_Pool_info;

struct CONSTANT_Class_info{
	u1 tag;
	u2 name_index;
};
typedef struct CONSTANT_Pool_info CONSTANT_Pool_info;

struct CONSTANT_Fieldref_info{
	u1 tag;
	u2 class_index;
	u2 name_and_type_index;
};
typedef struct CONSTANT_Fieldref_info CONSTANT_Fieldref_info;

struct CONSTANT_NameAndType_info{
	u1 tag;
	u2 name_index;
	u2 descriptor_index;
};
typedef struct CONSTANT_NameAndType_info CONSTANT_NameAndType_info;

struct CONSTANT_Utf8_info{
	u1 tag;
	u2 length;
	u1 *bytes;
};
typedef struct CONSTANT_Utf8_info CONSTANT_Utf8_info;

struct CONSTANT_Methodref_info{
	u1 tag;
	u2 class_index;
	u2 name_and_type_index;
};
typedef struct CONSTANT_Methodref_info CONSTANT_Methodref_info;

struct CONSTANT_InterfaceMethodref_info{
	u1 tag;
	u2 class_index;
	u2 name_and_type_index;
};
typedef struct CONSTANT_InterfaceMethodref_info CONSTANT_InterfaceMethodref_info;

struct CONSTANT_String_info{
	u1 tag;
	u2 string_index;
};
typedef struct CONSTANT_String_info CONSTANT_String_info;

struct CONSTANT_Integer_info{
	u1 tag;
	u4 bytes;
};
typedef struct CONSTANT_Integer_info CONSTANT_Integer_info;

struct CONSTANT_Float_info{
	u1 tag;
	u4 bytes;
};
typedef struct CONSTANT_Float_info CONSTANT_Float_info;

struct CONSTANT_Long_info{
	u1 tag;
	u4 high_bytes;
	u4 low_bytes;
};
typedef struct CONSTANT_Long_info  CONSTANT_Long_info;

struct CONSTANT_Double_info{
	u1 tag;
	u4 high_bytes;
	u4 low_bytes;
};
typedef struct CONSTANT_Double_info CONSTANT_Double_info;

struct attribute_info{
	u2 attribute_name_index;
	u4 attribute_length;
	u2 tag;
	u1 *info;
}; 
typedef struct attribute_info attribute_info;

struct ConstantValue_attribute{
	u2 attribute_name_index;
	u4 attribute_length;
	u2 tag;
	u2 constantvalue_index;
};
typedef struct ConstantValue_attribute ConstantValue_attribute;

struct Code_attribute{
	u2 attribute_name_index;
	u4 attribute_length;
	u2 tag;
	u2 max_stack;
	u2 max_locals;
	u4 code_length;
	u1 *code;
	u2 exception_table_length;
	exception_tab *exception_table;
	u2 attributes_count;
	void **attributes;
};
typedef struct Code_attribute Code_attribute;

struct Deprecated_attribute{
	u2 attribute_name_index;
	u4 attribute_length;
	u2 tag;
};
typedef struct Deprecated_attribute Deprecated_attribute;

struct Exceptions_attribute{
	u2 attribute_name_index;
	u4 attribute_length;
	u2 tag;
	u2 number_of_exceptions;
	u2 *exception_index_table;
};
typedef struct Exceptions_attribute Exceptions_attribute;

struct InnerClasses_attribute{
	u2 attribute_name_index;
	u4 attribute_length;
	u2 tag;
	u2 number_of_classes;
	class_tab *classes;
};
typedef struct InnerClasses_attribute InnerClasses_attribute;

struct LineNumberTable_attribute{
	u2 attribute_name_index;
	u4 attribute_length;
	u2 tag;
	u2 line_number_table_length;
	line_number_tab   *line_number_table;
};
typedef struct LineNumberTable_attribute LineNumberTable_attribute;

struct local_variable{
	u2 start_pc;
	u2 length;
	u2 name_index;
	u2 descriptor_index;
	u2 index;
};
typedef struct local_variable local_variable_tab;

struct LocalVariableTable_attribute{
	u2 attribute_name_index;
	u4 attribute_length;
	u2 tag;
	u2 local_variable_table_length;
	local_variable_tab *local_variable_table;
};
typedef struct LocalVariableTable_attribute LocalVariableTable_attribute;

struct SourceFile_attribute{
	u2 attribute_name_index;
	u4 attribute_length;
	u2 tag;
	u2 sourcefile_index;
};
typedef struct SourceFile_attribute SourceFile_attribute;

struct Synthetic_attribute{
	u2 attribute_name_index;
	u4 attribute_length;
};
typedef struct Synthetic_attribute Synthetic_attribute;



#endif
