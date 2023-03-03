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
        Node *parent = nullptr;
        Node *uncle = nullptr;
        Node *current = root;

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
                else if(node == node->parent->right){
                    //case 2 left rotate
                    //case 3 right rotate
                }
            }
            else{
                //swap left and right
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
                if (curr->right == NULL) {
                    curr->right = newNode;
                    newNode->parent = curr; // set parent pointer
                    break;
                }
                curr = curr->right;
            }
        }


    }

    void printBT(const std::string& prefix, const Node* node, bool isLeft)
    {
        if (node != nullptr)
        {
            std::cout << prefix;
            std::cout << (isLeft ? "|--" : "L--");
            // print the value of the node
            std::cout << node->data << std::endl;
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


};

int main(){

    RedBlackTree tree = RedBlackTree();
    tree.insert(5);
    tree.insert(6);
    tree.insert(1);
    tree.insert(1);
    tree.insert(0);
    tree.insert(100);
    tree.insert(30);
    tree.insert(200);
    tree.insert(7);
    tree.displayTree();


}
