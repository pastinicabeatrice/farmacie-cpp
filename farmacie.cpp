#include <iostream>
#include <string>

using namespace std;

enum ModEliberare {
	cuReteta, faraReteta, Gratis, Compensat
};

const char* denumireMod(ModEliberare mod) {
	switch (mod) {
	case cuReteta: return "cu reteta";
	case faraReteta: return "fara reteta";
	case Gratis: return "gratuit";
	case Compensat: return "compensat";
	}
	return "necunoscut";
}

class Farmacie {
private:
	string nume;
	const int anInfiintare;
	int nrAngajati;
	float* salarii;
	ModEliberare modEliberare;
	static float salariuMinim;

	void copiereSalarii(int nr, const float* sursa) {
		this->nrAngajati = nr;
		this->salarii = nr > 0 ? new float[nr] : nullptr;
		for (int i = 0; i < nr; i++) {
			this->salarii[i] = sursa[i];
		}
	}

public:
	class Farmacist {
	public:
		string nume;
		int experientaAni;

		Farmacist() : nume("Necunoscut"), experientaAni(0) {}
		Farmacist(string nume, int experientaAni) : nume(nume), experientaAni(experientaAni) {}
	};

	Farmacie() : anInfiintare(2023), nume("Necunoscuta"), nrAngajati(0), salarii(nullptr), modEliberare(Gratis) {}

	Farmacie(string nume, ModEliberare modEliberare)
		: anInfiintare(2023), nume(nume), nrAngajati(0), salarii(nullptr), modEliberare(modEliberare) {}

	Farmacie(string nume, int anInfiintare, int nrAngajati, const float* salarii, ModEliberare modEliberare)
		: anInfiintare(anInfiintare), nume(nume), salarii(nullptr), modEliberare(modEliberare) {
		copiereSalarii(nrAngajati, salarii);
	}

	Farmacie(const Farmacie& f) : anInfiintare(f.anInfiintare), nume(f.nume), salarii(nullptr), modEliberare(f.modEliberare) {
		copiereSalarii(f.nrAngajati, f.salarii);
	}

	Farmacie& operator=(const Farmacie& f) {
		if (this != &f) {
			delete[] this->salarii;
			this->nume = f.nume;
			this->modEliberare = f.modEliberare;
			copiereSalarii(f.nrAngajati, f.salarii);
		}
		return *this;
	}

	~Farmacie() {
		delete[] this->salarii;
	}

	string getNume() const {
		return this->nume;
	}

	void setNume(string nume) {
		if (nume.length() > 2) {
			this->nume = nume;
		}
	}

	int getAnInfiintare() const {
		return this->anInfiintare;
	}

	int getNrAngajati() const {
		return this->nrAngajati;
	}

	void setAngajati(int nr, const float* salarii) {
		if (nr > 0 && salarii != nullptr) {
			delete[] this->salarii;
			copiereSalarii(nr, salarii);
		}
	}

	float getSalariu(int pozitie) const {
		if (pozitie >= 0 && pozitie < nrAngajati) {
			return this->salarii[pozitie];
		}
		return 0;
	}

	float totalSalarii() const {
		float total = 0;
		for (int i = 0; i < nrAngajati; i++) {
			total += salarii[i];
		}
		return total;
	}

	float salariuMediu() const {
		return nrAngajati > 0 ? totalSalarii() / nrAngajati : 0;
	}

	int angajatiSubSalariulMinim() const {
		int nr = 0;
		for (int i = 0; i < nrAngajati; i++) {
			if (salarii[i] < salariuMinim) {
				nr++;
			}
		}
		return nr;
	}

	float& operator[](int pozitie) {
		if (pozitie < 0 || pozitie >= nrAngajati) {
			throw out_of_range("Pozitie invalida");
		}
		return salarii[pozitie];
	}

	Farmacie& operator+=(float salariuNou) {
		float* nou = new float[nrAngajati + 1];
		for (int i = 0; i < nrAngajati; i++) {
			nou[i] = salarii[i];
		}
		nou[nrAngajati] = salariuNou;
		delete[] salarii;
		salarii = nou;
		nrAngajati++;
		return *this;
	}

