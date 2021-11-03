/*
   CSCI 262 Data Structures, Fall 2019, Project 4 - Markov

   Author: Massimo Giusti

   Modified: 11/3/2021
*/

#include "word_model.h"
#include <unordered_map>
#include <vector>
#include <sstream>
#include <string>
#include <iostream>


void word_model::initialize(string text, int order) {
    str_map.clear();
    string temp = "";
    string next = "";
    stringstream stream = stringstream(text);
    vector<string> data;

    //push each word onto data vector
    while(!stream.eof()){
        getline(stream,temp, ' ');
        data.push_back(temp);
    }
    //wrap around
    for(int i = 0; i < order; i++){
        data.push_back(data.at(i));
    }

    //for each word, create a key that is a string of words length order
    for(int i = 0; i < data.size() - order; i++){
        temp = "";
        next = data.at(i + order);
        //get string of words according to order
        for(int j = 0; j < order; j++){
            temp += data.at(i + j);
            temp += " ";
        }
        //put that key onto the map with value of the next word in the data
        str_map.insert(pair<string, vector<string>> (temp, vector<string>()));
        str_map[temp].push_back(next);
    }
}


string word_model::generate(int size) {
    //get random key
    auto it = str_map.begin();
    advance(it, rand() % str_map.size());
    string result = "";
    string temp = " ";
    string str = "";

    for(int i = 0; i < size; i++){
        //get random element at random index
        int randInt = rand() % it->second.size();
        str = it->second.at(randInt);
        //append that random element to result
        result += str;
        result += " ";
        //set random element to key for next iteration
        if(str_map.find(str) != str_map.end()){    
            it = str_map.find(str);
        }else{
            //if order is greater than one, we need some more sophisticated pattern matching to get the next key
            //first, trim the key of the first word and append the current word added to result, str
            istringstream stream = istringstream(it->first);
            getline(stream, temp, ' ');
            getline(stream, temp);
            temp += str;
            temp += " ";
            //after the string is modified, find the corresponding key
            it = str_map.find(temp);
            
        }
    }

    return result;
}
