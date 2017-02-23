#include <cstddef>
#include <math.h>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;


template <typename T>
struct Node {
    T data;         // Data held at this node in tree
    Node<T>* left;  // Pointer to left child
    Node<T>* right; // Pointer to right child
    Node<T>* parentNode; //Pointer to parent
};

template <typename T>
struct Tree {
    Node<T>* root; // Pointer to topmost (root) node
    vector<Item> bestSolution;
    float bestValue;
    bool isFinished;
};

template <typename T>
void initialize(Tree<T> &t)
{
    t.root = new Node<T>;
    vector<Item> temp;
    t.root->data = temp;
    t.bestValue = 0;
    t.root->right = NULL;
    t.root->left = NULL;
    t.isFinished = false;
}

void printItemVector(vector<Item> items)
{
    for (int i=0; i < items.size(); i++){
        cout << "Name: " << items[i].getName() << " Cost:" << items[i].getCost() << " Value: " << items[i].getValue()  << endl;
    }
}

// is the recursive destroy function, accepting a Node* argument.
template <typename T>
void destroy(Node<T>* n)
{
    if( n == NULL )
        return;
    
    destroy(n->left);  // Recursively destroy left subtree
    destroy(n->right); // Recursively destroy right subtree
    delete n;          // Delete this node
}

// This is the function called by the user, to destroy a Tree.
// It will call the recursive function, beginning with the root node.
template <typename T>
void destroy(Tree<T> &t)
{
    destroy(t.root);
    t.root = NULL;
}

