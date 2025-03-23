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

    // TODO: Function to load story data from a text file and build the binary tree
    void loadStoryFromFile(const std::string& filename, char delimiter) {
        ifstream infile;
        infile.open(filename); // Open the file
        string currentLine;
        string currentData;

        if (infile.is_open()) { // Check if the file was successfully opened

            while (getline(infile, currentLine)) { // File and each specific line

                stringstream s(currentLine);

                while (getline(s, currentData, delimiter)) {
                    cout << currentData << endl;
                }
            }

            infile.close();
        } else {
            cout << "No file was found" << endl;
        }
    }

    // TODO: Function to start the game and traverse the tree based on user input
    void playGame(){}
};

#endif // GAMEDECISIONTREE_H