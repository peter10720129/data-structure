// 10720129 張書維   10720127 劉宜鑫
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <cstdio>
#include <string.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <iomanip>
#include <algorithm>
#include <cmath>

using namespace std ;

typedef enum { MIN,MAX} heaptype;

struct Data {

  string snum,sname,dnum ;  // school number , name // department number
  string dname,type,level ; // 日間/進修別  /等級別
  string city,System, nstd ;
  int nprof,ngrad ;
  int serial ;
  heaptype layer ;
};

class Heap {

public :
	vector<Data> items ;
	Heap() {} ;

	int LeftMost () ;  // the left most node of heap
	int Bottom () { return items.size() - 1 ;} // return the bottom index of the heap
	int getRoot() { return (IsEmpty()) ? -1:0 ;}  // if heap empty return -1 as root value
	bool IsEmpty () { return ( items.size() > 0) ? false:true ; } // check if heap is empty
	void MinInsert ( Data newItem ) ; // insert ins of min heap
	void MMInsert ( Data newItem) ; // min-max heap insert
	void MinDelete () ; // min heap delete
	void MMDelete ( int i ) ; // min-max delete
	void MMDRebuild ( int root ) ;
	void MinRebuild ( int root ) ;
	void ShowResult( int cmd ) ;
	void reset() { items.clear() ; }


};

bool Isnum ( char str[99]);
void Command(  int & cmd ) ;
bool Readfile(string fileName,vector<Data> & List ) ;


int main() {
	int cmd, cmdrecord = 0 ;
	Command(cmd) ;
	vector<Data> List ;
	Heap mheap ; // min heap
	Heap heap ; // minmax heap
	while ( cmd != 0 ) {

        if ( cmd == 0 ) break ;
        else if ( cmd == 1  or cmd == 2 ) {
          heap.reset() ;
          cout << "Input a file number (e.g., 101, 102, 103, ... [0] Quit) :"  ;
          List.clear() ;

          string fileName ;
	      cin >> fileName ;
	      if ( fileName != "0"){
            Readfile(fileName,List) ;
            for ( int i = 0 ; i < List.size() ; i++) {
              if ( cmd == 1 ) mheap.MinInsert( List[i] ) ;
      	      else heap.MMInsert( List[i] ) ; // cmd = 2
      	    }

		    if ( cmd == 1 ) mheap.ShowResult( cmd ) ;
		    else heap.ShowResult( cmd ) ;
          }
		}
		else if ( cmd == 3 ) {  // min heap delete

		    if ( cmdrecord == 1 or cmdrecord == 3 ) {

		      string del ;
		      cout << "Are you want to delete ? ENTER (Y/N)" << endl ;
		      cin >> del ;
		      while ( del != "N") {
		    	heap.MinDelete() ;
		    	heap.ShowResult( cmd ) ;
		    	cout << "Are you want to delete ? ENTER (Y/N)" << endl ;
		        cin >> del ;
		      }
		    }
		    else cout << "PLEASE EXECUTE COMMAND 1 FIRST !" << endl ;
		}
		else if ( cmd == 4) { // min-max heap delete
			if ( heap.IsEmpty()) ;
			else {

				if ( cmdrecord == 2 or cmdrecord == 4 ) {
					int  value, i = 1  ;
			        cout << "Enter the value of K in [1," << heap.items.size() << "] : " ;
			        cin >> value ;
			        if ( value <= heap.items.size() and value > 0 ) {

				        while ( value != 0  ) {

				    	  heap.MMDelete( i ) ;
				    	  i++ ;
				          value-- ;
				        }
					}
				}
				else cout << "PLEASE EXECUTE COMMAND 2 FIRST !" << endl ;
			}//else
		}

		cmdrecord = cmd ;
		Command(cmd) ;
	}
	return 0;
}


// swap ins
void Swap( vector<Data> & items,int a, int b) {
	Data temp = items[a];
	items[a] = items[b] ;
	items[b] = temp ;
}

