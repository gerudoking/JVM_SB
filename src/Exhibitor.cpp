#include "Exhibitor.h"

Exhibitor::Exhibitor(){

}

Exhibitor::~Exhibitor(){

}

void Exhibitor::ShowInfo(ClassFile* jvm_class){
	char *className, *superClassName;
    int index = jvm_class->constant_pool[jvm_class->this_class - 1].info.Class.name_index - 1;
    className = NameInfo(jvm_class, index);
    index = jvm_class->constant_pool[jvm_class->super_class - 1].info.Class.name_index - 1;
    superClassName = NameInfo(jvm_class, index);

    printf("\n");
    printf("===========================");
    printf("========Class File=========");
    printf("===========================");
    printf("|-> Minor: %d\n", jvm_class->minor_version);
    printf("|-> Major: %d\n", jvm_class->major_version);
    printf("|-> Constant Pool Count: %d\n", jvm_class->constant_pool_count);
    printf("|-> Access Flags: 0x%x\n", jvm_class->access_flags);
    printf("|-> This.class: <%s>, |CP={%d}|\n", className, jvm_class->this_class);
    printf("|-> Super.class: <%s>, |CP={%d}|\n", superClassName, jvm_class->super_class);
    printf("|-> Interface Count: %d\n", jvm_class->interfaces_count);
    printf("|-> Field Count: %d\n", jvm_class->fields_count);
    printf("|-> Method Count: %d\n", jvm_class->methods_count);
    printf("|-> Attribute Count: %d\n", jvm_class->attributes_count);
	printf("===========================\n");
}

void Exhibitor::ShowInfoOnFile(ClassFile* jvm_class, FILE* file){

}

void Exhibitor::ShowConstantPool(ClassFile* jvm_class){

}

void Exhibitor::ShowConstantPoolOnFile(ClassFile* jvm_class, FILE* file){

}

void Exhibitor::ShowAttribute(ClassFile* jvm_class, attribute_info* attributeInfo){

}

void Exhibitor::ShowAttributeOnFile(ClassFile* jvm_class, attribute_info* attributeInfo){

}

void Exhibitor::ShowAllAttributes(ClassFile* jvm_class){

}

void Exhibitor::ShowAllAttributesOnFile(ClassFile* jvm_class){

}

void Exhibitor::ShowFields(ClassFile* jvm_class){

}

void Exhibitor::ShowFieldsOnFile(ClassFile* jvm_class){

}

void Exhibitor::ShowInterface(CpInfo cp){

}

void Exhibitor::ShowInterfaceOnFile(ClassFile* jvm_class, CpInfo cp, FILE* file){

}

void Exhibitor::ShowAllInterfaces(ClassFile* jvm_class){

}

void Exhibitor::ShowAllInterfacesOnFile(ClassFile* jvm_class, FILE* file){

}

void Exhibitor::ShowMethods(ClassFile* jvm_class){

}

void Exhibitor::ShowMethodsOnFile(ClassFile* jvm_class, FILE* file){

}

char* Exhibitor::NameInfo(ClassFile* jvm_class, u2 index){
	return nullptr;
}

char* Exhibitor::RefFieldInfo(ClassFile* jvm_class, u2 index){
	return nullptr;
}

char* Exhibitor::MethodInfo(ClassFile* jvm_class, u2 index){
	return nullptr;
}