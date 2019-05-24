#include "Exhibitor.h"

Exhibitor::Exhibitor() {

}

Exhibitor::~Exhibitor() {

}

void Exhibitor::ShowInfo(ClassFile* jvm_class) {
	char *className, *superClassName;
	int index = jvm_class->constant_pool[jvm_class->this_class - 1].info.Class.name_index - 1;
	className = NameInfo(jvm_class, index);
	index = jvm_class->constant_pool[jvm_class->super_class - 1].info.Class.name_index - 1;
	superClassName = NameInfo(jvm_class, index);

	printf("\n");
	printf("##############################");
	printf("######### Class File #########");
	printf("##############################");
	printf("|-> Minor: %d\n", jvm_class->minor_version);
	printf("|-> Major: %d\n", jvm_class->major_version);
	printf("|-> Constant Pool Count: %d\n", jvm_class->constant_pool_count);
	printf("|-> Access Flags: 0x%x\n", jvm_class->access_flags);
	printf("|-> This.class: %s, |CP={%d}|\n", className, jvm_class->this_class);
	printf("|-> Super.class: %s, |CP={%d}|\n", superClassName, jvm_class->super_class);
	printf("|-> Interface Count: %d\n", jvm_class->interfaces_count);
	printf("|-> Field Count: %d\n", jvm_class->fields_count);
	printf("|-> Method Count: %d\n", jvm_class->methods_count);
	printf("|-> Attribute Count: %d\n", jvm_class->attributes_count);
	printf("######################################################\n\n");
}

void Exhibitor::ShowInfoOnFile(ClassFile* jvm_class, FILE* file) {
	char *className, *superClassName;
	int index = jvm_class->constant_pool[jvm_class->this_class - 1].info.Class.name_index - 1;

	className = NameInfo(jvm_class, index);
	index = jvm_class->constant_pool[jvm_class->super_class - 1].info.Class.name_index - 1;
	superClassName = NameInfo(jvm_class, index);

	fprintf(file, "############ Informations ############");
	fprintf(file, "|-> Minor: %d\n", jvm_class->minor_version);
	fprintf(file, "|-> Major: %d\n", jvm_class->major_version);
	fprintf(file, "|-> Constant Pool Count: %d\n", jvm_class->constant_pool_count);
	fprintf(file, "|-> Access Flags: 0x%x\n", jvm_class->access_flags);
	fprintf(file, "|-> This.class: %s, |CP={%d}|\n", className, jvm_class->this_class);
	fprintf(file, "|-> Super.class: %s, |CP={%d}|\n", superClassName, jvm_class->super_class);
	fprintf(file, "|-> Interface Counter: %d\n", jvm_class->interfaces_count);
	fprintf(file, "|-> Field Counter: %d\n", jvm_class->fields_count);
	fprintf(file, "|-> Method Counter: %d\n", jvm_class->methods_count);
	fprintf(file, "|-> Attribute Counter: %d\n", jvm_class->attributes_count);
	fprintf(file, "######################################################\n\n");

	free(className);
	free(superClassName);
}

void Exhibitor::ShowConstantPool(ClassFile* jvm_class) {
	u8 longTemp;

	char *reference_name = NULL;
	char *reference_name2 = NULL;
	char *reference_name3 = NULL;

	printf("\n\n################## EXHIBITOR FILE .class ##################\n\n");
	printf("###### constant-pool ######\n");
	printf("jvm_class->constant_pool_count = %d\n", jvm_class->constant_pool_count);

	int index = 0;
	float float_value;
	double double_value;

	for (int i = 0; i < (jvm_class->constant_pool_count - 1); i++) {
		printf("\n===> ");
		switch (jvm_class->constant_pool[i].tag) {
		case CONSTANTClass:
			index = jvm_class->constant_pool[i].info.Class.name_index - 1;
			reference_name = NameInfo(jvm_class, index);
			printf("{%d} const_class:\n", (i + 1));
			printf("jvm_class = %s, |CP={%d}|\n", reference_name, jvm_class->constant_pool[i].info.Class.name_index);
			break;

		case CONSTANTFieldref:
			index = jvm_class->constant_pool[i].info.Fieldref.class_index - 1;
			index = jvm_class->constant_pool[index].info.Class.name_index - 1;
			reference_name = NameInfo(jvm_class, index);
			printf("{%d} const_ref_field:\n", (i + 1));
			printf("jvm_class: %s, |CP={%d}|\n", reference_name, jvm_class->constant_pool[i].info.Fieldref.class_index);
			index = jvm_class->constant_pool[i].info.Fieldref.name_and_type_index - 1;
			reference_name = NameInfo(jvm_class, jvm_class->constant_pool[index].info.NameAndType.name_index - 1);
			reference_name2 = NameInfo(jvm_class, jvm_class->constant_pool[index].info.NameAndType.descriptor_index - 1);
			printf("TypeAndName: <%s%s>, |CP={%d}|\n", reference_name, reference_name2,
					jvm_class->constant_pool[i].info.Fieldref.name_and_type_index);
			break;

		case CONSTANTMethodref:
			index = jvm_class->constant_pool[i].info.Fieldref.class_index - 1;
			index = jvm_class->constant_pool[index].info.Class.name_index - 1;
			reference_name = NameInfo(jvm_class, index);
			printf("{%d} cont_ref_method:\n", (i + 1));
			printf("jvm_class: %s, |CP={%d}|\n", reference_name, jvm_class->constant_pool[i].info.Methodref.class_index);
			index = jvm_class->constant_pool[i].info.Fieldref.name_and_type_index - 1;
			reference_name = NameInfo(jvm_class, jvm_class->constant_pool[index].info.NameAndType.name_index - 1);
			reference_name2 = NameInfo(jvm_class, jvm_class->constant_pool[index].info.NameAndType.descriptor_index - 1);
			printf("TypeAndName: <%s%s>, |CP={%d}|\n", reference_name, reference_name2,
					jvm_class->constant_pool[i].info.Methodref.name_and_type_index);
			break;

		case CONSTANTInterfaceMethodref:
			index = jvm_class->constant_pool[jvm_class->constant_pool[i].info.InterfaceMethodref.class_index - 1].info.Class.name_index - 1;
			reference_name = NameInfo(jvm_class, index);
			index =
					jvm_class->constant_pool[jvm_class->constant_pool[i].info.InterfaceMethodref.name_and_type_index - 1].info.NameAndType.name_index
							- 1;
			reference_name2 = NameInfo(jvm_class, index);
			index =
					jvm_class->constant_pool[jvm_class->constant_pool[i].info.InterfaceMethodref.name_and_type_index - 1].info.NameAndType.descriptor_index
							- 1;
			reference_name3 = NameInfo(jvm_class, index);
			reference_name2 = strcat(reference_name2, reference_name3);
			printf("{%d} const_interface_ref_method:\n", (i + 1));
			printf("jvm_class: %s, |CP={%d}|\n", reference_name, jvm_class->constant_pool[i].info.InterfaceMethodref.class_index);
			printf("TypeAndName: %s, |CP={%d}|\n", reference_name2,
					jvm_class->constant_pool[i].info.InterfaceMethodref.name_and_type_index);
			break;

		case CONSTANTString:
			index = jvm_class->constant_pool[i].info.String.string_index - 1;
			reference_name = NameInfo(jvm_class, index);
			printf("{%d} const_string:\n", (i + 1));
			printf("string: %s, |CP={%d}|\n", reference_name, jvm_class->constant_pool[i].info.String.string_index);
			break;

		case CONSTANTInteger:
			printf("{%d} const_int: \n", (i + 1));
			printf("Bytes: 0x%x\n", jvm_class->constant_pool[i].info.Integer.bytes);
			printf("Integer: %d\n", jvm_class->constant_pool[i].info.Integer.bytes);
			break;

		case CONSTANTFloat:
			memcpy(&float_value, &(jvm_class->constant_pool[i].info.Float.bytes), sizeof(u4));
			printf("{%d} const_float:\n", (i + 1));
			printf("Bytes: 0x%x\n", jvm_class->constant_pool[i].info.Float.bytes);
			printf("Float: %f\n", float_value);
			break;

		case CONSTANTLong:
			longTemp = (u8) jvm_class->constant_pool[i].info.Long.high_bytes << 32;
			longTemp = longTemp | jvm_class->constant_pool[i].info.Long.low_bytes;
			printf("{%d} const_long:\n", (i + 1));
			printf("High: 0x%x\n", jvm_class->constant_pool[i].info.Long.high_bytes);
			printf("Low: t0x%x\n", jvm_class->constant_pool[i].info.Long.low_bytes);
			printf("Long: %lld\n", longTemp);
			i++;
			printf("[%d]\n", (i + 1));
			break;

		case CONSTANTDouble:
			longTemp = (u8) jvm_class->constant_pool[i].info.Double.high_bytes << 32;
			longTemp = longTemp | jvm_class->constant_pool[i].info.Double.low_bytes;
			memcpy(&double_value, &longTemp, sizeof(u8));
			printf("{%d} const_double :\n", (i + 1));
			printf("High: 0x%x\n", jvm_class->constant_pool[i].info.Double.high_bytes);
			printf("Low: 0x%x\n", jvm_class->constant_pool[i].info.Double.low_bytes);
			printf("Double: %f\n", double_value);
			i++;
			printf("[%d]\n", (i + 1));
			break;

		case CONSTANTNameAndType:
			index = jvm_class->constant_pool[i].info.NameAndType.name_index - 1;
			reference_name = NameInfo(jvm_class, index);
			index = jvm_class->constant_pool[i].info.NameAndType.descriptor_index - 1;
			reference_name2 = NameInfo(jvm_class, index);
			printf("{%d} const_typeandname:\n", (i + 1));
			printf("Name: %s, |CP={%d}|\n", reference_name, jvm_class->constant_pool[i].info.NameAndType.name_index);
			printf("Descriptor: %s, |CP={%d}|\n", reference_name2, jvm_class->constant_pool[i].info.NameAndType.descriptor_index);
			break;

		case CONSTANTUtf8:
			printf("{%d} const_utf8:\n", (i + 1));
			printf("Byte Vector Size:%d\n", jvm_class->constant_pool[i].info.Utf8.length);
			printf("String Size: %d\n", jvm_class->constant_pool[i].info.Utf8.length);
			printf("String: ");
			for (int j = 0; j < jvm_class->constant_pool[i].info.Utf8.length; j++)
				printf("%c", jvm_class->constant_pool[i].info.Utf8.bytes[j]);
			printf("\n");
			break;
		}
	}

	printf("\n");
	free(reference_name);
	free(reference_name2);
	free(reference_name3);
}

