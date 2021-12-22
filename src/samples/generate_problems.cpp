#include "mahjong/mahjong.hpp"

using namespace mahjong;

int main(int, char **)
{
    // calc() に手牌を指定した場合、通常手、七対子手、国士無双手の向聴数を計算し、
    // 向聴数が最小となる手の種類及び向聴数をタプルで返します。
    {
        Hand hand({Tile::Manzu1, Tile::Manzu1, Tile::Manzu1, Tile::Manzu2, Tile::AkaManzu5,
                Tile::Manzu6, Tile::Manzu7, Tile::Manzu8, Tile::Manzu9, Tile::Pinzu1,
                Tile::Pinzu1, Tile::Pinzu2, Tile::Pinzu2});

        auto [syanten_type, syanten] = SyantenCalculator::calc(hand);

        std::cout << fmt::format("手牌: {}, 向聴数の種類: {}, 向聴数: {}", hand.to_string(),
                                SyantenType::Name[syanten_type], syanten)
                << std::endl;
    }
}
