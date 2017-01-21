//  pa2.cpp
#include <iostream>
#include "pa2.h"


//This method creates the 32 NULL nodes of memory
void LinkedList::createPages(){
    //This section is related to when the linked list does not exist yet, so the head has to be created first before anything else
    if(head == NULL){
        head = new Node();
        temp = head;
        return;
    }
    
    //temp2 represents the new node being added to the list
    Node *temp2 = new Node();
    temp -> next = temp2; //Connects the newest node to the list.
    temp = temp2;
}


//Other useful methods needed to help out with the methods for the menu options

//Checks if the program name is already used
bool LinkedList::isNameUsed(std::string programname){
    //Assumes that the program name is not taken yet
    bool isnametaken = false;
    
    //checks whether head has the same name
    if(head -> programname.compare(programname) == 0){
        isnametaken = true;
        return isnametaken; //exits out of this method
    }
    
    
    
    //temp is at the beginning of the list for comparison
    temp = head;
    
    //checks for every page that is not empty and has a program in it
    while(temp != NULL){
        if (temp -> programname.compare(programname) == 0){
            isnametaken = true;
            return isnametaken; //exits out of this method
        }
        
        //temp points to the next node for comparison
        temp = temp -> next;
    }
    return isnametaken;
}


//Accounts for the fact that each node represents 4 KB of memory, so proper conversions from KB to the amount of pages available
int kbToPage(int kb){
    int page;
    
    //if the user's program size is perfectly divisible by 4
    if((kb % 4) == 0){
        page = kb/4; //This will determine how many pages will be taken up
    }
    
    //if the user's program size was not perfectly divisible by 4
    else{
        page = (kb/4) + 1; // +1 because the remainder just takes up the next page
    }
    
    return page;
}




//MAIN MENU OPTION-RELATED METHODS BELOW
//1.) Add program (2 types to accomodate for best/worst fit algorithm)
//Parameters: Takes in desired program name, then spits out the amount of pages used on the 32 nodes, pageused: the amount of KB the user wants to be added to memory
void LinkedList::addProgramBest (std::string programname, int pageused){
    //Arbitrary location variables to keep track of which location is better for the new program to be stored in.
    Node *smallest = NULL; //keeps track of the smallest spot available for best fit
    Node *location = NULL; //keeps track of the possible smallest spot available
    //arbitrary counters of free pages available based on the arbitrary locations above
    int min = 0; //keeps track of the current minimum
    int count = 0;
    
    
    //Starts off at the beginning to compare which free spot is perfect for the best fit algorithm
    temp = head;
    
    //This part figures out where to add the new program to the 32 nodes of memory
    //Keeps running until it reaches the end of the linked list
    while(temp != NULL){
        
        //if the node being examined is used, skip to the next node. This also gives a chance to reset the temporary location and counter(count and location changes again once they find an empty node spot).
        if(temp -> nodeused == true){
            location = NULL;
            count = 0;
        }
        //if the node is empty, do the following
        if(temp -> nodeused == false){
            //This is related to when the starting position of the null node is found, keeps counting afterwards once more empty spots are found
            if(location == NULL){
                location = temp;
            }
            count++;
            //This runs when we find a node that does not contain a program/if we reached the end of the list
            //Also changes the min and smallest based on the count and location
            if((temp -> next == NULL) || (temp -> next -> nodeused)){
                //In the case where we do not have a min/the specific location of where the smallest amount of memory is at.
                if ((min == 0) && (count >= pageused)){
                    min = count;
                    smallest = location;
                }
                //If the count at a specific location is less than the current minimum. You want the smallest spot to fit the user's program's required memory space, but it has to have at least the amount that the user requires as well.
                else if((count < min) && (count >= pageused)){
                    min = count;
                    smallest = location;
                }
            }
            
        }
        
        //Keeps going through the 32 nodes until it reaches the end.
        temp = temp -> next;
    }//end of while loop
    
    //This runs if you don't have enough memory to add to the 32 nodes
    if((min == 0) || (smallest == NULL)){
        std::cout << "Error, not enough memory for " << programname << ".\n\n";
        return;
    }
    
    
    //This portion adds the program to the 32 nodes based on our min and location
    count = pageused;
    while (count > 0){
        smallest -> programname = programname;
        smallest -> nodeused = true;
        count--;
        smallest = smallest -> next;
    }
    
    //Statement prints out after the program is sucessfully added to the linked list
    std::cout << "Program " << programname << " added successfully: " << pageused << " page(s) used.\n\n";
    
}



