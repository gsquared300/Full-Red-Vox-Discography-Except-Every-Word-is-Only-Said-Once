/*
	Known errors:
		If a word starts with an open parenthesis (probably other puctuation as well), the last character will be left out.
		Seems to only affect contractions though (i.e "(They'll" turning into "they'l")
		Should be able to detect while editing the songs, but should still fix. 
*/

#include <iostream> //adds functionality to input and output data to the terminal or, in this case, a file
#include <fstream> //adds functionality to interact with other files
#include <string> //adds functionality of strings of letters. Yes, you have to tell the program you want to be able to store multiple letters in a variable. Whee.
#include <vector> //adds functionality for a vector, or a list of variables.
#include <algorithm> //Not 100% sure what exactly this adds, but in this case it allows me to delete characters from an array or string

using namespace std;

typedef pair<string, int> wPair; //typedef basically allows you to refer to something as something else, in this case a pair of string and int being called a wPair. Pairs are basically types of variables that store two values.

ifstream inFile; //defines the input file
ofstream outFile("lyrics2.txt"); //defines the output file and its name
string word; //defines the are where the current word from the file will be stored.
vector<wPair> array; //defines the list that will be used to store the words that have already been used, as well the number of times they have been used. Note it's called array since I originally used an array but swiched to a vector since arrays are for when you want a limit to how many elements you can store in the list.
bool isInFile; //defines a true or false statement for whether or not a word is in the file.


vector<wPair> quickSort(const vector<wPair> &orig){ //This is quicksort. Basically sorts a list of stuff, in this case a vector of wPairs. If you want to know how quicksort works, look it up.
    if(orig.size() <= 1){
        return orig;
    }
    vector<wPair> ret;
    for(int i = 0; i < orig.size(); i++){
        ret.push_back(orig[i]);
    }
    if(ret.size() == 2){
        if(ret[0].second < ret[1].second){
            wPair temp = ret[0];
            ret[0] = ret[1];
            ret[1] = temp;
        }
        return ret;
    }
    wPair pivot = ret[0];
    vector<wPair> one;
    vector<wPair> two;
    for(int i = 0; i < ret.size(); i++){
        if(ret[i].second < pivot.second){
            two.push_back(ret[i]);
        }else if(ret[i].second > pivot.second){
            one.push_back(ret[i]);
        }
    }
    one = quickSort(one);
    two = quickSort(two);
    int j;
    for(j = 0; j < one.size(); j++){
        ret[j] = one[j];
    }
    ret[j] = pivot;
    for(int i = 0; i < two.size(); i++){
        j++;
        ret[j] = two[i];
    }
    return ret;
}

int main(){
    
    inFile.open("lyrics.txt", ios::in | ios::app);//defines inFile as any file named lyrics.txt in the directory the program is located in.
    
    while(!inFile.eof()){ //while the program has not reached the end of the file, run lines 20 to 45.
        isInFile = false;
        inFile>>word; //go to the next line of the file and store whatever is on it to word.
      	for(int i = 0; i < word.length(); i++){ //count to the number of characters in the word and loop lines 23 to 34 while what your count is less than the size of the list.
          	if(word[i] >= 65 && word[i] <= 90)word[i]+=32; //If the ASCII value of the ith character is an uppercase letter, make it lower case (see https://theasciicode.com.ar/ascii-table-characters.pdf)
			else if(word[i] == -30 && word[i+1] == -128 && word[i+2] == -103){ //So apparently there is a different apostrophe in unicode that gets translated into three characters when viewed in ASCII. This checks for it and changes it to a regular apostrophe. This different apostrophe first appeared in the lyrics for Visions. Thanks Vin.
				word[i+1]='\'';
				word.erase(remove(word.begin(), word.end(), word[i]), word.end());
				word.erase(remove(word.begin(), word.end(), word[i+1]), word.end());
				i--;
			}
			else if((word[i] < 97 || word[i] > 122) && (word[i] != '\\' && word[i] != '/' && word[i] != '\'')){ //If the ith character is a punctuation other than \ or / (which I use as tally markers between songs) or '
				word.erase(remove(word.begin(), word.end(), word[i]), word.end()); //delete it
				i--; //go back a character since we haven't processed the new ith character.
			}
        }
        for(int i = 0; i < array.size(); i++){ //count to the number of words in the list and loop lines 37 to 40 while what your count is less than the size of the list.
            if(array[i].first == word){ //if the word is in the list
                isInFile = true;
				array[i].second++; //increment the number of times the word is used by one.
                break;//stop the loop
            }
        }
        if(!isInFile){ //if isInFile = false
			outFile << word << " "; //put word into the output file
            array.push_back(make_pair(word, 0)); //put the word on the list
        }
    }
	cout << "Number of unique words: " << array.size() << endl << endl; //Show the number of unique words on the screen.
	array = quickSort(array); //sort the list of words according to the number of times they appear.
	cout << "Top 10 most used words:" << endl;
	for(int i = 0; i < 10; i++){
		cout << array[i].first << ": " << array[i].second << endl;
	}
	return 0; //Stop the program.
}