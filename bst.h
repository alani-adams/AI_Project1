#include <cstddef>

template <typename T>
struct Node {
    T data;         // Data held at this node in tree
    Node<T>* left;  // Pointer to left child
    Node<T>* right; // Pointer to right child
};

template <typename T>
struct Tree {
    Node<T>* root; // Pointer to topmost (root) node
};

template <typename T>
void initialize(Tree<T> &t)
{
    t.root = NULL;
}

// This is the recursive destroy function, accepting a Node* argument.
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
Tree<T>* insert(Tree<T> &t, T value)
{
    // Create new node to add to tree
    Node<T>* newNode1 = new Node<T>;
    newNode->data  = value;
    newNode->left  = NULL;
    newNode->right = NULL;
    
    /*if( t.root == NULL ) { // empty tree
        t.root = newNode;
        return;
    }
    */

    Node<T>* walker = t.root;
    while( true )
    {
        if( walker->data > value )
        {
            if( walker->left == NULL )
            {
                walker->left = newNode;
                return;
            }
            else
                walker = walker->left;
        }
        else // walker->data < value
        {
            if( walker->right == NULL )
            {
                walker->right = newNode;
                return;
            }
            else
                walker = walker->right;
        }
    }
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
        s << "\t" << N->data << " -> " << N->left->data << ";\n"
        << visualize(N->left);
    }
    else
    {
        s << "\tNLC" << N->data << " [shape=point];\n";
        s << "\t" << N->data << " -> NLC" << N->data << ";\n";
    }
    if (N->right) {
        s << "\t" << N->data << " -> " << N->right->data << ";\n"
        << visualize(N->right);
    }
    else
    {
        s << "\tNRC" << N->data << " [shape=point];\n";
        s << "\t" << N->data << " -> NRC" << N->data << ";\n";
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
