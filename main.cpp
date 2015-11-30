#include <cstdlib>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <queue>
#include <algorithm>
#include <utility>
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

void stem(string& word);
void trim(string& word);
size_t firstNonVowelAfterVowel(const string& word, size_t start);
size_t getStartR1(const string& word);
size_t getStartR2(const string& word, size_t startR1);
void changeY(string& word);
void step0(string& word);
bool step1A(string& word);
void step1B(string& word, size_t startR1);
void step1C(string& word);
void step2(string& word, size_t startR1);
void step3(string& word, size_t startR1, size_t startR2);
void step4(string& word, size_t startR2);
void step5(string& word, size_t startR1, size_t startR2);
inline bool isShort(const string& word);
bool special(string& word);
bool isVowel(char c);
bool isVowelY(char c);
bool endsWith(const string& word, const string& str);
bool endsInDouble(const string& word);
bool replaceIfExists(string& word, const string& suffix,
	const string& replacement, size_t start);
bool ValidEndsWithLI(char c);
bool containsVowel(const string& word, size_t start, size_t end);

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
struct strNode{
	string word;
	vector<int> pList;
};

struct Node{
	int pNum;
	vector<strNode*> nodeList;
};


// This reads in an input file from stdin
// Reads past new lines now
vector<Node*> paragraphList;
void getFile(){
	vector<strNode*> importedData;
	string tempStringP;
	int listcount = 1;

	while (getline(cin, tempStringP)){ //reads in a line from ideone
		if (tempStringP == "/////"){
			Node *p = new Node;
			p->pNum = listcount;
			p->nodeList = importedData;
			paragraphList.push_back(p);
			importedData.clear();
			listcount++;
		}


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
				}
				if (ispunct(tempStringP[i])) {
					tempStringP.erase(i--, 1);
					len = tempStringP.size();
				}
			}

			//push string with removed punctuation onto the imported data list
			if (!isStop(tempStringP) && tempStringP != "") {
				strNode *s = new strNode;
				s->pList.push_back(listcount);
				s->word = tempStringP;
				importedData.push_back(s);
			}
		}
	}
	/*	for (int i = 0; i < paragraphList.size(); i++)
	{
	cout << "New Paragraph: ";
	for (int j = 0; j < paragraphList[i]->nodeList.size(); j++){
	cout << paragraphList[i]->nodeList[j]->word << " -> ";
	}
	cout << endl;
	}

	*/

	//  printing function ends here
}

void populateMap() { // Done
	for (int i = 0; i < stopWords.size(); i++){
		mymap.insert(make_pair(strhash(stopWords[i]), stopWords[i]));
	}
}

// This stems the string that it is given
void stem(string& word) {
	// doesn't care about words smaller than 3 characters
	if (word.size() <= 2)
		return;

	if (word[0] == '\'')
		word = word.substr(1, word.size() - 1);

	changeY(word);
	size_t startR1 = getStartR1(word);
	size_t startR2 = getStartR2(word, startR1);

	step0(word);

	if (step1A(word)) {
		replace(word.begin(), word.end(), 'Y', 'y');
		return;
	}

	step1B(word, startR1);
	step1C(word);
	step2(word, startR1);
	step3(word, startR1, startR2);
	step4(word, startR2);
	step5(word, startR1, startR2);

	replace(word.begin(), word.end(), 'Y', 'y');
	return;
}

// Trims the word given to it. Trimming entails turning it to all lowercase, and removing non-alphanumeric characters
void trim(string& word) {
	transform(word.begin(), word.end(), word.begin(), ::tolower);
	remove_if(word.begin(), word.end(), [](char c){
		return !((c >= 'a' && c <= 'z') || c == '\'');
	});
}

// Checks for special cases of words ["gener", "commun", "arsen"].
size_t getStartR1(const string& word) {
	// defined special cases
	if (word.size() >= 5 && word[0] == 'g' && word[1] == 'e' && word[2] == 'n'
		&& word[3] == 'e' && word[4] == 'r')
		return 5;
	if (word.size() >= 6 && word[0] == 'c' && word[1] == 'o' && word[2] == 'm'
		&& word[3] == 'm' && word[4] == 'u' && word[5] == 'n')
		return 6;
	if (word.size() >= 5 && word[0] == 'a' && word[1] == 'r' && word[2] == 's'
		&& word[3] == 'e' && word[4] == 'n')
		return 5;
	// If no special cases found, use standard function
	return firstNonVowelAfterVowel(word, 1);
}

