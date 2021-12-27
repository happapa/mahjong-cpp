#include "mahjong/mahjong.hpp"

#include <algorithm>
#include <chrono>
#include <numeric>
#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <iterator>
#include <fstream>

using namespace mahjong;

typedef std::vector<int> Tiles;

struct Problem
{
    int id;
    int round;
    int seat;
    int turn;
    int dora;
    int shanten;
    int ncand;
    Tiles wall;
    Tiles hand;
    std::vector<int> candidates;
    std::vector<int> ev;
    std::vector<int> ukeire;
    std::vector<bool> shanten_down;

    std::string to_string()
    {
        std::string s = "";
        s += "Id: " + std::to_string(id) + " ";
        s += "Round: " + std::to_string(round) + " ";
        s += "Seat: " + std::to_string(seat) + " ";
        s += "Turn: " + std::to_string(turn) + " ";
        s += "Dora: " + std::to_string(dora) + " ";
        s += "Shanten: " + std::to_string(shanten) + " ";
        s += "NCand: " + std::to_string(ncand) + "\n";
        // s += "Wall: ";
        // for (int i = 0; i < wall.size(); i++)
        // {
        //     s += std::to_string(wall.at(i)) + " ";
        // }
        s += "Hand: ";
        for (int i = 0; i < hand.size(); i++)
        {
            s += std::to_string(hand.at(i)) + " ";
        }
        s += "\nCand: ";
        for (int i = 0; i < candidates.size(); i++)
        {
            // s += std::to_string(candidates.at(i)) + " ";
            s += Tile::Name.at(candidates.at(i)) + " ";
        }
        s += "\nEV: ";
        for (int i = 0; i < ev.size(); i++)
        {
            s += std::to_string(ev.at(i)) + " ";
        }
        s += "\nUkeire: ";
        for (int i = 0; i < ukeire.size(); i++)
        {
            s += std::to_string(ukeire.at(i)) + " ";
        }
        s += "\nSD: ";
        for (int i = 0; i < shanten_down.size(); i++)
        {
            s += std::to_string(shanten_down.at(i)) + " ";
        }
        s += "\n" + Hand(hand).to_string() + " " + std::to_string(hand.size()) + " " + std::to_string(shanten);


        return s;
    }


    std::string to_string_neat()
    {
        std::string s = "";
        s += std::to_string(id) + " ";
        s += std::to_string(round) + " ";
        s += std::to_string(seat) + " ";
        s += std::to_string(turn) + " ";
        s += std::to_string(dora) + " ";
        s += std::to_string(shanten) + " ";
        s += std::to_string(ncand) + "\n";

        for (int i = 0; i < hand.size(); i++)
        {
            s += std::to_string(hand.at(i)) + " ";
        }

        s += "\n";
        for (int i = 0; i < candidates.size(); i++)
        {
            s += std::to_string(candidates.at(i)) + " ";
        }

        s += "\n";
        for (int i = 0; i < ev.size(); i++)
        {
            s += std::to_string(ev.at(i)) + " ";
        }

        s += "\n";
        for (int i = 0; i < ukeire.size(); i++)
        {
            s += std::to_string(ukeire.at(i)) + " ";
        }

        s += "\n";
        for (int i = 0; i < shanten_down.size(); i++)
        {
            s += std::to_string(shanten_down.at(i)) + " ";
        }
        return s;
    }

    std::string to_string_oneline()
    {
        std::string s = "";
        s += std::to_string(id) + " ";
        s += std::to_string(round) + " ";
        s += std::to_string(seat) + " ";
        s += std::to_string(turn) + " ";
        s += std::to_string(dora) + " ";
        s += std::to_string(shanten) + " ";
        s += std::to_string(ncand) + " ";

        for (int i = 0; i < hand.size(); i++)
        {
            s += std::to_string(hand.at(i)) + " ";
        }

        // s += "\n";
        for (int i = 0; i < candidates.size(); i++)
        {
            s += std::to_string(candidates.at(i)) + " ";
        }

        // s += "\n";
        for (int i = 0; i < ev.size(); i++)
        {
            s += std::to_string(ev.at(i)) + " ";
        }

        // s += "\n";
        for (int i = 0; i < ukeire.size(); i++)
        {
            s += std::to_string(ukeire.at(i)) + " ";
        }

        // s += "\n";
        for (int i = 0; i < shanten_down.size(); i++)
        {
            s += std::to_string(shanten_down.at(i)) + " ";
        }
        return s;
    }
};


template<typename Iter, typename RandomGenerator>
Iter select_randomly(Iter start, Iter end, RandomGenerator& g) {
    std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
    std::advance(start, dis(g));
    return start;
}

