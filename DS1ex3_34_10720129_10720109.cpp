// 10720129 張書維 10720109 王睿安 
#include <stdio.h>
#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <sstream>
using namespace std;

struct Postfix {    //  存放 postfix 的 linked list  
    string store ;
	Postfix * next ;
};
class Stack {    //  計算的stack 
	public :
	int num ;
	void Pop( int & top ) {
	 top-- ;
    }
	void Push( float & fnum) {
	num = fnum ;
    }

};
class Postack {   // infix to postfix 的stack 
	public :
		char  op ;
};
bool Isnum ( vector <char> str){
	int i =0;
	while(i < str.size() ){
		if (str[i]<'0' || str[i]>'9') return 0;
		i++;
	}
	return 1;
}
bool Isnumstr ( char str[60]){
	int i =0;
	while(i < strlen(str) ){
		if (str[i]<'0' || str[i]>'9') return 0;
		i++;
	}
	return 1;
}
bool Isnumber ( char num ) {
	if ( num >= '0' && num <= '9' ) return 1;
	else return 0 ;
}
bool Isoperator( char Operator) {
	if ( Operator== '+'|| Operator== '-'|| Operator== '*'|| Operator== '/') return 1 ;
	else return 0 ;
}
void Command(  int & cmd ) {
	char str[99];
	printf( "       Command List\n ----0.----QUIT------------------------\n ----1.Infix2postfix Transformation---------\n") ;
   
	scanf( "%s", str) ;
	while ( ! Isnumstr(str)){
	  printf( "[%s] Is An Invalid Command Please Try Again !!! \n",str);
      scanf( "%s", str) ;
	}
	cmd = atoi(str) ;

	while ( ! ( cmd == 1 || cmd ==0)) {
	  printf( "[%s] Is An Invalid Command Please Try Again !!! \n",str);
      scanf( "%s", str) ;
      while ( ! Isnumstr(str)){
	  printf( "[%s] Invalid Command Please Try Again !!! \n",str);
	  scanf( "%s", str) ;
      }
      cmd = atoi(str) ;
	}

}
bool CheckforError1( vector <char> infix) {      //  檢查 infix 每一個字元是否為合法符號 0~9 +-*/ 
	for ( int i = infix.size() ;i != 0 ;i--) {
		if ( infix[i-1] != '+'&&infix[i-1] != '-'&&infix[i-1] != '*'&&infix[i-1] != '/'&&infix[i-1] != '('
		     && infix[i-1] != ')'&& ( infix[i-1] < '0' || infix[i-1] > '9' )) {
		     	printf( "Error 1 : %c is not a legitimate character.\n",infix[i-1]) ;
		     	return 1 ;
		     	
			 }
		
	}
	return 0 ;
	
}
bool Check( vector <char> infix ) {    // 檢查是否是個合法的infix 
	
	int length = infix.size(), i = 0;
	int open = 0, close = 0 ;
	if ( Isnum(infix)) return 1 ;
	if ( CheckforError1( infix )) return false ; 
 	for ( int i = infix.size();i != 0 ; i-- ) {
		if ( infix[i-1]== '(') open++ ;
		if ( infix[i-1]== ')') close ++;
	}
	if ( close != open) {
		if ( close > open ) cout << "Error 2 : There is one extra close parenthesis"<<endl ;
		else if ( close < open )  cout << "Error 2 : There is one extra open parenthesis"<<endl ;
		return 0 ;
	}
	if ( length == 1 ) {
		cout << "Error 3 : There exist extra operator" << endl ;
		return 0 ;
	}
	if ( infix[0] == '(') {
		if ( infix[1]== '+'|| infix[1]== '-'|| infix[1]== '*'|| infix[1]== '/') {
			cout << "Error 3 : There exist extra operator" << endl ;
			return 0 ;
		}
		else if ( infix[1]== ')') {
		    cout << "Error 3: it is not infix in the parentheses." << endl ;
		    return 0 ;
		}
		length -- ;
		i++ ;
	}
    else if ( Isnumber(infix[0])) {
    	while ( Isnumber(infix[i])) {		
		  i++ ;
		  length--;
	    }
    	if ( infix[i] == '(') {
		  cout << "Error 3 : There exist extra operand" << endl ;
		  return 0 ;
	    }
	    if ( infix[i]== ')') {
	    	cout <<  "Error 2: there is one extra close parenthesis." << endl ;
            return 0 ;
		}          
		length-- ;
		i++ ;
	}
	else if ( infix[0]== ')') {
			cout <<  "Error 2: there is one extra close parenthesis." << endl ;
            return 0 ;
	}
	else if ( infix[0]== '+'|| infix[0]== '-'|| infix[0]== '*'|| infix[0]== '/') {
		cout << "Error 3 : There exist extra operator" << endl ;
		return 0 ;
	}


	while ( length != 0) {
	  	if ( Isnumber(infix[i]) ) {
	  	 while ( Isnumber(infix[i])&& length != 0 ) {
	  	 	i++;
	  	 	length-- ;
		 }
		 if ( length == 0 ) return 1 ;
		 
		 if ( infix[i] == '(') {
		 	cout << "Error 3 : There exist extra operand" << endl ;
		 	return 0 ;
		 }  	
		}
		else if ( Isoperator(infix[i]) ){
			length--;
			i++ ;
			if ( infix[i]== ')') {
				cout << "Error 3 : There exist extra operator" << endl ;
		 	    return 0 ;
			}
			else if ( Isoperator(infix[i])) {
				cout << "Error 3 : There exist extra operator" << endl ;
		 	    return 0 ;	
			}
		}
		else if ( infix[i]== '(') {
			length-- ;
			i++ ;
			if ( length == 0 ) {
			    cout <<  "Error 2: there exist extra close parenthesis." << endl ;
		     	return 0 ;	
			}
			if ( Isoperator(infix[i])) {
				cout << "Error 3 : There exist extra operator" << endl ;
		 	    return 0 ;
			}
			else if ( infix[i] == ')') {
				cout << "Error 3: it is not infix in the parentheses." << endl ;
		        return 0 ;
			}
			
		}
		else if ( infix[i]== ')') {
			length-- ;
			i++ ;
			if ( length == 0 ) return 1 ;
			if ( Isnumber(infix[i])){
				cout << "Error 3 : There exist extra operand" << endl ;
		 	   return 0 ;	
			}
			else if ( infix[i] == '('){
				cout << "Error 3 : There exist extra operand" << endl ;
		 	   return 0 ;					
			}
 		}
	}
}
int priority(char operater) {   // 給予對應計算符號的權重 
    switch(operater) { 
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        default:            return 0;
    } 
} 
double Arithmetic ( char operater,double num1, double num2, bool & error ) {  // 四則運算 
	switch(operater) {
		case '+' : return num1 + num2 ;
	    case '-' : return num1-num2 ;
		case '*' : return num1*num2 ;
		case '/' :
		 if ( num2 == 0 ) error = true ;
		 else return num1 / num2 ;
		 break ;
	} 
}
void Calculate( Postfix * head, bool & error ) {    // 計算postfix 
    char op = '\0' ;
    Stack * calstack ;
	calstack = new Stack[10] ; 
	Postfix * cur = NULL;
	cur = head ;
	int top = 0 ;
	while ( cur != NULL ) {
		op = cur->store[0]  ;
		
		switch(op) {
			case'+': case'-':case'*':case'/':
			calstack[top-2].num = Arithmetic(op,calstack[top-2].num,calstack[top-1].num, error) ;
            calstack[top-2].Pop(top) ;
			break ;
			default :
			  int num ;
			  stringstream ss ;
			  ss << cur -> store ;
			  ss >> num ;
			  float fnum = num ;
              
			  calstack[top].Push(fnum) ;
			  top ++ ;
		}
		cur = cur -> next ;
		if ( error == true ) cur = NULL ;
	}

	if ( error == true ) 
	  cout << "### Error: Divided by ZERO! ###" << endl << "### It cannot be successfully evaluated! ###" << endl ;
	else cout << "Answer :" << calstack[top-1].num << endl ;
}
bool InfixtoPostfix( vector<char> &infix) {   // infix to postfix
	Postack * postack ;
	postack = new Postack[10] ; 
	bool error = false ;
	Postfix * head = NULL;
	Postfix * cur = NULL ;
	int i,j,top ;
	for ( i = 0,j=0,top=0; i < infix.size();i++){
		 switch(infix[i]) { 
        case '(':            
            postack[++top].op = infix[i]; 
            break; 
        case '+': case '-': case '*': case '/': 
            while(priority(postack[top].op) >= priority(infix[i])) { 
          	  cur -> next = new Postfix() ;
          	  cur = cur -> next ;
          	  cur -> store = postack[top--].op ;
          	  cur -> next = NULL ; 
            } 
            postack[++top].op = infix[i]; 
            
            break; 
        case ')': 
            while(postack[top].op != '(') { 
              
          	  cur -> next = new Postfix() ;
          	  cur = cur -> next ;
          	  cur -> store = postack[top--].op ;
          	  
          	  cur -> next = NULL ; 
            } 
            top--;  
            break; 
        default: 
          if ( head == NULL ) {
	        head = new Postfix() ;
			head -> store += infix[i] ;
			head -> next = NULL ;
			cur = head ;
		  }
          else {
          	if ( Isnumber(infix[i-1]) ) cur -> store += infix[i] ;
          	else {
          	  cur -> next = new Postfix() ;
          	  cur = cur -> next ;
          	  cur -> store += infix[i] ;
          	  cur -> next = NULL ; 
			}
		  }
	}
}
	while(top > 0) { 
	            
        cur -> next = new Postfix() ;
        cur = cur -> next ;
        cur -> store = postack[top--].op ;
        cur -> next = NULL ;
    }
    cur = head ;
    cout << "postfix expression :" ;
    while ( cur -> next != NULL) {
    	cout << cur -> store << "," ;
    	cur = cur -> next ;
	}
	cout << cur -> store << endl ;
	Calculate( head,error) ;

}
int main() {
	vector<char> infix;
	char ch = '\0' ;
	int cmd = -1 ;
	int i=0 ,j ;
	Command(cmd) ;
	if ( cmd == 0 ) return 0 ; 
	scanf( "%c", &ch) ;
	scanf( "%c", &ch) ;
	while ( ch == ' ') scanf( "%c", &ch) ;
	while ( ch != '\n') {
		if ( ch != ' ')infix.push_back(ch) ;
		scanf("%c",&ch) ;
	}
	
	while ( cmd != 0) {
		if (Check(infix)) {
		cout << "It is a legitimate infix expression." << endl ;
		InfixtoPostfix(infix) ;
	    }
		infix.clear() ;
		Command(cmd) ;
		if ( cmd == 0 ) return 0 ; 
        scanf( "%c", &ch) ;
		scanf( "%c", &ch) ;
	    while ( ch == ' ') scanf( "%c", &ch) ;
	    while ( ch != '\n') {
	  	  if ( ch != ' ')infix.push_back(ch) ;
		  scanf("%c",&ch) ;
	    }
	}
} 

