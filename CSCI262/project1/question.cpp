#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include "personality_test.h"
#include "question.h"

using namespace std;



question::question(string category_id, string question_id, string yes_answer, string no_answer){
    this->category_id = category_id;
    this->question_id = question_id;
    this->no_answer = no_answer;
    this->yes_answer = yes_answer;
}

        