void LinkedList::addProgramWorst(std::string programname, int pageused){
    //Arbitrary location variables to keep track of which location is better for the new program to be stored in.
    Node *largest = NULL; //keeps track of the smallest spot available for best fit
    Node *location = NULL; //keeps track of the possible smallest spot available
    //arbitrary counters of free pages available based on the arbitrary locations above
    int max = 0; //keeps track of the current minimum
    int count = 0;
    
    
    //Starts off at the beginning to compare which free spot is perfect for the best fit algorithm
    temp = head;
    
    //This part figures out where to add the new program to the 32 nodes of memory
    //Keeps running until it reaches the end of the linked list
    while(temp != NULL){
        
        //if the node being examined is used, skip to the next node. This also gives a chance to reset the temporary location and counter(count and location changes again once they find an empty node spot).
        if(temp -> nodeused == true){
            location = NULL;
            count = 0;
        }
        //if the node is empty, do the following
        if(temp -> nodeused == false){
            //This is related to when the starting position of the null node is found, keeps counting afterwards once more empty spots are found
            if(location == NULL){
                location = temp;
            }
            count++;
            //This runs when we find a node that does not contain a program/if we reached the end of the list
            //Also changes the min and smallest based on the count and location
            if((temp -> next == NULL) || (temp -> next -> nodeused)){
                //In the case where we do not have a min/the specific location of where the smallest amount of memory is at.
                if ((max == 0) && (count >= pageused)){
                    max = count;
                    largest = location;
                }
                //If the count at a specific location is less than the current minimum. You want the smallest spot to fit the user's program's required memory space, but it has to have at least the amount that the user requires as well.
                else if((count > max) && (count >= pageused)){
                    max = count;
                    largest = location;
                }
            }
            
        }
        
        //Keeps going through the 32 nodes until it reaches the end.
        temp = temp -> next;
    }//end of while loop
    
    //This runs if you don't have enough memory to add to the 32 nodes
    if((max == 0) || (largest == NULL)){
        std::cout << "Error, not enough memory for " << programname << ".\n\n";
        return;
    }
    
    
    //This portion adds the program to the 32 nodes based on our min and location
    count = pageused;
    while (count > 0){
        largest -> programname = programname;
        largest -> nodeused = true;
        count--;
        largest = largest -> next;
    }
    
    //Statement prints out after the program is sucessfully added to the linked list
    std::cout << "Program " << programname << " added successfully: " << pageused << " page(s) used.\n\n";
}



//2.)Kill Program: Removes the program and releases the memory
void LinkedList::killProgram(std::string programname){
    //In the case when the user tries to look for a programn named FREE
    if (programname.compare("FREE") == 0){
        std::cout << "This program does not exist.\n";
        return;
    }
    
    int programCounter = 0; //keeps track of how many programs are removed
    
    //If you know the head is equal to an already known program name, add that to the kill program counter
    if(head -> programname == programname){
        head -> programname = ""; //resets the program name to NULL
        head -> nodeused = false; //indicates that that page is no longer used
        programCounter++; //increase the kill counter by 1
    }
    
    //starts temp off at the beginning
    Node * temp = head;
    while(temp != NULL){
        if(temp -> programname == programname){
            temp -> programname = "";
            temp -> nodeused = false;//indicates that that page is no longer used
            programCounter++;
            
            //compares next node
            temp = temp -> next;
        }
        else{
            temp = temp -> next; //moves along if the program name is not equal to user input
        }
    }
    
    std::cout << "Program " << programname << " successfully killed, " << programCounter << " page(s) reclaimed.\n\n";
    
}




//3.)Fragmentation
//Fragments: When there are gaps in between the programs, isolated programs.
void LinkedList::fragmentation(){
    //starts the temp at the beginning for comparison
    temp = head;
    //accounts for the number of fragmentation within the memory
    int fragments = 0;
    
    //Goes through the whole list and looks for fragments.
    while(temp != NULL){
        //Possibility of incrementing only if the node is used and the next node is not used, then this counts as a fragment
        if(temp -> nodeused == true){
            //if the next nodes are used by a program, increment fragments, or if you reached the end of the list
            if (temp -> next == NULL || temp -> next -> nodeused == false){
                fragments++;
            }
        }
        
        //moves the temp to the next node
        temp = temp -> next;
    }
    
    //prints statement out
    std::cout << std::endl;
    std::cout << "There are " << fragments << " fragment(s).\n\n";
    
    
}





//4.)Print memory
void LinkedList::traverseAndPrint(){
    //Makes temp start at the beginning of the list
    temp = head;
    int newLine = 0; //creates a new line after going through 8 pages/nodes
    
    //Keeps running until it reaches the end of the linked list
    while(temp != NULL){
        //nodeUsed being false indicates that the node is not currently being used
        if (temp -> nodeused == false){
            if(newLine == 8){
                std::cout << std::endl;
                newLine = 0; //resets the row after skipping to the next line
            }
            std::cout << "FREE\t";
            
            //This moves the temp to the next node for comparison
            temp = temp -> next;
            newLine ++;
        }
        
        //Runs if temp -> nodeUsed == true instead. Therefore, the program's name gets printed instead of FREE
        else{
            if(newLine == 8){
                std::cout << std::endl;
                newLine = 0;
            }
            
            newLine++;
            std::cout << temp -> programname << "\t";
            temp = temp -> next;
            
        }
    }
}




//Calling up here in order for main method to use it.
int checkInput(std::string type, std::string programname);
std::string invalidFree(std::string &programname);


//Main Method

