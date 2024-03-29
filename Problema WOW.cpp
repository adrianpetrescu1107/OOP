#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

class Caracter
{
	//protected:
public:
	string nume;
	int level, base_hp, base_atk, base_def, base_sp_atk, base_sp_def, base_spd;
	int hp_level, atk_level, def_level, sp_atk_level, sp_def_level, spd_level;
	int /*hp_stage,*/ atk_stage, def_stage, sp_atk_stage, sp_def_stage, spd_stage;
	int hp, atk, def, sp_atk, sp_def, spd;
	string mod;
	vector<string> spells;
	map<string, string> vraji_in_mapa; // map[spells[i]]
	int contor_spelluri;
	vector<int> stage;

	//public:
	Caracter() {}
	
	void set_stage()
	{
		for (int i = 0; i < 6; i++)
			stage.push_back(0);
	}

	void set_contor_spelluri()
	{
		contor_spelluri = 0;
	}

	void start_lupta()
	{
		hp_level = ((base_hp * level) / 50) + level + 10;
		atk_level = ((base_atk * level) / 50) + 10;
		def_level = ((base_def * level) / 50) + 10;
		sp_atk_level = ((base_sp_atk * level) / 50) + 10;
		sp_def_level = ((base_sp_def * level) / 50) + 10;
		spd_level = ((base_spd * level) / 50) + 10;
		hp = hp_level;
		atk = atk_level;
		def = def_level;
		sp_atk = sp_atk_level;
		sp_def = sp_def_level;
		spd = spd_level;
		//set_stage();
		for (int i = 0; i < 6; i++)
			stage[i] = 0;
		//contor_spelluri = 0;
	}
	void val_efective()
	{
		if (atk_stage >= 0)
			atk = (2 + atk_stage) * atk_level / 2;
		else
			atk = 2 * atk_level / (2 - atk_stage);

		if (def_stage >= 0)
			def = (2 + def_stage) * def_level / 2;
		else
			def = 2 * def_level / (2 - def_stage);

		if (sp_atk_stage >= 0)
			sp_atk = (2 + sp_atk_stage) * sp_atk_level / 2;
		else
			sp_atk = 2 * sp_atk_level / (2 - sp_atk_stage);

		if (sp_def_stage >= 0)
			sp_def = (2 + sp_def_stage) * sp_def_level / 2;
		else
			sp_def = 2 * sp_def_level / (2 - sp_def_stage);

		if (spd_stage >= 0)
			spd = (2 + spd_stage) * spd_level / 2;
		else
			spd = 2 * spd_level / (2 - spd_stage);
	}
	string abilitate_folosita()
	{
		if (mod == "USOR")
			return spells[0];
		if (mod == "MEDIU")
		{
			string x = spells[contor_spelluri];
			contor_spelluri++;
			if (contor_spelluri >= spells.size())
				contor_spelluri = 0;
			return x;
		}
		return "";
	}
	void citire_nume(string x)
	{
		nume = x;
	}

	void citire_level(int x)
	{
		level = x;
	}

	void citire_mod(string x)
	{
		mod = x;
	}

	void citire_spell(string x)
	{
		spells.push_back(x);
	}
	int get_hp()
	{
		return hp;
	}
	void afisare_player()
	{
		cout << nume << " " << level << " " << mod << " ";
		for (int i = 0; i < spells.size(); i++)
			cout << spells[i] << " ";
	}
	void base_stats(string caractere)
	{
		string line;
		ifstream car(caractere);
		if (car.is_open())
		{
			while (getline(car, line))
			{
				int i;
				string word = "";
				for (i = 0; i < line.size() && (line[i] != ' '); i++)
				{
					word = word + line[i];
				}
				if (word == nume)
				{
					string val = "";
					int count = 0;
					for (int j = i + 1; j < line.size(); j++)
					{
						if (line[j] == ' ')
						{
							if (count == 0)
							{
								base_hp = stoi(val);
							}
							if (count == 1)
							{
								base_atk = stoi(val);
							}
							if (count == 2)
							{
								base_def = stoi(val);
							}

							if (count == 3)
							{
								base_sp_atk = stoi(val);
							}
							if (count == 4)
							{
								base_sp_def = stoi(val);
							}
							count++;
							val = "";
						}
						else
							val = val + line[j];
					}

					base_spd = stoi(val);
				}
			}
		}
		car.close();
	}
	int get_spd()
	{
		return spd;
	}
	void vrajile_mele(string abilitati)
	{
		for (int poz = 0; poz < spells.size(); poz++)
		{
			string line;
			ifstream ab(abilitati);
			if (ab.is_open())
			{
				while (getline(ab, line))
				{
					int i;
					string word = "";
					for (i = 0; i < line.size() && (line[i] != ' '); i++)
					{
						word = word + line[i];
					}
					if (word == spells[poz])
					{
						string val = "";
						for (int j = i + 1; j < line.size(); j++)
						{
							val = val + line[j];
						}
						vraji_in_mapa.insert(pair < string, string >(spells[poz], val));
					}
				}
			}
			ab.close();
		}
	}

	void afisare()
	{
		cout << hp << " " << atk << " " << def << " " << sp_atk << " " << sp_def << " " << spd << endl;
	}
	virtual void xp(int lvl)
	{

	}
};

class Propriu : public Caracter
{
protected:
	int exp = 0;
public:
	Propriu() {}
	void xp(int lvl) override
	{
		exp = exp + lvl;
		if (exp >= 2 * level)
		{
			exp = exp - 2 * level;
			level = level + 1;

		}
		if (level > 100)
			level = 100;
	}
};

