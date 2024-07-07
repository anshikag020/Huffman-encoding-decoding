class Node{
public:
    char c;
    Node *left, *right;

    Node(char c, Node* left, Node* right)
        : c(c), left(left), right(right){}
    
    Node(char c)
        :c(c), left(nullptr), right(nullptr){}
};

void clear_tree(Node* root);

#define PSEUDO_EOF char(128)       
#define CHAR_CODE_SEPARATOR char(129) 
#define CODES_SEPARATOR char(130)    
#define CODE_TEXT_SEPARATOR char(131)