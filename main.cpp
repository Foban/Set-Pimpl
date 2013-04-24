#include "sets.h"
#include <iostream>
 
using namespace std;

class ConSet: public Set{
public:
	ConSet();
	ConSet(int *, int);
	ConSet(const ConSet &);
	ConSet(const Set &);
	ConSet & operator +=(const ConSet &);
	ConSet & operator -=(const ConSet &);
	ConSet & operator *=(const ConSet &);
	bool operator == (const ConSet &) const;
	ConSet & operator = (const ConSet &);
	ConSet operator + (const ConSet &) const;
	ConSet operator - (const ConSet &) const;
	ConSet operator * (const ConSet &) const;
	friend ostream & operator << (ostream &, const ConSet &);
	friend istream & operator >> (istream &, ConSet &);
	~ConSet();
};

int main(){
	ConSet a, b, c;
	cout << "Input set a: ";
	cin >> a;
	cout << "Input set b: ";
	cin >> b;
	cout << "a=" << a << "\tb=" << b << '\n';
	c= a + b;
	cout << "c=a+b=" << c << '\n';
	c = a - b;
	cout << "c=a-b=" << c << '\n';
	c = a * b;
	cout << "c=a*b=" << c << '\n';
	c += a;
	cout << "c+=a=" << c << '\n';
	c += b;
	cout << "c+=b=" << c << '\n';
	c -= a;
	cout << "c-=a=" << c << '\n';
	c *= b;
	cout << "c*=b=" << c << '\n';


	system("pause");
    return 0;
}

/////////////////////////////////////////////////////////////

ConSet::ConSet():
Set()
{}

ConSet::ConSet(int* elements, int length):
Set(elements, length)
{}

ConSet::ConSet(const ConSet & set):
Set(set)
{}

ConSet::ConSet(const Set & set):
Set(set)
{}

ConSet::~ConSet()
{}

ConSet &ConSet::operator+=(const ConSet & other){
	Set::operator+=(other);
	return *this;
}


ConSet &ConSet::operator-=(const ConSet & other){
	Set::operator-=(other);
	return *this;
}

ConSet &ConSet::operator*=(const ConSet & other){
	Set::operator*=(other);
	return *this;
}

ConSet &ConSet::operator=(const ConSet & other){
	Set::operator=(other);
	return *this;
}

bool ConSet::operator==(const ConSet & other) const{
	return Set::operator==(other);
}

ConSet ConSet::operator+(const ConSet & other) const{
	return ConSet(Set::operator+(other));
}

ConSet ConSet::operator-(const ConSet & other) const{
	return ConSet(Set::operator-(other));
}

ConSet ConSet::operator*(const ConSet & other) const{
	return ConSet(Set::operator*(other));
}

ostream & operator << (ostream &out, const ConSet &set ){
	out << '{'; 
	int set_length = set.get_length();
	int* set_elements = set.get_elements();
	for(int i = 0; i < set_length-1; ++i)
		out << set_elements[i] << ", ";
	if(set_length) out << set_elements[set_length-1];
	out << '}';
	return out;
}
istream & operator >> (istream & in,  ConSet &set){
	int length, *ar;
	in >> length;
	ar = new int[length];
	for(int i = 0; i < length; ++i){
		in >> ar[i];
	}
	set = ConSet(ar, length);
	return in;
}