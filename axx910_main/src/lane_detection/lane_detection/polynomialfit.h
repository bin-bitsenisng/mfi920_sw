#ifndef __POLYNOMIALFIT_H__
#define __POLYNOMIALFIT_H__

#include <iostream>
#include <vector>

using namespace std;

class Polyfitter
{
private:
	int h;
	vector<double> x;
	vector<double> y;
	vector<double> coefficient;
public:
	vector<double> getCoefficient();
	void polyfit(vector<double> y, vector<double> x, int degree);
	void polyVal();
};

#endif