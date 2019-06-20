/*!
 * \file OperandsStack.h
 * \brief Pilha responsável por armazenar os operandos da JVM
 */

#ifndef OPERANDSSTACK_H
#define OPERANDSSTACK_H

#include <stack>
#include <cstdint>
#include <string>
#include <sstream>
#include <stdbool.h>

#include "BasicTypes.h"

#define INVALID 99
#define TYPE_NOT_SET 0
#define TYPE_INT 1
#define TYPE_FLOAT 2
#define TYPE_LONG 3
#define TYPE_DOUBLE 4
#define TYPE_BOOL 5
#define TYPE_REFERENCE 6

using namespace std;

/** @class OperandsStack
 @brief Classe da pilha de operandos

 Responsável por armazenar e manipular a pilha de operandos
 */
class OperandsStack {
private:
	//pilha para os valores armazenados
	stack<uint32_t> stackElementos;

	//pilha para o tipo dos valores armazenados
	stack<uint8_t> stackTipos;

	//pilha para o tipo dos valores armazenados
	stack<uint8_t> stackTiposReais;

	bool typePushed;

	//variavel para determinar se o sistema tem 64 bits
	static const bool bits64 = (sizeof(int*) == 8);

	//variavel para determinar tamanho m�ximo da pilha
	const int realMax;
public:
	/** @fn OperandsStack(int maxSize)
	 @brief Construtor
	 @param maxSize Indica tamanho m�ximo da pilha de operandos
	 */
	OperandsStack(int);

	/** @fn uint8_t desempilhaTopoTipo()
	 @brief Recupera o tipo do topo da pilha de operandos
	 */
	uint8_t desempilhaTopoTipo();

	/** @fn element desempilhaTopoValor()
	 @brief Recupera o valor do topo da pilha de operandos
	 */
	Element desempilhaTopoValor();

	/** @fn element desempilha()
	 @brief Desempilha o topo da pilha de operandos e retorna em um elemento de valor
	 */
	Element desempilha();

	/** @fn element desempilhaTyped()
	 @brief Desempilha o topo da pilha de operandos e retorna em um elemento tipado
	 */
	TypedElement desempilhaTyped();

	/** @fn string obterString()
	 @brief Retorna o topo da pilha de operandos formatado em uma string
	 */
	string obterString();

	/** @fn void empilharInt(int x)
	 @brief Empilha um valor de tipo inteiro
	 @param x Valor a ser empilhado
	 */
	void empilharInt(int x);

	/** @fn void empilharLong(int64_t x)
	 @brief Empilha um valor de tipo long
	 @param x Valor a ser empilhado
	 */
	void empilharLong(int64_t x);

	/** @fn void empilharFloat(float x)
	 @brief Empilha um valor de tipo float

	 @param x Valor a ser empilhado
	 */
	void empilharFloat(float x);

	/** @fn void empilharDouble(double x)
	 @brief Empilha um valor de tipo double

	 @param x Valor a ser empilhado
	 */
	void empilharDouble(double x);

	/** @fn void empilharBool(bool x)
	 @brief Empilha um valor de tipo bool

	 @param x Valor a ser empilhado
	 */
	void empilharBool(bool x);

	/** @fn void empilharReferencia(int *x)
	 @brief Empilha um valor de tipo referencia

	 @param x Referencia a ser empilhada
	 */
	void empilharReferencia(int *x);

	/** @fn void empilharTypedElement(TypedElement typedElement)
	 @brief Empilha um elemento tipado, chamando a função adequada ao tipo

	 @param typedElement Elemento tipado a ser empilhado
	 */
	void empilharTypedElement(TypedElement typedElement);

	/** @fn void empilhar(Element, uint8_t)
	 @brief Verifica o tipo do elemento que deve ser empilhado e chama a função adequada

	 @param element Elemento a ser empilhado
	 @param tipo Tipo do elemento a ser empilhado
	 */
	void empilhar(Element, uint8_t);

	/** @fn int obterTamanho()
	 @brief retorna o tamanho da pilha de operandos
	 */
	int obterTamanho();

	/** @fn int obterTamanhoMaximoPilha()
	 @brief Retorna o tamanho máximo da pilha de operandos
	 */
	int obterTamanhoMaximoPilha();

	/** @fn bool estaVazia()
	 @brief Retorna se a pilha está vazia (1) ou não (0)
	 */
	bool estaVazia();

	/** @fn void imprimirTodasOperacoes()
	 @brief imprimir Todas as Operacoes
	 */
	void imprimirTodasOperacoes();
	const int max;
};

#endif