template<typename Iter>
Iter select_randomly(Iter start, Iter end) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return select_randomly(start, end, gen);
}


void discard_tile(int tile, Tiles &hand)
{
    for (int i = 0; i < hand.size(); i++)
    {
        if (hand.at(i) == tile ||
            tile == Tile::Manzu5 && hand.at(i) == Tile::AkaManzu5 ||
            tile == Tile::Pinzu5 && hand.at(i) == Tile::AkaPinzu5 ||
            tile == Tile::Sozu5 && hand.at(i) == Tile::AkaSozu5)
        {
            hand.erase(hand.begin()+i);
            break;
        }        
    }
}


void draw_from_wall(Tiles &hand, Tiles &wall)
{
    int tile = wall.back();
    hand.push_back(tile);
    wall.pop_back();
}


Tiles draw_hand(Tiles &wall)
{
    Tiles hand;
    for (int i = 0; i < 14; i++)
    {
        hand.push_back(wall.back());
        wall.pop_back();
    }
    
    return hand;
}


int draw_dora(Tiles &wall)
{
    int dora = wall.back();
    wall.pop_back();
    return dora;
}


Tiles random_wall()
{
    std::vector<int> wall{
        Tile::Manzu1, Tile::Manzu1, Tile::Manzu1, Tile::Manzu1,    
        Tile::Manzu2, Tile::Manzu2, Tile::Manzu2, Tile::Manzu2,    
        Tile::Manzu3, Tile::Manzu3, Tile::Manzu3, Tile::Manzu3,    
        Tile::Manzu4, Tile::Manzu4, Tile::Manzu4, Tile::Manzu4,    
        Tile::Manzu5, Tile::Manzu5, Tile::Manzu5, Tile::AkaManzu5, 
        Tile::Manzu6, Tile::Manzu6, Tile::Manzu6, Tile::Manzu6,    
        Tile::Manzu7, Tile::Manzu7, Tile::Manzu7, Tile::Manzu7,    
        Tile::Manzu8, Tile::Manzu8, Tile::Manzu8, Tile::Manzu8,    
        Tile::Manzu9, Tile::Manzu9, Tile::Manzu9, Tile::Manzu9,    
        Tile::Pinzu1, Tile::Pinzu1, Tile::Pinzu1, Tile::Pinzu1,    
        Tile::Pinzu2, Tile::Pinzu2, Tile::Pinzu2, Tile::Pinzu2,    
        Tile::Pinzu3, Tile::Pinzu3, Tile::Pinzu3, Tile::Pinzu3,    
        Tile::Pinzu4, Tile::Pinzu4, Tile::Pinzu4, Tile::Pinzu4,    
        Tile::Pinzu5, Tile::Pinzu5, Tile::Pinzu5, Tile::AkaPinzu5,
        Tile::Pinzu6, Tile::Pinzu6, Tile::Pinzu6, Tile::Pinzu6,   
        Tile::Pinzu7, Tile::Pinzu7, Tile::Pinzu7, Tile::Pinzu7,   
        Tile::Pinzu8, Tile::Pinzu8, Tile::Pinzu8, Tile::Pinzu8,   
        Tile::Pinzu9, Tile::Pinzu9, Tile::Pinzu9, Tile::Pinzu9,   
        Tile::Sozu1, Tile::Sozu1, Tile::Sozu1, Tile::Sozu1,    
        Tile::Sozu2, Tile::Sozu2, Tile::Sozu2, Tile::Sozu2,    
        Tile::Sozu3, Tile::Sozu3, Tile::Sozu3, Tile::Sozu3,    
        Tile::Sozu4, Tile::Sozu4, Tile::Sozu4, Tile::Sozu4,    
        Tile::Sozu5, Tile::Sozu5, Tile::Sozu5, Tile::AkaSozu5, 
        Tile::Sozu6, Tile::Sozu6, Tile::Sozu6, Tile::Sozu6,    
        Tile::Sozu7, Tile::Sozu7, Tile::Sozu7, Tile::Sozu7,    
        Tile::Sozu8, Tile::Sozu8, Tile::Sozu8, Tile::Sozu8,    
        Tile::Sozu9, Tile::Sozu9, Tile::Sozu9, Tile::Sozu9,    
        Tile::Ton, Tile::Ton, Tile::Ton, Tile::Ton,       
        Tile::Nan, Tile::Nan, Tile::Nan, Tile::Nan,       
        Tile::Sya, Tile::Sya, Tile::Sya, Tile::Sya,       
        Tile::Pe, Tile::Pe, Tile::Pe, Tile::Pe,        
        Tile::Haku, Tile::Haku, Tile::Haku, Tile::Haku, 
        Tile::Hatu, Tile::Hatu, Tile::Hatu, Tile::Hatu, 
        Tile::Tyun, Tile::Tyun, Tile::Tyun, Tile::Tyun  
    };

    auto rd = std::random_device {}; 
    auto rng = std::default_random_engine { rd() };
    std::shuffle(std::begin(wall), std::end(wall), rng);

    return wall;
}


