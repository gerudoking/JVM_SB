/*!
 * \file fields.h
 * \brief Gerencia as informações dos campos do arquivo .class
 */

/**
 * @def FIELDS
 * @brief Define uso para evitar a inclusão múltipla de arquivos.
 */
#ifndef FIELDS
#define FIELDS

#include <fstream>
#include "constantPool.h"
#include "attributes.h"
#include "classeTiposBasicos.h"

using namespace std;

/** @struct field_info
 * @brief Struct responsável por armazenar os campos declarados.
 */
typedef struct {
	unsigned char accessFlags;
	unsigned char name_index;
	unsigned char descriptor_index;
	unsigned char attributes_count;
	attribute_info *attributes;
} field_info;

/**
 * @fn imprimirField(field_info field, Cp_info *constantPool, int indice);
 * @brief Função que imprime um campo.
 * @param field Struct com informações do campo.
 * @param constantPool Ponteiro para pool de constantes.
 * @param indice Índice do vetor que contém um campo.
 */
void imprimirField(field_info field, cp_info *constantPool, int indice);

/**
 * @fn void imprimirTodosField(field_info *field, Cp_info *constantPool, int tamanho)
 * @brief Função que chama printField o número de vezes determinado por "length"
 * @param field Struct que contém informação dos campos.
 * @param constantPool Ponteiro para pool de constantes.
 * @param tamanho Define o número de chamadas à printField.
 */
void imprimirTodosField(field_info *field, cp_info *constantPool, int tamanho);

/**
 * @fn gravarArquivoField(field_info field, Cp_info *constantPool, int indice, fstream &arquivoSaida)
 * @brief Função que imprime um campo.
 * @param field Struct com informações do campo.
 * @param constantPool Ponteiro para pool de constantes.
 * @param indice Índice do vetor que contém um campo.
 * @param arquivoSaida arquivo de saida
 */
void gravarArquivoField(field_info field, cp_info *constantPool, int indice, fstream &arquivoSaida);

/**
 * @fn void gravarArquivoTodosField(field_info *field, cp_info *constantPool, int tamanho, fstream &arquivoSaida)
 * @brief Função que chama printField o número de vezes determinado por "length"
 * @param field Struct que contém informação dos campos.
 * @param constantPool Ponteiro para pool de constantes.
 * @param tamanho Define o número de chamadas à printField.
 * @param arquivoSaida arquivo de saida
 */
void gravarArquivoTodosField(field_info *field, cp_info *constantPool, int tamanho, fstream &arquivoSaida);

/**
 * @fn field_info readField (FILE* fp, cp_info *cp)
 * @brief Função que lê um campo
 * @param arquivoEntrada Ponteiro para arquivo .class.
 * @param constantPool Ponteiro para pool de constantes.
 */
field_info lerField(FILE* arquivoEntrada, cp_info* constantPool);

/**
 * @fn field_info lerField(FILE* arquivoEntrada, Cp_info* constantPool);
 * @brief Função que aloca field_info espaço e chama readField "lenght" vezes
 * @param arquivoEntrada Ponteiro para arquivo .class.
 * @param tamanho Define o número de chamadas à readField.
 * @param constantPool Ponteiro para pool de constantes.
 */
field_info *lerTodosFields(FILE* arquivoEntrada, int tamanho, cp_info* constantPool);

/**
 * @fn string obterFlagField(unsigned short flag);
 * @brief Função para mostrar as flags dos campos
 * @param flag Flags em haxadecimal que serão convertidas para string.
 */
string obterFlagField(unsigned short flag);

#endif
