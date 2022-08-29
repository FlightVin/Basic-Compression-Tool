compression : compression.o huffman_tree.o huffman_node.h
	g++ -o compression -g compression.o huffman_tree.o

compression.o : compression.cpp huffman_node.h huffman_tree.h
	g++ -c compression.cpp

huffman_tree.o : huffman_tree.cpp huffman_node.h huffman_tree.h 
	g++ -c huffman_tree.cpp

clean :
	rm compression compression.o huffman_tree.o