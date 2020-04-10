void Tree_AVL::levelorder( vector<fieldType> & list, int key){
    int num = numofnode( rootAVL ) - key,  i = 0 ; 
    queue<treenodeType*> leftitem;
    leftitem.push(rootAVL);                   
                                    
    while (!leftitem.empty()){    
	    treenodeType *cur = leftitem.front();                   
        i++ ;
        if ( i >= num )
          list.push_back( cur->data )  ;
        
        leftitem.pop();                          
  

        if (cur->left != NULL){   
            leftitem.push(cur->left);
        }
        if (cur->right != NULL){   
            leftitem.push(cur->right);
        }
    }
}
