/*!
 * \file LocalVariables.h
 * \brief Stores local variables to current method
 */

/*! \def LOCALVARIABLES
 \brief Macro

 Define used to avoid multiple inclusions of this file
 */

#ifndef LOCALVARIABLES_H
#define LOCALVARIABLES_H

#include <cstdint>
#include <stack>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include "BasicTypes.h"

using namespace std;

//to test if addresses are 32 or 64 bits
#define BITS (sizeof(int*) == 8)

#define INVALID 99
#define TYPE_NOT_SET 0
#define TYPE_INT 1
#define TYPE_FLOAT 2
#define TYPE_LONG 3
#define TYPE_DOUBLE 4
#define TYPE_BOOL 5
#define TYPE_REFERENCE 6

/*! \class VariaveisLocais
 \brief classe VariaveisLocais

 Responsible for all operations that envolves the local variables
 */
class VariaveisLocais {
private:
	//array to values
	uint32_t *elements;
	//array to types
	uint8_t *types;
	//maximum slots quantity 
	const uint16_t max;
	const uint16_t realMax;
	//says if types occupy 2 slots (used to simulate arrays)
	const bool dois;
public:
	/*! \fn VariaveisLocais(uint16_t maxSize)
	 \brief VariaveisLocais class constructor

	 \param maxSize Maximum size of local variables that can be stored
	 */
	VariaveisLocais(uint16_t);

	/*! \fn VariaveisLocais(uint16_t maxSize)
	 \brief VariaveisLocais class constructor

	 \param maxSize Maximum site of local variables that can be stored
	 \param slots Says if needs to be used two slots for all elements
	 */
	VariaveisLocais(uint16_t, bool);
	/*! \fn ~VariaveisLocais()
	 \brief Destructor 4
	 */
	~VariaveisLocais();

	/*! \fn void imprimirAll() const
	 \brief Function to show all values
	 */
	void imprimirAll() const;

	/*! \fn void set(int index, typedElement x)
	 \brief Receives the typed element and inserts on past index
	 \param index Says the index that will be inserted the past element
	 \param x Typed element that will be inserted on indicated index
	 */
	void set(int, TypedElement);

	/*! \fn typedElement get(int index) const
	 \brief Gets element on past position by index
	 \param index Indicates the index that will be obtained the element
	 */
	TypedElement get(int) const;

	/*! \fn int obterMax() const
	 \brief Function to know maximum size
	 */
	int obterMax() const;

	//function to allow class use like a struct's array
	/*! \fn const typedElement operator[] (const int index) const
	 \brief Function to allow class use like a struct's array
	 \param index Indicates the index that must be accessed to obtain the typed element
	 */
	const TypedElement operator[](const int) const;

};

#endif
