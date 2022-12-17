// ABCU University.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CSVparse.h"
using namespace std;

// define a structure to hold course information
struct Course {
    string courseNum; // unique identifier
    string title;
    string prereq;
    string prereqTwo;
};

// Internal structure for tree node
struct Node {
    Course course;
    Node* left;
    Node* right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a course
    Node(Course aCourse) :
        Node() {
        course = aCourse;
    }
};

class BinaryTree {

private:
    Node* root;

    void addNode(Node* node, Course course);
    void inOrder(Node* node);
    BinaryTree* bt;



public:
    BinaryTree();
    void InOrder();
    void Insert(Course course);
    Course Search(string courseNum);
};

BinaryTree::BinaryTree() {
    //initialize housekeeping variables
    root = nullptr;
}


void BinaryTree::InOrder() {
    // call inOrder fuction and pass root 
    this->inOrder(root);
}


/**
 * Insert a course
 */
void BinaryTree::Insert(Course course) {

    // if root equal to null ptr
      // root is equal to new node course
    // else
      // add Node root and course
    if (root == nullptr) {
        root = new Node(course);
    }
    else {
        this->addNode(root, course);
    }
}


/**
 * Search for a bid
 */
Course BinaryTree::Search(string courseNum) {

    // set current node equal to root
    Node* currNode = root;
    // keep looping downwards until bottom reached or matching courseId found
        // if match found, return current bid
    while (currNode != nullptr) {
        if (currNode->course.courseNum.compare(courseNum) == 0) {
            return currNode->course;
        }
        if (courseNum.compare(currNode->course.courseNum) < 0) {
            currNode = currNode->left;
        }
        else {
            currNode = currNode->right;
        }
    }
    // if course is smaller than current node then traverse left
    // else larger so traverse right
    Course course;
    return course;
}

/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinaryTree::addNode(Node* node, Course course) {
    // if node is larger then add to left
        // if no left node
            // this node becomes left
        // else recurse down the left node

    if (node->course.courseNum.compare(course.courseNum) > 0) {
        if (node->left == nullptr) {
            node->left = new Node(course);
        }
        // else
        // if no right node
            // this node becomes right
        else {
            this->addNode(node->left, course);
        }
    }
    else {
        if (node->right == nullptr) {
            node->right = new Node(course);
        }
        else {
            this->addNode(node->right, course);
        }
    }
}
void BinaryTree::inOrder(Node* node) {
    //if node is not equal to null ptr
    //InOrder not left
    //output courseID, title, prereq, prereqTwo
    //InOder right

    if (node != nullptr) {
        inOrder(node->left);

        cout << node->course.courseNum << ": " << node->course.title << " | "
            << node->course.prereq
            << " | " << node->course.prereq << " | " << node->course.prereqTwo << endl;

        inOrder(node->right);
    }
}


void displayCourse(Course course) {
    cout << course.courseNum << ": " << course.title << " | " << course.prereq << " | "
        << course.prereqTwo << endl;
    return;
}

void loadCourses(string csvPath, BinaryTree* bt) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " | ";
    }
    cout << "" << endl;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Course course;
            course.courseNum = file[i][0];
            course.title = file[i][1];
            course.prereq = file[i][2];
            course.prereqTwo = file[i][3];

            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            // push this bid to the end
            bt->Insert(course);
        }
    }
    catch (csv::Error& e) {
        std::cerr << e.what() << std::endl;
    }
}
int main()
{
    string csvPath;
    string courseKey;

    
    Course course;
    BinaryTree* bt;
    bt = new BinaryTree();

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Courses" << endl;
        cout << "  2. Display Course List" << endl;
        cout << "  3. Find Course" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            // load courses
            cout << "enter CSV Path" << endl;
            cin >> csvPath;
            loadCourses(csvPath, bt);
            break;

        case 2:
            //display ordered course list
            bt->InOrder();
            break;

        case 3:
            //display specific course
            cin >> courseKey;
            course = bt->Search(courseKey);

            if (!course.courseNum.empty()) {
                displayCourse(course);
            }
            else {
                cout << "Course Id " << courseKey << " not found." << endl;
            }
            break;
        }

        cout << "Good bye." << endl;

        return 0;
    }
}
