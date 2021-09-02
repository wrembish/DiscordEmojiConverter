#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

// creates a map from the character (the key) to a vector of possible emoji strings
// from the text file containing the data
map<char, vector<string>> get_conversion_map() {
	// the empty map we are going to fill in
	map<char, vector<string>> output_map;
	
	// input file stream to get the text from the input file
	ifstream ifs("letter_to_emoji.txt");
	
	// converts the ifstream to a string
	string line;
    line.assign((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));
	
	// declare a variable to hold the key, the emoji conversion, 
	// whether or not the next character is a key, and a vector to hold the emoji strings
	char key;
	string convert = "";
	bool isKey = true;
	vector<string> values;
	
	// loop through the string we made from the input file
	for(int i = 0; i < line.length(); i++) {
		
		// if this character is a key
		if(isKey) {
			// set key to the character
			key = line[i];
			// stop this if statement from being true for now
			isKey = false;
		} else if(line[i] == '=') {
			// if the character is a '=' ignore it
		} else if(line[i] == '\n') { // if the character is an endline character
			//add the last emoji string to the vector
			values.push_back(convert);
			// reset the emoji string for the next iteration
			convert = "";
			// add the key we grabbed earlier and the vector of emoji strings to the map
			output_map.insert(pair<char,vector<string>>(key,values));
			// clear the emoji string vector
			values.clear();
			// the next character WILL be a key
			isKey = true;
		} else if(line[i] == ' ') { // if the character is a space
			// make sure the emoji string isn't blank or a space for some reason
			if(convert != "" && convert != " ") {
				// then add it to the emoji string vector
				values.push_back(convert);
			}
			// reset the emoji string regardless
			convert = "";
		} else { // otherwise you add the character to the emoji string
			convert += line[i];
		}

	}
	// add the last key values pair that doesn't already get added to the map
	values.push_back(convert);
	output_map.insert(pair<char,vector<string>>(key,values));
	
	// return the value
	return output_map;
};

// actually convers a input string to a bunch of emojis
string convert_to_emoji(string input) {
	// make a random seed for random based on the time
	srand(time(NULL));
	// make a blank string to hold the emoji converted string
	string output = "";
	// get the conversion map
	map<char,vector<string>> conversionMap = get_conversion_map();
	// iterate through each character of the input string
	for(int i = 0; i < input.size(); i++) {
		// add a randomly generated selection from the current characters mapped
		// emoji strings and a space after it
		output += conversionMap[toupper(input[i])][rand()%conversionMap[toupper(input[i])].size()] + " ";
	}
	
	//return the new string
	return output;
};

int main() {
	cout << "enter the word to convert: ";
	string toConvert, converted;
	std::cin >> toConvert;
	converted = convert_to_emoji(toConvert);
	cout << converted << endl;
};