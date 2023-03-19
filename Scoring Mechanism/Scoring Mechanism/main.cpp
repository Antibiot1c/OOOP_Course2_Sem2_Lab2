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
    map<string, vector<int>> scores; // Store scores for each group

public:
    // Add a task
    void add_task(string name, int max_score) {
        tasks.push_back({ name, max_score });
    }

    // Add scores for a group
    void add_scores(string group, vector<int> group_scores) {
        scores[group] = group_scores;
    }

    // Calculate overall result for a group
    double calculate_result(string group) {
        double total_score = 0.0;
        vector<int> group_scores = scores[group];
        int num_tasks = min(group_scores.size(), tasks.size());
        for (int i = 0; i < num_tasks; i++) {
            // Check and adjust scores
            if (group_scores[i] < 0) {
                group_scores[i] = 0;
            }
            else if (group_scores[i] > tasks[i].max_score) {
                group_scores[i] = tasks[i].max_score;
            }
            // Add score to total
            total_score += group_scores[i];
        }
        // Return average score
        return total_score / tasks.size();
    }

    // Get scores for all groups
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
    task_manager.add_task("Mathematics", 10);
    task_manager.add_task("Physics", 15);
    task_manager.add_task("History", 5);

    // Input groups and scores
    int num_groups;
    cout << "Enter number of groups: ";
    cin >> num_groups;

    for (int i = 1; i <= num_groups; i++) {
        string group_name;
        cout << "Enter name for group " << i << ": ";
        cin >> group_name;

        vector<int> group_scores;
        for (int j = 0; j < task_manager.num_tasks(); j++) {
            int score;
            cout << "Enter score for " << task_manager.get_task(j).name << " in group " << group_name << ": ";
            cin >> score;
            group_scores.push_back(score);
        }

        task_manager.add_scores(group_name, group_scores);
    }

    // Save scores to file
    string file_name;
    cout << "Enter name of file to save scores to: ";
    cin >> file_name; ofstream out_file(file_name);
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

        // Write group scores
        map<string, vector<int>> scores = task_manager.get_scores();
        for (auto score_pair : scores) {
            out_file << score_pair.first << ",";
            vector<int> group_scores = score_pair.second;
            for (int i = 0; i < group_scores.size(); i++) {
                out_file << group_scores[i];
                if (i < group_scores.size() - 1) {
                    out_file << ",";
                }
            }
            out_file << endl;
        }
        out_file.close();
        cout << "Scores saved to " << file_name << endl;
    }
    else {
        cout << "Unable to open file " << file_name << " for writing." << endl;
    }

    // Calculate and print results for each group
    map<string, vector<int>> scores = task_manager.get_scores();
    for (auto score_pair : scores) {
        string group_name = score_pair.first;
        double result = task_manager.calculate_result(group_name);
        cout << "Result for group " << group_name << ": " << result << endl;
    }
}