class Inamic : public Caracter
{
protected:

public:
	Inamic() {}
	void xp(int lvl) override
	{

	}
};

void lupta(Propriu& aliat, Inamic adversar)
{
	aliat.start_lupta();
	adversar.start_lupta();
	aliat.afisare();
	adversar.afisare();
	bool ok = false;
	//cout << aliat.stage[1] << " " << aliat.stage[2] << " " << aliat.stage[3] << " " << aliat.stage[4] << " " << aliat.stage[5] << endl;
	while (aliat.get_hp() > 0 && adversar.get_hp() > 0)
	{
		if (aliat.get_spd() >= adversar.get_spd())
		{
			//ce spell se utilizeaza, ales cu ajutorul lui mod, daca e usor o sa fie doar v[1], daca e mediu e v[i]
			vector<string> atribute1;
			string word1 = "";
			string abil1 = aliat.abilitate_folosita();
			for (int i = 0; i < aliat.vraji_in_mapa[abil1].size(); i++)
			{
				if (aliat.vraji_in_mapa[abil1][i] == ' ')
				{
					atribute1.push_back(word1);
					word1 = "";
				}
				else
				{
					word1 = word1 + aliat.vraji_in_mapa[abil1][i];
				}
			}
			atribute1.push_back(word1);

			for (int i = 0; i < atribute1.size(); i = i + 3)
			{
				if (atribute1[i] == "DMG" && aliat.hp > 0)
				{
					//atribute[i+1]=pwr
					//atribute[i+2]=type_atk
					int dmg = 1;
					if (atribute1[i + 2] == "ATK")
					{
						dmg = aliat.level * stoi(atribute1[i + 1]) * aliat.atk / (60 * adversar.def);
					}
					else
					{
						dmg = aliat.level * stoi(atribute1[i + 1]) * aliat.sp_atk / (60 * adversar.sp_def);
					}
					adversar.hp = adversar.hp - dmg;
					
				}
				/*for (int j = 0; j < atribute1.size(); j++)
					cout << atribute1[j] << " ";
				cout << endl;*/
			//	cout << atribute1[i] << endl;
				if (atribute1[i] == "SELF_MOD" && aliat.hp > 0)
				{
					//atribute[i+1] = atr
					//atribute[i+2] = stage
					int stage = stoi(atribute1[i + 2]);
					if (atribute1[i + 1] == "ATK")
					{
						aliat.stage[1] = aliat.stage[1] + stage;
						if (aliat.stage[1] < -6)
							aliat.stage[1] = -6;
						if (aliat.stage[1] > 6)
							aliat.stage[1] = 6;
						if (aliat.stage[1] >= 0)
							aliat.atk = (2 + aliat.stage[1]) * aliat.atk_level / 2;
						else
							aliat.atk = 2 * aliat.atk_level / (2 - aliat.stage[1]);
					}

					if (atribute1[i + 1] == "DEF")
					{
						aliat.stage[2] = aliat.stage[2] + stage;
						if (aliat.stage[2] < -6)
							aliat.stage[2] = -6;
						if (aliat.stage[2] > 6)
							aliat.stage[2] = 6;
						if (aliat.stage[2] >= 0)
							aliat.def = (2 + aliat.stage[2]) * aliat.def_level / 2;
						else
							aliat.def = 2 * aliat.def_level / (2 - aliat.stage[2]);
					}

					if (atribute1[i + 1] == "SP_ATK")
					{
						aliat.stage[3] = aliat.stage[3] + stage;
						if (aliat.stage[3] < -6)
							aliat.stage[3] = -6;
						if (aliat.stage[3] > 6)
							aliat.stage[3] = 6;
						if (aliat.stage[3] >= 0)
							aliat.sp_atk = (2 + aliat.stage[3]) * aliat.sp_atk_level / 2;
						else
							aliat.sp_atk = 2 * aliat.sp_atk_level / (2 - aliat.stage[3]);
					}

					if (atribute1[i + 1] == "SP_DEF")
					{
						aliat.stage[4] = aliat.stage[4] + stage;
						if (aliat.stage[4] < -6)
							aliat.stage[4] = -6;
						if (aliat.stage[4] > 6)
							aliat.stage[4] = 6;
						if (aliat.stage[4] >= 0)
							aliat.sp_def = (2 + aliat.stage[4]) * aliat.sp_def_level / 2;
						else
							aliat.sp_def = 2 * aliat.sp_def_level / (2 - aliat.stage[4]);
					}

					if (atribute1[i + 1] == "SPD")
					{
						aliat.stage[5] = aliat.stage[5] + stage;
						//cout << atribute1[i+2] << endl;
						if (aliat.stage[5] < -6)
							aliat.stage[5] = -6;
						if (aliat.stage[5] > 6)
							aliat.stage[5] = 6;
						if (aliat.stage[5] >= 0)
							aliat.spd = (2 + aliat.stage[5]) * aliat.spd_level / 2;
						else
							aliat.spd = 2 * aliat.spd_level / (2 - aliat.stage[5]);
					}
				//	cout << stage << endl;
				}

				if (atribute1[i] == "ENEMY_MOD" && adversar.hp > 0 && aliat.hp > 0)
				{
					//atribute[i+1] = atr
					//atribute[i+2] = stage
					int stage = stoi(atribute1[i + 2]);
					if (atribute1[i + 1] == "ATK")
					{
						adversar.stage[1] = adversar.stage[1] + stage;
						if (adversar.stage[1] < -6)
							adversar.stage[1] = -6;
						if (adversar.stage[1] > 6)
							adversar.stage[1] = 6;
						if (adversar.stage[1] >= 0)
							adversar.atk = (2 + adversar.stage[1]) * adversar.atk_level / 2;
						else
							adversar.atk = 2 * adversar.atk_level / (2 - adversar.stage[1]);
					}

					if (atribute1[i + 1] == "DEF")
					{
						adversar.stage[2] = adversar.stage[2] + stage;
						if (adversar.stage[2] < -6)
							adversar.stage[2] = -6;
						if (adversar.stage[2] > 6)
							adversar.stage[2] = 6;
						if (adversar.stage[2] >= 0)
							adversar.def = (2 + adversar.stage[2]) * adversar.def_level / 2;
						else
							adversar.def = 2 * adversar.def_level / (2 - adversar.stage[2]);
					}

					if (atribute1[i + 1] == "SP_ATK")
					{
						adversar.stage[3] = adversar.stage[3] + stage;
						if (adversar.stage[3] < -6)
							adversar.stage[3] = -6;
						if (adversar.stage[3] > 6)
							adversar.stage[3] = 6;
						if (adversar.stage[3] >= 0)
							adversar.sp_atk = (2 + adversar.stage[3]) * adversar.sp_atk_level / 2;
						else
							adversar.sp_atk = 2 * adversar.sp_atk_level / (2 - adversar.stage[3]);
					}

					if (atribute1[i + 1] == "SP_DEF")
					{
						adversar.stage[4] = adversar.stage[4] + stage;
						if (adversar.stage[4] < -6)
							adversar.stage[4] = -6;
						if (adversar.stage[4] > 6)
							adversar.stage[4] = 6;
						if (adversar.stage[4] >= 0)
							adversar.sp_def = (2 + adversar.stage[4]) * adversar.sp_def_level / 2;
						else
							adversar.sp_def = 2 * adversar.sp_def_level / (2 - adversar.stage[4]);
					}

					if (atribute1[i + 1] == "SPD")
					{
						adversar.stage[5] = adversar.stage[5] + stage;
						if (adversar.stage[5] < -6)
							adversar.stage[5] = -6;
						if (adversar.stage[5] > 6)
							adversar.stage[5] = 6;
						if (adversar.stage[5] >= 0)
							adversar.spd = (2 + adversar.stage[5]) * adversar.spd_level / 2;
						else
							adversar.spd = 2 * adversar.spd_level / (2 - adversar.stage[5]);
					}
				}
			/*	if ((adversar.hp <= 0 || aliat.hp <= 0) && ok == false)
				{
					aliat.afisare();
					adversar.afisare();
					ok = true;
					break;
				}*/
			}

			// INAMICCCCCC
			//ce spell se utilizeaza, ales cu ajutorul lui mod, daca e usor o sa fie doar v[1], daca e mediu e v[i]
			vector<string> atribute2;
			string word2 = "";
			string abil2 = adversar.abilitate_folosita();
			for (int i = 0; i < adversar.vraji_in_mapa[abil2].size(); i++)
			{
				if (adversar.vraji_in_mapa[abil2][i] == ' ')
				{
					atribute2.push_back(word2);
					word2 = "";
				}
				else
				{
					word2 = word2 + adversar.vraji_in_mapa[abil2][i];
				}
			}
			atribute2.push_back(word2);

			for (int i = 0; i < atribute2.size(); i = i + 3)
			{
				if (atribute2[i] == "DMG" && adversar.hp > 0)
				{
					//atribute[i+1]=pwr
					//atribute[i+2]=type_atk
					int dmg = 1;
					if (atribute2[i + 2] == "ATK")
					{
						dmg = adversar.level * stoi(atribute2[i + 1]) * adversar.atk / (60 * aliat.def);
					}
					else
					{
						dmg = adversar.level * stoi(atribute2[i + 1]) * adversar.sp_atk / (60 * aliat.sp_def);
					}
					aliat.hp = aliat.hp - dmg;

				}
				if (atribute2[i] == "SELF_MOD"  && adversar.hp > 0)
				{
					//atribute[i+1] = atr
					//atribute[i+2] = stage
					int stage = stoi(atribute2[i + 2]);
					if (atribute2[i + 1] == "ATK")
					{
						adversar.stage[1] = adversar.stage[1] + stage;
						if (adversar.stage[1] < -6)
							adversar.stage[1] = -6;
						if (adversar.stage[1] > 6)
							adversar.stage[1] = 6;
						if (adversar.stage[1] >= 0)
							adversar.atk = (2 + adversar.stage[1]) * adversar.atk_level / 2;
						else
							adversar.atk = 2 * adversar.atk_level / (2 - adversar.stage[1]);
					}

					if (atribute2[i + 1] == "DEF")
					{
						adversar.stage[2] = adversar.stage[2] + stage;
						if (adversar.stage[2] < -6)
							adversar.stage[2] = -6;
						if (adversar.stage[2] > 6)
							adversar.stage[2] = 6;
						if (adversar.stage[2] >= 0)
							adversar.def = (2 + adversar.stage[2]) * adversar.def_level / 2;
						else
							adversar.def = 2 * adversar.def_level / (2 - adversar.stage[2]);
					}

					if (atribute2[i + 1] == "SP_ATK")
					{
						adversar.stage[3] = adversar.stage[3] + stage;
						if (adversar.stage[3] < -6)
							adversar.stage[3] = -6;
						if (adversar.stage[3] > 6)
							adversar.stage[3] = 6;
						if (adversar.stage[3] >= 0)
							adversar.sp_atk = (2 + adversar.stage[3]) * adversar.sp_atk_level / 2;
						else
							adversar.sp_atk = 2 * adversar.sp_atk_level / (2 - adversar.stage[3]);
					}

					if (atribute2[i + 1] == "SP_DEF")
					{
						adversar.stage[4] = adversar.stage[4] + stage;
						if (adversar.stage[4] < -6)
							adversar.stage[4] = -6;
						if (adversar.stage[4] > 6)
							adversar.stage[4] = 6;
						if (adversar.stage[4] >= 0)
							adversar.sp_def = (2 + adversar.stage[4]) * adversar.sp_def_level / 2;
						else
							adversar.sp_def = 2 * adversar.sp_def_level / (2 - adversar.stage[4]);
					}

					if (atribute2[i + 1] == "SPD")
					{
						adversar.stage[5] = adversar.stage[5] + stage;
						if (adversar.stage[5] < -6)
							adversar.stage[5] = -6;
						if (adversar.stage[5] > 6)
							adversar.stage[5] = 6;
						if (adversar.stage[5] >= 0)
							adversar.spd = (2 + adversar.stage[5]) * adversar.spd_level / 2;
						else
							adversar.spd = 2 * adversar.spd_level / (2 - adversar.stage[5]);
					}
				}

				if (atribute2[i] == "ENEMY_MOD" && aliat.hp > 0 && adversar.hp > 0)
				{
					//atribute[i+1] = atr
					//atribute[i+2] = stage
					int stage = stoi(atribute2[i + 2]);
					if (atribute2[i + 1] == "ATK")
					{
						aliat.stage[1] = aliat.stage[1] + stage;
						if (aliat.stage[1] < -6)
							aliat.stage[1] = -6;
						if (aliat.stage[1] > 6)
							aliat.stage[1] = 6;
						if (aliat.stage[1] >= 0)
							aliat.atk = (2 + aliat.stage[1]) * aliat.atk_level / 2;
						else
							aliat.atk = 2 * aliat.atk_level / (2 - aliat.stage[1]);
					}

					if (atribute2[i + 1] == "DEF")
					{
						aliat.stage[2] = aliat.stage[2] + stage;
						if (aliat.stage[2] < -6)
							aliat.stage[2] = -6;
						if (aliat.stage[2] > 6)
							aliat.stage[2] = 6;
						if (aliat.stage[2] >= 0)
							aliat.def = (2 + aliat.stage[2]) * aliat.def_level / 2;
						else
							aliat.def = 2 * aliat.def_level / (2 - aliat.stage[2]);
					}

					if (atribute2[i + 1] == "SP_ATK")
					{
						aliat.stage[3] = aliat.stage[3] + stage;
						if (aliat.stage[3] < -6)
							aliat.stage[3] = -6;
						if (aliat.stage[3] > 6)
							aliat.stage[3] = 6;
						if (aliat.stage[3] >= 0)
							aliat.sp_atk = (2 + aliat.stage[3]) * aliat.sp_atk_level / 2;
						else
							aliat.sp_atk = 2 * aliat.sp_atk_level / (2 - aliat.stage[3]);
					}

					if (atribute2[i + 1] == "SP_DEF")
					{
						aliat.stage[4] = aliat.stage[4] + stage;
						if (aliat.stage[4] < -6)
							aliat.stage[4] = -6;
						if (aliat.stage[4] > 6)
							aliat.stage[4] = 6;
						if (aliat.stage[4] >= 0)
							aliat.sp_def = (2 + aliat.stage[4]) * aliat.sp_def_level / 2;
						else
							aliat.sp_def = 2 * aliat.sp_def_level / (2 - aliat.stage[4]);
					}

					if (atribute2[i + 1] == "SPD")
					{
						aliat.stage[5] = aliat.stage[5] + stage;
						if (aliat.stage[5] < -6)
							aliat.stage[5] = -6;
						if (aliat.stage[5] > 6)
							aliat.stage[5] = 6;
						if (aliat.stage[5] >= 0)
							aliat.spd = (2 + aliat.stage[5]) * aliat.spd_level / 2;
						else
							aliat.spd = 2 * aliat.spd_level / (2 - aliat.stage[5]);
					}
				}
				/*if ((aliat.hp <= 0 || adversar.hp <= 0) && ok == false)
				{
					aliat.afisare();
					adversar.afisare();
					ok = true;
					break;
				}*/
			}

		}
		else
		{

			vector<string> atribute3;
			string word3 = "";
			string abil3 = adversar.abilitate_folosita();
			for (int i = 0; i < adversar.vraji_in_mapa[abil3].size(); i++)
			{
				if (adversar.vraji_in_mapa[abil3][i] == ' ')
				{
					atribute3.push_back(word3);
					word3 = "";
				}
				else
				{
					word3 = word3 + adversar.vraji_in_mapa[abil3][i];
				}
			}
			atribute3.push_back(word3);
			//cout << atribute3[0] << atribute3[1] << atribute3[2] << endl;
			for (int i = 0; i < atribute3.size(); i = i + 3)
			{
				if (atribute3[i] == "DMG" && adversar.hp > 0)
				{
					//atribute[i+1]=pwr
					//atribute[i+2]=type_atk
					int dmg = 1;
					if (atribute3[i + 2] == "ATK")
					{
						dmg = adversar.level * stoi(atribute3[i + 1]) * adversar.atk / (60 * aliat.def);
					}
					else
					{
						dmg = adversar.level * stoi(atribute3[i + 1]) * adversar.sp_atk / (60 * aliat.sp_def);
					}
					aliat.hp = aliat.hp - dmg;

				}
				if (atribute3[i] == "SELF_MOD"  && adversar.hp > 0)
				{
					//atribute[i+1] = atr
					//atribute[i+2] = stage
					int stage = stoi(atribute3[i + 2]);
					if (atribute3[i + 1] == "ATK")
					{
						adversar.stage[1] = adversar.stage[1] + stage;
						if (adversar.stage[1] < -6)
							adversar.stage[1] = -6;
						if (adversar.stage[1] > 6)
							adversar.stage[1] = 6;
						if (adversar.stage[1] >= 0)
							adversar.atk = (2 + adversar.stage[1]) * adversar.atk_level / 2;
						else
							adversar.atk = 2 * adversar.atk_level / (2 - adversar.stage[1]);
					}

					if (atribute3[i + 1] == "DEF")
					{
						adversar.stage[2] = adversar.stage[2] + stage;
						if (adversar.stage[2] < -6)
							adversar.stage[2] = -6;
						if (adversar.stage[2] > 6)
							adversar.stage[2] = 6;
						if (adversar.stage[2] >= 0)
							adversar.def = (2 + adversar.stage[2]) * adversar.def_level / 2;
						else
							adversar.def = 2 * adversar.def_level / (2 - adversar.stage[2]);
					}

					if (atribute3[i + 1] == "SP_ATK")
					{
						adversar.stage[3] = adversar.stage[3] + stage;
						if (adversar.stage[3] < -6)
							adversar.stage[3] = -6;
						if (adversar.stage[3] > 6)
							adversar.stage[3] = 6;
						if (adversar.stage[3] >= 0)
							adversar.sp_atk = (2 + adversar.stage[3]) * adversar.sp_atk_level / 2;
						else
							adversar.sp_atk = 2 * adversar.sp_atk_level / (2 - adversar.stage[3]);
					}

					if (atribute3[i + 1] == "SP_DEF")
					{
						adversar.stage[4] = adversar.stage[4] + stage;
						if (adversar.stage[4] < -6)
							adversar.stage[4] = -6;
						if (adversar.stage[4] > 6)
							adversar.stage[4] = 6;
						if (adversar.stage[4] >= 0)
							adversar.sp_def = (2 + adversar.stage[4]) * adversar.sp_def_level / 2;
						else
							adversar.sp_def = 2 * adversar.sp_def_level / (2 - adversar.stage[4]);
					}

					if (atribute3[i + 1] == "SPD")
					{
						adversar.stage[5] = adversar.stage[5] + stage;
						if (adversar.stage[5] < -6)
							adversar.stage[5] = -6;
						if (adversar.stage[5] > 6)
							adversar.stage[5] = 6;
						if (adversar.stage[5] >= 0)
							adversar.spd = (2 + adversar.stage[5]) * adversar.spd_level / 2;
						else
							adversar.spd = 2 * adversar.spd_level / (2 - adversar.stage[5]);
					}
				}

				if (atribute3[i] == "ENEMY_MOD" && adversar.hp > 0 && aliat.hp > 0)
				{
					//atribute[i+1] = atr
					//atribute[i+2] = stage
					int stage = stoi(atribute3[i + 2]);
					if (atribute3[i + 1] == "ATK")
					{
						aliat.stage[1] = aliat.stage[1] + stage;
						if (aliat.stage[1] < -6)
							aliat.stage[1] = -6;
						if (aliat.stage[1] > 6)
							aliat.stage[1] = 6;
						if (aliat.stage[1] >= 0)
							aliat.atk = (2 + aliat.stage[1]) * aliat.atk_level / 2;
						else
							aliat.atk = 2 * aliat.atk_level / (2 - aliat.stage[1]);
					}

					if (atribute3[i + 1] == "DEF")
					{
						aliat.stage[2] = aliat.stage[2] + stage;
						if (aliat.stage[2] < -6)
							aliat.stage[2] = -6;
						if (aliat.stage[2] > 6)
							aliat.stage[2] = 6;
						if (aliat.stage[2] >= 0)
							aliat.def = (2 + aliat.stage[2]) * aliat.def_level / 2;
						else
							aliat.def = 2 * aliat.def_level / (2 - aliat.stage[2]);
					}

					if (atribute3[i + 1] == "SP_ATK")
					{
						aliat.stage[3] = aliat.stage[3] + stage;
						//cout << aliat.stage[3] << endl;
						if (aliat.stage[3] < -6)
							aliat.stage[3] = -6;
						if (aliat.stage[3] > 6)
							aliat.stage[3] = 6;
						if (aliat.stage[3] >= 0)
							aliat.sp_atk = (2 + aliat.stage[3]) * aliat.sp_atk_level / 2;
						else
							aliat.sp_atk = 2 * aliat.sp_atk_level / (2 - aliat.stage[3]);
					}
					//cout << aliat.stage[3] << " " << aliat.sp_atk_level << " " << aliat.sp_atk << endl;

					if (atribute3[i + 1] == "SP_DEF")
					{
						aliat.stage[4] = aliat.stage[4] + stage;
						if (aliat.stage[4] < -6)
							aliat.stage[4] = -6;
						if (aliat.stage[4] > 6)
							aliat.stage[4] = 6;
						if (aliat.stage[4] >= 0)
							aliat.sp_def = (2 + aliat.stage[4]) * aliat.sp_def_level / 2;
						else
							aliat.sp_def = 2 * aliat.sp_def_level / (2 - aliat.stage[4]);
					}

					if (atribute3[i + 1] == "SPD")
					{
						aliat.stage[5] = aliat.stage[5] + stage;
						if (aliat.stage[5] < -6)
							aliat.stage[5] = -6;
						if (aliat.stage[5] > 6)
							aliat.stage[5] = 6;
						if (aliat.stage[5] >= 0)
							aliat.spd = (2 + aliat.stage[5]) * aliat.spd_level / 2;
						else
							aliat.spd = 2 * aliat.spd_level / (2 - aliat.stage[5]);
					}
				}
				/*if ((aliat.hp <= 0 || adversar.hp <= 0) && ok == false)
				{
					aliat.afisare();
					adversar.afisare();
					ok = true;
					break;
				}*/
			}



			// ALIATTT

			vector<string> atribute4;
			string word4 = "";
			string abil4 = aliat.abilitate_folosita();
			for (int i = 0; i < aliat.vraji_in_mapa[abil4].size(); i++)
			{
				if (aliat.vraji_in_mapa[abil4][i] == ' ')
				{
					atribute4.push_back(word4);
					word4 = "";
				}
				else
				{
					word4 = word4 + aliat.vraji_in_mapa[abil4][i];
				}
			}
			atribute4.push_back(word4);
		//	cout << abil4 << endl;
			for (int i = 0; i < atribute4.size(); i = i + 3)
			{
				if (atribute4[i] == "DMG" && aliat.hp > 0)
				{
					//atribute[i+1]=pwr
					//atribute[i+2]=type_atk
					int dmg = 1;
					if (atribute4[i + 2] == "ATK")
					{
						dmg = aliat.level * stoi(atribute4[i + 1]) * aliat.atk / (60 * adversar.def);
					}
					else
					{
						dmg = aliat.level * stoi(atribute4[i + 1]) * aliat.sp_atk / (60 * adversar.sp_def);
					}
					adversar.hp = adversar.hp - dmg;
				}
				if (atribute4[i] == "SELF_MOD"  && aliat.hp > 0)
				{
					//atribute[i+1] = atr
					//atribute[i+2] = stage
					int stage = stoi(atribute4[i + 2]);
					if (atribute4[i + 1] == "ATK")
					{
						aliat.stage[1] = aliat.stage[1] + stage;
						if (aliat.stage[1] < -6)
							aliat.stage[1] = -6;
						if (aliat.stage[1] > 6)
							aliat.stage[1] = 6;
						if (aliat.stage[1] >= 0)
							aliat.atk = (2 + aliat.stage[1]) * aliat.atk_level / 2;
						else
							aliat.atk = 2 * aliat.atk_level / (2 - aliat.stage[1]);
					}

					if (atribute4[i + 1] == "DEF")
					{
						aliat.stage[2] = aliat.stage[2] + stage;
						if (aliat.stage[2] < -6)
							aliat.stage[2] = -6;
						if (aliat.stage[2] > 6)
							aliat.stage[2] = 6;
						if (aliat.stage[2] >= 0)
							aliat.def = (2 + aliat.stage[2]) * aliat.def_level / 2;
						else
							aliat.def = 2 * aliat.def_level / (2 - aliat.stage[2]);
					}

					if (atribute4[i + 1] == "SP_ATK")
					{
						aliat.stage[3] = aliat.stage[3] + stage;
						if (aliat.stage[3] < -6)
							aliat.stage[3] = -6;
						if (aliat.stage[3] > 6)
							aliat.stage[3] = 6;
						if (aliat.stage[3] >= 0)
							aliat.sp_atk = (2 + aliat.stage[3]) * aliat.sp_atk_level / 2;
						else
							aliat.sp_atk = 2 * aliat.sp_atk_level / (2 - aliat.stage[3]);
					}

					if (atribute4[i + 1] == "SP_DEF")
					{
						aliat.stage[4] = aliat.stage[4] + stage;
						if (aliat.stage[4] < -6)
							aliat.stage[4] = -6;
						if (aliat.stage[4] > 6)
							aliat.stage[4] = 6;
						if (aliat.stage[4] >= 0)
							aliat.sp_def = (2 + aliat.stage[4]) * aliat.sp_def_level / 2;
						else
							aliat.sp_def = 2 * aliat.sp_def_level / (2 - aliat.stage[4]);
					}

					if (atribute4[i + 1] == "SPD")
					{
						aliat.stage[5] = aliat.stage[5] + stage;
						if (aliat.stage[5] < -6)
							aliat.stage[5] = -6;
						if (aliat.stage[5] > 6)
							aliat.stage[5] = 6;
						if (aliat.stage[5] >= 0)
							aliat.spd = (2 + aliat.stage[5]) * aliat.spd_level / 2;
						else
							aliat.spd = 2 * aliat.spd_level / (2 - aliat.stage[5]);
					}
				}

				if (atribute4[i] == "ENEMY_MOD"  && aliat.hp > 0 && adversar.hp > 0)
				{
					//atribute[i+1] = atr
					//atribute[i+2] = stage
					int stage = stoi(atribute4[i + 2]);
					if (atribute4[i + 1] == "ATK")
					{
						adversar.stage[1] = adversar.stage[1] + stage;
						if (adversar.stage[1] < -6)
							adversar.stage[1] = -6;
						if (adversar.stage[1] > 6)
							adversar.stage[1] = 6;
						if (adversar.stage[1] >= 0)
							adversar.atk = (2 + adversar.stage[1]) * adversar.atk_level / 2;
						else
							adversar.atk = 2 * adversar.atk_level / (2 - adversar.stage[1]);
					}

					if (atribute4[i + 1] == "DEF")
					{
						adversar.stage[2] = adversar.stage[2] + stage;
						if (adversar.stage[2] < -6)
							adversar.stage[2] = -6;
						if (adversar.stage[2] > 6)
							adversar.stage[2] = 6;
						if (adversar.stage[2] >= 0)
							adversar.def = (2 + adversar.stage[2]) * adversar.def_level / 2;
						else
							adversar.def = 2 * adversar.def_level / (2 - adversar.stage[2]);
					}

					if (atribute4[i + 1] == "SP_ATK")
					{
						adversar.stage[3] = adversar.stage[3] + stage;
						if (adversar.stage[3] < -6)
							adversar.stage[3] = -6;
						if (adversar.stage[3] > 6)
							adversar.stage[3] = 6;
						if (adversar.stage[3] >= 0)
							adversar.sp_atk = (2 + adversar.stage[3]) * adversar.sp_atk_level / 2;
						else
							adversar.sp_atk = 2 * adversar.sp_atk_level / (2 - adversar.stage[3]);
					}

					if (atribute4[i + 1] == "SP_DEF")
					{
						adversar.stage[4] = adversar.stage[4] + stage;
						if (adversar.stage[4] < -6)
							adversar.stage[4] = -6;
						if (adversar.stage[4] > 6)
							adversar.stage[4] = 6;
						if (adversar.stage[4] >= 0)
							adversar.sp_def = (2 + adversar.stage[4]) * adversar.sp_def_level / 2;
						else
							adversar.sp_def = 2 * adversar.sp_def_level / (2 - adversar.stage[4]);
					}

					if (atribute4[i + 1] == "SPD")
					{
						adversar.stage[5] = adversar.stage[5] + stage;
						if (adversar.stage[5] < -6)
							adversar.stage[5] = -6;
						if (adversar.stage[5] > 6)
							adversar.stage[5] = 6;
						if (adversar.stage[5] >= 0)
							adversar.spd = (2 + adversar.stage[5]) * adversar.spd_level / 2;
						else
							adversar.spd = 2 * adversar.spd_level / (2 - adversar.stage[5]);
					}
				}
				/*if ((adversar.hp <= 0 || aliat.hp <= 0) && ok == false)
				{
					aliat.afisare();
					adversar.afisare();
					ok = true;
					break;
				}*/
			}
		}
	//	cout << aliat.stage[3] << endl;
		if (ok == false)
		{
			aliat.afisare();
			adversar.afisare();
		}
	}
	if (aliat.hp > 0)
		aliat.xp(adversar.level);
	//cout << aliat.stage[3] << endl;
	//cout << aliat.stage[1] << " " << aliat.stage[2] << " " << aliat.stage[3] << " " << aliat.stage[4] << " " << aliat.stage[5] << endl;

}

