// xll_gamma.cpp - Gamma distribution.
#pragma once
#include "fms_gamma.h"
#include "xll_black.h"

using namespace fms;
using namespace xll;

#ifdef _DEBUG
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
#endif

//!!! Implement XLL.GAMMA.PUT
static AddIn xai_gamma_put(
	Function(XLL_DOUBLE, L"?xll_gamma_put", L"XLL.GAMMA.PUT")
	.Arg(XLL_DOUBLE, L"f", L"is the forward.", L"100")
	.Arg(XLL_DOUBLE, L"sigma", L"is the volatility.", L"0.2")
	.Arg(XLL_DOUBLE, L"k", L"is the strike.", L"100")
	.Arg(XLL_DOUBLE, L"t", L"is the time in years to expiration.", L"0.25")
	.Category(L"XLL")
	.FunctionHelp(L"Return the Gamma put value.")
	.Documentation(
		L"The value of a Gamma put option is k P(G " le_ " k) - E[F 1(G " le_ " k)]. "
		L"The expected value is k P(G " le_ " k) - f P_(G " le_ " k), "
	)
);
double WINAPI xll_gamma_put(double f, double sigma, double k, double t)
{
#pragma XLLEXPORT
	double result = std::numeric_limits<double>::quiet_NaN();

	try {
		result = gamma::put(f, sigma, k, t);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return result;
}

