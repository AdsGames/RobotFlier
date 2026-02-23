#include "init.h"

// Construct state
void InitScene::init()
{
    // Title
    asw::display::set_title("A.D.S. Games - Robot Flier");

    // Icon
    asw::display::set_icon("assets/icon.ico");

    // Loads fonts
    orbitron_12 = asw::assets::load_font("assets/fonts/orbitron_ttf.ttf", 12);
    orbitron_18 = asw::assets::load_font("assets/fonts/orbitron_ttf.ttf", 18);
    orbitron_24 = asw::assets::load_font("assets/fonts/orbitron_ttf.ttf", 24);
    orbitron_30 = asw::assets::load_font("assets/fonts/orbitron_ttf.ttf", 30);
    orbitron_36 = asw::assets::load_font("assets/fonts/orbitron_ttf.ttf", 36);
}
