#ifndef SETS_H
#define SETS_H

class Set{
public:
	Set();
	Set(int *, int);
	Set(const Set &);
	int operator[](int ) const;
	Set & operator +=(const Set &);
	Set & operator -=(const Set &);
	Set & operator *=(const Set &);
	bool operator == (const Set &) const;
	Set & operator = (const Set &);
	Set operator + (const Set &) const;
	Set operator - (const Set &) const;
	Set operator * (const Set &) const;
	~Set();

protected:
	int get_length() const;
	int* get_elements()const;

private:
	class ImSet;
	ImSet *pimpl;
	Set (const ImSet &);
};

#endif