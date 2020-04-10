#ifndef INTERFACE_H
#define INTERFACE_H

#include <string>

#include "tree23.h"
#include "treeavl.h"



struct Data ;
class Interface {
public :
	Interface() ;
	~Interface() ;
	void interfaceLoop() ;
	void clear() ;
	int command() ;
	bool isnum ( char str[99] );
	bool readfile( string fileName, vector<Data> & List) ;
	void show23Result( vector<Data> List ) ;
	void showAVLResult( vector<Data> List ) ;
	void showtop_kResult( vector<Data> List ) ;
	Tree_AVL treeAVL ;
	Tree_2_3 tree23 ;
	
};

#endif 
