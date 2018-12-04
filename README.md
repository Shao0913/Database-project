# Database-project

		Coconut DataBase Project
		-------------------------
		-------------------------

This project takes an input file containing dataseries, builds a tree and
supports querying for the tree.


Required Files
--------------
* output.txt
* znormtime.cpp
* tree_m.h


Procedure
-------------
* The required files should be stored in the same directory.
* The znormtime.cpp file only should be ran because it automatically links to other files.
* First, you have to input 'l' to preprocess a dataset (This means applying z-nomalization).
  This preprocessing will create two files "saxoutput.txt" and "timerecord.txt".
* Then, you can input 'a' to automatically build a tree and prepare for query.
* Input '3' to begin a query process then enter a dataseries and end with '#' symbol.
* The output of this query will be the sortable summarization (a long integer number) and the 
  dataseries that has been found in the tree.



It build on VS code 2017 IDE.  output.txt is raw data file produced by synthetic generator, which will be used as input file here. Therefore, in order to run this program, the output.txt has to be placed with code in same directory and configured as input arguments (main function requries arguments input). 

When the program run, the first step is to input "l" to preprocess raw data file. After finishing the preprocessing, two files will be generated: saxoutput.txt and timerecord.txt. The saxoutput.txt is used in building tree procedure, and the timerecord.txt is used in preprocessing construction time consumption evaluation. For every time run the prepocessing part, the existed two files need to delete, otherwise, it won't override it. After getting result of processed data, you can enter "a" to build the B-Tree. After build the B-tree, terminal will ask if you want to query, if you want you can enter "3" to start query process. Then terminal will ask for query sequence, just copy and paste the raw data sequence you want to query with "#" as end postfix. At last, the terminal will output the result, the first line is the index of this sequence, the second line is the sequence that this index point at, the third line is the address of current node stored.

Only the znormtime.cpp and tree_m.h is the main part, the rest is library or the code was used during the programming and denied eventually.
