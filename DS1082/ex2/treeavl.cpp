#include "treeavl.h"
#include <queue>
Tree_AVL :: Tree_AVL() {
	
}

Tree_AVL :: ~ Tree_AVL() {
	
}

void Tree_AVL::remove( int key ) {    // remove the node that it's key < key 
	treenodeType * del = removelocate( key ) ;
	treenodeType * successorparent ;
	while ( del != NULL ) {
		treenodeType * successor ;
		if ( del->right !=NULL) { // 被刪除節點 有右小孩
	        successor = leftmost(del->right) ; //讓 change 去替代被刪除節點的位置 右子樹的最左端鑑直 即為最接近被刪除節點
	        successorparent = successor->parent ;
            if (successor->right != NULL) {            // 切斷change 前後鏈結 並接上
                    if  (successor->parent != del) {
                        successor->right->parent = successor->parent ;
                        successor->parent->left = successor->right ;
                	}
                    else {
                        successor->right->parent = del ;
                        del->right = successor->right ;
                	}
        	}
            else {
                if (successor->parent == del) del->right = NULL ;
                else successor->parent->left = NULL ;
        	}
            passValue(successor,del) ; // # 將 successor 節點的直傳給被刪除之節點 ;
            delete successor ;
            successor = NULL  ; //# 節點被刪除
        }
        else if (del->left == NULL and del->right == NULL ) {// # 被刪除節點無小孩
            successorparent = del->parent ;
            if  (del->parent != NULL )  {			//# 可以直接刪掉
                if (del->parent->left == del) del->parent->left = NULL  ;
                else if (del->parent->right == del ) del->parent->right = NULL  ;
                delete del ;
                del = NULL ;
        	}
            else {
              
              delete rootAVL ;
			  rootAVL = NULL  ;
			  break ;
			}
    	}
        else if  (del->left != NULL and del->right == NULL) {
            successor = rightmost(del->left) ;
            successorparent = successor->parent ;
            if  (successor->left != NULL) {
                if  (successor->parent != del ){
                    successor->left->parent = successor->parent ;
                    successor->parent->right = successor->left ;
            	}
                else {
                    successor->left->parent = del ;
                    del->left = successor->left ;
            	}
        	}
            else {
                if  (successor->parent->right == successor) successor->parent->right = NULL ;
                else if  ( del->left == successor ) del->left = NULL ;
			}
            passValue(successor,del)  ;
            delete successor ;
            successor = NULL  ;
    	}
    	
    	while ( successorparent != NULL ) {
		  if ( abs(getBF( successorparent)) == 2) 
		    balance( successorparent) ;
		  successorparent = successorparent->parent ;
		} 
		
		del = removelocate( key ) ; 
		
	}
}

void Tree_AVL::passValue( treenodeType * successor, treenodeType * newNode ) {
	newNode->data = successor->data ;
}
treenodeType * Tree_AVL::removelocate( int key) {
	treenodeType * cur = rootAVL ;
	while ( cur != NULL) {
		if ( key >= cur->data.key ) break ;
		cur = cur-> left ;
	}
	return cur ;
}

treenodeType * Tree_AVL::leftmost( treenodeType * root ) {
	treenodeType * cur = root ;
	while ( cur->left != NULL ) 
	  cur = cur->left ;
	return cur ; 
}

treenodeType * Tree_AVL::rightmost( treenodeType * root ) {
	treenodeType * cur = root ;
	while ( cur->right != NULL ) 
	  cur = cur->right ;
	return cur ; 
}
void Tree_AVL::insert( int serial, int key) {

	fieldType newField ;
	newField.rSet.push_back(serial) ;
	newField.key = key ;
	if ( rootAVL == NULL ) {
		rootAVL = createnode( newField) ;
	}
	else {
		
		treenodeType * cur = rootAVL, *pre = NULL ;
		bool isduplicate = false ;
		while ( cur != NULL ) {


			pre = cur ;
	
			if ( key == cur->data.key ) {
				cur->data.rSet.push_back( serial ) ;
				isduplicate = true ;
				break ;
			}
			else if ( key > cur->data.key ) {
				cur = cur-> right ;
	
			}
			else if ( key < cur->data.key ) {
				cur = cur-> left ;
	
			}
		
		}
		
		if ( !isduplicate) {
			
			treenodeType * newNode = createnode(newField) ;
			treenodeType * walk ;
			if ( key > pre->data.key ) 
			  pre->right = newNode ;
			else 
			  pre->left  = newNode ;
            newNode->parent = pre ;
            walk = newNode ;
            while ( walk != NULL ) {
            
				if ( abs( getBF( walk ) ) == 2) 
				  break ;
				walk = walk->parent ;
			}

            
			balance( walk ) ;
		}
		
	}
}

