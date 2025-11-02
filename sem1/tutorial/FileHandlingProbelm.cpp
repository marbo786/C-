#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

const int NUMBER_OF_QUESTIONS = 20;
const int NUMBER_OF_STUDENTS = 50;

void readFile(ifstream& inFile);
void markTest(char studentAnswers[][NUMBER_OF_QUESTIONS], string* studentIDs, const string& correctAnswers);
char assignGrade(int score);

int main() {
    string studentIDs[NUMBER_OF_STUDENTS];
    string correctAnswers;
    char studentAnswers[NUMBER_OF_STUDENTS][NUMBER_OF_QUESTIONS] = {0}; // Initialize to prevent garbage values
    ifstream inFile;

    // Open the file and handle errors
    readFile(inFile);

    // Read the correct answers first
    getline(inFile, correctAnswers); // First line is the answer key

    // Read each student's ID and answers
    for (int i = 0; i < NUMBER_OF_STUDENTS; i++) {
        if (!(inFile >> studentIDs[i])) { 
            // Break if there are fewer students than expected
            break;
        }
        // Read the entire line for the answers
        string line;
        getline(inFile, line);

        // Parse answers from the line using a traditional for loop
        int answerIndex = 0;
        for (size_t k = 0; k < line.length() && answerIndex < NUMBER_OF_QUESTIONS; k++) {
            if (line[k] != ' ') {
                studentAnswers[i][answerIndex++] = line[k];
            }
        }
    }

    // Close the file after reading
    inFile.close();

    // Evaluate and grade tests
    markTest(studentAnswers, studentIDs, correctAnswers);

    return 0;
}

void readFile(ifstream& inFile) {
    inFile.open("studentsTestScore.txt");
    if (!inFile) {
        cout << "Error: Could not open the input file." << endl;
        exit(1);
    }
}

void markTest(char studentAnswers[][NUMBER_OF_QUESTIONS], string* studentIDs, const string& correctAnswers) {
    for (int i = 0; i < NUMBER_OF_STUDENTS; i++) {
        // Skip if the student ID is empty (indicating fewer students than expected)
        if (studentIDs[i].empty()) {
            break;
        }

        cout << "Student ID: " << studentIDs[i] << endl;

        int score = 0;
        cout << "Answers: ";

        for (int j = 0; j < NUMBER_OF_QUESTIONS; j++) {
            cout << studentAnswers[i][j];
            if (j < correctAnswers.length() && studentAnswers[i][j] == correctAnswers[j]) {
                score += 2; // Correct answer
            } else if (studentAnswers[i][j] != correctAnswers[j] && studentAnswers[i][j] != ' ') {
                score -= 1; // Incorrect answer but not blank
            }
        }

        // Ensure non-negative scores
        if (score < 0) {
            score = 0;
        }

        cout << endl;

        // Assign and display grade
        char grade = assignGrade(score);
        cout << "Score: " << fixed << setprecision(2) << (static_cast<double>(score) / (NUMBER_OF_QUESTIONS * 2)) * 100 << "%" << endl;
        cout << "Grade: " << grade << endl << endl;
    }
}

char assignGrade(int score) {
    double percentScore = static_cast<double>(score) / (NUMBER_OF_QUESTIONS * 2); // Total possible points
    if (percentScore >= 0.9) {
        return 'A';
    } else if (percentScore >= 0.8) {
        return 'B';
    } else if (percentScore >= 0.7) {
        return 'C';
    } else if (percentScore >= 0.6) {
        return 'D';
    } else {
        return 'F';
    }
}

