#include<iostream>
#include<string>
using namespace std;
#include"compress.h"
#include"decompress.h"
#include"Huffman_node.h"



int main(){
    string task;
    while(true){
        cout << "Do you wish to compress, decompress or exit?: ";
        cin >> task;
        if(task == "exit") return 0;
        else if(task == "compress"){
            cout << "Enter path to the file to be compressed: ";
            string file_to_compress;
            cin >> file_to_compress;
            cout << "Enter name of output file: ";
            string compressed_file;
            cin >> compressed_file;
            compress_to_file(file_to_compress, compressed_file);
        }
        else if(task == "decompress"){
            cout << "Enter path to the file to be decompressed: ";
            string file_to_decompress;
            cin >> file_to_decompress;
            string output_file;
            cout << "Enter name of decompressed file: ";
            cin >> output_file;
            decompress_func(file_to_decompress, output_file);
        }
        else{
            cout << "Sorry, I didn't understand that\n";
        }
    }
}