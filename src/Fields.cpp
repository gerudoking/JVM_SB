/*!
 * \file Fields.cpp
 * \brief Módulo responsável pela manipulação dos campos existentes no arquivo .class
 */

#include "Fields.h"

void imprimirField(Field_info field, Cp_info *constantPool, int indice) {
	printf("\tField %d : \n", indice);
	printf("\t%s", obterFlagField(field.accessFlags).c_str());
	printf("\t\tNome: %s\n", capturarIndiceDeReferencia(constantPool, field.name_index).c_str());
	printf("\t\tDescritor: %s\n", capturarIndiceDeReferencia(constantPool, field.descriptor_index).c_str());
	printf("\t\tNúmero de Atributos: %d\n", (int) field.attributes_count);

	for (int i = 0; i < field.attributes_count; i++) {
		printf("\t\t\tAtributo %d:", i);
		imprimirAttribute(field.attributes[i], constantPool);
	}
}

void imprimirTodosField(Field_info *field, Cp_info *constantPool, int tamanho) {
	for (int i = 0; i < tamanho; i++) {
		imprimirField(field[i], constantPool, i);
	}
}

void gravarArquivoField(Field_info field, Cp_info *constantPool, int indice, fstream &arquivoSaida) {
	printf("\tField %d : \n", indice);
	printf("\t%s", obterFlagField(field.accessFlags).c_str());
	printf("\t\tNome: %s\n", capturarIndiceDeReferencia(constantPool, field.name_index).c_str());
	printf("\t\tDescritor: %s\n", capturarIndiceDeReferencia(constantPool, field.descriptor_index).c_str());
	printf("\t\tNúmero de Atributos: %d\n", (int) field.attributes_count);

	for (int i = 0; i < field.attributes_count; i++) {
		printf("\t\t\tAtributo %d:", i);
		gravarArquivoAttribute(field.attributes[i], constantPool, arquivoSaida);
	}
}

void gravarArquivoTodosField(Field_info *field, Cp_info *constantPool, int tamanho, fstream &arquivoSaida) {
	for (int i = 0; i < tamanho; i++) {
		gravarArquivoField(field[i], constantPool, i, arquivoSaida);
	}
}

Field_info lerField(FILE* arquivoEntrada, Cp_info* constantPool) {
	Field_info field;

	field.accessFlags = lerU2(arquivoEntrada) & 0X0df;
	field.name_index = lerU2(arquivoEntrada);
	field.descriptor_index = lerU2(arquivoEntrada);
	field.attributes_count = lerU2(arquivoEntrada);
	field.attributes = (Attribute_info *) malloc(sizeof(Attribute_info) * field.attributes_count);
	for (int i = 0; i < field.attributes_count; i++) {
		field.attributes[i] = lerAttribute(arquivoEntrada, constantPool);
	}

	return field;
}

Field_info *lerTodosFields(FILE* arquivoEntrada, int tamanho, Cp_info* constantPool) {
	Field_info *field = (Field_info *) malloc(sizeof(Field_info) * tamanho);

	for (int i = 0; i < tamanho; i++) {
		field[i] = lerField(arquivoEntrada, constantPool);
	}
	return field;
}

string obterFlagField(unsigned short flag) {
	bool primeiro = true;
	string flagField = "";

	if (flag & 0x01) {
		if (primeiro) {
			flagField += "\tflags: ";
			primeiro = false;
		} else {
			flagField += ", ";
		}
		flagField += "ACC_PUBLIC";
	}

	if (flag & 0x02) {
		if (primeiro) {
			flagField += "\tflags: ";
			primeiro = false;
		} else {
			flagField += ", ";
		}
		flagField += "ACC_PRIVATE";
	}

	if (flag & 0x04) {
		if (primeiro) {
			flagField += "\tflags: ";
			primeiro = false;
		} else {
			flagField += ", ";
		}
		flagField += "ACC_PROTECTED";
	}

	if (flag & 0x08) {
		if (primeiro) {
			flagField += "\tflags: ";
			primeiro = false;
		} else {
			flagField += ", ";
		}
		flagField += "ACC_STATIC";
	}

	if (flag & 0x010) {
		if (primeiro) {
			flagField += "\tflags: ";
			primeiro = false;
		} else {
			flagField += ", ";
		}
		flagField += "ACC_FINAL";
	}

	if (flag & 0x040) {
		if (primeiro) {
			flagField += "\tflags: ";
			primeiro = false;
		} else {
			flagField += ", ";
		}
		flagField += "ACC_VOLATILE";
	}

	if (flag & 0x080) {
		if (primeiro) {
			flagField += "\tflags: ";
			primeiro = false;
		} else {
			flagField += ", ";
		}
		flagField += "ACC_TRANSIENT";
	}

	flagField += "\n";

	return flagField;
}
