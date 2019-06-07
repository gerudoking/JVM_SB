/*!
 * \file constantPool.cpp
 * \brief Este módulo contém as funções necessárias para a manipulação do pool de constantes.
 */

#include "constantPool.h"

int carregarConstantPool(cp_info *constantPool, int tamanho, FILE* arquivoEntrada) {
	int i;

	for (i = 1; i < tamanho; i++) {
		// Retorna a tag
		constantPool[i].tag = lerU1(arquivoEntrada);

		// Checa o tipo do campo
		if (!(constantPool[i].tag > 0) && !(constantPool[i].tag <= 12) && !(constantPool[i].tag != 2)) {
			// Se não sabe o tipo, termina a função
			return i;
		}

		// Lê o dado de acordo com o tipo
		switch (constantPool[i].tag) {
		case UTF8:
			constantPool[i].info = (ClassLoaderType *) malloc(sizeof(ClassLoaderType) * 2);
			constantPool[i].info[0].u2 = lerU2(arquivoEntrada);
			constantPool[i].info[1].array = lerUTF8(arquivoEntrada, constantPool[i].info[0].u2);
			break;

		case INTEGER:
		case FLOAT:
			constantPool[i].info = (ClassLoaderType *) malloc(sizeof(ClassLoaderType));
			constantPool[i].info[0].u4 = lerU4(arquivoEntrada);
			break;

		case LONG:
		case DOUBLE:
			constantPool[i].info = (ClassLoaderType *) malloc(sizeof(ClassLoaderType));
			constantPool[i].info[0].u4 = lerU4(arquivoEntrada);
			constantPool[++i].tag = INVALID; //indica no proximo espaco que ele deve ser ignorado
			constantPool[i].info = (ClassLoaderType *) malloc(sizeof(ClassLoaderType));
			constantPool[i].info[0].u4 = lerU4(arquivoEntrada);
			break;

		case CLASS:
		case STRING:
			constantPool[i].info = (ClassLoaderType *) malloc(sizeof(ClassLoaderType));
			constantPool[i].info[0].u2 = lerU2(arquivoEntrada);
			break;

		case FIELD_REF:
		case METHOD_REF:
		case INTERFACE_REF:
		case NAME_AND_TYPE:
			constantPool[i].info = (ClassLoaderType *) malloc(sizeof(ClassLoaderType) * 2);
			constantPool[i].info[0].u2 = lerU2(arquivoEntrada);
			constantPool[i].info[1].u2 = lerU2(arquivoEntrada);
			break;
		}
	}

	// Retorna o número de elementos
	return i;
}

string capturarIndiceDeReferencia(cp_info *constantPool, U2 indice) {
	switch (constantPool[indice].tag) {
	case UTF8:
		// Return the string
		return obterUTF8(constantPool[indice].info[1].array, constantPool[indice].info[0].u2);

	case CLASS:
	case STRING:
		// Get the string from the info field
		return capturarIndiceDeReferencia(constantPool, constantPool[indice].info[0].u2);

	case NAME_AND_TYPE:
		// Get the string from the two info fields separeted bi ':'
		return (capturarIndiceDeReferencia(constantPool, constantPool[indice].info[0].u2) + "  "
				+ capturarIndiceDeReferencia(constantPool, constantPool[indice].info[1].u2));

	case METHOD_REF:
	case INTERFACE_REF:
	case FIELD_REF:
		// Get the string from the two info fields separeted bi '.'
		return (capturarIndiceDeReferencia(constantPool, constantPool[indice].info[0].u2) + "  "
				+ capturarIndiceDeReferencia(constantPool, constantPool[indice].info[1].u2));
	}
	return "";
}

