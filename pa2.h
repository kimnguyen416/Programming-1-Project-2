//  pa2.h


#ifndef pa2_h
#define pa2_h
#include <iostream>
#include <string>


//Declaration of the start up menu
int choice();

//Creation of the Node class
class Node{
public:
    //variables
    int data;
    Node *next; //reference to the next node
    bool nodeused; //accounts for whether the node/page is occupied or not
    std::string programname;
    
    //Constructors
    
    
    //Default constructor: This is when your 32 node memory is empty.
    Node(){
        next = NULL;
        nodeused = false; //Indicates that the node is not used
        programname = "FREE";
    }
    
    //This constructor is for when a node is given data
    Node(int data){
        //initializes the variables
        this -> data = data;
        next = NULL;
    }
    
};


//Declaration of the LinkedList class
class LinkedList{
public:
    Node *head;
    Node *temp;
    std::string programname;
    
    //constructor
    LinkedList(){
        head = NULL;
    }
    
    //Methods
    
    void createPages();//creates a linked list of 32 nodes that represents the total available memory
    bool isNameUsed(std::string programname); //checks whether the program name is already taken/not
    
    //Based on user's choice on best/worst fit, these methods will accomodate for that
    //Parameters: Takes in the new program name that the user wants, then returns the amount of pages used
    //Choice 1.)
    void addProgramBest(std::string programname, int pagesused);
    void addProgramWorst(std::string programname, int pagesused);
    //Choice 2.) Kills the program and frees up space
    void killProgram(std::string programname);
    //Choice 3.) Fragmentation
    //returns the amount of fragments of the memory space
    void fragmentation();
    //Choice 4.) Prints the memories current status
    void traverseAndPrint();
    
    
};



#endif /* pa2_h */
