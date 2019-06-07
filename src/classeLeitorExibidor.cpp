/*!
 * \file classeLeitorExibidor.cpp
 * \brief Classe que irá realizar a leitura do bytecode e salvar as informações do class file
 */

#include "classeLeitorExibidor.h"

/**
 * Construtor que configura um objeto da classe Leitor com o nome do arquivo passado.
 *
 * @param in argumento passado como nome do arquivo na inicializacao do programa
 */
LeitorExibidor::LeitorExibidor(char *in) { // @suppress("Class members should be properly initialized")
	if (in) {	//associa o nome do arquivo passado a variavel filename
		fileName = in;
	}
	status = -1;
}

/**
 * Construtor que configura um objeto da classe Leitor com o nome do arquivo passado.
 *
 * @param in argumento passado como nome do arquivo na inicializacao do programa
 */
LeitorExibidor::LeitorExibidor(std::string in) { // @suppress("Class members should be properly initialized")
	//verifica se o arquivo passado é vazio
	if (!in.empty()) {
		//copia para fileName o nome do arquivo lido
		fileName = new char[in.size() + 1];
		std::copy(in.begin(), in.end(), fileName);
		fileName[in.size()] = 0;
	}
	status = -1;
}

/* Função que vai abrir o arquivo dado */
int LeitorExibidor::inicializarArquivo(char *argv[]) {
	string str(argv[2]);
	string extensao = str.substr(0, str.length() - 6);

	arquivoSaida.open(extensao.append(".txt").c_str(), ios::in | ios::out | ios::trunc);

	if (arquivoSaida.is_open()) {
		return (status = 0);
	} else {
		cout << "Não foi possivel abrir arquivo" << endl;
	}
	return status = -1;
}

void LeitorExibidor::fecharArquivo() {
	arquivoSaida.close();
}

/** @fn validacao(void)
 * @brief Valida estrutura obrigatoria */
int LeitorExibidor::validacao(void) {
	//**verifica se o arquivo possui a extensao .class
	if (!validarExtensao()) {
		cout << obterErro(INVALID_EXTENSION) << endl;
		status = INVALID_EXTENSION;
	}

	//**verifica se o nome do arquivo bate com o nome da class definida no bytecode
	if (!verificarThisClass()) {
		cout << obterErro(INVALID_NAME) << endl;
		status = INVALID_NAME;
	}

	//**verifica se o metodo main esta entre os metodos lidos no bytecode
	if(!verificarMain()){
		cout << obterErro(MISSING_MAIN) << endl;
		status = MISSING_MAIN;
	}

	return (status = 0);

}

/** @fn carregar()
 * Carrega o class file na classe
 * @return variavel status que indica se houve erro no programa
 */
