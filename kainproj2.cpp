#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

// Define a structure to hold course information
struct Course {
    string courseNumber;
    string title;
    vector<string> prerequisites;
};

// Function to split a string by a delimiter
vector<string> split(const string& line, char delimiter) {
    vector<string> result;
    stringstream ss(line);
    string item;
    while (getline(ss, item, delimiter)) {
        result.push_back(item);
    }
    return result;
}

// Function to load course data from a file
map<string, Course> loadCourseData(const string& fileName) {
    map<string, Course> courseMap;
    ifstream file(fileName);  // Open the file

    if (!file.is_open()) {  // Check if the file was opened successfully
        cerr << "Error: Could not open file " << fileName << endl;
        return courseMap;
    }

    string line;
    while (getline(file, line)) {  // Read the file line by line
        vector<string> parts = split(line, ',');  // Assuming CSV format
        if (parts.size() < 2) continue;  // Skip invalid lines

        Course course;
        course.courseNumber = parts[0];
        course.title = parts[1];

        // Add prerequisites if they exist
        for (size_t i = 2; i < parts.size(); ++i) {
            course.prerequisites.push_back(parts[i]);
        }

        // Insert into the map
        courseMap[course.courseNumber] = course;
    }

    file.close();
    return courseMap;
}

// Function to print all courses sorted by course number
void printCourseList(const map<string, Course>& courses) {
    cout << "Course List:\n";
    for (const auto& pair : courses) {
        cout << pair.first << ", " << pair.second.title << endl;
    }
}

// Function to print course details
void printCourse(const map<string, Course>& courses, const string& courseNumber) {
    auto it = courses.find(courseNumber);
    if (it != courses.end()) {
        const Course& course = it->second;
        cout << "Course Number: " << course.courseNumber << endl;
        cout << "Title: " << course.title << endl;
        cout << "Prerequisites: ";
        if (course.prerequisites.empty()) {
            cout << "None";
        }
        else {
            for (size_t i = 0; i < course.prerequisites.size(); ++i) {
                cout << course.prerequisites[i];
                if (i != course.prerequisites.size() - 1) cout << ", ";
            }
        }
        cout << endl;
    }
    else {
        cout << "Course not found.\n";
    }
}

// Main menu function
void displayMenu() {
    cout << "\nMenu:\n";
    cout << "1. Load Data Structure\n";
    cout << "2. Print Course List\n";
    cout << "3. Print Course\n";
    cout << "9. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    map<string, Course> courses;  // Data structure to hold the courses
    int choice;

    while (true) {
        displayMenu();  // Show menu
        cin >> choice;

        if (choice == 1) {
            // Ask for file name from the user
            string fileName;
            cout << "Enter the file path (e.g., C:/path/to/info.csv): ";
            cin.ignore();  // To ignore any lingering input from previous 'cin'
            getline(cin, fileName);  // Use getline to capture the full path, even with spaces
            courses = loadCourseData(fileName); // Load the course data
            if (!courses.empty()) {
                cout << "Data loaded successfully.\n";
            } else {
                cout << "No data loaded. Check the file format or file path.\n";
            }
        }
        else if (choice == 2) {
            if (courses.empty()) {
                cout << "No data loaded. Please load the data first.\n";
            }
            else {
                printCourseList(courses);  // Print the list of courses in alphanumeric order
            }
        }
        else if (choice == 3) {
            if (courses.empty()) {
                cout << "No data loaded. Please load the data first.\n";
            }
            else {
                string courseNumber;
                cout << "Enter the course number: ";
                cin >> courseNumber;
                printCourse(courses, courseNumber); // Print course details (title and prerequisites)
            }
        }
        else if (choice == 9) {
            cout << "Exiting program.\n";
            break;  // Exit the loop and end the program
        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
