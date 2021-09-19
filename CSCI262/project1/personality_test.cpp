#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

#include "question.h"
#include "personality_test.h"

using namespace std;

/* Load method
 * 1) Provided an istream object, read in each line and process them accordingly
 * 2) Ensure to see if the input is "correct" (do at least one simple check, like first character is a number)
 * Input: istream object
 * Output: Boolean
 */
bool personality_test::load(istream &in) {
    string str = "";
    string category_id = "";
    string question_id = "";
    string yes_answer = "";
    string no_answer = "";

    getline(in, str); //skip first line
    while(!in.eof()){
        getline(in, str);
        istringstream stream(str);
        stream >> category_id;
        stream >> yes_answer;
        stream >> no_answer;
        getline(stream, question_id);
        //check for valid file format
        if(category_id.size() > 1 || yes_answer.size() > 1 || no_answer.size() > 1){
            //the last line starts with "@", skip over final line to ensure that the file remains valid
            if(category_id == "@"){
                break;
            }else{
                return false;
            }
        }
        //data structure is a list of questions
        listOfQuestions.push_back(question(category_id, question_id, yes_answer, no_answer));
    }
    return true;
}

/* Run Test method
 * 1) Call proper methods in order to run the test
 * @param: None
 * @return: None, Text to Console
 */
void personality_test::run_test() {
    string output = analyze_personality();
    categorize_output(output);
}

/* Analyze Personality Method
 * 1) Ask user one question at a time
 * 2) Read in user's response and construct a STRING containing the responses
 * 3) Analyze the responses to construct a personality type (eg. ENFJ)
 * @param None
 * @return string
 */
string personality_test::analyze_personality() {
    string output = "";
    string input = "";
    for(int i = 0; i < listOfQuestions.size(); i++){
        while(true){
            cout << "Question #: " << listOfQuestions[i].category_id;
            cout << " " << listOfQuestions[i].question_id << endl;
            cin >> input;
            if(input == "Y" || input == "y" ||  input == "yes" || input == "Yes" ||input == "YES"){
                output += listOfQuestions[i].yes_answer;
                break;
            }else if(input == "N" || input == "n" ||  input == "no" || input == "No" ||input == "NO"){
                output += listOfQuestions[i].no_answer;
                break;
            }else{
                cout << "Sorry, I didn't recognize your input, please type again" << endl;
            }
        }
    }
    return output;
}

/* Categorize Output Method
 * 1) Read in the analysis.txt file
 * 2) Provided a user's personality type, print out to console the user's personality description
 * @param Personality type string (eg. "ENFJ")
 * @return None, Text to console
 */
void personality_test::categorize_output(string my_personality) {
    //vector indeces represent occurences of each personality letter 
    ifstream fin("analysis.txt");
    string line = "";
    //analysis.txt components
    string personalityType = "";
    string category = "";
    string type = "";
    string description = "";
    string myPersonalityType = "";
    string output = "";
    vector<char> letters = {'I','E','N','S','T','F','J','P'};
    vector<int> occurences = {0,0,0,0,0,0,0,0};
    //loop to get occurences of each personality trait letter
    for(int i = 0; i < letters.size(); i++){
        for(int j = 0; j < my_personality.size(); j++){
            if(letters[i] == my_personality[j]){
                occurences[i]++;
            }
        }
    }
    /* since each personality trait is composed of 4 digits with two traits per digit,
     * pairs of traits can be examined at a time to compose the overall personality trait
     */
    for(int i = 0; i < occurences.size(); i += 2){
        if(occurences[i] > occurences[i+1]){
            myPersonalityType += letters[i];
        }else{
            myPersonalityType += letters[i+1];
        }
    }
    getline(fin, line);
    //read analysis.txt for matching trait to myPersonalityType
    while(!fin.eof()){
        getline(fin, line);
        istringstream stream(line);
        stream >> personalityType;
        if(personalityType == myPersonalityType){
            stream >> category;
            stream >> type;
            getline(stream, description);
            //prints trait and stores it in order to pass it to save_output
            output += "Your personality type is: " + personalityType + "\n\n";
            output += "The category is: " + category + "\n\n";
            output += "You are: " + type + "\n\n";
            output += "Description:" + description + "\n\n"; 
            cout << "======================" << endl << output << "======================" << endl;
            break;
            //once trait is found, loop can end
        }
    }
    cout << "Do you want to save?" << endl;
    string input = "";
    cin >> input;
    if(input == "Y" || input == "y" ||  input == "yes" || input == "Yes" ||input == "YES"){
       save_output(output);
    }
}

/* Save Output
 * 1) Ask user to save or not
 * 2) If yes, ask for a file name and save the results
 * @param string (the thing to write)
 * @return None, creates a file
 */
void personality_test::save_output(string output) {
    string fileName;
    cout << "Please enter a file name" << endl;
    cin >> fileName;
    ofstream myFile(fileName);
    myFile << output; 
    myFile.close(); 
}