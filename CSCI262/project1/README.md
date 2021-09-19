# Project 1: Personality Test

- Massimo Giusti
- 09/04/2021
- CSCI 262

## Features

- Personality_test allows the user to input a file and then be told their personality type.
- In addition, it will catch incorrectly formatted files and handles errors with reading files.
- save_output also allows the user to save their personality type to the file of their choice.
- After taking the personality test, the user can redo the test with any other file as many times as they want.

## Developement

- I chose to make a question class to handle the data that came from parsing the questions file.
- My data structure was a `vector<question>` as a public member of the personality_test class.
- I also chose to store the question answers as a string which were then parsed into a personality type.

## Testing 

- In order to test whether the input file was formatted correctly, I looked at the first few elements of each line. I knew that the first and last line were not going to follow the format, so I included exceptions for them.
- for each question line, however, i tested whether or not the input I got from stream was longer than 1 char. This would work because the questions were numbered 1-4 and the personality traits were denoted as single letters, so if the first few elements of each line was larger than a char, then the file would be incorrectly formatted.
- in addition, I had tried to check for integers at the beginning of the line, but istringstream parsed the int to string early, and I could not get `isdigit()` and `stoi()` working.