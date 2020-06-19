#ifndef ENGINE_SETTINGS_SETTING_MANAGER_H
#define ENGINE_SETTINGS_SETTING_MANAGER_H

#include <map>
#include <string>
#include <variant>

typedef std::variant<std::string, int, bool, float> SettingType;
typedef std::pair<std::string, SettingType> Setting;

class SettingManager {
 public:
  // Constructor
  SettingManager();
  SettingManager(const std::string file);
  void load(const std::string file);

  // Getters
  template <class T>
  T get(const std::string key, T fallback) const {
    auto pair = this->findSetting(key);

    try {
      return std::get<T>(pair.second);
    } catch (const std::bad_variant_access&) {
      return fallback;
    }
  }

  // Setters
  void set(const std::string key, SettingType value);
  void set(const Setting pair);

 private:
  const Setting findSetting(const std::string key) const;
  bool settingExists(const std::string key) const;

  std::variant<SettingType> test;
  std::map<std::string, SettingType> settings;
};

#endif  // ENGINE_SETTINGS_SETTING_MANAGER_H
