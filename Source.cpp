// PHYS 30762 Programming in C++
// Assignment 4

// Class for complex numbers

#include<iostream>
#include<cmath>
#include<string>
#include<sstream>

class complex
{
	// Make function to overload operators << and >> friends
	friend std::ostream& operator<<(std::ostream& os, const complex& c);
	friend std::istream& operator>>(std::istream& input, complex& c);
private:
	double re, im;
public:
	// Constructors & destructor
	complex() : re{}, im{} {} //default
	complex(double r, double i) : re{ r }, im{ i } {} //parameterised
	~complex() {}

	// Return real component
	double return_re() const { return re; }
	// Return imaginary component
	double return_im() const { return im; }
	// Return modulus
	double return_mod() const { return sqrt(re * re + im * im); }
	// Return argument
	double return_arg() const;
	// Return complex conjugate
	complex complex_conj() const { complex result{ re, -im }; return result; }
	// Overload + operator for addition 
	complex operator+(const complex& c) const { complex result{ re + c.re, im + c.im }; return result; }
	// Overload - operator for subtraction
	complex operator-(const complex& c) const { complex result{ re - c.re, im - c.im }; return result; }
	// Overload * operator for multiplication, z1*z2
	complex operator*(const complex& c) const {
		complex result{ re * c.re - im * c.im, re * c.im + im * c.re }; return result;
	}
	// Overload / operator for division, z1/z2
	complex operator/(const complex& c) const {
		complex result{ (re * c.re + im * c.im) / (c.re * c.re + c.im * c.im),
		(im * c.re - re * c.im) / (c.re * c.re + c.im * c.im) }; return result;
	} //allowed to divide by 0 as will return a nan, which is OK
};
// return complex argument in [0,2pi). Left (0,0) allowed as atan kind of deals with it and
// user input is not assessed here. atan is also fine for re=0
double complex::return_arg() const
{
	if (re >= 0 && im >= 0) { return atan(im / re); }
	else if (re < 0) { return atan(1) * 4 + atan(im / re); }
	else { return atan(1) * 8 + atan(im / re); }
}

// Functions to overload << and >> operators for complex numbers
std::ostream& operator<<(std::ostream& os, const complex& c)
{
	if (c.im >= 0) { os << c.re << " + " << c.im << "i"; }
	else { os << c.re << " - " << -c.im << "i"; } //decided to leave in 0 coefficients
	return os;
}

std::istream& operator>>(std::istream& input_stream, complex& c)
{
	while (true) {
		char sign, i; double a, b; std::string input_string;

		std::cout << "Enter a complex number of the form a+/-bi: ";
		std::getline(input_stream, input_string);

		std::stringstream ss(input_string);
		if (ss >> a && ss >> sign && (sign == '+' || sign == '-') && ss >> b && ss.get(i) && i == 'i') {
			if (sign == '-')
				b *= -1;

			c.re = a;
			c.im = b;
			break;
		}
		else {
			std::cout << "Invalid input. Please try again." << std::endl;
		}
	}
	return input_stream;
}

int main()
{
	std::cout.precision(3);

	//Use overloading of >> operator
	complex c;
	std::cin >> c;
	std::cout << "You inputted: " << c << std::endl;

	// Create two complex numbers
	complex a{ 4, 3 };
	complex b{ 1, -2 };

	// Get real and imaginary components, modulus and argument
	double a_re{ a.return_re() };
	double a_im{ a.return_im() };
	double a_mod{ a.return_mod() };
	double a_arg{ a.return_arg() };
	// Get conjugates
	complex a_conj{ a.complex_conj() };
	// Get sum, difference, product and quotient of a and b
	complex sum{ a + b };
	complex diff{ a - b };
	complex prod{ a * b };
	complex quot{ a / b };
	// Print out results, also demonstrating use of overloaded operator<<
	std::cout << "Take complex numbers a = " << a << " and b = " << b << std::endl;
	std::cout << "a has real and imaginary parts " << a_re << " and " << a_im << " respectively." << std::endl;
	std::cout << "It has modulus " << a_mod << " and argument " << a_arg << " and its complex conjugate is "
		<< a_conj << "." << std::endl;
	std::cout << "a and b have sum, difference, product and quotient of " << sum << ", " << diff << ", "
		<< prod << " and " << quot << " respectively." << std::endl;

	return 0;
}