// checks size of word and returns it if the same
size_t getStartR2(const string& word, size_t startR1) {
	if (startR1 == word.size())
		return startR1;

	return firstNonVowelAfterVowel(word, startR1 + 1);
}

// return the first consonant character that appears after a vowel, beginning from start
size_t firstNonVowelAfterVowel(const string& word, size_t start) {
	for (size_t i = start; i != 0 && i < word.size(); ++i) {
		if (!isVowelY(word[i]) && isVowelY(word[i - 1]))
			return i + 1;
	}
	return word.size();
}

// changes case of the char y depending on what appears before it, and when it appears in the string
void changeY(string& word) {
	if (word[0] == 'y')
		word[0] = 'Y';

	for (size_t i = 1; i < word.size(); ++i) {
		if (word[i] == 'y' && isVowel(word[i - 1]))
			word[i++] = 'Y'; // skip next iteration
	}
}

/** 0
* catch words that are possesive || plural
*/
void step0(string& word) {
	replaceIfExists(word, "'s'", "", 0) || replaceIfExists(word, "'s", "", 0) || replaceIfExists(word, "'", "", 0);
}

/** 1A
* Looks for past tense words. Checks for edge cases as well
* Focus on suffix of: "Cs", "sses", "s", "ieC" (Where C is a variable character)
*/
bool step1A(string& word) {
	if (!replaceIfExists(word, "sses", "ss", 0)) {
		if (endsWith(word, "ied") || endsWith(word, "ies")) {
			// if preceded by only one letter
			if (word.size() <= 4)
				word.pop_back();
			else {
				word.pop_back();
				word.pop_back();
			}
		}
		else if (endsWith(word, "s") && !endsWith(word, "us") && !endsWith(word, "ss")) {
			if (word.size() > 2 && containsVowel(word, 0, word.size() - 2))
				word.pop_back();
		}
	}

	// special case after step 1a
	return word == "inning" || word == "outing" || word == "canning"
		|| word == "herring" || word == "earring" || word == "proceed"
		|| word == "exceed" || word == "succeed";
}

/** 1B
* Looks for (paste-tense)adverbs.
* Focus on suffix of: "eC", "ingCC","eed","edly" (Where C is a variable character)
*/
void step1B(string& word, size_t startR1) {
	bool exists = endsWith(word, "eedly") || endsWith(word, "eed");

	if (exists) // look only in startR1 now
		replaceIfExists(word, "eedly", "ee", startR1) || replaceIfExists(word, "eed", "ee", startR1);
	else {
		size_t size = word.size();
		bool deleted = (containsVowel(word, 0, size - 2) && replaceIfExists(word, "ed", "", 0))
			|| (containsVowel(word, 0, size - 4) && replaceIfExists(word, "edly", "", 0))
			|| (containsVowel(word, 0, size - 3) && replaceIfExists(word, "ing", "", 0))
			|| (containsVowel(word, 0, size - 5) && replaceIfExists(word, "ingly", "", 0));

		if (deleted && (endsWith(word, "at") || endsWith(word, "bl") || endsWith(word, "iz")))
			word.push_back('e');
		else if (deleted && endsInDouble(word))
			word.pop_back();
		else if (deleted && startR1 == word.size() && isShort(word))
			word.push_back('e');
	}
}

/** 1C
* Looks for words ending in y
* Swaps 'y' with 'i'
*/
void step1C(string& word) {
	size_t size = word.size();
	if (size > 2 && (word[size - 1] == 'y' || word[size - 1] == 'Y'))
		if (!isVowel(word[size - 2]))
			word[size - 1] = 'i';
}

