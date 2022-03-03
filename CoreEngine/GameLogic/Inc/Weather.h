/**
 * @file Weather.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdint.h>

enum class e_PrecipitationType
{
    CLEAR,
    RAIN,
    SNOW,
    FOG,
    SAND,
    HAIL,
    FALLING_ASH,
    ACID_RAIN,

    NUM_PRECIPITATIONS
};

enum class e_WindType
{
    CALM,
    LIGHT,
    MEDIUM,
    GALE,

    NUM_WINDS
};

enum class e_SkyType
{
    CLEAR,
    CLOUDY,
    DARK,
    LIGHTNING,
    RAINBOW,
    BRIGHT,

    NUM_SKIES
};

enum class e_TemperatureType
{
    FREEZING,
    COLD,
    NORMAL,
    WARM,
    HOT,
    SPACE,

    NUM_TEMPERATURES
};

struct s_WeatherType
{
    e_PrecipitationType precipitation_;
    e_WindType          wind_;
    e_SkyType           sky_;
    e_TemperatureType   temperature_;
};

/*

const _Weather normalWeather = {PRECIP_CLEAR, WIND_CALM, SKY_CLEAR, TEMP_NORMAL};

const _Weather breezy = {PRECIP_CLEAR, WIND_LIGHT, SKY_CLEAR, TEMP_NORMAL};
const _Weather gusty = {PRECIP_CLEAR, WIND_MEDIUM, SKY_CLEAR, TEMP_NORMAL};
const _Weather gale = {PRECIP_CLEAR, WIND_GALE, SKY_CLEAR, TEMP_NORMAL};

const _Weather lightRain = {PRECIP_RAIN, WIND_LIGHT, SKY_CLOUDY, TEMP_NORMAL};
const _Weather downpour = {PRECIP_RAIN, WIND_MEDIUM, SKY_DARK, TEMP_NORMAL};
const _Weather thunderstorm = {PRECIP_RAIN, WIND_MEDIUM, SKY_LIGHTNING, TEMP_NORMAL};
const _Weather tempest = {PRECIP_RAIN, WIND_GALE, SKY_LIGHTNING, TEMP_NORMAL};

const _Weather flurry = {PRECIP_SNOW, WIND_LIGHT, SKY_CLOUDY, TEMP_FREEZING};
const _Weather snow = {PRECIP_SNOW, WIND_MEDIUM, SKY_CLOUDY, TEMP_FREEZING};
const _Weather blizzard = {PRECIP_SNOW, WIND_GALE, SKY_CLOUDY, TEMP_FREEZING};
 * 
 */

const s_WeatherType CLEAR_WEATHER = { e_PrecipitationType::CLEAR,
                                      e_WindType::CALM,
                                      e_SkyType::CLEAR,
                                      e_TemperatureType::NORMAL };