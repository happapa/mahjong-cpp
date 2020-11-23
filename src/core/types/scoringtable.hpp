#ifndef MAHJONG_CPP_SCOREBOARD
#define MAHJONG_CPP_SCOREBOARD

#include <vector>

namespace mahjong {

struct ScoringTable {

    /**
     * @brief 子が親にロンされたときに支払う点数
     */
    // clang-format off
    static const inline std::vector<std::vector<int>> Ko2OyaRon = {
    //    1翻    2翻    3翻    4翻
        {   0,     0,     0,     0}, // 20符 (20符は平和自摸なのでロンの場合はない)
        {   0,  2400,  4800,  9600}, // 25符 (七対子は最低2翻以上)
        {1500,  2900,  5800, 11600}, // 30符
        {2000,  3900,  7700,     0}, // 40符
        {2400,  4800,  9600,     0}, // 50符
        {2900,  5800, 11600,     0}, // 60符
        {3400,  6800,     0,     0}, // 70符
        {3900,  7700,     0,     0}, // 80符
        {4400,  8700,     0,     0}, // 90符
        {4800,  9600,     0,     0}, // 100符
        {5300, 10600,     0,     0}, // 110符
    };
    // clang-format on

    /**
     * @brief 親が子にロンされたときに支払う点数
     */
    // clang-format off
    static const inline std::vector<std::vector<int>> Oya2KoRon = {
    //    1翻   2翻   3翻   4翻
        {   0,    0,    0,    0}, // 20符 (20符は平和自摸なのでロンの場合はない)
        {   0, 1600, 3200, 6400}, // 25符 (七対子は最低2翻以上)
        {1000, 2000, 3900, 7700}, // 30符
        {1300, 2600, 5200,    0}, // 40符
        {1600, 3200, 6400,    0}, // 50符
        {2000, 3900, 7700,    0}, // 60符
        {2300, 4500,    0,    0}, // 70符
        {2600, 5200,    0,    0}, // 80符
        {2900, 5800,    0,    0}, // 90符
        {3200, 6400,    0,    0}, // 100符
        {3600, 7100,    0,    0}, // 110符
    };
    // clang-format on

    /**
     * @brief 子が親に自摸されたときに支払う点数
     */
    // clang-format off
    static const inline std::vector<std::vector<int>> Ko2OyaTumo = {
    //    1翻   2翻   3翻   4翻
        {   0,  700, 1300, 2600}, // 20符 (平和、門前清自摸和は最低2翻以上)
        {   0,    0, 1600, 3200}, // 25符 (七対子、門前清自摸和は最低3翻以上)
        { 500, 1000, 2000, 3900}, // 30符
        { 700, 1300, 2600,    0}, // 40符
        { 800, 1600, 3200,    0}, // 50符
        {1000, 2000, 3900,    0}, // 60符
        {1200, 2300,    0,    0}, // 70符
        {1300, 2600,    0,    0}, // 80符
        {1500, 2900,    0,    0}, // 90符
        {1600, 3200,    0,    0}, // 100符
        {1800, 3600,    0,    0}, // 110符
    };
    // clang-format on

    /**
     * @brief 親が子に自摸されたときに支払う点数
     */
    // clang-format off
    static const inline std::vector<std::vector<int>> Oya2KoTumo = {
    //    1翻   2翻   3翻   4翻
        {   0,  700, 1300, 2600}, // 20符 (平和、門前清自摸和は最低2翻以上)
        {   0,    0, 1600, 3200}, // 25符 (七対子、門前清自摸和は最低3翻以上)
        { 500, 1000, 2000, 3900}, // 30符
        { 700, 1300, 2600,    0}, // 40符
        { 800, 1600, 3200,    0}, // 50符
        {1000, 2000, 3900,    0}, // 60符
        {1200, 2300,    0,    0}, // 70符
        {1300, 2600,    0,    0}, // 80符
        {1500, 2900,    0,    0}, // 90符
        {1600, 3200,    0,    0}, // 100符
        {1800, 3600,    0,    0}, // 110符
    };
    // clang-format on

    /**
     * @brief 子が子に自摸されたときに支払う点数 (満貫以上)
     */
    // clang-format off
    static const inline std::vector<std::vector<int>> Ko2KoTumo = {
    //    1翻   2翻   3翻   4翻
        {  0,  400,  700, 1300}, // 20符 (平和、門前清自摸和は最低2翻以上)
        {  0,    0,  800, 1600}, // 25符 (七対子、門前清自摸和は最低3翻以上)
        {300,  500, 1000, 2000}, // 30符
        {400,  700, 1300,    0}, // 40符
        {400,  800, 1600,    0}, // 50符
        {500, 1000, 2000,    0}, // 60符
        {600, 1200,    0,    0}, // 70符
        {700, 1300,    0,    0}, // 80符
        {800, 1500,    0,    0}, // 90符
        {800, 1600,    0,    0}, // 100符
        {900, 1800,    0,    0}, // 110符
    };
    // clang-format on

    /**
     * @brief 子が親にロンされたときに支払う点数 (満貫以上)
     */
    static const inline std::vector<int> Ko2OyaRonOverMangan = {
        12000,  // 満貫
        18000,  // 跳満
        24000,  // 倍満
        36000,  // 三倍満
        48000,  // 数え役満
        48000,  // 役満
        96000,  // ダブル役満
        144000, // トリプル役満
        192000, // 四倍役満
        240000, // 五倍役満
        288000, // 六倍役満
    };

    /**
     * @brief 親が子にロンされたときに支払う点数 (満貫以上)
     */
    static const inline std::vector<int> Oya2KoRonOverMangan = {
        8000,   // 満貫
        12000,  // 跳満
        16000,  // 倍満
        24000,  // 三倍満
        32000,  // 数え役満
        32000,  // 役満
        64000,  // ダブル役満
        96000,  // トリプル役満
        128000, // 四倍役満
        160000, // 五倍役満
        192000, // 六倍役満
    };

    /**
     * @brief 子が親に自摸されたときに支払う点数 (満貫以上)
     */
    static const inline std::vector<int> Ko2OyaTumoOverMangan = {
        4000,  // 満貫
        6000,  // 跳満
        8000,  // 倍満
        12000, // 三倍満
        16000, // 数え役満
        16000, // 役満
        32000, // ダブル役満
        48000, // トリプル役満
        64000, // 四倍役満
        80000, // 五倍役満
        96000, // 六倍役満
    };

    /**
     * @brief 親が子に自摸されたときに支払う点数 (満貫以上)
     */
    static const inline std::vector<int> Oya2KoTumoOverMangan = {
        4000,  // 満貫
        6000,  // 跳満
        8000,  // 倍満
        12000, // 三倍満
        16000, // 数え役満
        16000, // 役満
        32000, // ダブル役満
        48000, // トリプル役満
        64000, // 四倍役満
        80000, // 五倍役満
        96000, // 六倍役満
    };

    /**
     * @brief 子が子に自摸されたときに支払う点数
     */
    static const inline std::vector<int> Ko2KoTumoOverMangan = {
        2000,  // 満貫
        3000,  // 跳満
        4000,  // 倍満
        6000,  // 三倍満
        8000,  // 数え役満
        8000,  // 役満
        16000, // ダブル役満
        24000, // トリプル役満
        32000, // 四倍役満
        40000, // 五倍役満
        48000, // 六倍役満
    };
};
} // namespace mahjong

#endif /* MAHJONG_CPP_SCOREBOARD */