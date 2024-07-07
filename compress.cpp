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
#include"compress.h"



// returns 0 if successful, else 1
int find_freq_count(string to_compress_fname, unordered_map<char, ll>& freq_count, ll& count){
    ifstream to_compress(to_compress_fname);
    if(!to_compress.is_open()){
        cout << "File not found!\n";
        return 1;
    }
    char ch;
    while(to_compress.get(ch)){
        freq_count[ch]++;
        count++;
    }
    to_compress.close();

    return 0;
}

Node* create_huffman_tree(unordered_map<char,ll>& freq_count, ll count){
                    // freq of subtree,   pointer to root of subtree
    priority_queue<pair<double, Node*> , vector<pair<double, Node*>> , greater<pair<double, Node*>>> pq;

    int n = freq_count.size();
    count++;
    for(const auto& itr: freq_count){
        pq.emplace(make_pair((double)itr.second/count, new Node(itr.first)));
    }
    pq.emplace(make_pair((double)1/count, new Node(PSEUDO_EOF)));
    // pq.emplace(make_pair((double)n/count, new Node(CHAR_CODE_SEPARATOR)));
    // pq.emplace(make_pair((double)n/count, new Node(CODES_SEPARATOR)));
    // pq.emplace(make_pair((double)1/count, new Node(CODE_TEXT_SEPARATOR)));

    while(pq.size() >= 2){
        Node* left = pq.top().second;
        double left_freq = pq.top().first;
        pq.pop();
        Node* right = pq.top().second;
        double right_freq = pq.top().first;
        pq.pop();
        Node* new_node = new Node('\0', left, right);
        pq.emplace(make_pair(left_freq + right_freq, new_node));
    }
    return pq.top().second;
}

void create_code(unordered_map<char, string>& code, Node* root, string curr){
    if(root){
        if(root -> c != '\0'){
            code[root -> c] = curr;
            return;
        }
        create_code(code, root -> left, curr + '0');
        create_code(code, root -> right, curr + '1');
    }
}

void print_header(ofstream& output_stream, unordered_map<char,string>& code){
    for(const auto& itr: code){
        //output_stream << itr.first << CHAR_CODE_SEPARATOR << itr.second << CODES_SEPARATOR;
        output_stream << itr.first << itr.second << CODES_SEPARATOR;
    }
    output_stream << CODE_TEXT_SEPARATOR;
}

void clear_tree(Node* root){
    if(root){
        clear_tree(root -> left);
        clear_tree(root -> right);
        delete root;
    }
}

void print_encoded_text(ofstream &output_stream, unordered_map<char, string>& code, string input_fname){
    ifstream input_stream(input_fname);
    char ch;
    string encoded_text = "";
    while(input_stream.get(ch)){
        encoded_text += code[ch];
    }
    input_stream.close();
    encoded_text += code[PSEUDO_EOF];
    int rem = (encoded_text.length() - 1) % 8;
    for(int i = 0; i < 8 - rem ; i++){
        encoded_text += '0';
    }
    bitset<8> bits;
    stringstream stringStream(encoded_text);
    while(stringStream >> bits){
        char c = static_cast<char> (bits.to_ulong());
        output_stream.put(c);
    }
    output_stream.close();
}

void compress_to_file(string to_compress_fname, string output_fname){

    //find frequency count for each character
    unordered_map<char, ll> freq_count;
    ll count_chars = 0;
    if(find_freq_count(to_compress_fname, freq_count, count_chars))   return;

    if(freq_count.empty()) return;

    //create huffman tree
    Node* tree_root = create_huffman_tree(freq_count, count_chars);

    freq_count.clear();

    //find codes for every character
    unordered_map<char, string> code;
    create_code(code, tree_root, "");


    

    //open input and output files
    ifstream input_stream(to_compress_fname);
    ofstream output_stream(output_fname);

    //print header in output file
    print_header(output_stream, code);
    clear_tree(tree_root);

    //print the encoded text
    print_encoded_text(output_stream, code, to_compress_fname);

    code.clear();

}