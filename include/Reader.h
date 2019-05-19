#ifndef READER_H
#define READER_H

#include <string.h>
#include <fstream>
#include "Structures.h"

using namespace std;

class Reader
{
public:
	Reader();
	~Reader();

	int InsertClass(char *filename, ClassFile *jvm_class);
	
private:

	u1 ReadU1(FILE *file);
	u2 ReadU2(FILE *file);
	u4 ReadU4(FILE *file);

	int root = 1;
	char *dicName = NULL;
	char *fileName = NULL;

	char* GetDirectory(char *file);
	char* GetFileName(char *file);
	int CheckFileName(ClassFile *jvm_class, char *name);

	int FillHeader(FILE *file, ClassFile *jvm_class);
	void FillConstantPool(FILE *file, ClassFile *jvm_class);
	void FillInterface(FILE *file, ClassFile *jvm_class);
	void FillFields(FILE *file, ClassFile *jvm_class);
	void FillMethods(FILE *file, ClassFile *jvm_class);
	void FillAttribute(FILE *file, ClassFile *jvm_class, attribute_info *attribute);
	void FillAttributes(FILE *file, ClassFile *jvm_class);
	void FillClassInfo(FILE *file, ClassFile *jvm_class);
};

#endif