Massimo Giusti
CSCI 261: Data Structures
Project 2, Mazes

1. Collaborators: nobody

2. I didn't face many challenges during this project, although a design issue I encountered 
   was finding a way to store the stack and queue. I though about making it local, but the 
   sample code was designed for them to be global, so I declared them as such. In addition,
   I wanted to cut down on code by trying to automate the solve() function to work for both
   stacks and queues without repeating the algorithm. After trying to pass them to the function
   as structs and objects, I realized it wouldn't work due to the difference in interface. 
   Therefore, I resorted to making a case for solving the maze with stack and a case for solving
   the maze with queue.

3. What I liked about this assignment was the restriction on design. When first thinking of how
   I wanted to do the project, I immediately though of recursion and DFS, however I liked how
   the project incorporated stacks and queues to get to the same result.

4. I only spent a couple hours at most on coding this project up.

Note - Example mazes are in a sub-directory
Also note - .exe files are not in submission folder, and neither is CMakeLists

