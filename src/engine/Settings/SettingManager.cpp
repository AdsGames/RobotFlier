#include "SettingManager.h"

#include <algorithm>
#include <exception>
#include <fstream>

#include "../../helpers/stringFns.h"

struct FileIOException : public std::exception {
  const char* what() const throw() { return "File I/O Exception"; }
};

// Load file
void SettingManager::load(const std::string file) {
  std::string line;
  std::ifstream fileStream(file);

  if (!fileStream.is_open()) {
    throw FileIOException();
  }

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
      settings[key] = stringFns::toBoolean(value);
    } else if (stringFns::isInteger(value)) {
      settings[key] = stringFns::toInteger(value);
    } else if (stringFns::isFloat(value)) {
      settings[key] = stringFns::toFloat(value);
    } else {
      settings[key] = value;
    }
  }

  fileStream.close();

  // Set internal file name
  file_name = file;
}

// Save file
void SettingManager::save() {
  save(file_name);
}

void SettingManager::save(const std::string file) {
  std::ofstream fileStream(file);
  std::string line = "";

  if (!fileStream.is_open()) {
    throw FileIOException();
  }

  for (auto const& [key, value] : this->settings) {
    fileStream << key + "=";
    fileStream << getString(key);
    fileStream << "\n";
  }

  fileStream.close();
}

// Setters
void SettingManager::set(const std::string key, SettingType value) {
  set({key, value});
}

void SettingManager::set(const Setting pair) {
  settings[pair.first] = pair.second;

  if (autosave) {
    save();
  }
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

  throw std::runtime_error("Could not find setting " + key);
}

// Set autosave
void SettingManager::setAutosave(const bool autosave) {
  this->autosave = autosave;
}