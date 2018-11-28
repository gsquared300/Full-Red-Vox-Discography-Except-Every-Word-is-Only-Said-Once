#include <iostream> //adds functionality to input and output data to the terminal or, in this case, a file
#include <fstream> //adds functionality to interact with other files
#include <string> //adds functionality of strings of letters. Yes, you have to tell the program you want to be able to store multiple letters in a variable. Whee.
#include <vector> //adds functionality for a vector, or a list of variables.

using namespace std;

ifstream inFile; //defines the input file
ofstream outFile("lyrics2.txt"); //defines the output file and its name
string word; //defines the place where the current word from the file will be stored.
vector<string> array; //defines the list that will be sued to store the words that have already been used. Note it's called array since I originally used an array but swiched to a vector since arrays are for when you want a limit to how many elements you can store in the list.
bool isInFile; //defines a true or false statement for whether or not a worde is in the file.

int main(){
    
    inFile.open("lyrics.txt", ios::in | ios::app);//defines inFile as any file named lyrics.txt in the directory the program is located in.
    
    while(!inFile.eof()){ //while the program has not reached the end of the file, run lines 19 to 32.
        isInFile = false;
        getline(inFile, word); //go to the next line of the file and store whatever is on it to word.
        for(int i = 0; i < array.size(); i++){ //count to the number of words in the list and loop lines 22 to 25 while what your count is less than the size of the list.
            if(array[i] == word){ //if the word is in the list
                isInFile = true;
                break;//stop the loop
            }
        }
        if(!isInFile){ //if isInFile = false
            outFile << word; //put word into the output file
            array.push_back(word); //put the word on the list
        }
    }
    //technically supposed to be a return 0 here, but the program works either way
}
