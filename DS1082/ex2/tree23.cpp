#include "tree23.h"
#include <vector>
#include <stdio.h>
#include <iostream>
Tree_2_3 :: Tree_2_3 () {
	
}

Tree_2_3 :: ~ Tree_2_3 () {
	
}

void Tree_2_3::deleted(stack<pointType> & aPath, string name ) {

	
    nodeType * delitem = aPath.top().pnode ;
    if ( this->getNumofNode( root23 ) == 1 && delitem->data[1].rSet.size() == 0) {
		delete root23 ;
		root23 = NULL ;
		return ;
	} 
	pointType curP ;
	aPath.pop() ;
	if ( !aPath.empty() ) curP = aPath.top() ;
    
    cout << "delete "<<delitem->data[0].key ;
	if ( !aPath.empty() ) cout << "it's parent "<<curP.pnode->data[0].key << " "<< curP.pidx <<endl ;
	if ( isbottom(delitem) ) {                                // on leaf 
	    if ( delitem->data[1].rSet.size() != 0 )   {  // current has two item so direct delete the data
	      if ( delitem->data[0].key.compare(name) == 0 ) {  // 
	        delitem->data[0].rSet = delitem->data[1].rSet ;
	        delitem->data[0].key = delitem->data[1].key ;
	      }
	      delitem->data[1].rSet.clear() ;
	    }
	    else {                                                // empty node ! 
	        
			if ( curP.pidx == 0 ) {
				if ( curP.pnode->link[1]->data[1].rSet.size() != 0 ) {  // it's sibling has two item and can give one to it 
					//redistribute() OK
					delitem->data[0].rSet = curP.pnode->data[0].rSet ;
					delitem->data[0].key = curP.pnode->data[0].key ;

					curP.pnode->data[0].rSet = curP.pnode->link[1]->data[0].rSet ;
					curP.pnode->data[0].key  = curP.pnode->link[1]->data[0].key  ;
					curP.pnode->link[1]->data[0].rSet = curP.pnode->link[1]->data[1].rSet ;
					curP.pnode->link[1]->data[0].key  = curP.pnode->link[1]->data[1].key  ;
					curP.pnode->link[1]->data[1].rSet.clear() ;
				}
				else {  // merge 
			        
				    leafMerge( delitem, aPath) ;
				    
				}
			}
			else if ( curP.pidx == 1 ) {
				
				if ( curP.pnode->link[0]->data[1].rSet.size() != 0 ) {  // it's sibling has two item and can give one to it 
					//redistribute() OK
					delitem->data[0].rSet = curP.pnode->data[0].rSet ;
					delitem->data[0].key = curP.pnode->data[0].key ;
					
					curP.pnode->data[0].rSet = curP.pnode->link[0]->data[1].rSet ;
					curP.pnode->data[0].key  = curP.pnode->link[0]->data[1].key  ;
					curP.pnode->link[0]->data[1].rSet.clear() ;
				}
				else {  // merge 
				    
				    leafMerge( delitem, aPath) ;
				
				  
				}
			}
			else if ( curP.pidx == 2 ) {
				if ( curP.pnode->link[1]->data[1].rSet.size() != 0 ) {  // it's sibling has two item and can give one to it 
					//redistribute() OK
					delitem->data[0].rSet = curP.pnode->data[1].rSet ;
					delitem->data[0].key = curP.pnode->data[1].key ;
					curP.pnode->data[1].rSet = curP.pnode->link[1]->data[1].rSet ;
					curP.pnode->data[1].key  = curP.pnode->link[1]->data[1].key  ;
					curP.pnode->link[1]->data[1].rSet.clear() ;
				}
				else {
					leafMerge( delitem, aPath) ;
				}
   			}
   		}
   	}
   else {                  //  non leaf 
     
     if ( delitem->link[1] != NULL ) {     //  actual non leaf
	   
	    curP.pnode = delitem ;

	    nodeType * successor ;
	    
        if ( delitem->data[1].rSet.size() == 0 ) {
          curP.pidx = 1 ;
          aPath.push( curP ) ;
		  successor = leftmost( delitem->link[1], aPath ) ;
		  delitem->data[0] = successor->data[0] ;
	    }
		else {
		  
		 if ( delitem->data[0].key.compare(name) == 0 ) {
		 	curP.pidx = 1 ;
		 	aPath.push( curP ) ;
		 	successor = leftmost( delitem->link[1], aPath ) ;
		 	delitem->data[0] = successor->data[0] ;
		 }
		 else {
		 	curP.pidx = 2 ;
		 	aPath.push( curP ) ;
		 	successor = leftmost( delitem->link[2], aPath ) ;
		 	delitem->data[1] = successor->data[0] ;
		 }
		  

		   
	    }
	    
		
		deleted( aPath, successor->data[0].key) ;
		 
     }
     else {               //  continue to do merge or distribute 
	   
       if (  curP.pidx == 0 ) {
	      if ( curP.pnode->link[1]->data[1].rSet.size() == 0 ) // merge
	        nonLeafMerge( aPath, delitem->link[0], delitem) ;
	      else {         // it's sibling has two 
	        delitem->data[0] = curP.pnode->data[0] ;
	        curP.pnode->data[0] = curP.pnode->link[1]->data[0] ;
	        curP.pnode->link[1]->data[0] = curP.pnode->link[1]->data[1] ;
	        curP.pnode->link[1]->data[1].rSet.clear() ;
	        delitem->link[1] = curP.pnode->link[1]->link[0] ;
	        curP.pnode->link[1]->link[0]->parent = delitem ;
	        curP.pnode->link[1]->link[0] = curP.pnode->link[1]->link[1] ;
	        curP.pnode->link[1]->link[1] = curP.pnode->link[1]->link[2] ;
	        curP.pnode->link[1]->link[2] = NULL ;
		  }
	   }
	   else if ( curP.pidx == 1) {
	   
	   	  if ( curP.pnode->link[0]->data[1].rSet.size() == 0 ) // merge
	        nonLeafMerge( aPath, delitem->link[0], delitem) ;
	      else {         // it's sibling has two 
	 
	        delitem->data[0] = curP.pnode->data[0] ;
	        
	        curP.pnode->data[0] = curP.pnode->link[0]->data[1] ;
	        curP.pnode->link[0]->data[1].rSet.clear() ;
	        delitem->link[1] = delitem->link[0] ;
	        delitem->link[0] = curP.pnode->link[0]->link[2] ;
	        curP.pnode->link[0]->link[2]->parent = delitem ;
	        curP.pnode->link[0]->link[2] = NULL ;
	        
		  }
	   }
	   else { // pidx == 2 
	      if ( curP.pnode->link[1]->data[1].rSet.size() == 0 ) // merge
	        nonLeafMerge( aPath, delitem->link[0], delitem) ;
	      else {         // it's sibling has two 
	        delitem->data[0] = curP.pnode->data[1] ;
	        curP.pnode->data[1] = curP.pnode->link[1]->data[1] ;
	        curP.pnode->link[1]->data[1].rSet.clear() ;
	        delitem->link[1] = delitem->link[0] ;
	        delitem->link[0] = curP.pnode->link[1]->link[2] ;
	        curP.pnode->link[1]->link[2]->parent = delitem ;
	        curP.pnode->link[1]->link[2] = NULL ;
	        
		  }
	   }
     
     }
     
   }
   
}

