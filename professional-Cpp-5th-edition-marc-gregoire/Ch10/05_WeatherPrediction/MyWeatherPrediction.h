/*
 * Chapter 10 - MyWeatherPrediction (derived class)
 *
 * Adds Celsius support and a more user-friendly `showResult()` on top of the
 * Fahrenheit-only WeatherPrediction. This is the classic shape of "extend
 * without modifying": the base header stays untouched, all new behavior lives
 * here.
 *
 * Key notes:
 *   - `showResult()` and `getTemperature()` are marked `override` so the
 *     compiler verifies they match the base signature (including `const`).
 *   - `convertCelsiusToFahrenheit` and the reverse are `static` and `private`
 *     - pure helpers with no per-object state, used only inside this class.
 *   - `getTemperature()` calls `WeatherPrediction::getTemperature()` to reuse
 *     the base implementation and just append the degree symbol. That keeps
 *     the override thin and avoids duplicating the base logic.
 */
#pragma once

#include "WeatherPrediction.h"
#include <string>

class MyWeatherPrediction : public WeatherPrediction
{
public:
	virtual void setCurrentTempCelsius(int temp);

	virtual int getTomorrowTempCelsius() const;

	void showResult() const override;

	std::string getTemperature() const override;

private:
	static int convertCelsiusToFahrenheit(int celsius);
	static int convertFahrenheitToCelsius(int fahrenheit);
};
