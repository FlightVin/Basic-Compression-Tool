#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#include <vector>
#include <queue>
#include <fstream>
#include "huffman_node.h"

using namespace std;

int convert_bin_to_dec(const string& bin_str);

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
    void assign_codes();
    void assign_code_to_node(HuffmanNode* cur_node, string& cur_code);
    void create_compressed_file();
};

#endif