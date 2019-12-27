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
using namespace std ;
struct Queue {
	int OID,Timeout,Arrival ;
	int Duration,Depart,ArriCPU ;
	Queue * next ;
};
typedef Queue * QueuePtr ;

class QueueList{
	
public :
	double size ;
	double readtime,sortingtime, writetime  ;
	Queue * head ;
	Queue * tail ;
	void Enqueue( QueuePtr newNode) ;
	void Dequeue() ;
	bool IsEmpty() ;
	void Reverse() ;
	void ShowQueue() ;
	QueuePtr Gethead() ;
	QueuePtr Getail() ;
	QueuePtr At( int location ) ;
	QueueList() : head(0), tail(0), size(0){} ;
};
typedef QueueList * QueueListPtr ;
class CPU{
	public :
		QueueListPtr Abort,Done,List ;
		QueueListPtr runstate,waitstate ;
		double delay,successrate ;
		int data,time ;
		CPU() {};
		
};
typedef CPU * CPUPtr ;
 bool Readfile( QueueListPtr List, string fileName,int cmd) {  
  	char ch = '\0' ;
  	int Eof = 0,OID,Arrival;
  	int Duration, Timeout;
  	double start,end ;
  	start = clock() ;
    QueuePtr newNode;
  	FILE *infile = NULL ;
  	bool success = false ;
  	if ( cmd == 1)fileName = "input" + fileName + ".txt" ;
  	else if ( cmd == 2) fileName = "sorted" + fileName + ".txt" ;
  	infile = fopen(fileName.c_str(),"r") ;
  	if ( infile == NULL) {
	  cout << fileName + " does not exist"<<endl ;
	  return false ;
    }
    else {
     

    	while ( ch != '\n') fscanf(infile,"%c",&ch) ;
    	while (Eof!=-1) {
    	  newNode= new Queue ;
    	  newNode->next = NULL ;
    	  Eof = fscanf(infile,"%d",&OID) ;
    	  newNode->OID=OID ;
    	  Eof = fscanf( infile,"%d",&Arrival) ;
    	  newNode->Arrival = Arrival ;
    	  Eof = fscanf( infile,"%d",&Duration) ;
    	  newNode->Duration = Duration ;
    	  Eof = fscanf( infile,"%d",&Timeout) ;
    	  newNode->Timeout = Timeout ;
          if ( Eof != -1 )List->Enqueue(newNode) ;
          
		}
	}
	fclose( infile) ;
	if (cmd == 1 )List->ShowQueue() ;
	end = clock() ;
	List->readtime = (end-start)  ;
	return success ;
	
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

	printf( "**** Simulate QUEUES BY SQF *****\n**** ----0---- QUIT   ***********\n**** ------Sorting----- *********\n** ---2---Simulate one QUEUE ****\n") ;
    cout << "Input a command(0, 1, 2):" << endl ; 
	scanf( "%s", str) ;

	while ( ! Isnum(str)){

	  printf( "[%s] Is An Invalid Command Please Try Again !!! \n",str);

      scanf( "%s", str) ;

	}

	cmd = atoi(str) ;



	while ( ! ( cmd >= 0 && cmd <=2)) {

	  printf( "[%s] Is An Invalid Command Please Try Again !!! \n",str);

      scanf( "%s", str) ;

      while ( ! Isnum(str)){

	  printf( "[%s] Invalid Command Please Try Again !!! \n",str);

	  scanf( "%s", str) ;

      }

      cmd = atoi(str) ;

	}



}
bool WriteOutput(CPUPtr cpu,string fileName) {
	
	char ch = '\0' ;
    bool success ;
    double start,end ;
    start = clock() ;
  	fstream file ;
  	fileName = "output1" + fileName + ".txt" ;
  	file.open(fileName.c_str(), ios::out) ;
  	if ( file.fail()) {
	  cout << " Open failure"<<endl ;
	  return false ;
    }
    else {
    	file << "	[Abort job]	" << '\n' ;
    	file << "	OID     Abort	Delay" << '\n' ;
        QueuePtr walk = cpu ->Abort ->head;
        int i = 0 ;
        while ( walk != 0) {
        	file<<"["<<++i<<"]	" << walk->OID << "	" << walk->Depart << "	 "<< walk->Depart-walk->Arrival<< endl ;
        	cpu->delay += walk->Depart-walk->Arrival ;
            walk = walk -> next ;
		}
        i = 0 ;
		file << "	[Done job]	" << '\n' ;
    	file << "	OID     Departure	Delay" << '\n' ;
		walk = cpu->Done->head ;
		while (walk !=0) {
        	file<<"["<<++i<<"]	" << walk->OID << "	" << walk->Depart << "	 "<< walk->Depart-(walk->Arrival+walk->Duration)<< endl ;
        	cpu->delay += walk->Depart-(walk->Arrival+walk->Duration) ;
            walk = walk -> next ;	
		}

		file << "[Average Delay] "<< fixed<< setprecision(2)<< cpu->delay/cpu->data <<"ms"<<endl ;
		
		file << "[Success Rate] " << fixed<< setprecision(2) <<cpu->Done->size/cpu->data *100 << "%"<<endl ;

	}
	

	file.close() ;
	end = clock() ;
	return success ;
	
	
}
bool WriteFile(QueueListPtr List,string fileName) {
	char ch = '\0' ;
    bool success ;
    double start,end ;
    start = clock() ;
  	fstream file ;
  	fileName = "sorted" + fileName + ".txt" ;
  	file.open(fileName.c_str(), ios::out) ;
  	if ( file.fail()) {
	  cout << " Open failure"<<endl ;
	  return false ;
    }
    else {
    	file << "OID     Arrival Duration        TimeOut" << '\n' ;
        QueuePtr walk = List-> head ;
        while ( walk != 0) {
        	file << walk->OID << "	" << walk->Arrival << "	 "<< walk->Duration<<"	"<<walk->Timeout << endl ;
        	walk = walk -> next ;
		}
        
	}
	file.close() ;
	end = clock() ;
	List->writetime = (end-start)   ;
	return success ;
	
}
void Shell( int cmd) {
	int OID,Arrival,Duration;
	int loc,Timeout ;
	double start,end ;
	QueuePtr find,find2 ;
	QueueListPtr List = new QueueList;
	string fileName ;
	cin >> fileName ;
	Readfile( List,fileName,cmd) ;
	start = clock() ;
	for ( int gap = List->size / 2 ; gap>0; gap/=2) {
		for ( int unsort = gap; unsort < List->size;unsort++) {
		find = List->At(unsort) ;
		loc = unsort ;
		OID = find->OID ;
		Arrival = find->Arrival ;
		Duration = find->Duration ;
		Timeout = find->Timeout ;
		find = List->At(loc-gap) ;
		while ( (loc>=gap)&&(find->Arrival >= Arrival)) {		
			if ( find->Arrival == Arrival){	
				if ( find->OID > OID ) {
					find = List->At(loc) ;
			        find2 = List->At(loc-gap) ;
					find->OID = find2->OID ;
			        find->Arrival = find2->Arrival ;
			        find->Duration = find2->Duration ;
			        find->Timeout = find2->Timeout ;
				}
				else break ;
			}
			else {
			find = List->At(loc) ;
			find2 = List->At(loc-gap) ;
			find->OID = find2->OID ;
			find->Arrival = find2->Arrival ;
			find->Duration = find2->Duration ;
			find->Timeout = find2->Timeout ;

            }
            loc-=gap ;
            if ( loc-gap >= 0 )find = List->At(loc-gap) ;
            
		}
		find = List->At(loc) ;
		find->OID = OID ;
		find->Arrival = Arrival ;
		find->Duration = Duration ;
		find->Timeout = Timeout ;
	}
	find = 0 ;
	find2 = 0 ;
	}
	end = clock() ;
	
	system( "pause") ;
	WriteFile(List,fileName) ;
	List->sortingtime = (end-start)  ;
	int read = (int) List->readtime,sort = List->sortingtime,write=List->writetime ;
	printf("Reading data: %d clocks (%f ms).\n",read,List->readtime ) ;
	printf("Sorting data: %d clocks (%f ms).\n",sort,List->sortingtime ) ;
	printf("Writing data: %d clocks (%f ms).\n",write,List->writetime ) ;
	cout << "See  Sorted" << fileName << ".txt" <<endl ;
}

