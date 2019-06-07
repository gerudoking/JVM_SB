/*!
 * \file classeInstancia.h
 * \brief Definição da ClasseInstancia
 */
#ifndef CLASSE_INSTANCIA
#define CLASSE_INSTANCIA

class ClasseInstancia;

#include "classeLeitorExibidor.h"
#include "classeEstatica.h"
#include "classePilhaOperandos.h"
#include "classeHeap.h"
#include <map>

using namespace std;

/** @class ClasseInstancia
 * @brief Class instantiation.
 * @brief Lida com operações que lidam com uma instância da classe
 */
class ClasseInstancia {
private:
	map<string, TypedElement*> mapLocalFields;
	ClasseEstatica *classeEstatica;

public:
	/** @fn ClasseInstancia(ClasseEstatica* c)
	 * @brief Lida com operações que manipulam a instância da classe
	 * @param classeEstatica Referência para a ClasseEstatica
	 */
	ClasseInstancia(ClasseEstatica *classeEstatica);

	/** @fn ClasseEstatica *getStatic()
	 * @brief Retorna referência para a classe estatica.
	 */
	ClasseEstatica *obterclasseEstatica();

	/** @fn typedElement getField(string field)
	 * @brief Retorna field instanciado
	 * @param field do field.
	 * @return struct typedElement que contém informações sobre nome do tipo e valor
	 */
	TypedElement obterField(string field);

	/** @fn bool setField(string s, typedElement e)
	 * @brief Defina um valor para um field da ClasseInstancia
	 * @param field nome do field
	 * @param typedElement novo tipo que será atribuido ao field
	 * @return booleano indicado se o field foi definido
	 */
	bool atualizarField(string field, TypedElement typedElement);

	/** @fn bool atualizarFieldFinals(string field, TypedElement typedElement)
	 * @brief Define Field como final
	 * @param field nome do field desejado
	 * @param typedElement tipo para o field
	 * @return booleano que indica se o field foi setado com o novo tipo ou não
	 */
	bool atualizarFieldFinals(string field, TypedElement typedElement);

	/** @fn void imprimirClasseInstancia()
	 * @brief Mostra todas as classes instanciadas
	 */
	void imprimirClasseInstancia();

};

#endif
