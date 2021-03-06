//
// Book : Version du chapitre 9 de l'ouvrage.
// "Programming -- Principles and Practice Using C++" de Bjarne Stroustrup (2ème édition : 2014)
// Commit initial : 27 janvier 2018 
// Commit en cours : Exercice n°13 de la page 340 à 341
// Caractères spéciaux : [ ]   '\n'   {  }   ||   ~   _     @

// Librairie indispensable sous Windows et VC++
#include "stdafx.h"


// Librairie restreinte fournie par BS
#include "std_lib_facilities.h"

class Rational {
public:
	// Constructeur par défaut
	Rational() = default;

	// Constructeur
	Rational(int n, int d) :rational_numerator(n), rational_denominator(d)
	{

		if (d==0) throw Invalid();		// Le dénominateur ne peut être nul !
		
		rational_doubleValue = static_cast<double>(n) / static_cast<double>(d); // Sinon, on peut affecter le résultat de la division du numérateur et du dénominateur en les convertissant en double (sinon 5/2 donne 2 et pas 2.5)
	}

	class Invalid { };                 // to throw as exception

	// non-modifying operations
	int numerator() const noexcept { return rational_numerator; }
	int denominator() const noexcept { return rational_denominator; }
	double doubleValue() const noexcept { return rational_doubleValue; }
	

	// modifying operations
	// none ***************

private:							// Les variables privées sont initialisées par défaut : CPP CoreGuidelines
	int rational_numerator = 0;
	int rational_denominator = 0;
	double rational_doubleValue=0.0;
};


bool operator==(const Rational& fraction1, const Rational& fraction2) noexcept	// Overloading de l'opérateur == qui compare deux fractions
{
	if(fraction1.numerator()== fraction2.numerator()&& fraction1.denominator() == fraction2.denominator())return true; // Les numérateurs et dénominateurs des 2 fractions comparées doivent être identiques
	return false;
}

void affichageFraction(string msg,const Rational& fraction1)	// Affichage formaté d'une fraction
{
	cout <<msg<<" : "<<fraction1.numerator() << " / " << fraction1.denominator() << " qui correspond à " << fraction1.doubleValue() << '\n';
}

Rational addition(const Rational& fraction1, const Rational& fraction2)	// Addition de deux fractions passées en référence
{
	int const new_numerateur = fraction1.numerator()*fraction2.denominator() + fraction2.numerator()*fraction1.denominator();
	int const new_denominateur = fraction1.denominator()*fraction2.denominator();

	Rational fraction_resultante= { new_numerateur,new_denominateur };
	return fraction_resultante;
}

Rational soustraction(const Rational& fraction1, const Rational& fraction2)	// Soustraction de deux fractions passées en référence
{
	int const new_numerateur = fraction1.numerator()*fraction2.denominator() - fraction2.numerator()*fraction1.denominator();
	int const new_denominateur = fraction1.denominator()*fraction2.denominator();

	Rational fraction_resultante = { new_numerateur,new_denominateur };
	return fraction_resultante;
}

Rational multiplication(const Rational& fraction1, const Rational& fraction2)	// Multiplication de deux fractions passées en référence
{
	int const new_numerateur = fraction1.numerator()* fraction2.numerator();
	int const new_denominateur = fraction1.denominator()*fraction2.denominator();

	Rational fraction_resultante = { new_numerateur,new_denominateur };
	return fraction_resultante;
}

Rational division(const Rational& fraction1, const Rational& fraction2)	// Division de deux fractions passées en référence
{
	int const new_numerateur = fraction1.numerator()* fraction2.denominator();
	int const new_denominateur = fraction1.denominator()*fraction2.numerator();

	Rational fraction_resultante = { new_numerateur,new_denominateur };
	return fraction_resultante;
}

int main()
{
	try
	{
		// A mettre dans la 1ère ligne du "main" pour afficher les caractères accentués sous la console Windows
		std::locale::global(std::locale("fr-FR"));

		// Numérateurs et dénominateurs de test
		vector <int> num_test{1,1,76,100  };
		vector <int> denom_test{2,2,87,100};
		vector <Rational> fraction(size(num_test));	// On crée un vecteur de fractions

		// Initialisation et assignation
		for (int i = 0; i< static_cast<int>(size(num_test)); i++)
		{
			// Création de l'objet
			fraction[i] = { num_test[i],denom_test[i] };
		
			// Vérification en l'affichant
			affichageFraction("Fraction créée",fraction[i]);

		};

		// Addition
		affichageFraction("Résultat des 2 fractions additionnées", addition(fraction[0], fraction[1]));

		// Soustraction
		affichageFraction("Résultat des 2 fractions soustraites", soustraction(fraction[0], fraction[1]));
				
		// Multiplication
		affichageFraction("Résultat des 2 fractions multipliées", multiplication(fraction[0], fraction[1]));

		// Division
		affichageFraction("Résultat des 2 fractions divisées", division(fraction[0], fraction[1]));

		// On teste l'égalité entre les premières fractions créées
		cout << "Les deux premières fractions créées sont" << ((fraction[0] == fraction[1]) ? " identiques\n" : " DIFFERENTES\n");
		
		keep_window_open();
		
		return 0;
	}
	catch (Rational::Invalid&)
	{
		cerr << "error: Le dénominateur ne peut être nul\n";
		keep_window_open("q");	// For some Windows(tm) setup
		return 1;
	}
	
	
	catch (runtime_error& e) 
	{	// this code is to produce error messages
		cout << e.what() << '\n';
		keep_window_open("q");	// For some Windows(tm) setups
	}
}

