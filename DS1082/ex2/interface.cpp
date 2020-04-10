#include "interface.h"
#include "treeavl.h"
#include "tree23.h"


#include <cstring>
#include <cstdio>

#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <cmath>
using namespace std ;

struct Data ;


Interface :: Interface() {
	interfaceLoop() ;

} 

Interface :: ~Interface() {
	
}

void Interface :: interfaceLoop () {
	int cmdrecord = -1 ;
	int cmd = command() ;
	string fileName ;
	vector<Data> List ;
	while ( cmd != 0 ) { 
        
        if ( cmd == 0 ) break ;
        else if ( cmd == 1 ) {
          clear() ;
          List.clear() ;
          string fileName ;       
		     
          cout << "Input a file number (e.g., 201, 202, 203, ... [0] Quit) :"  ;
	      cin >> fileName ;
	     
	      while ( ! readfile(fileName,List) && fileName != "0"  ) {
		    cout << "Input a file number (e.g., 201, 202, 203, ... [0] Quit) :"  ;
	        cin >> fileName ;

          }

	      if ( fileName != "0"){
            for ( int i = 0 ; i < List.size() ; i++) 
                tree23.insert( List[i].serial, List[i].sname ) ;
      	    show23Result( List ) ;
          }

          
		}
		else if ( cmdrecord == 1 && cmd ==2 ) {
		
			for ( int i = 0 ; i < List.size() ; i++) {
		
                 treeAVL.insert( List[i].serial, List[i].ngrad ) ;
            }
            showAVLResult( List ) ;
		}
		else if ( cmd == 3) {
			string name ;
			cout << "Please enter the school name you want to delete :" ;
			cin >> name ;
			cout << "Delete Records :" << endl ; 
			
        	int delnum = 0 ;
        	bool exist = false ;
        	for ( int i = 0;i<List.size(); ) {
        
			    if( List[i].sname.compare(name) == 0 )  {
			  		exist = true ;
			  		cout << "[" << ++delnum << "]	" << List[i].sname << "	" << List[i].dname << "	" << List[i].type << "	" << List[i].level << "	" ;
					cout << List[i].nstd << "	" << List[i].nprof << "	" << List[i].ngrad << endl ;
					List.erase(List.begin()+i) ;
				}
				else i++ ;
			}
			if ( !exist ) {
				cout << "The school " << name << " is not at the 2-3 tree !!!" << endl ;
			}
			else {
			  stack<pointType> path ;
		      tree23.deletelocate( name,path) ;
			  tree23.deleted( path, name ) ;
			  show23Result( List ) ;
			  
			  tree23.preorder( tree23.root23 ) ;
		    }
		}
		else if ( cmd == 5) {
			int key, delnum = 0 ;
			cout << "Enter K in [1," << List.size() <<"]" ;
			cin >> key ;
			while ( key < 0) {
				cout << "Enter K in [1," << List.size() <<"]" ;
			    cin >> key ;
			}
			
		    treeAVL.top_k_search( key, List ) ;
	
			
		}
		else cout << "### Choose 1 first. ###" << endl ;

		cmdrecord = cmd ;
		cmd = command() ;
	}

}

void Interface :: show23Result( vector<Data> List ) {
	cout << "Tree height : " <<  tree23.getHeight()  << endl ;
	cout << "Number of Node :" << tree23.getNumofNode( tree23.root23 ) << endl ;
	if ( tree23.root23 == NULL ) return ;
    vector<int> printList ;
    int serial = 1 ;
    
    for ( int i = 0 ; i < tree23.root23->data[0].rSet.size() ; i++) 
        for ( int j = 0 ; j < List.size() ; j++) 
		  if ( List[j].serial == tree23.root23->data[0].rSet[i] ) 
		  	printList.push_back(List[j].serial) ; 
		
    
	for ( int i = 0 ; i < tree23.root23->data[1].rSet.size() ; i++) 
        for ( int j = 0 ; j < List.size() ; j++) 
		  if ( List[j].serial == tree23.root23->data[1].rSet[i] ) 
		  	printList.push_back(List[j].serial) ;
	sort(printList.begin(),printList.end()) ;
    for ( int i = 0 ; i < printList.size() ; i ++) {
    	
    	for ( int j = 0 ; j < List.size() ; j ++) {
		
    	  if ( printList[i] == List[j].serial) {
    	  	cout << serial++ << ": [" << List[j].serial << "] " << List[j].sname << ", " << List[j].dname << ", " ;
    	  	cout << List[j].type <<", " << List[j].level << ", " << List[j].ngrad << endl ;
    		break ;
		  }
	    }
	}
    
	
	

}