/** 2
* No focus on anything specific.
* Look at the list of suffixes compared. to find out more
*/
void step2(string& word, size_t startR1) {

	static const vector<pair<string, string>> subs
		= { { "ational", "ate" },
		{ "tional", "tion" },
		{ "enci", "ence" },
		{ "anci", "ance" },
		{ "abli", "able" },
		{ "entli", "ent" },
		{ "izer", "ize" },
		{ "ization", "ize" },
		{ "ation", "ate" },
		{ "ator", "ate" },
		{ "alism", "al" },
		{ "aliti", "al" },
		{ "alli", "al" },
		{ "fulness", "ful" },
		{ "ousli", "ous" },
		{ "ousness", "ous" },
		{ "iveness", "ive" },
		{ "iviti", "ive" },
		{ "biliti", "ble" },
		{ "bli", "ble" },
		{ "fulli", "ful" },
		{ "lessli", "less" } };

	for (auto& sub : subs)
		if (replaceIfExists(word, sub.first, sub.second, startR1))
			return;

	if (!replaceIfExists(word, "logi", "log", startR1 - 1)) {
		// make sure we choose the longest suffix
		if (endsWith(word, "li") && !endsWith(word, "abli")
			&& !endsWith(word, "entli") && !endsWith(word, "aliti")
			&& !endsWith(word, "alli") && !endsWith(word, "ousli")
			&& !endsWith(word, "bli") && !endsWith(word, "fulli")
			&& !endsWith(word, "lessli"))
			if (word.size() > 3 && word.size() - 2 >= startR1 && ValidEndsWithLI(word[word.size() - 3])) {
				word.pop_back();
				word.pop_back();
			}
	}
}

/** 3
* Same as Step2
* No specific focus on certain suffixes
*/
void step3(string& word, size_t startR1, size_t startR2) {
	static const vector<pair<string, string>> subs
		= { { "ational", "ate" },
		{ "tional", "tion" },
		{ "alize", "al" },
		{ "icate", "ic" },
		{ "iciti", "ic" },
		{ "ical", "ic" },
		{ "ful", "" },
		{ "ness", "" } };

	for (auto& sub : subs)
		if (replaceIfExists(word, sub.first, sub.second, startR1))
			return;

	replaceIfExists(word, "ative", "", startR2);
}

/** 4
* Same as step 3 for the most part.
* one deviation is that this makes sure that the word with the longest suffix is used,
* instead of using a shorter suffix, which would be wrong is certain cases
*/
void step4(string& word, size_t startR2) {
	static const vector<pair<string, string>> subs
		= { { "al", "" },
		{ "ance", "" },
		{ "ence", "" },
		{ "er", "" },
		{ "ic", "" },
		{ "able", "" },
		{ "ible", "" },
		{ "ant", "" },
		{ "ement", "" },
		{ "ment", "" },
		{ "ism", "" },
		{ "ate", "" },
		{ "iti", "" },
		{ "ous", "" },
		{ "ive", "" },
		{ "ize", "" } };

	for (auto& sub : subs)
		if (replaceIfExists(word, sub.first, sub.second, startR2))
			return;

	// ensures word with longest tail is used
	if (!endsWith(word, "ement") && !endsWith(word, "ment"))
		if (replaceIfExists(word, "ent", "", startR2))
			return;

	// shortcut
	replaceIfExists(word, "sion", "s", startR2 - 1) || replaceIfExists(word, "tion", "t", startR2 - 1);
}

/** 5
* Checks the end of word for the char 'e'
* pops 'e' off if its found
*/
void step5(string& word, size_t startR1, size_t startR2) {
	size_t size = word.size();

	if (word[size - 1] == 'e') {

		if (size - 1 >= startR2)
			word.pop_back();

		else if (size - 1 >= startR1 && !isShort(word.substr(0, size - 1)))
			word.pop_back();

	}
	else if (word[word.size() - 1] == 'l') {

		if (word.size() - 1 >= startR2 && word[word.size() - 2] == 'l')
			word.pop_back();
	}
}

//Checks word for low amount of syllables
bool isShort(const string& word) {
	size_t size = word.size();

	if (size >= 3) {
		if (!isVowelY(word[size - 3]) && isVowelY(word[size - 2])
			&& !isVowelY(word[size - 1]) && word[size - 1] != 'w'
			&& word[size - 1] != 'x' && word[size - 1] != 'Y')
			return true;
	}
	return size == 2 && isVowelY(word[0]) && !isVowelY(word[1]);
}

//checks if the character is the vowel version of y
bool isVowelY(char c) {
	return c == 'e' || c == 'a' || c == 'i' || c == 'o' || c == 'u' || c == 'y';
}

//checks if given character is a vowel
bool isVowel(char c) {
	return c == 'e' || c == 'a' || c == 'i' || c == 'o' || c == 'u';
}

