#ifndef READER_H
#define READER_H

#include <string>
#include "Structures.h"

class Reader
{
public:
	Reader();
	~Reader();

	void SetReadFile(std::string fileName);
private:
	u1 Readu1();
	u2 Readu2();
	u4 Readu4();

	ifstream fileToRead;
};

#endif