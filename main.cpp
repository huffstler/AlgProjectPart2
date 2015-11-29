//
//  main.cpp
//  ProjectII
//
//  Created by Foster Clark on 11/29/15.
//  Copyright © 2015 Foster Clark. All rights reserved.
//

#include <iostream>
#include <cstdlib>
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



string stopWords[] = {"a","about","above","across","after","afterwards","again","against","all","almost","alone","along","already","also","although","always","am","among","amongst","amoungst","amount","an","and","another","any",
    "anyhow","anyone","anything","anyway","anywhere","are","around","as","at","back","be","became","because",
    "become","becomes","becoming","been","before","beforehand","behind","being","below","beside","besides",
    "between","beyond","bill","both","bottom","but","by","call","can","cannot","cant","co","computer","con",
    "could","couldnt","cry","de","describe","detail","do","done","down","due","during","each","eg","eight",
    "either","eleven","else","elsewhere","empty","enough","etc","even","ever","every","everyone","everything","everywhere","except","few","fifteen","fify","fill","find","fire","first","five","for","former",
    "formerly","forty","found","four","from","front","full","further","get","give","go","had","has","hasnt",
    "have","he","hence","her","here","hereafter","hereby","herein","hereupon","hers","him","his","how",
    "however","hundred","i","ie","if","in","inc","indeed","interest","into","is","it","its","keep","last",
    "latter","latterly","least","less","ltd","made","many","may","me","meanwhile","might","mill","mine",
    "more","moreover","most","mostly","move","much","must","my","name","namely","neither","never",
    "nevertheless","next","nine","no","nobody","none","noone","nor","not","nothing","now","nowhere",
    "of","off","often","on","once","one","only","onto","or","other","others","otherwise","our","ours",
    "ourselves","out","over","own","part","per","perhaps","please","put","rather","re","same","see",
    "seem","seemed","seeming","seems","serious","several","she","should","show","side","since","sincere",
    "six","sixty","so","some","somehow","someone","something","sometime","sometimes","somewhere","still",
    "such","system","take","ten","than","that","the","their","them","themselves","then","thence","there",
    "thereafter","thereby","therefore","therein","thereupon","these","they","thick","thin","third",
    "this","those","though","three","through","throughout","thru","thus","to","together","too","top",
    "toward","towards","twelve","twenty","two","un","under","until","up","upon","us","very","via",
    "was","we","well","were","what","whatever","when","whence","whenever","where","whereafter",
    "whereas","whereby","wherein","whereupon","wherever","whether","which","while","whither","who",
    "whoever","whole","whom","whose","why","will","with","within","without","would","yet","you",
    "your","yours","yourself","yourselves"};



void importData(){
    //string importedData[500];
    list<string> importedData;
    string tempStringP;
    int count = 0;
    //unordered_map<string, int> m;
    while (getline(cin, tempStringP, '\n')){ //reads in a line from ideone
        for (int i = 0; tempStringP[i] != '\0'; i++){//lowercase everything
            tempStringP[i] = tolower(tempStringP[i]);
        }
    }
    
        stringstream iss(tempStringP);
        while (getline(iss, tempStringP, ' ')){ //get string up to a space
            tempStringP.erase(0,1);
            importedData.push_back(tempStringP);
            //.add(tempStringP);
            count++;
        }
               
               cout << &importedData << " ";
}

               
               
               
               
               
               




// This reads in an input file from stdin
void getFile() {
    
}

// this removes stop words from the input (and the query)
void stopwords() {
    
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