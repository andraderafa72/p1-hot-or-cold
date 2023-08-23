#include <iostream>
#include <string>
#include <ostream>

constexpr short default_value{30};
constexpr short max_value{30};

void print_game_rules(int max_number)
{
    std::cout << "===================================================\n"
              << "Welcome to the Hot-Cold Guess game, copyright 2020.\n"
              << "---------------------------------------------------\n\n"
              << "These are the game rules:\n"
              << "\t* I’ll choose a random number in [1,"<< max_number << "]. Your job is to guess that number.\n"
              << "\t* From the second guess onward, I’ll tell you if your guess is hot (closer than the previous guess) or cold (farther from the previous guess).\n"
              << "\t* If you wish to quit the game, just type in a negative number.\n\n"
              << "Good luck!\n"
              << "----------------------------------------------------\n\n";
}

void print_end_game(){
    std::cout << "\nThanks for playing.\n";
}

void print_win_game(int rounds){
    std::cout << ">>> Yeah, correct guess!\n"
    << "\nIt took you " << rounds << " rounds to guess the correct number!\n"
    << "===================================================\n";

    print_end_game();
}

int mod(int n)
{
    return n >= 0 ? n : -n;
}

class HotOrCold
{
    int prev_value;
    int target;
    int limit;
    int round;

public:
    bool game_finished = false;
    HotOrCold(int _limit)
    {
        round = 1;
        prev_value = -1;
        limit = _limit;
        target = std::rand() % limit;
    }

    void guess_number()
    {
        if (round == 1)
        {
            std::cout << ">>> Guess the number: ";
        }

        int value;
        std::cin >> value;

        if(value < 0){
            game_finished = true;
            print_end_game();
            return;
        }

        if(value > limit){
            std::cout << ">>> Value above the limit! Type a value between 1 and " << limit << ".\n";
            return;
        }

        bool is_target = target == value;
        if (is_target)
        {
            game_finished = true;
            print_win_game(round);
            return;
        }

        if (round == 1)
        {
            std::cout << ">>> Nop, try again: ";
            round++;
            return;
        }


        int distance_from_target = mod(target - value);
        int prev_distance = mod(target - prev_value);
        std::string status = distance_from_target > prev_distance
                                 ? "it’s getting cold"
                                 : "it’s hot though";
                                 
        round++;
        prev_value = value;

        std::cout << ">>> Nop, " << status << ", try again: ";
    }
};

int main(int argc, char *argv[])
{

    int max_guess = argc == 2 ? std::stoi(argv[1]) : default_value;
    print_game_rules(max_guess);

    HotOrCold game(max_guess);

    while (!game.game_finished)
    {
        game.guess_number();
    }

    return 0;
}