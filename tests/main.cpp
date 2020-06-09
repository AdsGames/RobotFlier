#define CATCH_CONFIG_MAIN

#include <string>

#include "../src/engine/Settings/SettingManager.h"
#include "catch2/catch.hpp"

SettingManager settings = SettingManager("./data/settings.dat");

TEST_CASE("Load booleans", "[single-file]") {
  REQUIRE(settings.get<bool>("bool1", false) == true);
  REQUIRE(settings.get<bool>("bool2", true) == false);
}

TEST_CASE("Load integers", "[single-file]") {
  REQUIRE(settings.get<int>("int1", 0) == 1);
  REQUIRE(settings.get<int>("int2", 0) == 93458345);
}

TEST_CASE("Load strings", "[single-file]") {
  REQUIRE(settings.get<std::string>("testStr1", "") == "trueStr");
}

TEST_CASE("Load booleans", "[single-file]") {
  REQUIRE(settings.get<float>("testFloat1", 0.0f) == 0.01f);
  REQUIRE(settings.get<float>("testFloat2", 0.0f) == 0.00002f);
}