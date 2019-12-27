

// 10720129 張書維 10720109 王睿安 
#include <stdio.h>
#include <stdlib.h>
#include<vector>
#include <cstdio>
#include <string.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <iomanip>
#include <algorithm>
using namespace std ;
// 學校代碼	  學校名稱	t3科系代碼	t4科系名稱	t5日間∕進修別	t6等級別	t7學生數	t8教師數	stdnum上學年度畢業生數	t9縣市名稱	
//  t10體系別
// 1. 0002	2.國立清華大學	3.520114	4.資訊工程學系	5. D 日	 6. B 學士	7. 565	8. 43	stdnum 117	9.18 新竹市	10. 1 一般
struct Title {
  
  string snum,sname,dnum ;  // school number , name // department number
  string dname,type,level ; // 日間/進修別  /等級別 
  string city,System ;
  int nstd,nprof,ngrad ;
  Title * Left ;
  Title * Right ;
  Title * Parent ; 
};
class BST{
	public :
    Title * gradroot ;
    Title * snameroot ;
    Title * DelSearchbygrad(int key) ;
    Title * DelSearchbysname(string name) ;
    void Deletegradbys( int key) ;
    void Deletebysname( string name) ;
    void Addbygrad(Title * NewNode) ;
    void Addbysname(Title * NewNode) ;
    int Height(Title * Node ) ;
    bool Readfile(string fileName) ;  
    void Searchbygrad() ;
    void Searchbysname() ;
    void PreSearchbygrad(int & i,int inputgrad,Title * cur,bool & find) ;
    void PreSearchbysname(int & i,string inputschool,Title * cur, bool & find) ;

  Bst() {} ;


};
bool Isnum ( char str[99]);
void Command(  int & cmd ) ;
bool Readfile(string fileName,vector<Title> & List ) ;
int Max(int a,int b) ;
void PassValue( Title * change, Title *New  ){
	New->dname = change->dname ;
	New->sname = change->sname ;
	New-> type =  change->type ;
	New-> level =  change->level ;
	New -> nstd =  change->nstd ;
	New -> nprof = change->nprof ;
	New -> ngrad =  change->ngrad ;
}
Title * CreateNode( vector <Title> List,int i) {
	Title * New = new Title () ;
	New->dname = List[i].dname ;
	New->sname = List[i].sname ;
	New-> type = List[i].type ;
	New-> level = List[i].level ;
	New -> nstd = List[i].nstd ;
	New -> nprof = List[i].nprof ;
	New -> ngrad = List[i].ngrad ;
	New ->Left = New->Right =NULL ;
	
	return New ;
}
void Preorder( Title * cur) {
	if ( cur){
		cout << cur -> ngrad << endl ;
		Preorder(cur->Left) ;
		Preorder( cur->Right) ;
	}
}
void Inorder( Title * cur) {
	if ( cur){
		Inorder(cur->Left) ;
		cout << cur -> sname << endl ;
		Inorder( cur->Right) ;
	}
}
 void CreateTree( BST & tree,vector<Title> List) {
	for ( int i=0;i<List.size();i++) {
		tree.Addbygrad(CreateNode(List,i) ) ;
	}
	for ( int i=0;i<List.size();i++) {
		tree.Addbysname(CreateNode(List,i) ) ;
	}
    
    cout << "Tree heights:" << endl << "{Number of graduates} = " << tree.Height(tree.gradroot) <<endl;
    cout << "{School name} = " << tree.Height(tree.snameroot) << endl ;
    
}

