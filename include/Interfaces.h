/*!
 * \file Interfaces.h
 * \brief Gerencia as informações da interfaces do arquivo .class
 */

#ifndef INTERFACES_H
#define INTERFACES_H

#include <iostream>
#include "BasicTypes.h"
#include "ConstantPool.h"

/**
 * @fn unsigned short *lerTodasInterfaces(FILE* arquivoEntrada, int tamanho)
 * @brief Carrega as interfaces na mem�ria a partir do arquivo class.
 * @param arquivoEntrada Ponteiro para o arquivo class.
 * @param tamanho Número de interfaces a serem lidas.
 */
unsigned short *lerTodasInterfaces(FILE* arquivoEntrada, int tamanho);

/**
 * @fn void imprimirTodasInterfaces(unsigned short *interface, Cp_info *constantPool, int tamanho)
 * @brief Imprimir todas as interfaces do arquivo.
 * @param interface Array de interfaces.
 * @param constantPool Ponteiro para a constantpool.
 * @param tamanho Número de interfaces.
 */
void imprimirTodasInterfaces(unsigned short *interface, Cp_info *constantPool, int tamanho);

/**
 * @fn imprimirInterface(unsigned short interface, Cp_info *constantPool, int indice)
 * @brief Imprimir informação de uma interface específica com o indice da interface.
 * @param interface Indice do constantpool.
 * @param constantPool Ponteiro para o constantpool.
 * @param indice Indice da interface específica.
 */
void imprimirInterface(unsigned short interface, Cp_info *constantPool, int indice);

/**
 * @fn void gravarArquivoTodasInterfaces(unsigned short *interface, cp_info *constantPool, int tamanho, fstream &arquivoSaida)
 * @brief Imprimir todas as interfaces do arquivo.
 * @param interface Array de interfaces.
 * @param constantPool Ponteiro para a constantpool.
 * @param tamanho Número de interfaces.
 * @param arquivoSaida arquivo de saida
 */
void gravarArquivoTodasInterfaces(unsigned short *interface, Cp_info *constantPool, int tamanho, fstream &arquivoSaida);

/**
 * @fn void gravarArquivoInterface(unsigned short interface, cp_info *constantPool, int indice, fstream &arquivoSaida)
 * @brief Imprimir informação de uma interface específica com o indice da interface.
 * @param interface Indice do constantpool.
 * @param constantPool Ponteiro para o constantpool.
 * @param indice Indice da interface específica.
 * @param arquivoSaida arquivo de saida
 */
void gravarArquivoInterface(unsigned short interface, Cp_info *constantPool, int indice, fstream &arquivoSaida);

#endif
