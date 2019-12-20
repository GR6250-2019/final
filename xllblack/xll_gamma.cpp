// xll_gamma.cpp - Gamma distribution.
#include "fms_gamma.h"
#include "xll_black.h"

using namespace fms;
using namespace xll;

test test_gamma([] {
	
	ensure(::gamma(1) == 1);
	ensure(::gamma(2) == 1);
	ensure(::gamma(3) == 2);
	
	double A = 2, B = 1.0 / 3;
	double x, y;
	x = 1;
	y = gamma::pdf(x, A, B);
	ensure(y == 1.0 / 9 * std::exp(-1.0 / 3));
	y = gamma::cdf(x, A, B);
	ensure(fabs(y - 1.0 + 3.0 * std::exp(-1.0 / 3) * (1.0 / 9 + 1.0 / 3)) < 0.00001);
	
	
});


//!!! Implement XLL.GAMMA.PUT
static AddIn xai_black_put(
	Function(XLL_DOUBLE, L"?xll_gamma_put", L"XLL.GAMMA.PUT")
	.Arg(XLL_DOUBLE, L"f", L"is the forward.", L"100")
	.Arg(XLL_DOUBLE, L"sigma", L"is the volatility.", L"0.2")
	.Arg(XLL_DOUBLE, L"k", L"is the strike.", L"100")
	.Arg(XLL_DOUBLE, L"t", L"is the time in years to expiration.", L"0.25")
	.Category(L"XLL")
	.FunctionHelp(L"Return the GAMMA put value.")
	.Documentation(
		L"This function helps to calculate the put option price using GAMMA distribution,"
		L"Put value is E[(k - F)^+],which equals k*P(F 'less or equal to'  k) - E[F*1(F 'less or equal to' k)], "
		L"where E[F 1(G'less or equal to'k/f)], which equals f int_0^k x g(x) dx, and which equals to f gamma::cdf(k/f, a + 1, b), "
		L"where a,b equal to 1/(exp(s^2) - 1); "
	)
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