nodeType * Tree_2_3::leftmost( nodeType * root, stack<pointType> & path  ) {
	pointType curP ;
	nodeType * cur = root ;
	
	while ( cur->link[0] != NULL ) {
	  curP.pnode = cur ;
	  curP.pidx = 0 ;
	  path.push( curP) ;
	  cur = cur->link[0] ;
    }
    
    curP.pnode = cur ;
	curP.pidx = 0 ;
	cout << endl<<curP.pnode->data[0].key <<"	";
	cout << curP.pidx << endl;
	path.push( curP) ;
	return cur ; 
}


void Tree_2_3::leafMerge( nodeType * node, stack<point> & path ) {
	pointType curP = path.top() ;
	if ( curP.pnode->data[1].rSet.size() != 0 ) {  // it's parent has two items
	  delete node ;
	  node = NULL ;
	  if ( curP.pidx == 0) {
	  	
	  	curP.pnode->link[1]->data[1].rSet = curP.pnode->link[1]->data[0].rSet ;
	  	curP.pnode->link[1]->data[1].key = curP.pnode->link[1]->data[0].key ;
	  	curP.pnode->link[1]->data[0].rSet = curP.pnode->data[0].rSet ;
	  	curP.pnode->link[1]->data[0].key = curP.pnode->data[0].key ;
	  	curP.pnode->data[0].rSet = curP.pnode->data[1].rSet ;
	  	curP.pnode->data[0].key = curP.pnode->data[1].key ;
	  	curP.pnode->link[0] = curP.pnode->link[1] ;
	  	curP.pnode->link[1] = curP.pnode->link[2] ;
	  	curP.pnode->link[2] = NULL ;
	  
	  }
	  else if ( curP.pidx == 1) {              // if parent has two it must has three children
	  
	  	curP.pnode->link[0]->data[1].rSet = curP.pnode->data[0].rSet ;
	  	curP.pnode->link[0]->data[1].key = curP.pnode->data[0].key ;
	  	curP.pnode->data[0].rSet = curP.pnode->data[1].rSet ;
	  	curP.pnode->data[0].key  = curP.pnode->data[1].key ;
	  	curP.pnode->link[1] = curP.pnode->link[2] ;
	  
	  }
	  else {  // pidx == 2
	  
	  	curP.pnode->link[1]->data[1].rSet = curP.pnode->data[1].rSet ;
	  	curP.pnode->link[1]->data[1].key = curP.pnode->data[1].key ;
	  	curP.pnode->data[1].rSet.clear() ;
	  	
	  }
	  curP.pnode->link[2] = NULL ;
	  curP.pnode->data[1].rSet.clear() ;
	  
	}
	else {  // / it's parent has only one item 

  
	  if ( curP.pidx == 0 ) {
	  	delete node ;
	  	node = NULL ;
	  	
	  	curP.pnode->link[1]->data[1].rSet = curP.pnode->link[1]->data[0].rSet ;
	  	curP.pnode->link[1]->data[1].key = curP.pnode->link[1]->data[0].key ;
	  	curP.pnode->link[1]->data[0].rSet = curP.pnode->data[0].rSet ;
	  	curP.pnode->link[1]->data[0].key = curP.pnode->data[0].key ;
	  	
	  	curP.pnode->link[0] = curP.pnode->link[1] ;
	  	
	  }
	  else if ( curP.pidx == 1) {
	  	delete node ;
	  	node = NULL ;
	  	curP.pnode->link[0]->data[1].rSet = curP.pnode->data[0].rSet ;
	  	curP.pnode->link[0]->data[1].key = curP.pnode->data[0].key ;
      }
      curP.pnode->link[1] = NULL ;
      if ( curP.pnode->data[0].key == root23->data[0].key) {
      	root23 = curP.pnode->link[0] ;
      	root23->parent = NULL ;
      	delete curP.pnode ; 
      	return ;
	  }
	  else {
	  	
       
        deleted( path, curP.pnode->data[0].key) ;
      }

	  
	}
}