int main(int argc, char * argv[]) {
    std::string bestOrWorst = ""; //Related to the best/worst fit algorithm
    std::string programname = ""; //Parameter variable to keep track of the program names
    
    //Creates the Linked List with 32 pages in total
    LinkedList *memoryPage = new LinkedList;
    for(int page = 0; page < 32; page++){
        memoryPage -> LinkedList::createPages(); //calls the method from LinkedList class to create the 32 nodes
    }
    
    
    //This section is related to the terminal input for best/worst fit algorithm before the actual program begins
    if(argc != 2){
        std::cout << "Wrong number of arguments.\n";
        return -1;
    }
    else if(std::string(argv[1]) == "worst"){
        bestOrWorst = "worst";
    }
    else if(std::string(argv[1]) == "best"){
        bestOrWorst = "best";
    }
    else{
        std::cout << "Unknown command." << std::endl;
        return -1; //ends the code here
    }
    
    
    //Starts up the Main Menu for the user once best/worst fit is chosen
    std::cout << "Using " << bestOrWorst << " fit algorithm\n\n";
    int n = choice();
    //This loop runs all of the options that are displayed and keeps going until they enter 5 for exit
    while (n != 5){
        //1.) Add program, this portion should have more if else statements to accomodate for the 2 different algorithms
        if(n == 1){
            std::string validname = invalidFree(programname);
            std::cout << "Program size(KB) - ";
            //Checks for user's input first
            int programsize = checkInput("size", validname);
            std::cout << "\n\n";
            
            //converts KB to the amount of pages used based on user input
            int pagesize = kbToPage(programsize);
            
            if(programname.compare("FREE") != 0){
                if(programsize != -1) {
                    if(memoryPage -> isNameUsed(validname) == true){
                        std::cout << "Error, Program " << validname << " already running.\n\n";
                    }
                    else if((bestOrWorst == "worst")){
                        memoryPage ->addProgramWorst(validname, pagesize);
                    }
                    else if((bestOrWorst == "best")){
                        memoryPage ->addProgramBest(validname, pagesize);
                    }
                    
                    std::cout << "\n\n";
                }
            }
            
        }
        //2.)Kill Program
        else if (n == 2){
            std::cout << "Program name - ";
            std::cin >> programname;
            std::cout << "\n";
            
            if (programname.compare("FREE") == 0){
                std::cout << "The program name does not exist.\n\n";
            }
            
            if(programname.compare("FREE") != 0){
                //If the name is indeed used, kill the program as the user asks
                if(memoryPage -> isNameUsed(programname) == true){
                    memoryPage -> killProgram(programname);
                    std::cout << "\n";
                }
                else{
                    std::cout << "The program name does not exist.\n" << std::endl;
                }
            }
            
        }
        //3.)Fragmentation
        else if(n == 3){
            memoryPage -> fragmentation();
        }
        //4.)Print memory
        else if(n == 4){
            std::cout << std::endl;
            memoryPage -> traverseAndPrint();
            std::cout << "\n\n";
        }
        
        n = choice();
    }
    
    
    
    
    return 0;
    
}//end of main method




//METHODS BELOW ARE FOR ERROR CHECKS, Just in case the user enters something besides what was asked,
//or if their input was out of range

//Main Menu for users
int choice(){
    int n;
    
    std::cout << "1. Add program\n";
    std::cout << "2. Kill program\n";
    std::cout << "3. Fragmentation\n";
    std::cout << "4. Print memory\n";
    std::cout << "5. Exit\n\n";
    std::cout << "choice - ";
    std::cin >> n;
    
    //Tests for user's input before entering any of these menu options
    while(true){
        if((std::cin) && n >=1 && n <= 5){
            break;
        }
        
        //The section underneath prevents the user from entering anything besides integers from 1 to 5.
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std:: cout << "\nPlease enter a valid input.\n\n";
        
        std::cout << "1. Add program\n";
        std::cout << "2. Kill program\n";
        std::cout << "3. Fragmentation\n";
        std::cout << "4. Print memory\n";
        std::cout << "5. Exit\n\n";
        std::cout << "choice - ";
        std::cin >> n;
        std::cout << "\n\n";
        
    }
    
    return n;
}

//Makes sure they enter an integer and nothing else
int checkInput(std::string type, std::string programname){
    int num;
    
    while(!(std::cin>>num)){
        std::cout << "\nPlease enter a valid " << type << " input: ";
        std::cin.clear();
        std::cin.ignore(1000,'\n');
    }
    
    if (type.compare("size") == 0){
        if (num <= 0 || num > 128){
            std::cout << "\nError, Not enough memory for " << programname;
            return -1;
        }
    }
    return num;
}

//In the case that the user enter's FREE as their program name
std::string invalidFree(std::string &programname){
    std::cout << "Program name - ";
    std::cin >> programname;
    while((programname.compare("FREE") == 0)){
        std::cout << "Invalid program name, please enter a valid program name.\n";
        std::cout << "Program name - ";
        std::cin >> programname;
    }
    return programname;
}

