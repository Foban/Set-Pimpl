#include "sets.h"


class Set::ImSet{
public:
	ImSet();
	ImSet(int *, int);
	ImSet(const ImSet &);
	int operator[](int ) const;
	bool operator == (const ImSet &) const;
	ImSet & operator = (const ImSet &);
	ImSet operator + (const ImSet &) const;
	ImSet operator - (const ImSet &) const;
	ImSet operator * (const ImSet &) const;
	int get_length() const;
	int* get_elements() const;
	~ImSet();

private:
	void Recontain();
	int *elements;
	int length;
};


Set::Set():
pimpl(0)
{
	pimpl = new ImSet;
}

Set::Set(int *ar, int size):
pimpl(0)
{
	pimpl = new ImSet(ar, size); 
}

Set::Set(const Set & set):
pimpl(0)
{
	pimpl = new ImSet(*set.pimpl);
}

Set::Set(const ImSet & imset):
pimpl(0)
{
	pimpl = new ImSet(imset);
}

Set::~Set(){
	delete pimpl;
	pimpl = 0;
}

Set &Set::operator+=(const Set &other){
	return *this = *this + other;
}

Set &Set::operator-=(const Set &other){
	return *this = *this - other;
}

Set &Set::operator*=(const Set &other){
	return *this = *this * other;
}

bool Set::operator == (const Set &other) const{
	return *pimpl == *other.pimpl;
}

Set & Set::operator=(const Set &other){
	*pimpl = *other.pimpl;
	return *this;
}

Set Set::operator+(const Set &other) const{
	return Set(pimpl->operator+(*other.pimpl)) ;
}

Set Set::operator-(const Set &other)const{
	return Set(pimpl->operator-(*other.pimpl)) ;
}

Set Set::operator*(const Set &other)const{
	return Set(pimpl->operator*(*other.pimpl)) ;
}

int Set::operator[](int num) const{
	return (*pimpl)[num];
}

int Set::get_length() const{
	return pimpl->get_length();
}

int* Set::get_elements() const{
	return pimpl->get_elements();
}


////////////////////////////////////////////////////////////////

Set::ImSet::ImSet():
elements(0), length(0)
{}

Set::ImSet::ImSet(int *ar, int size):
elements(0), length(0)
{
	elements = new int[size];
	bool fl = true;
	length = size;
	for(int i = 0; i < size; ++i){
		for(int n = 0; n < i && fl; ++n)
			if(ar[i] == elements[n]){
				fl = false;
				--length;
			}
		if(fl)elements[i] = ar[i];
		fl = true;
	}
	if(size != length) Recontain();
}

Set::ImSet::ImSet(const ImSet & set):
elements(0), length(0)
{
	elements = new int[set.length];
	for(int i = 0; i < set.length; ++i)
		elements[i] = set.elements[i];
	length = set.length;
}

Set::ImSet::~ImSet(){
	delete [] elements;
}

void Set::ImSet::Recontain(){
	int *sets_elements = new int [length];
	for(int i = 0; i < length; ++i)
		sets_elements[i] = elements[i];
	delete [] elements;
	elements = sets_elements;
}

bool Set::ImSet::operator == (const ImSet &other) const{
	if(this != &other){
		bool fl = false;
		for(int i = 0; i < length; ++i){
			for(int n = 0; n < other.length && !fl; ++n)
				if(elements[i] == other.elements[n]) fl = true;
			if(!fl) return false;
			fl = false;
		}
		return true;
	}
	return true;
}

Set::ImSet & Set::ImSet::operator=(const ImSet &other){
	if(this != &other)
	{
		int *new_elements = new int[other.length];
		for(int i = 0; i < other.length; ++i)
			new_elements[i] = other.elements[i];
		delete [] elements;
		elements = new_elements;
		length = other.length;
	}
	return *this;
}

Set::ImSet Set::ImSet::operator+(const ImSet &other) const{
	if(this != &other)
	{
		if(length == 0) return other;
		if(other.length == 0) return *this;
		ImSet new_set;
		new_set.elements = new int[length+other.length];
		for(int i = 0; i < length; ++i)
			new_set.elements[i] = elements[i];
		int p = length;
		bool fl = true;
		for(int i = 0; i < other.length; ++i){
			for(int n = 0; n < length && fl; ++n){
				if(other.elements[i] == elements[n]) fl = false;
			}
			if(fl){
				new_set.elements[p] = other.elements[i];
				++p;
			}
			fl = true;
		}
		new_set.length = p;
		if(new_set.length != length + other.length) new_set.Recontain();
		return new_set;
	}
	return *this;
}

Set::ImSet Set::ImSet::operator-(const ImSet &other) const{
	ImSet new_set;
	if(this != &other){
		if(length == 0) return new_set;
		if(other.length == 0) return *this;
		new_set.elements = new int[length];
		new_set.length = length;
		int p = 0;
		bool fl = true;
		for(int n = 0; n < length; ++n){
			for(int i = 0; i < other.length && fl; ++i)
				if(elements[n] == other.elements[i])
					fl = false;
			if(!fl) --new_set.length;
			else{
				new_set.elements[p] = elements[n];
				++p;
			}
			fl = true;
		}
		if(new_set.length != length) new_set.Recontain();
	}
	return new_set;
}

Set::ImSet Set::ImSet::operator*(const ImSet &other) const{
	if(this != &other){
		ImSet new_set;
		if(length == 0 || other.length == 0) return new_set;
		int min_length = (length > other.length ? length : other.length);
		new_set.elements = new int [min_length];
		int p = 0;
		bool fl = true;
		for(int i = 0; i < other.length && p != min_length; ++i){
			for(int n = 0; n < length && fl; ++n)
			{
				if(elements[n] == other.elements[i]) 
					fl = false;
			}
			if(!fl){
				new_set.elements[p] = other.elements[i];
				++p;
			}
			fl = true;
		}
		new_set.length = p;
		if(new_set.length != min_length) new_set.Recontain();
		return new_set;
	}
	return *this;
}

int Set::ImSet::operator[](int i) const{
	if(i < length && i > (-1)){
		return elements[i];
	}
	else throw -1;
}

int Set::ImSet::get_length() const{
	return length;
}

int* Set::ImSet::get_elements() const{
	return elements;
}