void Exhibitor::ShowConstantPoolOnFile(ClassFile* jvm_class, FILE* file) {
	u8 longTemp;

	char *reference_name = NULL;
	char *reference_name2 = NULL;
	char *reference_name3 = NULL;

	fprintf(file, "\n\n################## EXHIBITOR FILE .class ##################\n\n");
	fprintf(file, "###### constant-pool ######\n");
	fprintf(file, "jvm_class->constant_pool_count = %d\n", jvm_class->constant_pool_count);

	int index = 0;
	float float_value;
	double double_value;

	for (int i = 0; i < (jvm_class->constant_pool_count - 1); i++) {
		fprintf(file, "\n===> ");
		switch (jvm_class->constant_pool[i].tag) {
		case CONSTANTClass:
			index = jvm_class->constant_pool[i].info.Class.name_index - 1;
			reference_name = NameInfo(jvm_class, index);
			fprintf(file, "{%d} const_class:\n", (i + 1));
			fprintf(file, "jvm_class = %s, |CP={%d}|\n", reference_name, jvm_class->constant_pool[i].info.Class.name_index);
			break;

		case CONSTANTFieldref:
			index = jvm_class->constant_pool[i].info.Fieldref.class_index - 1;
			index = jvm_class->constant_pool[index].info.Class.name_index - 1;
			reference_name = NameInfo(jvm_class, index);
			fprintf(file, "{%d} const_ref_field:\n", (i + 1));
			fprintf(file, "jvm_class: %s, |CP={%d}|\n", reference_name, jvm_class->constant_pool[i].info.Fieldref.class_index);
			index = jvm_class->constant_pool[i].info.Fieldref.name_and_type_index - 1;
			reference_name = NameInfo(jvm_class, jvm_class->constant_pool[index].info.NameAndType.name_index - 1);
			reference_name2 = NameInfo(jvm_class, jvm_class->constant_pool[index].info.NameAndType.descriptor_index - 1);
			fprintf(file, "TypeAndName: <%s%s>, |CP={%d}|\n", reference_name, reference_name2,
					jvm_class->constant_pool[i].info.Fieldref.name_and_type_index);
			break;

		case CONSTANTMethodref:
			index = jvm_class->constant_pool[i].info.Fieldref.class_index - 1;
			index = jvm_class->constant_pool[index].info.Class.name_index - 1;
			reference_name = NameInfo(jvm_class, index);
			fprintf(file, "{%d} cont_ref_method:\n", (i + 1));
			fprintf(file, "jvm_class: %s, |CP={%d}|\n", reference_name, jvm_class->constant_pool[i].info.Methodref.class_index);
			index = jvm_class->constant_pool[i].info.Fieldref.name_and_type_index - 1;
			reference_name = NameInfo(jvm_class, jvm_class->constant_pool[index].info.NameAndType.name_index - 1);
			reference_name2 = NameInfo(jvm_class, jvm_class->constant_pool[index].info.NameAndType.descriptor_index - 1);
			fprintf(file, "TypeAndName: <%s%s>, |CP={%d}|\n", reference_name, reference_name2,
					jvm_class->constant_pool[i].info.Methodref.name_and_type_index);
			break;

		case CONSTANTInterfaceMethodref:
			index = jvm_class->constant_pool[jvm_class->constant_pool[i].info.InterfaceMethodref.class_index - 1].info.Class.name_index - 1;
			reference_name = NameInfo(jvm_class, index);
			index =
					jvm_class->constant_pool[jvm_class->constant_pool[i].info.InterfaceMethodref.name_and_type_index - 1].info.NameAndType.name_index
							- 1;
			reference_name2 = NameInfo(jvm_class, index);
			index =
					jvm_class->constant_pool[jvm_class->constant_pool[i].info.InterfaceMethodref.name_and_type_index - 1].info.NameAndType.descriptor_index
							- 1;
			reference_name3 = NameInfo(jvm_class, index);
			reference_name2 = strcat(reference_name2, reference_name3);
			fprintf(file, "{%d} const_interface_ref_method:\n", (i + 1));
			fprintf(file, "jvm_class: %s, |CP={%d}|\n", reference_name, jvm_class->constant_pool[i].info.InterfaceMethodref.class_index);
			fprintf(file, "TypeAndName: %s, |CP={%d}|\n", reference_name2,
					jvm_class->constant_pool[i].info.InterfaceMethodref.name_and_type_index);
			break;

		case CONSTANTString:
			index = jvm_class->constant_pool[i].info.String.string_index - 1;
			reference_name = NameInfo(jvm_class, index);
			fprintf(file, "{%d} const_string:\n", (i + 1));
			fprintf(file, "string: %s, |CP={%d}|\n", reference_name, jvm_class->constant_pool[i].info.String.string_index);
			break;

		case CONSTANTInteger:
			fprintf(file, "{%d} const_int: \n", (i + 1));
			fprintf(file, "Bytes: 0x%x\n", jvm_class->constant_pool[i].info.Integer.bytes);
			fprintf(file, "Integer: %d\n", jvm_class->constant_pool[i].info.Integer.bytes);
			break;

		case CONSTANTFloat:
			memcpy(&float_value, &(jvm_class->constant_pool[i].info.Float.bytes), sizeof(u4));
			fprintf(file, "{%d} const_float:\n", (i + 1));
			fprintf(file, "Bytes: 0x%x\n", jvm_class->constant_pool[i].info.Float.bytes);
			fprintf(file, "Float: %f\n", float_value);
			break;

		case CONSTANTLong:
			longTemp = (u8) jvm_class->constant_pool[i].info.Long.high_bytes << 32;
			longTemp = longTemp | jvm_class->constant_pool[i].info.Long.low_bytes;
			fprintf(file, "{%d} const_long:\n", (i + 1));
			fprintf(file, "High: 0x%x\n", jvm_class->constant_pool[i].info.Long.high_bytes);
			fprintf(file, "Low: t0x%x\n", jvm_class->constant_pool[i].info.Long.low_bytes);
			fprintf(file, "Long: %lld\n", longTemp);
			i++;
			fprintf(file, "[%d]\n", (i + 1));
			break;

		case CONSTANTDouble:
			longTemp = (u8) jvm_class->constant_pool[i].info.Double.high_bytes << 32;
			longTemp = longTemp | jvm_class->constant_pool[i].info.Double.low_bytes;
			memcpy(&double_value, &longTemp, sizeof(u8));
			fprintf(file, "{%d} const_double :\n", (i + 1));
			fprintf(file, "High: 0x%x\n", jvm_class->constant_pool[i].info.Double.high_bytes);
			fprintf(file, "Low: 0x%x\n", jvm_class->constant_pool[i].info.Double.low_bytes);
			fprintf(file, "Double: %f\n", double_value);
			i++;
			fprintf(file, "[%d]\n", (i + 1));
			break;

		case CONSTANTNameAndType:
			index = jvm_class->constant_pool[i].info.NameAndType.name_index - 1;
			reference_name = NameInfo(jvm_class, index);
			index = jvm_class->constant_pool[i].info.NameAndType.descriptor_index - 1;
			reference_name2 = NameInfo(jvm_class, index);
			fprintf(file, "{%d} const_typeandname:\n", (i + 1));
			fprintf(file, "Name: %s, |CP={%d}|\n", reference_name, jvm_class->constant_pool[i].info.NameAndType.name_index);
			fprintf(file, "Descriptor: %s, |CP={%d}|\n", reference_name2, jvm_class->constant_pool[i].info.NameAndType.descriptor_index);
			break;

		case CONSTANTUtf8:
			fprintf(file, "{%d} const_utf8:\n", (i + 1));
			fprintf(file, "Byte Vector Size: %d\n", jvm_class->constant_pool[i].info.Utf8.length);
			fprintf(file, "String Size: %d\n", jvm_class->constant_pool[i].info.Utf8.length);
			fprintf(file, "String: ");
			for (int j = 0; j < jvm_class->constant_pool[i].info.Utf8.length; j++)
				fprintf(file, "%c", jvm_class->constant_pool[i].info.Utf8.bytes[j]);
			fprintf(file, "\n");
			break;
		}
	}

	fprintf(file, "\n");
	free(reference_name);
	free(reference_name2);
	free(reference_name3);
}

