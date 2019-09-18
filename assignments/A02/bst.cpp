 #include <iostream>
 #include <cstring>

using namespace std; 


struct node{
    int val;
    node *left, *right;
    node(){
        val=-1;
        right =nullptr;
        left = nullptr;
    }
};



class bst{
    private:
    node *root;
    void _insert(int key, node *ptr);
    node *search(int key, node *ptr);
    int height(node *root);
    int count(node *root);
  //  void print_node(node *n, string label= " ");
  //  void printgivenlevel(node *root, int level);

  void _Print(node* root){
        if(!root){
            return;
        }

         //preorder
        _Print(root->left);
        cout<<root->val<<" "; //inorder
        _Print(root->right);
        //postorder
    }


    public:
     bst (){
         root = nullptr;
     }

    void insert(int key);
    node *creatleaf(int key);
    int height();

     void Print(){
        _Print(root);
    }
   // void printleveloder();
  //  node *search(int key);
};


node * createleaf(int key){
    node *temp = new node();
    temp->val = key;
    temp->left = nullptr;
    temp->right = nullptr;

    return temp;
}



void bst :: insert(int key){
_insert(key,root);
}




void bst :: _insert(int key, node *ptr){
if (root == nullptr){
    root =createleaf(key);
}
else if(key < ptr -> val){
    if(ptr ->left != nullptr){
        _insert(key, ptr->left);
    }
    else{
        ptr->left = createleaf(key);
    }
}

else if(key > ptr->val){
    if(ptr->right !=nullptr){
        _insert(key, ptr->right);
    }
    else
        ptr->right = createleaf(key);
}
else
    cout << " The key has already been added "<<endl;
}

int bst ::height(){
    return height(root);
}

int bst ::height(node *root){
    if(!root){
        return 0;
    }

    else{
        int left = height(root->left);
        int right = height(root->right);
        if(left > right){
            return left +1;
        }
        else
            return right +1;
    }
}

int bst::count(node *root){
    if(!root){
        return 0;
    }
    else 
    return 1+ count(root->left) + count(root->right);
}

/*
void bst :: print_node(node *n, string label= " "){
    if (label != " "){
        cout << "[" <<label <<"]";
    }
     cout << "[[" << n << "][" << n->val << "]]\n";
        if (n->left)
        {
            cout << "\t|-->[L][[" << n->left << "][" << n->left->val << "]]\n";
        }
        else
        {
            cout << "\t\\-->[L][null]\n";
        }
        if (n->right)
        {
            cout << "\t\\-->[R][[" << n->right << "][" << n->right->val << "]]\n";
        }
        else
        {
            cout << "\t\\-->[R][null]\n";
        }
    
}
*//*
void bst ::printgivenlevel(node *root, int level){
    if(root == nullptr){
        return;
    }
    if(level == 1){
        print_node(root);
    }
    else if(level > 1){
        printgivenlevel(root->left, level - 1);
        printgivenlevel(root->right, level-1);
    }
}*/

/*
void bst :: printleveloder(){
    cout << "begin level order" << endl;
    int h = height(root);
    int i;
    for(i = 1; i<=h; i++){
        printgivenlevel(root, i);
        cout << endl; 
    }
    cout << "end of level order " << endl;
}
*/


int main(){
    bst tree;
 
    tree.insert(38);
    tree.insert(10);
    tree.insert(29);
    tree.insert(27);
    tree.insert(5);
    tree.insert(43);
    tree.insert(36);
    tree.insert(3);
    

    tree.Print();


    cout << tree.height() <<endl;
    
    
    return  0 ;
}