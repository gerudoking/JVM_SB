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
	char *className, *superClassName;
	int index = jvm_class->constant_pool[jvm_class->this_class - 1].info.Class.name_index - 1;

	className = NameInfo(jvm_class, index);
	index = jvm_class->constant_pool[jvm_class->super_class - 1].info.Class.name_index - 1;
	superClassName = NameInfo(jvm_class, index);

	fprintf(file, "=======Informations========");
	fprintf(file, "|-> Minor: %d\n", jvm_class->minor_version);
	fprintf(file, "|-> Major: %d\n", jvm_class->major_version);
	fprintf(file, "|-> Constant Pool Count: %d\n", jvm_class->constant_pool_count);
	fprintf(file, "|-> Access Flags: 0x%x\n", jvm_class->access_flags);
	fprintf(file, "|-> This.class: <%s>, |CP={%d}|\n", className, jvm_class->this_class);
	fprintf(file, "|-> Super.class: <%s>, |CP={%d}|\n", superClassName, jvm_class->super_class);
	fprintf(file, "|-> Interface Counter: %d\n", jvm_class->interfaces_count);
	fprintf(file, "|-> Field Counter: %d\n", jvm_class->fields_count);
	fprintf(file, "|-> Method Counter: %d\n", jvm_class->methods_count);
	fprintf(file, "|-> Attribute Counter: %d\n", jvm_class->attributes_count);
	fprintf(file, "=========================\n");
	fprintf(file, "\n");

	free(className);
	free(superClassName);
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
	switch (cp.tag) {
	case CONSTANTClass:
		printf("Tag: ");
		printf("%" PRIu8 "\n", cp.info.Class.tag);
		printf("Index Name: ");
		printf("%" PRIu16 "\n", cp.info.Class.name_index);
		break;
	case CONSTANTFieldref:
		printf("Tag: ");
		printf("%" PRIu8 "\n", cp.info.Fieldref.tag);
		printf("Index Class: ");
		printf("%" PRIu16 "\n", cp.info.Fieldref.class_index);
		printf("Index Name and Type: ");
		printf("%" PRIu16 "\n", cp.info.Fieldref.name_and_type_index);
		break;
	case CONSTANTMethodref:
		printf("Tag: ");
		printf("%" PRIu8 "\n", cp.info.Methodref.tag);
		printf("Index Class: ");
		printf("%" PRIu16 "\n", cp.info.Methodref.class_index);
		printf("Index Name and Type: ");
		printf("%" PRIu16 "\n", cp.info.Methodref.name_and_type_index);
		break;
	case CONSTANTInterfaceMethodref:
		printf("Tag: ");
		printf("%" PRIu8 "\n", cp.info.InterfaceMethodref.tag);
		printf("Index Class: ");
		printf("%" PRIu16 "\n", cp.info.InterfaceMethodref.class_index);
		printf("Index Name and Type: ");
		printf("%" PRIu16 "\n", cp.info.InterfaceMethodref.name_and_type_index);
		break;
	case CONSTANTString:
		printf("Tag: ");
		printf("%" PRIu8 "\n", cp.info.String.tag);
		printf("Index String: ");
		printf("%" PRIu16 "\n", cp.info.String.string_index);
		break;
	case CONSTANTInteger:
		printf("Tag: ");
		printf("%" PRIu8 "\n", cp.info.Integer.tag);
		printf("Bytes: ");
		printf("%" PRIu32 "\n", cp.info.Integer.bytes);
		break;
	case CONSTANTFloat:
		printf("Tag: ");
		printf("%" PRIu8 "\n", cp.info.Float.tag);
		printf("Bytes: ");
		printf("%" PRIu32 "\n", cp.info.Float.bytes);
		break;
	case CONSTANTLong:
		printf("Tag: ");
		printf("%" PRIu8 "\n", cp.info.Long.tag);
		printf("High Bytes: ");
		printf("%" PRIu32 "\n", cp.info.Long.high_bytes);
		printf("Low Bytes Bytes: ");
		printf("%" PRIu32 "\n", cp.info.Long.low_bytes);
		break;
	case CONSTANTDouble:
		printf("Tag: ");
		printf("%" PRIu8 "\n", cp.info.Double.tag);
		printf("High Bytes: ");
		printf("%" PRIu32 "\n", cp.info.Double.high_bytes);
		printf("Low Bytes Bytes: ");
		printf("%" PRIu32 "\n", cp.info.Double.low_bytes);
		break;
	case CONSTANTNameAndType:
		printf("Tag: ");
		printf("%" PRIu8 "\n", cp.info.NameAndType.tag);
		printf("Index Name: ");
		printf("%" PRIu16 "\n", cp.info.NameAndType.name_index);
		printf("Index Descriptor: ");
		printf("%" PRIu16 "\n", cp.info.NameAndType.descriptor_index);
		break;
	case CONSTANTUtf8:
		printf("Tag: ");
		printf("%" PRIu8 "\n", cp.info.Utf8.tag);
		for (int i = 0; i < cp.info.Utf8.length; i++) {
			uint8_t byte = cp.info.Utf8.bytes[i];
			char c = byte;
			printf("%c", c);
		}
		break;
	}
}

void Exhibitor::ShowInterfaceOnFile(ClassFile* jvm_class, CpInfo cp, FILE* file){

}

void Exhibitor::ShowAllInterfaces(ClassFile* jvm_class){
	printf("\n");
	printf("===========================");
	printf("====Interfaces=============");
	printf("===========================");
	printf("Interface Counter: %d\n", jvm_class->interfaces_count);
	for (int i = 0; i < jvm_class->interfaces_count; i++) {
		printf("\n~~~> ");
		printf("{%d}: CP={", i);
		printf("%" PRIu16, jvm_class->interfaces[i]);
		printf("}\n");
	}
	printf("\n");
}

void Exhibitor::ShowAllInterfacesOnFile(ClassFile* jvm_class, FILE* file){
	printf("\n");
	printf("===========================");
	printf("====Interfaces=============");
	printf("===========================");
	fprintf(file, "Interface Counter: %d\n", jvm_class->interfaces_count);
	for (int i = 0; i < jvm_class->interfaces_count; i++) {
		fprintf(file, "\n~~~> ");
		fprintf(file, "{%d}: CP={", i);
		fprintf(file, "%" PRIu16, jvm_class->interfaces[i]);
		fprintf(file, "}\n");
	}
	fprintf(file, "\n");
}

void Exhibitor::ShowMethods(ClassFile* jvm_class){

}

void Exhibitor::ShowMethodsOnFile(ClassFile* jvm_class, FILE* file){

}

char* Exhibitor::NameInfo(ClassFile* jvm_class, u2 index)
{
	char *name;
    int i;
    name = (char *) malloc((jvm_class->constant_pool[index].info.Utf8.length + 1) * sizeof(char));
    
    for (i = 0; i < jvm_class->constant_pool[index].info.Utf8.length; i++)
        name[i] = jvm_class->constant_pool[index].info.Utf8.bytes[i];
    
    name[i] = '\0';
    return name;
}

char* Exhibitor::RefFieldInfo(ClassFile* jvm_class, u2 index)
{
    return nullptr;
}

char* Exhibitor::MethodInfo(ClassFile* jvm_class, u2 index){
	return nullptr;
}