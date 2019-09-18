/*
Name : Ravishka Rathnasuriya
Professor: Dr. Terry Griffin
Date: 09/18/2019
Assignment: Binary Search Tree to make it complete and/or balanced tree 

Description: In this c++ code I have used a structure to implement the node of the binary search tree and 
then a class to make the binary search tree. Also, there is graph that prints out the tree. Using 
webgraphviz.com, we can check our binary search tree. Dr. Griffin gave us his sample code to use
 and make changes, so that the tree would become a complete/balanced.
Recurssive functions have been used to make the code easy since there are repeating functions. 

For data set of 2^n-1 this code would make the tree a balanced one. Also geeks for geeks and 
stackoverflow helped me to implement some codes and get an idea of how trees work on. 
The function descriptions are explained below. 
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//http://www.webgraphviz.com/

using namespace std;


/*
This is structure which creates a node for the binary tree.
Has two pointers left and right which would help to insert the next node to necessary place.
*/
struct node
{
    int data;
    node *left;
    node *right;
    //default constructor
    node()
    {
        data = -1;
        left = NULL;
        right = NULL;
    }

    //parametrized constructor
    node(int x)
    {
        data = x;
        left = NULL;
        right = NULL;
    }
};

/*
This is the class for binary search tree. All the methods are used to make the tree a balacnced and complete.
Insert the nodes at necessary positions by travesing. Graph is implemented inside this class too. 
*/
class BSTree
{
    //private data and methods of the class
private:
    //to implement the root node
    node *root;

    //this function is a recussive function that will count the number of nodes in left and right side. 
    int count(node *root)
    {
        if (!root)
        {
            return 0;
        }
        else
        {
            return 1 + count(root->left) + count(root->right);
        }
    }

  //private insert function that would take two pointers and traverse the tree.
  //This is a recursive function and also a overloaded function
    void insert(node *&root, node *&temp)
    {
        if (!root)
        {
            root = temp;
        }
        else
        {
            if (temp->data < root->data)  //if value is less than the root, go to left side
            {
                insert(root->left, temp);
            }
            else                       //else if value is greater than the root, go right
            {
                insert(root->right, temp);
            }
        }
    }

//this is the print function that prints the output tree to the text file
    void print_node(ofstream &outfile, node *n, string label = "")
    {
        if (label != "")
        {
            outfile << "[" << label << "]";
        }
        outfile << "[[" << n << "][" << n->data << "]]\n";
        if (n->left)
        {
            outfile << "\t|-->[L][[" << n->left << "][" << n->left->data << "]]\n";
        }
        else
        {
            outfile << "\t\\-->[L][null]\n";
        }
        if (n->right)
        {
            outfile << "\t\\-->[R][[" << n->right << "][" << n->right->data << "]]\n";
        }
        else
        {
            outfile << "\t\\-->[R][null]\n";
        }
    }

    /**
     * type = ['predecessor','successor']
     */
    node *minValueNode(node *root)
    {
        node *current = root;

        if (root->right)
        {
            current = root->right;
            while (current->left != NULL)
            {
                current = current->left;
            }
        }
        else if (root->left)
        {
            current = root->left;
            while (current->right != NULL)
            {
                current = current->right;
            }
        }

        return current;
    }

    //this function will find the height of the tree by traversing both left and right sides
    int height(node *root)
    {
        if (!root)
        {
            return 0;
        }
        else
        {
            int left = height(root->left);
            int right = height(root->right);
            if (left > right)
            {
                return left + 1;
            }
            else
            {
                return right + 1;
            }
        }
    }

    /* Print nodes at a given level */
    void printGivenLevel(node *root, int level, ofstream &outfile)
    {
        if (root == NULL)
            return;
        if (level == 1)
        {
            print_node(outfile, root);
        }
        else if (level > 1)
        {
            printGivenLevel(root->left, level - 1, outfile);
            printGivenLevel(root->right, level - 1, outfile);
        }
    }

    //************************************************************************
    // Method to help create GraphViz code so the expression tree can
    // be visualized. This method prints out all the unique node id's
    // by traversing the tree.
    // Recivies a node pointer to root and performs a simple recursive
    // tree traversal.
    //************************************************************************
    void GraphVizGetIds(node *nodePtr, ofstream &VizOut)
    {
        static int NullCount = 0;
        if (nodePtr)
        {
            GraphVizGetIds(nodePtr->left, VizOut);
            VizOut << "node" << nodePtr->data
                   << "[label=\"" << nodePtr->data << "\\n"
                   //<<"Add:"<<nodePtr<<"\\n"
                   //<<"Par:"<<nodePtr->parent<<"\\n"
                   //<<"Rt:"<<nodePtr->right<<"\\n"
                   //<<"Lt:"<<nodePtr->left<<"\\n"
                   << "\"]" << endl;
            if (!nodePtr->left)
            {
                NullCount++;
                VizOut << "nnode" << NullCount << "[label=\"X\",shape=point,width=.15]" << endl;
            }
            GraphVizGetIds(nodePtr->right, VizOut);
            if (!nodePtr->right)
            {
                NullCount++;
                VizOut << "nnode" << NullCount << "[label=\"X\",shape=point,width=.15]" << endl;
            }
        }
    }

