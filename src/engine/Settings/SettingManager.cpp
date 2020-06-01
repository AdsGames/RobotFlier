#include "SettingManager.h"

#include <algorithm>
#include <exception>
#include <fstream>

#include "../../helpers/stringFns.h"

struct FileIOException : public std::exception {
  const char* what() const throw() { return "File I/O Exception"; }
};

// Constructor
SettingManager::SettingManager() {}

SettingManager::SettingManager(const std::string file) {
  load(file);
}

// Load file
void SettingManager::load(const std::string file) {
  std::string line;
  std::ifstream fileStream(file);

  if (!fileStream.is_open()) {
    throw FileIOException();
  }

  if (fileStream.is_open()) {
    while (getline(fileStream, line)) {
      // Split string
      int delimLoc = line.find("=");
      if (delimLoc == -1) {
        continue;
      }

      // Get values
      std::string key = line.substr(0, delimLoc);
      std::string value = line.substr(delimLoc + 1, line.length());

      // Conversion
      if (stringFns::isBoolean(value)) {
        set(key, stringFns::toBoolean(value));
      } else if (stringFns::isInteger(value)) {
        set(key, stringFns::toInteger(value));
      } else if (stringFns::isFloat(value)) {
        set(key, stringFns::toFloat(value));
      } else {
        set(key, value);
      }
    }
    fileStream.close();
  }
}

// Setters
void SettingManager::set(const std::string key, SettingType value) {
  set({key, value});
}

void SettingManager::set(const Setting pair) {
  settings[pair.first] = pair.second;
}

// Setting exists
bool SettingManager::settingExists(const std::string key) const {
  auto it = std::find_if(
      settings.begin(), settings.end(),
      [key](const Setting& setting) { return setting.first == key; });
  return it != settings.end();
}

// Find
const Setting SettingManager::findSetting(const std::string key) const {
  auto it = std::find_if(
      settings.begin(), settings.end(),
      [key](const Setting& setting) { return setting.first == key; });

  if (it != settings.end()) {
    return *it;
  }

  return {"", ""};
}