	bool operator==(const Farmacie& f) const {
		return nume == f.nume && nrAngajati == f.nrAngajati;
	}

	bool operator>(const Farmacie& f) const {
		return totalSalarii() > f.totalSalarii();
	}

	static void marireSalariuMinim(int procent) {
		salariuMinim += salariuMinim * (procent / 100.0f);
	}

	static float getSalariuMinim() {
		return salariuMinim;
	}

	static void setSalariuMinim(float valoare) {
		if (valoare > 10) {
			salariuMinim = valoare;
		}
	}

	friend ostream& operator<<(ostream& out, const Farmacie& f);
	friend class DistribuitorMedicamente;
};

float Farmacie::salariuMinim = 1950;

ostream& operator<<(ostream& out, const Farmacie& f) {
	out << "Farmacia " << f.nume << " (infiintata in " << f.anInfiintare << ", eliberare "
		<< denumireMod(f.modEliberare) << "), " << f.nrAngajati << " angajati";
	if (f.nrAngajati > 0) {
		out << ", salarii: ";
		for (int i = 0; i < f.nrAngajati; i++) {
			out << f.salarii[i] << (i + 1 < f.nrAngajati ? ", " : "");
		}
	}
	return out;
}

class DistribuitorMedicamente {
private:
	string nume;
	Farmacie farmacie;

public:
	DistribuitorMedicamente(string nume, const Farmacie& farmacie) : nume(nume), farmacie(farmacie) {}

	string getNume() const {
		return nume;
	}

	void setNume(string nume) {
		if (!nume.empty()) {
			this->nume = nume;
		}
	}

	Farmacie getFarmacie() const {
		return this->farmacie;
	}

	void setFarmacie(const Farmacie& f) {
		this->farmacie = f;
	}

	void acordaBonus(float procent) {
		for (int i = 0; i < farmacie.nrAngajati; i++) {
			farmacie.salarii[i] += farmacie.salarii[i] * procent / 100;
		}
	}
};

int main() {
	Farmacie f1;
	f1.setNume("HelpNet");
	float salariiInitiale[] = { 3000, 5000, 4000 };
	f1.setAngajati(3, salariiInitiale);
	cout << f1 << endl;
	cout << "Salariu mediu: " << f1.salariuMediu() << endl;

	float salariiCatena[] = { 1950, 2300 };
	Farmacie f2("Catena", 2000, 2, salariiCatena, cuReteta);
	f2 += 2800;
	f2[0] = 2100;
	cout << f2 << endl;

	Farmacie f3("Tei", faraReteta);
	cout << f3 << endl;

	cout << "\nSalariul minim: " << Farmacie::getSalariuMinim() << endl;
	Farmacie::marireSalariuMinim(10);
	cout << "Salariul minim dupa majorarea cu 10%: " << Farmacie::getSalariuMinim() << endl;
	cout << "Angajati Catena sub salariul minim: " << f2.angajatiSubSalariulMinim() << endl;

	Farmacie copie = f2;
	cout << "\nCopia este identica cu originalul: " << (copie == f2 ? "da" : "nu") << endl;
	f3 = f1;
	cout << "Dupa atribuire: " << f3 << endl;
	cout << (f1 > f2 ? f1.getNume() : f2.getNume()) << " are cheltuieli salariale mai mari." << endl;

	Farmacie::Farmacist farmacist("Popescu", 7);
	cout << "\nFarmacist: " << farmacist.nume << ", " << farmacist.experientaAni << " ani experienta" << endl;

	DistribuitorMedicamente distribuitor("MedDistrib", f2);
	distribuitor.acordaBonus(5);
	cout << "Distribuitorul " << distribuitor.getNume() << " gestioneaza: " << distribuitor.getFarmacie() << endl;

	Farmacie* retea = new Farmacie[3];
	retea[0] = f1;
	retea[1] = f2;
	retea[2] = Farmacie("Sensiblu", Compensat);
	cout << "\nReteaua de farmacii:" << endl;
	for (int i = 0; i < 3; i++) {
		cout << "  " << retea[i] << endl;
	}
	delete[] retea;

	return 0;
}
