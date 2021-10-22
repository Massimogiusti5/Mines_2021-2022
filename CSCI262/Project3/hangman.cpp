/*
    hangman.cpp
        
    Method implementations for the hangman class.
    
    assignment: CSCI 262 Project - Evil Hangman        

    author: Massimo Giusti

    last modified: 10/22/2021
*/

#include "hangman.h"
#include <fstream>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <iostream>

using namespace std;

// constructor
// left blank
hangman::hangman() { 
}


// start_new_game()
//
// Setup a new game of hangman.
void hangman::start_new_game(int num_guesses, int length) {
    hiddenWord = "";
    isWon = false;
    isLost = false;
    family = "";
    guesses = num_guesses;
    //initalize default family: "----" length n, where n is user inputted length for word
    for(int i = 0; i < length; i++){
        family.push_back('-');
    }
    //push all words of length n to set
    string input;
    ifstream fin("dictionary.txt");
    while(!fin.eof()){
        getline(fin, input);
        if(input.size() == length){
            words.emplace(input);
        }
    }
}


// process_guess()
//
// Process a player's guess - should return true/false depending on whether
// or not the guess was in the hidden word.  If the guess is incorrect, the
// remaining guess count is decreased.
bool hangman::process_guess(char c) {
    guessedChars.push_back(c);
    //clear map every guess
    families.clear();
    string curFamily = family;
    int max = 0;
    //for each element in set
    for(unordered_set<string>::iterator it = words.begin(); it != words.end(); it++){
        //for each char in set element
        for(int i = 0; i < (*it).size(); i++){
            //if char matches with i, update the family current word belongs to
            if((*it).at(i) == c){
                curFamily.at(i) = c;
            }
        }
        //push word to corresponding family in map
        //value of map is a vector of all the belonging words
        families.insert(pair<string,vector<string>> (curFamily, vector<string>()));
        families[curFamily].push_back((*it));
        //reset family to default for next word
        //default family is the display word every round
        curFamily = family;
    }
    
    //go through map and find family with most words
    //store that key to curFamily
    for(unordered_map<string,vector<string>>::iterator it = families.begin(); it != families.end(); it++){
        if(it->second.size() > max){
            max = it->second.size();
            curFamily = it->first;
        }
    }

    //go through and delete all non-belonging words to curFamily
    words.clear();
    for(int i = 0; i < families[curFamily].size(); i++){
        words.emplace(families[curFamily].at(i));
    }

    //logic to determine good guess or not
    //if the family did not change, i.e, the most occurring family was the default, return false
    if(curFamily == family){
        guesses--;
        //reduce guesses and check for loss
        if(guesses == 0){
            isLost = true;
            hiddenWord = *words.begin();
        }
        return false;
    //else update default family and check for win
    //win condition is if there is 1 word left and all the letters are revealed
    }else{
        family = curFamily;
        if(words.size() == 1 && family == *words.begin()) isWon = true;
        return true;
    }
}


// get_display_word()
//
// Return a representation of the hidden word, with unguessed letters
// masked by '-' characters.
string hangman::get_display_word() {
    return family;
}

string hangman::print_remaining(){
    string size = to_string(words.size());
    if(!showRemaining){
        return ("Words in chosen family: " + size);
    }else{
        return "";
    }
}


// get_guesses_remaining()
//
// Return the number of guesses remaining for the player.
int hangman::get_guesses_remaining() {
    return guesses;
}


// get_guessed_chars()
//
// What letters has the player already guessed?  Return in alphabetic order.
string hangman::get_guessed_chars() {
    sort(guessedChars.begin(), guessedChars.end());
    return guessedChars;
}


// was_char_guessed()
//
// Return true if letter was already guessed.
bool hangman::was_char_guessed(char c) {
    for(int i = 0; i < guessedChars.size(); i++){
        if(guessedChars.at(i) == c) return true;
    }
    return false;
}


// is_won()
//
// Return true if the game has been won by the player.
bool hangman::is_won() {
    return isWon;
}


// is_lost()
//
// Return true if the game has been lost.
bool hangman::is_lost() {
    return isLost;
}


// get_hidden_word
//
// Return the true hidden word to show the player.
string hangman::get_hidden_word() {
    return hiddenWord;
}


