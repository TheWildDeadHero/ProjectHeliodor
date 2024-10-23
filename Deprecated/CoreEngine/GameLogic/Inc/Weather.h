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

#ifndef GUARD_WEATHER_H
#define GUARD_WEATHER_H

#include <stdint.h>

/**
 * @brief 
 * 
 */
namespace WeatherData
{
    /**
     * @brief Enumerator for precipiation type for battles and overworld behavior.
     * 
     */
    enum class PrecipitationType
    {
        CLEAR,              /**< No precipitation           */
        RAIN,               /**< Rain                       */
        SNOW,               /**< Snow                       */
        FOG,                /**< Fog/Mist                   */
        SAND,               /**< Sandstorm                  */
        HAIL,               /**< Hail/Falling Ice           */
        ASH,                /**< Falling ash from volcano   */
        ACID_RAIN,          /**< Acid rain                  */

        NUM_PRECIPITATIONS  /**< Precipitation Counter */
    };

    /**
     * @brief 
     * 
     */
    enum class WindType
    {
        CALM,               /**< */
        LIGHT,              /**< */
        MEDIUM,             /**< */
        GALE,               /**< */

        NUM_WINDS           /**< */
    };

    /**
     * @brief 
     * 
     */
    enum class SkyType
    {
        CLEAR,              /**< */
        CLOUDY,             /**< */
        LIGHTNING,          /**< */
        RAINBOW,            /**< */
        BRIGHT,             /**< */
        STAR_SHOWER,        /**< */

        NUM_SKIES           /**< */
    };

    /**
     * @brief 
     * 
     */
    enum class TemperatureType
    {
        FREEZING,           /**< */
        COLD,               /**< */
        NORMAL,             /**< */
        WARM,               /**< */
        HOT,                /**< */
        SPACE,              /**< */

        NUM_TEMPERATURES    /**< */
    };
};

/**
 * @brief 
 * 
 */
struct WeatherType
{
    WeatherData::PrecipitationType precipitation_;  /**< */
    WeatherData::WindType          wind_;           /**< */
    WeatherData::SkyType           sky_;            /**< */
    WeatherData::TemperatureType   temperature_;    /**< */
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

const WeatherType CLEAR_WEATHER = { WeatherData::PrecipitationType::CLEAR,
                                    WeatherData::WindType::CALM,
                                    WeatherData::SkyType::CLEAR,
                                    WeatherData::TemperatureType::NORMAL };


#endif // GUARD_WEATHER_H