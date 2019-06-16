/*!
 * \file Methods.h
 * \brief Gerencia as informações dos metodos do arquivo .class
 */
#ifndef METHOD_H
#define METHOD_H

#include <fstream>
#include "ConstantPool.h"
#include "Attributes.h"
#include "BasicTypes.h"

using namespace std;

typedef struct {
	uint16_t access_flags;
	uint16_t name_index;
	uint16_t descriptor_index;
	uint16_t attributes_count;
	attribute_info *attributes;
} method_info;

/** @fn method_info lerMethod(FILE* arquivoEntrada, cp_info *constantPool)
 * Lê um método do arquivo .class
 *
 * @param *arquivoEntrada ponteiro para o arquivo .class
 * @param *constantPool ponteiro para as informações do pool de constantes
 */
method_info lerMethod(FILE* arquivoEntrada, cp_info *constantPool);

/** @fn method_info *lerTodosMethods(FILE* arquivoEntrada, int tamanho, cp_info *constantPool)
 * Lê os métodos do arquivo .class
 *
 * @param *arquivoEntrada ponteiro para o arquivo .class
 * @param tamanho quantidade de métodos presente
 * @param *constantPool ponteiro para as informações do pool de constantes
 */
method_info *lerTodosMethods(FILE* arquivoEntrada, int tamanho, cp_info *constantPool);

/** @fn void imprimirMethod(method_info method, cp_info *constantPool)
 * Mostra um método do arquivo .class
 *
 * @param method contém as informações do método
 * @param *constantPool ponteiro para as informações do pool de constantes
 */
void imprimirMethod(method_info method, cp_info *constantPool);

/** @fn imprimirTodosMethods(method_info *method, cp_info *constantPool, int tamanho)
 * Mostra todos os métodos do arquivo .class
 *
 * @param *method ponteiro para as informações do método
 * @param *constantPool ponteiro para as informações do pool de constantes
 * @param tamanho quantidade de métodos a serem mostrados
 */
void imprimirTodosMethods(method_info *method, cp_info *constantPool, int tamanho);

/** @fn gravarArquivoMethod(method_info method, cp_info *constantPool, int indice, fstream &arquivoSaida)
 * @brief Mostra um método do arquivo .class
 * @param method contém as informações do método
 * @param *constantPool ponteiro para as informações do pool de constantes
 * @param arquivoSaida arquivo de saida
 */
void gravarArquivoMethod(method_info method, cp_info *constantPool, int indice, fstream &arquivoSaida);

/** @fn gravarArquivoTodosMethods(method_info *method_info, cp_info *constantPool, int tamanho, fstream &arquivoSaida)
 * @brief Mostra todos os métodos do arquivo .class
 * @param *method ponteiro para as informações do método
 * @param *constantPool ponteiro para as informações do pool de constantes
 * @param tamanho quantidade de métodos a serem mostrados
 * @param arquivoSaida arquivo de saida
 */
void gravarArquivoTodosMethods(method_info *method_info, cp_info *constantPool, int tamanho, fstream &arquivoSaida);

/** @fn string obterFlagMethod(uint16_t flag)
 * Obtém as access flags dos métodos para print
 *
 * @param flag dos métodos dado method_info.access_flags
 *
 */
string obterFlagMethod(uint16_t flag);

#endif 
