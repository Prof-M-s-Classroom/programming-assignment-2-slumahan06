#ifndef GAMEDECISIONTREE_H
#define GAMEDECISIONTREE_H

#include <unordered_map>
#include <fstream> // Gives access to ifstream objects
#include <sstream>
#include <iostream>
#include "Node.h"
#include "Story.h"
using namespace std;

template <typename T>
class GameDecisionTree {
private:
    Node<T>* root;

public:
    // TODO: Constructor
    GameDecisionTree() : root(nullptr) {}

    // Traverses the tree to set the new node in the correct place(s) using recursion
    void checkEachEvent(Node<Story>* root, Node<Story>* newNode) { // Preorder traversal
        //cout<<"Testing"<<endl;

        // Start at the root
        Node<Story>* temp = root;
        if (temp == nullptr) {
            return;
        } else {
            if (temp->data.leftEventNumber == newNode->data.eventNumber) {
                temp->left = newNode;
            } else if (temp->data.rightEventNumber == newNode->data.eventNumber) {
                temp->right = newNode;
            }

            checkEachEvent(temp->left, newNode); // Check the left side of the node
            checkEachEvent(temp->right, newNode); // Check the right side of the node
        }
    }

    // TODO: Function to load story data from a text file and build the binary tree
    void loadStoryFromFile(const std::string& filename, char delimiter) {
        ifstream infile;
        infile.open(filename); // Open the file
        string currentLine;
        string currentData;

        int eventNumber;
        int leftEvent;
        int rightEvent;
        string description;

        if (infile.is_open()) { // Check if the file was successfully opened

            while (getline(infile, currentLine)) { // File and each specific line

                stringstream s(currentLine);
                int counter = 0;

                while (getline(s, currentData, delimiter)) {
                    if (counter == 0) { // Item is the event number
                        eventNumber = stoi(currentData);
                    } else if (counter == 1) { // Item is the description
                        description = currentData;
                    } else if (counter == 2) { // Item is the left event path
                        leftEvent = stoi(currentData);
                    } else if (counter == 3) { // Item is the right event path
                        rightEvent = stoi(currentData);
                    }

                    counter++;
                }

                // No matching constructor for initialization??
                // Incompatible pointer types

                // Create a new story event using the given event data
                Story *newEvent = new Story(description, eventNumber, leftEvent, rightEvent);

                // Create a new node with the story data
                Node<Story>* newNode = new Node<Story>(*newEvent);

                if (root == nullptr) {
                    root = newNode; // Set the root to the first node
                } else {
                    checkEachEvent(root, newNode); // Use the function to build the tree
                }
            }

            infile.close(); // Close the file
        } else {
            cout << "No file was found?" << endl;
        }
    }

    // TODO: Function to start the game and traverse the tree based on user input
    void playGame() {
        Node<Story>* currentEvent = root; // Start at the root (the first event)
        while (currentEvent->data.eventNumber != -1) {
            int x = 0;
            cout << currentEvent->data.description << endl;

            // Options displayed here

            if (currentEvent->data.leftEventNumber == -1 && currentEvent->data.rightEventNumber == -1) {
                break;
            }

            cout << "Enter choice: ";
            cin >> x;

            if (x == 1) {
                if (currentEvent->data.leftEventNumber != -1) {
                    currentEvent = currentEvent->left;
                } else {
                    break;
                }
            } else if (x == 2) {
                if (currentEvent->data.rightEventNumber != -1) {
                    currentEvent = currentEvent->right;
                } else {
                    break;
                }
            }
        }
    }
};

#endif // GAMEDECISIONTREE_H