// when swap occur in different layer
void LayerSwap( vector<Data> & items, int a, int b) {
	heaptype temp ;
	temp = items[b].layer ;
	items[b].layer = items[a].layer ;
	items[a].layer = temp ;
}
// insert instruction for heap
void Heap::MinInsert( Data newItem )  {
	items.push_back( newItem ) ; // put the new item at the end of heap
	int place = items.size() - 1 ;

	int parent = ( place - 1) / 2 ; // trickle new item up to its pos

	while ( ( parent >= 0 ) && ( items[place].ngrad < items[parent].ngrad ) ){

		Swap(items,parent,place) ;
		place = parent ;  // conti to find
		parent = ( place - 1 ) / 2 ;
	}


}

// min-max insert
void Heap::MMInsert( Data newItem ) {

	items.push_back( newItem ) ;
	int cur = Bottom() ;
	int parent = ( cur - 1) / 2 ;
	int grandparent = ( parent - 1) / 2 ;
	items[cur].layer = ( (int)floor(log2(cur+1)) % 2) ? MAX:MIN ;
	// cout << "[ " << items[i].serial << "] " << items[i].ngrad << endl ; test data
	if ( items[cur].layer == MIN ) {
		if ( items[cur].ngrad > items[parent].ngrad ) { // need swap and reheap up at the parent in max
		  Swap(items,cur,parent) ;
		  LayerSwap(items,cur,parent) ;
		  cur = parent ;
		  parent = ( cur - 1) / 2 ;
		  grandparent = ( parent - 1) / 2 ;
        }
    }
    else {  // max layer
    	if ( items[cur].ngrad < items[parent].ngrad ) { // need swap and reheap up at the parent in min
		  Swap(items,cur,parent) ;
		  LayerSwap(items,cur,parent) ;
		  cur = parent ;
		  parent = ( cur - 1) / 2 ;
		  grandparent = ( parent - 1) / 2 ;
        }
	}
    if ( items[cur].layer == MAX ) {  // at layer max
		while ( ( grandparent >= 0 ) and
		        ( items[cur].ngrad > items[grandparent].ngrad) and  items[grandparent].layer == items[cur].layer ){
		    Swap(items,cur,grandparent) ;
		    cur = grandparent ;
		    parent = ( cur - 1) / 2 ;
		    grandparent = ( parent - 1) / 2 ;
		}
    }
    else {
    	while ( ( grandparent >= 0 ) and
		        ( items[cur].ngrad < items[grandparent].ngrad) and  items[grandparent].layer == items[cur].layer ){
		    Swap(items,cur,grandparent) ;
		    cur = grandparent ;
		    parent = ( cur - 1) / 2 ;
		    grandparent = ( parent - 1) / 2 ;
		}
	}


}

// min-max delete
void Heap :: MMDelete( int i ) {
  	if ( IsEmpty() ) cout << " heap empty !" << endl ;
	else {
		int root = 0 ;
        cout << "Top	" << i << ":["<<items[root].serial << "]"<< items[root].sname<< items[root].dname << ","<< items[root].type  ;
        cout << ","<< items[root].level << ","<< items[root].ngrad << endl ;
		items[root] = items[Bottom()] ;
		items.pop_back() ;
        MMDRebuild(root) ;
 	}
}

// delete item
void Heap::MinDelete() {

	if ( IsEmpty() ) cout << " heap empty !" << endl ;
	else {
		Data root = items[0] ;
		items[0] = items[Bottom()] ;
		items.pop_back() ;

		MinRebuild(0) ;
	}
}


// rebulid heap
void Heap::MinRebuild( int root ) {
	int child = root * 2 + 1 ; // its left child

	if ( child < items.size() ) {
		int rightchild = child + 1 ;
		if (( rightchild < items.size() ) and (items[rightchild].ngrad < items[child].ngrad ) ) // (min-heap)
			child = rightchild ;  // decide which child is smaller
		if ( items[root].ngrad > items[child].ngrad ) { // if root > child then swap (min-heap)
			Swap(items,root,child) ;
			MinRebuild(child) ;
		}
    }

}