/*template <typename T>
Tree<T> insert(Tree<T> &tr, T itemList, Knapsack knapsack)
{
    Node<T>* walker = new Node<T>;
    walker = tr.root;
    
    bool moveRight = false;
    int index = 0; //row
    int noOfTotalNodes =  (pow(2, itemList.size()+1) - 1);
    int count = 1;

    //cout << index << endl;
    //cout << noOfTotalNodes <<endl<<endl;
    while( count <= noOfTotalNodes ) //supposed to be < or <=?
    {
        


        Node<T>* newNode = new Node<T>;
        //newNode->data  = NULL;
        newNode->left  = NULL;
        newNode->right = NULL;
        newNode->parentNode = NULL;

        //cout <<"Index " <<index << endl;
        //cout << "count " <<count << endl;
        //printItemVector(walker->data);
        int cost=0;
        int value=0;
        for(int i=0; i<walker->data.size(); i++)
        {
            cost += walker->data[i].getCost();
            value += walker->data[i].getValue();

        }
        if(cost<= knapsack.getLimit() && value >= tr.bestValue)
        {
            tr.bestSolution = walker->data;
            tr.bestValue = value;
        }


        if(index==0 && (walker->left!=NULL) && (walker->right!=NULL))
        {    
            return tr;
        }
        else if ( moveRight && (walker->right!=NULL))
        {
            index--;
            walker = walker->parentNode;
            //move right is still true
        }
        else if ( moveRight )
        {
            newNode->parentNode = walker;
            walker->right = newNode;
            
            T temp = walker->data;

            walker = walker->right;
            
            walker->data = temp;
            walker->data.push_back(itemList[index]);
            
            moveRight = false;
            count++;
            index++;
            
            //we also need to add new value in vector[index]
        }
        else if (walker->left == NULL && index < itemList.size())//index is < amount of items)
        {
            newNode->parentNode = walker;
            walker->left = newNode;

            T temp = walker->data;
            walker = walker->left;
            walker->data = temp; 
            index++;
            count++;
        }
        else if (index >= itemList.size())
        {
            //we need to move up a row
            moveRight = true;
            walker = walker->parentNode;
            index--;
        }
        

    }
    
    return tr;
}*/
template <typename T>
Tree<T> insert(Tree<T> &trPr, T itemList, Knapsack knapsack)
{

    std::clock_t start;
    double duration = 0;

    start = std::clock();

    Node<T>* walker = new Node<T>;
    walker = trPr.root;

    if (walker->right != NULL)
    {
        //cout << "true" << endl;
        walker->right = NULL;
    }

    
    bool moveRight = false;
    int index = 0; //row
    int noOfTotalNodes =  (pow(2, itemList.size()+1) - 1);
    int count = 1;

    //cout << index << endl;
    //cout << "num of total nodes" << noOfTotalNodes <<endl<<endl;


    /*float minimum = 0;

    float minimums[3] = {knapsack.getHighestValue(), knapsack.getLowestCost(), knapsack.getValueCostRatio()};
    for (int i = 0; i < 3; i++)
    {
        if(minimums[i] >= minimum)
            minimum = minimums[i];
    }    */

    //cout << "Minimum: " << minimum;

    while( count <= noOfTotalNodes ) //supposed to be < or <=?
    {
        duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

        if (duration > 30)
            return trPr;

        //float minimum = min(knapsack.getHighestValue(), knapsack.getLowestCost(), knapsack.getValueCostRatio());

        Node<T>* newNode = new Node<T>;
        //newNode->data  = NULL;
        newNode->left  = NULL;
        newNode->right = NULL;
        newNode->parentNode = NULL;

        //cout <<"Index " <<index << endl;
        //cout << "count " <<count << endl;
        //printItemVector(walker->data);

        int cost=0;
        int value=0;


        for(int i=0; i<walker->data.size(); i++)
        {
            cost += walker->data[i].getCost();
            value += walker->data[i].getValue();
            //cout << "cost " << cost << endl;
            //cout << "value " << value << endl;

        }


        //this is for pruning based on greedyMin
       /* int possibleVal = value;
        for (int i = index; i < itemList.size(); i++)
            possibleVal += itemList[i].getValue();

*/
        if(cost <= knapsack.getLimit() && value >= trPr.bestValue)
        {
            trPr.bestSolution = walker->data;
            trPr.bestValue = value; 
            //cout << "new best solution " << value << endl;

            /*if (trPr.bestValue >= minimum)
                minimum = trPr.bestValue;*/
        }

        /*if(cost > knapsack.getLimit() || possibleVal < minimum)
        {
            count += (pow(2, (itemList.size()-index+1)) - 2);
            index--;
            walker = walker->parentNode; 
            moveRight=true;
            //cout << "prune the tree " << endl;
        }*/



        /*if(index==0 && (walker->left!=NULL) && (walker->right!=NULL))
        {    
            cout << "hello again" <<endl;
            return tr;
        }
        else */
        if(index<=0 && (walker->left!=NULL) && (walker->right!=NULL))
        {    
            //cout << walker->right << endl;
            trPr.isFinished = true;
            return trPr;
        }
        else if ( moveRight && (walker->right!=NULL))
        {
            index--;
            walker = walker->parentNode;
            //move right is still true
        }
        else if ( moveRight )
        {
            newNode->parentNode = walker;
            walker->right = newNode;
            
            T temp = walker->data;

            walker = walker->right;
            
            walker->data = temp;
            walker->data.push_back(itemList[index]);
            
            moveRight = false;
            count++;
            index++;
            //we also need to add new value in vector[index]
        }
        else if (walker->left == NULL && index < itemList.size())//index is < amount of items)
        {
            newNode->parentNode = walker;
            walker->left = newNode;

            T temp = walker->data;
            walker = walker->left;
            walker->data = temp; 
            index++;
            count++;
        }
        else if (index >= itemList.size())
        {
            //we need to move up a row
            moveRight = true;
            walker = walker->parentNode;
            index--;
        }
        

    }
    
    return trPr;
}

