#include "InitProgram.h"

InitProgram::InitProgram()
{
	initProgramReader = new Reader();
}

InitProgram::~InitProgram() { }

char InitProgram::StartProgram(int args_size, char **argv, ClassFile * jvm_class)
{
    strcpy(className, argv[1]);
	char op = '-'; // (s for screen, f for file, b for both, n for none)
	char classNewName[21];

	if(args_size == 3)
		return op = argv[2][0];
	else
    {
        printf("\nOPERATION ARGUMENT NOT VALID!\n");
        exit(1);
	}
}

//------------------------------------ FUNÇÃO QUE LÊ DO .CLASS E CRIA O CLASSFILE

int InitProgram::ReadClass(ClassFile* jvm_class)
{
    printf("Reading class...");
	return initProgramReader->InsertClass(className, jvm_class);
}