Title * Leftmost( Title * cur) {
	while ( cur -> Left!= NULL ) cur = cur ->Left ;
	return cur ;
}
Title * Rightmost( Title * cur) {
	while ( cur -> Right!= NULL ) cur = cur ->Right ;
	return cur ;
}
int main() {
	
	int cmd,key ;
	string name ;
	Command(cmd) ;
	BST tree = BST() ;
	vector<Title> List ;
	
	while ( cmd != 0 ) {
        if ( cmd == 1) {
        	cout << "Input a file number (e.g., 601, 602, 603, ... ) :  "  ;
        	List.clear() ;
        	tree = BST() ;
           string fileName ;
	       cin >> fileName ;
           Readfile(fileName,List) ;
		   CreateTree(tree,List) ;
		   
	    }
        if ( cmd == 2 && tree.gradroot != NULL) tree.Searchbygrad();
        if ( cmd == 3&& tree.gradroot!=NULL) tree.Searchbysname();

        if (cmd == 4&& tree.gradroot!=NULL){
        	cout << "Input the School Name  >> " ;
            
        	cin >> name ;

        	for ( int i = 0;i<List.size();){
        		if(List[i].sname == name) List.erase(List.begin()+i) ;
        		if(List[i].sname != name) i++ ;
			}
        	cout << "Delete Records :" << endl ; 
        	tree.Deletebysname(name) ;
        	cout << "Tree heights:" << endl << "{Number of graduates} = " << tree.Height(tree.gradroot) <<endl;
            cout << "{School name} = " << tree.Height(tree.snameroot) << endl ;
		}
        if ( cmd != 1&& tree.gradroot== NULL) cout << "PLease execute command 1 first !!!" << endl ;
		Command(cmd) ;
	}
	return 0;
}

  bool Isnum ( char str[99]){

	int i =0;

	while(i < strlen(str)){

		if (str[i]<'0' || str[i]>'9') return 0;

		i++;

	}

	return 1;

}
void Command(  int & cmd ) { // 抓指令 
	char str[99];
	printf( "*** University Graduate Information System ***\n* 0. Quit                                    *\n") ;
	cout << "* 1. Create Two Binary Search Trees          *" << endl ;
	cout << "* 2. Search by Number of Graduates           *" << endl ;
	cout << "* 3. Search by School Name                   *" <<endl ;
    cout << "* 4. Delete by School Name                   *" <<endl << "**********************************************"<<endl;
    cout << "Input a command(0, 1, 2, 3, 4):"  ; 
	scanf( "%s", str) ;
	while ( ! Isnum(str)){
	  printf( "[%s] Is An Invalid Command Please Try Again !!! \n",str);
      scanf( "%s", str) ;
	}
	cmd = atoi(str) ;
	while ( ! ( cmd >= 0 && cmd <=4)) {
	  printf( "[%s] Is An Invalid Command Please Try Again !!! \n",str);
      scanf( "%s", str) ;
      while ( ! Isnum(str)){
	  printf( "[%s] Invalid Command Please Try Again !!! \n",str);
	  scanf( "%s", str) ;
      }
      cmd = atoi(str) ;
	}
}
bool Readfile(string fileName,vector<Title> & List) {  
  	char ch = '\0' ;
  	int Eof = 0;
  	int i = 0 ;
  	double start,end ;
  	start = clock() ;
  	FILE *infile = NULL ;
  	bool success = false ;
  	fileName = "input" + fileName + ".txt";
  	infile = fopen(fileName.c_str(),"r") ;
  	if ( infile == NULL) {
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
        	Title New = Title() ;
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
				fscanf(infile,"%d",&New.nstd ) ;
				fscanf(infile,"%c",&ch ) ;
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
	

	
	fclose( infile) ;
    
	end = clock() ;
	return success ;
	
  }

void BST::Addbygrad(Title * NewNode) {
	Title *pre = 0 ;
	Title *walk = gradroot ;
	Title * New = NewNode ;
	while ( walk != NULL) {
		pre = walk ;
		if ( New->ngrad < walk->ngrad ) walk = walk-> Left ;
	    else walk = walk -> Right ;
	}
	New->Parent = pre ;
	if ( pre == NULL ) gradroot = New ;
	else if ( New->ngrad < pre->ngrad ) pre->Left = New ;
	else pre->Right = New ;	
}
void BST ::Addbysname(Title * NewNode) {
	Title *pre = 0 ;
	Title *walk = snameroot ;
	Title * New = NewNode ;
	while ( walk != NULL) {
		pre = walk ;
		if ( New->sname.compare( walk->sname ) <0 ) walk = walk-> Left ;
	    else walk = walk -> Right ;
	}
	New->Parent = pre ;
	if ( pre == NULL ) snameroot = New ;
	else if ( New->sname.compare(pre->sname ) <0 )  pre->Left = New ;
	else pre->Right = New ;	
}
int Max( int a,int b) {
	return ( (a>b) ? a:b) ; // if ( a > b ) return a  else return b

}
int BST::Height(Title * Node) {
	if ( Node == NULL) return 0 ;
	int lefth = Height(Node->Left);
	int righth = Height(Node->Right) ;
	return 1 + Max(lefth,righth) ;
}


void BST::PreSearchbygrad(int & i,int inputgrad,Title * cur,bool & find) {
	bool stop = false ;
	if ( cur) {
		if ( cur->ngrad >= inputgrad) {
		
		cout << "["<<++i <<"]	"<< cur->sname<<"	"<<cur->dname<< "	"<<cur->type<< "	" ;
		cout << cur->level <<"	"<<cur->nstd<<"	"<<cur->nprof<<"	"<<cur->ngrad<<endl ; 
		find = true ;
	    }
	    if ( cur-> ngrad < inputgrad) if ( cur->Left != NULL ) if ( cur->Left->ngrad < inputgrad) stop = true ;
	    
		if ( !stop) PreSearchbygrad(i,inputgrad,cur->Left,find) ;
		PreSearchbygrad(i,inputgrad,cur->Right,find) ;
	}
}
void BST::PreSearchbysname(int & i,string inputschool,Title * cur,bool & find) {
	bool lstop = false,rstop=false ;
	if ( cur) {
		if ( cur->sname.compare(inputschool)==0 ) {
		
		cout << "["<<++i <<"]	"<< cur->sname<<"	"<<cur->dname<< "	"<<cur->type<< "	" ;
		cout << cur->level <<"	"<<cur->nstd<<"	"<<cur->nprof<<"	"<<cur->ngrad<<endl ; 
		find = true ;
	    }
	    if ( cur->sname.compare(inputschool)<0) if ( cur->Left != NULL ) if ( cur->Left->sname.compare(inputschool) < 0) lstop = true ;
	    if ( cur->sname.compare(inputschool)>0) if ( cur->Right != NULL ) if ( cur->Right->sname.compare(inputschool) > 0) rstop = true ;
		if ( !lstop) PreSearchbysname(i,inputschool,cur->Left,find) ;
		if ( !rstop) PreSearchbysname(i,inputschool,cur->Right,find) ;
	}
}
void BST :: Searchbysname() {
	int i = 0 ;
	bool find = false ;
	cout << "Input the School Name: " ;
	string inputschool ;
	cin >> inputschool ;
	Title * cur = snameroot ;
	PreSearchbysname(i,inputschool,cur,find) ;
	if ( !find) cout << "There is no match !!!"  << endl ;
}

void BST :: Searchbygrad() {
	int inputgrad,i=0;
	bool find = false ;
	cout << "Input the number of graduates: " ;  
	scanf("%d",&inputgrad) ;
	Title * cur = gradroot ;
	PreSearchbygrad(i,inputgrad,cur,find) ;
	if ( !find) cout << "There is no match !!!"  << endl ;

}

Title * BST :: DelSearchbysname(string name) {
	Title * walk = snameroot ;
	while ( walk != NULL && name.compare(walk->sname) != 0) {
	   if ( name.compare(walk->sname)>0) walk = walk -> Right ;
	   else walk = walk -> Left ;
	}
	return walk ;
}
void BST :: Deletebysname( string name ) {
	int i = 0 ;
	Title * del = DelSearchbysname(name) ;
	if ( del == NULL) {
		cout << "NOT found" << endl ;
		return ;
	}
	while ( del != NULL ) {
	cout << "["<<++i <<"]	"<< del->sname<<"	"<<del->dname<< "	"<<del->type<< "	" ;
	cout << del->level <<"	"<<del->nstd<<"	"<<del->nprof<<"	"<<del->ngrad<<endl ; 
	Deletegradbys(del->ngrad) ;
	Title * change = NULL ;
	if ( del -> Left != NULL && del->Right !=NULL) {
				

		change = Leftmost(del->Right) ;
;
		if ( change ->Right != NULL) {
		  if ( change ->Parent != del) {
		  change->Right->Parent = change->Parent ;
		  change -> Parent->Left = change -> Right ;
	      }
	      else {
	      change->Right->Parent = change->Parent ;
		  change -> Parent->Right = change -> Right ;
		  }
	    }
        else {
		  if ( change->Parent->Right == change)change->Parent->Right = NULL ;
		  if ( change->Parent->Left == change)change->Parent->Left = NULL ;

	    }
        PassValue(change,del) ;
		if ( del->Parent == NULL)delete del ;
		delete change ;


	}
	else if ( del->Left == NULL && del->Right == NULL) {
		if ( del->Parent != NULL) {
			if ( del->Parent->Left == del) del->Parent->Left = NULL ;
			if ( del->Parent->Right == del) del->Parent->Right = NULL ;
		}
		delete del ;
		
	}
	else if ( del->Left == NULL && del->Right != NULL) {
		change = Leftmost(del->Right) ;
		if ( change ->Right != NULL) {
		  if ( change ->Parent != del) {
		  change->Right->Parent = change->Parent ;
		  change -> Parent->Left = change -> Right ;
	      }
	      else {
	      change->Right->Parent = change->Parent ;
		  change -> Parent->Right = change -> Right ;
		  }
	    }
        else {
          if ( change->Parent->Right == change)change->Parent->Right = NULL ;
		  if ( change->Parent->Left == change)change->Parent->Left = NULL ;
		}
		PassValue(change,del) ;
		if ( del->Parent == NULL)delete del ;
	}
	else if ( del->Left != NULL && del->Right == NULL) {
		change = Rightmost(del->Left) ;
		if ( change ->Left != NULL) {
		  if ( change->Parent !=del ){
		   change->Left->Parent = change->Parent ;
		   change -> Parent->Right = change -> Left;
	     }
	     else {
	     	change->Left->Parent = change->Parent ;
	     	change->Parent->Left = change ->Left ;
		 }
	    }
        else {
          if ( change->Parent->Right == change)change->Parent->Right = NULL ;
		  if ( change->Parent->Left == change)change->Parent->Left = NULL ;
		}
		PassValue(change,del) ;
		if ( del->Parent == NULL)delete del ;
	}
	del = DelSearchbysname(name) ;
}
	 
}

Title * BST :: DelSearchbygrad(int key) {
	Title * walk = gradroot ;
	while ( walk != NULL && key != walk->ngrad) {
	  if ( key < walk->ngrad)walk = walk -> Left ;
	  else walk = walk->Right ;
	}
	return walk ;
}
void BST :: Deletegradbys( int key) {
	Title * del = DelSearchbygrad(key) ;
	if ( del == NULL) {
		cout << "NOT found" << endl ;
		return ;
	}

	Title * change = NULL ;
	if ( del -> Left != NULL && del->Right !=NULL) {
				

		change = Leftmost(del->Right) ;
;
		if ( change ->Right != NULL) {
		  if ( change ->Parent != del) {
		  change->Right->Parent = change->Parent ;
		  change -> Parent->Left = change -> Right ;
	      }
	      else {
	      change->Right->Parent = change->Parent ;
		  change -> Parent->Right = change -> Right ;
		  }
	    }
        else {
		  if ( change->Parent->Right == change)change->Parent->Right = NULL ;
		  if ( change->Parent->Left == change)change->Parent->Left = NULL ;

	    }
        PassValue(change,del) ;
		if ( del->Parent == NULL)delete del ;
		delete change ;


	}
	else if ( del->Left == NULL && del->Right == NULL) {
		if ( del->Parent != NULL) {
			if ( del->Parent->Left == del) del->Parent->Left = NULL ;
			if ( del->Parent->Right == del) del->Parent->Right = NULL ;
		}
		delete del ;
		
	}
	else if ( del->Left == NULL && del->Right != NULL) {
		change = Leftmost(del->Right) ;
		if ( change ->Right != NULL) {
		  if ( change ->Parent != del) {
		  change->Right->Parent = change->Parent ;
		  change -> Parent->Left = change -> Right ;
	      }
	      else {
	      change->Right->Parent = change->Parent ;
		  change -> Parent->Right = change -> Right ;
		  }
	    }
        else {
          if ( change->Parent->Right == change)change->Parent->Right = NULL ;
		  if ( change->Parent->Left == change)change->Parent->Left = NULL ;
		}
		PassValue(change,del) ;
		if ( del->Parent == NULL)delete del ;
	}
	else if ( del->Left != NULL && del->Right == NULL) {
		change = Rightmost(del->Left) ;
		if ( change ->Left != NULL) {
		  if ( change->Parent !=del ){
		   change->Left->Parent = change->Parent ;
		   change -> Parent->Right = change -> Left;
	     }
	     else {
	     	change->Left->Parent = change->Parent ;
	     	change->Parent->Left = change ->Left ;
		 }
	    }
        else {
          if ( change->Parent->Right == change)change->Parent->Right = NULL ;
		  if ( change->Parent->Left == change)change->Parent->Left = NULL ;
		}
		PassValue(change,del) ;
		if ( del->Parent == NULL)delete del ;
	}
	del = DelSearchbygrad(key) ;

	 
}
