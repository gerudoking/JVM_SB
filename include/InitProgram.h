#ifndef INITPROGRAM_H
#define INITPROGRAM_H

#include <string.h>
#include <fstream>
#include "Reader.h"

using namespace std;

class InitProgram {
public:
	InitProgram();
	~InitProgram();

	char className[21];
	Reader* initProgramReader;
	Exhibitor* initProgramExhibitor;
	FILE* initProgramFile;

	void StartProgram(char **argv);
	int ReadClass(ClassFile *jvm_class);
	void JVM_Menu(ClassFile *jvm_class);
	int createFileTXT(char *fileName);

};

#endif
