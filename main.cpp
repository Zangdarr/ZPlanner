#include<iostream>
#include<fstream>
#include<ctime>
using namespace std;

void action_selector(std::string);
void add_task(); 
void print_task();

struct configuration{
    std::string filename_today;
    std::string filename_current;
};

struct configuration s_config {"undefined", "undefined"};

int main(){
    //creation of the database folder
    std::system("[ ! -d database ] && mkdir database");

    std::string action;
    char filename_today[9];

    std::time_t time_today = std::time(nullptr);
    std::string str_today = std::asctime(std::localtime(&time_today));
    std::strftime(filename_today, sizeof(filename_today), "%m-%d-%y", std::localtime(&time_today));
    
    s_config.filename_today.assign(filename_today, 9);  
    s_config.filename_current.assign(filename_today, 9);  
    
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
    std::string new_task;
    std::getline(std::cin, new_task); //get the task from the user

    std::string today_year = s_config.filename_today.substr(6,2);
    std::string today_month = s_config.filename_today.substr(0,2);
    std::string today_folder = "database/20" + today_year + "_" + today_month; // determine the folder of the day

    std::string command_line = "[ ! -d " + today_folder + " ] && mkdir " + today_folder; 
    std::system(command_line.c_str()); // creation of the folder if needed
    
    std::string today_path = today_folder + "/" + s_config.filename_today; //

    std::ofstream out(today_path, std::fstream::app | std::fstream::out | std::fstream::in);
    out << new_task;
    out << "\n";

    std::cout<< "Task added.\n";

}

void print_task(){
    std::cout<< "TODO :\n";
    
    std::string today_year = s_config.filename_today.substr(6,2);
    std::string today_month = s_config.filename_today.substr(0,2);
    std::string today_folder = "database/20" + today_year + "_" + today_month; // determine the folder of the day

    std::string today_path = today_folder + "/" + s_config.filename_today; //

   
    std::ifstream file(today_path);
    std::string str_tmp;

    while(std::getline(file, str_tmp)){
        std::cout<< " - ";
        std::cout<< str_tmp;
        std::cout<< '\n';
    }
}