void imprimirConstantPool(cp_info *constantPool, int tamanho) {
	cout << "Constant Pool:" << endl;

	for (int i = 1; i < tamanho; i++) {
		printf("\t [%3d] ", i);
		cout << nomeTiposDados[constantPool[i].tag - 1];
		switch (constantPool[i].tag) {
		case UTF8: //tem um campo u2 e um array de u1 como info
			cout << "\t" << obterUTF8(constantPool[i].info[1].array, constantPool[i].info[0].u2);
			break;
		case INTEGER: //tem apenas um campo u4 em info
			cout << "\t" << constantPool[i].info[0].u4;
			break;
		case FLOAT: //tem apenas um campo u4 em info que deve ser convertido para float
			cout << "\t" << converter_u4_to_float(constantPool[i].info[0]) << "f";
			break;
		case LONG: //tem dois campos u4 em info que devem ser convertidos em um long
			cout << "\t" << converter_u4_to_long(constantPool[i].info[0], constantPool[i + 1].info[0]) << "l";
			i++; //para ignorar o proximo slot
			break;
		case DOUBLE: //tem dois campos u4 em infoque devem ser convertidos em um double
			cout << "\t" << converter_u4_to_double(constantPool[i].info[0], constantPool[i + 1].info[0]) << "d";
			i++; //para ignorar o proximo slot
			break;
		case CLASS: //tem apenas um campo u2 em info
		case STRING:
			cout << " " << constantPool[i].info[0].u2 << "\t\t// " << capturarIndiceDeReferencia(constantPool, i);
			break;
		case NAME_AND_TYPE: //tipo que tem dois campos u2 de info e usam o ':' para separar eles
			cout << " cp info #" << constantPool[i].info[0].u2 << "  cp info #" << constantPool[i].info[1].u2;
			cout << "\t\t// " << capturarIndiceDeReferencia(constantPool, i);
			break;
		case METHOD_REF: //tipos que tem dois campos u2 de info e usam o '.' para separar eles
		case INTERFACE_REF:
		case FIELD_REF:
			cout << " cp info #" << constantPool[i].info[0].u2 << "  cp info #" << constantPool[i].info[1].u2;
			cout << "\t\t// " << capturarIndiceDeReferencia(constantPool, i);
			break;
		}
		cout << endl;
	}
	cout << endl;
}

void gravarArquivoConstantPool(cp_info *constantPool, int tamanho, fstream &arquivoSaida) {
	arquivoSaida << "Constant Pool:" << endl;

	for (int i = 1; i < tamanho; i++) {
		arquivoSaida << "\t [ " << i << " ]";
		arquivoSaida << nomeTiposDados[constantPool[i].tag - 1];
		switch (constantPool[i].tag) {
		case UTF8: //tem um campo u2 e um array de u1 como info
			arquivoSaida << "\t" << obterUTF8(constantPool[i].info[1].array, constantPool[i].info[0].u2);
			break;
		case INTEGER: //tem apenas um campo u4 em info
			arquivoSaida << "\t" << constantPool[i].info[0].u4;
			break;
		case FLOAT: //tem apenas um campo u4 em info que deve ser convertido para float
			arquivoSaida << "\t" << converter_u4_to_float(constantPool[i].info[0]) << "f";
			break;
		case LONG: //tem dois campos u4 em info que devem ser convertidos em um long
			arquivoSaida << "\t" << converter_u4_to_long(constantPool[i].info[0], constantPool[i + 1].info[0]) << "l";
			i++; //para ignorar o proximo slot
			break;
		case DOUBLE: //tem dois campos u4 em infoque devem ser convertidos em um double
			arquivoSaida << "\t" << converter_u4_to_double(constantPool[i].info[0], constantPool[i + 1].info[0]) << "d";
			i++; //para ignorar o proximo slot
			break;
		case CLASS: //tem apenas um campo u2 em info
		case STRING:
			arquivoSaida << " " << constantPool[i].info[0].u2 << "\t\t// " << capturarIndiceDeReferencia(constantPool, i);
			break;
		case NAME_AND_TYPE: //tipo que tem dois campos u2 de info e usam o ':' para separar eles
			arquivoSaida << " cp info #" << constantPool[i].info[0].u2 << "  cp info #" << constantPool[i].info[1].u2;
			arquivoSaida << "\t\t// " << capturarIndiceDeReferencia(constantPool, i);
			break;
		case METHOD_REF: //tipos que tem dois campos u2 de info e usam o '.' para separar eles
		case INTERFACE_REF:
		case FIELD_REF:
			arquivoSaida << " cp info #" << constantPool[i].info[0].u2 << "  cp info #" << constantPool[i].info[1].u2;
			arquivoSaida << "\t\t// " << capturarIndiceDeReferencia(constantPool, i);
			break;
		}
		arquivoSaida << endl;
	}
	arquivoSaida << endl;
}
