#ifndef _QUESTION_H
#define _QUESTION_H

#include <string>
using namespace std;

class question{
    public:
        string category_id;
        string question_id;
        string yes_answer;
        string no_answer;
        question(string category_id, string question, string yes_answer, string no_answer);
};

#endif