#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "personality_test.h"

using namespace std;

void load_file(personality_test&);

/* main
 * Calls necessary functions in this file as well as functions in personality_test
 * @param None
 * @return None, Text to Console
 */
int main () {
    cout << "====================================" << endl;
    cout << "Welcome to CSCI262 Personality Test!" << endl;
    cout << "====================================" << endl << endl;


    personality_test test;
    load_file(test);
    test.run_test();

    //prompts the user whether or not to continue
    while(true){
        cout << "Do you want to play again?" << endl;
        string input = "";
        cin >> input;
        if(input == "Y" || input == "y" ||  input == "yes" || input == "Yes" ||input == "YES"){
            test.listOfQuestions.clear();
            load_file(test);
            test.run_test();

        }else{
            break;
        }
    }
}

/* Load File Method
 * 1) Prompt the user for a file name. 
 * 2) Confirm that the file can be loaded
 * 3) Run personality_test::load to load in the data
 * 4) If personality_test::load fails, report this and retry
 * @param personality_test object (by reference)
 * @return None, Text to Console
 */
void load_file(personality_test& test) {
        ifstream fin;
        string fileName;
    while (true) {
        cout << "Please enter the input file name, e.g., \"questions.txt\": ";
        cin >> fileName;
        fin.open(fileName); 
        if(!fin){ 
            cout << "error opening file \"" << fileName << "\"" << endl;
        //check for valid file using test.load()
        }else if(!test.load(fin)){
            cout << "Input file \"" << fileName << "\" appears to not be a proper file!" << endl;
            fin.close();
        }else{
            break;
        }
    }
}
