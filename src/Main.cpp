#include "InitProgram.h"

int main(int argc, char *argv[]) {
	InitProgram* initProgram = new InitProgram();

	ClassFile *mainClass = (ClassFile *) malloc(sizeof(ClassFile));

	char op = initProgram->StartProgram(argc, argv, mainClass);
	initProgram->ReadClass(mainClass);

	initProgram->JVM_Menu(mainClass, initProgram->initProgramFile);

	free(initProgram);
	return 0;
}
