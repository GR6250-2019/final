// xll_gamma.cpp - Gamma distribution.
#include "../xll12/xll/xll.h"
#include "../xll12/xll/shfb/entities.h"
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

static AddIn xai_gamma_pdf(
	Function(XLL_DOUBLE, L"?xll_gamma_pdf", L"XLL.GAMMA.PDF")
	.Arg(XLL_DOUBLE, L"x", L"is the value at which to compute the gamma pdf.")
	.Arg(XLL_DOUBLE, L"a", L"is a parameter of gamma pdf")
	.Arg(XLL_DOUBLE, L"b", L"is a parameter of gamma pdf")
	.Category(CATEGORY)
	.FunctionHelp(L"Return the value of the probability density function of gamma, where the mean is a/b and variance is a/b^2.")
	.Documentation(
		L"This function computes the probability density function of gamma."
		L"Gamma distribution: g(x) = x^{a-1} exp(-b x) b^a/Gamma(a), x > 0"
	)
);
double WINAPI xll_gamma_pdf(double x, double a, double b)
{
#pragma XLLEXPORT


	return fms::gamma::pdf(x, a, b);
}

static AddIn xai_gamma_cdf(
	Function(XLL_DOUBLE, L"?xll_gamma_cdf", L"XLL.GAMMA.CDF")
	.Arg(XLL_DOUBLE, L"x", L"is the value at which to compute the cdf.")
	.Arg(XLL_DOUBLE, L"a", L"is the a parameter of gamma cdf")
	.Arg(XLL_DOUBLE, L"b", L"is the a parameter of gamma pdf")
	.Category(CATEGORY)
	.FunctionHelp(L"Return the value of the cumulative distribution function of gamma.")
	.Documentation(
		L"This function computes the cumulative distribution function of gamma "
	)
);
double WINAPI xll_gamma_cdf(double x, double a, double b)
{
#pragma XLLEXPORT
	
	return fms::gamma::cdf(x, a, b);
}

static AddIn xai_gamma_put(
	Function(XLL_DOUBLE, L"?xll_gamma_put", L"XLL.GAMMA.PUT")
	.Arg(XLL_DOUBLE, L"f", L"is the forward.")
	.Arg(XLL_DOUBLE, L"sigma", L"is the volatility.")
	.Arg(XLL_DOUBLE, L"k", L"is the strike.")
	.Arg(XLL_DOUBLE, L"t", L"is the time in years to expiration.")
	.Category(L"XLL")
	.FunctionHelp(L"Return put gamma value.")
);

double WINAPI xll_gamma_put(double f, double sigma, double k, double t)
{
#pragma XLLEXPORT
	double result = std::numeric_limits<double>::quiet_NaN();

	try {
		result = fms::gamma::put(f, sigma, k, t);
	}
	catch (const std::exception & ex) {
		XLL_ERROR(ex.what());
	}

	return result;
}


