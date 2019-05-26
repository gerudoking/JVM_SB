#include "InitProgram.h"

int main(int argc, char *argv[]) {
	(void)argc;
	InitProgram* initProgram = new InitProgram();

	ClassFile *mainClass = (ClassFile *) malloc(sizeof(ClassFile));

	initProgram->StartProgram(argv);
	initProgram->ReadClass(mainClass);

	initProgram->JVM_Menu(mainClass);

	free(initProgram);
	return 0;
}
