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
// t1學校代碼	t2學校名稱	t3科系代碼	t4科系名稱	t5日間∕進修別	t6等級別	t7學生數	t8教師數	stdnum上學年度畢業生數	t9縣市名稱	
//  t10體系別
// 1. 0002	2.國立清華大學	3.520114	4.資訊工程學系	5. D 日	 6. B 學士	7. 565	8. 43	stdnum 117	9.18 新竹市	10. 1 一般
struct Title {
  
  string text1,text2,text3 ;
  string text4,text5,text6 ;
  string text7,text8,text9 ;
  string text10 ;
  int stdnum ;
};
class School{
	public :

  vector <Title> List,bubbleList,selectList ;
  vector <Title> mergeList,quickList,radixList ;
  bool Readfile(string fileName) ;  
  void Bubble() ;
  void Quick(int front,int end) ;
  int Partition(int front,int end);
  void MergeSort( int front,int end) ;
  void Select() ;
  void Merge (int front ,int mid ,int end ) ;
  void Radix() ;
  School() {} ;


};

  bool Isnum ( char str[99]){

	int i =0;

	while(i < strlen(str)){

		if (str[i]<'0' || str[i]>'9') return 0;

		i++;

	}

	return 1;

}
int FindLargest(vector<Title > List ) {
	int max = -1 ;
	for ( int i = 0; i < List.size();i++){
		if ( List[i].stdnum > max ) max = List[i].stdnum ;
		
	}
	return max ;
}
void Command(  int & cmd ) { // 抓指令 
	char str[99];
	printf( "**** Sorting Algorithm *****\n**** ----0---- QUIT   ***********\n**** ---1---Bubble and Select----- *********\n** ---2---Quick and Merge ****\n ****---3---Radix Sort ****\n") ;
    cout << "Input a command(0, 1, 2, 3):" << endl ; 
	scanf( "%s", str) ;
	while ( ! Isnum(str)){
	  printf( "[%s] Is An Invalid Command Please Try Again !!! \n",str);
      scanf( "%s", str) ;
	}
	cmd = atoi(str) ;
	while ( ! ( cmd >= 0 && cmd <=3)) {
	  printf( "[%s] Is An Invalid Command Please Try Again !!! \n",str);
      scanf( "%s", str) ;
      while ( ! Isnum(str)){
	  printf( "[%s] Invalid Command Please Try Again !!! \n",str);
	  scanf( "%s", str) ;
      }
      cmd = atoi(str) ;
	}
}

bool WriteFile(int cmd,string fileName,vector<Title> print) {
	
	char ch = '\0' ;
    bool success ;
    
    switch ( cmd) {
    	case 1 : 
		  fileName = "mybubble_sort" + fileName + ".txt" ;
          break ;
    	case 2 : 
		  fileName = "myselect_sort" + fileName + ".txt" ;
		  break ;
    	case 3 : 
		  fileName = "mymerge_sort" + fileName + ".txt" ;
		  break ;
    	case 4 : 
		  fileName = "myquick_sort" + fileName + ".txt" ;
		  break ;
		case 5 :
		  fileName = "myradix_sort" + fileName + ".txt" ;
          break ;
			
	}
  	fstream file ;
  	file.open(fileName.c_str(), ios::out) ;
  	if ( file.fail()) {
	  cout << " Open failure"<<endl ;
	  return false ;
    }
    else {
    	cout << "data mounts >>>" << print.size() << endl ; 
      for( int i = 0 ; i < print.size();i++){
	  
        file << print[i].text1 << "	"<< print[i].text2 << "	"<<print[i].text3 << "	" ;
        file << print[i].text4 << "	"<< print[i].text5 << "	"<<print[i].text6 << "	" ;
        file << print[i].text7 << "	"<< print[i].text8 << "	"<<print[i].stdnum<< "	" << print[i].text9 << "	"<<print[i].text10 << endl ;
	  
    }
	}
	file.close() ;
	return success ;
}

void Swap( vector<Title> & List,int a,int b){
	swap(List[a],List[b]) ;


}