void Exhibitor::ShowAttribute(ClassFile* jvm_class, attribute_info* attributeInfo) {
	char *reference_name = NULL;
	char *attributeType = NULL;
	u8 longTemp;
	float float_value;
	double double_value;
	u2 index = attributeInfo->attribute_name_index - 1;
	int iteration;

	attributeType = (char *) malloc((jvm_class->constant_pool[index].info.Utf8.length + 1) * sizeof(char));

	for (iteration = 0; iteration < jvm_class->constant_pool[index].info.Utf8.length; iteration++) {
		printf("%c", jvm_class->constant_pool[index].info.Utf8.bytes[iteration]);
		attributeType[iteration] = jvm_class->constant_pool[index].info.Utf8.bytes[iteration];
	}

	attributeType[iteration] = '\0';
	index = attributeInfo->attribute_name_index - 1;
	reference_name = NameInfo(jvm_class, index);
	printf("\n\tIndex Name = %s, |CP={%d}|\n", reference_name, attributeInfo->attribute_name_index);
	printf("\tattribute_length = %d\n", attributeInfo->attribute_length);
	free(reference_name);

	if (attributeInfo->attribute_length > 0) {
		if (!strcmp(attributeType, "ConstantValue")) {
			int i;
			u2 indexTemp;
			index = attributeInfo->info.ConstantValue.constantvalue_index - 1;
			switch (jvm_class->constant_pool[index].tag) {
			case CONSTANTInteger:
				i = (int32_t) jvm_class->constant_pool[index].info.Integer.bytes;
				printf("\nconstantvalue_index = %d, |CP={%d}|", i, attributeInfo->info.ConstantValue.constantvalue_index);
				break;

			case CONSTANTLong:
				longTemp = (u8) jvm_class->constant_pool[index].info.Long.high_bytes << 32
						| jvm_class->constant_pool[index].info.Long.low_bytes;
				printf("\nconstantvalue_index = %ld, |CP={%d}|", longTemp, attributeInfo->info.ConstantValue.constantvalue_index);
				break;

			case CONSTANTFloat:
				memcpy(&float_value, &(jvm_class->constant_pool[index].info.Float.bytes), sizeof(u4));
				printf("\nconstantvalue_index = %f, |CP={%d}|", float_value, attributeInfo->info.ConstantValue.constantvalue_index);
				break;

			case CONSTANTDouble:
				longTemp = (u8) jvm_class->constant_pool[index].info.Double.high_bytes << 32
						| jvm_class->constant_pool[index].info.Double.low_bytes;
				memcpy(&double_value, &(jvm_class->constant_pool[index].info.Float.bytes), sizeof(u8));
				printf("\nconstantvalue_index = %f, |CP={%d}|", double_value, attributeInfo->info.ConstantValue.constantvalue_index);
				break;

			case CONSTANTString:
				indexTemp = jvm_class->constant_pool[index].info.String.string_index - 1;
				reference_name = NameInfo(jvm_class, indexTemp);
				printf("\nconstantvalue_index = %s, |CP={%d}|", reference_name, attributeInfo->info.ConstantValue.constantvalue_index);
				break;
			}
		} else if (!strcmp(attributeType, "Code")) {
			printf("\t### OTHER DATA ###\n");
			printf("\tmax_stack = %d\n", attributeInfo->info.CodeAttribute.max_stack);
			printf("\tmax_locals = %d\n", attributeInfo->info.CodeAttribute.max_locals);
			printf("\tcode_length = %d\n", attributeInfo->info.CodeAttribute.code_length);
			printf("\tCode: \n");
			for (int i = 0; i < attributeInfo->info.CodeAttribute.code_length; i++) {
				Instruction map[0xCA];
				Mnemonics(map);
				u1 opcode = attributeInfo->info.CodeAttribute.code[i], instrIndex1, instrIndex2;
				u2 instrIndex;
				int16_t offset;
				char *instrRef;
				printf("\t\t\t%d: %s\t", i, map[opcode].mnemonic);
				int j;
				double double_value;
				switch (map[opcode].req_cp) {
				case REQ_METHODREF_1:
					instrIndex = attributeInfo->info.CodeAttribute.code[++i];
					instrRef = MethodInfo(jvm_class, instrIndex - 1);
					printf("%s, |CP={%d}|\t", instrRef, instrIndex);
					break;
				case REQ_METHODREF_2:
					instrIndex1 = attributeInfo->info.CodeAttribute.code[++i];
					instrIndex2 = attributeInfo->info.CodeAttribute.code[++i];
					instrIndex = (instrIndex2 | (instrIndex1 << 8));
					instrRef = MethodInfo(jvm_class, instrIndex - 1);
					printf("%s, |CP={%d}|\t", instrRef, instrIndex);
					break;
				case REQ_FIELDREF:
					instrIndex1 = attributeInfo->info.CodeAttribute.code[++i];
					instrIndex2 = attributeInfo->info.CodeAttribute.code[++i];
					instrIndex = (instrIndex2 | (instrIndex1 << 8));
					instrRef = RefFieldInfo(jvm_class, instrIndex - 1);
					printf("%s, |CP={%d}|\t", instrRef, instrIndex);
					break;
				case REQ_JMPREF:
					instrIndex1 = attributeInfo->info.CodeAttribute.code[++i];
					instrIndex2 = attributeInfo->info.CodeAttribute.code[++i];
					offset = (int16_t) (instrIndex2 | (instrIndex1 << 8));
					printf("%d\t(%d)\t", (offset - 2) + i, offset);
					break;
				case REQ_LDCREF_1:
					instrIndex = attributeInfo->info.CodeAttribute.code[++i] - 1;
					printf("%d\t", instrIndex + 1);
					switch (jvm_class->constant_pool[instrIndex].tag) {
					case CONSTANTInteger:
						printf("%d\t", jvm_class->constant_pool[instrIndex].info.Integer.bytes);
						break;
					case CONSTANTFloat:
						memcpy(&float_value, &(jvm_class->constant_pool[instrIndex].info.Float.bytes), sizeof(u4));
						printf("%f\t", float_value);
						break;
					case CONSTANTLong:
						longTemp = (u8) jvm_class->constant_pool[instrIndex].info.Long.high_bytes << 32;
						longTemp = longTemp | jvm_class->constant_pool[instrIndex].info.Long.low_bytes;
						printf("%ld\t", longTemp);
						break;
					case CONSTANTDouble:
						longTemp = (u8) jvm_class->constant_pool[instrIndex].info.Double.high_bytes << 32;
						longTemp = longTemp | jvm_class->constant_pool[instrIndex].info.Double.low_bytes;
						memcpy(&double_value, &longTemp, sizeof(u8));
						printf("%f\t", double_value);
						break;
					}
					break;
				case REQ_LDCREF_2:
					instrIndex1 = attributeInfo->info.CodeAttribute.code[++i];
					instrIndex2 = attributeInfo->info.CodeAttribute.code[++i];
					instrIndex = (instrIndex2 | (instrIndex1 << sizeof(u1))) - 1;
					printf("%d\t", instrIndex + 1);
					switch (jvm_class->constant_pool[instrIndex].tag) {
					case CONSTANTInteger:
						printf("%d\t", jvm_class->constant_pool[instrIndex].info.Integer.bytes);
						break;
					case CONSTANTFloat:
						memcpy(&float_value, &(jvm_class->constant_pool[instrIndex].info.Float.bytes), sizeof(u4));
						printf("%f\t", float_value);
						break;
					case CONSTANTLong:
						longTemp = (u8) jvm_class->constant_pool[instrIndex].info.Long.high_bytes << 32;
						longTemp = longTemp | jvm_class->constant_pool[instrIndex].info.Long.low_bytes;
						printf("%ld\t", longTemp);
						break;
					case CONSTANTDouble:
						longTemp = (u8) jvm_class->constant_pool[instrIndex].info.Double.high_bytes << 32;
						longTemp = longTemp | jvm_class->constant_pool[instrIndex].info.Double.low_bytes;
						memcpy(&double_value, &longTemp, sizeof(u8));
						printf("%f\t", double_value);
						break;
					}
					break;
				case REQ_ARRAYREF:
					instrIndex = attributeInfo->info.CodeAttribute.code[++i];
					printf("%d\t", instrIndex);
					switch (instrIndex) {
					case 0:
						printf("(ref)\t");
						break;
					case 4:
						printf("(boolean)\t");
						break;
					case 5:
						printf("(char)\t");
						break;
					case 6:
						printf("(float)\t");
						break;
					case 7:
						printf("(double)\t");
						break;
					case 8:
						printf("(byte)\t");
						break;
					case 9:
						printf("(short)\t");
						break;
					case 10:
						printf("(int)\t");
						break;
					case 11:
						printf("(long)\t");
						break;
					default:
						break;
					}
					break;
				case REQ_IINCREF:
					instrIndex1 = attributeInfo->info.CodeAttribute.code[++i];
					instrIndex2 = attributeInfo->info.CodeAttribute.code[++i];
					printf("%d by %d\t", instrIndex1, instrIndex2);
					break;
				default:
					for (j = 0; j < map[opcode].operators; j++)
						printf("%d\t", attributeInfo->info.CodeAttribute.code[++i]);
					break;
				}
				printf("\n");
			}

			printf("\n\texception_table_length = %d\n", attributeInfo->info.CodeAttribute.exception_table_length);
			if (attributeInfo->info.CodeAttribute.exception_table_length > 0) {
				printf("\tStart PC\tEnd PC\tHandler PC\tCatch Type\n");
				for (int i = 0; i < attributeInfo->info.CodeAttribute.exception_table_length; i++) {
					printf("%d: %d\t", i, attributeInfo->info.CodeAttribute.exception_table[i].start_pc);
					printf("%d\t", attributeInfo->info.CodeAttribute.exception_table[i].end_pc);
					printf("%d\t", attributeInfo->info.CodeAttribute.exception_table[i].handler_pc);
					printf("%d\n", attributeInfo->info.CodeAttribute.exception_table[i].catch_type);
				}
			}

			printf("\tCode's attributes_count = %d\n", attributeInfo->info.CodeAttribute.attributes_count);
			for (int k = 0; k < attributeInfo->info.CodeAttribute.attributes_count; k++) {
				printf("\t{%d} ", k);
				ShowAttribute(jvm_class, &(attributeInfo->info.CodeAttribute.attributes[k]));
			}
		} else if (!strcmp(attributeType, "Exceptions")) {
			printf("\tnumber_of_exceptions = %d\n", attributeInfo->info.Exception.number_of_exceptions);
			for (int i = 0; i < attributeInfo->info.Exception.number_of_exceptions; i++) {
				index = attributeInfo->info.Exception.exception_index_table[i] - 1;
				index = jvm_class->constant_pool[index].info.Class.name_index - 1;
				reference_name = NameInfo(jvm_class, index);
				printf("\tException Index = %s, |CP={%d}|\n", reference_name, attributeInfo->info.Exception.exception_index_table[i]);
				free(reference_name);
			}
		} else if (!strcmp(attributeType, "InnerClasses")) {
			printf("\tnumber_of_classes = %d\n", attributeInfo->info.InnerClasses.number_of_classes);
			for (int i = 0; i < attributeInfo->info.InnerClasses.number_of_classes; i++) {
				free(reference_name);
				index = attributeInfo->info.InnerClasses.classes[i].inner_class_info_index - 1;
				index = jvm_class->constant_pool[index].info.Class.name_index - 1;
				reference_name = NameInfo(jvm_class, index);
				printf("\t\tinner_class_info_index = %s, |CP={%d}|\n", reference_name,
						attributeInfo->info.InnerClasses.classes[i].inner_class_info_index);
				index = attributeInfo->info.InnerClasses.classes[i].outer_class_info_index - 1;
				index = jvm_class->constant_pool[index].info.Class.name_index - 1;
				free(reference_name);
				reference_name = NameInfo(jvm_class, index);
				printf("\t\touter_class_info_index = %s, |CP={%d}|\n", reference_name,
						attributeInfo->info.InnerClasses.classes[i].outer_class_info_index);
				index = attributeInfo->info.InnerClasses.classes[i].inner_class_info_index - 1;
				free(reference_name);
				reference_name = NameInfo(jvm_class, index);
				printf("\t\tinner_name_index = %s, |CP={%d}|\n", reference_name,
						attributeInfo->info.InnerClasses.classes[i].inner_name_index);
				printf("\t\tinner_class_access_flags = %d\n", attributeInfo->info.InnerClasses.classes[i].inner_class_access_flags);
			}
		} else if (!strcmp(attributeType, "SourceFile")) {
			index = attributeInfo->info.Sourcefile.sourcefile_index - 1;
			reference_name = NameInfo(jvm_class, index);
			printf("\tsourcefile_index = %s, |CP={%d}|\n", reference_name, attributeInfo->info.Sourcefile.sourcefile_index);
			free(reference_name);
		} else if (!strcmp(attributeType, "LineNumberTable")) {
			printf("\tLine Numbers = %d\n", attributeInfo->info.LineNumberTable.line_number_table_length);
			if (attributeInfo->info.LineNumberTable.line_number_table_length > 0) {
				printf("\n\tStart PC\tLine Number\n");
				for (int i = 0; i < attributeInfo->info.LineNumberTable.line_number_table_length; i++) {
					printf("\t\t%d: %d", i, attributeInfo->info.LineNumberTable.line_number_table[i].start_pc);
					printf("\t\t%d\n", attributeInfo->info.LineNumberTable.line_number_table[i].line_number);
				}
			}
		} else if (!strcmp(attributeType, "LocalVariableTable")) {
			printf("\tTable Length = %d\n", attributeInfo->info.LocalVariableTable.local_variable_table_length);
			for (int i = 0; i < attributeInfo->info.LocalVariableTable.local_variable_table_length; i++) {
				free(reference_name);
				printf("\t\tStart PC = %d\n", attributeInfo->info.LocalVariableTable.local_variable_table[i].start_pc);
				printf("\t\tLength = %d\n", attributeInfo->info.LocalVariableTable.local_variable_table[i].length);
				index = attributeInfo->info.LocalVariableTable.local_variable_table[i].name_index - 1;
				reference_name = NameInfo(jvm_class, index);
				printf("\t\tName Index = %s, |CP={%d}|\n", reference_name,
						attributeInfo->info.LocalVariableTable.local_variable_table[i].name_index);
				index = attributeInfo->info.LocalVariableTable.local_variable_table[i].descriptor_index - 1;
				free(reference_name);
				reference_name = NameInfo(jvm_class, index);
				printf("\t\tDescriptor Index = %s, |CP={%d}|\n", reference_name,
						attributeInfo->info.LocalVariableTable.local_variable_table[i].descriptor_index);
				printf("\t\tIndex: %d\n", attributeInfo->info.LocalVariableTable.local_variable_table[i].index);
			}
		} else {
			printf("\tDefault: \t");
			for (int i = 0; i < attributeInfo->attribute_length; i++)
				printf("\t%x", attributeInfo->info.Default.data[i]);
			printf("\n");
		}
	}

	free(reference_name);
	free(attributeType);
}

