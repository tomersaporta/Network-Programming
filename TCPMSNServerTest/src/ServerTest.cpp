//============================================================================
// Name        : ServerTest.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "TCPMSNServer.h"
using namespace networkingLab;
using namespace std;

int main() {
	cout << "!!!TCP MSN Server!!!" << endl; // prints !!!Hello World!!!

	TCPMSNServer*s = new TCPMSNServer();
		s->startServer();

	return 0;
}
