#include <iostream>
#include <fstream>
#include <vector> 
#include <ctime>
#include <iomanip>
#include <string.h>

int main(int argc, char** argv)
{
    // declare file 
    std::fstream file;

    // prints the CLI usage
    if (argc == 1 || strcmp(argv[1], "help") == 0) {
        std::cout << "Usage :-\n";
        std::cout << "$ ./todo add \"todo item\"  # Add a new todo\n";
        std::cout << "$ ./todo ls               # Show remaining todos\n";
        std::cout << "$ ./todo del NUMBER       # Delete a todo\n";
        std::cout << "$ ./todo done NUMBER      # Complete a todo\n";
        std::cout << "$ ./todo help             # Show usage\n";
        std::cout << "$ ./todo report           # Statistics\n";
    }

    // ls command to see all the todos that are not yet complete
    if (argc == 2 && strcmp(argv[1], "ls") == 0) {

        // Opn file in input mode
        file.open("todo.txt", std::ios::in);

        if (!file) {
            std::cout << "There are no pending todos!\n";
            return 0;  
        }

        std::string str;

        std::vector<std::string> tasks;

        // Save all todos as strings in a vector
        while (std::getline(file, str)) {
            tasks.push_back(str);
        }

        // Display message if there are no todos (vector is empty)
        if (tasks.size() == 0 || (tasks.size() == 1 && tasks[0].length() == 0)) {
            std::cout << "There are no pending todos!\n";
            return 0;
        }

        // Most recently added todo is displayed first
        for (int i = tasks.size() - 1; i >= 0; i--) {
            std::cout << "[" << i + 1 << "] " << tasks[i] << "\n";
        }

        // Close the file
        file.close();
    }

    // Attempting to add a todo with nom message
    if (argc == 2 && strcmp(argv[1], "add") == 0) {
        std::cout << "Error: Missing todo string. Nothing added!\n";
        return 0;
    }

    // Adding a new todo
    if (argc == 3 && strcmp(argv[1], "add") == 0) {
        
        // Store new todo as string
        std::string newTask = argv[2];

        // Attempting to add empty todo, i.e. todo with no message
        if (newTask.length() == 0) {
            std::cout << "Error: Missing todo string. Nothing added!\n";
            return 0;
        }

        // Open file in append mode
        file.open("todo.txt", std::ios::app);

        if (!file) {
            std::cout << "There was an error opening todo.txt!\n";
            return 0;  
        }

        // Append new todo to file
        file << newTask << "\n";

        // Display success message
        std::cout << "Added todo: \"" << newTask << "\"\n";  

        // Close the file
        file.close();
    }

    // Attempting to delete a todo item without giving an index number 
    if (argc == 2 && strcmp(argv[1], "del") == 0) {
        std::cout << "Error: Missing NUMBER for deleting todo.\n";
        return 0;
    }

    // Deleting a todo
    if (argc == 3 && strcmp(argv[1], "del") == 0) {

        // Store index number of todo to be deleted
        size_t taskNumber = atoi(argv[2]);

        // Open file in input mode
        file.open("todo.txt", std::ios::in);

        if (!file) {
            std::cout << "There was an error opening todo.txt!\n";
            return 0;  
        }

        std::string str;

        std::vector<std::string> tasks;

        // Save all todos as strings in a vector
        while (std::getline(file, str)) {
            tasks.push_back(str);
        }

        // Attempting to delete a non-existed todo item
        if (taskNumber < 1 || taskNumber > tasks.size()) {
            std::cout << "Error: todo #" << taskNumber << " does not exist. Nothing deleted.\n";
            return 0;
        }

        // Remove the required todo from the vector
        tasks.erase(tasks.begin() + taskNumber - 1);

        // Open todo.txt file in "truncate" mode, which clears all the content of the file
        std::ofstream ofs;
        ofs.open("todo.txt", std::ofstream::out | std::ofstream::trunc);
        ofs.close();

        // Close the file
        file.close();

        // Open the file again to append the new set of todos to it (after deleting the required todo)
        file.open("todo.txt", std::ios::app);

        // Append the todos line by line
        for (auto& it : tasks) {
            file << it << "\n";
        }

        // Display success message
        std::cout << "Deleted todo #" << taskNumber << "\n";

        // Close the file
        file.close();
    }

    // Attempting to mark as done a todo item without giving an index number
    if (argc == 2 && strcmp(argv[1], "done") == 0) {
        std::cout << "Error: Missing NUMBER for marking todo as done.\n";
        return 0;
    }

    // Marking a todo item as done
    if (argc == 3 && strcmp(argv[1], "done") == 0) {

        // Store index number of todo to be marked as done 
        size_t taskNumber = atoi(argv[2]);

        // Open file in input mode
        file.open("todo.txt", std::ios::in);

        if (!file) {
            std::cout << "There was an error opening todo.txt!\n";
            return 0;  
        }

        std::string str;

        std::vector<std::string> tasks;

        // Save all todos as strings in a vector
        while (std::getline(file, str)) {
            tasks.push_back(str);
        }

        // Attempting to mark as done a non-existent todo item
        if (taskNumber < 1 || taskNumber > tasks.size()) {
            std::cout << "Error: todo #" << taskNumber << " does not exist.\n";
            return 0;
        }

        // Save the done task as a string
        std::string doneTask = tasks[taskNumber - 1];

        // Remove the done task from the vector containing (pending) todo items
        tasks.erase(tasks.begin() + taskNumber - 1);

        // Close the file 
        file.close();

        // Open todo.txt file in "truncate" mode, which clears all the content of the file
        std::ofstream ofs;
        ofs.open("todo.txt", std::ofstream::out | std::ofstream::trunc);
        ofs.close();

        // Open the todo.txt file again to append the new set of pending todos to it (after removing the done todo)
        file.open("todo.txt", std::ios::app);

        // Append the pending todos line by line to todo.txt
        for (auto& it : tasks) {
            file << it << "\n";
        }

        //Close the file
        file.close();

        // Open done.txt to append the done tasks to it
        file.open("done.txt", std::ios::app);

        // Current date/time based on current system
        time_t now = time(0);

        // Localtime
        tm *ltm = localtime(&now);

        // Print various components of the tm structure, which contains info about current date, to the done.txt file
        file << "x " << std::setfill('0') << std::setw(4) << 1900 + ltm -> tm_year << "-"
                    << std::setfill('0') << std::setw(2) << 1 + ltm -> tm_mon << "-"
                    << std::setfill('0') << std::setw(2) << ltm -> tm_mday << " " << doneTask << "\n";

        // Success message
        std::cout << "Marked todo #" << taskNumber << " as done.\n";

        // Close the file
        file.close();
    }

    // Printing the report
    if (argc == 2 && strcmp(argv[1], "report") == 0) {

        // Open todo.txt in in[ut mode]
        file.open("todo.txt", std::ios::in);

        if (!file) {
            std::cout << "There was an error opening todo.txt!\n";
            return 0;  
        }

        std::string str;

        std::vector<std::string> tasks;

        // Save all (pending) todos as strings in a vector
        while (std::getline(file, str)) {
            tasks.push_back(str);
        }

        // Number of pending todos is equal to the size of the vector 
        size_t numberOfTodoTasks = tasks.size();

        file.close();

        // Open the done.txt file
        file.open("done.txt", std::ios::in);

        if (!file) {
            std::cout << "There was an error opening done.txt!\n";
            return 0;  
        }

        std::string str1;

        std::vector<std::string> doneTasks;

        // Save all (done) todos as strings in a vector
        while (std::getline(file, str1)) {
            doneTasks.push_back(str1);
        }

        // Number of done todos is equal to the size of the vector of done todos
        size_t numberOfDoneTasks = doneTasks.size();

        // Close the file
        file.close();

        // Current date/time based on current system
        time_t now = time(0);

        // Localtime
        tm *ltm = localtime(&now);

        // Print report containing various components of the tm structure, which contains info about current date
        std::cout << std::setfill('0') << std::setw(4) << 1900 + ltm -> tm_year << "-"
                    << std::setfill('0') << std::setw(2) << 1 + ltm -> tm_mon << "-"
                    << std::setfill('0') << std::setw(2) << ltm -> tm_mday << " Pending : " << numberOfTodoTasks
                    << " Completed : " << numberOfDoneTasks << "\n";
    }

    return 0;
}
