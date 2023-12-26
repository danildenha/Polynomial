// Polynomial.h -- starter code

#ifndef __POLYNOMIAL_H_
#define __POLYNOMIAL_H_
#include <iostream>
#include <list>
#include <cmath>
using namespace std;

// Monomial - class that creates the terms that get inserted in a Polynomial
template <typename NumT>
class Monomial {
public:
	Monomial<NumT>(NumT c = 0, int d = 0) : coeff(c), expo(d) { };
	NumT coefficient(void) const { return coeff; };
	int degree(void) const { return expo; };
	void assign_coefficient(const NumT c) { coeff = c; };
	void assign_degree(const int d) { expo = d; };

	bool operator==(const Monomial<NumT>& m) const {
		return (coeff == m.coeff && expo == m.expo);
	}

	bool operator!=(const Monomial<NumT>& m) const {
		return (coeff != m.coeff || expo != m.expo);
	}
private:
	NumT coeff; // in our case this will be an int
	int	expo;
};

//Polynomial Class
template <typename NumberType>
class Polynomial
{
public:
	// Default constructor
	Polynomial<NumberType>(NumberType c = 0, int d = 0) {
		const Monomial<NumberType> m(c, d);
		term_list.push_back(m); //creates at least one monomial
		number_of_terms = 1;
		highest_degree = d;
	}

	// Type conversion construct
	Polynomial<NumberType>(const Monomial<NumberType>& m) {
		term_list.push_back(m);
		number_of_terms = 1;
		highest_degree = m.degree();
	}

	// Destructor - use default destructors and list's destructor
	~Polynomial<NumberType>() { term_list.clear(); }

	// Copy Constructor
	Polynomial<NumberType>(const Polynomial<NumberType>& rhs)
		: term_list(rhs.term_list),
		number_of_terms(rhs.number_of_terms),
		highest_degree(rhs.highest_degree) {}

	int gethighestdegree() const { return highest_degree; }

	// copy assignment
	const Polynomial<NumberType>& operator=(const Polynomial<NumberType>& rhs)
	{
		this->term_list = rhs.term_list;
		this->number_of_terms = rhs.number_of_terms;
		this->highest_degree = rhs.highest_degree;
		return *this;
	}

	// move assignment
	const Polynomial<NumberType>& operator=(Polynomial<NumberType>&& rhs)
	{
		if (this != &rhs)
		{
			*this = rhs;

			// Clear source data to prevent memory leaks
			rhs.term_list.clear();
			rhs.number_of_terms = 0;
			rhs.highest_degree = 0;
		}
		return *this;
	}

	// addition of different types
	Polynomial<NumberType> operator+=(const Monomial<NumberType>& m)
	{
		insert_in_poly(*this, m);
		return *this;

	}//1
	Polynomial<NumberType> operator+=(const Polynomial<NumberType>& rhs)
	{
		for (const auto x : rhs.term_list)
		{
			insert_in_poly(*this, x);
		}
		return *this;
	}
	//2
	const Polynomial<NumberType> operator+ (const Monomial<NumberType>& m)const
	{
		Polynomial<NumberType> result(*this);
		result += m;
		return result;
	}
	//3
	const Polynomial<NumberType> operator+ (const Polynomial<NumberType>& rhs) const
	{
		Polynomial<NumberType> result(*this);
		result += rhs;
		return result;
	}
	//4

	// substraction of different types
	Polynomial<NumberType> operator-=(const Monomial<NumberType>& m)
	{
		auto it = find_if(term_list.begin(), term_list.end(),
			[&m](auto term) {return term.degree() == m.degree(); });
		if (it != term_list.end())
		{
			NumberType result = it->coefficient() - m.coefficient();
			if (result != 0)
			it->assign_coefficient(result);
			else
			{
				term_list.erase(it);
				--number_of_terms;
			}
		}
		else
		{
			insert_in_poly(*this, Monomial<NumberType>(-m.coefficient(), m.degree()));
		}
		return *this;
	}
	Polynomial<NumberType> operator-=(const Polynomial<NumberType>& rhs)
	{
		for (const auto x : rhs.term_list)
		{
			*this -= x;
		}
		return *this;
	}
	const Polynomial<NumberType> operator- (const Monomial<NumberType>& m)const
	{
		Polynomial<NumberType> result(*this);
		result -= m;
		return result;
	}
	const Polynomial<NumberType> operator- (const Polynomial<NumberType>& rhs) const
	{
		Polynomial<NumberType> result(*this);
		result -= rhs;
		return result;
	}

