#include "ScoreTable.h"

#include <fstream>

// Default CTOR
ScoreTable::ScoreTable() : ScoreTable("scores.dat") {}

// Pass file to CTOR
ScoreTable::ScoreTable(const std::string& path)
    : path(path),
      default_table(
          "Allan\n600\nDanward\n500\nL.K."
          "\n400\nDudefaceIII\n300\nJohnny\n200\nSlimeKnight\n175\nBilly\n150\n"
          "Jimothy\n125\nCarter\n100\nAndrew\n10") {
  for (int i = 0; i < TABLE_SIZE; i++)
    scores[i] = 0;

  if (!read()) {
    create();
    read();
  }
}

// Create table
bool ScoreTable::create() {
  std::ofstream w(path);

  if (!w) {
    w.close();
    return false;
  }

  w << default_table;
  w.close();

  return true;
}

// Read High Scores
bool ScoreTable::read() {
  std::ifstream r(path);

  if (!r) {
    r.close();
    return false;
  }

  for (int i = 0; i < TABLE_SIZE; i++) {
    r >> names[i];
    r >> scores[i];
  }

  r.close();

  return true;
}

// Save Scores
bool ScoreTable::write() {
  std::ofstream w(path);

  if (!w) {
    w.close();
    return false;
  }

  for (int i = 0; i < TABLE_SIZE; i++) {
    w << names[i] << "\n" << scores[i] << "\n";
  }

  w.close();

  return true;
}

// Add score
void ScoreTable::add(const std::string& name, int score) {
  // Update List
  for (int i = 0; i < TABLE_SIZE; i++) {
    if (score > scores[i]) {
      for (int t = 9; t > i; t--) {
        scores[t] = scores[t - 1];
        names[t] = names[t - 1];
      }

      scores[i] = score;
      names[i] = name;

      if (name == "") {
        names[i] = "Player";
      }

      break;
    }
  }

  // Save
  write();
}

// Get names
int ScoreTable::getScore(int index) const {
  return (index >= 0 && index < TABLE_SIZE) ? scores[index] : 0;
}

// Get scores
std::string ScoreTable::getName(int index) const {
  return (index >= 0 && index < TABLE_SIZE) ? names[index] : "";
}
