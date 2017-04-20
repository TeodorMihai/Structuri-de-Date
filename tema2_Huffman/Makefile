build: main.cpp heap.cpp huffman.cpp
	g++ -Wall main.cpp heap.cpp nod.cpp huffman.cpp -o huffman

clean:
	rm huffman
run:
	./huffman -c data.in data.out

compress:
	./huffman -c data.in data.out

decompress:
	./huffman -d data.out data.in

arhiva:
	zip Cotet_Teodor_Mihai_312CC_Tema2_SD.zip *.cpp *.h README Makefile
