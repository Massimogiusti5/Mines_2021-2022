#ifndef _PERSONALITY_TEST_H
#define _PERSONALITY_TEST_H

#include <string>
#include <vector>
#include <iostream>
#include "question.h"

using namespace std;

// personality test class
class personality_test {
    public:
        bool load(istream& fin);
        void printout(vector<string> str);
        void run_test();
        string analyze_personality();
        void categorize_output(string);
        void save_output(string);
        // Added a list of questions object to personality_test
        vector<question> listOfQuestions;
};


#endif
