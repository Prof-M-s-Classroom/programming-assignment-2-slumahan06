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

    void checkEachEvent(Node<Story>* root, Node<Story>* newNode) { // Preorder
        //cout<<"Testing"<<endl;
        Node<Story>* temp = root;
        if (temp == nullptr) {
            return;
        } else {
            if (temp->data.leftEventNumber == newNode->data.eventNumber) {
                temp->left = newNode;
            } else if (temp->data.rightEventNumber == newNode->data.eventNumber) {
                temp->right = newNode;
            }
            checkEachEvent(temp->left, newNode);
            checkEachEvent(temp->right, newNode);
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
                    if (counter == 0) {
                        eventNumber = stoi(currentData);
                    } else if (counter == 1) {
                        description = currentData;
                    } else if (counter == 2) {
                        leftEvent = stoi(currentData);
                    } else if (counter == 3) {
                        rightEvent = stoi(currentData);
                    }

                    counter++;
                }

                // No matching constructor for initialization??
                // Incompatible pointer types
                Story *newEvent = new Story(description, eventNumber, leftEvent, rightEvent);
                Node<Story>* newNode = new Node<Story>(*newEvent);

                if (root == nullptr) {
                    root = newNode;
                } else {
                    checkEachEvent(root, newNode);
                }
            }

            infile.close();
        } else {
            cout << "No file was found" << endl;
        }
    }

    // TODO: Function to start the game and traverse the tree based on user input
    void playGame() {
        Node<Story>* currentEvent = root;
        while (currentEvent->data.eventNumber != -1) {
            int x = 0;
            cout << currentEvent->data.description << "Do you: " << endl;

            // Options displayed here

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