// Min-max rebuild
void Heap::MMDRebuild( int root ) {
	int child = root*2 + 1 ;
	int grandchild = root*4 + 3 ;
	if ( child < items.size() ) {
		int rightchild = child + 1 ;
		if ( (rightchild < items.size() ) and ( items[rightchild].ngrad < items[child].ngrad ))
		  child = rightchild ;
		if ( items[root].ngrad <= items[child].ngrad ) { //  <=  !!!   no need to swap if equal

			if ( grandchild < items.size() ) { //  what i forget

			  int nextgrandchild = grandchild + 1, mingrandchild = grandchild ;

			  while ( nextgrandchild < items.size() and nextgrandchild < root*4 + 7) { // decide which grandchild should swap
		  		if ( items[mingrandchild].ngrad > items[nextgrandchild].ngrad )
	  			  mingrandchild = nextgrandchild ;
				nextgrandchild++ ;

			  }

			  if ( items[root].ngrad > items[mingrandchild].ngrad) {   //  this if  what i forget

			    Swap(items,root,mingrandchild) ;
			    MMDRebuild(mingrandchild) ;
		      }
		    }
		}
		else {
			Swap(items,root,child) ;
			LayerSwap(items,root,child) ;
			MMDRebuild(root) ;
		}
	}

}


// to find the leftmost node in the heap
int Heap::LeftMost() {
	int curnode = 0, prenode = -1 ;  // start at root
	while ( curnode < items.size()){
		prenode = curnode ;
		curnode = curnode * 2 + 1 ;
	}
	return prenode ;
}

void Heap::ShowResult( int cmd) {
	if ( cmd == 1 or cmd == 3) cout << "<min heap>" << endl ;
	else if ( cmd == 2 or cmd == 4 ) cout << "<min-max heap >" << endl ;

	if ( getRoot() != -1  )cout << "root : [" <<items[getRoot()].serial << "] " << items[getRoot()].ngrad << endl ;
	if ( Bottom() != -1 )cout << "bottom : [" <<items[Bottom()].serial << "] " << items[Bottom()].ngrad << endl ;
	if ( LeftMost() != -1 )cout << "leftmost bottom : [" <<items[LeftMost()].serial << "] " << items[LeftMost()].ngrad << endl ;
	if ( IsEmpty() ) cout << "There is nothing in the heap " << endl ;

}


bool Isnum ( char str[99]){
	int i =0;
	while(i < strlen(str)){
		if (str[i]<'0' || str[i]>'9') return 0;
		i++;
	}
	return true ;

}
void Command(  int & cmd ) { // 抓指令
	string ins ;
	cout << "***        Heap Construction        ***" << endl ;
	cout << "* 0. QUIT                             *" << endl ;
	cout << "* 1. Build a min heap                 *" << endl ;
    cout << "* 2. Build a min-max heap             *" << endl ;
    cout << "* 3. Delete a node in min heap        *" << endl ;
    cout << "* 4. Top-K minimums from min-max heap *" << endl ;
	cout << "***************************************"<<endl;
    cout << "Input a command(0, 1, 2, 3, 4):"  ;
	cin >> ins ;
	while ( ins != "0" && ins !="1" && ins != "2" && ins != "3" && ins != "4" ) {

	  cout << "["<<ins << "]" << "Is An Invalid Command Please Try Again !!! " << endl ;
	  cin >> ins ;
    }
    cmd = atoi(ins.c_str());
}
bool Readfile(string fileName,vector<Data> & List) {
  	char ch = '\0' ;
  	int Eof = 0;
  	int i = 0, serial = 0 ;
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

	fclose( infile ) ;
	return success ;

}

