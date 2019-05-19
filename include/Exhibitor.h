/** @file exibidor.h
 *  @brief Funções para exibir conteúdo da JVM na tela e em arquivos
 */

//---------------
// é chamado por: main.c
// chama: ---
//---------------

//--- INCLUDE'S

#include <stdio.h>
#include "Reader.h"

//--- DEFINE'S

#define REQ_METHODREF_1 61
#define REQ_METHODREF_2 62
#define REQ_FIELDREF 63
#define REQ_LDCREF_1 64
#define REQ_LDCREF_2 65
#define REQ_JMPREF 66
#define REQ_ARRAYREF 67
#define REQ_IINCREF 68

//--- FUNÇÕES

/**
*  @brief Função que mostra informações na tela
* @param classe Ponteiro para o arquivo de classe a ser printado na tela
*/
void mostra_outras_informacoes(ClassFile *classe);

/**
*   @brief Função para mostrar informações em um arquivo
*   @param classe   Ponteiro para o arquivo de classe a ser salvo no arquivo
*   @param file     Ponteiro para o arquivo a ser manipulado
*/
void mostra_outras_informacoes_arquivo(ClassFile *classe, FILE *file);

/**
*  @brief Função que exibe a pool de constantes
* @param classe Ponteiro para o arquivo de classe a ser printado na tela
*/

void mostra_poolDe_constantes(ClassFile *classe);
/**
*   @brief Função para mostrar a pool de constantes em um arquivo
*   @param classe   Ponteiro para o arquivo de classe a ser salvo no arquivo
*   @param file     Ponteiro para o arquivo a ser manipulado
*/
void mostra_poolDe_constantes_arquivo(ClassFile *classe, FILE *file);

/**
*   @brief Função para mostrar um atributo específico na tela
*   @param attributeInfo    Ponteiro para as informações do atributo
*   @param classe           Ponteiro para o arquivo de classe do atributo
*/
void mostra_atributo(attribute_info *attributeInfo, ClassFile *classe);

/**
*   @brief Função para mostrar um atributo específico e salvar em um arquivo
*   @param attributeInfo    Ponteiro para as informações do atributo
*   @param classe           Ponteiro para o arquivo de classe
*   @param file             Ponteiro para o arquivo a ser manipulado
*/
void mostra_atributo_arquivo(attribute_info *attributeInfo, ClassFile *classe, FILE *file);

/**
*   @brief Função para mostrar todos os atributos de um class file na tela
*   @param classe           Ponteiro para o arquivo de classe
*/
void mostra_atributos(ClassFile *classe);

/**
*   @brief Função para mostrar todos os atributos de um class file e salvar em um arquivo
*   @param classe           Ponteiro para o arquivo de classe
*   @param file             Ponteiro para o arquivo a ser manipulado
*/
void mostra_atributos_arquivo(ClassFile *classe, FILE *file);

/**
*   @brief Função para mostrar todos os campos de um class file e mostrar na tela
*   @param classe           Ponteiro para o arquivo de classe
*   @param file             Ponteiro para o arquivo a ser manipulado
*/
void mostra_campos(ClassFile *classe);

/**
*   @brief Função para mostrar todos os campos de um class file e salvar em um arquivo
*   @param classe           Ponteiro para o arquivo de classe
*   @param file             Ponteiro para o arquivo a ser manipulado
*/
void mostra_campos_arquivo(ClassFile *classe, FILE *file);

/**
*   @brief Função para fazer a interface com o valor de informação a ser mostrado na tela
*   @param val_cpinfo  Valor a ser selecionado
*/
void mostra_interface(cp_info val_cpinfo);

/**
*   @brief Função para fazer a interface com o valor de informação a ser mostrado em um arquivo
*   @param val_cpinfo  Valor a ser selecionado
*   @param file        Ponteiro para o arquivo a ser manipulado
*/
void mostra_interface_arquivo(ClassFile *classe, FILE *file, cp_info val_cpinfo);

/**
*   @brief Função para mostrar o número de interfaces de um class file na tela
*   @param classe  Ponteiro do class file a ser mostrado
*/
void mostra_interfaces(ClassFile *classe);

/**
*   @brief Função para mostrar o número de interfaces de um class file em um arquivo
*   @param classe  Ponteiro do class file a ser mostrado
*   @param file        Ponteiro para o arquivo a ser manipulado
*/
void mostra_interfaces_arquivo(ClassFile * classe, FILE *file);

/**
*   @brief Função para mostrar os métodos do class file na tela
*   @param classe  Ponteiro do class file a ser mostrado
*/
void mostra_metodos(ClassFile *classe);

/**
*   @brief Função para mostrar os métodos do class file em um arquivo
*   @param classe  Ponteiro do class file a ser mostrado
*   @param file    Ponteiro para o arquivo a ser manipulado
*/
void mostra_metodos_arquivo(ClassFile *classe, FILE *file);

/**
*   @brief Faz o mapeamento dos mnemônicos de todas as instruções
*   @param mapa  Ponteiro para o mapa de instruções
*/
void mnemonicos(Instrucao *mapa);

/**
*   @brief Função que retorna a string com informação do nome de um campo do class file
*   @param classe  Ponteiro do class file a ser utilizado
*   @param index   Índice da constant pool
*/
char* informacao_nome(u2 index, ClassFile *classe);

/**
*   @brief Função que retorna a string com informação do método de um campo do class file
*   @param classe  Ponteiro do class file a ser utilizado
*   @param index   Índice da constant pool
*/
char* informacoes_metodo(u2 index, ClassFile *classe);

/**
*   @brief Função que retorna a string com informação do campo de referência de um campo do class file
*   @param classe  Ponteiro do class file a ser utilizado
*   @param index   Índice da constant pool
*/
char* informacoes_camporef(u2 index, ClassFile *classe);