int LeitorExibidor::carregar() {
	int verificarCP;

	//verifica se o arquivo passado existe
	if (!fileName) {
		//imprime "Argumento passado invalido!"
		printf("%s\n", obterErro(MISSING_ARGUMENT).c_str());
		return (status = MISSING_ARGUMENT);
	}

	//**verifica se o arquivo possui a extensao .class
	if (!validarExtensao()) {
		// imprime "ERRO: O arquivo deve ter a extensao .class!\n"
		printf("%s\n", obterErro(INVALID_EXTENSION).c_str());
		return (status = INVALID_EXTENSION);
	}

	//abre o arquivo para leitura
	arquivoClass = fopen(fileName, "rb");

	//verifica se o arquivo conseguiu ser aberto para leitura
	if (arquivoClass == NULL) {
		//imprime "ERRO: nao foi possivel abrir o arquivo ..."
		printf("%s\n", obterErro(CANT_OPEN).c_str());
		return (status = CANT_OPEN);
	}

	//verifica se o arquivo comeca com o magic number
	if (lerU4(arquivoClass) != 0xcafebabe) //le 32 bits
			{
		//se nao possui 0xcafebabe o arquivo é invalido
		printf("%s\n", obterErro(INVALID_FILE).c_str());
		return (status = INVALID_FILE);
	}

	//armazena o minor version
	minVersion = lerU2(arquivoClass);

	//armazena major version
	majVersion = lerU2(arquivoClass);

	//le o numero de constantes na constant pool
	lengthCP = lerU2(arquivoClass);

	//carrega a ConstantPool na memoria chamando o metodo que se encontra na classe da constantPool
	constantPool = (cp_info *) malloc(sizeof(cp_info) * lengthCP);
	verificarCP = carregarConstantPool(constantPool, lengthCP, arquivoClass);

	//verifica se todos os elementos foram lidos
	if (verificarCP != lengthCP) {
		//se todos n tiverem sido lidos entao alguma constante tem um tipo nao conhecido
		cerr << obterErro(UNKNOWN_TYPE);
		return (status = UNKNOWN_TYPE);
	}

	//le as Flags de acesso
	accessFlags = lerU2(arquivoClass);

	//le a classe definida pelo arquivo
	this_class = lerU2(arquivoClass);

	//**verifica se o nome do arquivo bate com o nome da class definida no bytecode
	if (!verificarThisClass()) {
		cerr << obterErro(INVALID_NAME);
		return (status = INVALID_NAME);
	}

	//armazena informacao sobre a superclass
	super_class = lerU2(arquivoClass);

	//le o numero de interfaces
	interfacesCount = lerU2(arquivoClass);

	//carrega as interfaces
	interfaces = lerTodasInterfaces(arquivoClass, interfacesCount);

	//le o numero de fields
	fieldsCount = lerU2(arquivoClass);

	//carrega os fields na memoria
	fields = lerTodosFields(arquivoClass, fieldsCount, constantPool);

	//le o numero de metodos
	methodsCount = lerU2(arquivoClass);

	//carrega os metodos na memoria
	methods = lerTodosMethods(arquivoClass, methodsCount, constantPool);

	//le o numero de atributos
	attributesCount = lerU2(arquivoClass);

	//carrega atributos
	attributes = lerTodosAttributes(arquivoClass, constantPool, attributesCount);

	//**verifica se o metodo main esta entre os metodos lidos no bytecode
	encontrouMain = verificarMain();

	//**verifica se existe o metodo <clinit>
	encontrouClinit = verificarClinit();

	//fecha o arquivo
	fclose(arquivoClass);
	arquivoClass = NULL;

	//se nao houve nenhum erro retorna 0
	return (status = 0);
}

/**
 * Impressão do programa
 * @return true ou false dependendo se a variavel status indicar que houve erro na leitura
 */
bool LeitorExibidor::exibir() {
	//verifica se o arquivo foi lido
	if (status != 0) {
		return false;
	}

	//imprime as informacoes basicas lidas
	imprimirInformacoesGerais();

	//chama o metodo que se encontra na classe constantPool para imprimir as constantes
	imprimirConstantPool(constantPool, lengthCP);

	//chama o metodo que se encontra na classe interfaces para imprimi-las
	imprimirTodasInterfaces(interfaces, constantPool, interfacesCount);

	//chama o metodo que se encontra na classe fields para imprimir os fields
	imprimirTodosField(fields, constantPool, fieldsCount);

	//chama o metodo que se encontra na classe methods para imprimir os metodos
	imprimirTodosMethods(methods, constantPool, methodsCount);

	//chama o metodo que se encontra na classe attributes para imprimir os atributos
	imprimirTodosAttributes(attributes, constantPool, attributesCount);

	return true;
}

/**
 * Gravação do programa
 * @return true ou false dependendo se a variavel status indicar que houve erro na leitura
 */
bool LeitorExibidor::gravarArquivo() {
	//verifica se o arquivo foi lido
	if (status != 0) {
		return false;
	}

	gravarArquivoInformacoesGerais();

	gravarArquivoConstantPool(constantPool, lengthCP, arquivoSaida);

	gravarArquivoTodasInterfaces(interfaces, constantPool, interfacesCount, arquivoSaida);

	gravarArquivoTodosField(fields, constantPool, fieldsCount, arquivoSaida);

	gravarArquivoTodosMethods(methods, constantPool, methodsCount, arquivoSaida);

	gravarArquivoTodosAttributes(attributes, constantPool, attributesCount, arquivoSaida);

	return true;
}

/**
 * Exibidor do programa
 * @return variavel status que indica se houve erro no programa
 */
