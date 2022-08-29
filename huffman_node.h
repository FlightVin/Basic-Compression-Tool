#ifndef HUFFMAN_NODE_H
#define HUFFMAN_NODE_H

#include <string>

using namespace std;

class HuffmanNode{
public:
    HuffmanNode* left_child;
    HuffmanNode* right_child;

    char character;
    size_t frequency;
    string huffman_code;

    HuffmanNode(){
        left_child = NULL;
        right_child = NULL;
        frequency = 0;
        character = '\0';
    }
};


#endif