void Tree_AVL::balance( treenodeType * node ) {
	
	if ( node == NULL) return ;  
	     
    treenodeType * parent = node->parent ;

	if ( getBF( node )  == 2)  {
		if ( node->data.key != rootAVL->data.key ) {
		
			if ( getBF( node->left) > 0 )   // LL
		  	 node = rotateLL(node) ;  		
			else   //  LR
		  	 node = rotateLR(node) ;
		  	node->parent = parent ;
		    if ( parent->data.key > node->data.key ) parent->left = node ;
		    else parent->right = node ;
	    }
	    else {
	    	if ( getBF( node->left) > 0 )   // LL
		  	  rootAVL = rotateLL(rootAVL) ;  		
			else   //  LR
		  	  rootAVL = rotateLR(rootAVL) ;
	
		}
	
	}
	else if ( getBF(node) == -2) {
		
		if ( node->data.key != rootAVL->data.key ) {
		  
	    
		  if ( getBF( node->right) < 0 ) 
		    node = rotateRR(node) ;
		  else 
		    node = rotateRL(node) ;
		  node->parent = parent ;
		  if ( parent->data.key > node->data.key ) parent->left = node ;
		  else parent->right = node ;
	    }
	    else {
	    	
	      if ( getBF( node->right) < 0 ) 
		    rootAVL = rotateRR(rootAVL) ;
		  else 
		    rootAVL = rotateRL(rootAVL) ;
		}
	
	}




} 

treenodeType * Tree_AVL::rotateLL( treenodeType * oldroot) {

	treenodeType * newR ;
	newR = oldroot->left ;
	newR->parent = NULL ;
	
	
	if ( newR->right != NULL) {
	  oldroot->left = newR->right ;
	  newR->right->parent = oldroot ;
	}
	else 
	  oldroot->left = NULL ;
	 
	newR->right = oldroot ;
	oldroot->parent = newR ; 
	return newR ;
}

treenodeType * Tree_AVL::rotateRR( treenodeType * oldroot) {
	treenodeType * newR ;
	newR = oldroot->right ;
	newR->parent = NULL ;
	
	if ( newR->left != NULL) {
		oldroot->right = newR->left ;
		newR->left->parent = oldroot ;
	}
	else 
	  oldroot->right = NULL ;
	  

	newR->left = oldroot ;
	oldroot->parent = newR ;
	return newR ;
}

treenodeType * Tree_AVL::rotateLR( treenodeType * root ) {
	treenodeType * newleft = rotateRR( root->left ) ;
	root->left = newleft ;
	newleft->parent = root ;
	return rotateLL( root ) ;
}

treenodeType * Tree_AVL::rotateRL( treenodeType * root ) {
	
    treenodeType * newright = rotateLL( root->right) ;
	root->right =  newright ;
	newright->parent = root ;

	return rotateRR( root ) ;
}

treenodeType * Tree_AVL::createnode( fieldType field) {
	treenodeType * newNode = new treenodeType ;
	newNode->left = NULL ;
	newNode->right = NULL ;
	newNode->parent = NULL ;
	newNode->data = field ;
	return newNode ;
}
int Tree_AVL::getHeight( treenodeType * node) {
	if ( node == NULL ) return 0 ;
	else {
		return 1 + max(getHeight(node->left), getHeight(node->right ) ) ;
	}
}

int Tree_AVL::numofnode( treenodeType * root) {
	if ( root == NULL ) return 0 ;
	else {
		return 1+ numofnode(root->right) + numofnode(root->left) ;
	}
}



void Tree_AVL::top_k_search( int key, vector<Data> List ) {
	vector<int> list, duplicate ;
	int index = 0 ;
	int kth = List.size() - key ;
	inorder(rootAVL,list,key,index,kth,duplicate) ;
	vector<int> printList ;
    int serial = 1 ;
    
    for ( int i = list.size()-1; i >=0 ; i--) {
    	
    	for ( int k = 0 ; k < List.size() ; k++) 
		  if ( List[k].serial == list[i] ) 
		  	printList.push_back(List[k].serial) ; 
		
	}
    for ( int i = duplicate.size()-1 ; i >= 1; i--) {
    	    	
    	for ( int k = 0 ; k < List.size() ; k++) 
		  if ( List[k].serial == duplicate[i] ) 
		  	printList.push_back(List[k].serial) ; 
	}
    
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

void Tree_AVL::inorder(treenodeType * root, vector<int> & list, int key, int & index, int kth,vector<int> & duplicate){
	if ( root == NULL) return ;
	else {


		inorder(root->left,list,key,index,kth,duplicate) ;
		for ( int i = 0 ; i < root->data.rSet.size() ; i++ ) {		
		  index++;
		  if ( index >= kth ) {
		  	if ( list.size() == 0) {
		  		duplicate = root->data.rSet ;
			}
		  	list.push_back( root->data.rSet[i]) ;
		  }
	    }
        
		inorder(root->right,list,key,index,kth,duplicate) ;
	}
}


