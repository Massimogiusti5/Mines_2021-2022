/*
   CSCI 262 Data Structures, Fall 2019, Project 4 - Markov

   Author: Massimo Giusti

   Modified: 11/3/2021
*/

#include "map_model.h"
#include <unordered_map>
#include <vector>
#include <sstream>
#include <string>
#include <iostream>
#include <time.h>
using namespace std;

void map_model::initialize(string text, int order) {
    char_map.clear();
    string temp = "";

    //add wrap around
    temp = text.substr(0,order);
    text += temp;
    //for each susbstring length order:
    for(int i = 0; i < text.size()-order; i++){
        temp = text.substr(i, order);
        char_map.insert(pair<string, vector<char>> (temp, vector<char>()));
        //push the next char to the map at key substring
        char_map[temp].push_back(text.at(i+order));
    }
}

string map_model::generate(int size) {
    //get random index of map
    auto it = char_map.begin();
    advance(it, rand() % char_map.size());
    string result = "";
    string str = "";


    for(int i = 0; i < size; i++){
        //get random element at random key
        int randInt = rand() % it->second.size();
        str = it->second.at(randInt);
        //append to result
        result += str;
        
        //new key becomes matched with a substring of [1,key] + next char
        //this is done to ensure that maps with order > 1 can be accurate
        it = char_map.find(it->first.substr(1, it->first.length()-1) + str);
        
        
    }

    return result;
}
