/*
 * Chapter 10 - WeatherPrediction (driver)
 *
 * Exercises the derived class. Notice that calling `showResult()` and
 * `getTemperature()` on a concrete MyWeatherPrediction invokes the *Derived*
 * overrides directly. The polymorphism behavior matters when you hold one of
 * these through a `WeatherPrediction&` or pointer (not shown here).
 */
#include "MyWeatherPrediction.h"
#include <print>

using namespace std;

int main()
{
	MyWeatherPrediction p;
	p.setCurrentTempCelsius(33);
	p.setPositionOfJupiter(80);
	p.showResult();
	println("{}", p.getTemperature());
}
