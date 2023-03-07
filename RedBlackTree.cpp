#include <iostream>
using namespace std;



struct Node{
    int data;
    bool isRed;
    Node *left, *right, *parent;

    Node(int data){
        this->data = data;
        isRed = true;
        left = right = parent = nullptr;
    }


};

class RedBlackTree{

    Node *root;

    public: RedBlackTree(){
        root = nullptr;
    }

    void insert(int data){
        Node *node = new Node(data);
        Node *uncle = nullptr;


        treeInsert(node);
        while(node != root && node->parent->isRed){
            if(node->parent == node->parent->parent->left){
                uncle = node->parent->parent->right;
                if(uncle->isRed){
                    // Case 1: Recolor
                    node->parent->isRed = false;
                    uncle->isRed = false;
                    node->parent->parent->isRed = true;
                    node = node->parent->parent;
                }
                else{
                    if(node == node->parent->right){
                        //case 2 left rotate
                        node = node->parent;
                        leftRotate(node);
                    }
                    //case 3 right rotate
                    node->parent->isRed = false;
                    node->parent->parent->isRed = true;
                    rightRotate(node->parent->parent);
                }
            }
            else{
                //swap left and right
                // Same as above with "left" and "right" exchanged
                uncle = node->parent->parent->left;
                if (uncle->isRed) {
                    // Case 1: Recolor
                    node->parent->isRed = false;
                    uncle->isRed = false;
                    node->parent->parent->isRed = true;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->left) {
                        // Case 2: Right rotate
                        node = node->parent;
                        rightRotate(node);
                    }
                    // Case 3: Left rotate
                    node->parent->isRed = false;
                    node->parent->parent->isRed = true;
                    leftRotate(node->parent->parent);
                }
            }
        }
        root->isRed = false;
    }




    void displayTree(){
        inorderTraversal(root);
        cout << "\n";
        printBT(root);
    }

    void treeInsert(Node *newNode){

        if (root == nullptr) {
            root = newNode;
            return;
        }
        Node *curr = root;
        while (true) {
            if (newNode->data < curr->data) {
                if (curr->left == nullptr) {
                    curr->left = newNode;
                    newNode->parent = curr; // set parent pointer
                    break;
                }
                curr = curr->left;
            } else {
                if (curr->right == nullptr) {
                    curr->right = newNode;
                    newNode->parent = curr; // set parent pointer
                    break;
                }
                curr = curr->right;
            }
        }


    }
    Node* leftRotate(Node *node) {
        Node* pivot = node->right;
        node->right = pivot->left;
        if (pivot->left != nullptr) {
            pivot->left->parent = node;
        }
        pivot->parent = node->parent;
        if (node->parent == nullptr) {
            root = pivot;
        } else if (node == node->parent->left) {
            node->parent->left = pivot;
        } else {
            node->parent->right = pivot;
        }
        pivot->left = node;
        node->parent = pivot;
        return pivot; // return new root node
    }

    Node* rightRotate(Node *node) {
        Node* pivot = node->left;
        node->left = pivot->right;
        if (pivot->right != nullptr) {
            pivot->right->parent = node;
        }
        pivot->parent = node->parent;
        if (node->parent == nullptr) {
            root = pivot;
        } else if (node == node->parent->right) {
            node->parent->right = pivot;
        } else {
            node->parent->left = pivot;
        }
        pivot->right = node;
        node->parent = pivot;
        return pivot; // return new root node
    }


    //print method is from stackOverflow users Adrian Schneider and Michael Hauptvogel
    // https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c
    void printBT(const std::string& prefix, const Node* node, bool isLeft)
    {
        if (node != nullptr)
        {
            std::cout << prefix;
            std::cout << (isLeft ? "|--" : "L--");
            // print the value of the node
            char color;
            if(node->isRed){
                 color = 'R';
            }
            else{
                 color = 'B';
            }
            std::cout << node->data << color << std::endl;
            // enter the next tree level - left and right branch
            printBT(prefix + (isLeft ? "|   " : "    "), node->right, true);
            printBT(prefix + (isLeft ? "|   " : "    "), node->left, false);
        }
    }

    void printBT(const Node *node)
    {
        printBT("", node, false);
    }


    void inorderTraversal(Node* node) {
        if (node == nullptr) {
            return;
        }
        inorderTraversal(node->left);
        cout << node->data << " ";
        inorderTraversal(node->right);
    }

    Node* minimumNode(Node* x) {
        while (x->left != nullptr) {
            x = x->left;
        }
        return x;
    }

    void flipColors(Node* node) {
        node->isRed = !node->isRed;
        node->left->isRed = !node->left->isRed;
        node->right->isRed = !node->right->isRed;
    }

    void deleteNode(int key){
        deleteNode(root, key);
    }
    Node* deleteNode(Node* root, int key) {
        if (root == nullptr) {
            return root;
        }

        // Step 1: Perform standard BST delete
        if (key < root->data) {
            root->left = deleteNode(root->left, key);
        } else if (key > root->data) {
            root->right = deleteNode(root->right, key);
        } else {
            // Node to be deleted found
            if (root->left == nullptr && root->right == nullptr) {
                // Case 1: Node is a leaf node
                delete root;
                root = nullptr;
            } else if (root->left == nullptr) {
                // Case 2: Node has only right child
                Node* temp = root;
                root = root->right;
                delete temp;
            } else if (root->right == nullptr) {
                // Case 3: Node has only left child
                Node* temp = root;
                root = root->left;
                delete temp;
            } else {
                // Case 4: Node has both left and right children
                Node* temp = minimumNode(root->right);
                root->data = temp->data;
                root->right = deleteNode(root->right, temp->data);
            }
        }

        // If the tree had only one node then return
        if (root == nullptr) {
            return root;
        }

        // Step 2: Update node color and maintain Red-Black tree properties
        if (root->right != nullptr && root->right->isRed && !root->left->isRed) {
            root = leftRotate(root);
        }
        if (root->left != nullptr && root->left->isRed && root->left->left != nullptr && root->left->left->isRed) {
            root = rightRotate(root);
        }
        if (root->left != nullptr && root->left->isRed && root->right != nullptr && root->right->isRed) {
            flipColors(root);
        }

        return root;
    }



};

int main(){

    RedBlackTree tree = RedBlackTree();

    tree.insert(834);
    tree.insert(807);
  //  tree.insert(512);
    tree.insert(882);
   // tree.insert(127);
    tree.insert(1);
    //tree.insert(675);
    //tree.insert(75);
  /*  tree.insert(216);
    tree.insert(822);
    tree.insert(249);
    tree.insert(114);
    tree.insert(689);
    tree.insert(625);
    tree.insert(974);
    tree.insert(221);
    tree.insert(92);
    tree.insert(374);
    tree.insert(123);
    tree.insert(838);
    tree.insert(930);
    tree.insert(654);
    tree.insert(806);
    tree.insert(234);
    tree.insert(381);*/




    tree.displayTree();



}
