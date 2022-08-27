#ifndef HUFFMAN_NODE_H
#define HUFFMAN_NODE_H

#include <string>

using namespace std;

class huffman_node{
public:
    huffman_node* left_child;
    huffman_node* right_child;

    char character;
    size_t frequency;
    std::string huffman_code;

    huffman_node(){
        left_child = NULL;
        right_child = NULL;
    }
};


#endif