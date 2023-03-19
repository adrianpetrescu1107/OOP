#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

class Robot
{
protected:
	double p1, p2, p3, precizie, gros, perimetru, arie, cul, robot1, robot2, cost;
	string umplere;
public:
	Robot()
	{
		p1 = 0;
		p2 = 0;
		p3 = 0;
		precizie = 0;
		gros = 0;
		perimetru = 0;
		arie = 0;
		cul = 0;
		robot1 = 0;
		robot2 = 0;
		cost = 0;
		umplere = "GOALA";
	}
	virtual void Perimetru() {}
	virtual void Arie() {}
	void calcul_Robot1()
	{
		robot1 = gros * precizie * perimetru;
	}
	void calcul_Robot2()
	{
		if (umplere == "GOALA")
			robot2 = 0;
		if (umplere == "COLORATA")
			robot2 = cul * arie;
	}
	void calcul_cost()
	{
		cost = robot1 + robot2;
	}
	double get_cost()
	{
		return cost;
	}
};
class Cerc : public Robot
{
protected:
	double raza;
public:
	Cerc(double p11, double p21, double p31, double cul1, double raza1, double gros1, double pr, string ump)
	{
		p1 = p11;
		p2 = p21;
		p3 = p31;
		raza = raza1;
		gros = gros1;
		if (pr == 1)
			precizie = p1;
		if (pr == 2)
			precizie = p2;
		if (pr == 3)
			precizie = p3;
		perimetru = 0;
		arie = 0;
		cul = cul1;
		umplere = ump;
	}
	void Perimetru() override
	{
		perimetru = 2 * 3.14159265358979323846 * raza;
	}
	void Arie() override
	{
		arie = 3.14159265358979323846 * raza * raza;
	}
};
class Patrat : public Robot
{
protected:
	double lat;
public:
	Patrat(double p11, double p21, double p31, double cul1, double lat1, double gros1, double pr, string ump)
	{
		p1 = p11;
		p2 = p21;
		p3 = p31;
		lat = lat1;
		gros = gros1;
		if (pr == 1)
			precizie = p1;
		if (pr == 2)
			precizie = p2;
		if (pr == 3)
			precizie = p3;
		perimetru = 0;
		arie = 0;
		cul = cul1;
		umplere = ump;
	}
	void Perimetru() override
	{
		perimetru = 4 * lat;
	}
	void Arie() override
	{
		arie = lat * lat;
	}
};
class Dreptunghi : public Robot
{
protected:
	double lung, lat;
public:
	Dreptunghi(double p11, double p21, double p31, double cul1, double lung1, double lat1, double gros1, double pr, string ump)
	{
		p1 = p11;
		p2 = p21;
		p3 = p31;
		lung = lung1;
		lat = lat1;
		gros = gros1;
		if (pr == 1)
			precizie = p1;
		if (pr == 2)
			precizie = p2;
		if (pr == 3)
			precizie = p3;
		perimetru = 0;
		arie = 0;
		cul = cul1;
		umplere = ump;
	}
	void Perimetru() override
	{
		perimetru = 2 * lung + 2 * lat;
	}
	void Arie() override
	{
		arie = lung * lat;
	}
};
class Triunghi : public Robot
{
protected:
	double lat, h;
public:
	Triunghi(double p11, double p21, double p31, double cul1, double lat1, double h1, double gros1, double pr, string ump)
	{
		p1 = p11;
		p2 = p21;
		p3 = p31;
		lat = lat1;
		h = h1;
		gros = gros1;
		if (pr == 1)
			precizie = p1;
		if (pr == 2)
			precizie = p2;
		if (pr == 3)
			precizie = p3;
		perimetru = 0;
		arie = 0;
		cul = cul1;
		umplere = ump;
	}
	void Perimetru() override
	{
		perimetru = 3 * lat;
	}
	void Arie() override
	{
		arie = (lat * h) / 2;
	}
};
void sortare(vector<double> v, int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n - i - 1; j++)
			if (v[j] > v[j + 1])
			{
				double aux;
				aux = v[j];
				v[j] = v[j + 1];
				v[j + 1] = aux;
			}
}
int main()
{
	double p1, p2, p3, cul;
	cin >> p1 >> p2 >> p3 >> cul;
	int n;
	cin >> n;
	Robot* pointer;
//	double* v = new double[n];
	vector<double> v(n);
	for (int i = 0; i < n; i++)
		v[i] = 0;
	for (int i = 0; i < n; i++)
	{
		double gros, pr;
		string umplere, forma;
		cin >> gros >> pr >> umplere >> forma;
		if (forma == "CERC")
		{
			double r;
			cin >> r;
			Cerc val(p1, p2, p3, cul, r, gros, pr, umplere);
			pointer = &val;
			pointer->Perimetru();
			pointer->Arie();
			pointer->calcul_Robot1();
			pointer->calcul_Robot2();
			pointer->calcul_cost();
			v[i] = pointer->get_cost();
		}
		if (forma == "PATRAT")
		{
			double r;
			cin >> r;
			Patrat val(p1, p2, p3, cul, r, gros, pr, umplere);
			pointer = &val;
			pointer->Perimetru();
			pointer->Arie();
			pointer->calcul_Robot1();
			pointer->calcul_Robot2();
			pointer->calcul_cost();
			v[i] = pointer->get_cost();
		}
		if (forma == "DREPTUNGHI")
		{
			double lung, lat;
			cin >> lung >> lat;
			Dreptunghi val(p1, p2, p3, cul, lung, lat, gros, pr, umplere);
			pointer = &val;
			pointer->Perimetru();
			pointer->Arie();
			pointer->calcul_Robot1();
			pointer->calcul_Robot2();
			pointer->calcul_cost();
			v[i] = pointer->get_cost();
		}
		if (forma == "TRIUNGHI")
		{
			double lat, h;
			cin >> lat >> h;
			Triunghi val(p1, p2, p3, cul, lat, h, gros, pr, umplere);
			pointer = &val;
			pointer->Perimetru();
			pointer->Arie();
			pointer->calcul_Robot1();
			pointer->calcul_Robot2();
			pointer->calcul_cost();
			v[i] = pointer->get_cost();
		}
	//	cout << v[i] << " ";
	}
	//sortare(v, n);
//	int vsize = sizeof(v) / sizeof(v[0]);
	sort(v.begin(),v.end());
	for (int i = 0; i < n; i++)
		cout << fixed << setprecision(2) << v[i] << " "; 
	return 0;
}
