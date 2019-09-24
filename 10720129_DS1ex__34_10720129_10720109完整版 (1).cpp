// 10720129 張書維 10720109 王睿安 
// Input 內容 只接受 小於92的純正整數  5a 5% 5. .1 a1 都判定為Input Error   
#include <stdio.h>
#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <string.h>
struct Fnum {
   unsigned long long int num ; 
   unsigned long long int factor[10] ; 
} ;
char ch = '0' ;
bool Isnum ( char str[99]){
	int i =0;
	while(i < strlen(str)){
		if (str[i]<'0' || str[i]>'9') return 0;
		i++;
	}
	return 1;
}
struct Fnum mynum[100] ;
void Command( 	unsigned long long int & cmd ) {
	char str[99];
	printf( "       Command List\n ----1----iterative method-----\n ----2----recursive method-----\n ----3----------leave----------\n ") ;
   
	scanf( "%s", str) ;
	while ( ! Isnum(str)){
	  printf( "[%s] Is An Invalid Command Please Try Again !!! \n",str);
      scanf( "%s", str) ;
	}
	cmd = atoi(str) ;

	while ( ! ( cmd >= 1 && cmd <=3)) {
	  printf( "[%s] Is An Invalid Command Please Try Again !!! \n",str);
      scanf( "%s", str) ;
      while ( ! Isnum(str)){
	  printf( "[%s] Invalid Command Please Try Again !!! \n",str);
	  scanf( "%s", str) ;
      }
      cmd = atoi(str) ;
	}

}
void Outerloop(int & i, int & outerlp, int & j, int & target) {
	outerlp += 1 ;
	mynum[0].num = 0 ;
	mynum[1].num = 1 ;
	mynum[i].num =mynum[i-1].num + mynum[i-2].num ; 
    unsigned long long int sqr = sqrt(mynum[i].num);
    unsigned long long int innerlp = 0 ;
    while ( sqr != 0 ) {
        if ( mynum[i].num % sqr == 0 ) {
        mynum[i].factor[j] = sqr ;
        j++ ;
        mynum[i].factor[j] = mynum[i].num / sqr ;
        sqr =1;               
        }
        sqr--;
        innerlp += 1 ;
     
	}
    printf("[%d] %llu = %llu * %llu ", outerlp,mynum[i].num,mynum[i].factor[j-1], mynum[i].factor[j] );    
    printf( "( innerloop call times: %llu)\n", innerlp );
    j = 0 ;
	i++ ;
	target -= 1 ;
	innerlp = 0 ;
	if ( target != 0 ) Outerloop(i,outerlp,j,target) ;
} // 
int main() {
	int target, i = 2;
	unsigned long long int t = 1,innerlp = 0 ;
	unsigned long long int sqr = 0;
	unsigned long long int cmd = -1 ;
	mynum[0].num = 0 ;
	mynum[1].num = 1 ;
    int outerlp = 0 ;
    int store, j = 0 ;
	char str[99];	
	Command( cmd) ;
	while ( cmd != 3) { 
	
      printf( "請輸入一個小於92的正整數\n") ; 

	  scanf( "%s", str) ;
      while ( ! Isnum(str)){
		printf( "Input Error Please Try Again!!!\n");
     	scanf( "%s", str) ;
	  }	
	  target = atoi(str);
      while ( target <= 0 || target > 92 ) {
	  	printf( "Your Input Out Of Range !!! \n");
		scanf( "%s", str) ;
		while ( ! Isnum(str)){
	      printf( "Input Error Please Try   Again!!!\n");
		  scanf( "%s", str) ;	
    	}	
        target = atoi(str);
	  }
	
	if ( cmd == 1) {
	 printf( "The result of the iterative method\n");
  	 while ( target != 0) {
	    outerlp += 1 ;
		mynum[i].num =mynum[i-1].num + mynum[i-2].num ; 
	    sqr = sqrt(mynum[i].num);
        while ( sqr !=0) {
            if ( mynum[i].num % sqr == 0 ) {
                mynum[i].factor[j] = sqr ;
                j++ ;
                mynum[i].factor[j] = mynum[i].num / sqr ;
                sqr =1;
                   
            }
             sqr--;
            innerlp += 1 ;
        }
        
        
         
          printf("[%d] %llu = %llu * %llu ", outerlp,mynum[i].num,mynum[i].factor[j-1], mynum[i].factor[j] );
        
   
        
        printf( "( innerloop call times: %llu)\n", innerlp );
        t = 1 ;
        j = 0 ;
		i++ ;
		target -= 1 ;
		innerlp = 0 ;
	  }
	} // if 
	if ( cmd == 2) {
		 printf( "The result of the recursive method\n");

		Outerloop(i, outerlp, j, target ) ;
	}
	i =2 ;
	
	printf( "( outerloop call times: %d)\n", outerlp );
	outerlp = 0 ;
	Command(cmd);
    }
    printf( "Bye Bye ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~") ;
	return 0;
}