void M1(School school,string fileName){
 	double start,end ;

	school.bubbleList = school.List ;
	school.selectList = school.List ;
	start = clock() ;
	school.Bubble() ;
	end = clock() ;
	cout << "Bubble Sorting time >" << end-start << endl ;
	school.Select() ; 
	start = clock() ;
	cout << "Select Sorting time >" << start-end << endl ;
	WriteFile(1,fileName,school.bubbleList) ;
	WriteFile(2,fileName,school.selectList) ;
}
void M2(School school,string fileName) {
	double start,end ;
	school.mergeList = school.quickList = school.List ;
	start = clock() ;
	school.MergeSort(0,school.mergeList.size()-1) ;
    end = clock() ;
	cout << "Merge Sorting time >" << end-start  << endl ;
	school.Quick(0,school.quickList.size()-1) ;
	start = clock() ;
	cout << "Quick Sorting time >" << start-end<< endl ;
	WriteFile(3,fileName,school.mergeList) ;
	WriteFile(4,fileName,school.quickList) ;
}
void M3(School school,string fileName) {
	double start,end ;
	school.radixList = school.List ;
	start = clock() ;
	school.Radix() ;
    end = clock() ;
	cout << "Radix Sorting time >" << end-start  << endl ;
	WriteFile(5,fileName,school.radixList) ;
	
}
void Radixsort(int * List, int num){
	int temp[10][num] = {0}; 
    int counter[num] = {0}; 
    int max = -1 ;
    int i;
	for ( int i = 0; i < num;i++)if ( List[i] > max ) max = List[i];
	for (int base = 1;(max /base)>0;base*=10) {
        for(i = 0; i < num; i++) { 
            int lsd = ((List[i] / base) % 10); 
            temp[lsd][counter[lsd]] = List[i]; 
            counter[lsd]++; 
        } 
        
        // 重新排列
        int k = 0;
        for(i = 0; i < 10; i++) { 
            if(counter[i] > 0)  {
                int j;
                for(j = 0; j < counter[i]; j++, k++) { 
                    
					List[k] = temp[i][j]; 
                    
                } 
            }
            counter[i]= 0 ;
        } 
    } 	
	

}
int main() {
	
	int cmd ;
	Command(cmd) ;
	while ( cmd != 0 ) {
		cout << "Input a file number (e.g., 501, 502, 503, ... ) :  " << endl ;
			string fileName ;
	cin >> fileName ;
	School school = School() ;
	school.Readfile(fileName) ;
		M1(school,fileName) ;
		M2(school,fileName) ;
		M3(school,fileName) ;

		Command(cmd) ;
	}
	return 0;
}


void School ::Bubble() {
    bool sorted = true;    
    for (int pass = 1; pass < bubbleList.size() ; ++pass){    
	 sorted =false;
        for (int index = 0; index < bubbleList.size()-pass; index++){    
	      if (bubbleList[index].stdnum < bubbleList[index+1].stdnum) {     
	         Swap(bubbleList,index,index+1);
             
            } // end if
        } // end inner for
    } // end outer for
}
void School ::Select() {
	for ( int i = 0 ; i < selectList.size() ; i++) {
		int max = i ;

		for ( int j = i+1;j<selectList.size();j++) {
			if (selectList[j].stdnum >= selectList[max].stdnum) max = j;
		} 
		if ( i != max) Swap(selectList,i,max) ;
	}
}

void School ::Merge(int front ,int mid ,int end ) {
	vector<Title> Left(mergeList.begin()+front,mergeList.begin()+mid+1), Right(mergeList.begin()+mid+1,mergeList.begin()+end+1 ) ;
	Title temp = Title() ;
	temp.stdnum = -1 ;
	Left.push_back(temp) ;
	Right.push_back(temp) ;
	int idxleft=0,idxright = 0 ;
	for ( int i = front ; i<=end;i++ ) {
		if ( Left[idxleft].stdnum >= Right[idxright].stdnum) mergeList[i] = Left[idxleft++] ;
		else  mergeList[i] = Right[idxright++];
	} 
}
void School ::MergeSort( int front,int end) {
	if ( front < end) {
		int mid = (front +end ) /2 ;
		MergeSort(front,mid);
		MergeSort(mid+1,end);
		Merge(front,mid,end) ;
	}
	
}
int School ::Partition(int front,int end){

	
	int pivot = quickList[front].stdnum ;
	int i = end + 1 ;
	for ( int j = end; j > front ;j--) {
		if ( quickList[j].stdnum < pivot){
			i-- ;
			Swap(quickList,i,j) ;
		}
	}
	i-- ;
	Swap(quickList,i,front) ;
    
	return i ;
}
void School ::Quick(int front,int end) {
  if (front < end ) {
  	 int pivot = Partition(front,end) ;
  	 Quick(front,pivot-1) ;
  	 Quick(pivot+1,end) ;
  }	
}

