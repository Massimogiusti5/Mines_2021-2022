Massimo Giusti
CSCI262: Data Structures
Project 4: Markov
11/3/2021

1) No collaborators

2) A challenge I had was making the text generation accurate. My data structure for both the word model and map model
   was a map<string, vector<string>>. This means that the keys were strings, and when the order is greater than one,
   the strings would be longer than one word or one char, which made word generation difficult. My generation algorithm
   started with a random key, and then given a random element at that key, append that to result then update the key with the 
   corresponding random value generated. The problem with this was with higher order chains. To solve this, I had
   to enhance the pattern matching by using substrings and trimming the current key so that I could find the next
   corresponding key in the chain. 

3) I did not really enjoy this assignment. The instructions were very vague, and I found myself very confused or stuck
   at times when thinking of what to do next. In addition, the starter code is very difficult to understand, so a lot of my
   struggles were just figuring out what was going on with the starter code and then the assignment instructions were vague 
   especially for the word model. I caught myself going constantly in the wrong direction, and the developement process
   for the models was not enjoyable due to the difficult debugging.

4) I spent a few hours on this assignment. Probably close to 3-3.5 hours.