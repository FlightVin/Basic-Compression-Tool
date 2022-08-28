#include "huffman_tree.h"
#define HuffmanPriorityQueue priority_queue <HuffmanNode*, vector<HuffmanNode*>, CompareHuffmanNode> 

HuffmanTree::HuffmanTree(string in_file, string out_file){
    input_file_path = in_file;
    output_file_path = out_file;

    input_file_stream.open(input_file_path);
    output_file_stream.open(output_file_path);

    huffman_nodeptr_vector = vector<HuffmanNode*>(256);
    create_huffman_vector();
}

void HuffmanTree::create_huffman_vector(){
    for (int i = 0; i<huffman_nodeptr_vector.size(); i++){
        huffman_nodeptr_vector[i] = new HuffmanNode;
        huffman_nodeptr_vector[i]->character = static_cast<char>(i);
    }
}

void HuffmanTree::make_pq(){
    char read_char;
    input_file_stream.get(read_char);
    while(read_char != EOF){
        huffman_nodeptr_vector[static_cast<int>(read_char)]->frequency++;
        input_file_stream.get(read_char);
    }

    for (int i = 0; i<huffman_nodeptr_vector.size(); i++){
        if (huffman_nodeptr_vector[i]->frequency > 0){
            huffman_node_pq.push(huffman_nodeptr_vector[i]);
        }
    }
}

void HuffmanTree::create_tree(){
    HuffmanPriorityQueue temp_pq(huffman_node_pq);
    HuffmanNode* temp_root;

    while (temp_pq.size() > 1){
        temp_root = new HuffmanNode;

        HuffmanNode* left_node = temp_pq.top(); temp_pq.pop();
        HuffmanNode* right_node = temp_pq.top(); temp_pq.pop();

        temp_root->frequency = left_node->frequency + right_node->frequency;
        temp_root->left_child = left_node;
    }

    huffman_tree_root = temp_root;
}