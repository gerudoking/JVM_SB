/*!
 * \file classeEstatica.h
 * \brief Definição da ClasseEstatica
 */
#ifndef CLASSE_ESTATICA
#define CLASSE_ESTATICA

class ClasseEstatica;

#include "classeLeitorExibidor.h"
#include "classePilhaOperandos.h"
#include "classeInstancia.h"
#include "classeHeap.h"
#include <map>

using namespace std;

/** @class ClasseEstatica
 * @brief Fields Estáticos compartilhados por todas as instâncias.
 * @brief Define operações que manipulam classes estáticas
 */
class ClasseEstatica {
private:
	map<string, TypedElement*> mapStaticFields;
	LeitorExibidor *leitorExibidor;

public:
	/** @fn ClasseEstatica(LeitorExibidor *leitorExibidor)
	 * @brief Construtor da ClasseEstatica
	 * @param Leitor informação do class file já carregada na memória
	 */
	ClasseEstatica(LeitorExibidor *leitorExibidor);

	/** @fn TypedElement obterField(string field)
	 * @brief Retorna as informações de um field
	 * @param field nome do field desejado
	 * @return struct typedElement que contém informações sobre nome do tipo e valor
	 */
	TypedElement obterField(string field);

	/** @fn bool setField(string s, typedElement e)
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

	/** @fn ClasseInstancia *getInstance()
	 @brief Retorna a instância da classe
	 */
	ClasseInstancia *obterInstanceClasseInstancia();
};

#endif