void Interface :: showAVLResult( vector<Data> List ) {

	cout << "Tree height : " <<  treeAVL.getHeight( treeAVL.rootAVL )  << endl ;
	cout << "Number of Node :" << treeAVL.numofnode( treeAVL.rootAVL ) << endl ;
	if ( treeAVL.rootAVL == NULL ) return ;
    vector<int> printList ;
    int serial = 1 ;
    for ( int i = 0 ; i < treeAVL.rootAVL->data.rSet.size() ; i++) 
        for ( int j = 0 ; j < List.size() ; j++) 
		  if ( List[j].serial == treeAVL.rootAVL->data.rSet[i] ) 
		  	printList.push_back(List[j].serial) ; 
		
	sort(printList.begin(),printList.end()) ;
    for ( int i = 0 ; i < printList.size() ; i ++) {
    	
    	for ( int j = 0 ; j < List.size() ; j ++) {
		
    	  if ( printList[i] == List[j].serial) {
    	  	cout << serial++ << ": [" << List[j].serial << "] " << List[j].sname << ", " << List[j].dname << ", " ;
    	  	cout << List[j].type <<", " << List[j].level << ", " << List[j].ngrad << endl ;
    		break ;
		  }
	    }
	}
    
	
	

}
void Interface :: clear() {
	treeAVL = Tree_AVL() ;
	tree23 = Tree_2_3() ;
	tree23.root23 = NULL ;
	treeAVL.rootAVL = NULL ;
}
bool Interface :: isnum ( char str[99]){
	int i =0;
	while(i < strlen(str)){
		if (str[i]<'0' || str[i]>'9') return 0;
		i++;
	}
	return true ;

}
int Interface :: command() { // §ì«ü¥O
	string ins ;
	cout << "***      Search Tree Utilities      ***" << endl ;
	cout << "* 0. QUIT                             *" << endl ;
	cout << "* 1. Build a 2-3 Tree                 *" << endl ;
    cout << "* 2. Build a AVL Tree                 *" << endl ;
    cout << "* 3. Delete node in 2-3 Tree          *" << endl ;
    cout << "* 4. Delete node in AVL Tree          *" << endl ;
    cout << "* 5. Top K search in AVL Tree         *" << endl ;
	cout << "***************************************"<<endl;
    cout << "Input a command(0, 1, 2, 3, 4, 5):"  ;
	cin >> ins ;
	while ( ins != "0" && ins !="1" && ins != "2" && ins != "3" && ins != "4" && ins !="5" ) {

	  cout << "["<<ins << "]" << "Is An Invalid Command Please Try Again !!! " << endl ;
	  cin >> ins ;
    }
    return atoi(ins.c_str()) ;
}
bool Interface:: readfile(string fileName,vector<Data> & List) {
  	char ch = '\0' ;
  	int Eof = 0;
  	int i = 0, serial = 0 ;

  	FILE *infile = NULL ;
  	fileName = "input" + fileName + ".txt";
  	infile = fopen(fileName.c_str(),"r") ;
  	if ( infile == NULL ) {
	  cout << fileName + " does not exist"<<endl ;
	  return false ;
    }
    else {


    	while ( ch != '\n') fscanf(infile,"%c",&ch) ;
    	fscanf(infile,"%c",&ch ) ;
    	while ( ch != '\n') fscanf(infile,"%c",&ch) ;
    	fscanf(infile,"%c",&ch ) ;
    	while ( ch != '\n') fscanf(infile,"%c",&ch) ;
    	Eof = fscanf(infile,"%c",&ch ) ;


        while (Eof != -1) {
        	Data New = Data() ;
        	serial++ ;
        	New.serial = serial ;

        	while ( ch != '\n'&&Eof != -1 ) {
        		while ( ch != '\t') {
        			New.snum += ch ;
        			fscanf(infile,"%c",&ch ) ;
				}
				fscanf(infile,"%c",&ch ) ;
				while ( ch != '\t') {
        			New.sname += ch;
        			fscanf(infile,"%c",&ch ) ;
				}
				fscanf(infile,"%c",&ch ) ;
				while ( ch != '\t') {
        			New.dnum += ch;
        			fscanf(infile,"%c",&ch ) ;
				}

				fscanf(infile,"%c",&ch ) ;
				while ( ch != '\t') {
        			New.dname += ch;
        			fscanf(infile,"%c",&ch ) ;
				}
				fscanf(infile,"%c",&ch ) ;
				while ( ch != '\t') {
        			New.type += ch;
        			fscanf(infile,"%c",&ch ) ;
				}
				fscanf(infile,"%c",&ch ) ;
				while ( ch != '\t') {
        			New.level += ch;
        			fscanf(infile,"%c",&ch ) ;
				}
				fscanf(infile,"%c",&ch ) ;
				while ( ch != '\t') {
        			New.nstd += ch;
        			fscanf(infile,"%c",&ch ) ;
				}
				
				fscanf(infile,"%d",&New.nprof ) ;
				fscanf(infile,"%c",&ch ) ;

				fscanf(infile,"%d",&New.ngrad ) ;
				fscanf(infile,"%c",&ch ) ;
				fscanf(infile,"%c",&ch ) ;
				while ( ch != '\t') {
        			New.city += ch;
        			fscanf(infile,"%c",&ch ) ;
				}

				fscanf(infile,"%c",&ch ) ;
				while ( ch != '\n'&&Eof != -1  ) {

        			New.System += ch;
        			Eof = fscanf(infile,"%c",&ch ) ;
				}
			}
			i++ ;
			List.push_back(New) ;
			if ( ch == '\n') Eof = fscanf(infile,"%c",&ch ) ;

		}
	}

	fclose( infile ) ;
	return true ;

}

