/*!
 * \file Methods.cpp
 * \brief
 */

#include "Methods.h"

Method_info lerMethod(FILE* arquivoEntrada, Cp_info *constantPool) {
	Method_info method;

	method.access_flags = lerU2(arquivoEntrada) & 0xFFF;
	method.name_index = lerU2(arquivoEntrada);
	method.descriptor_index = lerU2(arquivoEntrada);
	method.attributes_count = lerU2(arquivoEntrada);
	method.attributes = (Attribute_info *) malloc(sizeof(Attribute_info) * method.attributes_count);

	for (int i = 0; i < method.attributes_count; i++) {
		method.attributes[i] = lerAttribute(arquivoEntrada, constantPool);
	}

	return method;
}

Method_info *lerTodosMethods(FILE* arquivoEntrada, int tamanho, Cp_info *constantPool) {
	Method_info *method = (Method_info *) malloc(sizeof(Method_info) * tamanho);

	for (int i = 0; i < tamanho; i++) {
		method[i] = lerMethod(arquivoEntrada, constantPool);
	}

	return method;
}

void imprimirMethod(Method_info method, Cp_info *constantPool) {
	cout << "" << endl;
	cout << "\tNome: " << capturarIndiceDeReferencia(constantPool, method.name_index) << endl;
	cout << "\tDescritor: " << capturarIndiceDeReferencia(constantPool, method.descriptor_index) << endl;
	cout << obterFlagMethod(method.access_flags);
	cout << "\tNúmero de Atributos: " << (int) method.attributes_count << endl;

	for (int i = 0; i < method.attributes_count; i++) {
		cout << "\t\tAttribute " << i << ": " << endl;
		imprimirAttribute(method.attributes[i], constantPool);
	}
}

void imprimirMethod(Method_info method, Cp_info *constantPool, int indice) {
	cout << "\tMethod " << indice << ":" << endl;
	cout << "\t\tNome: cp info #" << method.name_index << " " << capturarIndiceDeReferencia(constantPool, method.name_index) << endl;
	cout << "\t\tDescritor: cp info # " << method.descriptor_index << capturarIndiceDeReferencia(constantPool, method.descriptor_index)
			<< endl;
	cout << "\t" << obterFlagMethod(method.access_flags);
	cout << "\t\tNúmero de Atributos: " << (int) method.attributes_count << endl;
	for (int i = 0; i < method.attributes_count; i++) {
		cout << "\tAttribute " << i << ": " << endl;
		imprimirAttribute(method.attributes[i], constantPool);
	}
}

void imprimirTodosMethods(Method_info *method, Cp_info *constantPool, int tamanho) {
	for (int i = 0; i < tamanho; i++) {
		imprimirMethod(method[i], constantPool, i);
	}
}

void gravarArquivoMethod(Method_info method, Cp_info *constantPool, int indice, fstream &arquivoSaida) {
	arquivoSaida << "\tMethod " << indice << ":" << endl;
	arquivoSaida << "\t\tNome: cp info #" << method.name_index << " " << capturarIndiceDeReferencia(constantPool, method.name_index)
			<< endl;
	arquivoSaida << "\t\tDescritor: cp info # " << method.descriptor_index
			<< capturarIndiceDeReferencia(constantPool, method.descriptor_index) << endl;
	arquivoSaida << "\t" << obterFlagMethod(method.access_flags);
	arquivoSaida << "\t\tNúmero de Atributos: " << (int) method.attributes_count << endl;
	for (int i = 0; i < method.attributes_count; i++) {
		arquivoSaida << "\tAttribute " << i << ": " << endl;
		gravarArquivoAttribute(method.attributes[i], constantPool, arquivoSaida);
	}
}

void gravarArquivoTodosMethods(Method_info *method, Cp_info *constantPool, int tamanho, fstream &arquivoSaida) {
	for (int i = 0; i < tamanho; i++) {
		gravarArquivoMethod(method[i], constantPool, i, arquivoSaida);
	}
}

string obterFlagMethod(uint16_t flag) {
	bool primeiro = true;
	string flagMethod = "";

	if (flag & 0x01) {
		if (primeiro) {
			flagMethod += "\tflags: ";
			primeiro = false;
		} else {
			flagMethod += ", ";
		}
		flagMethod += "ACC_PUBLIC";
	}

	if (flag & 0x02) {
		if (primeiro) {
			flagMethod += "\tflags: ";
			primeiro = false;
		} else {
			flagMethod += ", ";
		}
		flagMethod += "ACC_PRIVATE";
	}

	if (flag & 0x04) {
		if (primeiro) {
			flagMethod += "\tflags: ";
			primeiro = false;
		} else {
			flagMethod += ", ";
		}
		flagMethod += "ACC_PROTECTED";
	}

	if (flag & 0x08) {
		if (primeiro) {
			flagMethod += "\tflags: ";
			primeiro = false;
		} else {
			flagMethod += ", ";
		}
		flagMethod += "ACC_STATIC";
	}

	if (flag & 0x010) {
		if (primeiro) {
			flagMethod += "\tflags: ";
			primeiro = false;
		} else {
			flagMethod += ", ";
		}
		flagMethod += "ACC_FINAL";
	}

	if (flag & 0x020) {
		if (primeiro) {
			flagMethod += "\tflags: ";
			primeiro = false;
		} else {
			flagMethod += ", ";
		}
		flagMethod += "ACC_SYNCHRONIZED";
	}

	if (flag & 0x0100) {
		if (primeiro) {
			flagMethod += "\tflags: ";
			primeiro = false;
		} else {
			flagMethod += ", ";
		}
		flagMethod += "ACC_NATIVE";
	}

	if (flag & 0x0400) {
		if (primeiro) {
			flagMethod += "\tflags: ";
			primeiro = false;
		} else {
			flagMethod += ", ";
		}
		flagMethod += "ACC_ABSTRACT";
	}

	if (flag & 0x0800) {
		if (primeiro) {
			flagMethod += "\tflags: ";
			primeiro = false;
		} else {
			flagMethod += ", ";
		}
		flagMethod += "ACC_STRICT";
	}

	flagMethod += "\n";

	return flagMethod;
}
