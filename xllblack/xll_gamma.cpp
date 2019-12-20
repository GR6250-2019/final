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
	.Arg(XLL_DOUBLE, L"f", L"is the forward.", L"100")
	.Arg(XLL_DOUBLE, L"sigma", L"is the volatility.", L"0.2")
	.Arg(XLL_DOUBLE, L"k", L"is the strike.", L"100")
	.Arg(XLL_DOUBLE, L"t", L"is the time in years to expiration.", L"0.25")
	.Category(L"XLL")
	.FunctionHelp(L"Return Gamma put value.")
	.Documentation(
		L"The value of a Black put option is E[max{k - F, 0}]. "
		L"The expected value is k P(F " le_ " k) - f P_(F " le_ " k), "
		L"where dP_/dP = exp(sigma B_t - sigma^2 t/2). ")
);
double WINAPI xll_gamma_put(double f, double sigma, double k, double t)
{
#pragma XLLEXPORT
	double result = std::numeric_limits<double>::quiet_NaN();

	try {
		result = fms::gamma::put(f, sigma, k, t);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return result;
}
#ifdef _DEBUG

test test_gamma_put([]() {

	ensure(double(round(xll_gamma_put(100, 0.2, 100, 0.25) * 1000) / 1000) == 3.996);

	});

#endif 