/*
 * Chapter 10 - WeatherPrediction (base interface)
 *
 * A toy base class used through the chapter to demonstrate "inheriting to
 * change behavior". WeatherPrediction works in Fahrenheit; MyWeatherPrediction
 * (next file) extends it to support Celsius without touching this header.
 *
 * Key notes:
 *   - Every function intended to be overridden is `virtual`, including the
 *     destructor.
 *   - The class is openly substitutable - any subclass can replace any member
 *     function and the rest of the class keeps working through the vtable.
 *   - Predictions themselves are nonsense; the point is the inheritance shape,
 *     not the weather model.
 */
#pragma once

#include <string>

// Predicts the weather using proven new-age techniques given the current
// temperature and the distance from Jupiter to Mars. If these values are
// not provided, a guess is still given but it's only 99% accurate.
class WeatherPrediction
{
public:
	// Virtual destructor - required for any polymorphic base.
	virtual ~WeatherPrediction();

	// Sets the current temperature in Fahrenheit
	virtual void setCurrentTempFahrenheit(int temp);

	// Sets the current distance between Jupiter and Mars
	virtual void setPositionOfJupiter(int distanceFromMars);

	// Gets the prediction for tomorrow's temperature
	virtual int getTomorrowTempFahrenheit() const;

	// Gets the probability of rain tomorrow. 1 means
	// definite rain. 0 means no chance of rain.
	virtual double getChanceOfRain() const;

	// Displays the result to the user in this format:
	// Result: x.xx chance. Temp. xx
	virtual void showResult() const;

	// Returns a string representation of the temperature
	virtual std::string getTemperature() const;

private:
	int m_currentTempFahrenheit{ 0 };
	int m_distanceFromMars{ 0 };
};
