#include <iostream>
#include <vector>
#include <string>

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

public:
    // Add a task
    void add_task(string name, int max_score) {
        tasks.push_back({ name, max_score });
    }

    // Calculate overall result
    double calculate_result(vector<int> scores) {
        double total_score = 0.0;
        int num_tasks = min(scores.size(), tasks.size());
        for (int i = 0; i < num_tasks; i++) {
            // Check and adjust scores
            if (scores[i] < 0) {
                scores[i] = 0;
            }
            else if (scores[i] > tasks[i].max_score) {
                scores[i] = tasks[i].max_score;
            }
            // Add score to total
            total_score += scores[i];
        }
        // Return average score
        return total_score / tasks.size();
    }
};

int main() {
    // Create task manager
    TaskManager task_manager;

    // Add tasks
    task_manager.add_task("Mathematics", 10);
    task_manager.add_task("Physics", 15);
    task_manager.add_task("History", 5);

    // Input scores
    vector<int> scores = { 8, 12, 7 };

    // Calculate and output result
    double result = task_manager.calculate_result(scores);
    cout << "Overall score: " << result << endl;

    return 0;
}