void Tree_2_3::nonLeafMerge( stack<pointType> path, nodeType * addleaf, nodeType * delitem) {
	pointType curP = path.top() ;
	cout << "additem " << addleaf->data[0].key << endl ;
    cout << "delete	"<<delitem->data[0].key << "  it's parent 	" << curP.pnode->data[0].key<< "	" <<  curP.pidx<<endl ;
	if ( curP.pidx == 0 ) {
		if ( curP.pnode->data[1].rSet.size() != 0 ) {  // parent has two items
		  curP.pnode->link[1]->data[1].rSet = curP.pnode->link[1]->data[0].rSet ;
		  curP.pnode->link[1]->data[1].key = curP.pnode->link[1]->data[0].key ;
		  curP.pnode->link[1]->data[0].rSet = curP.pnode->data[0].rSet ;
		  curP.pnode->link[1]->data[0].key = curP.pnode->data[0].key ;
		  curP.pnode->data[0].rSet = curP.pnode->data[1].rSet ;
		  curP.pnode->data[0].key = curP.pnode->data[1].key;
		  curP.pnode->data[1].rSet.clear() ;
		  
		  delete curP.pnode->link[0] ;
		  curP.pnode->link[0] = curP.pnode->link[1] ;
		  curP.pnode->link[1] = curP.pnode->link[2] ;
		  curP.pnode->link[2] = NULL ;
		  
		  curP.pnode->link[0]->link[2] = curP.pnode->link[0]->link[1] ;
		  curP.pnode->link[0]->link[1] = curP.pnode->link[0]->link[0] ;
		  curP.pnode->link[0]->link[0] = addleaf ;
		  addleaf->parent = curP.pnode->link[0]->link[0] ;
		}
		else {  // only one item
		  curP.pnode->link[1]->data[1].rSet = curP.pnode->link[1]->data[0].rSet ;
		  curP.pnode->link[1]->data[1].key = curP.pnode->link[1]->data[0].key ;
		  curP.pnode->link[1]->data[0].rSet = curP.pnode->data[0].rSet ;
		  curP.pnode->link[1]->data[0].key = curP.pnode->data[0].key ;
		  curP.pnode->link[1]->link[2] = curP.pnode->link[1]->link[1] ;
		  curP.pnode->link[1]->link[1] = curP.pnode->link[1]->link[0] ;
		  curP.pnode->link[1]->link[0] = addleaf ;
		  addleaf->parent = curP.pnode->link[1]->link[0] ;
		  delete curP.pnode->link[0] ;
		  curP.pnode->link[0] = curP.pnode->link[1] ;
		  curP.pnode->link[1] = NULL ;
		  
		  if ( curP.pnode->data[0].key == root23->data[0].key ) {
		       
			  root23 = curP.pnode->link[0] ;
			  root23->parent = NULL ;
			  delete curP.pnode ;
			  curP.pnode = NULL ;	
		  }
		  else {
		  
		
		  	deleted( path, curP.pnode->data[0].key) ;
		  }
		}
	}
	
	else if ( curP.pidx == 1) { 
		if ( curP.pnode->data[1].rSet.size() != 0 ) {  // parent has two items
		  curP.pnode->link[0]->data[1].rSet = curP.pnode->data[0].rSet ;
		  curP.pnode->link[0]->data[1].key = curP.pnode->data[0].key ;
		  curP.pnode->data[0].rSet = curP.pnode->data[1].rSet ;
		  curP.pnode->data[0].key = curP.pnode->data[1].key;
		  curP.pnode->data[1].rSet.clear() ;
		  
		  delete curP.pnode->link[1] ;
		  curP.pnode->link[0]->link[2] = addleaf ;
		  addleaf->parent = curP.pnode->link[0]->link[2] ;
		  curP.pnode->link[1] = curP.pnode->link[2] ;
		  curP.pnode->link[2] = NULL ;
		}
		else {  // only one item
		 
		  curP.pnode->link[0]->data[1].rSet = curP.pnode->data[0].rSet ;
		  curP.pnode->link[0]->data[1].key = curP.pnode->data[0].key ;
          
		  curP.pnode->link[0]->link[2] = addleaf ;
		  addleaf->parent = curP.pnode->link[0]->link[2] ;
		  delete curP.pnode->link[1] ;
		  curP.pnode->link[1] = NULL ;
		  if ( curP.pnode->data[0].key == root23->data[0].key ) {
			  root23 = curP.pnode->link[0] ;
			  root23->parent = NULL ;
			  delete curP.pnode ;
			  curP.pnode = NULL ;
		  }
		  else {
		  	deleted( path, curP.pnode->data[0].key) ;
		  }
		}
	
	}
	else { // pidx == 2
	  curP.pnode->link[1]->data[1].rSet = curP.pnode->data[1].rSet ;
	  curP.pnode->link[1]->data[1].key = curP.pnode->data[1].key ;
	  delete curP.pnode->link[2] ;
	  curP.pnode->link[2] = NULL ;
	  curP.pnode->link[1]->link[2] = addleaf ;
	  addleaf->parent = curP.pnode->link[1]->link[2] ;
	}
	
    
}
nodeType * Tree_2_3::deletelocate( string name, stack<pointType> & path ) {
	pointType oneP ;
	int pos ;
	nodeType * cur = root23 ;
	
	while (  true ) {
		oneP.pnode = cur ;
		for ( pos = 0 ; pos < KEY_NUM; pos++) {
			
			if ( ( ! cur->data[pos].rSet.size()) || ( name.compare(cur->data[pos].key) ) < 0 ) // unused slot or  name < key 
		      break ;
		    else if ( !name.compare(cur->data[pos].key )) {  //  name == key 
		      oneP.pidx = pos ;
		      path.push(oneP) ;
		      oneP = path.top() ;
	
		      return cur ;
			}
		}
		oneP.pidx = pos ;
		path.push(oneP) ;
		cur = cur->link[pos] ;
	}
	
	
}

