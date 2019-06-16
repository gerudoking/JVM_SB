/*!
 * \file interfaces.cpp
 * \brief
 */

#include "Interfaces.h"

unsigned short *lerTodasInterfaces(FILE* arquivoEntrada, int tamanho) {
	unsigned short *vetorInterfaces = (unsigned short *) malloc(sizeof(int) * tamanho);

	for (int i = 0; i < tamanho; i++) {
		vetorInterfaces[i] = lerU2(arquivoEntrada);
	}

	return vetorInterfaces;
}

void imprimirTodasInterfaces(unsigned short *interface, cp_info *constantPool, int tamanho) {
	for (int i = 0; i < tamanho; i++) {
		imprimirInterface(interface[i], constantPool, i);
	}
}

void imprimirInterface(unsigned short interface, cp_info *constantPool, int indice) {
	cout << "\tInterface " << indice << ": " << capturarIndiceDeReferencia(constantPool, interface) << endl;
}

void gravarArquivoTodasInterfaces(unsigned short *interface, cp_info *constantPool, int tamanho, fstream &arquivoSaida) {
	for (int i = 0; i < tamanho; i++) {
		gravarArquivoInterface(interface[i], constantPool, i, arquivoSaida);
	}
}

void gravarArquivoInterface(unsigned short interface, cp_info *constantPool, int indice, fstream &arquivoSaida) {
	arquivoSaida << "\tInterface " << indice << ": " << capturarIndiceDeReferencia(constantPool, interface) << endl;
}
