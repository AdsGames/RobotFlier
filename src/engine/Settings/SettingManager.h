#ifndef ENGINE_SETTINGS_SETTING_MANAGER_H
#define ENGINE_SETTINGS_SETTING_MANAGER_H

#include <map>
#include <string>
#include <variant>

typedef std::variant<std::string, int, bool, float> SettingType;
typedef std::pair<std::string, SettingType> Setting;

class SettingManager {
 public:
  // Ctor
  SettingManager();

  // File IO
  void load(const std::string& file);
  void save();
  void save(const std::string& file);

  // Getters
  template <class T>
  T get(const std::string& key, T fallback) const {
    try {
      auto pair = this->findSetting(key);
      return std::get<T>(pair.second);
    } catch (...) {
      return fallback;
    }
  }

  std::string getString(const std::string& key) const {
    auto pair = this->findSetting(key);

    switch (pair.second.index()) {
      case 0:
        return std::get<std::string>(pair.second);
      case 1:
        return std::to_string(std::get<int>(pair.second));
      case 2:
        return std::get<bool>(pair.second) ? "true" : "false";
      case 3:
        return std::to_string(std::get<float>(pair.second));
      default:
        return "";
    }
  }

  // Setters
  void set(const std::string& key, SettingType value);
  void set(const Setting pair);

  void setAutosave(const bool autosave);

 private:
  const Setting findSetting(const std::string& key) const;

  std::string file_name;
  bool autosave;

  std::variant<SettingType> test;
  std::map<std::string, SettingType> settings;
};

#endif  // ENGINE_SETTINGS_SETTING_MANAGER_H
