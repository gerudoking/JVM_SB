/*!
 * \file StaticClass.h
 * \brief Definição da StaticClass
 */
#ifndef STATICCLASS_H
#define STATICCLASS_H

class StaticClass;

#include "ClasseLeitorExibidor.h"
#include "OperandsStack.h"
#include "InstanceClass.h"
#include "Heap.h"
#include <map>

using namespace std;

/** @class StaticClass
 * @brief Fields Estáticos compartilhados por todas as instâncias.
 * @brief Define operações que manipulam classes estáticas
 */
class StaticClass {
private:
	map<string, TypedElement*> mapStaticFields;
	LeitorExibidor *leitorExibidor;

public:
	/** @fn StaticClass(LeitorExibidor *leitorExibidor)
	 * @brief Construtor da StaticClass
	 * @param leitorExibidor informação do class file já carregada na memória
	 */
	StaticClass(LeitorExibidor *leitorExibidor);

	/** @fn TypedElement obterField(string field)
	 * @brief Retorna as informações de um field
	 * @param field nome do field desejado
	 * @return struct typedElement que contém informações sobre nome do tipo e valor
	 */
	TypedElement obterField(string field);

	/** @fn bool atualizarField(string field, TypedElement typedElement)
	 * @brief Coloca um novo valor pra um field
	 * @param field nome do field desejado
	 * @param typedElement tipo para o field
	 * @return booleano que indica se o field foi setado com o novo tipo ou não
	 */
	bool atualizarField(string field, TypedElement typedElement);

	/** @fn bool atualizarFieldFinals(string field, TypedElement typedElement)
	 * @brief Marca Field como final
	 * @param field nome do field desejado
	 * @param typedElement tipo para o field
	 * @return booleano que indica se o field foi setado com o novo tipo ou não
	 */
	bool atualizarFieldFinals(string field, TypedElement typedElement);

	/** @fn Leitor *obterClasseLeitorExibidor()
	 * @brief Retorna as informações do class file.
	 * @return ponteiro para a instancia de ClasseLeitor que contém as informações salvas na memória
	 */
	LeitorExibidor *obterClasseLeitorExibidor();

	/** @fn Instance *obterInstanceClass()
	 @brief Retorna a instância da classe
	 */
	InstanceClass *obterInstanceClass();
};

#endif
