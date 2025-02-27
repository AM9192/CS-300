#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string>

using namespace std;

// Define a struct to hold course information
struct Course {
    string courseNumber;          // Unique identifier for the course (e.g., "CSCI100")
    string name;                  // Full course name (e.g., "Introduction to Computer Science")
    vector<string> prerequisites; // List of prerequisite course numbers
};

// Declare a map to store courses sorted by course number
map<string, Course> courses;

// Function prototypes
void loadCoursesFromFile(string filename);
void printCourseList();
void printCourseDetails(string);

// Function: Load courses from CSV file
void loadCoursesFromFile(string filename) {
    cout << "Trying to open file: " << filename << endl;  // Debugging output

    ifstream file(filename);  // Attempt to open the file

    if (!file) {
        cout << "Error opening file! Make sure the file exists and is in the correct directory.\n" << endl;
        return;
    }

    cout << "File opened successfully!" << endl;

    string line;
    while (getline(file, line)) {
        cout << "Processing line: " << line << endl;  // Debugging print
        stringstream ss(line);
        string courseNumber, name, prereq;

        // Read the course number
        if (!getline(ss, courseNumber, ',')) continue;

        // Read the course name
        if (!getline(ss, name, ',')) continue;

        // Create a Course object
        Course course;
        course.courseNumber = courseNumber;
        course.name = name;

        // Read prerequisites
        while (getline(ss, prereq, ',')) {
            if (!prereq.empty()) {  // Prevent adding empty prerequisites
                course.prerequisites.push_back(prereq);
            }
        }

        // Store the course in the map
        courses[courseNumber] = course;
    }

    file.close();
    cout << "Course data loaded successfully!\n" << endl;
}

// Function: Display the main menu
void displayMenu() {
    cout << "\nWelcome to the Course Planner!" << endl;
    cout << "1. Load Data Structure" << endl;
    cout << "2. Print Course List" << endl;
    cout << "3. Print Course Details" << endl;
    cout << "9. Exit" << endl;
    cout << "What would you like to do? ";
}

// Function: Print the sorted list of courses
void printCourseList() {
    if (courses.empty()) {
        cout << "\nNo courses available. Please load data first.\n";
        return;
    }

    cout << "\nHere is a sample schedule:\n" << endl;
    for (const auto& pair : courses) {
        cout << pair.first << ", " << pair.second.name << endl;
    }
}

// Function: Print details of a specific course
void printCourseDetails(string courseNumber) {
    auto it = courses.find(courseNumber);

    if (it != courses.end()) { // If course is found
        Course course = it->second;
        cout << "\n" << course.courseNumber << ", " << course.name << endl;
        cout << "Prerequisites: ";

        if (course.prerequisites.empty()) {
            cout << "None";
        }
        else {
            for (size_t i = 0; i < course.prerequisites.size(); ++i) {
                cout << course.prerequisites[i];
                if (i < course.prerequisites.size() - 1) {
                    cout << ", ";
                }
            }
        }
        cout << endl;
    }
    else { // Course not found
        cout << "\nCourse not found. Please check the course number and try again.\n";
    }
}

// Main function: Handles the menu system
int main() {
    int choice;
    string filename, courseNumber;

    do {
        displayMenu();

        // Get user input
        cin >> choice;

        // Handle input errors
        if (cin.fail()) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(10000, '\n');  // Clear invalid input
            continue; // Restart menu
        }

        switch (choice) {
        case 1:
            cout << "Enter filename (or full path if needed): ";
            cin >> filename;
            loadCoursesFromFile(filename);
            break;
        case 2:
            printCourseList();
            break;
        case 3:
            cout << "Enter course number: ";
            cin >> courseNumber;
            printCourseDetails(courseNumber);
            break;
        case 9:
            cout << "Thank you for using the course planner! Goodbye.\n";
            break;
        default:
            cout << "Invalid option. Please enter a valid choice.\n";
        }
    } while (choice != 9);

    return 0;
}