/** @file ClassFile.h
 * @brief Definição da ClassFile
 */

#ifndef CLASSFILE
#define CLASSFILE

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string>
#include <fstream>
#include "BasicTypes.h"

using namespace std;
/**
 * @class ClassFile
 * @section DESCRIPTION
 * A classe ClassFile contém os bytecodes armazenados em memoria
 */
class ClassFile {
public:


	/** @fn ClassFile()
	 * @brief Construtor que configura um objeto da classe ClassFile com o nome do arquivo passado.

	 */
	ClassFile();

	u4 magic;
	u2 minor_version;
	u2 major_version;
	u2 constant_pool_count;
	cp_info *constant_pool;
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
	attribute_info *attributes;

};
#endif