void Tree_2_3 :: insert( int newRid, string newKey ) {
	slotType newSlot ;
	newSlot.key = newKey ;
	newSlot.rSet.push_back(newRid) ;

	if ( root23 == NULL) {
		root23 = createNode( NULL, NULL, NULL, newSlot) ; // the first item 
	}
	else {
	  
		stack<pointType> aPath ; // stack tp keep the search path 
		pointType curP ; 		 // last-visited node at the top of stack 
		blockType blockUp ;      //  a data block received from the split 
		searchPath(newKey,aPath) ;
		if ( !aPath.empty()) {
			curP = aPath.top() ;
			if ( curP.pnode->data[curP.pidx].rSet.size() and  // it's a duplicate 
			   ( !newKey.compare(curP.pnode->data[curP.pidx].key))) {   
			   	curP.pnode->data[curP.pidx].rSet.push_back(newRid) ;
		    }
		    else if ( !curP.pnode->data[KEY_NUM-1].rSet.size())   {
		       insertLeaf(newSlot, curP) ;
		    }
		    else {  								// current node is full need to split 
		    	splitLeaf(newSlot,curP,blockUp) ;   //  split a leaf
				if ( curP.pnode->parent == NULL ) { // root split
				  root23 = createRoot(curP.pnode, blockUp.link, blockUp.slot) ;
			    }
				else {								//  split non-leaf 
				  do {
					aPath.pop() ;
					curP = aPath.top() ;
					if ( !curP.pnode->data[KEY_NUM-1].rSet.size()) {
						insertNonLeaf(curP, blockUp) ; // add a slot into a non-leaf
					
					    break ;
					
					}
					else {  // split a full non-leaf
					    
						splitNonLeaf(curP, blockUp) ; // split a non-leaf
						if ( curP.pnode->parent == NULL) {
							root23 = createRoot(curP.pnode, blockUp.link, blockUp.slot) ;
							break ;
						}
					}
					
					 
				  } while ( true) ;
			    }
			}
 		}
	}

	
}


