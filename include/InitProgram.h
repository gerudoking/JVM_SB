#ifndef INITPROGRAM_H
#define INITPROGRAM_H

#include <string.h>
#include <fstream>
#include "Reader.h"

using namespace std;

class InitProgram
{
public:
	InitProgram();
	~InitProgram();

    char className[21];
    Reader* initProgramReader;

    char StartProgram(int args_size, char **argv, ClassFile * jvm_class);
    int ReadClass(ClassFile *jvm_class);

private:
};

#endif