/*
 * File.h
 *
 *  Created on: Jun 5, 2017
 *      Author: user
 */

#ifndef SRC_FILE_H_
#define SRC_FILE_H_

#include "FileBase.h"

namespace networkingLab {

class File :public FileBase{

public:
	//FILE * pFile;
	//string path;


	File(string path,int mode);
	virtual ~File();
	//virtual int read(char* msg, int len);
	//virtual int write(const char* msg, int len);
	//virtual void close();
};

} /* namespace networkingLab */

#endif /* SRC_FILE_H_ */
