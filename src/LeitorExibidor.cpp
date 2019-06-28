#include <string>
#include "LeitorExibidor.h"
#include "BasicTypes.h"
#include "Methods.h"

LeitorExibidor::LeitorExibidor() {
	classFile = NULL;
}

LeitorExibidor::LeitorExibidor(ClassFile *pClass) {
	classFile = pClass;
}

