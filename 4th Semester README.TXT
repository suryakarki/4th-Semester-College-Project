#About the program:

The program counts the number of articles(a, an, the) and dates(all valid dates) for all the paragraphs seperately which are read from the input file.

#Programing Language used:

C++

#Development Environment:

Code::Blocks
Version: Release 16.01 rev 10702
SDK Version: 1.29.0
Compiler Information: GNU GCC Compiler

#Operating System used:

Windows 10 Pro

#Working of Program:

The program when build and run asks the user to input a number N (where N= Number of Paragraphs to be taken from the file). Then it asks for the path of file to be tested. Once the user enter the correct path of file, the file is opened and total number of paragraphs in the file are calculated. Then the file is again opened by the program and the file is read character by character and then stored in a string. Once a complete word is stored in the string it is then passed to a function which calculates the number of articles by comparing the string passed with a, an, and the. Another string is passed to a function which stores the content of a paragraph dynamically with the help of a linked list. Once the paragraph is changed the program calls another function which has access to the linked list created and then the output for first paragraph is displayed on the screen and all the counters and front & rear of the linked list are set to NULL. The program continues to store, pass, count, and display the number of articles & valid dates for every paragraph. Once the number of paragraphs is equal to the number N(entered by user) the program ends.


#Note:

The number N is to be entered by the user only. It is to be not taken directly from the first line of input file.
