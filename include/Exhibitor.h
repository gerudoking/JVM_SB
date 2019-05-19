#ifndef EXHIBITOR_H
#define EXHIBITOR_H

#include "Structures.h"
#include <cstdio>
#include <cstdlib>

using namespace std;

class Exhibitor
{
public:
	Exhibitor();
	~Exhibitor();

	void ShowInfo(ClassFile* jvm_class);
	void ShowInfoOnFile(ClassFile* jvm_class, FILE* file);
	void ShowConstantPool(ClassFile* jvm_class);
	void ShowConstantPoolOnFile(ClassFile* jvm_class, FILE* file);
	void ShowAttribute(ClassFile* jvm_class, attribute_info* attributeInfo);
	void ShowAttributeOnFile(ClassFile* jvm_class, attribute_info* attributeInfo);
	void ShowAllAttributes(ClassFile* jvm_class);
	void ShowAllAttributesOnFile(ClassFile* jvm_class);
	void ShowFields(ClassFile* jvm_class);
	void ShowFieldsOnFile(ClassFile* jvm_class);
	void ShowInterface(CpInfo cp);
	void ShowInterfaceOnFile(ClassFile* jvm_class, CpInfo cp, FILE* file);
	void ShowAllInterfaces(ClassFile* jvm_class);
	void ShowAllInterfacesOnFile(ClassFile* jvm_class, FILE* file);
	void ShowMethods(ClassFile* jvm_class);
	void ShowMethodsOnFile(ClassFile* jvm_class, FILE* file);

	char* NameInfo(ClassFile* jvm_class, u2 index);
	char* RefFieldInfo(ClassFile* jvm_class, u2 index);
	char* MethodInfo(ClassFile* jvm_class, u2 index);

private:
	//void Mnemonics(fazer argumento aqui);
};

#endif