Tiles random_wall_no_honors()
{
    std::vector<int> wall{
        Tile::Manzu1, Tile::Manzu1, Tile::Manzu1, Tile::Manzu1,    
        Tile::Manzu2, Tile::Manzu2, Tile::Manzu2, Tile::Manzu2,    
        Tile::Manzu3, Tile::Manzu3, Tile::Manzu3, Tile::Manzu3,    
        Tile::Manzu4, Tile::Manzu4, Tile::Manzu4, Tile::Manzu4,    
        Tile::Manzu5, Tile::Manzu5, Tile::Manzu5, Tile::AkaManzu5, 
        Tile::Manzu6, Tile::Manzu6, Tile::Manzu6, Tile::Manzu6,    
        Tile::Manzu7, Tile::Manzu7, Tile::Manzu7, Tile::Manzu7,    
        Tile::Manzu8, Tile::Manzu8, Tile::Manzu8, Tile::Manzu8,    
        Tile::Manzu9, Tile::Manzu9, Tile::Manzu9, Tile::Manzu9,    
        Tile::Pinzu1, Tile::Pinzu1, Tile::Pinzu1, Tile::Pinzu1,    
        Tile::Pinzu2, Tile::Pinzu2, Tile::Pinzu2, Tile::Pinzu2,    
        Tile::Pinzu3, Tile::Pinzu3, Tile::Pinzu3, Tile::Pinzu3,    
        Tile::Pinzu4, Tile::Pinzu4, Tile::Pinzu4, Tile::Pinzu4,    
        Tile::Pinzu5, Tile::Pinzu5, Tile::Pinzu5, Tile::AkaPinzu5,
        Tile::Pinzu6, Tile::Pinzu6, Tile::Pinzu6, Tile::Pinzu6,   
        Tile::Pinzu7, Tile::Pinzu7, Tile::Pinzu7, Tile::Pinzu7,   
        Tile::Pinzu8, Tile::Pinzu8, Tile::Pinzu8, Tile::Pinzu8,   
        Tile::Pinzu9, Tile::Pinzu9, Tile::Pinzu9, Tile::Pinzu9,   
        Tile::Sozu1, Tile::Sozu1, Tile::Sozu1, Tile::Sozu1,    
        Tile::Sozu2, Tile::Sozu2, Tile::Sozu2, Tile::Sozu2,    
        Tile::Sozu3, Tile::Sozu3, Tile::Sozu3, Tile::Sozu3,    
        Tile::Sozu4, Tile::Sozu4, Tile::Sozu4, Tile::Sozu4,    
        Tile::Sozu5, Tile::Sozu5, Tile::Sozu5, Tile::AkaSozu5, 
        Tile::Sozu6, Tile::Sozu6, Tile::Sozu6, Tile::Sozu6,    
        Tile::Sozu7, Tile::Sozu7, Tile::Sozu7, Tile::Sozu7,    
        Tile::Sozu8, Tile::Sozu8, Tile::Sozu8, Tile::Sozu8,    
        Tile::Sozu9, Tile::Sozu9, Tile::Sozu9, Tile::Sozu9 
    };

    auto rd = std::random_device {}; 
    auto rng = std::default_random_engine { rd() };
    std::shuffle(std::begin(wall), std::end(wall), rng);

    return wall;
}



bool compare_tiles(const int a, const int b)
{
    int af = a;
    int bf = b;

    if (a == Tile::AkaManzu5)
    {
        af = Tile::Manzu5;
    }
    else if (a == Tile::AkaPinzu5)
    {
        af = Tile::Pinzu5;
    }
    else if (a == Tile::AkaSozu5)
    {
        af = Tile::Sozu5;
    }

    if (b == Tile::AkaManzu5)
    {
        bf = Tile::Manzu5;
    }
    else if (b == Tile::AkaPinzu5)
    {
        bf = Tile::Pinzu5;
    }
    else if (b == Tile::AkaSozu5)
    {
        bf = Tile::Sozu5;
    }
    
    return af < bf;
}


