#include "Reader.h"

int main(int argc, char const *argv[])
{
	
	return 0;
}

//DECLARAÇÃO DE VARIÁVEIS
int infor;
char nome_classe[21];

//------------------------------------ FUNÇÃO MAIN
int main(int argc, char **argv) {
	
	int metmet=1, nomeIndex;
	opStck * pdo = create_stack();
	opStck ** top = &pdo;
	
	ClassFile *classe = (ClassFile *) malloc(sizeof(ClassFile));
	char op = argumentos_iniciais(argc, argv, classe);
	ler(classe); //leitor
	if(op!='e'){
		callback_exibidor(0, false);
    	int erro = exibir(classe, op); //exibidor
  		callback_exibidor(erro, true);
	}else{	

		//nomeIndex = classe->methods[metmet].name_index - 1;
        #define nameCmpr classe->constant_pool[nomeIndex].info.Utf8.bytes
       // printf("\nMetodo invocado: %s", nameCmpr);
		buildMthd(classe->methods[metmet].attributes->info.CodeAttribute.code, classe->methods[metmet].attributes->info.CodeAttribute.code_length, classe, top);
		 /*BYTECODE:
		for(int i=0; i<classe->methods[2].attributes->info.CodeAttribute.code_length; ++i){
			printf("%x\n", classe->methods[2].attributes->info.CodeAttribute.code[i]);
		}
		*/
	}
    return 0;
}
//------------------------------------ FIM FUNÇÃO MAIN

//IMPLEMENTAÇÃO DE FUNÇÕES AUXILIARES

//------------------------------------ FUNÇÃO QUE LÊ ARGUMENTOS DO TERMINAL NA HORA DA EXECUÇÃO

char argumentos_iniciais(int args_size, char **argv, ClassFile * classe){
     strcpy(nome_classe, argv[1]);
	char op; /// Modo de impressao (t - tela, a - arquivo, s - ambos, n - nenhum)
	char classe_n[21];

	if(args_size == 3)
		op = argv[2][0];
	else{
            printf("A quantidade de argumentos nao e valida.\n");
            printf("Digite o nome do arquivo com a classe a ser carregada (com a extensao):\n");
            strcpy(nome_classe, classe_n);
            printf("Voce quer imprimir as classes em tela (t), arquivo (a) ou ambos (d)? Caso queira executar a JVM, use (e)\n");
            scanf("%c", &op);
	}
	return op;
}

//------------------------------------ FUNÇÃO QUE LÊ DO .CLASS E CRIA O CLASSFILE

int ler(ClassFile * classe){
	infor = insere_classe(nome_classe, classe);
	return infor;
}

//------------------------------------ FUNÇÃO QUE RETORNA SUCESSO OU ERRO

void callback_exibidor(int erro, _Bool fim){
	if(!fim){
		if(infor != SUCESSO){
			printf("O carregamento foi interrompido.\n");
			exit(infor);
		}
	}else{
    	if(erro == ERRO_ARQUIVO){ // funçao de impressao
       		printf("**ERRO**: arquivo nao foi criado.\n");
       		exit(ERRO_ARQUIVO);
    	}else if(infor == SUCESSO) {
       		printf("***Leitor e exibidor foram efetudos com sucesso!!!\n");
       		exit(SUCESSO);
   		}else{
       		printf("A execucao foi interrompida!.\n");
       		exit(infor);
    	}
	}
}

//------------------------------------ FUNÇÃO QUE EXIBE O CONTEÚDO DO CLASS LOADER

int exibir(ClassFile *classe, char op) {
    FILE *arquivo_saida; //arquivo a ser gerado com a saída do exibidor
    char *fileName, *name; // nome dos arquivos
    int index = classe->constant_pool[classe->this_class - 1].info.Class.name_index - 1;
    name = informacao_nome(index, classe); // Recupera nome da classe
    fileName = (char *)malloc(sizeof(char) * (strlen(name)+5));
    strcpy(fileName, name);
    strcat(fileName, ".txt"); // Adiciona extensao txt

    switch(op) {
        case 'a': // Impressao em Arquivo
            arquivo_saida = fopen(fileName, "w");
            if (!arquivo_saida) {
                free(fileName);
                return ERRO_ARQUIVO;
            }
            mostra_poolDe_constantes_arquivo(classe, arquivo_saida);
            mostra_campos_arquivo(classe, arquivo_saida);
			mostra_metodos_arquivo(classe, arquivo_saida);
  			mostra_atributos_arquivo(classe, arquivo_saida);
			mostra_interfaces_arquivo(classe, arquivo_saida);
	    	mostra_outras_informacoes_arquivo(classe, arquivo_saida);
            fclose(arquivo_saida);
			printf("Arquivo %s criado com sucesso!\n", fileName);
            break;
        case 't': // Impressao em Tela
            mostra_poolDe_constantes(classe);
            mostra_campos(classe);
            mostra_metodos(classe);
            mostra_atributos(classe);
			mostra_interfaces(classe);
			mostra_outras_informacoes(classe);
            break;
        case 'd':
            arquivo_saida = fopen(fileName, "w");
            if (!arquivo_saida) {
                free(fileName);
                return ERRO_ARQUIVO;
            }
            mostra_poolDe_constantes(classe);
            mostra_poolDe_constantes_arquivo(classe, arquivo_saida);
            mostra_campos(classe);
     	    mostra_campos_arquivo(classe, arquivo_saida);
            mostra_metodos(classe);
          	mostra_metodos_arquivo(classe, arquivo_saida);
            mostra_atributos(classe);
          	mostra_atributos_arquivo(classe, arquivo_saida);
			mostra_interfaces(classe);
			mostra_interfaces_arquivo(classe, arquivo_saida);
            mostra_outras_informacoes(classe);
            mostra_outras_informacoes_arquivo(classe, arquivo_saida);
            fclose(arquivo_saida);
			printf("\nArquivo %s criado com sucesso!\n", fileName);
            break;
        default:
			printf("A opcao de impressao nao e valida. Por favor, rode novamente o programa e digite uma opcao valida.");
			printf("Opcoes: imprimir em tela (t), arquivo (a), ambos (d).\n");
            break;
    }
    free(fileName);

    return SUCESSO;
}
/*
int executa_programa(ClassFile *classe) {
    ListaClasses *lista_de_classes = NULL; /// Lista de classes carregadas no programa
    method_info *metodo_main = NULL;
    ClassFile *classe_inicial = NULL;
	lista_de_classes = InsereListaDeClasses(&lista_de_classes, classe);

	classe_inicial = RecuperaIesimaClasse(0, &(heap->listaDeClasses)); // Recupera a primeira classe
    carrega_instrucoes();

    metodo_main = recupera_metodo(classe_inicial, "main");
    if(!metodo_main) {
        printf("ERRO: Metodo MAIN nao encontrado.\n");
        return ERRO_MAIN;
    }

    if(!executa_init(classe, pilha_de_frames, heap)) {
        printf("ERRO: Metodo <init> nao encontrado.\n");
        return ERRO_MAIN;
    }

    prepara_metodo(metodo_main, classe_inicial, &pilha_de_frames, &heap);
    executa_metodo(metodo_main, classe_inicial, pilha_de_frames);

	if(heap != NULL)
		desalocaHeap(heap);
	if(pilha_de_frames != NULL)
        free(pilha_de_frames);

    return SUCESSO;
}*/