/*
 * main.cpp
 *
 * Starter code for the Circle Markers lab, CSCI 262
 */

#include <iostream>
#include <list>
#include <vector>

using namespace std;

int main() {
    int players = 0;
    int markers = 0;

    cout << "How many players will there be?" << endl;
    cin >> players;

    cout << endl;
    cout << "What is the highest numbered marker?" << endl;
    cin >> markers;

    cout << endl;
    int curPlayer = 1;
    vector<int> scores(players+1, 0);

    // This will hold our circle of markers
    list<int> game;
    game.push_front(0);
    list<int>::iterator it = game.begin();


    // Loop over all the rest of the markers
    for (int m = 1; m <= markers; m++) {
        if (m % 23 == 0) {
            scores.at(curPlayer) += m;
            //go 7 back
            for(int i = 0; i < 8; i++){
                if(it == game.begin()){
                    it = game.end();
                    it--;
                }else{
                    it--;
                }
            }
            //add to score
            scores.at(curPlayer) += *it;
            it = game.erase(it);
            it++;
        }else{
            if(it == game.end()){
                it = game.begin();
                it++;
                game.insert(it, m);
            }else{
                it++;
                game.insert(it, m);
            }
        }
	
        // advance to the next player
        if(curPlayer == scores.size()-1){
            curPlayer = 1;
        }else{
            curPlayer++;
        }
    }

    // game is over, let's see who won, with how many markers
    int high_score = 0;
    int winner = 0;
    for(int i = 0; i < scores.size(); i++){
        if(scores.at(i) > high_score){
            high_score = scores.at(i);
            winner = i;
        }
    } 
    cout << "The winner is player " << winner << " with a score of " << high_score << "!" << endl;
}


