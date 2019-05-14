#include "Reader.h"

Reader::Reader(){
	
}

Reader::~Reader(){

}

void Reader::SetReadFile(std::string fileName){
	if(fileToRead.is_open()){
		fileToRead.close();
	}

	fileToRead.open(fileName, ios::binary);
}

void Reader::Readu1(){

}

void Reader::Readu2(){

}

void Reader::Readu4(){
	
}