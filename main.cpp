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

//Plan out how this shit is going to work.
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

			//This removes periods
			unsigned long len = tempStringP.size();

			for (unsigned long i = 0; i < len; i++) {
				if (isdigit(tempStringP[i])) {
					tempStringP.erase(i--, 1);
					len = tempStringP.size();
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

		while (true) {
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
void stem(){

}

// this indexes the remaining words from the given input
void index() {
	//idea of how to do this. Make index by paragraph instead of document
	//iterate through list of keywords until a new line is hit (has to be added in primary iteration)
	//push all these words onto a list named paragraph[i] (where i is the paragraph number)
	//when a new paragraph starts, make a new list adding in all words
	//do so until the end, having a seperate list of keywords for each paragraph
	//for each keyword in orignal list (inputeddata) check if it is in each paragraph
	//cout keyword: "appears in" (whichever lists it is found in)


	list<string> Data;
	list<list<string>> Pgraphs;
	string tempStringP;
	int Pnumber = 0; //current paragraph number
	while (getline(cin, tempStringP)){
		while (getline(cin, tempStringP, '\n')){ //reads in a line from ideone
			Pnumber++;

			// cout << Pnumber << " ";

			for (int i = 0; tempStringP[i] != '\0'; i++) {//lowercase everything
				tempStringP[i] = tolower(tempStringP[i]);
			}

			stringstream iss(tempStringP);

			while (getline(iss, tempStringP, ' ')){ //get string up to a space

				//This removes periods
				unsigned long len = tempStringP.size();

				for (unsigned long i = 0; i < len; i++) {

					if (ispunct(tempStringP[i])) {
						tempStringP.erase(i--, 1);
						len = tempStringP.size();
					}
				}

				//push string with removed punctuation onto the imported data list
				if (!isStop(tempStringP)) {
					Data.push_back(tempStringP);
				}
			}
			Pgraphs.push_back(Data);
			Data.clear();

			/*
			//printing the lists
			for(list<list<string>>::iterator iter = Pgraphs.begin(); iter!= Pgraphs.end(); iter++){
			for(list<string>::iterator iter2 = iter->begin(); iter2!= iter->end(); iter2++){

			cout << Pnumber << "\n ";
			cout << *iter2;

			if(iter2 == importedData.end()) {
			break;
			} else {
			cout << ", ";
			}
			}
			}
			*/

			list<list<string>>::iterator row;
			list<string>::iterator col;
			for (row = Pgraphs.begin(); row != Pgraphs.end(); row++){
				for (col = row->begin(); col != row->end(); col++){

				}
			}


		}
	}


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
	//  getFile(); // reads std for the file to be input.
	index();



}
