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

bool isVowel(char ch);

bool isVowelY(char ch);

bool endsWith(const string& word, const string& str);

bool endsInDouble(const string& word);

bool replaceIfExists(string& word, const string& suffix,
	const string& replacement, size_t start);

bool isValidLIEnding(char ch);

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
struct Node{
	int pNum;
	vector<string> wordList;
};


// This reads in an input file from stdin
// Reads past new lines now
void getFile(){
	vector<string> importedData;
	string tempStringP;
	int listcount = 1;
	vector<Node*> paragraphList;
	//int count = 0;

	while (getline(cin, tempStringP)){ //reads in a line from ideone
		if (tempStringP == "/////"){
			Node *p = new Node;
			p->pNum = listcount;
			p->wordList = importedData;
			paragraphList.push_back(p);
			importedData.clear();
			listcount++;
			cout << "New paragraph" << endl;
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
	/*
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
	*/
	for (int i = 0; i < paragraphList.size(); i++)
	{	
		cout << "New Paragraph: ";
		for (int j = 0; j < paragraphList[i]->wordList.size(); j++){
			cout << paragraphList[i]->wordList[j]<< " -> ";
		}
		cout << endl;
	}



	//  printing function ends here
}

void populateMap() { // Done
	for (int i = 0; i < stopWords.size(); i++){
		mymap.insert(make_pair(strhash(stopWords[i]), stopWords[i]));
	}
}

// This stems the string that it is given
void stem(string& word)
{
	// special case short words or sentence tags
	if (word.size() <= 2 || word == "<s>" || word == "</s>")
		return;

	// max word length is 35 for English
	if (word.size() > 35)
		word = word.substr(0, 35);

	if (word[0] == '\'')
		word = word.substr(1, word.size() - 1);

	if (special(word))
		return;

	changeY(word);
	size_t startR1 = getStartR1(word);
	size_t startR2 = getStartR2(word, startR1);

	step0(word);

	if (step1A(word))
	{
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

void trim(string& word)
{
	if (word == "<s>" || word == "</s>")
		return;

	transform(word.begin(), word.end(), word.begin(), ::tolower);
	remove_if(word.begin(), word.end(), [](char ch)
	{
		return !((ch >= 'a' && ch <= 'z') || ch == '\'');
	});
}

size_t getStartR1(const string& word)
{
	// special cases
	if (word.size() >= 5 && word[0] == 'g' && word[1] == 'e' && word[2] == 'n'
		&& word[3] == 'e' && word[4] == 'r')
		return 5;
	if (word.size() >= 6 && word[0] == 'c' && word[1] == 'o' && word[2] == 'm'
		&& word[3] == 'm' && word[4] == 'u' && word[5] == 'n')
		return 6;
	if (word.size() >= 5 && word[0] == 'a' && word[1] == 'r' && word[2] == 's'
		&& word[3] == 'e' && word[4] == 'n')
		return 5;

	// general case
	return firstNonVowelAfterVowel(word, 1);
}

size_t getStartR2(const string& word,
	size_t startR1)
{
	if (startR1 == word.size())
		return startR1;

	return firstNonVowelAfterVowel(word, startR1 + 1);
}

size_t
firstNonVowelAfterVowel(const string& word,
size_t start)
{
	for (size_t i = start; i != 0 && i < word.size(); ++i)
	{
		if (!isVowelY(word[i]) && isVowelY(word[i - 1]))
			return i + 1;
	}

	return word.size();
}

void changeY(string& word)
{
	if (word[0] == 'y')
		word[0] = 'Y';

	for (size_t i = 1; i < word.size(); ++i)
	{
		if (word[i] == 'y' && isVowel(word[i - 1]))
			word[i++] = 'Y'; // skip next iteration
	}
}

/**
Step 0
*/
void step0(string& word)
{
	// short circuit the longest suffix
	replaceIfExists(word, "'s'", "", 0) || replaceIfExists(word, "'s", "", 0)
		|| replaceIfExists(word, "'", "", 0);
}

/**
Step 1a:

sses
replace by ss

ied   ies
replace by i if preceded by more than one letter, otherwise by ie
(so ties -> tie, cries -> cri)

us   ss
do nothing

s
delete if the preceding word part contains a vowel not immediately before
the
s (so gas and this retain the s, gaps and kiwis lose it)
*/
bool step1A(string& word)
{
	if (!replaceIfExists(word, "sses", "ss", 0))
	{
		if (endsWith(word, "ied") || endsWith(word, "ies"))
		{
			// if preceded by only one letter
			if (word.size() <= 4)
				word.pop_back();
			else
			{
				word.pop_back();
				word.pop_back();
			}
		}
		else if (endsWith(word, "s") && !endsWith(word, "us")
			&& !endsWith(word, "ss"))
		{
			if (word.size() > 2 && containsVowel(word, 0, word.size() - 2))
				word.pop_back();
		}
	}

	// special case after step 1a
	return word == "inning" || word == "outing" || word == "canning"
		|| word == "herring" || word == "earring" || word == "proceed"
		|| word == "exceed" || word == "succeed";
}

/**
Step 1b:

eed   eedly
replace by ee if in R1

ed   edly   ing   ingly
delete if the preceding word part contains a vowel, and after the
deletion:
if the word ends at, bl or iz add e (so luxuriat -> luxuriate), or
if the word ends with a double remove the last letter (so hopp -> hop), or
if the word is short, add e (so hop -> hope)
*/
void step1B(string& word, size_t startR1)
{
	bool exists = endsWith(word, "eedly") || endsWith(word, "eed");

	if (exists) // look only in startR1 now
		replaceIfExists(word, "eedly", "ee", startR1)
		|| replaceIfExists(word, "eed", "ee", startR1);
	else
	{
		size_t size = word.size();
		bool deleted = (containsVowel(word, 0, size - 2)
			&& replaceIfExists(word, "ed", "", 0))
			|| (containsVowel(word, 0, size - 4)
			&& replaceIfExists(word, "edly", "", 0))
			|| (containsVowel(word, 0, size - 3)
			&& replaceIfExists(word, "ing", "", 0))
			|| (containsVowel(word, 0, size - 5)
			&& replaceIfExists(word, "ingly", "", 0));

		if (deleted && (endsWith(word, "at") || endsWith(word, "bl")
			|| endsWith(word, "iz")))
			word.push_back('e');
		else if (deleted && endsInDouble(word))
			word.pop_back();
		else if (deleted && startR1 == word.size() && isShort(word))
			word.push_back('e');
	}
}

/**
Step 1c:

Replace suffix y or Y by i if preceded by a non-vowel which is not the first
letter of the word (so cry -> cri, by -> by, say -> say)
*/
void step1C(string& word)
{
	size_t size = word.size();
	if (size > 2 && (word[size - 1] == 'y' || word[size - 1] == 'Y'))
		if (!isVowel(word[size - 2]))
			word[size - 1] = 'i';
}

/**
Step 2:

If found and in R1, perform the action indicated.

tional:               replace by tion
enci:                 replace by ence
anci:                 replace by ance
abli:                 replace by able
entli:                replace by ent
izer, ization:        replace by ize
ational, ation, ator: replace by ate
alism, aliti, alli:   replace by al
fulness:              replace by ful
ousli, ousness:       replace by ous
iveness, iviti:       replace by ive
biliti, bli:          replace by ble
fulli:                replace by ful
lessli:               replace by less
ogi:                  replace by og if preceded by l
li:                   delete if preceded by a valid li-ending
*/
void step2(string& word, size_t startR1)
{
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

	if (!replaceIfExists(word, "logi", "log", startR1 - 1))
	{
		// make sure we choose the longest suffix
		if (endsWith(word, "li") && !endsWith(word, "abli")
			&& !endsWith(word, "entli") && !endsWith(word, "aliti")
			&& !endsWith(word, "alli") && !endsWith(word, "ousli")
			&& !endsWith(word, "bli") && !endsWith(word, "fulli")
			&& !endsWith(word, "lessli"))
			if (word.size() > 3 && word.size() - 2 >= startR1
				&& isValidLIEnding(word[word.size() - 3]))
			{
				word.pop_back();
				word.pop_back();
			}
	}
}

/**
Step 3:

If found and in R1, perform the action indicated.

ational:            replace by ate
tional:             replace by tion
alize:              replace by al
icate, iciti, ical: replace by ic
ful, ness:          delete
ative:              delete if in R2
*/
void step3(string& word, size_t startR1,
	size_t startR2)
{
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

/**
Step 4:

If found and in R2, perform the action indicated.

al ance ence er ic able ible ant ement ment ent ism ate
iti ous ive ize
delete
ion
delete if preceded by s or t
*/
void step4(string& word, size_t startR2)
{
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

	// make sure we only choose the longest suffix
	if (!endsWith(word, "ement") && !endsWith(word, "ment"))
		if (replaceIfExists(word, "ent", "", startR2))
			return;

	// short circuit
	replaceIfExists(word, "sion", "s", startR2 - 1)
		|| replaceIfExists(word, "tion", "t", startR2 - 1);
}

/**
Step 5:

e     delete if in R2, or in R1 and not preceded by a short syllable
l     delete if in R2 and preceded by l
*/
void step5(string& word, size_t startR1,
	size_t startR2)
{
	size_t size = word.size();
	if (word[size - 1] == 'e')
	{
		if (size - 1 >= startR2)
			word.pop_back();
		else if (size - 1 >= startR1 && !isShort(word.substr(0, size - 1)))
			word.pop_back();
	}
	else if (word[word.size() - 1] == 'l')
	{
		if (word.size() - 1 >= startR2 && word[word.size() - 2] == 'l')
			word.pop_back();
	}
}

/**
* Determines whether a word ends in a short syllable.
* Define a short syllable in a word as either
*
* (a) a vowel followed by a non-vowel other than w, x or Y and preceded by a
*non-vowel
* (b) a vowel at the beginning of the word followed by a non-vowel.
*/
bool isShort(const string& word)
{
	size_t size = word.size();

	if (size >= 3)
	{
		if (!isVowelY(word[size - 3]) && isVowelY(word[size - 2])
			&& !isVowelY(word[size - 1]) && word[size - 1] != 'w'
			&& word[size - 1] != 'x' && word[size - 1] != 'Y')
			return true;
	}
	return size == 2 && isVowelY(word[0]) && !isVowelY(word[1]);
}

bool special(string& word)
{
	static const unordered_map<string, string> exceptions
		= { { "skis", "ski" },
		{ "skies", "sky" },
		{ "dying", "die" },
		{ "lying", "lie" },
		{ "tying", "tie" },
		{ "idly", "idl" },
		{ "gently", "gentl" },
		{ "ugly", "ugli" },
		{ "early", "earli" },
		{ "only", "onli" },
		{ "singly", "singl" } };

	// special cases
	auto ex = exceptions.find(word);
	if (ex != exceptions.end())
	{
		word = ex->second;
		return true;
	}

	// invariants
	return word == "sky" || word == "news" || word == "howe" || word == "atlas"
		|| word == "cosmos" || word == "bias" || word == "andes";
}

bool isVowelY(char ch)
{
	return ch == 'e' || ch == 'a' || ch == 'i' || ch == 'o' || ch == 'u'
		|| ch == 'y';
}

bool isVowel(char ch)
{
	return ch == 'e' || ch == 'a' || ch == 'i' || ch == 'o' || ch == 'u';
}

bool endsWith(const string& word,
	const string& str)
{
	return word.size() >= str.size()
		&& equal(word.begin() + (word.size() - str.size()), word.end(),
		str.begin());
}

bool endsInDouble(const string& word)
{
	if (word.size() >= 2)
	{
		char a = word[word.size() - 1];
		char b = word[word.size() - 2];

		if (a == b)
			return a == 'b' || a == 'd' || a == 'f' || a == 'g' || a == 'm'
			|| a == 'n' || a == 'p' || a == 'r' || a == 't';
	}

	return false;
}

bool replaceIfExists(string& word,
	const string& suffix,
	const string& replacement,
	size_t start)
{
	size_t idx = word.size() - suffix.size();
	if (idx < start)
		return false;

	if (equal(word.begin() + idx, word.end(), suffix.begin()))
	{
		word = word.substr(0, word.size() - suffix.size()) + replacement;
		return true;
	}
	return false;
}

bool isValidLIEnding(char ch)
{
	return ch == 'c' || ch == 'd' || ch == 'e' || ch == 'g' || ch == 'h'
		|| ch == 'k' || ch == 'm' || ch == 'n' || ch == 'r' || ch == 't';
}

bool containsVowel(const string& word,
	size_t start, size_t end)
{
	if (end <= word.size())
	{
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


	vector<string> Data;
	vector<vector<string>> Pgraphs;
	string tempStringP;
	int Pnumber = 0; //current paragraph number
	//while (getline(cin, tempStringP)){
	while (getline(cin, tempStringP, '\n')){ //reads in a line from ideone

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
		// cout << Pnumber << "\n";
		Pgraphs.push_back(Data);
		Data.clear();
	}

	//check where the words occur
	for (vector<vector<string>>::iterator iter = Pgraphs.begin(); iter != Pgraphs.end(); iter++){
		Pnumber++;
		for (vector<string>::iterator iter2 = iter->begin(); iter2 != iter->end(); iter2++){
			//this is where you input what you want to index
//			if (find(iter2->begin(), iter2->end(), tempStringP) != iter2->end()) {
//				cout << tempStringP << "is in the paragraph" << Pnumber;
//			}
		}
	}
}





//}

/*
//printing the lists
for(vector<vector<string>>::iterator iter = Pgraphs.begin(); iter!= Pgraphs.end(); iter++){
Pnumber++;
//  Pnumber = floor(Pnumber / 2);
for(vector<string>::iterator iter2 = iter->begin(); iter2!= iter->end(); iter2++){

cout << Pnumber << "\n ";
cout << *iter2;

if(iter2 == Data.end()) {
break;
} else {
cout << ", ";
}
}
}
*/



















// This reads in the user query from stdin
void getQuery() {

}

// This returns the amount of times that the query occurred in the doc
void returnResults(){

}

// Main method
int main() {
	string godly = "deformities";
	stem(godly);
	cout << godly << endl;
	//system("pause");
	populateMap();// puts the stop words in a map for quick access
	getFile(); // reads std for the file to be input.
	index();



}
