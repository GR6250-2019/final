// xll_gamma.cpp - Gamma distribution.
#include "fms_gamma.h"
#include "xll_black.h"

using namespace fms;
using namespace xll;

test test_gamma([] {
	
	ensure(::gamma(1) == 1);
	ensure(::gamma(2) == 1);
	ensure(::gamma(3) == 2);
	
	double a = 2, b = 3;
	double x, y;
	x = 1;
	y = gamma::pdf(x, a, b);
	y = gamma::cdf(x, a, b);

});

//!!! Implement XLL.GAMMA.PUT

static AddIn xai_gamma_put(
	Function(XLL_DOUBLE, L"?xll_gamma_put", L"XLL.GAMMA.PUT")
	.Arg(XLL_DOUBLE, L"f", L"is the current price of the underlying asset.")
	.Arg(XLL_DOUBLE, L"sigma", L"is the volatility of the asset.")
	.Arg(XLL_DOUBLE, L"k", L"is the strike price.")
	.Arg(XLL_DOUBLE, L"t", L"is the remaining time to maturity.")
	.Category(CATEGORY)
	.FunctionHelp(L"Return the value of the gamma payoff.")
	.Documentation(
		L"This function computes the payoff of a put option using the gamma distribuiton."
	)
);
double WINAPI xll_gamma_put(double f, double sigma, double k, double t)
{
#pragma XLLEXPORT
	double result = std::numeric_limits<double>::quiet_NaN();

	try {
		result = gamma::put(f, sigma, k, t);
	}
	catch (const std::exception & ex) {
		XLL_ERROR(ex.what());
	}

	return result;
}