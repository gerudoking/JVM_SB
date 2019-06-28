/*!
 * \file Main.cpp
 * \brief Modulo principal, dá a opção de escolha entre exibidor e interpretador
 */
#include "ClassFile.h"
#include "LeitorExibidor.h"

/**
 * Software Básico 2019/1
 * Prof. Marcelo Ladeira
 *
 * Projeto Java Virtual Machine (JVM)
 *
 * @brief Funcao principal, dá a opção de escolha entre exibidor e interpretador
 * 
 * @param argc, *argv[]
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

	ClassFile classFile(argv[2]);
	LeitorExibidor leitorExibidor(&classFile);

	if (argv[1][1] == 'e') { //exibidor

		if (leitorExibidor.classFile->carregar() == 0) {

			//imprime o bytecode lido
			leitorExibidor.classFile->exibir();
			if (leitorExibidor.classFile->inicializarArquivo(argv) == 0) {
				leitorExibidor.classFile->gravarArquivo();
				leitorExibidor.classFile->fecharArquivo();
			}
		}
	} else if (argv[1][1] == 'i') { //interpretador
		leitorExibidor.classFile->carregar();

		if (leitorExibidor.classFile->obterStatus() == 0 && !leitorExibidor.classFile->validacao()) {

			MethodArea::path = string(leitorExibidor.classFile->obterPath());
			MethodArea::adicionarClasse(&classFile);

			PilhaJVM pilhaJVM(&classFile);
			pilhaJVM.executarMetodos();
		}

	} else {
		printf("Parametros invalidos, o programa deve ser executado com: %s -e ou -i arquivo.class\n", argv[0]);
		return 1;
	}

	cout << "Fim do programa JVM" << endl;

	return 0;
}