void School :: Radix() {
    vector< vector<Title> > temp(10,vector<Title> (radixList.size()) )  ; 
    int counter[radixList.size()] = {0} ; 
    int i,j;    
	int maxData = FindLargest(radixList) ;
    for (int base = 1;(maxData /base)>0;base*=10) {
        for(i = 0; i < radixList.size(); i++) { 
            int lsd = ((radixList[i].stdnum / base) % 10); 
            temp[lsd][counter[lsd]] = radixList[i]; 
            counter[lsd]++; 
        } 
        
        // 重新排列
        int k = 0;
        for(i = 0; i < 10; i++) { 
            if(counter[i] > 0)  {
                int j;
                for(j = 0; j < counter[i]; j++, k++) { 
                    radixList[k] = temp[i][j]; 
                    
                } 
            }
            counter[i]= 0 ;
        } 
    } 
	reverse(radixList.begin(),radixList.end())  ;	
} 
 bool School::Readfile(string fileName) {  
    int num,temp,j=0 ;
    bool flag = 0 ;
    double start,end;
    cout << "Data num >" ;
    scanf("%d",&num) ;
    int * data = new int[num] ;
    temp = 	rand() % 17409 + 1;
    data[0] = temp ;
    j++ ;
    int i = num-1 ;
    start = clock() ;
    while ( i !=0) {
    	temp = 	rand() % 17409 + 1;
    	flag = 0 ;
    	for ( int k = j,a=0;k!=0;k--){
    		if ( data[a] == temp) flag = 1;
    		a++ ;
		}
        if ( flag == 0) {    	
		data[j] = temp ;
		j++;
		i-- ;
	   }
	}
	Radixsort(data,num);
  	char ch = '\0' ;
  	int Eof = 0;
  	start = clock() ;
  	FILE *infile = NULL ;
  	bool success = false ;
  	Title New = Title() ;

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
        int idx =0,k=0;
        
    	while ( num !=0) {
        	New = Title() ;
        		while ( ch != '\t') {
        			New.text1 += ch ;
        			fscanf(infile,"%c",&ch ) ;
				}
				fscanf(infile,"%c",&ch ) ;
				while ( ch != '\t') {
        			New.text2 += ch;
        			fscanf(infile,"%c",&ch ) ;
				}
				fscanf(infile,"%c",&ch ) ;
				while ( ch != '\t') {
        			New.text3 += ch;
        			fscanf(infile,"%c",&ch ) ;
				}
				
				fscanf(infile,"%c",&ch ) ;
				while ( ch != '\t') {
        			New.text4 += ch;
        			fscanf(infile,"%c",&ch ) ;
				}
				fscanf(infile,"%c",&ch ) ;
				while ( ch != '\t') {
        			New.text5 += ch;
        			fscanf(infile,"%c",&ch ) ;
				}
				fscanf(infile,"%c",&ch ) ;
				while ( ch != '\t') {
        			New.text6 += ch;
        			fscanf(infile,"%c",&ch ) ;
				}
				fscanf(infile,"%c",&ch ) ;
				while ( ch != '\t') {
        			New.text7 += ch;
        			fscanf(infile,"%c",&ch ) ;
				}
				fscanf(infile,"%c",&ch ) ;
				while ( ch != '\t') {
        			New.text8 += ch;
        			fscanf(infile,"%c",&ch ) ;
				}
				fscanf(infile,"%d",&New.stdnum ) ;
				fscanf(infile,"%c",&ch ) ;
				fscanf(infile,"%c",&ch ) ;
				while ( ch != '\t') {
        			New.text9 += ch;
        			fscanf(infile,"%c",&ch ) ;
				}
				
				fscanf(infile,"%c",&ch ) ;
				while ( ch != '\n'&&Eof != -1  ) {
					
        			New.text10 += ch;
        			Eof = fscanf(infile,"%c",&ch ) ;
        			
        			
				}
			
			k++;
			if (k== data[idx]){
			  List.push_back(New) ;
			  idx++;
			  num--;
		    }
			if ( ch == '\n') Eof = fscanf(infile,"%c",&ch ) ;
		}
		

	
		fclose( infile) ;
	


}
	end = clock() ;
	cout << "Creating Data time >> " << end-start << "	ms" << endl ;
	return success ;
  }