	// MULTIPLICATION
	Polynomial<NumberType> operator*=(const Monomial<NumberType>& m)
	{
		for (auto curr : term_list)
		{
			curr.assign_coefficient(m.coefficient() * curr.coefficient());
			curr.assign_degree(m.degree() + curr.degree());
		}
		highest_degree += m.degree();
		return *this;
	}
	Polynomial<NumberType> operator*=(const Polynomial<NumberType>& rhs)
	{
		Polynomial<NumberType> result(*this);

		for (auto& term1 : term_list)
		{
			for (auto& term2 : rhs.term_list)
			{
				NumberType newCoeff = term1.coefficient() * term2.coefficient();
				int newDegree = term1.degree() + term2.degree();
				Monomial<NumberType> temp(newCoeff, newDegree);

				insert_in_poly(result, temp);
			}
		}
		*this = result;
		return *this;
	}
	const Polynomial<NumberType> operator*(const Monomial<NumberType>& m) const
	{
		Polynomial<NumberType> result(*this);
		result *= m;
		return result;
	}
	const Polynomial<NumberType> operator*(const Polynomial<NumberType>& rhs)const
	{
		Polynomial<NumberType> result(*this);
		result *= rhs;
		return result;
	}

	// EVALUATION POLYNOMIAL
	const NumberType evaluate(NumberType x) const
	{
		NumberType result{ 0 };
		for (auto& curr : term_list)
		{
			//if no static_cast included then compiler warns us about potential data loss
			result += static_cast<NumberType>(curr.coefficient() * power(x,curr.degree()));
		}
		return result;
	}

	// EQUALITY TESTS
	bool operator==(const Polynomial<NumberType>& p) const
	{
		if (term_list.size() != p.term_list.size())
		{
			return false;
		}
		auto it1 = term_list.begin();
		auto it2 = p.term_list.begin();
		while (it1 != term_list.end() && it2 != p.term_list.end())
		{
			if (it1->degree() != it2->degree() || it1->coefficient() != it2->coefficient())
			{
				return false;
			}
			++it1;
			++it2;
		}
		return true;
	}
	bool operator!=(const Polynomial<NumberType>& p) const
	{
		return !(*this == p);
	}

	// CALLED FROM ISTREAM AND OSTREAM OVERLOADS
	// read() function has responsibility for getting input, creating Monomial object,
	//			and inserting into Polynomial object
	void read(istream& in = cin)
	{
		term_list.clear(); // Clear the existing terms
		int coeff;

		while (in >> coeff && coeff != 0) {
			int degree;
			in >> degree;
			insert_in_poly(*this, Monomial<NumberType>(coeff, degree));
		}
	}

	// print() function -- make sure you look back at requirements for this
	void print(ostream& out = cout) const
	{
		out << "\nNumber terms " << number_of_terms << endl;
		for (auto it = term_list.begin(); it != term_list.end(); ++it) {
			//variables to improve readability
			bool beginning = it != term_list.begin();
			NumberType currCoeff = it->coefficient();
			int currDegree = it->degree();

			if (beginning && currCoeff > 0)
			{
				out << " + ";
			}
			else if (beginning)
			{
				out << " - ";
			}
			else if (currCoeff < 0)
			{
				out << "-";
			}

			if (abs(currCoeff) != 1 || currDegree == 0)
			{
				out << abs(currCoeff);
			}

			if (currDegree > 0)
			{
				out << "x";
				if (currDegree > 1) {
					out << "^" << currDegree;
				}
			}
		}
		out << endl;
	}

private:
	list<Monomial<NumberType> > term_list; //SORTED BY DECREASING DEGREES
	int number_of_terms;
	int highest_degree;

	//private helper member function -- review notes below function prototype
	void insert_in_poly(Polynomial<NumberType>& p, const Monomial<NumberType>& m)
	{
		auto it = find_if(p.term_list.begin(), p.term_list.end(),
			[&m](auto term) { return term.degree() == m.degree(); });

		if (it != p.term_list.end())
		{
			it->assign_coefficient(m.coefficient() + it->coefficient());
		}
		else
		{
			p.term_list.push_back(m);
			p.term_list.sort([](const auto& x, const auto& y) { return x.degree() > y.degree(); });
		}

		p.number_of_terms = p.term_list.size();
		p.highest_degree = (p.term_list.empty()) ? 0 : p.term_list.front().degree();
	}

	// Used in evaluate member function
	NumberType power(NumberType x, int n) const
	{
		return pow(x, n);
	}
};

// DO NOT MODIFY
template<typename NumberType>
istream& operator>>(istream& in, Polynomial<NumberType>& rhs) {
	rhs.read();
	return in;
}

// DO NOT MODIFY
template<typename NumberType>
ostream& operator<<(ostream& out, const  Polynomial<NumberType>& rhs) {
	rhs.print();
	return out;
}

#endif


