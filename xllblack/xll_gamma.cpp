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
	Function(XLL_DOUBLE, L"?xll_gamma_put", L"XLL.GAMMA.PUT")
	.Arg(XLL_DOUBLE, L"f", L"is the current price. ")
	.Arg(XLL_DOUBLE, L"sigma", L"is the volatility. ")
	.Arg(XLL_DOUBLE, L"k", L"is the strike price. ")
	.Arg(XLL_DOUBLE, L"t", L"is the time remaining. ")
	.Category(L"XLL")
	.FunctionHelp(L"Returns the price of a put option.")
	.Documentation(
		L"Contrary to the conventional Black-Scholes-Merton equation, "
		L"this pricing function assumes the underlying asset follows a Gamma distribution. "
		L"The function's inputs are the current price, the volatility, the strike price, and the maturity, "
		L"and calculates E[max(K-F,0)]. "
		L"The output is the price of a European put option."
	)
);

double WINAPI xll_gamma_put(double f, double sigma, double k, double t)
{
#pragma XLLEXPORT

	double put = fms::gamma::put(f, sigma, k, t);
	ensure(put >= 0)

	return put;
}