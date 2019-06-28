/*!
 * \file Methods.h
 * \brief Gerencia as informações dos metodos do arquivo .class
 */
#ifndef METHOD_H
#define METHOD_H

#include <fstream>

#include "Attributes.h"
#include "BasicTypes.h"
#include "ConstantPool.h"

using namespace std;

/** @struct Method_info
 * @brief Struct responsável por armazenar os metodos declarados.
 */
typedef struct {
	uint16_t access_flags;
	uint16_t name_index;
	uint16_t descriptor_index;
	uint16_t attributes_count;
	Attribute_info *attributes;
} Method_info;

/** @fn method_info lerMethod(FILE* arquivoEntrada, cp_info *constantPool)
 * Lê um método do arquivo .class
 *
 * @param *arquivoEntrada ponteiro para o arquivo .class
 * @param *constantPool ponteiro para as informações do pool de constantes
 */
Method_info lerMethod(FILE* arquivoEntrada, Cp_info *constantPool);

/** @fn method_info *lerTodosMethods(FILE* arquivoEntrada, int tamanho, cp_info *constantPool)
 * Lê os métodos do arquivo .class
 *
 * @param *arquivoEntrada ponteiro para o arquivo .class
 * @param tamanho quantidade de métodos presente
 * @param *constantPool ponteiro para as informações do pool de constantes
 */
Method_info *lerTodosMethods(FILE* arquivoEntrada, int tamanho, Cp_info *constantPool);

/** @fn void imprimirMethod(method_info method, cp_info *constantPool)
 * Mostra um método do arquivo .class
 *
 * @param method contém as informações do método
 * @param *constantPool ponteiro para as informações do pool de constantes
 */
void imprimirMethod(Method_info method, Cp_info *constantPool);

/** @fn imprimirTodosMethods(method_info *method, cp_info *constantPool, int tamanho)
 * Mostra todos os métodos do arquivo .class
 *
 * @param *method ponteiro para as informações do método
 * @param *constantPool ponteiro para as informações do pool de constantes
 * @param tamanho quantidade de métodos a serem mostrados
 */
void imprimirTodosMethods(Method_info *method, Cp_info *constantPool, int tamanho);

/** @fn gravarArquivoMethod(method_info method, cp_info *constantPool, int indice, fstream &arquivoSaida)
 * @brief Mostra um método do arquivo .class
 * @param method contém as informações do método
 * @param *constantPool ponteiro para as informações do pool de constantes
 * @param indice indice para o method
 * @param arquivoSaida arquivo de saida
 */
void gravarArquivoMethod(Method_info method, Cp_info *constantPool, int indice, fstream &arquivoSaida);

/** @fn gravarArquivoTodosMethods(method_info *method, cp_info *constantPool, int tamanho, fstream &arquivoSaida)
 * @brief Mostra todos os métodos do arquivo .class
 * @param *method ponteiro para as informações do método
 * @param *constantPool ponteiro para as informações do pool de constantes
 * @param tamanho quantidade de métodos a serem mostrados
 * @param arquivoSaida arquivo de saida
 */
void gravarArquivoTodosMethods(Method_info *method, Cp_info *constantPool, int tamanho, fstream &arquivoSaida);

/** @fn string obterFlagMethod(uint16_t flag)
 * Obtém as access flags dos métodos para print
 *
 * @param flag dos métodos dado method_info.access_flags
 *
 */
string obterFlagMethod(uint16_t flag);

#endif 
