#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <array>


using namespace std;
using namespace std::chrono;

class Process_Stats {
public:
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_burst;
    int waiting_time;
    int demotion_count;
    int quantum_remaining;

    Process_Stats(int pid, int arrival_time, int burst_time, int quantum) {
        this->pid = pid;
        this->arrival_time = arrival_time;
        this->burst_time = burst_time;
        this->waiting_time = 0;
        this->demotion_count = 0;
        this->quantum_remaining = quantum;
        this->remaining_burst = burst_time;
    }

    int getQuantum_remaining() const {
        return quantum_remaining;
    }

    int getDemotion_count() const {
        return demotion_count;
    }

    int getRemaining_burst() const {
        return remaining_burst;
    }
};

int main() {
    int clock_tick = 0;
    int process_id = 1;
    int idle_time = 0;
    int dispatch_counter = 0;
    int execution_time = 0;

    Process_Stats process_stats = static_cast<Process_Stats &&>(NULL);

    queue<Process_Stats> queue_a;
    queue<Process_Stats> queue_b;

    // Declare time quantum for respective queues
    int queue_a_quantum = 5;
    int queue_b_quantum = 40;

    // Record the execution time, start
    auto start = high_resolution_clock::now();

    // Read the file name
    string inputFileName;

    // Read demotion threshold and dispatch ratio
    int demotion_threshold, dispatch_ration;

    // Get the input from the user
    cin >> inputFileName;
    cin >> demotion_threshold;
    cin >> dispatch_ration;

    // Read contents from the file
    string file = R"(C:\Users\sahit\CLionProjects\Simulation\)" + inputFileName;
    ifstream readFile(file);
    std::string line;


    int arrival_time = 0;
    while (getline(readFile, line)) {
        clock_tick++;

        // remove unwanted characters from the line
        line.erase(remove(line.begin(), line.end(), ' '), line.end());

        if(&process_stats != NULL){
            processExecuting.remaining_burst--;
            processExecuting.quantum_remaining--;
        }

        if (line == "idle" || line == "Idle") {
            idle_time += 1;

            continue;
        } else {
            int x = stoi(line);
            process[line_count].Burst_Time = x;
            RoundRobin_scheduler(vector_stats, queue_a_quantum);
            RoundRobin_scheduler(vector_stats, queue_b_quantum);
            FCFS_scheduler(vector_stats);
        }

        float waiting_time = 0;
    }

    // Record the execution time, start
    auto stop = high_resolution_clock::now();

    // Total duration in milliseconds
    auto duration = duration_cast<milliseconds>(stop - start);

    // Display the output
    std::cout << "End Time " << stop.time_since_epoch().count() << std::endl;
    std::cout << "Processes Completed: " << std::endl;
    std::cout << "Total execution time: " << duration.count() << std::endl;
    std::cout << "Idle time: " << idle_time << std::endl;
    std::cout << "Wait time average: " << std::endl;

    return 0;
}
