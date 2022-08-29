#include <iostream>
#include "huffman_tree.h"
#include "huffman_tree.h"

using namespace std;

int main(int argc, char** argv){

    if (argc < 3){
        cout<<"Input format: $ ./a.out input_file output_file"<<endl;
        exit(EXIT_FAILURE);
    }
    cout<<"Input file: "<<argv[1]<<endl;
    cout<<"Output file: "<<argv[2]<<endl;

    HuffmanTree my_huffman(argv[1], argv[2]);
    my_huffman.make_pq();
    my_huffman.create_tree();
    my_huffman.assign_codes();
    my_huffman.create_compressed_file();

    cout<<"Done compressing"<<endl;
    exit(EXIT_SUCCESS);
}