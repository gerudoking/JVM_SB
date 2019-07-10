#include <cstdlib>
#include <cstdio>
#include <cstdlib>

#include <iostream>
#include <string>

#include "ClassVisao.h"
#include "Utils.h"
#include "Heap.h"
#include "InstanceClass.h"
#include "LeitorExibidor.h"
#include "MethodArea.h"
#include "Operations.h"
#include "StaticClass.h"

using namespace std;
/**
 * Software Básico 2019/1
 * Prof. Marcelo Ladeira
 *
 * Projeto Java Virtual Machine (JVM)
 *
 * @brief Funcao principal, dá a opção de escolha entre exibidor e interpretador
 *
 * @param argc, *argv[]
 * @brief Grupo 4
 * @brief Membros:
 * @author Ana Luisa Salvador Alvarez - 16/0048036
 * @author Eduardo de Azevedo dos Santos - 14/0136967
 * @author Iago Lobo Ribeiro de Moraes - 14/0082921
 * @author Luan Mendes Gonçalves Freitas - 15/0015585
 * @author Miguel Barreto Rezende Marques de Freitas - 12/0130424
 */
int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf("Parametros invalidos, o programa deve ser executado com: %s -e ou -i arquivo.class\n", argv[0]);
		return 1;
	}

	const char *file_className = argv[2];

	// Carregamento da classe de entrada.
	MethodArea &methodArea = MethodArea::getInstance();
	StaticClass *classRuntime = methodArea.carregarClassNamed(file_className);
	// Fim do carregamento.

	// Verificação se o nome da classe de entrada é igual ao nome do arquivo.
	string className = getFormattedConstant(classRuntime->getClassFile()->constant_pool, classRuntime->getClassFile()->this_class);

	string fileName(file_className);

	if (!Utils::verificarThisClass(fileName, className)) {
		cerr << "Nome do arquivo diferente do nome da classe." << endl;
		exit(1);
	}

	// Fim da verificação
	if (argv[1][1] == 'e') { //exibidor
		//const char *file_output = (argc < 3) ? NULL : argv[2];
		string nome = classRuntime->inicializarArquivo(argv);
		FILE *output = fopen(nome.append(".txt").c_str(), "w+");
		if (output == NULL) {
			cerr << "Erro ao abrir arquivo " << nome << "." << endl;
			exit(2);
		}
		printArquivoClassFile(classRuntime->getClassFile(), output);
		exibeClassFile(classRuntime->getClassFile());
		fclose(output);
	} else if (argv[1][1] == 'i') { //interpretador

		Operations &operations = Operations::getInstance();
		bool existeMain = operations.verificarMetodoExiste(classRuntime, "main", "([Ljava/lang/String;)V");
		if (!existeMain) {
			cerr << "O arquivo não possui metodo main" << "." << endl;
			exit(2);
		}
		operations.executarMetodos(classRuntime);
	}

	else {
		printf("Parametros invalidos, o programa deve ser executado com: %s -e ou -i arquivo.class\n", argv[0]);
		return 1;
	}

	//cout << "Fim do programa JVM" << endl;
	return 0;
}
