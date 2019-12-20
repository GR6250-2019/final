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

AddIn xai_gamma_put(
	Function(XLL_DOUBLE, L"?xll_gamma_put", CATEGORY L".GAMMA.PUT")
	.Arg(XLL_DOUBLE, L"f", L"is the spot price. ")
	.Arg(XLL_DOUBLE, L"sigma", L"is the volatility. ")
	.Arg(XLL_DOUBLE, L"k", L"is the strike. ")
	.Arg(XLL_DOUBLE, L"t", L"is the time in years to maturity. ")
	.Category(L"XLL")
	.FunctionHelp(L"Return the value of a put option.")
	.Documentation(L"Return the value of a put option." )
);
double WINAPI xll_gamma_put(double f, double sigma, double k, double t)
{
#pragma XLLEXPORT

	return gamma::put(f, sigma, k, t);
}
