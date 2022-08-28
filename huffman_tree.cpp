#include <iostream>
#include "huffman_tree.h"
#define HuffmanPriorityQueue priority_queue <HuffmanNode*, vector<HuffmanNode*>, CompareHuffmanNode> 

int convert_bin_to_dec(const string& bin_str){
    int res = 0;
    for (int i = 0; i<bin_str.size(); i++){
        res = res*2;
        res += bin_str[i] - '0';
    }
    return res;
}

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
    while(!input_file_stream.eof()){
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
        temp_root->right_child = right_node;

        temp_pq.push(temp_root);
    }

    huffman_tree_root = temp_root;
}

void HuffmanTree::assign_codes(){
    string str = "";
    assign_code_to_node(huffman_tree_root, str);
}

void HuffmanTree::assign_code_to_node(HuffmanNode* cur_node, string& cur_code){

    if (cur_node->left_child == NULL && cur_node->right_child == NULL){
        cur_node->huffman_code = cur_code;
        return; 
    }

    cur_code.push_back('0');
    assign_code_to_node(cur_node->left_child, cur_code);
    cur_code.pop_back();

    cur_code.push_back('1');
    assign_code_to_node(cur_node->right_child, cur_code);
    cur_code.pop_back();
}

void HuffmanTree::create_compressed_file(){

    input_file_stream.open(input_file_path, ios::in);
    output_file_stream.open(output_file_path, ios::out | ios::binary);

    string write_out_string = "", temp_str = "";

    HuffmanPriorityQueue temp_pq(huffman_node_pq);

    write_out_string.push_back(static_cast<char>(temp_pq.size()));

    while(!temp_pq.empty()){
        HuffmanNode* cur_node = temp_pq.top(); temp_pq.pop();
        write_out_string.push_back(cur_node->character);

        temp_str = string(255 - cur_node->huffman_code.size(), '0');
        temp_str.push_back('1');
        temp_str.append(cur_node->huffman_code);

        for (int i = 0; i<31; i++){
            write_out_string.push_back(static_cast<char>(convert_bin_to_dec(temp_str.substr(0, 8))));
            temp_str = temp_str.substr(8);
        }
        write_out_string.push_back(static_cast<char>(convert_bin_to_dec(temp_str.substr(0, 8))));
    }

    temp_str.clear();

    char read_char;
    input_file_stream.get(read_char);

    while(!input_file_stream.eof()){
        temp_str.append(huffman_nodeptr_vector[static_cast<int>(read_char)]->huffman_code);

        while(temp_str.size() > 8){
            write_out_string.push_back(static_cast<char>(convert_bin_to_dec(temp_str.substr(0, 8))));
            temp_str = temp_str.substr(8);
        }

        input_file_stream.get(read_char);
    }

    int left_over = 8 - temp_str.size();
    if (temp_str.size() < 8){
        temp_str.append(8 - temp_str.size(), '0');
    }
    write_out_string.push_back(static_cast<char>(convert_bin_to_dec(temp_str.substr(0, 8))));
    write_out_string.push_back(static_cast<char>(left_over));

    output_file_stream.write(write_out_string.c_str(), write_out_string.size());

    input_file_stream.close();
    output_file_stream.close();
}
