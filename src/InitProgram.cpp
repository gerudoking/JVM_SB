#include "InitProgram.h"

InitProgram::InitProgram()
{
	initProgramReader = new Reader();
}

InitProgram::~InitProgram() { }

char InitProgram::StartProgram(int args_size, char **argv, ClassFile * jvm_class)
{
    strcpy(className, argv[1]);
}

int InitProgram::ReadClass(ClassFile* jvm_class)
{
    printf("\nReading class...\n");
	int result = initProgramReader->InsertClass(className, jvm_class);
	free(initProgramReader);
	return result;
}

void InitProgram::JVM_Menu(ClassFile *jvm_class, FILE* file)
{
	initProgramExhibitor = new Exhibitor();

	printf("\n############################\n");
	printf("###### EXHIBITOR MENU ######\n");
	printf("############################\n\n");

	char op = '-';
	int shouldLoop = 1;

	while(shouldLoop)
	{
		printf("Choose your option: \n\n");
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
		printf("n - ShowAllInterfacesOnFile(ClassFile* jvm_class, FILE* file)\n");
		printf("o - ShowMethods(ClassFile* jvm_class)\n");
		printf("p - ShowMethodsOnFile(ClassFile* jvm_class, FILE* file)\n");
		printf("q - ShowInfo(ClassFile* jvm_class)\n");
		printf("r - ShowInfo(ClassFile* jvm_class)\n");
		printf("s - ShowInfo(ClassFile* jvm_class)\n");

		scanf("%c", &op);
		while(getchar()!='\n');

		switch(op)
		{
			case 'a':
				shouldLoop = 0;
				initProgramExhibitor->ShowInfo(jvm_class);
				break;
			case 'b':
				shouldLoop = 0;
				initProgramExhibitor->ShowInfoOnFile(jvm_class, initProgramFile);
				break;
			case 'c':
				shouldLoop = 0;
				initProgramExhibitor->ShowConstantPool(jvm_class);
				break;
			case 'd':
				shouldLoop = 0;
				initProgramExhibitor->ShowConstantPoolOnFile(jvm_class, initProgramFile);
				break;
			case 'e':
				shouldLoop = 0;
				break;
			case 'f':
				shouldLoop = 0;
				break;
			case 'g':
				shouldLoop = 0;
				break;
			case 'h':
				shouldLoop = 0;
				break;
			case 'i':
				shouldLoop = 0;
				break;
			case 'j':
				shouldLoop = 0;
				break;
			case 'k':
				shouldLoop = 0;
				break;
			case 'l':
				shouldLoop = 0;
				break;
			case 'm':
				shouldLoop = 0;
				break;
			case 'n':
				shouldLoop = 0;
				break;
			case 'o':
				shouldLoop = 0;
				break;
			case 'p':
				shouldLoop = 0;
				break;
			case 'q':
				shouldLoop = 0;
				break;
			case 'r':
				shouldLoop = 0;
				break;
			case 's':
				shouldLoop = 0;
				break;
			default:
				shouldLoop = 0;
				break;
		}
	}
}