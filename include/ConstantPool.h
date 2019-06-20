/** @file ConstantPool.h
 * @brief Módulo Constant pool
 * @details Este módulo contém as funções necessárias para a manipulação do pool de constantes.
 */

#ifndef CONSTANTPOOL_H
#define CONSTANTPOOL_H

#include <fstream>

#include "BasicTypes.h"

using namespace std;

/** @struct cp_info
 * @brief Possui um elemento pool de constante.
 */
typedef struct {
	U1 tag;
	ClassLoaderType *info;
} cp_info;

/// Formatos de dados no pool de constantes
const string nomeTiposDados[] = { "UTF-8", "-", "Integer", "Float", "Long", "Double", "Class", "String", "Field", "Method", "Interface",
		"Name and Type" };

#define INVALID 99 
#define UTF8 1
#define INTEGER 3
#define FLOAT 4
#define LONG 5
#define DOUBLE 6
#define CLASS 7
#define STRING 8
#define FIELD_REF 9
#define METHOD_REF 10
#define INTERFACE_REF 11
#define NAME_AND_TYPE 12

/** @fn int carregarConstantPool(cp_info *constantPool, int tamanho, FILE* arquivoEntrada)
 @brief Carrega o pool de constantes
 @param constantPool - um ponteiro para o pool de contantes
 @param tamanho - o tamanho do pool de constantes
 @param arquivoEntrada - ponteiro para o arquivo .class
 @section desc Descrição
 Função responsável por carregar o pool de constantes e todos os campos a ele relacionados
 @return o número de elementos do pool de constantes
 */
int carregarConstantPool(cp_info *constantPool, int tamanho, FILE* arquivoEntrada);

/** @fn string capturarIndiceDeReferencia (cp_info *constantPool, U2 indice)
 @brief Retorna os dados no índice.
 @param constantPool - um ponteiro para o pool de contantes
 @param indice - um índice para a posição no pool de constantes
 Função responsável por obter os dados correspondentes ao índice informado
 */
string capturarIndiceDeReferencia(cp_info *constantPool, U2 indice);

/** @fn void imprimirConstantPool(cp_info *constantPool, int tamanho)
 @brief Imprime o pool de constantes
 @param constantPool - um ponteiro para o pool de contantes
 @param tamanho - o tamanho do pool de constantes
 Função responsável por imprimir na tela o pool de constantes e todos os campos a ele relacionados
 */
void imprimirConstantPool(cp_info *constantPool, int tamanho);

/** @fn void gravarArquivoConstantPool(cp_info *constantPool, int tamanho, fstream &arquivoSaida)
 @brief Imprime o pool de constantes
 @param constantPool - um ponteiro para o pool de contantes
 @param tamanho - o tamanho do pool de constantes
 @param arquivoSaida - arquivo saida
 Função responsável por gravar no arquivo o pool de constantes e todos os campos a ele relacionados
 */
void gravarArquivoConstantPool(cp_info *constantPool, int tamanho, fstream &arquivoSaida);

#endif
