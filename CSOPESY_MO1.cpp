
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <thread>
#include <chrono>
#include <atomic>
#include <mutex>
#include <iomanip>
#include <queue>

// --- Shared State and Thread Control ---
// Global flag to signal all threads to exit.
std::atomic<bool> is_running{true};
std::atomic<bool> initialized{false};
std::atomic<bool> animation{false};
std::atomic<bool> run_once{true};

// config.txt inputs
#include <fstream>

std::ifstream configFile;
int num_cpu;
std::string scheduler;
int quantum_cycles;
int batch_process_freq;
int max_ins;
int min_ins;
int delays_per_exec;

// Shared state for the keyboard handler and command interpreter.
std::queue<std::string> command_queue;
std::mutex command_queue_mutex;

// The marquee logic thread and display thread share this variable.
std::string marquee_display_buffer = "CSOPESY MARQUEE          ";
std::mutex marquee_to_display_mutex;

int refresh_rate_ms = 200;
int commandCount = 0;

// --- Utility Function ---
// Moves the cursor to a specific (x, y) coordinate on the console.
void gotoxy(int x, int y) {
    std::cout << "\033[" << y << ";" << x << "H";
}

// --- Thread Functions ---
void keyboard_handler_thread_func() {
    std::string command_line;
    while (is_running) {
        std::cout << "Command >> ";
        std::getline(std::cin, command_line);
        
        if (!command_line.empty()) {
            if (command_line == "exit")
                is_running = false;

            std::unique_lock<std::mutex> lock(command_queue_mutex);
            command_queue.push(command_line);
            commandCount++;
            lock.unlock();
        }
    }
}

// --- Main Function (Command Interpreter Thread) ---
int main() {
    // Start the three worker threads.
    std::thread keyboard_handler_thread(keyboard_handler_thread_func);

    std::cout << "\033[2J\033[1;1H"; 

    std::cout << marquee_display_buffer;
    std::cout << "\nGroup Developers:\n";
    std::cout << "1. Matthew Copon\n";
    std::cout << "2. Chastine Cabatay\n";
    std::cout << "3. Ericson Tan\n";
    std::cout << "4. Joaquin Cardino\n";
    std::cout << "Version: 1.00.00\n\n\n\n\n\n\n\n\n";
    
    // Main loop that processes commands from the queue.
    while (is_running) {
        std::string command_line;
        {
            std::unique_lock<std::mutex> lock(command_queue_mutex);
            if (!command_queue.empty()) {
                command_line = command_queue.front();
                command_queue.pop();
            }
        }
        
        if (!command_line.empty()) {
            // Command processing logic goes here...
            if (command_line == "initialize") {
                configFile.open("filename.txt");
                
                if (!configFile.is_open()) {
                    std::cerr << "ERROR: config.txt could not be opened." << std::endl;
                }
                else
                {

                }
            }
            else if (command_line == "scheduler_start") {
                if (initialized){

                }
                else
                    std::cout << "ERROR: Console not initialized. Please initialize with 'initialize' command." << std::endl;
                
            }
            else if (command_line == "scheduler_stop") {
                if (initialized){

                }
                else
                    std::cout << "ERROR: Console not initialized. Please initialize with 'initialize' command." << std::endl;
            }
            else if (command_line == "report_util") {
                if (initialized){

                }
                else
                    std::cout << "ERROR: Console not initialized. Please initialize with 'initialize' command." << std::endl;
            }
            else if (command_line.rfind("screen", 0) == 0) {
                if (initialized){

                }
                else
                    std::cout << "ERROR: Console not initialized. Please initialize with 'initialize' command." << std::endl;
            }
            else {
                gotoxy(12, 15 + commandCount);
                std::cout << "Command not found.";
                gotoxy(12, 16 + commandCount);
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    // Join threads to ensure they finish cleanly.
    if (keyboard_handler_thread.joinable()) {
        keyboard_handler_thread.join();
    }

    return 0;
}