void LeitorExibidor::imprimirInformacoesGerais() {
	cout << "" << endl;

	cout << "Minor version:\t\t " << minVersion << endl;

	cout << "Major version:\t\t " << majVersion << endl;

	cout << "Número de Constant pool: " << lengthCP << endl;

	//imprime as flags
	imprimirFlags(accessFlags);

	//imprime a classe e o indice apontado
	cout << "This class:\t\t cp info #" << this_class << " <" << capturarIndiceDeReferencia(constantPool, this_class) << ">" << endl;

	//imprime a super classe e o indice apontado
	cout << "Super class:\t\t cp info #" << super_class << " <" << capturarIndiceDeReferencia(constantPool, super_class) << ">" << endl;

	cout << "Número de Interfaces:\t " << interfacesCount << endl;

	cout << "Número de Campos:\t " << fieldsCount << endl;

	cout << "Número de Metodos:\t " << methodsCount << endl;

	cout << "Número de Atributos:\t " << attributesCount << endl;

	cout << "" << endl;
}

/**
 * Exibidor do programa
 * @return variavel status que indica se houve erro no programa
 */
void LeitorExibidor::gravarArquivoInformacoesGerais() {
	arquivoSaida << "" << endl;

	arquivoSaida << "Minor version:\t\t " << minVersion << endl;

	arquivoSaida << "Major version:\t\t " << majVersion << endl;

	arquivoSaida << "Número de Constant pool: " << lengthCP << endl;

	//imprime as flags 
	gravarArquivoFlags(accessFlags, arquivoSaida);

	//imprime a classe e o indice apontado
	arquivoSaida << "This class:\t\t cp info #" << this_class << " <" << capturarIndiceDeReferencia(constantPool, this_class) << ">"
			<< endl;

	//imprime a super classe e o indice apontado
	arquivoSaida << "Super class:\t\t cp info #" << super_class << " <" << capturarIndiceDeReferencia(constantPool, super_class) << ">"
			<< endl;

	arquivoSaida << "Número de Interfaces:\t " << interfacesCount << endl;

	arquivoSaida << "Número de Campos:\t " << fieldsCount << endl;

	arquivoSaida << "Número de Metodos:\t " << methodsCount << endl;

	arquivoSaida << "Número de Atributos:\t " << attributesCount << endl;

	arquivoSaida << "" << endl;
}

/**
 * Lê os ultimos caracteres do arquivo pra ver se formam a extensao .class
 * @return booleano que indica se existe o .class
 */

bool LeitorExibidor::validarExtensao() {
	string aux = "", auxFilename(this->fileName);
	int size = auxFilename.size();

	if (size > 7) {
		for (int i = size - 6; i < size; i++) {
			aux += auxFilename[i];
		}
	}

	return aux == ".class";
}

/**
 * verifia se o metodo main existe nos metodos lidos no bytecode
 * @return booleano que indica se existe o metodo main
 */

bool LeitorExibidor::verificarMain() {
	bool encontrou = false;

	for (int i = 0; i < methodsCount; i++) {
		int name = methods[i].name_index, desc = methods[i].descriptor_index, flags = methods[i].access_flags;

		//verifica se o nome do metodo se encontra dentro das referencias das constantes
		if ("main" == capturarIndiceDeReferencia(constantPool, name)) {
			//verifica se o descritor do metodo esta correto
			if ("([Ljava/lang/String;)V" == capturarIndiceDeReferencia(constantPool, desc)) {
				if ((flags & 0x09) == 0x09) {
					mainMethod = i;
					encontrou = true;
					break;
				}
			}
		}
	}

	//se encontrou a main retorna true
	return encontrou;
}

/**
 * verifia se o metodo clinit existe nos metodos lidos no bytecode
 * @return booleano que indica se existe o metodo clinit
 */

bool LeitorExibidor::verificarClinit() {
	bool encontrou = false;

	for (int i = 0; i < methodsCount; i++) {
		//pega o nome do metodo
		int name = methods[i].name_index;

		//verifica se o nome do metodo se encontra nas constantes
		if ("<clinit>" == capturarIndiceDeReferencia(constantPool, name)) {
			clinit = i;
			encontrou = true;
			break;
		}
	}

	return encontrou;
}

/**
 * verifia se o metodo main foi encontrado
 * @return booleano que indica se existe o metodo main
 */
bool LeitorExibidor::existeMain() {
	//verifica se o metodo main esta entre os metodos lidos no bytecode
	encontrouMain = verificarMain();
	return encontrouMain;
}

