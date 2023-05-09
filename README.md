# Brief Description of the program logic
- This is a console-based application written in C++
- User interaction: 
    - `REG <customer_name>` command allow enter a new customer to the system if the name does not exist before. Otherwise, the command is considered as a new order for the customer who is already in the restaurant
    - `CLE <table_id>` command to allow manager explicitly delete a customer who is currently seating at the given table.
    - `PrintAVL`
    - `PrintMH`
    - `PrintHT`
    The last three command is to inspect the info related to the specified postfix. `PrintAVL` will print all customers at sector 2 (managed according to AVL tree). `PrintHT` displays customers at sector 1 (managed according to a hash table). The last command, `PrintMH`, print the log structure for LFCO policy.
- REG command parse the given customer name and use Huffman Coding Tree to encode the name into a customer code which for the sake of system processing in later step as well as for other commands.
- Out-of-slots policy: if a new customer comes to the restaurant and all tables are occupied. Depends on the customer code (resulted from encoding phase), a respective policy will be applied to replace an existing customer in the restaurant with the newly-coming one.
1. FIFO (first in first out)
2. LRCO (least recently customer order)
3. LFCO ( least frequently customer order)
# Huffman coding notes
Equal weight resolutions
- In this case, the node came earlier will take priority over the other

The order of character when add into heap
- Comply to their order in ASCII encoding