void Exhibitor::ShowAttributeOnFile(ClassFile* jvm_class, attribute_info* attributeInfo, FILE *file) {
	char *reference_name = NULL;
	char *attributeType = NULL;
	u8 longTemp;
	float float_value;
	double double_value;
	u2 index = attributeInfo->attribute_name_index - 1;
	int iteration;

	attributeType = (char *) malloc((jvm_class->constant_pool[index].info.Utf8.length + 1) * sizeof(char));

	for (iteration = 0; iteration < jvm_class->constant_pool[index].info.Utf8.length; iteration++) {
		fprintf(file, "%c", jvm_class->constant_pool[index].info.Utf8.bytes[iteration]);
		attributeType[iteration] = jvm_class->constant_pool[index].info.Utf8.bytes[iteration];
	}

	attributeType[iteration] = '\0';
	index = attributeInfo->attribute_name_index - 1;
	reference_name = NameInfo(jvm_class, index);
	fprintf(file, "\n\tIndex Name = %s, |CP={%d}|\n", reference_name, attributeInfo->attribute_name_index);
	fprintf(file, "\tattribute_length = %d\n", attributeInfo->attribute_length);
	free(reference_name);

	if (attributeInfo->attribute_length > 0) {
		if (!strcmp(attributeType, "ConstantValue")) {
			int i;
			u2 indexTemp;
			index = attributeInfo->info.ConstantValue.constantvalue_index - 1;
			switch (jvm_class->constant_pool[index].tag) {
			case CONSTANTInteger:
				i = (int32_t) jvm_class->constant_pool[index].info.Integer.bytes;
				fprintf(file, "\nconstantvalue_index = %d, |CP={%d}|", i, attributeInfo->info.ConstantValue.constantvalue_index);
				break;

			case CONSTANTLong:
				longTemp = (u8) jvm_class->constant_pool[index].info.Long.high_bytes << 32
						| jvm_class->constant_pool[index].info.Long.low_bytes;
				fprintf(file, "\nconstantvalue_index = %ld, |CP={%d}|", longTemp, attributeInfo->info.ConstantValue.constantvalue_index);
				break;

			case CONSTANTFloat:
				memcpy(&float_value, &(jvm_class->constant_pool[index].info.Float.bytes), sizeof(u4));
				fprintf(file, "\nconstantvalue_index = %f, |CP={%d}|", float_value, attributeInfo->info.ConstantValue.constantvalue_index);
				break;

			case CONSTANTDouble:
				longTemp = (u8) jvm_class->constant_pool[index].info.Double.high_bytes << 32
						| jvm_class->constant_pool[index].info.Double.low_bytes;
				memcpy(&double_value, &(jvm_class->constant_pool[index].info.Float.bytes), sizeof(u8));
				fprintf(file, "\nconstantvalue_index = %f, |CP={%d}|", double_value, attributeInfo->info.ConstantValue.constantvalue_index);
				break;

			case CONSTANTString:
				indexTemp = jvm_class->constant_pool[index].info.String.string_index - 1;
				reference_name = NameInfo(jvm_class, indexTemp);
				fprintf(file, "\nconstantvalue_index = %s, |CP={%d}|", reference_name,
						attributeInfo->info.ConstantValue.constantvalue_index);
				break;
			}
		} else if (!strcmp(attributeType, "Code")) {
			fprintf(file, "\t### OTHER DATA ###\n");
			fprintf(file, "\tmax_stack = %d\n", attributeInfo->info.CodeAttribute.max_stack);
			fprintf(file, "\tmax_locals = %d\n", attributeInfo->info.CodeAttribute.max_locals);
			fprintf(file, "\tcode_length = %d\n", attributeInfo->info.CodeAttribute.code_length);
			fprintf(file, "\tCode: \n");
			for (int i = 0; i < attributeInfo->info.CodeAttribute.code_length; i++) {
				Instruction map[0xCA];
				Mnemonics(map);
				u1 opcode = attributeInfo->info.CodeAttribute.code[i], instrIndex1, instrIndex2;
				u2 instrIndex;
				int16_t offset;
				char *instrRef;
				fprintf(file, "\t\t\t%d: %s\t", i, map[opcode].mnemonic);
				int j;
				double double_value;
				switch (map[opcode].req_cp) {
				case REQ_METHODREF_1:
					instrIndex = attributeInfo->info.CodeAttribute.code[++i];
					instrRef = MethodInfo(jvm_class, instrIndex - 1);
					fprintf(file, "%s, |CP={%d}|\t", instrRef, instrIndex);
					break;
				case REQ_METHODREF_2:
					instrIndex1 = attributeInfo->info.CodeAttribute.code[++i];
					instrIndex2 = attributeInfo->info.CodeAttribute.code[++i];
					instrIndex = (instrIndex2 | (instrIndex1 << 8));
					instrRef = MethodInfo(jvm_class, instrIndex - 1);
					fprintf(file, "%s, |CP={%d}|\t", instrRef, instrIndex);
					break;
				case REQ_FIELDREF:
					instrIndex1 = attributeInfo->info.CodeAttribute.code[++i];
					instrIndex2 = attributeInfo->info.CodeAttribute.code[++i];
					instrIndex = (instrIndex2 | (instrIndex1 << 8));
					instrRef = RefFieldInfo(jvm_class, instrIndex - 1);
					fprintf(file, "%s, |CP={%d}|\t", instrRef, instrIndex);
					break;
				case REQ_JMPREF:
					instrIndex1 = attributeInfo->info.CodeAttribute.code[++i];
					instrIndex2 = attributeInfo->info.CodeAttribute.code[++i];
					offset = (int16_t) (instrIndex2 | (instrIndex1 << 8));
					fprintf(file, "%d\t(%d)\t", (offset - 2) + i, offset);
					break;
				case REQ_LDCREF_1:
					instrIndex = attributeInfo->info.CodeAttribute.code[++i] - 1;
					fprintf(file, "%d\t", instrIndex + 1);
					switch (jvm_class->constant_pool[instrIndex].tag) {
					case CONSTANTInteger:
						fprintf(file, "%d\t", jvm_class->constant_pool[instrIndex].info.Integer.bytes);
						break;
					case CONSTANTFloat:
						memcpy(&float_value, &(jvm_class->constant_pool[instrIndex].info.Float.bytes), sizeof(u4));
						fprintf(file, "%f\t", float_value);
						break;
					case CONSTANTLong:
						longTemp = (u8) jvm_class->constant_pool[instrIndex].info.Long.high_bytes << 32;
						longTemp = longTemp | jvm_class->constant_pool[instrIndex].info.Long.low_bytes;
						fprintf(file, "%ld\t", longTemp);
						break;
					case CONSTANTDouble:
						longTemp = (u8) jvm_class->constant_pool[instrIndex].info.Double.high_bytes << 32;
						longTemp = longTemp | jvm_class->constant_pool[instrIndex].info.Double.low_bytes;
						memcpy(&double_value, &longTemp, sizeof(u8));
						fprintf(file, "%f\t", double_value);
						break;
					}
					break;
				case REQ_LDCREF_2:
					instrIndex1 = attributeInfo->info.CodeAttribute.code[++i];
					instrIndex2 = attributeInfo->info.CodeAttribute.code[++i];
					instrIndex = (instrIndex2 | (instrIndex1 << sizeof(u1))) - 1;
					fprintf(file, "%d\t", instrIndex + 1);
					switch (jvm_class->constant_pool[instrIndex].tag) {
					case CONSTANTInteger:
						fprintf(file, "%d\t", jvm_class->constant_pool[instrIndex].info.Integer.bytes);
						break;
					case CONSTANTFloat:
						memcpy(&float_value, &(jvm_class->constant_pool[instrIndex].info.Float.bytes), sizeof(u4));
						fprintf(file, "%f\t", float_value);
						break;
					case CONSTANTLong:
						longTemp = (u8) jvm_class->constant_pool[instrIndex].info.Long.high_bytes << 32;
						longTemp = longTemp | jvm_class->constant_pool[instrIndex].info.Long.low_bytes;
						fprintf(file, "%ld\t", longTemp);
						break;
					case CONSTANTDouble:
						longTemp = (u8) jvm_class->constant_pool[instrIndex].info.Double.high_bytes << 32;
						longTemp = longTemp | jvm_class->constant_pool[instrIndex].info.Double.low_bytes;
						memcpy(&double_value, &longTemp, sizeof(u8));
						fprintf(file, "%f\t", double_value);
						break;
					}
					break;
				case REQ_ARRAYREF:
					instrIndex = attributeInfo->info.CodeAttribute.code[++i];
					fprintf(file, "%d\t", instrIndex);
					switch (instrIndex) {
					case 0:
						fprintf(file, "(ref)\t");
						break;
					case 4:
						fprintf(file, "(boolean)\t");
						break;
					case 5:
						fprintf(file, "(char)\t");
						break;
					case 6:
						fprintf(file, "(float)\t");
						break;
					case 7:
						fprintf(file, "(double)\t");
						break;
					case 8:
						fprintf(file, "(byte)\t");
						break;
					case 9:
						fprintf(file, "(short)\t");
						break;
					case 10:
						fprintf(file, "(int)\t");
						break;
					case 11:
						fprintf(file, "(long)\t");
						break;
					default:
						break;
					}
					break;
				case REQ_IINCREF:
					instrIndex1 = attributeInfo->info.CodeAttribute.code[++i];
					instrIndex2 = attributeInfo->info.CodeAttribute.code[++i];
					fprintf(file, "%d by %d\t", instrIndex1, instrIndex2);
					break;
				default:
					for (j = 0; j < map[opcode].operators; j++)
						fprintf(file, "%d\t", attributeInfo->info.CodeAttribute.code[++i]);
					break;
				}
				fprintf(file, "\n");
			}

			fprintf(file, "\n\texception_table_length = %d\n", attributeInfo->info.CodeAttribute.exception_table_length);
			if (attributeInfo->info.CodeAttribute.exception_table_length > 0) {
				fprintf(file, "\tStart PC\tEnd PC\tHandler PC\tCatch Type\n");
				for (int i = 0; i < attributeInfo->info.CodeAttribute.exception_table_length; i++) {
					fprintf(file, "%d: %d\t", i, attributeInfo->info.CodeAttribute.exception_table[i].start_pc);
					fprintf(file, "%d\t", attributeInfo->info.CodeAttribute.exception_table[i].end_pc);
					fprintf(file, "%d\t", attributeInfo->info.CodeAttribute.exception_table[i].handler_pc);
					fprintf(file, "%d\n", attributeInfo->info.CodeAttribute.exception_table[i].catch_type);
				}
			}

			fprintf(file, "\tCode's attributes_count = %d\n", attributeInfo->info.CodeAttribute.attributes_count);
			for (int k = 0; k < attributeInfo->info.CodeAttribute.attributes_count; k++) {
				fprintf(file, "\t{%d} ", k);
				ShowAttributeOnFile(jvm_class, &(attributeInfo->info.CodeAttribute.attributes[k]), file);
			}
		} else if (!strcmp(attributeType, "Exceptions")) {
			fprintf(file, "\tnumber_of_exceptions = %d\n", attributeInfo->info.Exception.number_of_exceptions);
			for (int i = 0; i < attributeInfo->info.Exception.number_of_exceptions; i++) {
				index = attributeInfo->info.Exception.exception_index_table[i] - 1;
				index = jvm_class->constant_pool[index].info.Class.name_index - 1;
				reference_name = NameInfo(jvm_class, index);
				fprintf(file, "\tException Index = %s, |CP={%d}|\n", reference_name,
						attributeInfo->info.Exception.exception_index_table[i]);
				free(reference_name);
			}
		} else if (!strcmp(attributeType, "InnerClasses")) {
			fprintf(file, "\tnumber_of_classes = %d\n", attributeInfo->info.InnerClasses.number_of_classes);
			for (int i = 0; i < attributeInfo->info.InnerClasses.number_of_classes; i++) {
				free(reference_name);
				index = attributeInfo->info.InnerClasses.classes[i].inner_class_info_index - 1;
				index = jvm_class->constant_pool[index].info.Class.name_index - 1;
				reference_name = NameInfo(jvm_class, index);
				fprintf(file, "\t\tinner_class_info_index = %s, |CP={%d}|\n", reference_name,
						attributeInfo->info.InnerClasses.classes[i].inner_class_info_index);
				index = attributeInfo->info.InnerClasses.classes[i].outer_class_info_index - 1;
				index = jvm_class->constant_pool[index].info.Class.name_index - 1;
				free(reference_name);
				reference_name = NameInfo(jvm_class, index);
				fprintf(file, "\t\touter_class_info_index = %s, |CP={%d}|\n", reference_name,
						attributeInfo->info.InnerClasses.classes[i].outer_class_info_index);
				index = attributeInfo->info.InnerClasses.classes[i].inner_class_info_index - 1;
				free(reference_name);
				reference_name = NameInfo(jvm_class, index);
				fprintf(file, "\t\tinner_name_index = %s, |CP={%d}|\n", reference_name,
						attributeInfo->info.InnerClasses.classes[i].inner_name_index);
				fprintf(file, "\t\tinner_class_access_flags = %d\n", attributeInfo->info.InnerClasses.classes[i].inner_class_access_flags);
			}
		} else if (!strcmp(attributeType, "SourceFile")) {
			index = attributeInfo->info.Sourcefile.sourcefile_index - 1;
			reference_name = NameInfo(jvm_class, index);
			fprintf(file, "\tsourcefile_index = %s, |CP={%d}|\n", reference_name, attributeInfo->info.Sourcefile.sourcefile_index);
			free(reference_name);
		} else if (!strcmp(attributeType, "LineNumberTable")) {
			fprintf(file, "\tLine Numbers = %d\n", attributeInfo->info.LineNumberTable.line_number_table_length);
			if (attributeInfo->info.LineNumberTable.line_number_table_length > 0) {
				fprintf(file, "\n\tStart PC\tLine Number\n");
				for (int i = 0; i < attributeInfo->info.LineNumberTable.line_number_table_length; i++) {
					fprintf(file, "\t\t%d: %d", i, attributeInfo->info.LineNumberTable.line_number_table[i].start_pc);
					fprintf(file, "\t\t%d\n", attributeInfo->info.LineNumberTable.line_number_table[i].line_number);
				}
			}
		} else if (!strcmp(attributeType, "LocalVariableTable")) {
			fprintf(file, "\tTable Length = %d\n", attributeInfo->info.LocalVariableTable.local_variable_table_length);
			for (int i = 0; i < attributeInfo->info.LocalVariableTable.local_variable_table_length; i++) {
				free(reference_name);
				fprintf(file, "\t\tStart PC = %d\n", attributeInfo->info.LocalVariableTable.local_variable_table[i].start_pc);
				fprintf(file, "\t\tLength = %d\n", attributeInfo->info.LocalVariableTable.local_variable_table[i].length);
				index = attributeInfo->info.LocalVariableTable.local_variable_table[i].name_index - 1;
				reference_name = NameInfo(jvm_class, index);
				fprintf(file, "\t\tName Index = %s, |CP={%d}|\n", reference_name,
						attributeInfo->info.LocalVariableTable.local_variable_table[i].name_index);
				index = attributeInfo->info.LocalVariableTable.local_variable_table[i].descriptor_index - 1;
				free(reference_name);
				reference_name = NameInfo(jvm_class, index);
				fprintf(file, "\t\tDescriptor Index = %s, |CP={%d}|\n", reference_name,
						attributeInfo->info.LocalVariableTable.local_variable_table[i].descriptor_index);
				fprintf(file, "\t\tIndex: %d\n", attributeInfo->info.LocalVariableTable.local_variable_table[i].index);
			}
		} else {
			fprintf(file, "\tDefault: \t");
			for (int i = 0; i < attributeInfo->attribute_length; i++)
				fprintf(file, "\t%x", attributeInfo->info.Default.data[i]);
			fprintf(file, "\n");
		}
	}

	free(reference_name);
	free(attributeType);
}

