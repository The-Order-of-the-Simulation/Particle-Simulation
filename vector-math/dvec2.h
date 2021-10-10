#pragma once

class dvec2
{
	public:
		double x;
		double y;
};

dvec2 double2(double x, double y)
{
	dvec2 vector;
	vector.x = x;
	vector.y = y;
	return vector;
}

dvec2 double2f(double x)
{
	dvec2 vector;
	vector.x = x;
	vector.y = x;
	return vector;
}