// 10720129�i�Ѻ� 10720109���ͦw  �~���@��W����� 
#include <stdio.h>
#include <stdlib.h>
#include<vector>
#include <cstdio>
#include <string.h>
#include <iostream>
#include <fstream>
using namespace std;
 enum Direction {   // �ѹ���V 
	EAST = 123,
    WEST = 456,
	NORTH = 789,
	SOUTH = 1010
};
class Maze{
  private:
   vector<vector<char> > maze;   //  �x�s�g�c�a�� 
   vector<vector<char> > duplicate ;  // �Ω�_��g�c 
   int x, y ;   // �a�ϭ�l���P�e 
  public :
  	int xwall,ywall ;  // �����ܼ� ���[�F��� 'W' ���� �a�Ϫ����P�e 
  void SetMaze( int i , int j ,char ch ) {  // �]�w ���g�c��T 
  	maze[i][j] = ch ;
  }
  char GetMaze(int i, int j) { // ���o�g�c�a�� ����T 
    return maze[i][j] ;
  }
  void ShowMaze() {    // �L�X �a�� 
    int x=0,y=0;
  	for ( int i = ywall;i!=0;i--) {
  		for ( int j = xwall;j!=0;j--) {
  	        printf( "%c",maze[y][x]);

  			x++ ;
		  }
		printf( "\n") ;
		y++ ;
		x = 0 ;
	  }
   }
  void GetCopy(vector< vector<char> > & routemaze) {  // ���o�g�c�a�� �����|�a�Ϩϥ� 
  	 routemaze = maze ;
  }
  void RecoverMaze() {  // �_��Q�ʹL���� ���g�c�a�� 
  	maze = duplicate ;
  }
  bool LoadMaze( string fileName ) {   // �}���ɮ� Ū���g�c �~���@��'W' ����� 
  	vector<char> maker ;
  	char ch = '\0' ;
  	FILE *infile = NULL ;
  	bool success = false ;
  	fileName = "input" + fileName + ".txt" ;
  	infile = fopen(fileName.c_str(),"r") ;
  	if ( infile == NULL) {
	  cout << fileName + " does not exist"<<endl ;
	  return false ;
    }
  	else {
  		cout << "file open !" << endl ;
  		fscanf(infile,"%d%d",&x,&y);
  		xwall = x + 2 ;
  		ywall = y + 2 ;
  		for ( int i = xwall; i != 0;i--) maker.push_back('W') ;
        maze.push_back(maker);
        maker.clear() ;
        fscanf(infile,"%c",&ch);
        for ( int i = y ; i != 0 ;i--) {
		
		 maker.push_back('W') ;
	  	 for ( int j = x; j !=0; j--) {
			fscanf( infile,"%c",&ch ) ;
			maker.push_back(ch) ;
		 }
		 fscanf( infile,"%c",&ch ) ;
		 maker.push_back('W') ;
		 maze.push_back(maker);
		 maker.clear() ;
		
	    }
	    success = true ;
	}
	for ( int i = xwall; i != 0;i--) maker.push_back('W') ;
    maze.push_back(maker);
    maker.clear() ;
	fclose( infile) ;
	return success ;
  }
  void CleanMaze() {  // �M���g�c�a�� 
  	maze.clear() ;
  }
};
class Player{
	private:
	   int playerx=1 ,playery= 1,playerdirection;  // �ѹ� ��e�y�� �P��V 
	int decide = 0 ;    // ���ܼ� ��Run�� �Ω�M�w���g 
	
	
	public :
	int runtime = 0 ;  // �ѹ������B�� 
	bool stop = false ;
    int times = 0 ;
	int step = 0 ;
	Maze mymaze ;
    vector< vector<int> > route ;  // �Ҧ��g�L�����| 'R' 
    vector<int> xy ;  // �s���Ӹg�L��'R'�y�� 
    vector< vector<int> > gp ;   // �s��Ҧ��g�L��'G' �y�� 
    vector<int> gpxy ;   // �s���Ӹg�L��'G'�y�� 
    vector< vector<char> > routemaze ;  // �Ω� ��X���ĤG�i�a�� R���| 
	void GetCopy() {      // �VMaze ���o��l�a��    
		mymaze.GetCopy(routemaze) ;
	}
	void SetRoute() {  // �]�m 'R' ���| 
		int j = 0 ;
		for ( int i = step;i!=0;i--) {
			routemaze[route[j][0]][route[j][1]] = 'R' ;
			j++ ;
		}                                        
	}
	void SetRouteG () { // �_��Q'R'�л\����'G' 
    	int j = 0 ;
		for ( int i = times;i!=0;i--) {
			routemaze[gp[j][0]][gp[j][1]] = 'G' ;
			j++ ;
		}  		
	}
	void SetG() {   // �_��Q'V'�л\����'G' 
    	int j = 0 ;	
		for ( int i = times;i!=0;i--) {
			mymaze.SetMaze(gp[j][0],gp[j][1],'G') ;
			j++ ;
		}    
	}
	void ShowRoute() {    // �L�X���|�a�� 
    int x=0,y=0;
  	for ( int i = mymaze.ywall;i!=0;i--) {
  		for ( int j = mymaze.xwall;j!=0;j--) {
  	        printf( "%c",routemaze[y][x]);

  			x++ ;
		  }
		printf( "\n") ;
		y++ ;
		x = 0 ;
	  }
    }
	void Initialize () {    // ��l�� �ϥΪ̸�T 
		playerx = 1;
		playery = 1;
		mymaze.SetMaze(1,1,'V') ;
		if ( mymaze.GetMaze(1,2) == 'E') playerdirection = EAST ;
		else playerdirection = WEST ;
	}
	bool CheckforG(bool & end) {   // �T�{�ѹ� �|�P �O�_��'G' �p�G���N���ѹ����L�h �o�䪺�]�p���� �O�ɧ����ѹ����'G' 
		int backx, backy ;
	    if ( mymaze.GetMaze(playery,playerx+1) != 'G'&& mymaze.GetMaze(playery,playerx-1)!= 'G'&&
	         mymaze.GetMaze(playery+1,playerx) != 'G'&& mymaze.GetMaze(playery-1,playerx)!= 'G') return false ;
	    else {
	    	end = true ;
	    	times += 1 ;
	    	if ( mymaze.GetMaze(playery,playerx+1) == 'G') {
	    		playerx++ ;
	    		if ( playerdirection == NORTH) playerdirection = EAST ;
	    		if ( playerdirection == SOUTH) playerdirection = EAST ;
			}
			if ( mymaze.GetMaze(playery,playerx-1) == 'G') {
				playerx-- ;
				if ( playerdirection == NORTH) playerdirection = WEST ;
	    		if ( playerdirection == SOUTH) playerdirection = WEST ;
			}
			if ( mymaze.GetMaze(playery+1,playerx) == 'G' ) {
				playery++ ;
				if ( playerdirection == WEST) playerdirection = NORTH ;
	    		if ( playerdirection == EAST) playerdirection = NORTH ;
			}
			if ( mymaze.GetMaze(playery-1,playerx) == 'G' ) {
				playery--;
				if ( playerdirection == WEST) playerdirection = NORTH ;
	    		if ( playerdirection == EAST) playerdirection = NORTH ;
			}
	    	mymaze.SetMaze(playery,playerx,'V') ;
		    gpxy.push_back(playery) ;
		    gpxy.push_back(playerx) ;
		    
		    gp.push_back(gpxy) ;
		    gpxy.clear() ;


		  return true ;
     	}
	}
	void Run(int cmd, int target, bool & end ) {     // �D�[�c���]�w��V �T�w�|�P��T���� �H�H�����覡�Ө� �J�즺���N�^�Y  
		while ( !stop ) { 
	      runtime+= 1 ;		  
          if ( runtime == 10000 ) stop = true ;  //  �ѹ����g�c���B�� �W����10000�B 
		  step++ ;
		  xy.push_back(playery) ;
		  xy.push_back(playerx) ;
		  route.push_back(xy) ;
		  xy.clear() ;
		  if ( CheckforG(end) == true ) {
		  	target-- ;
		    if ( cmd == 1 )stop = true ;
		    if ( cmd == 2 && target != 0) end = false ;
		    if ( cmd == 2 && target == 0 ) {
		      stop = true ;
		   }
		  }
  		  if ( playerdirection == EAST && !stop  ) {
  			decide = rand()  ;
		  	if ( (mymaze.GetMaze(playery,playerx+1) == 'E' || mymaze.GetMaze(playery,playerx+1) =='V' ) &&
			     (mymaze.GetMaze(playery-1,playerx) == 'E' || mymaze.GetMaze(playery-1,playerx) =='V' ) &&  
				 (mymaze.GetMaze(playery+1,playerx) == 'E' || mymaze.GetMaze(playery+1,playerx) =='V' ) ) {
			  if ( decide % 3 == 2 ) playerx++ ; 
			  else if ( decide % 3 == 1) {
			    playery-- ;
			    playerdirection = NORTH ;
		      }
			  else if ( decide % 3 == 0 ) {
			  	playerdirection = SOUTH ;
			    playery++ ;
		      }
		    }   
		  	else if ( (mymaze.GetMaze(playery,playerx+1) != 'E' && mymaze.GetMaze(playery,playerx+1) !='V' ) &&
			     (mymaze.GetMaze(playery-1,playerx) == 'E' || mymaze.GetMaze(playery-1,playerx) =='V' ) &&  
				 (mymaze.GetMaze(playery+1,playerx) == 'E' || mymaze.GetMaze(playery+1,playerx) =='V' ) ) {				
			    if ( decide % 2 == 0) {
				  playery-- ;
				  playerdirection = NORTH ;
				}
				else {
				    playery++ ;
				    playerdirection = SOUTH ;
				}
			}
		  	else if ( (mymaze.GetMaze(playery,playerx+1) == 'E' || mymaze.GetMaze(playery,playerx+1) =='V' ) &&
			     (mymaze.GetMaze(playery-1,playerx) != 'E' && mymaze.GetMaze(playery-1,playerx) !='V' ) &&  
				 (mymaze.GetMaze(playery+1,playerx) == 'E' || mymaze.GetMaze(playery+1,playerx) =='V' ) ) {				
				if ( decide % 2 != 0) playerx++ ;
				else {
				    playery++ ;
				    playerdirection = SOUTH ;
				}	
			}
		  	else if ( (mymaze.GetMaze(playery,playerx+1) == 'E' || mymaze.GetMaze(playery,playerx+1) =='V' ) &&
			     (mymaze.GetMaze(playery-1,playerx) == 'E' || mymaze.GetMaze(playery-1,playerx) =='V' ) &&  
				 (mymaze.GetMaze(playery+1,playerx) != 'E' || mymaze.GetMaze(playery+1,playerx) !='V' ) ) {				
			    if ( decide % 2 == 0) playerx++ ;
				else {
				    playery-- ;
				    playerdirection = NORTH;
				}	          
			}
		  	else if ( (mymaze.GetMaze(playery,playerx+1) == 'E' || mymaze.GetMaze(playery,playerx+1) =='V' ) &&
			     (mymaze.GetMaze(playery-1,playerx) != 'E' && mymaze.GetMaze(playery-1,playerx) !='V' ) &&  
				 (mymaze.GetMaze(playery+1,playerx) != 'E' && mymaze.GetMaze(playery+1,playerx) !='V' ) ) {				
				 playerx++ ;
			}
		  	else if ( (mymaze.GetMaze(playery,playerx+1) != 'E' && mymaze.GetMaze(playery,playerx+1) !='V' ) &&
			     (mymaze.GetMaze(playery-1,playerx) == 'E' || mymaze.GetMaze(playery-1,playerx) =='V' ) &&  
				 (mymaze.GetMaze(playery+1,playerx) != 'E' && mymaze.GetMaze(playery+1,playerx) !='V' ) ) {              
			  playery-- ;
			  playerdirection = NORTH;
		    }
		  	else if ( (mymaze.GetMaze(playery,playerx+1) != 'E' && mymaze.GetMaze(playery,playerx+1) !='V' ) &&
			     (mymaze.GetMaze(playery-1,playerx) != 'E' && mymaze.GetMaze(playery-1,playerx) !='V' ) &&  
				 (mymaze.GetMaze(playery+1,playerx) == 'E' || mymaze.GetMaze(playery+1,playerx) =='V' ) ) {              
			  playery++ ;
			  playerdirection = SOUTH;
		    }		      
			mymaze.SetMaze(playery,playerx,'V') ;

			if ( ( mymaze.GetMaze(playery,playerx+1)== 'W'|| mymaze.GetMaze(playery,playerx+1)== 'O') &&
			     (mymaze.GetMaze(playery+1,playerx)== 'W'||mymaze.GetMaze(playery+1,playerx)== 'O') &&
				 (mymaze.GetMaze(playery-1,playerx)== 'W'||mymaze.GetMaze(playery-1,playerx)== 'O')  ) playerdirection = WEST ;
		  } 
		  else if ( playerdirection == SOUTH && !stop ) {
		  	  decide = rand() ;
		  	  if ( (mymaze.GetMaze(playery,playerx+1) == 'E' || mymaze.GetMaze(playery,playerx+1) == 'V') &&
				   (mymaze.GetMaze(playery,playerx-1) == 'E' || mymaze.GetMaze(playery,playerx-1) == 'V') &&  
				   (mymaze.GetMaze(playery+1,playerx) == 'E' || mymaze.GetMaze(playery+1,playerx) =='V' )) {
			  if ( decide % 3 == 2 ) playery++ ; 
			  else if ( decide % 3 == 1) {
			    playerx-- ;
			    playerdirection = WEST ;
		      }
			  else if ( decide % 3 == 0 ) {
			  	playerdirection = EAST ;
			    playerx++ ;
		      }
		    }   
		  	else if ( (mymaze.GetMaze(playery,playerx+1) == 'E' || mymaze.GetMaze(playery,playerx+1) == 'V') &&
				   (mymaze.GetMaze(playery,playerx-1) == 'E' || mymaze.GetMaze(playery,playerx-1) == 'V') &&  
				   (mymaze.GetMaze(playery+1,playerx) != 'E' && mymaze.GetMaze(playery+1,playerx) !='V' )) {				
				if ( decide % 2 == 0) {
				  playerx-- ;
				  playerdirection = WEST ;
				}
				else {
				    playerx++ ;
				    playerdirection = EAST ;
				}
			}
		  	else if ( (mymaze.GetMaze(playery,playerx+1) == 'E' || mymaze.GetMaze(playery,playerx+1) == 'V') &&
				   (mymaze.GetMaze(playery,playerx-1) != 'E' && mymaze.GetMaze(playery,playerx-1) != 'V') &&  
				   (mymaze.GetMaze(playery+1,playerx) == 'E' || mymaze.GetMaze(playery+1,playerx) =='V' )) {	
				if ( decide % 2 == 0) playery++ ;
				else {
				    playerx++ ;
				    playerdirection = EAST ;
				}	
			}
		  	else if ( (mymaze.GetMaze(playery,playerx+1) != 'E' && mymaze.GetMaze(playery,playerx+1) != 'V') &&
				   (mymaze.GetMaze(playery,playerx-1) == 'E' || mymaze.GetMaze(playery,playerx-1) == 'V') &&  
				   (mymaze.GetMaze(playery+1,playerx) == 'E' || mymaze.GetMaze(playery+1,playerx) =='V' )) {					
				if ( decide % 2 == 0) playery++ ;
				else {
				    playerx-- ;
				    playerdirection = WEST;
				}	          
			}
		  	else if ( (mymaze.GetMaze(playery,playerx+1) != 'E' && mymaze.GetMaze(playery,playerx+1) != 'V') &&
				   (mymaze.GetMaze(playery,playerx-1) != 'E' && mymaze.GetMaze(playery,playerx-1) != 'V') &&  
				   (mymaze.GetMaze(playery+1,playerx) == 'E' || mymaze.GetMaze(playery+1,playerx) =='V' )) {
				   	
				playery++ ;
	     	}
		  	else if ( (mymaze.GetMaze(playery,playerx+1) != 'E' && mymaze.GetMaze(playery,playerx+1) != 'V') &&
				   (mymaze.GetMaze(playery,playerx-1) == 'E' || mymaze.GetMaze(playery,playerx-1) == 'V') &&  
				   (mymaze.GetMaze(playery+1,playerx) != 'E' && mymaze.GetMaze(playery+1,playerx) !='V' )) {              
			  playerx-- ;
			  playerdirection = WEST;
		    }
		  	else if ( (mymaze.GetMaze(playery,playerx+1) == 'E' || mymaze.GetMaze(playery,playerx+1) == 'V') &&
				   (mymaze.GetMaze(playery,playerx-1) != 'E' && mymaze.GetMaze(playery,playerx-1) != 'V') &&  
				   (mymaze.GetMaze(playery+1,playerx) != 'E' && mymaze.GetMaze(playery+1,playerx) !='V' )) {              
			  playerx++ ;
			  playerdirection = EAST;
		    }		      
			mymaze.SetMaze(playery,playerx,'V') ;

			if ( ( mymaze.GetMaze(playery,playerx+1)== 'W'|| mymaze.GetMaze(playery,playerx+1)== 'O') &&
			     (mymaze.GetMaze(playery+1,playerx)== 'W'||mymaze.GetMaze(playery+1,playerx)== 'O') &&
				 (mymaze.GetMaze(playery,playerx-1)== 'W'||mymaze.GetMaze(playery,playerx-1)== 'O')  ) playerdirection = NORTH ;
		  } 
		  else if ( playerdirection == NORTH && !stop ) {

		  	  decide = rand() ;
		  	  if ( (mymaze.GetMaze(playery,playerx+1) == 'E' || mymaze.GetMaze(playery,playerx+1) =='V' ) &&
				   (mymaze.GetMaze(playery,playerx-1) == 'E' || mymaze.GetMaze(playery,playerx-1) =='V' ) &&  
				   (mymaze.GetMaze(playery-1,playerx) == 'E' || mymaze.GetMaze(playery-1,playerx) =='V' ) ) {
			  if ( decide % 3 == 2 ) playery-- ; 
			  else if ( decide % 3 == 1) {
			    playerx-- ;
			    playerdirection = WEST ;
		      }
			  else if ( decide % 3 == 0 ) {
			  	playerdirection = EAST ;
			    playerx++ ;
		      }
		    }   
		  	else if ( (mymaze.GetMaze(playery,playerx+1) == 'E' || mymaze.GetMaze(playery,playerx+1) =='V' ) &&
				   (mymaze.GetMaze(playery,playerx-1) == 'E' || mymaze.GetMaze(playery,playerx-1) =='V' ) &&  
				   (mymaze.GetMaze(playery-1,playerx) != 'E' && mymaze.GetMaze(playery-1,playerx) !='V' ) ) {
				if ( decide % 2 == 0) {
				  playerx-- ;
				  playerdirection = WEST ;
				}
				else {
				    playerx++ ;
				    playerdirection = EAST ;
				}
			}
		  	else if ( (mymaze.GetMaze(playery,playerx+1) == 'E' || mymaze.GetMaze(playery,playerx+1) =='V' ) &&
				   (mymaze.GetMaze(playery,playerx-1) != 'E' && mymaze.GetMaze(playery,playerx-1) !='V' ) &&  
				   (mymaze.GetMaze(playery-1,playerx) == 'E' || mymaze.GetMaze(playery-1,playerx) =='V' ) ) {			
		    	if ( decide % 2 == 0) playery-- ;
				else {
				    playerx++ ;
				    playerdirection = EAST ;
				}	
			}
		  	else if ( (mymaze.GetMaze(playery,playerx+1) != 'E' && mymaze.GetMaze(playery,playerx+1) !='V' ) &&
				   (mymaze.GetMaze(playery,playerx-1) == 'E' || mymaze.GetMaze(playery,playerx-1) =='V' ) &&  
				   (mymaze.GetMaze(playery-1,playerx) == 'E' || mymaze.GetMaze(playery-1,playerx) =='V' ) ) {				
				if ( decide % 2 == 0) playery-- ;
				else {
				    playerx-- ;
				    playerdirection = WEST;
				}	          
		    }
		  	else if ( (mymaze.GetMaze(playery,playerx+1) != 'E' && mymaze.GetMaze(playery,playerx+1) !='V' ) &&
				   (mymaze.GetMaze(playery,playerx-1) != 'E' && mymaze.GetMaze(playery,playerx-1) !='V' ) &&  
				   (mymaze.GetMaze(playery-1,playerx) == 'E' || mymaze.GetMaze(playery-1,playerx) =='V' ) ) {					
				   playery-- ;
			}
		  	else if ( (mymaze.GetMaze(playery,playerx+1) != 'E' && mymaze.GetMaze(playery,playerx+1) !='V' ) &&
				   (mymaze.GetMaze(playery,playerx-1) == 'E' || mymaze.GetMaze(playery,playerx-1) =='V' ) &&  
				   (mymaze.GetMaze(playery-1,playerx) != 'E' && mymaze.GetMaze(playery-1,playerx) !='V' ) ) {              
			  playerx-- ;
			  playerdirection = WEST;
		    }
		  	else if ( (mymaze.GetMaze(playery,playerx+1) == 'E' || mymaze.GetMaze(playery,playerx+1) =='V' ) &&
				   (mymaze.GetMaze(playery,playerx-1) != 'E' && mymaze.GetMaze(playery,playerx-1) !='V' ) &&  
				   (mymaze.GetMaze(playery-1,playerx) != 'E' && mymaze.GetMaze(playery-1,playerx) !='V' ) ) {              
			  playerx++ ;
			  playerdirection = EAST;
		    }		      
			mymaze.SetMaze(playery,playerx,'V') ;

			if ( ( mymaze.GetMaze(playery,playerx+1)== 'W'|| mymaze.GetMaze(playery,playerx+1)== 'O') &&
			     (mymaze.GetMaze(playery-1,playerx)== 'W'||mymaze.GetMaze(playery-1,playerx)== 'O') &&
				 (mymaze.GetMaze(playery,playerx-1)== 'W'||mymaze.GetMaze(playery,playerx-1)== 'O')  ) playerdirection = SOUTH ;
		  } 
		  else if ( playerdirection == WEST && !stop ) {
		  	decide = rand()  ;
		  	if ((mymaze.GetMaze(playery,playerx-1) == 'E' || mymaze.GetMaze(playery,playerx-1) == 'V' ) &&
			    (mymaze.GetMaze(playery-1,playerx) == 'E' || mymaze.GetMaze(playery-1,playerx) == 'V' ) &&
				(mymaze.GetMaze(playery+1,playerx) == 'E' || mymaze.GetMaze(playery+1,playerx) == 'V' ) ) {
			  if ( decide % 3 == 2 ) playerx-- ; 
			  else if ( decide % 3 == 1) {
			    playery-- ;
			    playerdirection = NORTH ;
		      }
			  else if ( decide % 3 == 0 ) {
			  	playerdirection = SOUTH ;
			    playery++ ;
		      }
		    }   
		  	else if ((mymaze.GetMaze(playery,playerx-1) != 'E' && mymaze.GetMaze(playery,playerx-1) != 'V' ) &&
			    (mymaze.GetMaze(playery-1,playerx) == 'E' || mymaze.GetMaze(playery-1,playerx) == 'V' ) &&
				(mymaze.GetMaze(playery+1,playerx) == 'E' || mymaze.GetMaze(playery+1,playerx) == 'V' ) ) {				
				if ( decide % 2 == 0) {
				  playery-- ;
				  playerdirection = NORTH ;
				}
				else {
				    playery++ ;
				    playerdirection = SOUTH ;
				}
			}
		  	else if ((mymaze.GetMaze(playery,playerx-1) == 'E' || mymaze.GetMaze(playery,playerx-1) == 'V' ) &&
			    (mymaze.GetMaze(playery-1,playerx) != 'E' && mymaze.GetMaze(playery-1,playerx) != 'V' ) &&
				(mymaze.GetMaze(playery+1,playerx) == 'E' || mymaze.GetMaze(playery+1,playerx) == 'V' ) ) {				
			if ( decide % 2 == 0) playerx-- ;
				else {
				    playery++ ;
				    playerdirection = SOUTH ;
				}	
			}
		  	else if ((mymaze.GetMaze(playery,playerx-1) == 'E' || mymaze.GetMaze(playery,playerx-1) == 'V' ) &&
			    (mymaze.GetMaze(playery-1,playerx) == 'E' || mymaze.GetMaze(playery-1,playerx) == 'V' ) &&
				(mymaze.GetMaze(playery+1,playerx) != 'E' && mymaze.GetMaze(playery+1,playerx) != 'V' ) ) {				
			if ( decide % 2 == 0) playerx-- ;
				else {
				    playery-- ;
				    playerdirection = NORTH;
				}	          
			}
		  	else if ((mymaze.GetMaze(playery,playerx-1) == 'E' || mymaze.GetMaze(playery,playerx-1) == 'V' ) &&
			    (mymaze.GetMaze(playery-1,playerx) != 'E' && mymaze.GetMaze(playery-1,playerx) != 'V' ) &&
				(mymaze.GetMaze(playery+1,playerx) != 'E' && mymaze.GetMaze(playery+1,playerx) != 'V' ) ) {				
				playerx-- ;
			}
		  	else if ((mymaze.GetMaze(playery,playerx-1) != 'E' && mymaze.GetMaze(playery,playerx-1) != 'V' ) &&
			    (mymaze.GetMaze(playery-1,playerx) == 'E' || mymaze.GetMaze(playery-1,playerx) == 'V' ) &&
				(mymaze.GetMaze(playery+1,playerx) != 'E' && mymaze.GetMaze(playery+1,playerx) != 'V' ) ) {              
			  playery-- ;
			  playerdirection = NORTH;
		    }
		  	else if ((mymaze.GetMaze(playery,playerx-1) != 'E' && mymaze.GetMaze(playery,playerx-1) != 'V' ) &&
			    (mymaze.GetMaze(playery-1,playerx) != 'E' && mymaze.GetMaze(playery-1,playerx) != 'V' ) &&
				(mymaze.GetMaze(playery+1,playerx) == 'E' || mymaze.GetMaze(playery+1,playerx) == 'V' ) ) {              
			  playery++ ;
			  playerdirection = SOUTH;
		    }		      
			mymaze.SetMaze(playery,playerx,'V') ;

			if ( ( mymaze.GetMaze(playery,playerx-1)== 'W'|| mymaze.GetMaze(playery,playerx-1)== 'O') &&
			     (mymaze.GetMaze(playery+1,playerx)== 'W'||mymaze.GetMaze(playery+1,playerx)== 'O') &&
				 (mymaze.GetMaze(playery-1,playerx)== 'W'||mymaze.GetMaze(playery-1,playerx)== 'O')  ) playerdirection =EAST ;
		  }
		   
	}

     
}
    void Clean() {    // ��l�ƩҦ���T �~�����ϥ� �ӵ{�� 
    	mymaze.CleanMaze() ;
    	route.clear() ;
    	gp.clear() ;
    	times = 0 ;
    	step = 0 ;
    	stop = false ;
        runtime = 0 ;
	}
} ;
bool Isnum ( char str[99]){
	int i =0;
	while(i < strlen(str)){
		if (str[i]<'0' || str[i]>'9') return 0;
		i++;
	}
	return 1;
}
void Command(  int & cmd ) { // ����O 
	char str[99];
	printf( "       Command List\n ----1----Mission 1.Single target-----\n ----2----Mission 2.Mutiple targets-----\n ----3----------leave----------\n ") ;
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
int main()
{
  Player player1 ;
  int cmd = 0 ;
  int target = 0 ;
  bool end = false ;
  string fileName ;
  Command(cmd) ;
  while ( cmd != 3) {
  	do {
  	cout << "Choose the file you want to read. Ex: 201,202,203....." <<endl ;
  	cin >> fileName ;
   } while ( ! player1.mymaze.LoadMaze(fileName) )  ;
  if ( cmd == 1)  {
    player1.GetCopy() ;
    player1.Initialize() ;
    target = 1 ;
    while ( ! end ) {
      player1.Run(cmd,target,end) ;   
      if ( player1.runtime == 10000)  {
       player1.SetG() ;
	   player1.mymaze.ShowMaze() ;
	   cout << "Cannot Find The Goal!!!" << endl;
	  }

 
	  if ( player1.runtime == 10000) end = true ;

	  else {
	  
     
      if ( end == false ) {
      	player1.stop = false ;
      	player1.mymaze.RecoverMaze() ;
      	player1.step = 0 ;
      	player1.route.clear() ;
      	player1.Initialize() ;
	  }
	

    }
    
  }
   if ( player1.runtime == 10000) ;
   else {
   
    player1.SetG() ;
    player1.mymaze.ShowMaze() ;
    player1.SetRoute() ;
    player1.SetRouteG() ;
    player1.ShowRoute() ;
   }
  } // if 
  if ( cmd == 2) {
    player1.GetCopy() ;
    player1.Initialize() ;
    printf( "�п�J�ؼЭӼ�\n") ;
    scanf("%d",&target) ;
    int goalnumber = target ;
    while ( ! end ) {
      player1.Run(cmd,target,end) ;    
      if ( player1.runtime == 10000)  {
        player1.SetG() ;
	    player1.mymaze.ShowMaze() ;
	    printf( "Only Find %d Goals,But Your Target is %d.\n",player1.gp.size(),target) ;
      }
	  if ( player1.runtime == 10000 )	end = true ;
	        
      else {


      if ( end == false ) {
      	player1.stop = false ;
      	player1.mymaze.RecoverMaze() ;
      	player1.step = 0 ;
      	player1.route.clear() ;
      	player1.Initialize() ;
	  }
	

   }
   
 
  }
  if ( player1.runtime != 10000) {
  
    player1.SetG() ;
    player1.mymaze.ShowMaze() ;
    player1.SetRoute() ;
    player1.SetRouteG() ;
    player1.ShowRoute() ; 
  }
 }
  player1.Clean() ;
  end = false ;
  Command(cmd) ;
}
  return 0 ;
}




