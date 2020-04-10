#ifndef TREEAVL_H
#define TREEAVL_H

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stack>
#include "tree23.h"
using namespace std; 



typedef struct field {  			// a slot in a tree node 
   
	vector <int> rSet ; // a set of record with the same key 
	int key ; 		//  key = num of graduate 
}  fieldType ;

typedef struct treenode { 					 // a tree nodw of a avl tree
 
	fieldType data ;   		 //  a list of recore sorted by keys
	struct treenode * left  ;
	struct treenode * right ;
	struct treenode * parent ;
}  treenodeType ;


class Tree_AVL {
public :
	Tree_AVL()  ;
	~Tree_AVL() ;
	
	treenodeType * rootAVL ;
	void insert( int serial, int key ) ;
	void remove( int key ) ;               // remove the node
	treenodeType * removelocate( int key) ;// return the lacation of delete node 
	void balance( treenodeType * node ) ;  //  balnce the tree
	treenodeType * createnode( fieldType field) ; 
	int getHeight( treenodeType * node ) ;
	int getBF( treenodeType * node) { return ( node == NULL) ? 0 : getHeight(node->left) - getHeight(node->right) ; } // get balance factor
	int max( int a, int b) { return ( a > b) ? a:b ;}
	treenodeType * rotateLL( treenodeType * root) ;
	treenodeType * rotateLR( treenodeType * root) ;
	treenodeType * rotateRR( treenodeType * root) ;
	treenodeType * rotateRL( treenodeType * root) ;
	treenodeType * leftmost( treenodeType * root) ;
	treenodeType * rightmost( treenodeType * root) ; 
	

	void top_k_search( int key, vector<Data> List) ;

	void passValue( treenodeType * successor, treenodeType * newNode ) ;
	int numofnode( treenodeType * root ) ;
	void inorder(treenodeType * root, vector<int> & list, int key, int & index, int kth, vector<int> & duplicate) ;
	
	 
};


#endif
