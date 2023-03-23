#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

using namespace std;

// Structure to store information about tasks
struct Task {
    string name;
    int max_score;
};

// Class to store and evaluate task results
class TaskManager {
private:
    vector<Task> tasks;
    map<string, vector<int>> scores; // Store scores for each student

public:
    // Add a task
    void add_task(string name, int max_score) {
        tasks.push_back({ name, max_score });
    }

    // Add scores for a student
    void add_scores(string student, vector<int> student_scores) {
        // Check if any of the scores are negative
        for (int score : student_scores) {
            if (score < 0) {
                cout << "Error: negative score detected. Please enter a non-negative score." << endl;
                return;
            }
        }
        // Add scores if all scores are non-negative
        scores[student] = student_scores;
    }

    // Calculate overall result for a student
    double calculate_result(string student) {
        double total_score = 0.0;
        vector<int> student_scores = scores[student];
        int num_tasks = min(student_scores.size(), tasks.size());
        for (int i = 0; i < num_tasks; i++) {
            // Check and adjust scores
            if (student_scores[i] < 0) {
                student_scores[i] = 0;
            }
            else if (student_scores[i] > tasks[i].max_score) {
                student_scores[i] = tasks[i].max_score;
            }
            // Add score to total
            total_score += student_scores[i];
        }
        // Return average score
        return total_score / tasks.size();
    }

    // Get scores for all students
    map<string, vector<int>> get_scores() const {
        return scores;
    }

    // Get number of tasks
    int num_tasks() const {
        return tasks.size();
    }

    // Get task at index
    Task get_task(int index) const {
        return tasks[index];
    }
};

int main() {
    // Create task manager
    TaskManager task_manager;

    // Add tasks
    task_manager.add_task("Task 1", 10);
    task_manager.add_task("Task 2", 20);
    task_manager.add_task("Task 3", 15);

    // Add scores for students
    task_manager.add_scores("Alice", { 8, 15, 10 });
    task_manager.add_scores("Bob", { 12, 18, 20 });
    task_manager.add_scores("Charlie", { 10, -5, 15 }); // Negative score

    // Calculate results
    cout << "Results:" << endl;
    cout << "Alice: " << task_manager.calculate_result("Alice") << endl;
    cout << "Bob: " << task_manager.calculate_result("Bob") << endl;
    cout << "Charlie: " << task_manager.calculate_result("Charlie") << endl;

    // Save scores to file
    string file_name;
    cout << "Enter name of file to save scores to: ";
    cin >> file_name;
    ofstream out_file(file_name);
    if (out_file) {
        // Write task names
        out_file << "Student Name,";
        for (int i = 0; i < task_manager.num_tasks(); i++) {
            out_file << task_manager.get_task(i).name;
            if (i < task_manager.num_tasks() - 1) {
                out_file << ",";
            }
        }
        out_file << endl;

        // Write student scores
        map<string, vector<int>> scores = task_manager.get_scores();
        for (auto score_pair : scores) {
            out_file << score_pair.first << ",";
            vector<int> student_scores = score_pair.second;
       
                for (int i = 0; i < student_scores.size(); i++) {
                    out_file << student_scores[i];
                    if (i < student_scores.size() - 1) {
                        out_file << ",";
                    }
                }
            out_file << endl;
        }
        out_file.close();
        cout << "Scores saved to " << file_name << endl;
    }
    else {
        cout << "Error: could not open file " << file_name << endl;
    }

    return 0;
}