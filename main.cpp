#include <cstdlib>
//#include <std::hash>

using namespace std;

//Plan out how this shit is going to work.
/*

Program Flow:
	
Input text thats copied from a file, given to the program via stdin.
program removes stop words, stems the words and indexes them
program then gets a query (through std in)
program removes stop words from the query, and stems remaining words
program returns the amount of times that the query appears in given document

*/

unordered_map<string,string> stopMap;


// This reads in an input file from stdin
void getFile() {
	
}

// this removes stop words from the input (and the query)
void rmStopwords() {
	
}

// This stems the string that it is given
void stem(){
	
}

// this indexes the remaining words from the given input
void index() {
	
}

// This reads in the user query from stdin
void getQuery () {
	
}

// This returns the amount of times that the query occurred in the doc
void returnResults(){
	
}

// Main method
int main() {
	
}