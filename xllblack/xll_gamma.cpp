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
	.Arg(XLL_HANDLE, L"f", L"is the forward of the underlying.")
	.Arg(XLL_DOUBLE, L"sigma", L"is the volatility parameter.")
	.Arg(XLL_DOUBLE, L"k", L"is the strike of the binary option.")
	.Arg(XLL_DOUBLE, L"t", L"is the time to maturity.")
	.FunctionHelp(L"Returns the gamma payoff of put.")
	.Category(L"XLL")
	.Documentation(
	L"The function returns the gamma payoff of put."
	L"using the forward of underlying, volatility, strike price and time-to-maturity. ")
);
double WINAPI xll_gamma_put(double f, double sigma, double k, double t)
{
#pragma XLLEXPORT
	double p = std::numeric_limits<double>::quiet_NaN();

	try {
		p = fms::gamma::put(f, sigma, k, t);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return p;
}