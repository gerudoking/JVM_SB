

#include "Utils.h"

using namespace std;

double Utils::verificarVersao(ClassFile *classFile) {
    if (classFile->major_version < 45 || classFile->major_version > 52) {
        return 0;
    }
    
    if (classFile->major_version <= 48) {
        return 1.0 + (classFile->major_version - 44)*0.1;
    }
    
    return 5 + (classFile->major_version - 49);
}

bool Utils::verificarThisClass(string auxFilename, string auxClass ) {
	int auxPos;

	//remove extensao .class
	auxFilename = auxFilename.substr(0, auxFilename.size() - 6);

	//remove nomes de pastas no Windows
	auxPos = auxFilename.find("\\");

	while (auxPos >= 0 && (unsigned int) auxPos <= auxFilename.size()) {
		auxFilename = auxFilename.substr(auxPos + 1);
		auxPos = auxFilename.find("\\");
	}

	//remove nomes de pastas no Linux
	auxPos = auxFilename.find("/");
	while (auxPos >= 0 && (unsigned int) auxPos <= auxFilename.size()) {
		auxFilename = auxFilename.substr(auxPos + 1);
		auxPos = auxFilename.find("/");
	}
	//..
	//remove nomes de pastas no Windows
	auxPos = auxClass.find("\\");

	while (auxPos >= 0 && (unsigned int) auxPos <= auxClass.size()) {
		auxClass = auxClass.substr(auxPos + 1);
		auxPos = auxClass.find("\\");
	}

	//remove nomes de pastas no Linux
	auxPos = auxClass.find("/");
	while (auxPos >= 0 && (unsigned int) auxPos <= auxClass.size()) {
		auxClass = auxClass.substr(auxPos + 1);
		auxPos = auxClass.find("/");
	}

	return (auxClass == auxFilename);
}
/**	@fn int verificarVersaoClass(ClassFile *classFile)
	 * Converte os dados de versão obtidos da struct classFile para a convenção encontrada em https://en.wikipedia.org/wiki/Java_class_file#General_layout
	 *
	 * Não Tratados
	 * Java SE 14 = 58
	 * Java SE 13 = 57
	 * Java SE 12 = 56
	 * Java SE 11 = 55
	 * Java SE 10 = 54
	 * Java SE 9 = 53
	 *
	 * Tratados
	 * J2SE 8 = 52
	 * J2SE 7 = 51
	 * J2SE 6.0 = 50
	 * J2SE 5.0 = 49
	 * JDK 1.4 = 48
	 * JDK 1.3 = 47
	 * JDK 1.2 = 46
	 * JDK 1.1 = 45
	 * @return O valor equivalente à versão lida em *classFile.
	 */

double Utils::verificarVersaoClass(ClassFile *classFile) {
	if (classFile->major_version < 45 || classFile->major_version > 52) {
		return 5 + (classFile->major_version  - 49);
	}

/*
	 if (classFile->major_version <= 48) {
	        return 1.0 + (classFile->major_version - 44)*0.1;
	  }
*/


	return 0;
}

bool Utils::compararUtf8String(CONSTANT_Utf8_info constant, const char *str) {
    if (constant.length != strlen(str)) {
        return false;
    }
    
    for (int i = 0; i < constant.length; i++) {
        if(constant.bytes[i] != str[i]) return false;
    }
    
    return true;
}

void Utils::imprintTabs(FILE *out, uint8_t n) {
    for (uint8_t i = 0; i < n; i++) fprintf(out, "\t");
}
void Utils::exibeTabs(uint8_t n) {
    for (uint8_t i = 0; i < n; i++) printf( "\t");
}
const char* Utils::converterStreamToCString(const stringstream &ss) {
    string tmp = ss.str();
    char *result = (char*) malloc(sizeof(char) * (tmp.size() + 1));
    tmp.copy(result, tmp.size());
    result[tmp.size()] = '\0';
    
    return result;
}
