#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
#include <sstream>


std::string show_task(int task_id){
       std::ifstream file("tasks.txt");
       file.seekg(140*(task_id - 1));
        const int portion_length = 140; //140 is the size of each task within the text document  
        char portion[portion_length + 1]; // +1 for null terminator

    // Read the portion of the file
    file.read(portion, portion_length);
    portion[file.gcount()] = '\0'; // Null-terminate the string (if needed)
     file.close();
    
    std::string portionString(portion);
    std::cout<<portionString;//<<std::endl;

    std::ifstream file_new("tasks_Check.txt");
       file_new.seekg(task_id - 1);
        char portion_new[1]; 

    // Read the portion of the file
    file_new.read(portion_new, 1);{
     file_new.close();
    
    if (portion_new[0] == '0'){
        std::cout<<"This Task is not Completed"<<std::endl;
    }
    else {
         std::cout<<"This Task is Completed" <<std::endl;
}
    }
    return portionString;
}

//change the status of the task completion between completed and not completed
void Check_As_Completed (int Task_number){
   // Open the file for reading
    std::ifstream file("tasks_Check.txt");// new text document for storing checks  
    if (!file.is_open()) {
        std::cerr << "Failed to open file for reading." << std::endl;
        return;
    } 
    // Read the entire contents into a string
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();  // Close the file after reading
    std::string content = buffer.str();
    if (content[Task_number-1] == '0'){
    content.replace(Task_number-1, 1, "1");}
    else {
        content.replace(Task_number-1, 1, "0");}
    
    // Open the file for writing (this truncates the existing file)
    std::ofstream outfile("tasks_Check.txt");
    if (!outfile.is_open()) {
        std::cerr << "Failed to open file for writing." << std::endl;
        return;
    }

    // Write the modified content back to the file
    outfile << content;
    outfile.close();

}

//removing task from the to do list
void Remove_Task (int Task_number) {
    // Open the file for reading
    std::ifstream file("tasks.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open file for reading." << std::endl;
        return;
    }

    // Read the entire contents into a string
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();  // Close the file after reading

    std::string content = buffer.str();
    int start_pos = (Task_number-1) * 140;
    // Check if start_pos is within the string bounds
    if (start_pos >= content.size()) {
        std::cerr << "Start position is out of the string's bounds." << std::endl;
        return;
    }

    // Erase the specified section of the text
    content.erase(start_pos, 140);

    // Open the file for writing (this truncates the existing file)
    std::ofstream outfile("tasks.txt");
    if (!outfile.is_open()) {
        std::cerr << "Failed to open file for writing." << std::endl;
        return;
    }

    // Write the modified content back to the file
    outfile << content;
    outfile.close();


// removing the completion index for the task
    std::ifstream file_new("tasks_Check.txt");
    if (!file_new.is_open()) {
        std::cerr << "Failed to open file for reading." << std::endl;
        return;
    }

    // Read the entire contents into a string
    std::stringstream buffer_new;
    buffer_new << file_new.rdbuf();
    file_new.close();  // Close the file after reading

    content = buffer_new.str();
   
    // Erase the index
    content.erase(Task_number-1, 1);

    // Open the file for writing (this truncates the existing file)
    std::ofstream outfile_new("tasks_Check.txt");
    if (!outfile_new.is_open()) {
        std::cerr << "Failed to open file for writing." << std::endl;
        return;
    }

    // Write the modified content back to the file
    outfile_new << content;
    outfile_new.close();

}

//storing task into file to save its info
void addTaskToFile(const std::string& task,int desiredSize) {
    
    std::string pad_str = task;
    if (pad_str.size() < desiredSize) {
        pad_str.resize(desiredSize, ' '); // Pad with spaces
    } else if (pad_str.size() > desiredSize) {
        pad_str = pad_str.substr(0, desiredSize); // Truncate the string if it exceeds the desired size
    }
    std::ofstream outputFile("tasks.txt", std::ios::app); // Open file in append mode
    if (outputFile.is_open()) {
        outputFile << pad_str << std::endl; // Append task to file
        outputFile.close(); // Close file
    } else {
        std::cerr << "Unable to open file for writing." << std::endl;
    }
}

//function that add task to the do list
std::string add_task() {
    std::string description, due_date, priority, category;
    
    std::cout << "please enter task description: ";
    std::getline(std::cin, description);
    std::getline(std::cin, description);
    if (std::cin.fail()) {
        std::cerr << "Error: Invalid input for the first value.\n";}
    addTaskToFile(description, 99);

    std::cout << "Enter due date (YYYY-MM-DD): ";
    std::getline(std::cin, due_date);
    addTaskToFile(due_date, 14);
    std::cout << "Enter priority (low, moderate, high): ";
    std::getline(std::cin, priority);
    addTaskToFile(priority, 9);
    std::cout << "Enter category (college, work, house, family, hobbies, friends, me time): ";
    std::getline(std::cin, category);
    addTaskToFile(category, 14);
    
    std::cout << "Task added successfully:" << std::endl;
    std::cout << "Description: " << description << std::endl;
    std::cout << "Due Date: " << due_date << std::endl;
    std::cout << "Priority: " << priority << std::endl;
    std::cout << "Category: " << category << std::endl;
    

// to add a new check point to the folder
    std::ofstream outputFile("tasks_Check.txt", std::ios::app); // Open file in append mode
    if (outputFile.is_open()) {
        outputFile << 0 << std::endl; // Append task to file
        outputFile.close(); // Close file
    } else {
        std::cerr << "Unable to open file for writing." << std::endl;
    }

    return "000";

}

//main function
int main(){
    char key;
do {
        
     
    int choice;
    int task_id;
    std::cout<< "Please enter 1 to add, 2 to display the task , 3 to delete, 4 to to check as complete: ";
    std::cin >> choice;

    if (choice == 1 ){
        add_task();}
    else if (choice == 2){
        std::cout<< "please enter task ID: ";
        std::cin >> task_id;
        show_task (task_id);}
    else if (choice == 3){
        std::cout<< "please enter task ID: ";
        std::cin >> task_id;
        Remove_Task (task_id);}
    else if (choice == 4){
        std::cout<< "please enter task ID: ";
        std::cin >> task_id;
        Check_As_Completed (task_id);}
    else{
        std::cout<< "the value you entered is not permitted by the program."<< std::endl;};
        do {
            std::cout << "Press ESC to close, and enter to rerun " << std::endl;
            key = _getch();}
            while (key != 13 && key != 27);

    } while (key == 13 );
    return 0;
}