void Simulate(int cmd) {
	int Duration ;
	int  full = 0 ;
	bool next = 0,Abort=0,Done=0;
    CPUPtr cpu = new CPU ; 
    QueuePtr New ;
    cpu -> runstate = new QueueList ;
    cpu-> Abort = new QueueList ;
    cpu -> Done = new QueueList ;
	cpu -> waitstate = new QueueList ;
	string fileName ;
	cin >> fileName ;
	cpu->List = new QueueList ;
	Readfile(cpu->List,fileName,cmd);
    cout << "The simulation is running..." <<endl << "See Output"<<fileName<<".txt"<<endl;
    bool timeout=0,finish=0;
    cpu->time = cpu->data =0 ;
        while (cpu->List->size !=0 || cpu->runstate->size != 0) {
    	if ( cpu->runstate->size != 0) {	
    		 if ( Duration == 0 || cpu->time >= cpu->runstate->head->Timeout) {
			  	if ( Duration  == 0) {	
				   if ( cpu->time <= cpu->runstate->head->Timeout) finish =1;
			       else timeout= 1 ;
			    }
			  	if ( cpu->time == cpu->runstate->head->Timeout ) if ( Duration > 0) timeout = 1 ;
			    if ( cpu->time > cpu->runstate->head->Timeout ) timeout = 1 ;
			   cpu->runstate->head->Depart = cpu->time ;
		  }
		}
		bool next = 0;
		if ( timeout || finish){
			if ( finish) {
                New = cpu->runstate->head ;
			  	cpu->runstate->Dequeue() ;
                New->next = NULL ;
			  	cpu->Done->Enqueue(New) ;
			  	finish = 0 ;
			}
			else if ( timeout){ // run timeout
					New = cpu->runstate->head ;
					cpu->runstate->Dequeue() ;
					New->next = NULL ;
			  	    cpu->Abort->Enqueue(New) ;
			  	    timeout = 0 ;
			}
            next = 1 ;
	    }
        if ( cpu->List->size != 0){
		if ( cpu->time >= cpu->List->head->Arrival){
		    if ( cpu->runstate->size == 0){

		    	if ( cpu->waitstate->size ==0) {
 		    	New = cpu->List->head;
		    	cpu->List->Dequeue() ;	
		    	cpu->data++;

		        }
		        else {
		    
		        	New = cpu->waitstate->head ;
		        	cpu->waitstate->Dequeue() ;
				}
				New->next = NULL;
		        cpu->runstate->Enqueue(New) ;
		        cpu->runstate->head->ArriCPU = cpu->time ;
		        Duration = cpu->runstate->head->Duration ;
			}
			else {

			  if ( cpu->waitstate->size!= 3) {
			  	New = cpu->List->head ;
				cpu->List->Dequeue() ;
			  	New->next = NULL ;
			 	cpu->waitstate->Enqueue(New) ;
			 	cpu->data++;

		  	  }  
			  else {
			  	cpu->List->head->Depart = cpu->time ;
			  	New = cpu->List->head ;
				cpu->List->Dequeue() ;
			  	New->next = NULL ;
				cpu->Abort->Enqueue(New) ;
				cpu->data++;

		     } 

		   }
	      }
	     }	   
	     
		
	    if ( cpu->waitstate->size != 0){
			if ( cpu->runstate->size == 0 ){
				New = cpu->waitstate->head ;
		        cpu->waitstate->Dequeue() ;
				New->next = NULL;
		        cpu->runstate->Enqueue(New) ;
		        cpu->runstate->head->ArriCPU = cpu->time ;
                Duration = cpu->runstate->head->Duration ;
		    
			}
		}
		full =0;
        if ( cpu->List->size !=0) if ( cpu->List->head->Arrival > cpu->time) full=1;
        if ( cpu->List->size == 0 ) full = 1 ;
		if ( cpu-> data == 0) cpu->time ++ ;
		else {
        if ( next == 1 ){

	    if ( cpu->waitstate->size == 0)	{
		   if ( cpu->List->size != 0 ) {
		   	if ( cpu->runstate->size == 0){
		   		if ( cpu->List->head->Arrival > cpu->time)  {
				   
		   		cpu->time++;
		   		Duration--;
		   	    }
			   }
			   else {//run exist
			     if ( cpu->time > cpu->runstate->head->Timeout) Duration-- ;
			   }
   		   }
	     }
		 else {
		  if ( cpu->waitstate->head->Arrival > cpu->time) {
		    cpu->time++ ;
		    Duration-- ;
	 	 }  
	    }
	    }
		else {
		  if ( full)  {
		    cpu->time++ ;
		    Duration-- ;
		  }
	    }
	}
	    

   }
   WriteOutput(cpu,fileName) ;
}
int main() {
	
	int cmd ;
	Command(cmd) ;
	while ( cmd != 0 ) {
		cout << "Input a file number (e.g., 401, 402, 403, ... ) :  " << endl ;
		if ( cmd==1)Shell(cmd) ;
		else Simulate(cmd) ;
		Command(cmd) ;
	}
	return 0;
}