//checks if word ends with the given string, str
bool endsWith(const string& word, const string& str) {
	return word.size() >= str.size() && equal(word.begin() + (word.size() - str.size()), word.end(), str.begin());
}

//checks if given word ends with double of the chars listed [b,d,f,g,m,n,p,r,t]
bool endsInDouble(const string& word) {
	if (word.size() >= 2) {
		char a = word[word.size() - 1];
		char b = word[word.size() - 2];

		if (a == b)
			return a == 'b' || a == 'd' || a == 'f' || a == 'g' || a == 'm'
			|| a == 'n' || a == 'p' || a == 'r' || a == 't';
	}
	return false;
}

//replaces word with replacement beginning from start if word exists
bool replaceIfExists(string& word, const string& suffix, const string& replacement, size_t start) {
	size_t idx = word.size() - suffix.size();
	if (idx < start)
		return false;

	if (equal(word.begin() + idx, word.end(), suffix.begin())) {
		word = word.substr(0, word.size() - suffix.size()) + replacement;
		return true;
	}
	return false;
}

//checks some fringe cases. Words ending in 'li'
bool ValidEndsWithLI(char c) {
	return c == 'c' || c == 'd' || c == 'e' || c == 'g' || c == 'h'
		|| c == 'k' || c == 'm' || c == 'n' || c == 'r' || c == 't';
}

//returns true if word contains a vowel. False otherwise
bool containsVowel(const string& word, size_t start, size_t end) {
	if (end <= word.size()) {
		for (size_t i = start; i < end; ++i)
			if (isVowelY(word[i]))
				return true;
	}
	return false;
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
	bool flag = false;
	for (int i = 0; i < paragraphList.size(); i++){
		for (int j = 0; j < paragraphList[i]->nodeList.size(); j++){// this iterates through every word
			for (int f = 0; f < paragraphList.size(); f++){
				for (int x = 0; x < paragraphList[f]->nodeList.size(); x++){ // itterates through every word checking if it appears again and if so takes note of paragraph when it appaears
					if (paragraphList[i]->nodeList[j]->word == paragraphList[f]->nodeList[x]->word){
						for (int k = 0; k < paragraphList[i]->nodeList[j]->pList.size(); k++){
							if (paragraphList[i]->nodeList[j]->pList[k] == paragraphList[f]->pNum){
								flag = true;
							}
						}
						if (flag == false){
							paragraphList[i]->nodeList[j]->pList.push_back(paragraphList[f]->pNum);
						}
					}
				}flag = false;
			}
		}
	}
}

void stemFile(){
	for (int i = 0; i < paragraphList.size(); i++)
	{
		for (int j = 0; j < paragraphList[i]->nodeList.size(); j++){
			stem(paragraphList[i]->nodeList[j]->word);
		}
	}

}

void printList(){
	for (int i = 0; i < paragraphList.size(); i++)
	{
		cout << "Paragraph #" + to_string(paragraphList[i]->pNum) + ": " << endl;
		for (int j = 0; j < paragraphList[i]->nodeList.size(); j++){
			cout << paragraphList[i]->nodeList[j]->word << ": ";
			for (int k = 0; k < paragraphList[i]->nodeList[j]->pList.size(); k++){
				cout << paragraphList[i]->nodeList[j]->pList[k];
				if (paragraphList[i]->nodeList[j]->pList.size() - 1 != k){
					cout << ", ";
				}
			}
			cout << endl;
		}

	}

}

// This reads in the user query from stdin
vector<string> query;
void inputQuery(string s) {
	/*
	input a query
	remove stop words
	stem words
	*/
	stringstream iss(s);
	string m;
	while (getline(iss, m, ' ')){
		stem(m);
		query.push_back(m);
	}
	cout << "You input: ";
	for (int i = 0; i < query.size(); i++){
		cout << query[i];
		if (query.size() - 1 != i){
			cout << ", ";
		}
	}
	cout << endl;
}

// This returns the amount of times that the query occurred in the doc
void returnResults(){

}

// Main method
int main() {
	populateMap();// puts the stop words in a map for quick access
	getFile();	// reads std for the file to be input.
	stemFile();// reads std for the file to be input.
	index();
	inputQuery("Put your query input here");
	printList();
}
