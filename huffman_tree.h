#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#include <vector>
#include <queue>
#include <fstream>
#include "huffman_node.h"

using namespace std;

class HuffmanTree{
private:
    vector <HuffmanNode*> huffman_nodeptr_vector;
    string input_file_path, output_file_path;

    ifstream input_file_stream;
    ofstream output_file_stream;

    HuffmanNode* huffman_tree_root;

    class CompareHuffmanNode{
    public:
        bool operator() (const HuffmanNode* node1, const HuffmanNode* node2){
            return node1->frequency > node2->frequency;
        }
    };
    priority_queue <HuffmanNode*, vector<HuffmanNode*>, CompareHuffmanNode> huffman_node_pq;

public:
    HuffmanTree(string input_file, string output_file);
    void create_huffman_vector();
    void make_pq();   
    void create_tree();
};

#endif