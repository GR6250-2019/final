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
	.Arg(XLL_DOUBLE, L"f", L"is the forward price.", L"100")
	.Arg(XLL_DOUBLE, L"sigma", L"is the volatility.", L"0.2")
	.Arg(XLL_DOUBLE, L"k", L"is the strike price.", L"100")
	.Arg(XLL_DOUBLE, L"t", L"is the remaining time til expiration date.", L"0.25")
	.Category(L"XLL")
	.FunctionHelp(L"Return Black gamma put value.")
	.Documentation(L"This function using a Gamma distribution to compute the price of the put option.")
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