void Exhibitor::ShowAllAttributes(ClassFile* jvm_class) {
	printf("\n\n########## ATTRIBUTES ##########\n");
	printf("attributes_count = %d\n", jvm_class->attributes_count);
	for (int i = 0; i < jvm_class->attributes_count; i++) {
		printf("\n===> {%d} ", i);
		ShowAttribute(jvm_class, &(jvm_class->attributes[i]));
	}
}

void Exhibitor::ShowAllAttributesOnFile(ClassFile* jvm_class, FILE *file) {
	fprintf(file, "\n\n########## ATTRIBUTES ##########\n");
	fprintf(file, "attributes_count = %d\n", jvm_class->attributes_count);
	for (int i = 0; i < jvm_class->attributes_count; i++) {
		fprintf(file, "\n===> {%d} ", i);
		ShowAttributeOnFile(jvm_class, &(jvm_class->attributes[i]), file);
	}
}

void Exhibitor::ShowFields(ClassFile* jvm_class) {
	printf("\n########## FIELDS ##########\n");
	printf("fields_count: %d\n", jvm_class->fields_count);

	for (int i = 0; i < jvm_class->fields_count; i++) {
		char *reference_name = NULL;
		char *reference_name2 = NULL;
		int index = 0;

		printf("\n===> {%d} ", i);
		for (int j = 0; j < jvm_class->constant_pool[jvm_class->fields[i].name_index - 1].info.Utf8.length; j++)
			printf("%c", jvm_class->constant_pool[jvm_class->fields[i].name_index - 1].info.Utf8.bytes[j]);
		printf("\n");

		index = jvm_class->fields[i].name_index - 1;
		reference_name = NameInfo(jvm_class, index);

		index = jvm_class->fields[i].descriptor_index - 1;
		reference_name2 = NameInfo(jvm_class, index);

		printf("Name Index = %s, |CP={%d}|\n", reference_name, jvm_class->fields[i].name_index);
		printf("Descriptor Index = %s, |CP={%d}|\n", reference_name2, jvm_class->fields[i].descriptor_index);
		printf("access_flags = %d\n", jvm_class->fields[i].access_flags);
		printf("attributes_count = %d\n", jvm_class->fields[i].attributes_count);

		for (int j = 0; j < jvm_class->fields[i].attributes_count; j++) {
			printf("\n===> {%d} ", j);
			for (int k = 0; k < jvm_class->constant_pool[jvm_class->fields[i].attributes[j].attribute_name_index - 1].info.Utf8.length; k++)
				printf("%c", jvm_class->constant_pool[jvm_class->fields[i].attributes[j].attribute_name_index - 1].info.Utf8.bytes[k]);
			printf("\n");
			ShowAttribute(jvm_class, &jvm_class->fields[i].attributes[j]);
		}

		free(reference_name);
		free(reference_name2);
	}
}

void Exhibitor::ShowFieldsOnFile(ClassFile* jvm_class, FILE *file) {
	fprintf(file, "\n########## FIELDS ##########\n");
	fprintf(file, "fields_count: %d\n", jvm_class->fields_count);

	for (int i = 0; i < jvm_class->fields_count; i++) {
		char *reference_name = NULL;
		char *reference_name2 = NULL;
		int index = 0;

		fprintf(file, "\n===> {%d} ", i);
		for (int j = 0; j < jvm_class->constant_pool[jvm_class->fields[i].name_index - 1].info.Utf8.length; j++)
			fprintf(file, "%c", jvm_class->constant_pool[jvm_class->fields[i].name_index - 1].info.Utf8.bytes[j]);
		fprintf(file, "\n");

		index = jvm_class->fields[i].name_index - 1;
		reference_name = NameInfo(jvm_class, index);

		index = jvm_class->fields[i].descriptor_index - 1;
		reference_name2 = NameInfo(jvm_class, index);

		fprintf(file, "Name Index = %s, |CP={%d}|\n", reference_name, jvm_class->fields[i].name_index);
		fprintf(file, "Descriptor Index = %s, |CP={%d}|\n", reference_name2, jvm_class->fields[i].descriptor_index);
		fprintf(file, "access_flags = %d\n", jvm_class->fields[i].access_flags);
		fprintf(file, "attributes_count = %d\n", jvm_class->fields[i].attributes_count);

		for (int j = 0; j < jvm_class->fields[i].attributes_count; j++) {
			fprintf(file, "\n===> {%d} ", j);
			for (int k = 0; k < jvm_class->constant_pool[jvm_class->fields[i].attributes[j].attribute_name_index - 1].info.Utf8.length; k++)
				fprintf(file, "%c",
						jvm_class->constant_pool[jvm_class->fields[i].attributes[j].attribute_name_index - 1].info.Utf8.bytes[k]);
			fprintf(file, "\n");
			ShowAttribute(jvm_class, &jvm_class->fields[i].attributes[j]);
		}

		free(reference_name);
		free(reference_name2);
	}
}

