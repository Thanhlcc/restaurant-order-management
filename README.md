# Huffman coding notes
Equal weight resolutions
- In this case, the node came earlier will take priority over the other

The order of character when add into heap
- Comply to their order in ASCII encoding

## Input testcases:
### Trailing whitespace/tab
    REG thanh
 REG thanh
### Leading whitespace/tab
REG thanh  
REG thanh   
### separated by a tab
REG thanh
### separated by multiple ws
REG    thanh
### REG <name>
Case 1: valid input
REG Thanh
Case 2: name including number
REG tha12nh
### CLE <number>
Case 1: negative number
CLE -12
Case 2: positive number
CLE 12
### Print
Case 1: Print with second para
PrintAVL second