void sort_hand(Tiles &hand)
{
    std::sort(hand.begin(), hand.end(),
        [&hand](const int &a, const int &b){return compare_tiles(a,b);});
}


Problem generate_problem(int id)
{
    std::vector<int> possible_turns{3, 4, 5, 6, 7, 8, 9};
    std::vector<int> possible_round{Tile::Ton, Tile::Nan};
    std::vector<int> possible_seat{Tile::Ton, Tile::Nan, Tile::Sya, Tile::Pe};
    std::vector<int> possible_shanten{1, 1, 1, 2};

    Problem problem;
    problem.id = id;
    problem.round = *select_randomly(possible_round.begin(), possible_round.end());
    problem.seat = *select_randomly(possible_seat.begin(), possible_seat.end());
    problem.turn = *select_randomly(possible_turns.begin(), possible_turns.end());
    problem.shanten = 99;
    problem.wall = random_wall_no_honors();
    problem.dora = draw_dora(problem.wall);
    problem.hand = draw_hand(problem.wall);
    // problem.ev = std::vector<double>(14, 0);
    // problem.ukeire = std::vector<int>(14, 0);
    // problem.shanten_down = std::vector<bool>(14, false);

    int syanten_type = SyantenType::Normal;
    int flag = ExpectedValueCalculator::CalcSyantenDown   
               | ExpectedValueCalculator::CalcTegawari    
               | ExpectedValueCalculator::CalcDoubleReach 
               | ExpectedValueCalculator::CalcIppatu      
               | ExpectedValueCalculator::CalcHaiteitumo  
               | ExpectedValueCalculator::CalcUradora     
               | ExpectedValueCalculator::CalcAkaTileTumo;

    ExpectedValueCalculator exp_value_calculator;
    ScoreCalculator score_calculator;
    score_calculator.set_bakaze(problem.round);
    score_calculator.set_zikaze(problem.seat);
    score_calculator.set_dora_indicators(std::vector<int>{problem.dora});

    auto [_, syanten] = SyantenCalculator::calc(Hand(problem.hand), syanten_type);
    problem.shanten = syanten;

    int shanten_goal = *select_randomly(possible_shanten.begin(), possible_shanten.end());

    while (problem.shanten > shanten_goal)
    {
        std::vector<int> unnecessary = UnnecessaryTileSelector::select_normal(Hand(problem.hand));
        int d = *select_randomly(unnecessary.begin(), unnecessary.end());
        discard_tile(d, problem.hand);

        std::vector<int> required = RequiredTileSelector::select_normal(Hand(problem.hand));
        problem.hand.push_back(*select_randomly(required.begin(), required.end()));

        auto [_, syanten] = SyantenCalculator::calc(Hand(problem.hand), syanten_type);
        problem.shanten = syanten;
    }

    sort_hand(problem.hand);

    auto [success, candidates] = exp_value_calculator.calc(Hand(problem.hand),
        score_calculator, std::vector<int>{problem.dora}, syanten_type, flag);
    
    if (!success || candidates[0].tenpai_probs.empty())
    {
        throw;
    }

    problem.ncand = candidates.size();
    int turn = problem.turn;
    std::sort(candidates.begin(), candidates.end(),
                  [turn](const Candidate &a, const Candidate &b) {
                      return a.exp_values[turn - 1] > b.exp_values[turn - 1];
                  });

    for (int i = 0; i < candidates.size(); i++)
    {
        problem.candidates.push_back(candidates.at(i).tile);
        problem.ev.push_back(std::round(candidates.at(i).exp_values.at(problem.turn - 1)));
        problem.ukeire.push_back(std::accumulate(candidates.at(i).required_tiles.begin(), candidates.at(i).required_tiles.end(), 0,
                            [](auto &a, auto &b) { return a + std::get<1>(b); }));
        problem.shanten_down.push_back(candidates.at(i).syanten_down);
    }

    return problem;
}



int main(int, char**)
{
    std::ofstream file;
    file.open("problems.txt", std::ios::out);

    for (int i = 0; i < 1000; i++)
    {
        auto problem = generate_problem(i);
        std::cout << problem.to_string() << std::endl << std::endl;
        std::cout << problem.to_string_oneline() << std::endl << std::endl;
        file << problem.to_string_oneline() << std::endl;
    }

    file.close();

    return 0;
}



// int main(int, char **)
// {
//     int hand_size = 14;

//     Problem problem;
//     problem.id = 0;
//     problem.round = Tile::Ton;
//     problem.seat = Tile::Ton;
//     problem.turn = 1;
//     problem.shanten = -1;
//     problem.wall = random_wall();
//     problem.dora = draw_dora(problem.wall);
//     problem.hand = draw_hand(problem.wall);
//     problem.ev = std::vector<double>(hand_size, 0);
//     problem.ukeire = std::vector<int>(hand_size, 0);
//     problem.shanten_down = std::vector<bool>(hand_size, false);

