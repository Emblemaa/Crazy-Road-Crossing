#ifndef CONSTANTS_H
#define CONSTANTS_H

const float WINDOW_WIDTH = 1640.f;
const float WINDOW_HEIGHT = 900.f;

const float PLAY_WINDOW_WIDTH = 1340.f;
const float PLAY_WINDOW_HEIGHT = 900.f;

const float BUTTON_WIDTH = 150.f;
const float BUTTON_HEIGHT = 75.f;
const float BUTTON_GAP = BUTTON_HEIGHT + 30.f;

const float LOWEST_LANE_Y = 800.f;
const float GAP = 80.f;
const int LANE_NUMBER = 10;
const float STRIPE_THICKNESS = 5.f;

const float PLAYER_SPEED_X = 15.f;
const float PLAYER_SPEED_Y = GAP;
const float PLAYER_SIZE = 40.f;

const float OBSTACLE_SPEED = 0.15f;
const float OBSTACLE_BLOCK_HEIGHT = 20.f;

const float TRAFFIC_LIGHT_BLOCK_HEIGHT = 13.f;

const float SPAWN_SPEED = 1000.f;

const int MAX_ENEMY = 10;

#define GAMESPEED 0.5f

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "defineVariables.h"
using namespace std;

#endif