template <typename T>
Tree<T> insertPrune(Tree<T> &trPr, T itemList, Knapsack knapsack)
{

    std::clock_t start;
    double duration = 0;

    start = std::clock();

    Node<T>* walker = new Node<T>;
    walker = trPr.root;

    if (walker->right != NULL)
    {
        //cout << "true" << endl;
        walker->right = NULL;
    }

    
    bool moveRight = false;
    int index = 0; //row
    int noOfTotalNodes =  (pow(2, itemList.size()+1) - 1);
    int count = 1;

    //cout << index << endl;
    //cout << "num of total nodes" << noOfTotalNodes <<endl<<endl;


    float minimum = 0;

    float minimums[3] = {knapsack.getHighestValue(), knapsack.getLowestCost(), knapsack.getValueCostRatio()};
    for (int i = 0; i < 3; i++)
    {
        if(minimums[i] >= minimum)
            minimum = minimums[i];
    }    

    //cout << "Minimum: " << minimum;

    while( count <= noOfTotalNodes ) //supposed to be < or <=?
    {

        duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

        if (duration > 600)
            return trPr;

        //float minimum = min(knapsack.getHighestValue(), knapsack.getLowestCost(), knapsack.getValueCostRatio());

        Node<T>* newNode = new Node<T>;
        //newNode->data  = NULL;
        newNode->left  = NULL;
        newNode->right = NULL;
        newNode->parentNode = NULL;

        //cout <<"Index " <<index << endl;
        //cout << "count " <<count << endl;
        //printItemVector(walker->data);

        int cost=0;
        int value=0;


        for(int i=0; i<walker->data.size(); i++)
        {
            cost += walker->data[i].getCost();
            value += walker->data[i].getValue();
            //cout << "cost " << cost << endl;
            //cout << "value " << value << endl;

        }


        //this is for pruning based on greedyMin
        int possibleVal = value;
        for (int i = index; i < itemList.size(); i++)
            possibleVal += itemList[i].getValue();


        if(cost <= knapsack.getLimit() && value >= trPr.bestValue)
        {
            trPr.bestSolution = walker->data;
            trPr.bestValue = value; 
            //cout << "new best solution " << value << endl;

            if (trPr.bestValue >= minimum)
                minimum = trPr.bestValue;
        }

        if(cost > knapsack.getLimit() || possibleVal < minimum)
        {
            count += (pow(2, (itemList.size()-index+1)) - 2);
            index--;
            walker = walker->parentNode; 
            moveRight=true;
            //cout << "prune the tree " << endl;
        }



        /*if(index==0 && (walker->left!=NULL) && (walker->right!=NULL))
        {    
            cout << "hello again" <<endl;
            return tr;
        }
        else */
        if(index<=0 && (walker->left!=NULL) && (walker->right!=NULL))
        {    
            //cout << walker->right << endl;
            trPr.isFinished = true;
            return trPr;
        }
        else if ( moveRight && (walker->right!=NULL))
        {
            index--;
            walker = walker->parentNode;
            //move right is still true
        }
        else if ( moveRight )
        {
            newNode->parentNode = walker;
            walker->right = newNode;
            
            T temp = walker->data;

            walker = walker->right;
            
            walker->data = temp;
            walker->data.push_back(itemList[index]);
            
            moveRight = false;
            count++;
            index++;
            //we also need to add new value in vector[index]
        }
        else if (walker->left == NULL && index < itemList.size())//index is < amount of items)
        {
            newNode->parentNode = walker;
            walker->left = newNode;

            T temp = walker->data;
            walker = walker->left;
            walker->data = temp; 
            index++;
            count++;
        }
        else if (index >= itemList.size())
        {
            //we need to move up a row
            moveRight = true;
            walker = walker->parentNode;
            index--;
        }
        

    }
    
    return trPr;
}

// Return depth at which value appears
//    or -1 if value is not in tree
template <typename T>
int contains(Tree<T> &t, T value)
{
    Node<T>* walker = t.root;
    int depth = 0;
    
    while( walker != NULL )
    {
        if( walker->data == value )
            return depth;
        else if( walker->data > value )
            walker = walker->left;
        else // walker->data < value
            walker = walker->right;
        depth++;
    }
    return -1;
}


// Visualization recursive call per Node
template <typename T>
std::string visualize(Node<T>* N)
{
    std::stringstream s;
    if (N->left) {
        s << "\t" << printItemVector(N->data) << " -> " << printItemVector(N->left->data) << ";\n"
        << visualize(N->left);
    }
    else
    {
        s << "\tNLC" << printItemVector(N->data) << " [shape=point];\n";
        s << "\t" << printItemVector(N->data) << " -> NLC" << printItemVector(N->data) << ";\n";
    }
    if (N->right) {
        s << "\t" << printItemVector(N->data) << " -> " << printItemVector(N->right->data) << ";\n"
        << visualize(N->right);
    }
    else
    {
        s << "\tNRC" << printItemVector(N->data) << " [shape=point];\n";
        s << "\t" << printItemVector(N->data) << " -> NRC" << printItemVector(N->data) << ";\n";
    }
    return s.str();
}

// Output BST as graph (DOT notation) to given filename
template <typename T>
void visualize(Tree<T> t, std::string filename)
{
    std::ofstream fout;
    fout.open(filename.c_str());
    if( fout.is_open() )
    {
        if( !t.root ) //tree empty
            fout << "digraph G {\n"
            << "\tempty [label=\"Tree empty\"]\n}";
        else //tree not empty
            fout << "digraph G {\n"
            << "\tgraph [ordering = \"out\"];\n"
            << "\tnode [shape = circle];\n"
            << visualize(t.root)
            << "}\n";
    }
    fout.close();
}
