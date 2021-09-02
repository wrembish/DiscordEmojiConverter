#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
using namespace std;


// creates the character to vector of string map from the text file containing that data
map<char, vector<string>> get_conversion_map() {
	map<char, vector<string>> output_map;
	
	// reads all the text from the text file and makes it a string
	ifstream ifs("letter_to_emoji.txt");
	stringstream buffer;
	buffer << ifs.rdbuf();
	string line = buffer.str();
	
	char key;
	string emoji = "";
	bool isKey = true; // make it true if the next character is the start of a new line, false otherwise
	vector<string> values;
	
	// iterate through the string to get all the keys and values for the map
	for(int i = 0; i < line.size(); i++) {
		
		if(isKey) { // gets the key and sets isKey to false
			key = line.at(i);
			isKey = false;
		} else if(line.at(i) == '=' || line.at(i) == '\r') {
			// ignores the '=' character which is only in the input file to make it more human readable
			// also ignores the '\r' character which causes weird errors if you don't ignore it
		} else if(line.at(i) == '\n') { // on new line character add the key value pair to the map and reset everything
			values.push_back(emoji);
			output_map.emplace(key,values);
			
			emoji.clear();
			values.clear();
			isKey = true;
		} else if(line.at(i) == ' ') { // space means new emoji text so add what you got to the vector and reset
			if(emoji != "" && emoji != " ") { // make sure no empty strings or just spaces are added
				values.push_back(emoji);
			}
			emoji.clear();
		} else { // if none of the above are true, its just a character to add to the emoji string
			emoji += line.at(i);
		}

	}
	
	// make sure you grab the last key value pair and add it to the map
	values.push_back(emoji);
	output_map.emplace(key,values);
	
	return output_map;
};

// converts any input string to discord emoji's for each character
string convert_to_emoji(string input) {
	// seed random using the current time
	srand(time(NULL));
	string output = "";
	
	map<char,vector<string>> conversionMap = get_conversion_map();
	// loop through the string converting each character
	for(int i = 0; i < input.size(); i++) {
		// if there are multiple words, on space just add space otherwise go through continuing to convert each character
		if(input.at(i) == ' ') {
			output += " ";
		} else {
			// add a bit of randomness if there are multiple emojis to represent the letter
			int randoInt = rand()%conversionMap[toupper(input.at(i))].size();
			output += conversionMap[toupper(input.at(i))][randoInt] + " ";
		}
	}
	
	return output;
};

int main() {
	cout << "enter the word to convert: ";
	string toConvert, converted;
	getline(cin, toConvert);
	converted = convert_to_emoji(toConvert);
	cout << converted << endl;
};