void Tree_2_3 :: insertNonLeaf( pointType & goal, blockType oneB ) { // add a record into a leaf 



  if ( oneB.slot.key.compare(goal.pnode->data[0].key) >  0 ){  // right side full 
  	
    goal.pnode->link[2] = oneB.link ;
    oneB.link->parent = goal.pnode->link[2] ;
    goal.pnode->data[KEY_NUM-1].rSet = oneB.slot.rSet ;
    goal.pnode->data[KEY_NUM-1].key = oneB.slot.key ;
  }
  else {													  //  left side full 
    goal.pnode->link[2] = goal.pnode->link[1] ;
	goal.pnode->link[1]->parent = goal.pnode->link[2] ; 
  	goal.pnode->link[1] = oneB.link ;
    oneB.link->parent = goal.pnode->link[1] ;
    goal.pnode->data[KEY_NUM-1].rSet = goal.pnode->data[KEY_NUM-2].rSet ;
    goal.pnode->data[KEY_NUM-1].key = goal.pnode->data[KEY_NUM-2].key ;
    goal.pnode->data[KEY_NUM-2].rSet = oneB.slot.rSet ;
    goal.pnode->data[KEY_NUM-2].key = oneB.slot.key ;
  }
}


void Tree_2_3 :: splitNonLeaf( pointType & goal, blockType & oneB ) { // split a non-leaf for an insertion
  slotType buf[PTR_NUM] ;               // keep a full node record 
  nodeType *ptr[PTR_NUM + 1] ;          // keep pointers of children
  int idx = 0 ;
  for ( int i = 0 ; i < PTR_NUM ; i++) {  
    
  	buf[i].rSet = ( i == goal.pidx ) ? oneB.slot.rSet : goal.pnode->data[idx].rSet ;
  	buf[i].key  = ( i == goal.pidx ) ? oneB.slot.key  : goal.pnode->data[idx++].key ;
  	
  } 

  if ( oneB.link->data[0].key.compare(goal.pnode->link[2]->data[0].key ) > 0) {   //  right side full
  
    for ( int i = 0 ; i < PTR_NUM ; i++) {
  	  ptr[i] = goal.pnode->link[i] ;
    }
    ptr[3] = oneB.link ;
  }
  else if ( oneB.link->data[0].key.compare(goal.pnode->link[1]->data[0].key ) < 0){  // lef side full 
  	ptr[1] = oneB.link ;
  	ptr[0] = goal.pnode->link[0] ;
	ptr[2] = goal.pnode->link[1] ;
	ptr[3] = goal.pnode->link[2] ; 
  }
  else {																			// mid full
  	ptr[0] = goal.pnode->link[0] ;
	ptr[1] = goal.pnode->link[1] ;
	ptr[2] = oneB.link ;
	ptr[3] = goal.pnode->link[2] ; 
  }

  goal.pnode->data[0].rSet = buf[0].rSet ;
  goal.pnode->data[0].key  = buf[0].key ;
  goal.pnode->link[0] = ptr[0] ;
  ptr[0]->parent  = goal.pnode->link[0] ;
  goal.pnode->link[1] = ptr[1] ;
  ptr[1]->parent = goal.pnode->link[1] ;
  goal.pnode->link[2] = NULL ;
  
  for ( int i = 1 ; i < KEY_NUM ; i++) {
	goal.pnode->data[i].rSet.clear() ;
  }
  
  oneB.link = createNode(ptr[2],ptr[3],goal.pnode->parent, buf[2]) ;
  oneB.slot.key  = buf[1].key ;
  oneB.slot.rSet = buf[1].rSet ;
}


