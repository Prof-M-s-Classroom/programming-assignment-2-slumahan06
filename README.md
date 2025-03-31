[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/jIKk4bke)
# CS210 Data Structures SP25
## Programming Assignment 2: Text-Based RPG Using Decision Trees

### **Student Name:** `Sean Lumahan`  
### **Student ID:** `132492734`  

---

## **1. Project Overview**
(Provide a brief summary of your RPG game. Describe how it uses a decision tree and how the player interacts with it.)

Example:
> This project implements a text-based RPG using a **binary decision tree**. Each game event is represented as a node, and the player progresses by choosing between two paths at each stage. The storyline is loaded from an external text file (`story.txt`), which is parsed to construct the decision tree. The game ends when a leaf node (with `-1` as left and right children) is reached.

---

## **2. Folder & File Structure**
(Explain the role of each file in your project.)

- **`main.cpp`** → `When the program is ran, this is the file that is executed. It calls the functions present in the other files.`  
- **`GameDecisionTree.h`** → `This is where the two main functions: playGame() and loadStoryFromFile() are implemented.`  
- **`Node.h`** → `This file contains the backbone for each Node object: the data, and a pointer to the left and right nodes. It holds the constructor for the Node object, which means that each Node object created refers to this file for creation.`  
- **`Story.h`** → `This file contains the backbone for each of the Story objects: description, event number, and left and right events. It also contains the constructor. Each time a Story object is created, this is the file that is referred to.`  
- **`story.txt`** → `The program reads each line found in story.txt. Within each line, it uses the delimiter (which in this case is '|') to recognize each part of the Story class: event number, description, and left and right event.`  

---

## **3. Decision Tree Construction**
(Explain how the decision tree is built from the `story.txt` file.)

- How are `Story` objects created from the text file?  
  - In the loadStoryFromFile() function in GameDecisionTree.h, the program loops through all the lines in the story.txt file. At each line, it loops through the contents of the line by using the delimiters to extract the data and assign it to the correct variable name. Once all the data is taken, the contents are passed to create a Story object.
- How are nodes linked based on left and right event numbers? 
  - When a node is created, it takes the event number of the node (from the Story data) and traverses the tree. If the node's left or right child matches the new node's event number, the parent node's left/right pointer is set to the new node.
- What happens if an event has `-1` as left or right children?  
  - If an event has -1 as a left or right child, that means a left and/or right child does not exist and the current node is a leaf node. In my program, if both children are -1, the program automatically terminates since that means a leaf node was reached.

---

## **4. Game Traversal**
(Describe how the game moves through the decision tree.)

- How does user input determine the path taken?
  - The user's input determines whether the left side of the story or right side of the story is taken. If the user inputs '1', the story goes down the left side of the subtree. If the user inputs '2', the story goes down the right side of the subtree.
- What happens when the player reaches a leaf node?
  - If a leaf node is reached where the children are set to -1, my program automatically disconnects, since no further paths can be taken.
- Explain the special case where multiple events lead to the same outcome.
  - My special event is event 15, where the player decides to take in illegal campaign contributions from crime syndicates. The player can reach this event if they immediately choose to do so after they run low on campaign funds, or after they try asking for donations, yet they don't make enough money.

---

## **5. File Parsing & Data Loading**
(Explain the process of reading `story.txt` and constructing the decision tree.)

- How is the file read and parsed using a delimiter?  
  - The program uses the getline() function on each line to access each piece of data. Using the delimiter character that is passed through, it is able to distinguish where one piece of data ends and when another piece of data begins. Knowing these constraints, we can loop through the entire line, take each piece of data, and set it to variable to save it and move onto the next piece of data.
- How do you ensure nodes are properly linked?
  - I made a preorder traversal function to loop through the entire tree to make sure events are properly linked to one another. Preorder starts at the root, and then looks at the left node and right node. Even if a node is a child of one node, the function continues to loop through the rest of the tree in case multiple events lead to the same event.
- Any challenges faced while handling file input? 
  - I had problems originally trying to implement the getline() function to read the contents of each line. I noticed that each of the tutorials provided for the streams implemented the file reading differently.

---

## **6. Debugging Process (Errors & Fixes)**
(Describe one or more debugging challenges you faced and how you fixed them.)

Example:
> Initially, my program was crashing when trying to access an uninitialized node. I realized it was because I was not properly checking for `nullptr` before accessing child nodes, so I added a check to prevent accessing uninitialized memory.

---

## **7. Sample Output & Walkthrough**
(Provide an example of how the game runs, including player input.)

You are a 30-year-old State Senator with political ambitions. What chamber of Congress do you run for? (1. House / 2. Senate)

Enter choice: 1

You decide to run for the House of Representatives. The district where your hometown is located would be harder to win, but you can also run in a district you don't live in at all. What will you do? (1. Run in the hometown district / 2. Carpetbag)

Enter choice: 2

You take the risk and decide to run in the district you're not from (also known as carpetbagging). It's your campaign's biggest weakness. What will you do to change the narrative? (1. Viral media moment / 2. Attack opponents)

Enter choice: 2

You shift attention to your opponents and their ability to deliver for the people. This strategy is successful and your polling numbers rise. However, you face a fundraising issue. How will you raise some cash? (1. Appeal to supporters / 2. Illegal campaign contributions)

Enter choice: 1

You seek donations from the everyday citizen. While some don't buy your message, others contribute to your campaign. However, it's not enough as another fundraising deadline looms. What will you do? (1. Continue begging / 2. Illegal campaign contributions)

Enter choice: 2

With things not looking good, you take the risky route and take illegal campaign contributions from questionable syndicates. One of these deals gets leaked to the public, and you're facing huge backlash from all parties. What will you do? (1. Apologize and drop out / 2. Go into hiding)

Enter choice: 2

Accepting there is no easy way out of this, you go off-the-grid and into hiding! Authorities are actively searching for your whereabouts, and it's become a major headline in national news. Where will you go? (1. Canada / 2. Russia)

Enter choice: 2

You flee across the world into Russia, hoping Russian authorities will protect you from American authorities. All seems going well for a while, until a surprise raid is conducted in your living space! What now? (1. Fight back / 2. Surrender)

Enter choice: 1

If you are going to go out, you're going out on your own terms. Anything in your reach is used as a makeshift weapon, and several people are injured in the fight. Eventually, you are backed into a corner on the rooftop, where you notice a sniper aiming from an adjacent building...

Process finished with exit code 0

---

## **8. Big-O Analysis of Core Methods**
(Analyze the complexity of key methods.)

- **Loading the tree from the file** → `O(n^2) since I use a nested while loop, one to read each line and one to read the contents of each line.`  
- **Searching for an event in the tree** → `O(log(n)) since the player can only go either left or right.`  
- **Game traversal efficiency** → `O(log(n)) because each decision the player makes cuts the possible amount of events roughly in half each time.`  

---

## **9. Edge Cases & Testing**
(Describe at least one edge case you tested and its outcome.)

Example:
> I tested a scenario where the player reaches a dead-end (leaf node) and ensured the program correctly ends the game.

---

## **10. Justification of Additional Features (If Any)**
(If you added extra features, describe them and explain why.)

> No extra features were added, but I added a recursive function to help assist with traversal of the tree. It utilizes preorder traversal, starting at the root and then checking the left and right children.

---

## **Final Notes**
- **README is mandatory** → `(-10 points deduction if missing).`  
- **Code must compile and run** → `(Code that does not run will receive a 0).`  
- **Do not modify provided skeleton code** → `(You may only add to it).`  

---
