#include <iostream>
#include <string>
#include <ostream>

void print_game_rules(int max_number){
    std::cout << "===================================================\n" 
        << "Welcome to the Hot-Cold Guess game, copyright 2020.\n"
        << "---------------------------------------------------\n\n"
        << "These are the game rules:\n"
        << "\t* I’ll choose a random number in [1,50]. Your job is to guess that number.\n"
        << "\t* From the second guess onward, I’ll tell you if your guess is hot (closer than the previous guess) or cold (farther from the previous guess).\n"
        << "\t* If you wish to quit the game, just type in a negative number.\n\n"
        << "Good luck!\n"
        << "----------------------------------------------------\n\n";
}

int main(int argc, char *argv[]){
    // for (size_t i = 0; i < argc; i++)
    // {
    //     if(argv[i] == "-h" || argv[i] == "--help") std::cout << "help";
    // }
    
    try
    {
        int maxNumber = argc == 2 ? std::stoi(argv[1]) : 30;
        print_game_rules(50);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}