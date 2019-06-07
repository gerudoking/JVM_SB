/*!
 * \file classeTiposBasicos.h
 * \brief Tipos básicos utilizados para implementarmos a JVM.
 */

/** @def BASE
 *	@brief Macro
 *	@brief Define utilizado para evitar múltiplas inclusões desse arquivo.
 */
#ifndef BASE
#define BASE

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <iostream>
#include <math.h>
#include <sstream>
#include <vector>
#include <stdexcept>

using namespace std;

#define Float_NaN 0x7f800001
#define Float_PlusInfinity 0x7f800000
#define Float_MinusInfinity 0xff800000
#define Double_NaN 0x7ff0000000000001L 
#define Double_PlusInfinity 0x7ff0000000000000L
#define Double_MinusInfinity 0xfff0000000000000L

#define RT_BYTE 1
#define RT_BOOL 2
#define RT_CHAR 3
#define RT_SHORT 4
#define RT_INT 5
#define RT_FLOAT 6
#define RT_DOUBLE 7
#define RT_REFERENCE 8
#define RT_LONG 9

typedef uint8_t U1;
typedef uint16_t U2;
typedef uint32_t U4;

/** @union ClassLoaderType
 *	@brief Estrutura de dados para armazenamento
 *	Union responsável por armazenar todos os tamanhos de variáveis utilzadas na JVM
 */

typedef union {
	U1 *array; //ponteiro para uma string
	U1 u1; //8 bytes
	U2 u2; //16 bytes
	U4 u4; //32 bytes
} ClassLoaderType;

/** @union element
 *	@brief Generalização de funções de retorno/input
 *	Union responsável pela generalização de funções de retorno e uma função de input.
 */
typedef union element_u {
	double d;
	float f;
	uint32_t i;
	int32_t is;
	uint64_t l;
	int64_t ls;
	uint16_t s;
	int16_t ss;
	uint8_t b;
	int8_t bs;
	int* pi;
} element;

typedef struct {
	int* dims;
	int* array;
} n_array;

/** @struct typedElement_s
 *	@brief Agregador de tipos e informações.
 *	Struct responsável por juntar tipos e informações de elementos.
 */
typedef struct typedElement_s {
	element value;
	uint8_t type;
	uint8_t realType;
} TypedElement;

/** @fn U1 lerU1 (FILE *fp)
 *	@brief Função para ler 1 byte do arquivo .class
 *	@param fp. Ponteiro pro arquivo .class
 */
U1 lerU1(FILE *fp);

/** @fn U2 lerU2 (FILE *fp)
 *	@brief Função para ler 2 bytes do arquivo .class
 *	@param fp. Ponteiro pro arquivo .class
 */
U2 lerU2(FILE *fp);

/** @fn U4 lerU4 (FILE *fp)
 *	@brief Função para ler 4 bytes do arquivo .class
 *	@param fp. Ponteiro pro arquivo .class
 */
U4 lerU4(FILE *fp);

/** @fn U1 * lerUTF8(FILE* fp, int size)
 *	@brief Função para ler os bytes de uma string UTF-8
 *	@param fp. Ponteiro pro arquivo .class
 *	@param size Tamanho que será alocado para a string.
 */
U1 * lerUTF8(FILE* fp, int size);

/** @fn string imprimirUTF8 (unsigned char * s, int size)
 *	@brief Função para montar e mostrar a uma string UTF-8
 *	@param s Ponteiro para a posição inicial de uam string Unicode.
 *	@param size Tamanho da string a ser impressa.
 */
string obterUTF8(unsigned char * s, int size);

/** @fn int verificarFloat(float)
 *	@brief Função para verificar NaN e infinito
 *	@param f Número a ser verificado.
 */
int verificarFloat(float f);

/** @fn int verificarDouble(double)
 *	@brief Função para verificar NaN e infinito
 *	@param d Number to be checked.
 */
int verificarDouble(double d);

/** @fn string converter_float_to_string(float)
 *	@brief Função para converter float para string
 *	@param f Número a ser convertido.
 */
string converter_float_to_string(float f);

/** @fn string converter_double_to_string(double)
 *	@brief Função para converter double para string
 *	@param d Número a ser convertido.
 */
string converter_double_to_string(double d);

/** @fn float converter_u4_to_float (ClassLoaderType in)
 *  @brief Função para converter 4 bytes em float
 *  @param in quatro bytes a serem convertidos.
 */
float converter_u4_to_float(ClassLoaderType in);

/** @fn long converter_u4_to_long (ClassLoaderType high, ClassLoaderType low)
 *  @brief Função para converter 8 bytes em um longo
 *  @param high Quatro bytes mais significativos a serem convertidos.
 *  @param low Quatro últimos bytes significativos a serem convertidos.
 */
long converter_u4_to_long(ClassLoaderType high, ClassLoaderType low);

/** @fn double converter_u4_to_double (ClassLoaderType high, ClassLoaderType low)
 *  @brief Função para converter 8 bytes em um duplo
 *  @param high Quatro bytes mais significativos a serem convertidos.
 *  @param low Quatro últimos bytes significativos a serem convertidos.
 */
double converter_u4_to_double(ClassLoaderType high, ClassLoaderType low);

#endif
