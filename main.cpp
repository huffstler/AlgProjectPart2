#include <cstdlib>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <queue>
#include <string>
#include <array>
#include <list>
#include <sstream>

using namespace std;

/*
Program Flow:

Input text thats copied from a file, given to the program via stdin.
program removes stop words, stems the words and indexes them
program then gets a query (through std in)
program removes stop words from the query, and stems remaining words
program returns the amount of times that the query appears in given document
*/

unordered_map<int, string> mymap;
list<string> importedData;
hash<string> strhash;

vector<string> stopWords = { "a", "about", "above", "across", "after", "afterwards", "again", "against", "all", "almost", "alone", "along", "already", "also", "although", "always", "am", "among", "amongst", "amoungst", "amount", "an", "and", "another", "any", "anyhow", "anyone", "anything", "anyway", "anywhere", "are", "around", "as", "at", "back", "be", "became", "because", "become", "becomes", "becoming", "been", "before", "beforehand", "behind", "being", "below", "beside", "besides", "between", "beyond", "bill", "both", "bottom", "but", "by", "call", "can", "cannot", "cant", "co", "computer", "con", "could", "couldnt", "cry", "de", "describe", "detail", "do", "done", "down", "due", "during", "each", "eg", "eight", "either", "eleven", "else", "elsewhere", "empty", "enough", "etc", "even", "ever", "every", "everyone", "everything", "everywhere", "except", "few", "fifteen", "fify", "fill", "find", "fire", "first", "five", "for", "former", "formerly", "forty", "found", "four", "from", "front", "full", "further", "get", "give", "go", "had", "has", "hasnt", "have", "he", "hence", "her", "here", "hereafter", "hereby", "herein", "hereupon", "hers", "him", "his", "how", "however", "hundred", "i", "ie", "if", "in", "inc", "indeed", "interest", "into", "is", "it", "its", "keep", "last", "latter", "latterly", "least", "less", "ltd", "made", "many", "may", "me", "meanwhile", "might", "mill", "mine", "more", "moreover", "most", "mostly", "move", "much", "must", "my", "name", "namely", "neither", "never", "nevertheless", "next", "nine", "no", "nobody", "none", "noone", "nor", "not", "nothing", "now", "nowhere", "of", "off", "often", "on", "once", "one", "only", "onto", "or", "other", "others", "otherwise", "our", "ours", "ourselves", "out", "over", "own", "part", "per", "perhaps", "please", "put", "rather", "re", "same", "see", "seem", "seemed", "seeming", "seems", "serious", "several", "she", "should", "show", "side", "since", "sincere", "six", "sixty", "so", "some", "somehow", "someone", "something", "sometime", "sometimes", "somewhere", "still", "such", "system", "take", "ten", "than", "that", "the", "their", "them", "themselves", "then", "thence", "there", "thereafter", "thereby", "therefore", "therein", "thereupon", "these", "they", "thick", "thin", "third", "this", "those", "though", "three", "through", "throughout", "thru", "thus", "to", "together", "too", "top", "toward", "towards", "twelve", "twenty", "two", "un", "under", "until", "up", "upon", "us", "very", "via", "was", "we", "well", "were", "what", "whatever", "when", "whence", "whenever", "where", "whereafter", "whereas", "whereby", "wherein", "whereupon", "wherever", "whether", "which", "while", "whither", "who", "whoever", "whole", "whom", "whose", "why", "will", "with", "within", "without", "would", "yet", "you", "your", "yours", "yourself", "yourselves" };

int offset;
int start=0;
int end;

//Is it a stop word?
bool isStop(string word){
	if (mymap.find(strhash(word)) != mymap.end()) {
		return true;
	}
	else {
		return false;
	}
}

// This reads in an input file from stdin
// Reads past new lines now
void getFile(){
	list<string> importedData;
	string tempStringP;
	//int count = 0;

	while (getline(cin, tempStringP)){ //reads in a line from ideone

		for (int i = 0; tempStringP[i] != '\0'; i++) {//lowercase everything
			tempStringP[i] = tolower(tempStringP[i]);
		}

		stringstream iss(tempStringP);

		while (getline(iss, tempStringP, ' ')){ //get string up to a space
			//This removes punctuation and numbers
			unsigned long len = tempStringP.size();

			for (unsigned long i = 0; i < len; i++) {
				if (isdigit(tempStringP[i])) {
					tempStringP.erase(i--, 1);
					len = tempStringP.size();
				}
				if (ispunct(tempStringP[i])) {
					tempStringP.erase(i--, 1);
					len = tempStringP.size();
				}
			}

			//push string with removed punctuation onto the imported data list
			if (!isStop(tempStringP)) {
				importedData.push_back(tempStringP);
			}
			//count++;
		}
	}

	//This prints my imported data so I can see that it is correct
	//comment in and out as needed

	if (!importedData.empty()) {
		auto iter = importedData.begin();

		while (true) { // call stem here
			cout << *iter;
			++iter;

			if (iter == importedData.end()) {
				break;
			}
			else {
				cout << ", ";
			}
		}
	}

	//  printing function ends here
}

void populateMap() { // Done
	for (int i = 0; i < stopWords.size(); i++){
		mymap.insert(make_pair(strhash(stopWords[i]), stopWords[i]));
	}
}

// This stems the string that it is given
void stem(string *input) {  
	end = input.size() - 1;
	offset = end - start; // kinda stupid, I know
	
    if (input.size() > 2) {
		step1a(*input);
	  /*step1b();
		step1c(); 
		step2(); 
		step3(); 
		step4(); 
		step5(); */
	}
}

/* static char * b;
static int k,k0,j;       j is a general offset into the string 
		k = end index k0 starting index, j is the size I guess */
void step1a(string *input){
	//check if it ends with 's'
	if (*input.back() == 's'){
		if(*input.substr(end-3, 3) == "sses") { //ends in "sses"
			end -= 2;
		}
		else if (*input.substr(end-2, 2) == "ies") { //ends in "ies"
			*input.replace(substr(end-2, 2), "i");
		}
		else if (*input[end-1] != 's') { // second to last letter isn't an s. (ends in C's' where C is any consonant
			end --;
		}
	//check if it ends in "eed"
	} else if (*input.substr(end-2, 2) == "eed") {
		
	//check if it ends in "ed"
	} else if () {
		
	}
}

void step1b(string *input){
	
}

void step1c(string *input){
	
}

void step2(string *input){
	
}

void step3(string *input){
	
}

void step4(string *input){
	
}

void step5(string *input){
	
}



// this indexes the remaining words from the given input
void index() {

}

// This reads in the user query from stdin
void getQuery() {

}

// This returns the amount of times that the query occurred in the doc
void returnResults(){

}

// Main method
int main() {

	populateMap(); // puts the stop words in a map for quick access
	getFile(); // reads std for the file to be input.

}