int main()
{
	string caractere;//wow.txt
	getline(cin, caractere);
	string abilitati;//test.txt
	getline(cin, abilitati);

	string sir;
	int index = -1;

	Propriu aliat;
	vector<Inamic> inamici;
	while (getline(cin, sir))
	{
		int count = 0;
		string word = "";
		Inamic om_rau;
		for (int i = 0; i < sir.size(); i++)
		{
			if (sir[i] == ' ')
			{
				if (index == -1)
				{
					if (count == 0)
						aliat.citire_nume(word);
					if (count == 1)
						aliat.citire_level(stoi(word));
					if (count == 2)
						aliat.citire_mod(word);
					if (count >= 3)
						aliat.citire_spell(word);
				}
				else
				{
					if (count == 0)
						om_rau.citire_nume(word);
					if (count == 1)
						om_rau.citire_level(stoi(word));
					if (count == 2)
						om_rau.citire_mod(word);
					if (count >= 3)
						om_rau.citire_spell(word);
				}
				count++;
				word = "";
			}
			else
				word = word + sir[i];
		}
		if (index > -1)
		{
			om_rau.citire_spell(word);
			om_rau.base_stats(caractere);
			om_rau.vrajile_mele(abilitati);
			inamici.push_back(om_rau);
		}
		if (index == -1)
		{
			aliat.citire_spell(word);
			aliat.base_stats(caractere);
			aliat.vrajile_mele(abilitati);
			aliat.set_stage();
		}
		index++;
	}
	for (int i = 0; i < inamici.size(); i++)
	{
		inamici[i].set_stage();
		inamici[i].set_contor_spelluri();
		lupta(aliat, inamici[i]);
		cout << endl;
	}


	return 0;
}
/*
PHYSICAL_15 DMG 15 ATK
PHYSICAL_30 DMG 30 ATK
PHYSICAL_45 DMG 45 ATK
PHYSICAL_60 DMG 60 ATK
PHYSICAL_90 DMG 90 ATK
SPECIAL_15 DMG 15 SP_ATK
SPECIAL_30 DMG 30 SP_ATK
SPECIAL_45 DMG 45 SP_ATK
SPECIAL_60 DMG 60 SP_ATK
SPECIAL_90 DMG 90 SP_ATK
ATK_SELF_BUFF_1 SELF_MOD ATK 1
DEF_SELF_BUFF_1 SELF_MOD DEF 1
SP_ATK_SELF_BUFF_1 SELF_MOD SP_ATK 1
SP_DEF_SELF_BUFF_1 SELF_MOD SP_DEF 1
SPD_SELF_BUFF_1 SELF_MOD SPD 1
ATK_SELF_DEBUFF_1 SELF_MOD ATK -1
DEF_SELF_DEBUFF_1 SELF_MOD DEF -1
SP_ATK_SELF_DEBUFF_1 SELF_MOD SP_ATK -1
SP_DEF_SELF_DEBUFF_1 SELF_MOD SP_DEF -1
SPD_SELF_DEBUFF_1 SELF_MOD SPD -1
ATK_ENEMY_BUFF_1 ENEMY_MOD ATK 1
DEF_ENEMY_BUFF_1 ENEMY_MOD DEF 1
SP_ATK_ENEMY_BUFF_1 ENEMY_MOD SP_ATK 1
SP_DEF_ENEMY_BUFF_1 ENEMY_MOD SP_DEF 1
SPD_ENEMY_BUFF_1 ENEMY_MOD SPD 1
ATK_ENEMY_DEBUFF_1 ENEMY_MOD ATK -1
DEF_ENEMY_DEBUFF_1 ENEMY_MOD DEF -1
SP_ATK_ENEMY_DEBUFF_1 ENEMY_MOD SP_ATK -1
SP_DEF_ENEMY_DEBUFF_1 ENEMY_MOD SP_DEF -1
SPD_ENEMY_DEBUFF_1 ENEMY_MOD SPD -1
RND_SELF_BUFF_1 SELF_MOD ATK 3
RND_SELF_BUFF_2 SELF_MOD SPD 2
RND_SELF_BUFF_3 SELF_MOD SP_DEF 15
RND_SELF_DEBUFF_1 SELF_MOD SP_ATK -5
RND_SELF_DEBUFF_2 SELF_MOD ATK -4
RND_SELF_DEBUFF_3 SELF_MOD SPD -20
RND_ENEMY_BUFF_1 ENEMY_MOD SP_ATK 4
RND_ENEMY_BUFF_2 ENEMY_MOD DEF 2
RND_ENEMY_BUFF_3 ENEMY_MOD SPD 19
RND_ENEMY_DEBUFF_1 ENEMY_MOD ATK -3
RND_ENEMY_DEBUFF_2 ENEMY_MOD SPD -2
RND_ENEMY_DEBUFF_3 ENEMY_MOD SP_DEF -18
CLOSE_COMBAT SELF_MOD DEF -1 SELF_MOD SP_DEF -1 DMG 120 ATK
EXTREME_SPEED DMG 90 ATK SELF_MOD SPD 1
CRUNCH DMG 60 ATK ENEMY_MOD SP_DEF -1
FIRE_LASH DMG 60 SP_ATK ENEMY_MOD DEF -1
SEED_FLARE DMG 45 SP_ATK ENEMY_MOD SP_DEF -2
DRAGON_ASCENT SELF_MOD ATK -1 SELF_MOD SP_ATK -1 DMG 120 ATK
OVERHEAT DMG 120 SP_ATK SELF_MOD SP_ATK -2
V_CREATE DMG 150 ATK SELF_MOD SPD -1 SELF_MOD ATK -1 SELF_MOD DEF -1 SELF_MOD SP_DEF -1
ICE_HAMMER DMG 90 ATK SELF_MOD SPD -1
NOBLE_ROAR DMG 45 ATK ENEMY_MOD ATK -1 ENEMY_MOD SP_ATK -1
MEMENTO DMG 15 SP_ATK ENEMY_MOD ATK -2 ENEMY_MOD SP_ATK -2
BUBBLE DMG 60 SP_ATK ENEMY_MOD SPD -1
BREAK_THROUGH DMG 45 SP_ATK ENEMY_MOD SPD -1 ENEMY_MOD DEF -1

THRALL 80 82 83 100 100 80
GARROSH 78 84 78 109 85 100
EITRIGG 79 83 100 85 105 78
VARIAN 60 45 50 80 80 70
JAINA 65 80 40 45 80 75
GENN 83 80 75 70 70 91
MALFURION 55 81 60 50 70 97
BOLVAR 60 85 69 65 79 80
UTHER 60 90 55 90 80 110
SYLVANAS 90 82 87 75 85 76
LORTHEMAR 81 92 77 85 75 85
TERENAS 95 70 73 85 90 60
CAIRNE 73 76 75 81 100 100
BAINE 75 80 85 100 90 50
VOLJIN 70 65 60 90 75 90
DUROTAN 35 80 50 50 70 120
VELEN 90 110 80 100 80 95
ANDUIN 90 85 95 70 90 70
TYRANDE 55 50 45 135 85 120
ARTHAS 90 130 80 65 85 55
TIRION 80 105 65 100 60 70
KELTHUZAD 80 70 65 80 120 100
MAGNI 80 110 130 55 65 45
BRAN 65 100 70 80 80 105
GARRONA 90 70 80 70 95 70
TALANJI 50 95 180 85 45 70
HELLSCREAM 60 65 60 130 75 110
MALGANIS 55 130 110 50 50 75
NATHANOS 95 95 85 125 65 55
KAELTHAS 80 92 65 65 80 68
MAIEV 60 75 85 100 85 115
GULDAN 70 130 100 55 80 65
ILLIDAN 95 125 79 60 100 81
VAROK 91 134 95 100 100 80
TEST_30_WOW 30 30 30 30 30 30
TEST_60_WOW 60 60 60 60 60 60
TEST_90_WOW 90 90 90 90 90 90
*/