nodeType * Tree_2_3::createRoot( nodeType * left, nodeType * right , slotType oneSlot) {
 
  nodeType * newRoot = createNode(left, right, NULL, oneSlot) ;
  left->parent = newRoot ;
  right->parent = newRoot ;	
  
  return newRoot ;
}

void Tree_2_3::splitLeaf( slotType newS, pointType & aLeaf, blockType & aBlock ){
	slotType buf[PTR_NUM] ;
	
	int idx = 0 ;
	for ( int i = 0 ; i < PTR_NUM ; i++) {
		buf[i].rSet = ( i == aLeaf.pidx ) ? newS.rSet : aLeaf.pnode->data[idx].rSet ;
		buf[i].key = ( i == aLeaf.pidx ) ? newS.key : aLeaf.pnode->data[idx++].key ;
	}
	aLeaf.pnode->data[0].rSet = buf[0].rSet ;
	aLeaf.pnode->data[0].key  = buf[0].key ;
	for ( int i = 1 ; i < KEY_NUM ; i++) {
		aLeaf.pnode->data[i].rSet.clear() ;
	}
	aBlock.link = createNode(NULL,NULL,aLeaf.pnode->parent, buf[2]) ;
	
	aBlock.slot.rSet = buf[1].rSet ;
	aBlock.slot.key = buf[1].key ;
	
}



