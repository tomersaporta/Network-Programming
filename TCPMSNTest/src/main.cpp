//============================================================================
// Name        : TCPMSNTest.cpp
// Author      : Tomer Saporta
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "TCPMSNClientTest.h"
#include <iostream>

using namespace networkingLab;
using namespace std;

int main() {
	cout << "!!!TCPMSNClientTest!!!" << endl;
	TCPMSNClientTest TCPMSNtest;
	bool test = false;
	test = TCPMSNtest.test();
	if(test){
		cout<<"\n***TCP MSN Client Test PASS***\n"<<endl;
	}
	else {
		cout<<"TCP MSN Client Test Failed!!!!"<<endl;
	}
	return 0;
}