/**
 * verifia se o metodo clinit foi encontrado
 * @return booleano que indica se existe o metodo clinit
 */
bool LeitorExibidor::existeClinit() {
	//verifica se existe o metodo <clinit>
	encontrouClinit = verificarClinit();
	return encontrouClinit;
}

/**
 * Retorna o metodo main no formato da struct method_info
 * @return struct method_info contendo informações sobre o método
 */
method_info LeitorExibidor::obterMain() {
	if (encontrouMain) {
		return methods[mainMethod];
	} else {
		throw runtime_error("Nao foi encontrado um metodo main!\n");
	}
}

/**
 * Retorna o metodo clinit no formato da struct method_info
 * @return struct method_info contendo informações sobre o método
 */
method_info LeitorExibidor::obterClinit() {
	return methods[clinit];
}

/**
 * Verifica se a .class lida no bytecode é a mesma que foi declarada no nome do arquivo
 * @return booleano indicando se a .class está correta
 */
bool LeitorExibidor::verificarThisClass() {
	int auxPos;

	string auxFilename(this->fileName);
	string auxClass = capturarIndiceDeReferencia(this->constantPool, this->this_class);

	//remove extensao .class
	auxFilename = auxFilename.substr(0, auxFilename.size() - 6);

	//remove nomes de pastas no Windows
	auxPos = auxFilename.find("\\");

	while (auxPos >= 0 && (unsigned int) auxPos <= auxFilename.size()) {
		auxFilename = auxFilename.substr(auxPos + 1);
		auxPos = auxFilename.find("\\");
	}

	//remove nomes de pastas no Linux
	auxPos = auxFilename.find("/");
	while (auxPos >= 0 && (unsigned int) auxPos <= auxFilename.size()) {
		auxFilename = auxFilename.substr(auxPos + 1);
		auxPos = auxFilename.find("/");
	}

	return (auxClass == auxFilename);
}

/**
 * Retorna a variavel status que indica se houve erro na leitura do bytecode
 * @return status
 */
int LeitorExibidor::obterStatus() {
	return status;
}

/**
 * Verifica qual foi o erro encontrado pelo programa
 * @param error MACRO com o erro que foi encontrado
 * @return string contendo informação sobre o tipo de erro encontrado
 */
string LeitorExibidor::obterErro(int erro) {
	string mensagemErro = "";
	switch (erro) {
	case MISSING_ARGUMENT:
		mensagemErro = "ERRO: Argumento passado invalido!\n";
		break;
	case CANT_OPEN:
		mensagemErro = "ERRO: nao foi possivel abrir o arquivo \"" + string(fileName) + "\"!\n";
		break;
	case INVALID_FILE:
		mensagemErro = "ERRO: Arquivo invalido!\nAssinatura \"cafe babe\" nao encontrada.\n";
		break;
	case UNKNOWN_TYPE:
		mensagemErro = "ERRO: Tipo nao reconhecido para o pool de constantes!\nNao foi possivel carregar todo o PC.";
		break;
	case INVALID_NAME:
		mensagemErro = "ERRO: O nome da classe definida nao bate com o do arquivo!\n";
		break;
	case INVALID_EXTENSION:
		mensagemErro = "ERRO: O arquivo deve ter a extensao .class!\n";
		break;
	case MISSING_MAIN:
		mensagemErro = "O arquivo não possui metodo main\n";
		break;
	case MISSING_CLINIT:
		mensagemErro = "O arquivo não possui metodo clint\n";
	default:
		break;
	}
	return mensagemErro;
}

/**
 * método para pegar a constant pool lida
 * @return Retorna a array com a constant pool
 */
cp_info* LeitorExibidor::obterConstantPool() const {
	return constantPool;
}

/**
 * método para pegar a constant pool lida
 * @return Retorna a array com a constant pool
 */
U2 LeitorExibidor::obterTamanhoConstantPool() {
	return lengthCP;
}

/**
 * Verifica o caminho mais o nome do arquivo dependendo do sistema operacional
 * @return Retorna a string com o caminho total do arquivo
 */
