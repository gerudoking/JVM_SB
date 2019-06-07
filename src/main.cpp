/*!
 * \file main.cpp
 * \brief Modulo principal, dá a opção de escolha entre exibidor e interpretador
 */
#include "classeLeitorExibidor.h"

/**
 * @brief Funcao principal, dá a opção de escolha entre exibidor e interpretador
 * 
 * @param argc, *argv[]
 * @section Membros:
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

	LeitorExibidor leitorExibidor(argv[2]);

	if (argv[1][1] == 'e') { //exibidor
		if (leitorExibidor.carregar() == 0) {
			//imprime o bytecode lido
			leitorExibidor.exibir();
			if (leitorExibidor.inicializarArquivo(argv) == 0) {
				leitorExibidor.gravarArquivo();
				leitorExibidor.fecharArquivo();
			}
		}
	} else if (argv[1][1] == 'i') { //interpretador
		leitorExibidor.carregar();

		/*if (!leitorExibidor.existeMain()) {
			printf("O arquivo %s nao possui metodo main\n", argv[2]);
			return -1;
		} else if (leitorExibidor.obterStatus()) {
			return leitorExibidor.obterStatus();
		}*/

		if (!leitorExibidor.validacao()) {

			MethodArea::path = string(leitorExibidor.obterPath());
			MethodArea::adicionarClasse(&leitorExibidor);

			FrameStack frameStack(&leitorExibidor);
			frameStack.executarMetodos();
		}

	} else {
		printf("Parametros invalidos, o programa deve ser executado com: %s -e ou -i arquivo.class\n", argv[0]);
		return 1;
	}

	cout << "Fim do programa" << endl;

	return 0;
}
