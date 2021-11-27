Massimo Giusti
CSCI262: Data Structures
Project5: 20 questions

1) Collaborators: none
2) A challenge I had with this project was correctly handling cin. To get user input, you can use either the >> operator or getline, 
   and each do different things with cin. For example, the arrow operator leaves a new line character at the beginning of cin, so a
   subsequent getline would return null. Since this project was heavily reliant on user input, alot of bugs I encountered were with cin.
   After solving that, a design issue I encountered was figuring out an algorithm to traverse the binary tree to play the game. I ended 
   up deciding on a recursive approach to all my functions. This is because recursing over the tree with DFS and left child having priority 
   ended up reading the tree in preorder traversal. This proved advantageous for reading data and general recursion also helped with
   later traversals through the graph.

3) What I liked about this assignment was how I was free to implement the design of the project pretty much on my own. I followed the instructions
   and the hints, but I still felt like I was the one coming up with the solution and design for the project, unlike the last couple projects.

4) I spent a few hours on this assignment, probably close to 4 hours.

5) No EC features.
