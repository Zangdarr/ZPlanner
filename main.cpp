#include<iostream>
#include<fstream>
#include<ctime>
#include<cstring>

#include<typeinfo>

using namespace std;

void action_selector(std::string);
void add_task(); 
void print_task();
void modify_current_date();

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
    
    std::cout<< "Welcome on your ZPlanner" << std::endl
             << "Today we are " << str_today << std::endl;

    while(1){
        std::cout<< "What action do you want to realize on "<< s_config.filename_current << " ?" << std::endl
                 << "1 - print listed task" << std::endl
                 << "2 - add a new task" << std::endl
                 << "3 - modify the current date" << std::endl
                 << "Enter the task id :" << std::endl;

        std::cin>> action;
        std::cin.ignore();
        
        if(not (action == "1" or action == "2" or action == "3")){
            std::cout<< "Non attributed action." << std::endl << std::endl;
            continue;
        }

        action_selector(action);
    
        std::cin.get();

    }
}

void action_selector(std::string action){
    switch(std::stoi(action)){
        case 1: { print_task();
                    break;}
        case 2: { add_task();
                    break;}
        case 3: { modify_current_date();
                    break;}
        default:  std::cout<< "Unaffected id entered.";
                  break;
    }
}

void modify_current_date(){
    std::string new_date;
    bool b_structure, b_mm, b_dd; 
    int tmp;

    do{
        std::cout<< "Enter a date(mm-dd-yy) : ";
        std::getline(std::cin, new_date );

        b_structure = new_date[2] == new_date[5] and new_date[5] == '-' and new_date.length() == 8;
        if(not b_structure){
            std::cout<< "Error in format. Please respect the format given." << std::endl << std::endl ;
            continue;}

        tmp = std::stoi(new_date.substr(0,2));
        b_mm =  0 < tmp and tmp <= 12;
        if(not b_mm){
            std::cout<< "Error. The month provided isn't correct." << std::endl << std::endl ;
            continue;}

        tmp = std::stoi(new_date.substr(3,2));
        b_dd = 0 < tmp and tmp <= 31;
        if(not b_dd){
            std::cout<< "Error. The day provided isn't correct." << std::endl << std::endl ;
            continue;}
        
        break;
    } while(1);

    s_config.filename_current = new_date;  

}

void add_task(){
    std::cout<< "ADD TASK : ";
    std::string new_task;
    std::getline(std::cin, new_task); //get the task from the user

    std::string current_year = s_config.filename_current.substr(6,2);
    std::string current_month = s_config.filename_current.substr(0,2);
    std::string current_folder = "database/20" + current_year + "_" + current_month; // determine the current folder

    std::string command_line = "[ ! -d " + current_folder + " ] && mkdir " + current_folder; 
    std::system(command_line.c_str()); // creation of the folder if needed
    
    std::string current_path = current_folder + "/" + s_config.filename_current; //

    std::ofstream out(current_path, std::fstream::app | std::fstream::out | std::fstream::in);
    out << new_task;
    out << "\n";

    std::cout<< "Task added.\n";

}

void print_task(){
    std::cout<< "TODO :\n";
    
    std::string current_year = s_config.filename_current.substr(6,2);
    std::string current_month = s_config.filename_current.substr(0,2);
    std::string current_folder = "database/20" + current_year + "_" + current_month; // determine the folder of the day

    std::string current_path = current_folder + "/" + s_config.filename_current; //

    std::ifstream file(current_path);
    std::string str_tmp;

    while(std::getline(file, str_tmp)){
        std::cout<< " - ";
        std::cout<< str_tmp;
        std::cout<< '\n';
    }
}
