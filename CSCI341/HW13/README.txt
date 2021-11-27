Massimo Giusti
CSCI 341: Computer Organization
11/15/2021

1) Collaborators: none
2) Pseudocode (c)

int[] branchPredictionSim(int[] values, int size);
    int state = 0;
    int predictions[size];
    for(int i = 0; i < size; i++){
        if(state < 2){
            predictions[i] = 1;
        }else{
            predictions[i] = 2;
        }
        if(values[i] == 2){
            if(state < 3){
                state++;
            }
        }else{
            if(state > 0){
                state--;
            }
        }
    }
    return predictions;
}

3) This homework was pretty straightforward. The only issue I had was figuring out how to manage labels. The above 
   pseudocode has many if-statements, which means that implementing all the branch statements was difficult to plan 
   out, but after that, the algorithm came easy.

4) What I liked about this assignment was being able to test how accurate a dynamic branch predictor actually was 
   given a list of branch history. I also thought coming up with the algorithm for the branch predictor was fun.

5) I spent about an hour on this assignment.

6) No ec features. 