#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

class Acvariu
{
protected:
	double pret, tip, gros, profit, cost_prod;
	string forma;
public:
	virtual double volum() = 0;
	virtual double arie() = 0;
	void calc_prof()
	{
		profit = pret * volum() - gros * tip * arie();
	}
	double get_prof()
	{
		return profit;
	}
};

class Cub : public Acvariu
{
protected:
	double lat;
public:
	Cub(double pr1, double l1, double gr1, double tip_p)
	{
		pret = pr1;
		lat = l1;
		gros = gr1;
		tip = tip_p;

	}
	double arie() override
	{
		return 6 * lat * lat;
	}

	double volum() override
	{
		return lat * lat * lat;
	}
	void afis()
	{
		cout << pret * volum() << " " << pret << " " << gros * pret * arie() << " " << volum() << " " << arie();
	}
};

class Paralelipiped : public Acvariu
{
protected:
	double h, l, w;
public:
	Paralelipiped(double pr1, double h1, double l1, double w1, double gr1, double pr_b)
	{
		pret = pr1;
		h = h1;
		w = w1;
		l = l1;
		gros = gr1;
		tip = pr_b;
	}
	double arie() override
	{
		return 2 * (l * w + h * l + h * w);
	}

	double volum() override
	{
		return h * l * w;
	}
};

class Cilindru : public Acvariu
{
protected:
	double r, h;
public:
	Cilindru(double pr1, double r1, double h1,  double gr1, double pr_b)
	{
		pret = pr1;
		r = r1;
		gros = gr1;
		h = h1;
		tip = pr_b;
	}
	double arie() override
	{
		return 2 * 3.141592653589793238 * r *(r+h);
	}

	double volum() override
	{
		return 3.141592653589793238 * r * r * h;
	}
	void afis()
	{
		cout << pret * volum() - gros * tip * arie() <<" " << pret * volum() << " " << pret << " " << gros * pret * arie() << " " << volum() << " " << arie();
	}
};

int main()
{
	double p1, p2, p3;
	cin >> p1 >> p2 >> p3;
	int n;
	cin >> n;
	vector<double> v;
	for (int i = 0; i < n; i++)
	{
		double pret, tip_pret, gros;
		string forma;
		cin >> pret >> forma;
		if (forma == "CUB")
		{
			double l, pret_bun;
			cin >> l;
			cin >> tip_pret >> gros;
			if (tip_pret == 1)
				pret_bun = p1;
			if (tip_pret == 2)
				pret_bun = p2;
			if (tip_pret == 3)
				pret_bun = p3;
			Cub ob(pret, l, gros, pret_bun);
			ob.calc_prof();
			v.push_back(ob.get_prof());
		//	ob.afis();
		}

		if (forma == "CILINDRU")
		{
			double h, r, pret_bun;
			cin >> h >> r;
			cin >> tip_pret >> gros;
			if (tip_pret == 1)
				pret_bun = p1;
			if (tip_pret == 2)
				pret_bun = p2;
			if (tip_pret == 3)
				pret_bun = p3;
			Cilindru ob(pret,r, h,  gros, pret_bun);
			ob.calc_prof();
			v.push_back(ob.get_prof());
			//ob.afis();
		}

		if (forma == "PARALELIPIPED")
		{
			double h, l,w, pret_bun;
			cin >> h >> l >> w;
			cin >> tip_pret >> gros;
			if (tip_pret == 1)
				pret_bun = p1;
			if (tip_pret == 2)
				pret_bun = p2;
			if (tip_pret == 3)
				pret_bun = p3;
			Paralelipiped ob(pret, h, l, w, gros, pret_bun);
			ob.calc_prof();
			v.push_back(ob.get_prof());
		}
	}
	sort(v.begin(), v.end(), greater<double>());

	for (int i = 0; i < n; i++)
	{
		cout <<fixed <<setprecision(2)<< v[i] << " ";
	}
	return 0;
}