char *LeitorExibidor::obterPath() {
	string path = "", auxFilename(this->fileName);
	char *caminho_arquivo;
	int auxPos;

	//navega pelas pastas do windows
	auxPos = path.find("\\");
	while (auxPos >= 0 && (unsigned int) auxPos <= path.size()) {
		path += auxFilename.substr(0, auxPos + 1);
		auxFilename = auxFilename.substr(auxPos + 1);
		auxPos = auxFilename.find("\\");
	}

	//navega pelas pastas do linux
	auxPos = auxFilename.find("/");
	while (auxPos >= 0 && (unsigned int) auxPos <= auxFilename.size()) {
		path += auxFilename.substr(0, auxPos + 1);
		auxFilename = auxFilename.substr(auxPos + 1);
		auxPos = auxFilename.find("/");
	}

	//copia o resulta para a string caminho_arquivo
	caminho_arquivo = (char *) malloc(sizeof(char) * (path.size() + 1));
	for (unsigned int i = 0; i < path.size(); i++) {
		caminho_arquivo[i] = path[i];
	}
	caminho_arquivo[path.size()] = '\0';

	return caminho_arquivo;
}

/**
 * Retorna a array contendo os métodos
 * @return array do tipo method_info
 */
method_info *LeitorExibidor::obterMethods() {
	return methods;
}

/**
 * Retorna o número de methods
 * @return uint16_t indicando o numero de metodos
 */
U2 LeitorExibidor::obterMethodsCount() {
	return methodsCount;
}

/**
 * Retorna a variavel que indica o this_class
 * @return uint16_t this_class
 */
U2 LeitorExibidor::obterThis_class() {
	return this_class;
}

/**
 * Retorna a variável que indica o super_class
 * @return uint16_t super_class
 */
U2 LeitorExibidor::obterSuper_class() {
	return super_class;
}

/**
 * Retorna o número de fields
 * @return uint16_t indicando o numero de fields
 */
U2 LeitorExibidor::obterFieldsCount() {
	return fieldsCount;
}

/**
 * Retorna a array com as fields lidas
 * @return a array da struct field_info
 */
field_info *LeitorExibidor::obterFields() {
	return fields;
}

/**
 * Retorna um field
 * @param field_name nome do field que deseja retornar
 * @return struct field_info com a informação da field passada no parâmetro
 */
field_info* LeitorExibidor::obterField(string nome) {
	//percorre a array com as fields  ate encontrar field desejada
	for (int i = 0; i < obterFieldsCount(); i++) {
		if (capturarIndiceDeReferencia(constantPool, fields[i].name_index) == nome) {
			return fields + i;
		}
	}
	return NULL;

}

method_info* LeitorExibidor::getMethod(string name, string descriptor) {
	method_info method;

	for (int i = 0; i < this->methodsCount; i++) {
		method = this->methods[i];
		string method_name = capturarIndiceDeReferencia(this->constantPool, method.name_index);
		string method_desc = capturarIndiceDeReferencia(this->constantPool, method.descriptor_index);

		if (descriptor == method_desc && name == method_name) {
			return methods + i;
		}
	}

	if (obterSuper_class() == 0) {
		return NULL;
	} else {
		ClasseEstatica* a = MethodArea::obterClass(capturarIndiceDeReferencia(this->constantPool, obterSuper_class()));
		LeitorExibidor* l = a->obterClasseLeitorExibidor();

		return l->getMethod(name, descriptor);
	}
}

/**
 * Retorna a classe do metodo que esta sendo procurado
 * @param name nome do method
 * @param descriptor descritor do method
 * @return classe Leitor
 */
LeitorExibidor* LeitorExibidor::getClassThatHasSerachedMethod(string name, string descriptor) {
	method_info* method;

	for (int i = 0; i < this->methodsCount; i++) {
		method = (this->methods) + i;

		string method_name = capturarIndiceDeReferencia(this->constantPool, method->name_index);
		string method_desc = capturarIndiceDeReferencia(this->constantPool, method->descriptor_index);

		if (descriptor == method_desc && name == method_name) {
			return this;
		}
	}

	if (obterSuper_class() == 0) {
		return NULL;
	} else {
		LeitorExibidor* l =
				MethodArea::obterClass(capturarIndiceDeReferencia(this->constantPool, obterSuper_class()))->obterClasseLeitorExibidor();
		return l->getClassThatHasSerachedMethod(name, descriptor);
	}
}
