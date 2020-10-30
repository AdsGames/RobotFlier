#define CATCH_CONFIG_MAIN

#include <string>

#include "../engine/settings/SettingManager.h"
#include "catch2/catch.hpp"

SettingManager settingsTest = SettingManager();

TEST_CASE("Load booleans", "[single-file]") {
  settingsTest.load("./data/settings.dat");
  REQUIRE(settingsTest.get<bool>("bool1", false) == true);
  REQUIRE(settingsTest.get<bool>("bool2", true) == false);
}

TEST_CASE("Load integers", "[single-file]") {
  REQUIRE(settingsTest.get<int>("int1", 0) == 1);
  REQUIRE(settingsTest.get<int>("int2", 0) == 93458345);
}

TEST_CASE("Load strings", "[single-file]") {
  REQUIRE(settingsTest.get<std::string>("testStr1", "") == "trueStr");
}

TEST_CASE("Load floats", "[single-file]") {
  REQUIRE(settingsTest.get<float>("testFloat1", 0.0f) == 0.01f);
  REQUIRE(settingsTest.get<float>("testFloat2", 0.0f) == 0.00002f);
}