void Exhibitor::ShowInterface(CpInfo cp) {
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

void Exhibitor::ShowInterfaceOnFile(ClassFile* jvm_class, CpInfo cp, FILE* file) {
	switch (cp.tag) {
	case CONSTANTClass:
		fprintf(file, "Tag: ");
		fprintf(file, "%" PRIu8 "\n", cp.info.Class.tag);
		fprintf(file, "Index Name: ");
		fprintf(file, "%" PRIu16 "\n", cp.info.Class.name_index);
		break;
	case CONSTANTFieldref:
		fprintf(file, "Tag: ");
		fprintf(file, "%" PRIu8 "\n", cp.info.Fieldref.tag);
		fprintf(file, "Index Class: ");
		fprintf(file, "%" PRIu16 "\n", cp.info.Fieldref.class_index);
		fprintf(file, "Index Name and Type: ");
		fprintf(file, "%" PRIu16 "\n", cp.info.Fieldref.name_and_type_index);
		break;
	case CONSTANTMethodref:
		fprintf(file, "Tag: ");
		fprintf(file, "%" PRIu8 "\n", cp.info.Methodref.tag);
		fprintf(file, "Index Class: ");
		fprintf(file, "%" PRIu16 "\n", cp.info.Methodref.class_index);
		fprintf(file, "Index Name and Type: ");
		fprintf(file, "%" PRIu16 "\n", cp.info.Methodref.name_and_type_index);
		break;
	case CONSTANTInterfaceMethodref:
		fprintf(file, "Tag: ");
		fprintf(file, "%" PRIu8 "\n", cp.info.InterfaceMethodref.tag);
		fprintf(file, "Index Class: ");
		fprintf(file, "%" PRIu16 "\n", cp.info.InterfaceMethodref.class_index);
		fprintf(file, "Index Name and Type: ");
		fprintf(file, "%" PRIu16 "\n", cp.info.InterfaceMethodref.name_and_type_index);
		break;
	case CONSTANTString:
		fprintf(file, "Tag: ");
		fprintf(file, "%" PRIu8 "\n", cp.info.String.tag);
		fprintf(file, "Index String: ");
		fprintf(file, "%" PRIu16 "\n", cp.info.String.string_index);
		break;
	case CONSTANTInteger:
		fprintf(file, "Tag: ");
		fprintf(file, "%" PRIu8 "\n", cp.info.Integer.tag);
		fprintf(file, "Bytes: ");
		fprintf(file, "%" PRIu32 "\n", cp.info.Integer.bytes);
		break;
	case CONSTANTFloat:
		fprintf(file, "Tag: ");
		fprintf(file, "%" PRIu8 "\n", cp.info.Float.tag);
		fprintf(file, "Bytes: ");
		fprintf(file, "%" PRIu32 "\n", cp.info.Float.bytes);
		break;
	case CONSTANTLong:
		fprintf(file, "Tag: ");
		fprintf(file, "%" PRIu8 "\n", cp.info.Long.tag);
		fprintf(file, "High Bytes: ");
		fprintf(file, "%" PRIu32 "\n", cp.info.Long.high_bytes);
		fprintf(file, "Low Bytes Bytes: ");
		fprintf(file, "%" PRIu32 "\n", cp.info.Long.low_bytes);
		break;
	case CONSTANTDouble:
		fprintf(file, "Tag: ");
		fprintf(file, "%" PRIu8 "\n", cp.info.Double.tag);
		fprintf(file, "High Bytes: ");
		fprintf(file, "%" PRIu32 "\n", cp.info.Double.high_bytes);
		fprintf(file, "Low Bytes Bytes: ");
		fprintf(file, "%" PRIu32 "\n", cp.info.Double.low_bytes);
		break;
	case CONSTANTNameAndType:
		fprintf(file, "Tag: ");
		fprintf(file, "%" PRIu8 "\n", cp.info.NameAndType.tag);
		fprintf(file, "Index Name: ");
		fprintf(file, "%" PRIu16 "\n", cp.info.NameAndType.name_index);
		fprintf(file, "Index Descriptor: ");
		fprintf(file, "%" PRIu16 "\n", cp.info.NameAndType.descriptor_index);
		break;
	case CONSTANTUtf8:
		fprintf(file, "Tag: ");
		fprintf(file, "%" PRIu8 "\n", cp.info.Utf8.tag);
		for (int i = 0; i < cp.info.Utf8.length; i++) {
			uint8_t byte = cp.info.Utf8.bytes[i];
			char c = byte;
			fprintf(file, "%c", c);
		}
		break;
	}
}

void Exhibitor::ShowAllInterfaces(ClassFile* jvm_class) {
	printf("\n");
	printf("##############################");
	printf("######### Interfaces #########");
	printf("##############################");
	printf("Interface Counter: %d\n", jvm_class->interfaces_count);
	for (int i = 0; i < jvm_class->interfaces_count; i++) {
		printf("\n~~~> ");
		printf("{%d}: CP={", i);
		printf("%" PRIu16, jvm_class->interfaces[i]);
		printf("}\n");
	}
	printf("\n");
}

void Exhibitor::ShowAllInterfacesOnFile(ClassFile* jvm_class, FILE* file) {
	printf("\n");
	printf("##############################");
	printf("######### Interfaces #########");
	printf("##############################");
	fprintf(file, "Interface Counter: %d\n", jvm_class->interfaces_count);
	for (int i = 0; i < jvm_class->interfaces_count; i++) {
		fprintf(file, "\n~~~> ");
		fprintf(file, "{%d}: CP={", i);
		fprintf(file, "%" PRIu16, jvm_class->interfaces[i]);
		fprintf(file, "}\n");
	}
	fprintf(file, "\n");
}

void Exhibitor::ShowMethods(ClassFile* jvm_class) {
	printf("\n");
	printf("\n");
	printf("<---------------> Methods <--------------->\n");
	printf("methods_count = %d\n", jvm_class->methods_count);

	for (int i = 0; i < jvm_class->methods_count; i++) {
		int index = 0;
		char *name_ref = NULL;
		printf("\n===> ");
		printf("{%d} ", i);
		for (int j = 0; j < jvm_class->constant_pool[jvm_class->methods[i].name_index - 1].info.Utf8.length; j++)
			printf("%c", jvm_class->constant_pool[jvm_class->methods[i].name_index - 1].info.Utf8.bytes[j]);
		printf("\n");
		index = jvm_class->methods[i].name_index - 1;
		name_ref = NameInfo(jvm_class, index);
		printf("Name = %s, |CP={%d}|\n", name_ref, jvm_class->methods[i].name_index);
		index = jvm_class->methods[i].descriptor_index - 1;
		name_ref = NameInfo(jvm_class, index);
		printf("Descriptor = %s, |CP={%d}|\n", name_ref, jvm_class->methods[i].descriptor_index);
		printf("access_flags = 0x%x\n", jvm_class->methods[i].access_flags);
		printf("attributes_count = %d\n", jvm_class->methods[i].attributes_count);
		for (int j = 0; j < jvm_class->methods[i].attributes_count; j++) {
			printf("\n===> ");
			printf("{{%d}} ", j);
			ShowAttribute(jvm_class, &(jvm_class->methods[i].attributes[j]));
		}
	}
}

void Exhibitor::ShowMethodsOnFile(ClassFile* jvm_class, FILE* file) {
	fprintf(file, "\n");
	fprintf(file, "########### Methods ###########\n");
	fprintf(file, "Method Counter: \t%d\n", jvm_class->methods_count);

	for (int i = 0; i < jvm_class->methods_count; i++) {
		int index = 0;
		char *name_ref = NULL;
		fprintf(file, "\n~~~> ");
		fprintf(file, "{%d} ", i);
		for (int j = 0; j < jvm_class->constant_pool[jvm_class->methods[i].name_index - 1].info.Utf8.length; j++)
			fprintf(file, "%c", jvm_class->constant_pool[jvm_class->methods[i].name_index - 1].info.Utf8.bytes[j]);
		fprintf(file, "\n");
		index = jvm_class->methods[i].name_index - 1;
		name_ref = NameInfo(jvm_class, index);
		fprintf(file, "Name: <%s>, |CP={%d}|\n", name_ref, jvm_class->methods[i].name_index);
		index = jvm_class->methods[i].descriptor_index - 1;
		free(name_ref);
		name_ref = NameInfo(jvm_class, index);
		fprintf(file, "Descriptor: <%s>, |CP={%d}|\n", name_ref, jvm_class->methods[i].descriptor_index);
		fprintf(file, "Access Flags: 0x%x\n", jvm_class->methods[i].access_flags);
		fprintf(file, "Attribute Counter: %d\n", jvm_class->methods[i].attributes_count);
		for (int j = 0; j < jvm_class->methods[i].attributes_count; j++) {
			fprintf(file, "\n~~~~~> ");
			fprintf(file, "{{%d}} ", j);
			ShowAttributeOnFile(jvm_class, &(jvm_class->methods[i].attributes[j]), file);
		}
		free(name_ref);
	}
}

char* Exhibitor::NameInfo(ClassFile* jvm_class, u2 index) {
	char *name;
	int i;
	name = (char *) malloc((jvm_class->constant_pool[index].info.Utf8.length + 1) * sizeof(char));

	for (i = 0; i < jvm_class->constant_pool[index].info.Utf8.length; i++)
		name[i] = jvm_class->constant_pool[index].info.Utf8.bytes[i];

	name[i] = '\0';
	return name;
}

char* Exhibitor::RefFieldInfo(ClassFile* jvm_class, u2 index) {
	char *method_name;
	char *class_name;
	char *name;

	u2 method_index;
	u2 name_and_type_index;
	u2 class_index;

	class_index = jvm_class->constant_pool[index].info.Fieldref.class_index - 1;
	class_index = jvm_class->constant_pool[class_index].info.Class.name_index - 1;
	name_and_type_index = jvm_class->constant_pool[index].info.Fieldref.name_and_type_index - 1;
	method_index = jvm_class->constant_pool[name_and_type_index].info.NameAndType.name_index - 1;

	method_name = NameInfo(jvm_class, method_index);
	class_name = NameInfo(jvm_class, class_index);
	name = (char *) malloc((strlen(class_name) + strlen(method_name) + 2) * sizeof(char));

	strcpy(name, class_name);
	strcat(name, ".");
	strcat(name, method_name);

	free(class_name);
	free(method_name);
	return name;
}

char* Exhibitor::MethodInfo(ClassFile* jvm_class, u2 index) {
	char *method_name;
	char *class_name;
	char *name;

	u2 method_index;
	u2 name_and_type_index;
	u2 class_index;

	class_index = jvm_class->constant_pool[index].info.Methodref.class_index - 1;
	class_index = jvm_class->constant_pool[class_index].info.Class.name_index - 1;
	name_and_type_index = jvm_class->constant_pool[index].info.Methodref.name_and_type_index - 1;
	method_index = jvm_class->constant_pool[name_and_type_index].info.NameAndType.name_index - 1;

	method_name = NameInfo(jvm_class, method_index);
	class_name = NameInfo(jvm_class, class_index);
	name = (char *) malloc((strlen(class_name) + strlen(method_name) + 2) * sizeof(char));

	strcpy(name, class_name);
	strcat(name, ".");
	strcat(name, method_name);

	free(class_name);
	free(method_name);
	return name;
}

void Exhibitor::Mnemonics(Instruction *map) {
	strcpy(map[0x00].mnemonic, "nop");
	map[0x00].operators = 0;
	map[0x00].req_cp = 0;
	strcpy(map[0x01].mnemonic, "aconst_null");
	map[0x01].operators = 0;
	map[0x01].req_cp = 0;
	strcpy(map[0x02].mnemonic, "iconst_m1");
	map[0x02].operators = 0;
	map[0x02].req_cp = 0;
	strcpy(map[0x03].mnemonic, "iconst_0");
	map[0x03].operators = 0;
	map[0x03].req_cp = 0;
	strcpy(map[0x04].mnemonic, "iconst_1");
	map[0x04].operators = 0;
	map[0x04].req_cp = 0;
	strcpy(map[0x05].mnemonic, "iconst_2");
	map[0x05].operators = 0;
	map[0x05].req_cp = 0;
	strcpy(map[0x06].mnemonic, "iconst_3");
	map[0x06].operators = 0;
	map[0x06].req_cp = 0;
	strcpy(map[0x07].mnemonic, "iconst_4");
	map[0x07].operators = 0;
	map[0x07].req_cp = 0;
	strcpy(map[0x08].mnemonic, "iconst_5");
	map[0x08].operators = 0;
	map[0x08].req_cp = 0;
	strcpy(map[0x09].mnemonic, "lconst_0");
	map[0x09].operators = 0;
	map[0x09].req_cp = 0;
	strcpy(map[0x0A].mnemonic, "lconst_1");
	map[0x0A].operators = 0;
	map[0x0A].req_cp = 0;
	strcpy(map[0x0B].mnemonic, "fconst_0");
	map[0x0B].operators = 0;
	map[0x0B].req_cp = 0;
	strcpy(map[0x0C].mnemonic, "fconst_1");
	map[0x0C].operators = 0;
	map[0x0C].req_cp = 0;
	strcpy(map[0x0D].mnemonic, "fconst_2");
	map[0x0D].operators = 0;
	map[0x0D].req_cp = 0;
	strcpy(map[0x0E].mnemonic, "dconst_0");
	map[0x0E].operators = 0;
	map[0x0E].req_cp = 0;
	strcpy(map[0x0F].mnemonic, "dconst_1");
	map[0x0F].operators = 0;
	map[0x0F].req_cp = 0;
	strcpy(map[0x10].mnemonic, "bipush");
	map[0x10].operators = 1;
	map[0x10].req_cp = 0;
	strcpy(map[0x11].mnemonic, "sipush");
	map[0x11].operators = 2;
	map[0x11].req_cp = 0;
	strcpy(map[0x12].mnemonic, "ldc");
	map[0x12].operators = 1;
	map[0x12].req_cp = REQ_LDCREF_1;
	strcpy(map[0x13].mnemonic, "ldc_w");
	map[0x13].operators = 2;
	map[0x13].req_cp = REQ_LDCREF_1;
	strcpy(map[0x14].mnemonic, "ldc2_w");
	map[0x14].operators = 2;
	map[0x14].req_cp = REQ_LDCREF_2;
	strcpy(map[0x15].mnemonic, "iload");
	map[0x15].operators = 1;
	map[0x15].req_cp = 0;
	strcpy(map[0x16].mnemonic, "lload");
	map[0x16].operators = 1;
	map[0x16].req_cp = 0;
	strcpy(map[0x17].mnemonic, "fload");
	map[0x17].operators = 1;
	map[0x17].req_cp = 0;
	strcpy(map[0x18].mnemonic, "dload");
	map[0x18].operators = 1;
	map[0x18].req_cp = 0;
	strcpy(map[0x19].mnemonic, "aload");
	map[0x19].operators = 1;
	map[0x19].req_cp = 0;
	strcpy(map[0x1A].mnemonic, "iload_0");
	map[0x1A].operators = 0;
	map[0x1A].req_cp = 0;
	strcpy(map[0x1B].mnemonic, "iload_1");
	map[0x1B].operators = 0;
	map[0x1B].req_cp = 0;
	strcpy(map[0x1C].mnemonic, "iload_2");
	map[0x1C].operators = 0;
	map[0x1C].req_cp = 0;
	strcpy(map[0x1D].mnemonic, "iload_3");
	map[0x1D].operators = 0;
	map[0x1D].req_cp = 0;
	strcpy(map[0x1E].mnemonic, "lload_0");
	map[0x1E].operators = 0;
	map[0x1E].req_cp = 0;
	strcpy(map[0x1F].mnemonic, "lload_1");
	map[0x1F].operators = 0;
	map[0x1F].req_cp = 0;
	strcpy(map[0x20].mnemonic, "lload_2");
	map[0x20].operators = 0;
	map[0x20].req_cp = 0;
	strcpy(map[0x21].mnemonic, "lload_3");
	map[0x21].operators = 0;
	map[0x21].req_cp = 0;
	strcpy(map[0x22].mnemonic, "fload_0");
	map[0x22].operators = 0;
	map[0x22].req_cp = 0;
	strcpy(map[0x23].mnemonic, "fload_1");
	map[0x23].operators = 0;
	map[0x23].req_cp = 0;
	strcpy(map[0x24].mnemonic, "fload_2");
	map[0x24].operators = 0;
	map[0x24].req_cp = 0;
	strcpy(map[0x25].mnemonic, "fload_3");
	map[0x25].operators = 0;
	map[0x25].req_cp = 0;
	strcpy(map[0x26].mnemonic, "dload_0");
	map[0x26].operators = 0;
	map[0x26].req_cp = 0;
	strcpy(map[0x27].mnemonic, "dload_1");
	map[0x27].operators = 0;
	map[0x27].req_cp = 0;
	strcpy(map[0x28].mnemonic, "dload_2");
	map[0x28].operators = 0;
	map[0x28].req_cp = 0;
	strcpy(map[0x29].mnemonic, "dload_3");
	map[0x29].operators = 0;
	map[0x29].req_cp = 0;
	strcpy(map[0x2A].mnemonic, "aload_0");
	map[0x2A].operators = 0;
	map[0x2A].req_cp = 0;
	strcpy(map[0x2B].mnemonic, "aload_1");
	map[0x2B].operators = 0;
	map[0x2B].req_cp = 0;
	strcpy(map[0x2C].mnemonic, "aload_2");
	map[0x2C].operators = 0;
	map[0x2C].req_cp = 0;
	strcpy(map[0x2D].mnemonic, "aload_3");
	map[0x2D].operators = 0;
	map[0x2D].req_cp = 0;
	strcpy(map[0x2E].mnemonic, "iaload");
	map[0x2E].operators = 0;
	map[0x2E].req_cp = 0;
	strcpy(map[0x2F].mnemonic, "laload");
	map[0x2F].operators = 0;
	map[0x2F].req_cp = 0;
	strcpy(map[0x30].mnemonic, "faload");
	map[0x30].operators = 0;
	map[0x30].req_cp = 0;
	strcpy(map[0x31].mnemonic, "daload");
	map[0x31].operators = 0;
	map[0x31].req_cp = 0;
	strcpy(map[0x32].mnemonic, "aaload");
	map[0x32].operators = 0;
	map[0x32].req_cp = 0;
	strcpy(map[0x33].mnemonic, "baload");
	map[0x33].operators = 0;
	map[0x33].req_cp = 0;
	strcpy(map[0x34].mnemonic, "caload");
	map[0x34].operators = 0;
	map[0x34].req_cp = 0;
	strcpy(map[0x35].mnemonic, "saload");
	map[0x35].operators = 0;
	map[0x35].req_cp = 0;
	strcpy(map[0x36].mnemonic, "istore");
	map[0x36].operators = 1;
	map[0x36].req_cp = 0;
	strcpy(map[0x37].mnemonic, "lstore");
	map[0x37].operators = 1;
	map[0x37].req_cp = 0;
	strcpy(map[0x38].mnemonic, "fstore");
	map[0x38].operators = 1;
	map[0x38].req_cp = 0;
	strcpy(map[0x39].mnemonic, "dstore");
	map[0x39].operators = 1;
	map[0x39].req_cp = 0;
	strcpy(map[0x3A].mnemonic, "astore");
	map[0x3A].operators = 1;
	map[0x3A].req_cp = 0;
	strcpy(map[0x3B].mnemonic, "istore_0");
	map[0x3B].operators = 0;
	map[0x3B].req_cp = 0;
	strcpy(map[0x3C].mnemonic, "istore_1");
	map[0x3C].operators = 0;
	map[0x3C].req_cp = 0;
	strcpy(map[0x3D].mnemonic, "istore_2");
	map[0x3D].operators = 0;
	map[0x3D].req_cp = 0;
	strcpy(map[0x3E].mnemonic, "istore_3");
	map[0x3E].operators = 0;
	map[0x3E].req_cp = 0;
	strcpy(map[0x3F].mnemonic, "lstore_0");
	map[0x3F].operators = 0;
	map[0x3F].req_cp = 0;
	strcpy(map[0x40].mnemonic, "lstore_1");
	map[0x40].operators = 0;
	map[0x40].req_cp = 0;
	strcpy(map[0x41].mnemonic, "lstore_2");
	map[0x41].operators = 0;
	map[0x41].req_cp = 0;
	strcpy(map[0x42].mnemonic, "lstore_3");
	map[0x42].operators = 0;
	map[0x42].req_cp = 0;
	strcpy(map[0x43].mnemonic, "fstore_0");
	map[0x43].operators = 0;
	map[0x43].req_cp = 0;
	strcpy(map[0x44].mnemonic, "fstore_1");
	map[0x44].operators = 0;
	map[0x44].req_cp = 0;
	strcpy(map[0x45].mnemonic, "fstore_2");
	map[0x45].operators = 0;
	map[0x45].req_cp = 0;
	strcpy(map[0x46].mnemonic, "fstore_3");
	map[0x46].operators = 0;
	map[0x46].req_cp = 0;
	strcpy(map[0x47].mnemonic, "dstore_0");
	map[0x47].operators = 0;
	map[0x47].req_cp = 0;
	strcpy(map[0x48].mnemonic, "dstore_1");
	map[0x48].operators = 0;
	map[0x48].req_cp = 0;
	strcpy(map[0x49].mnemonic, "dstore_2");
	map[0x49].operators = 0;
	map[0x49].req_cp = 0;
	strcpy(map[0x4A].mnemonic, "dstore_3");
	map[0x4A].operators = 0;
	map[0x4A].req_cp = 0;
	strcpy(map[0x4B].mnemonic, "astore_0");
	map[0x4B].operators = 0;
	map[0x4B].req_cp = 0;
	strcpy(map[0x4C].mnemonic, "astore_1");
	map[0x4C].operators = 0;
	map[0x4C].req_cp = 0;
	strcpy(map[0x4D].mnemonic, "astore_2");
	map[0x4D].operators = 0;
	map[0x4D].req_cp = 0;
	strcpy(map[0x4E].mnemonic, "astore_3");
	map[0x4E].operators = 0;
	map[0x4E].req_cp = 0;
	strcpy(map[0x4F].mnemonic, "iastore");
	map[0x4F].operators = 0;
	map[0x4F].req_cp = 0;
	strcpy(map[0x50].mnemonic, "lastore");
	map[0x50].operators = 0;
	map[0x50].req_cp = 0;
	strcpy(map[0x51].mnemonic, "fastore");
	map[0x51].operators = 0;
	map[0x51].req_cp = 0;
	strcpy(map[0x52].mnemonic, "dastore");
	map[0x52].operators = 0;
	map[0x52].req_cp = 0;
	strcpy(map[0x53].mnemonic, "aastore");
	map[0x53].operators = 0;
	map[0x53].req_cp = 0;
	strcpy(map[0x54].mnemonic, "bastore");
	map[0x54].operators = 0;
	map[0x54].req_cp = 0;
	strcpy(map[0x55].mnemonic, "castore");
	map[0x55].operators = 0;
	map[0x55].req_cp = 0;
	strcpy(map[0x56].mnemonic, "sastore");
	map[0x56].operators = 0;
	map[0x56].req_cp = 0;
	strcpy(map[0x57].mnemonic, "pop");
	map[0x57].operators = 0;
	map[0x57].req_cp = 0;
	strcpy(map[0x58].mnemonic, "pop2");
	map[0x58].operators = 0;
	map[0x58].req_cp = 0;
	strcpy(map[0x59].mnemonic, "dup");
	map[0x59].operators = 0;
	map[0x59].req_cp = 0;
	strcpy(map[0x5A].mnemonic, "dup_x1");
	map[0x5A].operators = 0;
	map[0x5A].req_cp = 0;
	strcpy(map[0x5B].mnemonic, "dup_x2");
	map[0x5B].operators = 0;
	map[0x5B].req_cp = 0;
	strcpy(map[0x5C].mnemonic, "dup2");
	map[0x5C].operators = 0;
	map[0x5C].req_cp = 0;
	strcpy(map[0x5D].mnemonic, "dup2_x1");
	map[0x5D].operators = 0;
	map[0x5D].req_cp = 0;
	strcpy(map[0x5E].mnemonic, "dup2_x2");
	map[0x5E].operators = 0;
	map[0x5E].req_cp = 0;
	strcpy(map[0x5F].mnemonic, "swap");
	map[0x5F].operators = 0;
	map[0x5F].req_cp = 0;
	strcpy(map[0x60].mnemonic, "iadd");
	map[0x60].operators = 0;
	map[0x60].req_cp = 0;
	strcpy(map[0x61].mnemonic, "ladd");
	map[0x61].operators = 0;
	map[0x61].req_cp = 0;
	strcpy(map[0x62].mnemonic, "fadd");
	map[0x62].operators = 0;
	map[0x62].req_cp = 0;
	strcpy(map[0x63].mnemonic, "dadd");
	map[0x63].operators = 0;
	map[0x63].req_cp = 0;
	strcpy(map[0x64].mnemonic, "isub");
	map[0x64].operators = 0;
	map[0x64].req_cp = 0;
	strcpy(map[0x65].mnemonic, "lsub");
	map[0x65].operators = 0;
	map[0x65].req_cp = 0;
	strcpy(map[0x66].mnemonic, "fsub");
	map[0x66].operators = 0;
	map[0x66].req_cp = 0;
	strcpy(map[0x67].mnemonic, "dsub");
	map[0x67].operators = 0;
	map[0x67].req_cp = 0;
	strcpy(map[0x68].mnemonic, "imul");
	map[0x68].operators = 0;
	map[0x68].req_cp = 0;
	strcpy(map[0x69].mnemonic, "lmul");
	map[0x69].operators = 0;
	map[0x69].req_cp = 0;
	strcpy(map[0x6A].mnemonic, "fmul");
	map[0x6A].operators = 0;
	map[0x6A].req_cp = 0;
	strcpy(map[0x6B].mnemonic, "dmul");
	map[0x6B].operators = 0;
	map[0x6B].req_cp = 0;
	strcpy(map[0x6C].mnemonic, "idiv");
	map[0x6C].operators = 0;
	map[0x6C].req_cp = 0;
	strcpy(map[0x6D].mnemonic, "ldiv");
	map[0x6D].operators = 0;
	map[0x6D].req_cp = 0;
	strcpy(map[0x6E].mnemonic, "fdiv");
	map[0x6E].operators = 0;
	map[0x6E].req_cp = 0;
	strcpy(map[0x6F].mnemonic, "ddiv");
	map[0x6F].operators = 0;
	map[0x6F].req_cp = 0;
	strcpy(map[0x70].mnemonic, "irem");
	map[0x70].operators = 0;
	map[0x70].req_cp = 0;
	strcpy(map[0x71].mnemonic, "lrem");
	map[0x71].operators = 0;
	map[0x71].req_cp = 0;
	strcpy(map[0x72].mnemonic, "frem");
	map[0x72].operators = 0;
	map[0x72].req_cp = 0;
	strcpy(map[0x73].mnemonic, "drem");
	map[0x73].operators = 0;
	map[0x73].req_cp = 0;
	strcpy(map[0x74].mnemonic, "ineg");
	map[0x74].operators = 0;
	map[0x74].req_cp = 0;
	strcpy(map[0x75].mnemonic, "lneg");
	map[0x75].operators = 0;
	map[0x75].req_cp = 0;
	strcpy(map[0x76].mnemonic, "fneg");
	map[0x76].operators = 0;
	map[0x76].req_cp = 0;
	strcpy(map[0x77].mnemonic, "dneg");
	map[0x77].operators = 0;
	map[0x77].req_cp = 0;
	strcpy(map[0x78].mnemonic, "ishl");
	map[0x78].operators = 0;
	map[0x78].req_cp = 0;
	strcpy(map[0x79].mnemonic, "lshl");
	map[0x79].operators = 0;
	map[0x79].req_cp = 0;
	strcpy(map[0x7A].mnemonic, "ishr");
	map[0x7A].operators = 0;
	map[0x7A].req_cp = 0;
	strcpy(map[0x7B].mnemonic, "lshr");
	map[0x7B].operators = 0;
	map[0x7B].req_cp = 0;
	strcpy(map[0x7C].mnemonic, "iushr");
	map[0x7C].operators = 0;
	map[0x7C].req_cp = 0;
	strcpy(map[0x7D].mnemonic, "lushr");
	map[0x7D].operators = 0;
	map[0x7D].req_cp = 0;
	strcpy(map[0x7E].mnemonic, "iand");
	map[0x7E].operators = 0;
	map[0x7E].req_cp = 0;
	strcpy(map[0x7F].mnemonic, "land");
	map[0x7F].operators = 0;
	map[0x7F].req_cp = 0;
	strcpy(map[0x80].mnemonic, "ior");
	map[0x80].operators = 0;
	map[0x80].req_cp = 0;
	strcpy(map[0x81].mnemonic, "lor");
	map[0x81].operators = 0;
	map[0x81].req_cp = 0;
	strcpy(map[0x82].mnemonic, "ixor");
	map[0x82].operators = 0;
	map[0x82].req_cp = 0;
	strcpy(map[0x83].mnemonic, "lxor");
	map[0x83].operators = 0;
	map[0x83].req_cp = 0;
	strcpy(map[0x84].mnemonic, "iinc");
	map[0x84].operators = 2;
	map[0x84].req_cp = REQ_IINCREF;
	strcpy(map[0x85].mnemonic, "i2l");
	map[0x85].operators = 0;
	map[0x85].req_cp = 0;
	strcpy(map[0x86].mnemonic, "i2f");
	map[0x86].operators = 0;
	map[0x86].req_cp = 0;
	strcpy(map[0x87].mnemonic, "i2d");
	map[0x87].operators = 0;
	map[0x87].req_cp = 0;
	strcpy(map[0x88].mnemonic, "l2i");
	map[0x88].operators = 0;
	map[0x88].req_cp = 0;
	strcpy(map[0x89].mnemonic, "l2f");
	map[0x89].operators = 0;
	map[0x89].req_cp = 0;
	strcpy(map[0x8A].mnemonic, "l2d");
	map[0x8A].operators = 0;
	map[0x8A].req_cp = 0;
	strcpy(map[0x8B].mnemonic, "f2i");
	map[0x8B].operators = 0;
	map[0x8B].req_cp = 0;
	strcpy(map[0x8C].mnemonic, "f2l");
	map[0x8C].operators = 0;
	map[0x8C].req_cp = 0;
	strcpy(map[0x8D].mnemonic, "f2d");
	map[0x8D].operators = 0;
	map[0x8D].req_cp = 0;
	strcpy(map[0x8E].mnemonic, "d2i");
	map[0x8E].operators = 0;
	map[0x8E].req_cp = 0;
	strcpy(map[0x8F].mnemonic, "d2l");
	map[0x8F].operators = 0;
	map[0x8F].req_cp = 0;
	strcpy(map[0x90].mnemonic, "d2f");
	map[0x90].operators = 0;
	map[0x90].req_cp = 0;
	strcpy(map[0x91].mnemonic, "i2b");
	map[0x91].operators = 0;
	map[0x91].req_cp = 0;
	strcpy(map[0x92].mnemonic, "i2c");
	map[0x92].operators = 0;
	map[0x92].req_cp = 0;
	strcpy(map[0x93].mnemonic, "i2s");
	map[0x93].operators = 0;
	map[0x93].req_cp = 0;
	strcpy(map[0x94].mnemonic, "lcmp");
	map[0x94].operators = 0;
	map[0x94].req_cp = 0;
	strcpy(map[0x95].mnemonic, "fcmpl");
	map[0x95].operators = 0;
	map[0x95].req_cp = 0;
	strcpy(map[0x96].mnemonic, "fcmpg");
	map[0x96].operators = 0;
	map[0x96].req_cp = 0;
	strcpy(map[0x97].mnemonic, "dcmpl");
	map[0x97].operators = 0;
	map[0x97].req_cp = 0;
	strcpy(map[0x98].mnemonic, "dcmpg");
	map[0x98].operators = 0;
	map[0x98].req_cp = 0;
	strcpy(map[0x99].mnemonic, "ifeq");
	map[0x99].operators = 2;
	map[0x99].req_cp = REQ_JMPREF;
	strcpy(map[0x9A].mnemonic, "ifne");
	map[0x9A].operators = 2;
	map[0x9A].req_cp = REQ_JMPREF;
	strcpy(map[0x9B].mnemonic, "iflt");
	map[0x9B].operators = 2;
	map[0x9B].req_cp = REQ_JMPREF;
	strcpy(map[0x9C].mnemonic, "ifge");
	map[0x9C].operators = 2;
	map[0x9C].req_cp = REQ_JMPREF;
	strcpy(map[0x9D].mnemonic, "ifgt");
	map[0x9D].operators = 2;
	map[0x9D].req_cp = REQ_JMPREF;
	strcpy(map[0x9E].mnemonic, "ifle");
	map[0x9E].operators = 2;
	map[0x9E].req_cp = REQ_JMPREF;
	strcpy(map[0x9F].mnemonic, "if_icmpeq");
	map[0x9F].operators = 2;
	map[0x9F].req_cp = REQ_JMPREF;
	strcpy(map[0xA0].mnemonic, "if_icmpne");
	map[0xA0].operators = 2;
	map[0xA0].req_cp = REQ_JMPREF;
	strcpy(map[0xA1].mnemonic, "if_icmplt");
	map[0xA1].operators = 2;
	map[0xA1].req_cp = REQ_JMPREF;
	strcpy(map[0xA2].mnemonic, "if_icmpge");
	map[0xA2].operators = 2;
	map[0xA2].req_cp = REQ_JMPREF;
	strcpy(map[0xA3].mnemonic, "if_icmpgt");
	map[0xA3].operators = 2;
	map[0xA3].req_cp = REQ_JMPREF;
	strcpy(map[0xA4].mnemonic, "if_icmple");
	map[0xA4].operators = 2;
	map[0xA4].req_cp = REQ_JMPREF;
	strcpy(map[0xA5].mnemonic, "if_acmpeq");
	map[0xA5].operators = 2;
	map[0xA5].req_cp = REQ_JMPREF;
	strcpy(map[0xA6].mnemonic, "if_acmpne");
	map[0xA6].operators = 2;
	map[0xA6].req_cp = REQ_JMPREF;
	strcpy(map[0xA7].mnemonic, "goto");
	map[0xA7].operators = 2;
	map[0xA7].req_cp = REQ_JMPREF;
	strcpy(map[0xA8].mnemonic, "jsr");
	map[0xA8].operators = 2;
	map[0xA8].req_cp = REQ_JMPREF;
	strcpy(map[0xA9].mnemonic, "ret");
	map[0xA9].operators = 1;
	map[0xA9].req_cp = 0;
	strcpy(map[0xAA].mnemonic, "tableswitch");
	map[0xAA].operators = 14;
	map[0xAA].req_cp = 0;
	strcpy(map[0xAB].mnemonic, "lookupswitch");
	map[0xAB].operators = 10;
	map[0xAB].req_cp = 0;
	strcpy(map[0xAC].mnemonic, "ireturn");
	map[0xAC].operators = 0;
	map[0xAC].req_cp = 0;
	strcpy(map[0xAD].mnemonic, "lreturn");
	map[0xAD].operators = 0;
	map[0xAD].req_cp = 0;
	strcpy(map[0xAE].mnemonic, "freturn");
	map[0xAE].operators = 0;
	map[0xAE].req_cp = 0;
	strcpy(map[0xAF].mnemonic, "dreturn");
	map[0xAF].operators = 0;
	map[0xAF].req_cp = 0;
	strcpy(map[0xB0].mnemonic, "areturn");
	map[0xB0].operators = 0;
	map[0xB0].req_cp = 0;
	strcpy(map[0xB1].mnemonic, "return");
	map[0xB1].operators = 0;
	map[0xB1].req_cp = 0;
	strcpy(map[0xB2].mnemonic, "getstatic");
	map[0xB2].operators = 2;
	map[0xB2].req_cp = REQ_FIELDREF;
	strcpy(map[0xB3].mnemonic, "putstatic");
	map[0xB3].operators = 2;
	map[0xB3].req_cp = REQ_FIELDREF;
	strcpy(map[0xB4].mnemonic, "getfield");
	map[0xB4].operators = 2;
	map[0xB4].req_cp = REQ_FIELDREF;
	strcpy(map[0xB5].mnemonic, "putfield");
	map[0xB5].operators = 2;
	map[0xB5].req_cp = REQ_FIELDREF;
	strcpy(map[0xB6].mnemonic, "invokevirtual");
	map[0xB6].operators = 2;
	map[0xB6].req_cp = REQ_METHODREF_2;
	strcpy(map[0xB7].mnemonic, "invokespecial");
	map[0xB7].operators = 2;
	map[0xB7].req_cp = REQ_METHODREF_2;
	strcpy(map[0xB8].mnemonic, "invokestatic");
	map[0xB8].operators = 2;
	map[0xB8].req_cp = REQ_METHODREF_2;
	strcpy(map[0xB9].mnemonic, "invokeinterface");
	map[0xB9].operators = 4;
	map[0xB9].req_cp = REQ_METHODREF_2;
	strcpy(map[0xBB].mnemonic, "new");
	map[0xBB].operators = 2;
	map[0xBA].req_cp = 0;
	strcpy(map[0xBC].mnemonic, "newarray");
	map[0xBC].operators = 1;
	map[0xBC].req_cp = REQ_ARRAYREF;
	strcpy(map[0xBD].mnemonic, "anewarray");
	map[0xBD].operators = 2;
	map[0xBD].req_cp = 0;
	strcpy(map[0xBE].mnemonic, "arraylength");
	map[0xBE].operators = 0;
	map[0xBE].req_cp = 0;
	strcpy(map[0xBF].mnemonic, "athrow");
	map[0xBF].operators = 0;
	map[0xBF].req_cp = 0;
	strcpy(map[0xC0].mnemonic, "check_cast");
	map[0xC0].operators = 0;
	map[0xC0].req_cp = 0;
	strcpy(map[0xC1].mnemonic, "instance_of");
	map[0xC1].operators = 0;
	map[0xC1].req_cp = 0;
	strcpy(map[0xC2].mnemonic, "monitor_enter");
	map[0xC2].operators = 0;
	map[0xC2].req_cp = 0;
	strcpy(map[0xC3].mnemonic, "monitor_exit");
	map[0xC3].operators = 0;
	map[0xC3].req_cp = 0;
	strcpy(map[0xC4].mnemonic, "wide");
	map[0xC4].operators = 7;
	map[0xC4].req_cp = 0;
	strcpy(map[0xC5].mnemonic, "multianewarray");
	map[0xC5].operators = 3;
	map[0xC5].req_cp = 0;
	strcpy(map[0xC6].mnemonic, "ifnull");
	map[0xC6].operators = 2;
	map[0xC6].req_cp = 0;
	strcpy(map[0xC7].mnemonic, "ifnonnull");
	map[0xC7].operators = 2;
	map[0xC7].req_cp = 0;
	strcpy(map[0xC8].mnemonic, "goto_w");
	map[0xC8].operators = 4;
	map[0xC8].req_cp = 0;
	strcpy(map[0xC9].mnemonic, "jsr_w");
	map[0xC9].operators = 4;
	map[0xC9].req_cp = 0;
}
