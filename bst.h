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
    float bestValueCost;
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

    while( count <= noOfTotalNodes ) 
    {
        duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

        if (duration > 600)
            return trPr;


        Node<T>* newNode = new Node<T>;
        newNode->left  = NULL;
        newNode->right = NULL;
        newNode->parentNode = NULL;

        int cost=0;
        int value=0;


        for(int i=0; i<walker->data.size(); i++)
        {
            cost += walker->data[i].getCost();
            value += walker->data[i].getValue();


        }

        if(cost <= knapsack.getLimit() && value >= trPr.bestValue)
        {
            trPr.bestSolution = walker->data;
            trPr.bestValue = value; 
        }

        if(index<=0 && (walker->left!=NULL) && (walker->right!=NULL))
        {    
            trPr.isFinished = true;
            return trPr;
        }
        else if ( moveRight && (walker->right!=NULL))
        {
            index--;
            walker = walker->parentNode;
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
        }
        else if (walker->left == NULL && index < itemList.size())//index is < amount of items
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
        walker->right = NULL;
    }

    
    bool moveRight = false;
    int index = 0; //row
    int noOfTotalNodes =  (pow(2, itemList.size()+1) - 1);
    int count = 1;

    float minimum = 0;

    float minimums[3] = {knapsack.getHighestValue(), knapsack.getLowestCost(), knapsack.getValueCostRatio()};
    for (int i = 0; i < 3; i++)
    {
        if(minimums[i] >= minimum)
            minimum = minimums[i];
    }    


    while( count <= noOfTotalNodes )
    {

        duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

        if (duration > 600)
            return trPr;

        Node<T>* newNode = new Node<T>;
        newNode->left  = NULL;
        newNode->right = NULL;
        newNode->parentNode = NULL;

        int cost=0;
        int value=0;


        for(int i=0; i<walker->data.size(); i++)
        {
            cost += walker->data[i].getCost();
            value += walker->data[i].getValue();
        }


        //this is for pruning based on greedyMin
        int possibleVal = value;
        for (int i = index; i < itemList.size(); i++)
            possibleVal += itemList[i].getValue();


        if(cost <= knapsack.getLimit() && value >= trPr.bestValue)//update new Best Solution
        {
            trPr.bestSolution = walker->data;
            trPr.bestValue = value; 
            trPr.bestValueCost = cost;

            if (trPr.bestValue >= minimum)
                minimum = trPr.bestValue;
        }

        if(cost > knapsack.getLimit() || possibleVal < minimum)//prune the tree
        {
            count += (pow(2, (itemList.size()-index+1)) - 2);
            index--;
            walker = walker->parentNode; 
            moveRight=true;
        }

        if(index<=0 && (walker->left!=NULL) && (walker->right!=NULL))
        {    
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
        }
        else if (walker->left == NULL && index < itemList.size())//index is < amount of items
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
