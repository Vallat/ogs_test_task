#pragma once


const std::string WINDOW_NAME = "test task";
const unsigned int WINDOW_HEIGHT = 600;
const unsigned int WINDOW_WIDTH = 900;

const size_t LINES_AMOUNT = 3;
const size_t ROWS_AMOUNT = 3;
const unsigned int  ROW_HEIGHT = 500;
const unsigned int  ROW_WIDTH = 100;

const std::string SYMBOLS_TEXTURES[] = { "resources/shape_1.png", "resources/shape_2.png" , "resources/shape_3.png" , "resources/shape_4.png" , "resources/shape_5.png" };
constexpr size_t SYMBOLS_AMOUNT = _countof(SYMBOLS_TEXTURES);
const sf::Vector2f SPRITES_SCALE = sf::Vector2f(4.f, 4.f);


const float SPIN_SPEED = 6.0f;
const float ACCELERATION_MULTIPLIER = 0.1f;
const float SLOWDOWN_MULTIPLIER = 0.1f;
const float START_SPIN_SPEED_MULTIPLIER = 0.2f;
const size_t SPINS_BOTTOM_LIMIT = 20;
const size_t SPINS_UPPER_LIMIT = 25;
const size_t MIN_SPINS_BEFORE_STOP = 5;

const size_t BASE_VALUE_MULTIPLIER = 10;
const size_t THREE_IN_LINE_MULTIPLIER = 10;
const size_t TWO_IN_LINE_MULTIPLIER = 3;

const size_t SECONDS_TO_DISPLAY_RESULT = 10;


const float START_BUTTON_POSITION_X = WINDOW_WIDTH * 0.75f;
const float START_BUTTON_POSITION_Y = WINDOW_HEIGHT * 0.3f;
