#include <iostream> //adds functionality to input and output data to the terminal or, in this case, a file
#include <fstream> //adds functionality to interact with other files
#include <string> //adds functionality of strings of letters. Yes, you have to tell the program you want to be able to store multiple letters in a variable. Whee.
#include <vector> //adds functionality for a vector, or a list of variables.
#include <algorithm> //Not 100% sure what exactly this adds, but in this case it allows me to delete characters from an array or string

using namespace std;

ifstream inFile; //defines the input file
ofstream outFile("lyrics2.txt"); //defines the output file and its name
string word; //defines the are where the current word from the file will be stored.
vector<string> array; //defines the list that will be sued to store the words that have already been used. Note it's called array since I originally used an array but swiched to a vector since arrays are for when you want a limit to how many elements you can store in the list.
bool isInFile; //defines a true or false statement for whether or not a worde is in the file.

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
            if(array[i] == word){ //if the word is in the list
                isInFile = true;
                break;//stop the loop
            }
        }
        if(!isInFile){ //if isInFile = false
			outFile << word << " "; //put word into the output file
            array.push_back(word); //put the word on the list
        }
    }
	cout << "Number of unique words: " << array.size() << endl; //Show the number of unique words on the screen.
	return 0; //Stop the program.
}