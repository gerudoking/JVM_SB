/** @file Attributes.h
 * @brief Atributos a serem usados na execuçao da JVM
 */

#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>

#include "ConstantPool.h"

using namespace std;

/** @class Attribute_info;
 *  @brief Protótipo da struct "attribute_info"
 */
struct Attribute_info;

/** @struct ConstantValue_attribute
 *	@brief Struct para carregar o index dos atributos da "constantpool"
 */
typedef struct {
	unsigned short constantvalue_index;
} ConstantValue_attribute;

/** @struct T_exception_table
 *	@brief Struct para salvar exceções identificadas. Será utilizada
 *	como componente da struct "code_attribute"
 */
struct T_exception_table {
	unsigned short start_pc;
	unsigned short end_pc;
	unsigned short handler_pc;
	unsigned short catch_type;
};

/** @struct Code_attribute
 *	@brief Estrutura de dados para salvar atributos do tipo code
 */
typedef struct {
	unsigned short max_stack;
	unsigned short max_locals;
	unsigned int code_length;
	unsigned char* codigo;
	unsigned short exception_table_length;
	T_exception_table** exception_table;
	unsigned short attribute_count;
	Attribute_info* attributes;
} Code_attribute;

/** @struct Exception_attribute
 *	@brief Estrutura de dados para salvar atributos de tipo "exception"
 */
typedef struct {
	unsigned short number_of_exceptions;
	unsigned short* exception_index_table;
} Exception_attribute;

/** @union T_info
 *	@brief Estrutura de dados que agrega informações sobre cada atributo lido
 */
typedef union {
	ConstantValue_attribute constantValue;
	Code_attribute codeAttribute;
	Exception_attribute exception;
} T_info;

/** @struct Attribute_info
 *	@brief Estrutura de dados para salvar a posição do atributo na constantpool e seu tamanho
 */
struct Attribute_info {
	unsigned short name_index;
	unsigned int length;

	T_info* info;
};

/** @fn t_exception_table* lerExceptionHandler(FILE* arquivoEntrada)
 *	@brief Função de leitura de exceções
 *	@param arquivoEntrada Ponteiro para arquivo tipo .class
 */
T_exception_table* lerExceptionHandler(FILE* arquivoEntrada);

/** @fn t_info* lerAttributeInfo(FILE* arquivoEntrada, cp_info* constantPool, unsigned short indice, unsigned short tamanho)
 *	@brief Faz a leitura das informações de um atributo
 *	@param arquivoEntrada Ponteirp para arquivo .class.
 *	@param constantPool Ponteiro pra constantpool.
 *	@param indice Posição do atributo na constantpool.
 *	@param tamanho em bytes do atributo a ser lido.
 */
T_info* lerAttributeInfo(FILE* arquivoEntrada, Cp_info* constantPool, unsigned short indice, unsigned short tamanho);

/** @fn attribute_info lerAttribute(FILE* arquivoEntrada, cp_info *constantPool)
 *	@brief Faz a leitura de um atributo da constantpool.
 *	@param arquivoEntrada Ponteiro pro arquivo .class.
 *	@param constantPool Pointeiro pra constantpool.
 */
Attribute_info lerAttribute(FILE* arquivoEntrada, Cp_info *constantPool);

/** @fn attribute_info* lerTodosAttributes(FILE* arquivoEntrada, cp_info *constantPool, int tamanho)
 *	@brief Faz a leitura de n atributos da constantpool
 *	@param arquivoEntrada Ponteiro pro arquivo .class.
 *	@param constantPool Poteiro pra constant pool.
 *	@param tamanho Número de atributos.
 */
Attribute_info* lerTodosAttributes(FILE* arquivoEntrada, Cp_info *constantPool, int tamanho);

/** @fn void imprimirAttribute(attribute_info attribute, cp_info *constantPool)
 *	@brief Função que imprime na tela informações de um atributo.
 *	@param attribute do struct do attribute_info.
 *	@param constantPool Poteiro pra constant pool.
 */
void imprimirAttribute(Attribute_info attribute, Cp_info *constantPool);

/** @fn void imprimirTodosAttributes(attribute_info* attribute, cp_info* constantPool, int tamanho)
 *	@brief Função que imprime na tela informações de n atributos
 *	@param attribute Pointer to struct of types att.
 *	@param constantPool Poteiro pra constant pool.
 *	@param tamanho Number of times of the function printAttribute gonna be called.
 */
void imprimirTodosAttributes(Attribute_info* attribute, Cp_info* constantPool, int tamanho);

/** @fn void gravarArquivoTodosAttributes(attribute_info* attribute, cp_info* constantPool, int tamanho, fstream &arquivoSaida)
 *	@brief Função que imprime na tela informações de n atributos
 *	@param attribute Pointer to struct of types att.
 *	@param constantPool Poteiro pra constant pool.
 *	@param tamanho Number of times of the function printAttribute gonna be called.
 *	@param arquivoSaida arquivo de saída
 */
void gravarArquivoTodosAttributes(Attribute_info* attribute, Cp_info* constantPool, int tamanho, fstream &arquivoSaida);

/** @fn void gravarArquivoAttribute(attribute_info attribute, cp_info *constantPool, fstream &arquivoSaida)
 *	@brief Função que imprime na tela informações de um atributo.
 *	@param attribute do struct do attribute_info.
 *	@param constantPool Poteiro pra constant pool.
 *	@param arquivoSaida arquivo de saída
 */
void gravarArquivoAttribute(Attribute_info attribute, Cp_info *constantPool, fstream &arquivoSaida);

/** @fn string obterMnemonico(int opcode)
 *	@brief Retorna o nome da operação.
 *	@param opcode Opcode de operações da JVM
 */
string obterMnemonico(int opcode);

/** @fn void obterParametrosOpcode(unsigned char* codigo, int* indice)
 *	@brief Função que mostra na tela os parâmetros dos opcodes
 *	@param codigo Pointer of bytes wich are code and your arg. Ponteiro para vetor de bytes do código e seus parâemtros.
 *	@param indice Posição na constantpool.
 */
void obterParametrosOpcode(unsigned char* codigo, int* indice);

/** @fn void gravaArquivoObterParametrosOpcode(unsigned char* codigo, int* indice, fstream & arquivoSaida)
 *	@brief Função que mostra na tela os parâmetros dos opcodes
 *	@param codigo Pointer of bytes wich are code and your arg. Ponteiro para vetor de bytes do código e seus parâemtros.
 *	@param indice Posição na constantpool.
 *	@param arquivoSaida arquivo de saída
 */
void gravaArquivoObterParametrosOpcode(unsigned char* codigo, int* indice, fstream & arquivoSaida);

/** @fn uint32_t obterValorNBytes(uint8_t numero, unsigned char* codigo, int* indice)
 *	@brief Função para retornar o conteúdo dos próximos n bytes
 *	@param numero Número de bytes a serem lidos.
 *	@param codigo Ponteiro pra um vetor de bytes.
 *	@param indice Posição do opcode no vetor.
 */
uint32_t obterValorNBytes(uint8_t numero, unsigned char* codigo, int* indice);

#endif
