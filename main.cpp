#include<iostream>
#include<fstream>

using namespace std;

void action_selector(std::string);
void add_task(); 
void print_task();

#define FILENAME "task.csv"

int main(){

    std::string action;

    std::cout<< "Welcome on your ZPlanner\n";
    std::cout<< "What action do you want to realize?\n";
    std::cout<< "1 - print listed task\n";
    std::cout<< "2 - add a new task\n";
    std::cout<< "Enter the task id :\n";
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
    std::cout<< "function add_task()";

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
