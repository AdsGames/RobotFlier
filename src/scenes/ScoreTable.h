/**
 * Score Table
 * Allan Legemaate
 * 26/10/2017
 * Easy highscore management
 **/

#ifndef SCNES_SCORETABLE_H
#define SCNES_SCORETABLE_H

#include <string>

class ScoreTable {
 public:
  ScoreTable();
  explicit ScoreTable(const std::string& path);

  virtual ~ScoreTable(){};

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

  std::string names[TABLE_SIZE];
  int scores[TABLE_SIZE];
};

#endif  // SCNES_SCORETABLE_H
