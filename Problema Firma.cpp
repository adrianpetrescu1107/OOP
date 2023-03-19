#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Productie
{
protected:
	map<string, double> produc;
public:
	void inserare_productie(string resursa_obtinuta, double cantitate_obtinuta)
	{
		produc.insert(pair<string, double>(resursa_obtinuta, cantitate_obtinuta));
	}
	virtual void productie() = 0;
};

class Prelucrare
{
protected:
	map<vector<string>, vector<double>> preluc;
public:
	void inserare_prelucrare(string r_veche, double X, string r_noua, double Y)
	{
		vector<string> v;
		v.push_back(r_veche);
		v.push_back(r_noua);
		vector<double> u;
		u.push_back(X);
		u.push_back(Y);
		preluc.insert(pair<vector<string>, vector<double>>(v,u));
	}
	virtual void prelucrare() = 0;
};

class Consum
{
protected:
	map<string, double> cons;
public:
	void inserare_consum(string resursa_consumata, double cantitate_consumata)
	{
		cons.insert(pair<string, double>(resursa_consumata, cantitate_consumata));
	}
	virtual void consum() = 0;
};

class Tara : public Productie, public Prelucrare, public Consum
{
public:
	string nume_tara, c_cumparare, c_vanzare;
	double bani_tara, bani_taxe;
	map<string, double> res_tara;
	int fericire;
	Tara(){}
	Tara(map<string,double> pret_res)
	{
		bani_tara = 0;
		fericire = 100;
		for (auto it = pret_res.begin(); it != pret_res.end(); it++)
		{
			res_tara.insert(pair<string, double>(it->first, 0));
		}
	}
	void atrib(map<string, double> pret_res)
	{
		bani_tara = 0;
		fericire = 100;
		for (auto it = pret_res.begin(); it != pret_res.end(); it++)
		{
			res_tara.insert(pair<string, double>(it->first, 0));
		}
	}
	void productie()
	{
		for (auto it = produc.begin(); it != produc.end(); it++)
			res_tara[it->first] += int((it->second * fericire) / 100);
	}
	void consum()
	{
		for (auto it = cons.begin(); it != cons.end(); it++)
		{
			if (res_tara[it->first] >= it->second)
				res_tara[it->first] = res_tara[it->first] - it->second;
			else
			{
				fericire = fericire - (it->second - res_tara[it->first]);
				res_tara[it->first] = 0;
			}
		}
	}
	void prelucrare()
	{
		for(auto it = preluc.begin(); it != preluc.end(); it++)
		{
			if (res_tara[it->first[0]] >= it->second[0])
			{
				res_tara[it->first[0]] = res_tara[it->first[0]] - it->second[0];
				res_tara[it->first[1]] += int((it->second[1] * fericire) / 100);
			}
		}
	}

	void verif_fericire()
	{
		if (fericire > 100)
			fericire = 100;
		if (fericire < 50)
			fericire = 50;
	}
	friend class Firma;
	void actiuni()
	{
		bani_tara += int((bani_taxe * fericire) / 100);
		productie();
		prelucrare();
		consum();
		fericire += 5;
		verif_fericire();
	}
	void afisare()
	{
		cout << nume_tara << " " << fericire << " " << bani_tara << endl;
		for (auto it = res_tara.begin(); it != res_tara.end(); it++)
		{
			if(it->second != 0)
				cout << it->first << " " << it->second << endl;
		}
		cout << endl;
	}
};
class Firma
{
public:
	double bani_firma;
	map<string, double> res_firma;
	Firma(){}
	Firma(map<string, double> pret_res, double B)
	{
		bani_firma = B;
		for (auto it = pret_res.begin(); it != pret_res.end(); it++)
		{
			res_firma.insert(pair<string, double>(it->first, 0));
		}
	}
};
int main()
{
	int n;
	cin >> n;
	map < string, double > pret_res;
	vector<string> sir(n);
	for (int i = 0; i < n; i++)
	{
		string s;
		cin >> s;
		sir[i] = s;
	}
	for (int i = 0; i < n; i++)
	{
		double s;
		cin >> s;
		pret_res.insert(pair<string, double>(sir[i], s));
	}
	double b;
	cin >> b;
	int k;
	cin >> k;
	vector<Tara> tari(k);
	for (int i = 0; i < k; i++)
	{
		tari[i].bani_tara = 0;
		tari[i].fericire = 100;
	}
	for (int i = 0; i < k; i++)
	{
		string nume_tara, c_cumparare, c_vanzare;
		double bani_taxe;
		cin >> nume_tara >> bani_taxe >> c_cumparare >> c_vanzare;
		tari[i].nume_tara = nume_tara;
		tari[i].bani_taxe = bani_taxe;
		tari[i].c_cumparare = c_cumparare;
		tari[i].c_vanzare = c_vanzare;
		tari[i].atrib(pret_res);
		int n_productie, n_prelucrare, n_consum;
		cin >> n_productie;
		for (int j = 0; j < n_productie; j++)
		{
			string resursa_obtinuta;
			double cantitate_obtinuta;
			cin >> resursa_obtinuta >> cantitate_obtinuta;
			tari[i].inserare_productie(resursa_obtinuta, cantitate_obtinuta);
		}
		cin >> n_prelucrare;
		for (int l = 0; l < n_prelucrare; l++)
		{
			string resursa_consumata, resursa_obtinuta;
			double cantitate_consumata, cantitate_obtinuta;
			cin >> resursa_consumata >> cantitate_consumata >> resursa_obtinuta >> cantitate_obtinuta;
			tari[i].inserare_prelucrare(resursa_consumata, cantitate_consumata, resursa_obtinuta, cantitate_obtinuta);
		}
		cin >> n_consum;
		for (int m = 0; m < n_consum; m++)
		{
			string resursa_consumata;
			double cantitate_consumata;
			cin >> resursa_consumata >> cantitate_consumata;
			tari[i].inserare_consum(resursa_consumata, cantitate_consumata);
		}
	}
	int d;
	cin >> d;
	for (int i = 0; i < d; i++)
	{
		string nume_tara;
		cin >> nume_tara;
		int n_cumparare, n_vanzare;
		cin >> n_cumparare;
		for (int j = 0; j < n_cumparare; j++)
		{
			string resursa;
			double cantitate;
			cin >> resursa >> cantitate;
		}
		cin >> n_vanzare;
		for (int l = 0; l < n_vanzare; l++)
		{
			string resursa;
			double cantitate;
			cin >> resursa >> cantitate;
		}
	}
	for (int i = 0; i < d; i++)
	{
		for (int j = 0; j < k; j++)
		{
			tari[j].actiuni();
			tari[j].afisare();
		}
	}
	return 0;
}
