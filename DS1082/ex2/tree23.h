#ifndef TREE23_H
#define TREE23_H
#define PTR_NUM 3 
#define KEY_NUM PTR_NUM - 1
#include<stack>
#include<vector>
#include<string>

using namespace std ;

struct Data {
  string snum,sname,dnum ;  // school number , name // department number
  string dname,type,level ; // 日間/進修別  /等級別
  string city,System, nstd ;
  int nprof,ngrad ;
  int serial ;

};

typedef struct slot {  			// a slot in a tree node 
	vector <int> rSet ; // a set of record with the same key 
	string key ; 		//  key = school name 
}   slotType ;

typedef struct node { 					 // a tree nodw of a 23 tree
	slotType data[KEY_NUM] ;   		 //  a list of recore sorted by keys
	struct node *link[PTR_NUM] ; // a list of pointers
	struct node * parent ; 		 // a pointer to the parent node 
}   nodeType ;


typedef struct point { 	// a point on the search path
    node *pnode ; 		// pointer to a parent node
    int pidx ;			// entrance index on the parent node 
}   pointType ;

typedef struct block { // a data block recieved from a split 
	slotType slot ;	   // a pair of (id,key)
	nodeType *link ;   // a pointer to a child on the right 
}   blockType ;


class Tree_2_3 {
public :
	Tree_2_3() ;
	~Tree_2_3() ;
    nodeType * root23 ;
    void insert( int newRid, string newKey ) ; // add one record 
    nodeType * createNode( nodeType * left, nodeType * right, nodeType * parent, slotType newSlot) ; // create a node with one record 
    slotType  createSlot( vector<Data> item ) ;
    void searchPath( string name, stack<pointType> & aPath ) ; // find a matched slot or the position 
    void insertLeaf(  slotType newS, pointType & aLeaf ) ; // add a record into a leaf 
    void splitLeaf(  slotType news, pointType & aLeaf, blockType & aBlock ) ; // split a leaf for an insertion 
    nodeType * createRoot(  nodeType * left, nodeType * right , slotType oneSlot) ; // create a new root after a split
    void insertNonLeaf( pointType & goal, blockType oneB ) ; // add a record into a leaf 
    void splitNonLeaf( pointType & goal, blockType & oneB ) ; // split a non-leaf for an insertion
    void free23tree(nodeType * root ) ; // release the space of 23 tree
    int getHeight() ;
    int getNumofNode( nodeType * root ) ;
	void preorder( nodeType * root ) ;
	
	// delete operation 
	nodeType * deletelocate( string name, stack<pointType> & path ) ;
	void deleted( stack<pointType> & path, string name) ;
	bool isbottom( nodeType * node ) { return ( node->link[0] == 0) ? true : false ;}
	
	void leafMerge( nodeType * node, stack<pointType> & path ) ;
	void nonLeafMerge( stack<pointType> path, nodeType * addleaf, nodeType * delitem) ;
	nodeType * leftmost( nodeType * root, stack<pointType> & path ) ;
	nodeType * rightmost( nodeType * root) ; 
};


#endif
