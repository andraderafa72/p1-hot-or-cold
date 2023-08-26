#include <iostream>
#include <string>
#include <ostream>

void usage()
{
  std::cout << "Usage: hot_cold [<max_guess_value>] [-h] [--help]\n"
            << "\t <max_guess_value> => Max guess number. The game will generate a target between 1 and this parameter value. Default = 30"
            << "\t -h, --help => Print usage";
}

void print_game_rules(int max_number)
{
  std::cout << "===================================================\n"
            << "Welcome to the Hot-Cold Guess game, copyright 2020.\n"
            << "---------------------------------------------------\n\n"
            << "These are the game rules:\n"
            << "\t* I’ll choose a random number in [1," << max_number << "]. Your job is to guess that number.\n"
            << "\t* From the second guess onward, I’ll tell you if your guess is hot (closer than the previous guess) or cold (farther from the previous guess).\n"
            << "\t* If you wish to quit the game, just type in a negative number.\n\n"
            << "Good luck!\n"
            << "----------------------------------------------------\n\n";
}

void print_end_game()
{
  std::cout << "\nThanks for playing.\n";
}

void print_win_game(int rounds)
{
  std::cout << ">>> Yeah, correct guess!\n"
            << "\nIt took you " << rounds << " rounds to guess the correct number!\n"
            << "===================================================\n";

  print_end_game();
}

struct GameSettings
{
  short max_guess;
  static constexpr short default_guess_limit_value{30};
  static constexpr short max_limit_value{100};
};

void print_param_error()
{
  std::cout << ">>> Invalid limit, you should pass a value between 1 and " << GameSettings::max_limit_value << "\n";
  exit(1);
}

GameSettings proccess_arguments(int argc, char *argv[])
{
  GameSettings game_settings;

  for (size_t i = 0; i < argc; i++)
  {
    if (argv[i] == "-h" || argv[i] == "--help")
    {
      usage();
      exit(1);
    }
  }

  try
  {
    game_settings.max_guess = argc >= 2 ? std::stoi(argv[1]) : game_settings.default_guess_limit_value;
    if (game_settings.max_guess > game_settings.max_limit_value)
    {
      print_param_error();
    }
  }
  catch (const std::exception &e)
  {
    print_param_error();
  }

  return game_settings;
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

    if (value < 0)
    {
      game_finished = true;
      print_end_game();
      return;
    }

    if (value > limit)
    {
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
  GameSettings game_settings = proccess_arguments(argc, argv);

  print_game_rules(game_settings.max_guess);
  HotOrCold game(game_settings.max_guess);

  while (!game.game_finished)
  {
    game.guess_number();
  }

  return 0;
}