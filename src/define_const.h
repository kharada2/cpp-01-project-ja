#include <string>

#ifndef DEF_H_CONST
#define DEF_H_CONST

#define FUEL_MAX 20
#define FUEL_CHARGE 20
#define START_TIME 70
#define FUEL_CHARGE_MAX 2
#define SPEED_MAX 3
#define SPEED_HIGHWAY 2
#define SPEED_NORMAL 1
#define SPEED_MIN 0
#define PENALTY_SPEED_OVER 5
#define DISPLAY_RANGE 3
#define SHOW_POSSIBILITY 0.1  //%
#define SHOW_STOP 0.6         //%
const std::string DIAPLAY_EMPTY("\033[42m   \033[0m");
const std::string DIAPLAY_ROAD("\033[47m   \033[0m");
const std::string DIAPLAY_EGO_CAR("\033[47m\034 ▲ \033[0m");
const std::string DIAPLAY_GAS_STATION("\033[47m\033[1m F \033[0m");
const std::string DIAPLAY_HIGHWAY("\033[47m ◇ \033[0m");
const std::string DIAPLAY_GOAL("\033[47m G \033[0m");
const std::string DIAPLAY_CONVINI("\033[47m C \033[0m");

#endif
