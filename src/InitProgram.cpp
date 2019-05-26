#include "InitProgram.h"

InitProgram::InitProgram() {
	initProgramReader = new Reader();
}

InitProgram::~InitProgram() {
}

void InitProgram::StartProgram(char **argv) {
	strcpy(className, argv[1]);
}

int InitProgram::ReadClass(ClassFile* jvm_class) {
	printf("\nReading class...\n");
	int result = initProgramReader->InsertClass(className, jvm_class);
	free(initProgramReader);
	return result;
}

int InitProgram::createFileTXT(char *fileName) {
	initProgramFile = fopen(fileName, "w");
	if (!initProgramFile) {
		printf("File Creation Error\n");
		free(fileName);
		return FILE_ERROR;
	}
	return SUCCESS;
}

void InitProgram::JVM_Menu(ClassFile *jvm_class) {
	initProgramExhibitor = new Exhibitor();

	char *fileName, *name;
	int index = jvm_class->constant_pool[jvm_class->this_class - 1].info.Class.name_index - 1;

	name = initProgramExhibitor->NameInfo(jvm_class, index);
	fileName = (char *) malloc(sizeof(char) * (strlen(name)));

	strcpy(fileName, name);
	strcat(fileName, ".txt");

	char op = '-';
	int shouldLoop = 1;

	system("clear||cls");

	if (createFileTXT(fileName) == SUCCESS) {

		while (shouldLoop) {

			system("clear||cls");

			printf("\n############################\n");
			printf("###### EXHIBITOR MENU ######\n");
			printf("############################\n\n");

			printf("Choose your option: \n\n");
			printf("1 - Exibir na tela todos os atributos de .class\n");
			printf("2 - Gravar no arquivos todos os atributos de .class\n");

			printf("a - ShowInfo(ClassFile* jvm_class)\n");
			printf("b - ShowInfoOnFile(ClassFile* jvm_class, FILE* file)\n");
			printf("c - ShowConstantPool(ClassFile* jvm_class)\n");
			printf("d - ShowConstantPoolOnFile(ClassFile* jvm_class, FILE* file)\n");
			printf("e - ShowAttribute(ClassFile* jvm_class, attribute_info* attributeInfo)\n");
			printf("f - ShowAttributeOnFile(ClassFile* jvm_class, attribute_info* attributeInfo, FILE* file)\n");
			printf("g - ShowAllAttributes(ClassFile* jvm_class)\n");
			printf("h - ShowAllAttributesOnFile(ClassFile* jvm_class, FILE* file)\n");
			printf("i - ShowFields(ClassFile* jvm_class)\n");
			printf("j - ShowFieldsOnFile(ClassFile* jvm_class, FILE* file)\n");
			printf("k - ShowInterface(CpInfo cp)\n");
			printf("l - ShowInterfaceOnFile(ClassFile* jvm_class, CpInfo cp, FILE* file)\n");
			printf("m - ShowAllInterfaces(ClassFile* jvm_class)\n");
			printf("n - ShowAllInterfacesOnFile(CpInfo *cp, FILE* file)\n");
			printf("o - ShowMethods(ClassFile* jvm_class)\n");
			printf("p - ShowMethodsOnFile(ClassFile* jvm_class, FILE* file)\n");

			printf("z - Exit\n");

			scanf("%c", &op);
			while (getchar() != '\n');
			system("clear||cls");

			switch (op) {

			case '1':
				shouldLoop = 0;
				initProgramExhibitor->ShowConstantPool(jvm_class);
				initProgramExhibitor->ShowFields(jvm_class);
				//initProgramExhibitor->ShowMethods(jvm_class); erro de indice
				initProgramExhibitor->ShowAllAttributes(jvm_class);
				initProgramExhibitor->ShowInterface(jvm_class->constant_pool);
				initProgramExhibitor->ShowInfo(jvm_class);
				printf("Sucesso!\n");
				printf("Pressione enter para continuar\n");
				while (getchar() != '\n');
				break;

			case '2':
				shouldLoop = 0;
				initProgramExhibitor->ShowConstantPoolOnFile(jvm_class, initProgramFile);
				initProgramExhibitor->ShowFieldsOnFile(jvm_class, initProgramFile);
				//initProgramExhibitor->ShowMethodsOnFile(jvm_class, initProgramFile); erro de indice
				initProgramExhibitor->ShowAllAttributesOnFile(jvm_class, initProgramFile);
				initProgramExhibitor->ShowInterfaceOnFile(jvm_class->constant_pool, initProgramFile);
				initProgramExhibitor->ShowInfoOnFile(jvm_class, initProgramFile);
				printf("\nFile %s created successfully!\n", fileName);
				printf("Pressione enter para continuar\n");
				while (getchar() != '\n');
				break;

			case 'a':
				shouldLoop = 0;
				initProgramExhibitor->ShowInfo(jvm_class);
				printf("Pressione enter para continuar\n");
				while (getchar() != '\n');
				break;
			case 'b':
				shouldLoop = 0;
				initProgramExhibitor->ShowInfoOnFile(jvm_class, initProgramFile);
				printf("File %s created successfully!\n", fileName);
				printf("Pressione enter para continuar\n");
				while (getchar() != '\n');
				break;
			case 'c':
				shouldLoop = 0;
				initProgramExhibitor->ShowConstantPool(jvm_class);
				printf("Pressione enter para continuar\n");
				while (getchar() != '\n');
				break;
			case 'd':
				shouldLoop = 0;
				initProgramExhibitor->ShowConstantPoolOnFile(jvm_class, initProgramFile);
				printf("File %s created successfully!\n", fileName);
				printf("Pressione enter para continuar\n");
				while (getchar() != '\n');
				break;
			case 'e':
				shouldLoop = 0;
				for (int i = 0; i < jvm_class->attributes_count; i++)
					initProgramExhibitor->ShowAttribute(jvm_class, &(jvm_class->attributes[i]));
				printf("Pressione enter para continuar\n");
				while (getchar() != '\n');
				break;
			case 'f':
				shouldLoop = 0;
				for (int i = 0; i < jvm_class->attributes_count; i++)
					initProgramExhibitor->ShowAttributeOnFile(jvm_class, &(jvm_class->attributes[i]), initProgramFile);
				printf("File %s created successfully!\n", fileName);
				printf("Pressione enter para continuar\n");
				while (getchar() != '\n');
				break;
			case 'g':
				shouldLoop = 0;
				initProgramExhibitor->ShowAllAttributes(jvm_class);
				printf("Pressione enter para continuar\n");
				while (getchar() != '\n');
				break;
			case 'h':
				shouldLoop = 0;
				initProgramExhibitor->ShowAllAttributesOnFile(jvm_class, initProgramFile);
				printf("File %s created successfully!\n", fileName);
				printf("Pressione enter para continuar\n");
				while (getchar() != '\n');
				break;
			case 'i':
				shouldLoop = 0;
				initProgramExhibitor->ShowFields(jvm_class);
				printf("Pressione enter para continuar\n");
				while (getchar() != '\n');;
				break;
			case 'j':
				shouldLoop = 0;
				initProgramExhibitor->ShowFieldsOnFile(jvm_class, initProgramFile);
				fclose(initProgramFile);
				printf("File %s created successfully!\n", fileName);
				printf("Pressione enter para continuar\n");
				while (getchar() != '\n');;
				break;
			case 'k':
				initProgramExhibitor->ShowInterface(jvm_class->constant_pool);
				printf("Pressione enter para continuar\n");
				while (getchar() != '\n');;
				break;
			case 'l':
				shouldLoop = 0;
				initProgramExhibitor->ShowInterfaceOnFile(jvm_class->constant_pool, initProgramFile);
				printf("Pressione enter para continuar\n");
				while (getchar() != '\n');;
				break;
			case 'm':
				shouldLoop = 0;
				initProgramExhibitor->ShowAllInterfaces(jvm_class);
				printf("Pressione enter para continuar\n");
				while (getchar() != '\n');;
				break;
			case 'n':
				shouldLoop = 0;
				initProgramExhibitor->ShowAllInterfacesOnFile(jvm_class, initProgramFile);
				printf("Pressione enter para continuar\n");
				while (getchar() != '\n');;
				break;
			case 'o':
				shouldLoop = 0;
				//Com erro de indice
				//initProgramExhibitor->ShowMethods(jvm_class);
				printf("Função com erro\n");
				printf("Pressione enter para continuar\n");
				while (getchar() != '\n');
				break;
			case 'p':
				shouldLoop = 0;
				//Com erro de indice
				//initProgramExhibitor->ShowMethodsOnFile(jvm_class, initProgramFile);
				printf("Função com erro\n");
				printf("Pressione enter para continuar\n");
				while (getchar() != '\n');
				break;
			case 'z':
				shouldLoop = 0;
				break;
			default:
				shouldLoop = 0;
				break;
			}
		}
	}
	fclose(initProgramFile);
	free(fileName);
	printf("Programa finalizado\n");
}