//     int syanten_type = SyantenType::Normal;
//     int flag = ExpectedValueCalculator::CalcSyantenDown   
//                | ExpectedValueCalculator::CalcTegawari    
//                | ExpectedValueCalculator::CalcDoubleReach 
//                | ExpectedValueCalculator::CalcIppatu      
//                | ExpectedValueCalculator::CalcHaiteitumo  
//                | ExpectedValueCalculator::CalcUradora     
//                | ExpectedValueCalculator::CalcAkaTileTumo;

//     ExpectedValueCalculator exp_value_calculator;
//     ScoreCalculator score_calculator;

//     score_calculator.set_bakaze(problem.round);
//     score_calculator.set_zikaze(problem.seat);
//     score_calculator.set_dora_indicators(std::vector<int>{problem.dora});

//     for (int turn = 1; turn < 18; turn++)
//     {
//         problem.turn = turn; 
        
//         auto [_, syanten] = SyantenCalculator::calc(Hand(problem.hand), syanten_type);
//         problem.shanten = syanten;

        
//         if (syanten > 1)
//         {
//             std::vector<int> useless = UnnecessaryTileSelector::select_normal(Hand(problem.hand));
//             discard_tile(useless.back(), problem.hand);
//             draw_from_wall(problem.hand, problem.wall);

//             std::cout << Hand(problem.hand).to_string() << " " << problem.hand.size() << " " << useless.size() << std::endl;

//         }
//         else
//         {
//             std::cout << "SKIP" << std::endl;
//         }
        

        

//         // std::vector<int> uke = RequiredTileSelector::select_normal(Hand(problem.hand));
//         // for (int i = 0; i < uke.size(); i++)
//         // {
//         //     std::cout << uke.at(i) << " ";
//         // }
//         // std::cout << std::endl;
        


//         // auto [success, candidates] = exp_value_calculator.calc(Hand(problem.hand), score_calculator,
//         //     std::vector<int>{problem.dora}, syanten_type, flag);

//         // bool exp_value_calculated = !candidates[0].tenpai_probs.empty();
//         // if (exp_value_calculated)
//         // {
//         //     for (int i = 0; i < candidates.size(); i++)
//         //     {
//         //         std::cout << candidates.at(i).tile
//         //                 << " " << candidates.at(i).exp_values.at(turn-1)
//         //                 << std::endl;
//         //     }
//         // }
        

        

//         //////////////////////////////////////////////////////////

//         // std::cout << problem.to_string() << std::endl << std::endl; 
//     }
    







//     // auto [_, syanten] = SyantenCalculator::calc(Hand(problem.hand), syanten_type);
//     // problem.shanten = syanten;

//     // auto [success, candidates] =
//     //     exp_value_calculator.calc(Hand(problem.hand), score_calculator,
//     //     std::vector<int>{problem.dora}, syanten_type, flag);

//     // int turn = problem.turn;
//     // bool exp_value_calculated = !candidates[0].tenpai_probs.empty();
//     // if (exp_value_calculated)
//     //     std::sort(candidates.begin(), candidates.end(),
//     //               [turn](const Candidate &a, const Candidate &b) {
//     //                   return a.exp_values[turn - 1] > b.exp_values[turn - 1];
//     //               });



//     // for (int i = 0; i < candidates.size(); i++)
//     // {
//     //     std::cout << candidates.at(i).tile
//     //               << " " << candidates.at(i).exp_values.at(problem.turn-1)
//     //               << std::endl;
//     // }
    


//     // std::vector<int> vekki;
//     // vekki = std::vector<int>(10,1);


//     // int id;
//     // int round;
//     // int seat;
//     // int turn;
//     // int dora;
//     // Tiles hand;
//     // std::vector<int> ev;
//     // std::vector<int> ukeire;
//     // std::vector<int> shanten;


    
//     // int dora = draw_dora(wall);
//     // Tiles hand = draw_hand(wall);

//     // std::cout << "Wall: ";
//     // for (auto i : wall)
//     // {
//     //     std::cout << i << " ";
//     // }
//     // std::cout << std::endl;

//     // std::cout << "Hand: ";
//     // for (auto i : hand)
//     // {
//     //     std::cout << i << " ";
//     // }
//     // std::cout << std::endl;
//     // std::cout << Hand(hand).to_string() << std::endl;

//     // Hand h(hand);
    
    

// }
