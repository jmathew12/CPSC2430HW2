// James Mathew
// p2.cpp
// Susan Reeder
// CPSC 2430
// 10/11/2017
//	This program creates a list with MAX values ranging from 0 - (MAXRAN - 1)
//		in acending order. It will delete values from the beginning, end, and 
//		from somewhere in the middle. 

#include <iostream>
#include <ctime>
#include <fstream>
#include <cstdlib>

using namespace std;

struct Node
{
  int data;
  Node* next;
};

// Traverses the content of the list to the output stream outputDestination.
void printList (Node* list, ostream& outputDestination);

// Inserts val into the list, keeps the list in ascending order
bool insertInOrder(Node*& list, int val);

// deletes one instance of val from the list if exists
void deleteNode(Node*& list, int val);

// deletes the smallest value from the list
void deleteSmall(Node*& list);

// deletes the biggest value from the list
void deleteLarge(Node* list);

// deletes a random value from the list that is not the smallest or the 
//	biggest.
void deleteMiddle(Node*& list);

// returns the biggest value stored in the list
int findLast(Node* list);

// deletes all the nodes of the list
void deleteAll(Node*& list);

const string OUTFILE1 = "P2OutPutA.txt"; // output file
const string OUTFILE2 = "P2OutPutB.txt"; // output file

int main()
{
  ofstream outfile;
  srand(time(0));
  int input = 0;
  Node* list = nullptr;
  const int MAX = 50; // number of total elements
  const int MAXRAN = 100; // values of elementsrange from 0 to MAXRAN - 1
  cout << "Welcome! This program will first create " << MAX
       << " values and insert into the list." << endl;
  for (int i = 0; i < MAX; i++) {
    input = rand() % MAXRAN;
    insertInOrder(list, input);
  }
  outfile.open(OUTFILE1);
  printList(list, cout); // prints on screen
  printList(list, outfile); // prints to file
  outfile.close();
  deleteSmall(list);
  deleteLarge(list);
  deleteMiddle(list);
  cout<< endl;
  outfile.open(OUTFILE2);
  printList(list, cout); // prints on screen
  printList(list, outfile); // prints to file
  outfile.close();
  cout << "deleting" << endl;
  deleteAll(list);
  
  printList(list, cout);
  cout << "deleted" << endl;
  return 0;
}

void deleteAll(Node*& list) {
  while(list != nullptr) {
    deleteNode(list, list->data);
  }
}

int findLast(Node* list)
{
  Node* ptr;
  ptr = list;
  while(ptr->next != nullptr) {
    ptr = ptr->next;
  }
  return ptr->data;
}

void deleteMiddle(Node*& list)
{
  int count = 0;
  Node* ptr;
  ptr = list;
  while(ptr != nullptr){ // counts the number of elements
    count++;
    ptr = ptr->next;
  }
  int deleteIndx = (rand() % (count - 2));
  ptr = list;
  for(int i = 0; i <= deleteIndx; i++) {
    ptr = ptr->next;
  }
  deleteNode(list, ptr->data);
}

void deleteSmall(Node*& list)
{
  deleteNode(list, list->data);
}

void deleteLarge(Node* list)
{
  deleteNode(list, findLast(list));
}

void deleteNode(Node*& list, int val) 
{
  Node* delPtr;
  Node* ptr;
  if (list->data == val) { // deletes the head
    delPtr = list;
    list = list->next;
    delete delPtr;	
  } else { // if val is not in the head
    ptr = list;
    while(ptr->next != nullptr && ptr->next->data < val) {
      ptr = ptr->next;	
    }
    if (ptr->next != nullptr && ptr->next->data == val) {
      delPtr = ptr -> next;
      ptr->next = delPtr->next;
      delete delPtr;
    }
  } 
}

void printList(Node* list, ostream& outputDestination)
{
  Node* temp = list;
  while(temp != nullptr){
    outputDestination << temp->data << endl;
    temp = temp->next;
  }
}

bool insertInOrder(Node*& list, int val)
{
  Node* temp = new Node;
  if(temp == nullptr) {
    return false;
  }
  temp->data = val;
  temp->next = nullptr;
  if (list == nullptr) { // if list is empty
    list = temp;
  } else if(list->data > temp->data) { // if val goes to the beginning
    temp->next = list;
    list = temp;
  } else { // val goes in any other place
    Node* ptr;
    ptr = list;
    while(ptr->next != nullptr && ptr->next->data < temp->data) {
      ptr = ptr->next;
    }
    temp->next = ptr->next;
    ptr->next = temp;
  }
  return true;
}
