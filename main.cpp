#include<iostream>
#include<fstream>
#include<ctime>
using namespace std;

void action_selector(std::string);
void add_task(); 
void print_task();

#define FILENAME "task.csv"

int main(){

    std::time_t time_today = std::time(nullptr);
    std::string str_today = std::asctime(std::localtime(&time_today));
    std::string action;

    std::cout<< "Welcome on your ZPlanner\nToday we are " << str_today << "\n"
             << "What action do you want to realize?\n"
             << "1 - print listed task\n"
             << "2 - add a new task\n"
             << "Enter the task id :\n";
    std::cin>> action;
    std::cin.ignore();
    
    action_selector(action);
    
    std::cin.get();
}

void action_selector(std::string action){
    switch(std::stoi(action)){
        case 1: { print_task();
                    break;}
        case 2: { add_task();
                    break;}
        default:  std::cout<< "Unaffected id entered.";
                  break;
    }
}

void add_task(){
    std::cout<< "ADD TASK : ";
    std::ofstream out(FILENAME, std::fstream::app | std::fstream::out | std::fstream::in);
    std::string new_task;

    std::cin>> new_task;
    out << new_task;
    out << "\n";

    std::cout<< "Task added.\n";

}

void print_task(){
    std::cout<< "TODO :\n";
    
    std::ifstream file(FILENAME);
    std::string str_tmp;

    while(std::getline(file, str_tmp)){
        std::cout<< " - ";
        std::cout<< str_tmp;
        std::cout<< '\n';
    }
}
