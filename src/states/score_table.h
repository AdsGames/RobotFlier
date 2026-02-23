/**
 * Score Table
 * Allan Legemaate
 * 26/10/2017
 * Easy highscore management
 **/

#pragma once

#include <array>
#include <string>

class ScoreTable {
public:
    ScoreTable();
    explicit ScoreTable(const std::string& path);

    void add(const std::string& name, int score);

    int getScore(int index) const;
    std::string getName(int index) const;

private:
    static const char TABLE_SIZE = 10;

    std::string path;
    std::string default_table;

    bool create();
    bool read();
    bool write();

    std::array<std::string, TABLE_SIZE> names;
    std::array<int, TABLE_SIZE> scores;
};