    //************************************************************************
    // This method is partnered with the above method, but on this pass it
    // writes out the actual data from each node.
    // Don't worry about what this method and the above method do, just
    // use the output as your told:)
    //************************************************************************
    void GraphVizMakeConnections(node *nodePtr, ofstream &VizOut)
    {
        static int NullCount = 0;
        if (nodePtr)
        {
            GraphVizMakeConnections(nodePtr->left, VizOut);
            if (nodePtr->left)
                VizOut << "node" << nodePtr->data << "->"
                       << "node" << nodePtr->left->data << endl;
            else
            {
                NullCount++;
                VizOut << "node" << nodePtr->data << "->"
                       << "nnode" << NullCount << endl;
            }

            if (nodePtr->right)
                VizOut << "node" << nodePtr->data << "->"
                       << "node" << nodePtr->right->data << endl;
            else
            {
                NullCount++;
                VizOut << "node" << nodePtr->data << "->"
                       << "nnode" << NullCount << endl;
            }

            GraphVizMakeConnections(nodePtr->right, VizOut);
        }
    }

//this is the public class we implemented.
public:
//default constructor set root to null
    BSTree()
    {
        root = NULL;
    }

//deconstructor
    ~BSTree()
    {
    }

    //this is a overloaded function that used to calculate the no. of nodes
    int count()
    {
        return count(root);
    }

    /* this is the function that used to get the middle values of the 
    sorted vector to using the concept of binay search so that
    it is easy to get a balanced tree. Also,this called the public insert function
    and insert the values in the tree. This is also a recurssive function.
    */
    void treeImplementation(vector<int> v, int a, int b)
    {
        if (a > b)
        {
            return;
        }
        else
        {
            int mid = (a + b) / 2;
            insert(v[mid]);
            treeImplementation(v, a, (mid - 1));
            treeImplementation(v, (mid + 1), b);
        }
    }

    //overloaded public insert function using recussive function
    void insert(int x)
    {
        node *temp = new node(x);
        insert(root, temp);
    }

    //minimum value function.. predecessor and successor
    void minValue(ofstream &outfile)
    {
        print_node(outfile, minValueNode(root), "minVal");
    }

    // compute the height of the tree
    int height()
    {

        return height(root);
    }

    //Computes the top of the tree
    int top()
    {
        if (root)
            return root->data;
        else
            return 0;
    }

    /* Function to line by line print level order traversal a tree*/
    void printLevelOrder(ofstream &outfile)
    {
        outfile << "Begin Level Order===================\n";
        int h = height(root);
        int i;
        for (i = 1; i <= h; i++)
        {
            printGivenLevel(root, i, outfile);
            cout << "\n";
        }
        outfile << "End Level Order===================\n";
    }

    //************************************************************************
    // Recieves a filename to place the GraphViz data into.
    // It then calls the above two graphviz methods to create a data file
    // that can be used to visualize your expression tree.
    //************************************************************************
    void GraphVizOut(string filename)
    {
        ofstream VizOut;
        VizOut.open(filename);
       // VizOut << "Ravishka Rathnasuriya " <<endl<< endl;
        VizOut << "Digraph G {\n";
        GraphVizGetIds(root, VizOut);
        GraphVizMakeConnections(root, VizOut);
        VizOut << "}\n";
        VizOut.close();
    }
};

    //this is the function that does a bubble sort to the vector that the elements are stored in
    void bubbleSort(vector<int> &a){
     bool swapp = true;

     while (swapp){
        swapp = false;
        for (size_t i = 0; i < a.size() - 1; i++)
        {
            if (a[i] > a[i + 1])
            {
                a[i] += a[i + 1];
                a[i + 1] = a[i] - a[i + 1];
                a[i] -= a[i + 1];
                swapp = true;
            }
        }
     }
    }


    //test the sorted vector to make sure. Not needed
    void printVector(vector<int> a){
    for (size_t i = 0; i < a.size(); i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
    }

//this is the main function
int main()
{

    BSTree B;  //instance of the class

    //input file
    ifstream infile;
    infile.open("input.dat");

    //output file
    ofstream outfile;
    outfile.open("output.txt");

    vector<int> mydata;  //my vector

    int data;  

    //read the data from the input file
    while (infile >> data)
    {

        mydata.push_back(data); //store data in the vector
    }

    outfile << "Ravishka Rathnasuriya " << endl<< endl;

    // printVector(mydata);

    bubbleSort(mydata); //call bubble sort function

    // printVector(mydata);

    //call the implementation function
    B.treeImplementation(mydata, 0, mydata.size() - 1);

    //call for print function
    B.printLevelOrder(outfile);
    B.GraphVizOut("before.txt");
    infile.close();
    outfile.close();
    return 0;
}