Huffman coding application
===
This is a huffman encoding file application.<br>
You can use huffman.elf or main.cpp singly. <br>

# How to build
* Command Line Interface:
    * make
* Graphical User Interface:
    * ./setup.sh
    * make dep
    * ref: https://stackoverflow.com/questions/145270/calling-c-c-from-python
* setup python environment
    * ./setup.sh
* clean
    * make clean

# How to use
* python(GUI):
    * python3 p8.py
* zenity(GUI):
    1. <pre><code>cd zenity/</code></pre>
    2. <pre><code>./shellGUI.sh</code></pre>
* CLI:
    * compress: <pre><code>./huffman.elf -c ${file}</code></pre>
    * decompress: <pre><code>./huffman.elf -d ${file}</code></pre>

# Header format 
 * little endian
 * header format(2 part):<br>
    info:<br>
        <pre><code>|originSize(sizeof(size_t))|compressBitsLength (sizeof(size_t))|IEEE-754 for compressRate(4Byte)|<br>
        |codingTable.size(1Byte)|padding.length(1Byte)|</code></pre>
    codingtable:<br>
        <pre><code>|uChar(1Byte)|codingLength(1Byte)|coding contents|</code></pre><br>

==Warning==<br>
Input file(to compress) MAX size is 2^31 GB, MIN is 1 Byte<br>
You cannot compress nothing by huffman coding algorithm<br>

# Might do
1. more clear and efficient while compress
    * Assigning code have to traversal once, recording leafs are also traversal once.
    * After recording leafs push all leafs in to map?
    * **why don't I just push code into map once**
        * Will this be "not clean code"?