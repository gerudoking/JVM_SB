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