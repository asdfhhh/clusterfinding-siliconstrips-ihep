#pragma once

class RandomUser
{
public:
	RandomUser(void);
	~RandomUser(void);
	float mean;

	//Seed is the parameter of srand (the random number generator function of C).
	//srand takes an integer as a parameter. If this integer is the same,
	//then each time the program is exucuted, the same random numbers
	//will be generated. In order to avoid this, we put the current time as the parameter of
	//the srand function.
	int seed;
	//Initiate the random number generator. The initiation must be done outside the generation
	//functions, and usually is done only once.

	double Constant(double mean);
	double Uniform(double mean);
	double Exponential(double mean);
	int Poisson(int mean);
	double Pareto(double alpha);
	double Normal(double mean, double stdev);
	int Geometric(double p);
	double Weibull(double scale, double shape);
	double Erlang(int scale, double shape);
	int CosmicRandom();
};
