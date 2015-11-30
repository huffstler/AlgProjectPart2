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

int frnt = 0 , back, off;

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
}

void populateMap() { // Done
	for (int i = 0; i < stopWords.size(); i++){
		mymap.insert(make_pair(strhash(stopWords[i]), stopWords[i]));
	}
}

// This stems the string that it is given
void stem(string *input){
	back = *input.length() - 1;
	off = back - frnt; // kinda stupid, I know
	
	if (back + 1 > 2) { //runs if the word is larger than 2 chars
		step1a(*input);
		step1b(*input);
		step2(*input);
	}
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

/* static char * b;
static int k,k0,j;       j is a general offset into the string 
		k = end index k0 starting index, j is the size I guess */
void step1a(string *input){ //THIS IS NOT DONE. NEED TO WORK ON OTHER STUFF RIGHT NOW
	//check if it ends with 's'
	if (*input.back() == 's'){
		//substr [i1,i2) = [1,5) = 1-4
		if(*input.substr(end-3, 4) == "sses") { //ends in "sses"
			end -= 2;
		}
		else if (*input.substr(end-2, 3) == "ies") { //ends in "ies"
			*input.replace(substr(end-2, 3), "i");
		}
		else if (*input.at(end-1) != 's') { // second to last letter isn't an s. (ends in C's' where C is any consonant
			end --;
		}
	}
	//check if it ends in "eed"
	if (*input.substr(end-2, 3) == "eed") {
		//don't forget to check the m score
		end --;
	//check if it ends in "ed"
	} else if (*input.substr(end-1, 2) == "ed" || *input.substr(end-2, 3) == "ing") {
		
		if(*input.substr(end-1, 2) == "ed"){
			end -=2; // maybe get ride of this? Used to be end = offset;
		} else {
			end-=3;
		}
				
		if (*input.substr(end-1, 2) == "at") {
			*input.replace(substr(end-1, 2), "ate");
			
		} else if (*input.substr(end-1, 2) == "bl") {
			*input.replace(substr(end-1, 2), "ble");
			
		} else if (*input.substr(end-1, 2) == "iz") {
			*input.replace(substr(end-1, 2), "ize");
			
		} else if () {
			end --;
			if (*input.at(end) == 'l' || *input.at(end) == 's' || *input.at(end) == 'z'){
				end++;
			}
		} else if () {
			
		}
	}
}

void step1b (string *input) {
	if(*input.back() == "y") {
		*input.back() = 'i';
	}
}

void step2 (string *input) {
	switch (*input.at(end-1)){
		case 'a':
			if (*input.substr(end-6, 7) == "ational") {*input.replace(substr(end-6, 7), "ate"); break;}
			if (*input.substr(end-5, 6) == "tional") {*input.replace(substr(end-5, 6), "tion"); break;}
			break;
		case 'c':
			if (*input.substr(end-3, 4) == "enci") {*input.replace(substr(end-3, 4), "ence"); break;}
			if (*input.substr(end-3, 4) == "anci") {*input.replace(substr(end-3, 4), "ance"); break;}
			break;
		case 'e':
			if (*input.substr(end-3, 4) == "izer") {*input.replace(substr(end-3, 4), "ize"); break;}
			break;
		case 'l':
			if (*input.substr(end-2, 3) == "bli") {*input.replace(substr(end-2, 3), "ble"); break;}
			if (*input.substr(end-3, 4) == "alli") {*input.replace(substr(end-3, 4), "al"); break;}
			if (*input.substr(end-4, 5) == "entli") {*input.replace(substr(end-4, 5), "ent"); break;}
			if (*input.substr(end-2, 3) == "eli") {*input.replace(substr(end-2, 3), "e"); break;}
			if (*input.substr(end-4, 5) == "ousli") {*input.replace(substr(end-4, 5), "ous"); break;}
			break;
		case 'o':
			if (*input.substr(end-6, 7) == "ization") {*input.replace(substr(end-6, 7), "ize"); break;}
			if (*input.substr(end-4, 5) == "ation") {*input.replace(substr(end-4, 5), "ate"); break;}
			if (*input.substr(end-3, 4) == "ator") {*input.replace(substr(end-3, 4), "ate"); break;}
			break;
		case 's':
			if (*input.substr(end-4, 5) == "alism") {*input.replace(substr(end-4, 5), "al"); break;}
			if (*input.substr(end-6, 7) == "iveness") {*input.replace(substr(end-6, 7), "ive"); break;}
			if (*input.substr(end-6, 7) == "fulness") {*input.replace(substr(end-6, 7), "ful"); break;}
			if (*input.substr(end-6, 7) == "ousness") {*input.replace(substr(end-6, 7), "ous"); break;}
			break;
		case 't':
			if (*input.substr(end-4, 5) == "aliti") {*input.replace(substr(end-4, 5), "al"); break;}
			if (*input.substr(end-4, 5) == "iviti") {*input.replace(substr(end-4, 5), "ive"); break;}
			if (*input.substr(end-5, 6) == "biliti") {*input.replace(substr(end-5, 6) "ble"); break;}
		//case 'g':
	}
}

void step3 (string *input) {
	switch(*input.end()){
		case 'e':
			if (*input.substr(end-4, 5) == "icate") {*input.replace(substr(end-4, 5), "ic"); break;}
			if (*input.substr(end-4, 5) == "ative") {*input.replace(substr(end-4, 5), ""); break;}
			if (*input.substr(end-4, 5) == "alize") {*input.replace(substr(end-4, 5), "al"); break;}
			break;
		case 'i':
			if (*input.substr(end-4, 5) == "iciti") {*input.replace(substr(end-4, 5), "ic"); break;}
			break;
		case 'l':
			if (*input.substr(end-3, 4) == "ical") {*input.replace(substr(end-3, 4), "ic"); break;}
			if (*input.substr(end-2, 3) == "ful") {*input.replace(substr(end-2, 3), ""); break;}
			break;
		case 's':
			if (*input.substr(end-3, 4) == "ness") {*input.replace(substr(end-3, 4), ""); break;}
			break;
	}
}

void step4 (string *input) {}
	
void step5 (string *input) {}

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
