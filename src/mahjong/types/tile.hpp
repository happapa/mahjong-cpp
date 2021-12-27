#ifndef MAHJONG_CPP_TILES
#define MAHJONG_CPP_TILES

#include <string>
#include <vector>

namespace mahjong
{

struct Tile
{
    /**
     * @brief 牌の種類
     */
    enum Type
    {
        Null = -1,
        Manzu1,    /*! 一萬 */
        Manzu2,    /*! 二萬 */
        Manzu3,    /*! 三萬 */
        Manzu4,    /*! 四萬 */
        Manzu5,    /*! 五萬 */
        Manzu6,    /*! 六萬 */
        Manzu7,    /*! 七萬 */
        Manzu8,    /*! 八萬 */
        Manzu9,    /*! 九萬 */
        Pinzu1,    /*! 一筒 */
        Pinzu2,    /*! 二筒 */
        Pinzu3,    /*! 三筒 */
        Pinzu4,    /*! 四筒 */
        Pinzu5,    /*! 五筒 */
        Pinzu6,    /*! 六筒 */
        Pinzu7,    /*! 七筒 */
        Pinzu8,    /*! 八筒 */
        Pinzu9,    /*! 九筒 */
        Sozu1,     /*! 一索 */
        Sozu2,     /*! 二索 */
        Sozu3,     /*! 三索 */
        Sozu4,     /*! 四索 */
        Sozu5,     /*! 五索 */
        Sozu6,     /*! 六索 */
        Sozu7,     /*! 七索 */
        Sozu8,     /*! 八索 */
        Sozu9,     /*! 九索 */
        Ton,       /*! 東 */
        Nan,       /*! 南 */
        Sya,       /*! 西 */
        Pe,        /*! 北 */
        Haku,      /*! 白 */
        Hatu,      /*! 発 */
        Tyun,      /*! 中 */
        AkaManzu5, /*! 赤五萬 */
        AkaPinzu5, /*! 赤五筒 */
        AkaSozu5,  /*! 赤五索 */
        Length,
    };

    static inline const std::map<int, std::string> Name = {
        {Null, "Null"},          {Manzu1, "1m"},      {Manzu2, "2m"},
        {Manzu3, "3m"},        {Manzu4, "4m"},      {Manzu5, "5m"},
        {Manzu6, "6m"},        {Manzu7, "7m"},      {Manzu8, "8m"},
        {Manzu9, "9m"},        {Pinzu1, "1p"},      {Pinzu2, "2p"},
        {Pinzu3, "3p"},        {Pinzu4, "4p"},      {Pinzu5, "5p"},
        {Pinzu6, "6p"},        {Pinzu7, "7p"},      {Pinzu8, "8p"},
        {Pinzu9, "9p"},        {Sozu1, "1s"},       {Sozu2, "2s"},
        {Sozu3, "3s"},         {Sozu4, "4s"},       {Sozu5, "5s"},
        {Sozu6, "6s"},         {Sozu7, "7s"},       {Sozu8, "8s"},
        {Sozu9, "9s"},         {Ton, "1w"},         {Nan, "2w"},
        {Sya, "3w"},           {Pe, "4w"},          {Haku, "1d"},
        {Hatu, "2d"},          {Tyun, "3d"},        {AkaManzu5, "r5m"},
        {AkaPinzu5, "r5p"}, {AkaSozu5, "r5s"}};
};

/**
 * @brief 赤なしの牌を赤牌に変換する。
 *
 * @param tile 赤牌
 * @return int 赤なしの牌
 */
inline int normal2aka(int tile)
{
    if (tile == Tile::AkaManzu5)
        return Tile::Manzu5;
    else if (tile == Tile::AkaPinzu5)
        return Tile::Pinzu5;
    else if (tile == Tile::AkaSozu5)
        return Tile::Sozu5;
    else
        return tile;
}

/**
 * @brief 赤牌を赤なしの牌に変換する。
 *
 * @param tile 赤牌
 * @return int 赤なしの牌
 */
inline int aka2normal(int tile)
{
    if (tile <= Tile::Tyun)
        return tile;
    else if (tile == Tile::AkaManzu5)
        return Tile::Manzu5;
    else if (tile == Tile::AkaPinzu5)
        return Tile::Pinzu5;
    else
        return Tile::Sozu5;
}

/**
 * @brief 赤牌かどうかを判定する。
 *
 * @param tile 牌
 * @return bool 赤牌かどうか
 */
inline bool is_akahai(int tile) { return tile >= Tile::AkaManzu5; }

/**
 * @brief 萬子かどうかを判定する。
 *
 * @param tile 牌
 * @return bool 萬子かどうか
 */
inline bool is_manzu(int tile)
{
    return (Tile::Manzu1 <= tile && tile <= Tile::Manzu9) || tile == Tile::AkaManzu5;
}

/**
 * @brief 筒子かどうかを判定する。
 *
 * @param tile 牌
 * @return bool 筒子かどうか
 */
inline bool is_pinzu(int tile)
{
    return (Tile::Pinzu1 <= tile && tile <= Tile::Pinzu9) || tile == Tile::AkaPinzu5;
}

/**
 * @brief 索子かどうかを判定する。
 *
 * @param tile 牌
 * @return bool 索子かどうか
 */
inline bool is_sozu(int tile)
{
    return (Tile::Sozu1 <= tile && tile <= Tile::Sozu9) || tile == Tile::AkaSozu5;
}

/**
 * @brief 数牌かどうかを判定する。
 *
 * @param tile 牌
 * @return bool 数牌かどうか
 */
inline bool is_syuhai(int tile) { return tile < Tile::Ton || tile > Tile::Tyun; }

/**
 * @brief 字牌かどうかを判定する。
 *
 * @param tile 牌
 * @return bool 字牌かどうか
 */
inline bool is_zihai(int tile) { return Tile::Ton <= tile && tile <= Tile::Tyun; }

} // namespace mahjong

#endif /* MAHJONG_CPP_TILES */