void Tree_2_3::insertLeaf( slotType newS, pointType & aLeaf) {
	for ( int i = KEY_NUM - 1 ; i >= aLeaf.pidx; i-- ) { // scan from right to left
	  if ( i > aLeaf.pidx) {
	  	aLeaf.pnode->data[i].rSet = aLeaf.pnode->data[i-1].rSet ;
	  	aLeaf.pnode->data[i].key = aLeaf.pnode->data[i-1].key ;
	  }
	  else if ( i == aLeaf.pidx ) {
	  	aLeaf.pnode->data[i].rSet = newS.rSet ;
	  	aLeaf.pnode->data[i].key = newS.key ;
	  }
	  else break ;
	}
	
}
void Tree_2_3::searchPath( string name, stack<pointType> & path ) {
	pointType oneP ;
	int pos ;
	nodeType * cur = root23 ;
	
	while ( cur != NULL) {
		oneP.pnode = cur ;
		for ( pos = 0 ; pos < KEY_NUM; pos++) {
			
			if ( ( ! cur->data[pos].rSet.size()) || ( name.compare(cur->data[pos].key) ) < 0 ) // unused slot or  name < key 
		      break ;
		    else if ( !name.compare(cur->data[pos].key )) {  //  name == key 
		      oneP.pidx = pos ;
		      path.push(oneP) ;
		      return ;
			}
		}
		oneP.pidx = pos ;
		path.push(oneP) ;
		cur = cur->link[pos] ;
	}
	
	
}

nodeType * Tree_2_3 :: createNode( nodeType * left, nodeType * right , nodeType * parent , slotType newSlot) {

	nodeType * newNode = NULL ;
	try {
		newNode = new nodeType ;
		newNode->data[0].rSet = newSlot.rSet ;  // put the record into the slot 
		newNode->data[1].rSet.clear() ;
		newNode->data[0].key = newSlot.key ;
		newNode->data[1].key = "" ;
		newNode->parent = parent ;
		newNode->link[0] = left ;              
		newNode->link[1] = right ;
		newNode->link[2] = NULL ;
	    
	}  // end try 
	catch ( std::bad_alloc & ba ) {
		std::cerr << std::endl << "bad_alloc caught: " << ba.what() << std::endl ; 
	}  // end catch
	
	return newNode ;
	
}
void Tree_2_3::free23tree( nodeType * root ) {
	if ( root != NULL) {
		free23tree( root->link[0]) ;
		for( int i = 0 ; i < KEY_NUM; i++) {
			if( !root->data[i].rSet.size()) 
			  break;
			free23tree(root->link[i+1]) ;
		}
		delete root ;
	}
}

int Tree_2_3::getHeight() {
	nodeType * cur = root23 ;
	int num = 0 ;
    while ( cur != NULL ) {
		num++ ;
		cur = cur->link[0] ;
	}
	return num ;
}

int Tree_2_3::getNumofNode( nodeType * root ) {
	if ( root == NULL) return 0 ;
	else {
		return 1 + getNumofNode(root->link[2]) + getNumofNode(root->link[1]) + getNumofNode(root->link[0]) ;
	}
	
}

void Tree_2_3::preorder( nodeType * root ) {
	if ( root == NULL ) return ;
	else {
		
		cout << root->data[0].key << " " ;
		if ( root->data[1].rSet.size() != 0 ) 
		  cout << root->data[1].key << endl ;
		preorder(root->link[0]) ;
		preorder(root->link[1]) ;
		preorder(root->link[2]) ;
	}
} 
