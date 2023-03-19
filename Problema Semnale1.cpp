#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

class Semnal
{
public:
	Semnal* sus;
	Semnal* urm;
	Semnal* jos;
	double valoare;

	Semnal(double i)
	{
		valoare = i;
	}
	Semnal()
	{
		sus = urm = jos = nullptr;
	}
	virtual void f1() = 0;
	virtual void f2(double prag) = 0;
	virtual void f3(double prag) = 0;
	virtual void f4() = 0;
	virtual void adauga(double x) = 0;
	void afisare()
	{
		auto it = sus;
		while (it != nullptr)
		{
			cout << it->valoare << " ";
			it = it->urm;
		}
	}
};

class DSP1 : public Semnal
{
public:
	DSP1() {}
	DSP1(double i)
	{
		valoare = i;
	}
	void adauga(double x) override
	{
		Semnal* newNode;
		newNode = new DSP1(x);
		auto it = sus;
		if (it == nullptr)
		{
			sus = newNode;
			sus->urm = nullptr;
			return;
		}
		while (it->urm != nullptr)
		{
			it = it->urm;
		}
		it->urm = newNode;
		newNode->urm = nullptr;
	}
	void f1() override
	{
		int nr = 0;
		double pre = sus->valoare;
		auto it = sus->urm;
		auto it_ant = sus;
		while (it != nullptr)
		{
			if (pre > 0 && it->valoare < 0)
			{
				nr++;
				pre = it->valoare;
			}
			if (pre < 0 && it->valoare > 0)
			{
				nr++;
				pre = it->valoare;
			}
			if (it->valoare == 0)
			{
				nr++;
				pre = it->valoare;
			}
			if (it_ant->valoare == 0 && (it->valoare >= 0 || it->valoare <= 0))
			{
				nr++;
				pre = it->valoare;
			}
			it = it->urm;
			it_ant = it_ant->urm;
		}
		cout << nr << endl;
	}
	void f2(double prag) override
	{
		int nr = 0;
		auto it = sus;
		double sum = 0;
		while (it != nullptr)
		{
			if (nr == 9)
			{
				it->valoare = sum / 9;
				sum = 0;
				nr = 0;
			}
			else
			{
				nr++;
				sum = sum + it->valoare;
			}
			it = it->urm;
		}
		auto it2 = sus;
		while (it2 != nullptr)
		{
			cout << fixed << setprecision(2) << it2->valoare << " ";
			it2 = it2->urm;
		}
		cout << endl;
	}
	void f3(double prag) override
	{
		auto it = sus;
		while (it != nullptr)
		{
			if (it->valoare >= 15)
				it->valoare = 1;
			else
				it->valoare = 0;
			it = it->urm;
		}
		auto it2 = sus;
		while (it2 != nullptr)
		{
			cout << fixed << setprecision(0) << it2->valoare << " ";
			it2 = it2->urm;
		}
		cout << endl;
	}
	void f4() override
	{
		int nr = 5;
		auto it = sus;
		while (it != nullptr)
		{
			if (nr == 5)
			{
				cout << it->valoare << " ";
				nr = 1;
			}
			else
				nr++;
			it = it->urm;
		}
	}
};

class DSP2 : public Semnal
{
public:
	DSP2() {}
	DSP2(double i)
	{
		valoare = i;
	}
	void adauga(double x) override
	{
		Semnal* newNode;
		newNode = new DSP2(x);
		auto it = sus;
		if (it == nullptr)
		{
			sus = newNode;
			sus->urm = nullptr;
			return;
		}
		while (it->urm != nullptr)
		{
			it = it->urm;
		}
		it->urm = newNode;
		newNode->urm = nullptr;
	}
	void f1() override
	{
		int nr = 0;
		auto it = sus->urm;
		auto prev = sus;
		if (prev->valoare > it->valoare)
			nr++;
		while (it->urm != nullptr)
		{
			if (it->valoare > 0 && it->urm->valoare < it->valoare && prev->valoare < it->valoare)
				nr++;
			it = it->urm;
			prev = prev->urm;
		}
		if (it->valoare > prev->valoare)
			nr++;
		cout << nr << endl;
	}
	void f2(double prag) override
	{
		int nr = 0;
		auto it = sus->urm;
		auto prev = sus;
		if (prev->valoare > it->valoare)
			if (prev->valoare > prag)
				nr++;
		while (it->urm != nullptr)
		{
			if (it->valoare > 0 && it->urm->valoare < it->valoare && prev->valoare < it->valoare)
				if (it->valoare > prag)
					nr++;
			it = it->urm;
			prev = prev->urm;
		}
		if (it->valoare > prev->valoare)
			if (it->valoare > prag)
				nr++;
		cout << nr << endl;
	}
	void f3(double prag) override
	{
		auto it = sus->urm;
		auto prev = sus;
		if (prev->valoare > it->valoare)
			if (prev->valoare < prag)
				prev->valoare = it->valoare / 2;
		while (it->urm != nullptr)
		{
			if (it->valoare > 0 && it->urm->valoare < it->valoare && prev->valoare < it->valoare)
				if (it->valoare < prag)
					it->valoare = (prev->valoare + it->urm->valoare) / 2;
			it = it->urm;
			prev = prev->urm;
		}
		if (it->valoare > prev->valoare)
			if (it->valoare < prag)
				it->valoare = prev->valoare / 2;
		auto it2 = sus;
		while (it2 != nullptr)
		{
			cout << fixed << setprecision(2) << it2->valoare << " ";
			it2 = it2->urm;
		}
		cout << endl;
	}
	void f4() override
	{
		for (int i = 0; i < 5; i++)
		{
			Semnal* newNode;
			newNode = new DSP2(0.00);
			newNode->urm = sus;
			sus = newNode;
			Semnal* newNode2;
			newNode2 = new DSP2(0.00);
			auto it = sus;
			while (it->urm != nullptr)
				it = it->urm;
			it->urm = newNode2;
			newNode2->urm = nullptr;
		}
		auto it2 = sus;
		while (it2 != nullptr)
		{
			cout << fixed << setprecision(2) << it2->valoare << " ";
			it2 = it2->urm;
		}
		cout << endl;
	}
};

int main()
{
	int tip;
	double prag;
	//vector<double> lst;
	cin >> tip >> prag;
	if (tip == 1)
	{

		vector<double> lst;
		double x;
		while (cin >> x)
		{
			lst.push_back(x);
			//	list.adauga(x);
		}
		DSP1 list;
		for (int i = 0; i < lst.size(); i++)
			list.adauga(lst[i]);
	//	list.afisare();
		list.f1();
		list.f2(prag);
		list.f3(prag);
		list.f4();

		//cout << endl;
	}
	else
	{
		vector<double> lst;

		double x;
		while (cin >> x)
		{
			lst.push_back(x);
		}
		
		DSP2 list;
	//	list.adauga(lst);
		//list.afisare();
		for (int i = 0; i < lst.size(); i++)
			list.adauga(lst[i]);
		list.f1();
		list.f2(prag);
		list.f3(prag);
		list.f4();
	}
	return 0;
}
