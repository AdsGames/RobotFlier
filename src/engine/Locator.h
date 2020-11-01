#ifndef ENGINE_LOCATOR_H
#define ENGINE_LOCATOR_H

#include <memory>

#include "assets/AssetManager.h"
#include "audio/AudioService.h"
#include "display/Window.h"
#include "settings/SettingManager.h"

class Locator {
 public:
  // Provide instance of audio service
  template <class T, class... Args>
  static void provideAudio(Args&&... args) {
    std::unique_ptr<AudioService> service =
        std::make_unique<T>(T(std::forward<Args>(args)...));
    audio_service = std::move(service);
  }

  // Provide instance of asset manager
  template <class T, class... Args>
  static void provideAssetManager(Args&&... args) {
    std::unique_ptr<AssetManager> service =
        std::make_unique<T>(T(std::forward<Args>(args)...));
    asset_service = std::move(service);
  }

  // Provide instance of window
  template <class T, class... Args>
  static void provideWindow(Args&&... args) {
    std::unique_ptr<Window> service =
        std::make_unique<T>(T(std::forward<Args>(args)...));
    window_service = std::move(service);
  }

  // Provide instance of settings
  template <class T, class... Args>
  static void provideSettings(Args&&... args) {
    std::unique_ptr<SettingManager> service =
        std::make_unique<T>(T(std::forward<Args>(args)...));
    setting_service = std::move(service);
  }

  // Get audio service
  static AudioService& getAudio();

  // Get asset service
  static AssetManager& getAsset();

  // Get window
  static Window& getWindow();

  // Get settings
  static SettingManager& getSettings();

 private:
  static inline std::unique_ptr<AudioService> audio_service;
  static inline std::unique_ptr<AssetManager> asset_service;
  static inline std::unique_ptr<Window> window_service;
  static inline std::unique_ptr<SettingManager> setting_service;
};

#endif  // ENGINE_LOCATOR_H