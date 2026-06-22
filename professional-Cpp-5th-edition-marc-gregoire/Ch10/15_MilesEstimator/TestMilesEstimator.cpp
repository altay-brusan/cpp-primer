/*
 * Chapter 10 - MilesEstimator driver
 *
 * Same call (`getMilesLeft`) on both objects, but the answers differ because
 * the inner virtual hook resolves to different mpg values. This is the value
 * of the template-method / NVI pattern: callers don't change, behavior does.
 */
#include "MilesEstimator.h"
#include "EfficientCarMilesEstimator.h"
#include <print>

using namespace std;

int main()
{
	MilesEstimator myMilesEstimator;
	myMilesEstimator.setGallonsLeft(2);
	println("Normal estimator can go {} more miles.",
		myMilesEstimator.getMilesLeft());     // 20 * 2 = 40

	EfficientCarMilesEstimator myEstimator;
	myEstimator.setGallonsLeft(2);
	println("Efficient estimator can go {} more miles.",
		myEstimator.getMilesLeft());          // 35 * 2 = 70
}