void QueueList :: Enqueue(QueuePtr newNode) {
	if ( IsEmpty()) head = tail = newNode ;
	else {
	tail -> next = newNode ;
	tail = newNode;
    }
    size++ ;
}
void QueueList::Dequeue() {
	if (IsEmpty()) {
		std::cout <<  "Empty QUEUE !!" << endl ;
		return ;
	}
	if ( head ->next != NULL)head = head -> next ;
    else  head = 0 ;
	size-- ;
}
QueuePtr QueueList::Gethead() {
	if ( IsEmpty()) {
		std::cout <<  "Empty QUEUE !!" << endl ;
	    return 0 ;
	}
	return head ;
}
QueuePtr QueueList::Getail() {
	if ( IsEmpty()) {
		std::cout <<  "Empty QUEUE !!" << endl ;
		return 0 ;
	}
	return tail ;	
}
bool QueueList::IsEmpty(){
	if ( size == 0 ) return 1 ;
	else return 0; 
}
QueuePtr QueueList::At(int location) {
	int num = 0 ;
	Queue * find = head ;
	
	while ( num != location) {
		num++ ;
		find = find -> next ;
	}
    return find ;
}
void QueueList::Reverse() {
	QueuePtr recur = head ;
	QueuePtr repre = NULL ;
	QueuePtr precede = head -> next ;
	QueuePtr storeh = head ;
	while ( precede != NULL ) {
	  recur -> next = repre ;
	  repre = recur ;
	  recur = precede ;
	  precede = precede -> next ;
    }
    recur -> next = repre ;
    head = recur;
    tail = storeh ;
}
void QueueList::ShowQueue() {
	int i = 0 ;
	QueuePtr walk = head ;
	cout << "OID     Arrival Duration        TimeOut" << endl ;
	while ( walk != 0) {
		cout << "("<<++i<<")	" << walk ->OID <<"	" << walk->Arrival<<"	"<< walk->Duration<<"	"<< walk->Timeout << endl ;
		
		walk = walk -> next;  
	}
}
