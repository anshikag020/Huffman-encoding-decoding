#define ll long long
#include<iostream>
#include<unordered_map>
#include<queue>
#include<string>
#include<fstream>
#include<utility>
#include<sstream>
#include<functional>
#include<bitset>
using namespace std;
#include"Huffman_node.h"
#include"decompress.h"

void read_header(ifstream &input_stream, unordered_map<char, string>& code){
    char ch;
    input_stream.get(ch);
    while(ch != CODE_TEXT_SEPARATOR){
        char ch2;
        input_stream.get(ch2);
        while(ch2 != CODES_SEPARATOR){
            code[ch] += ch2;
            input_stream.get(ch2);
        }
        input_stream.get(ch);
    }
}

Node* create_huffman_tree(unordered_map<char, string>& code){
    Node* root = new Node('\0');
    for(const auto& itr: code){
        Node* curr = root;
        for(int i = 0; i < itr.second.length(); i++){
            if(itr.second[i] == '0'){
                if(!(curr -> left)) curr -> left = new Node('\0');
                curr = curr -> left;
            }
            else if(itr.second[i] == '1'){
                if(!(curr -> right))    curr -> right = new Node('\0');
                curr = curr -> right;
            }
        }
        curr -> c = itr.first;
    }
    return root;
}

void decompress_file(string& text_code, ofstream& output_stream, Node* root){
    Node* curr = root;
    for(char ch: text_code){
        if(curr -> c != '\0'){
            if(curr -> c == PSEUDO_EOF) return;
            output_stream << curr -> c;
            curr = root;
        }
        if(ch == '0')   curr = curr -> left;
        else curr = curr -> right;
    }
}

void decompress_func(string decompress_fname, string output_fname){
    ifstream input_file(decompress_fname);
    if(!input_file.is_open()){
        cout << "No such file exists!\n\n";
        return;
    }

    unordered_map<char, string> code;
    read_header(input_file, code);

    Node* tree_root = create_huffman_tree(code);

    string text_code;
    char ch;
    while(input_file.get(ch)){
        bitset<8> bits(ch);
        text_code += bits.to_string();
    }

    ofstream output_stream(output_fname);

    decompress_file(text_code, output_stream, tree_root);
    output_stream.close();
    clear_tree(tree_root);
}