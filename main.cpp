#define _USE_MATH_DEFINES

#include <iostream>
#include <Windows.h>
#include <vector>
#include <iostream>
#include <string>
#include <cassert>
#include <array>
#include <algorithm>
#include <list>
#include <set>
#include <functional>
#include <numeric>
#include <stdexcept>
#include <cmath>
#include <tuple>

class Message {
	std::string content;
public:
	Message(const std::string&  str) : content(str)
	{

	}	
	//permet de ne r�aliser qu'une comparaison du sens : Message == std::string 
	//Passage par r�f�rence constante pour �viter une copie
	bool operator==(const std::string&  rhs) const
	{
		return rhs.compare(content) > 0;
	}
	//permet de r�aliser �alement la comparaison : std::string == Message
	friend bool operator==(const std::string& lhs, const Message& rhs)
	{
		return lhs.compare(rhs.content);
	}
};

//Prototype
double division(double numerateur, double denominateur);

//Template
template <typename Collection>
void afficher(Collection const& iterable)
{
	for (auto const& e : iterable)
	{
		std::cout << e << std::endl;
	}
}


bool predicat_sort(int a, int b)
{
	return a + 1 < b;
}

std::tuple<double, double> g(double angle)
{
	return { std::cos(angle), std::sin(angle) };
}

int main()
{
	//Permet d'utiliser les accents dans les messages console
	SetConsoleOutputCP(1252);	

	std::cout << "Premier message !" << std::endl;
	//Charact�re d'�chappement '\'
	std::cout << "Exemple tabulation \t tab." << std::endl;

	//affichage des nombres
	std::cout << 0 << std::endl;
	std::cout << 1 << std::endl;
	std::cout << -1.6027 << std::endl;
	std::cout << 3.14159 << std::endl;
	std::cout << 2.71828 << std::endl;

	std::cout << std::endl << std::endl;

	//C++11 initialisation style
	int value{ 0 };

	//le mot cl� const, s'applique � ce qui se trouve � gauche
	int const* pValue; //int est constant, mais l'�toile se trouve � droite, donc le pointeur n'est pas constant
	//Changement d'adresse autoris� car le pointeur n'est pas constant [ok]
	pValue = &value;
	//Interdit car la valeur point� est constante [nok]
	//*pValue = 1;

	//Cette fois si la constante s'applique sur le pointeur et non pas la valeur cibl�.
	int* const pValue_1 = &value;
	//Interdit car pointeur constant [nok]
	//pValue_1 = &value;
	//Changement de valeur [ok]
	*pValue_1 = 5;

	//Mot cl� auto 
	/*
	Force l�initialisation d�une variable, �vitant au d�veloppeur un oubli d�initialisation, renfor�ant ainsi la s�curit� du code
	Evite les conversions implicites de types
	Renforce l�aspect s�mantique, en �vitant au d�veloppeur de se soucier de l�aspect syntaxique
	G�n�ralement un gain d�efficacit� quand du code est �crit, particuli�rement pour les tests unitaires ou seul l�aspect fonctionnel est int�ressant
	*/
	auto pi{ 3.14159265359 }; //auto d�tecte le type automatiquement ici double

	using namespace std::literals;
	//le 's" � la fin est important dans le cas d'un auto en c++, on veut que ce soit une String sinon c'est interpr�t� comme une chaine de caract�re en C
	//D�claration d'une chaine de caract�re avec le mot cl� auto
	auto chaine{ "Du texte."s };

	// Nouveau mot cl� not
	bool test{ not value };

	//iterations for each, vector tableau dynamique
	std::vector<int> const nbrs{ 2,4,6,8,10 };
	for (auto const nbr : nbrs)
	{
		std::cout << nbr << std::endl;
	}

	std::cout << std::endl << std::endl;

	//Tableau statique int taille 10, le reste non d�fini est initialis� � 0
	std::array<int, 10> array_tab{ 1,2,3,4,5,6,7 };
	for (auto const element : array_tab)
	{	
		std::cout << element << std::endl;
	}
	std::cout << std::endl << std::endl;

	//On peut le manipuler et modifier les cases, il est juste de taille statique 10, contrairement � un vecteur.
	array_tab.at(7) = 5; //at donne une r�f�rence donc modification possible

	std::cout << "Taille du tableau :" << std::size(array_tab) << std::endl; //10 car taille statique

	//parcourir un tableau en utilisant un iterator, begin et end
	for (auto it{ std::begin(array_tab) }; it != std::end(array_tab); ++it)
	{
		std::cout << *it << std::endl;
	}

	std::cout << std::endl << std::endl;

	//Parcourir � l'envers le tableau gr�ce � l'utilisation de rbegin et rend
	for (auto it{ std::rbegin(array_tab) }; it != std::rend(array_tab); ++it)
	{
		std::cout << *it << std::endl;
	}

	std::cout << std::endl << std::endl;

	//Utilisation de <algorithm>, chercher le nombre d'occurence d'un �l�ment dans le tableau
	auto const count_el{ std::count(std::begin(array_tab), std::end(array_tab), 1) };
	std::cout << "Nombre de 1 : " << count_el << std::endl;

	std::array<std::string, 5> listObjects{ "Triangle","Rectangle","Rond" };
	//find retourne un iterator sur le premier element trouv�
	auto const it_find = std::find(std::begin(listObjects), std::end(listObjects), "Rond");
	if (it_find != listObjects.end())
	{
		std::cout << "Element " << "Rond" << " found at position : ";
		std::cout << it_find - listObjects.begin() << " (counting from zero) \n";
	}


	//List ne poss�de pas d'it�rateur acc�s direct, uniquement bidirectionnels. On ne pas manipuler les �l�ments via it�rateurs
	std::list<int> nbrs_list{ 2, 3, 1, 7, -4 ,2 };
	//std::list propose ses propres m�thodes de tri
	nbrs_list.sort();
	//Pour une liste custom, on peut utiliser un pr�dicat pour r�aliser le tri 
	nbrs_list.sort(predicat_sort);

	std::cout << std::endl << std::endl;

	//particularit� des sets, elles ne peuvent contenir qu'une seule fois un �lement [est tri� contrairement � unordered_set]
	std::set<int> nbrs_set{ 2, 3, 1, 7, -4 ,2 };	
	//Il n'y aura qu'un seul 2 d'affich�
	for (auto it{ std::cbegin(nbrs_set) }; it != std::cend(nbrs_set); ++it)
	{
		//interdit car l'it�rateur est constant [cbegin/cend]
		//*it = 5;
		std::cout << *it << std::endl;
	}
	
	auto product{ std::accumulate(std::cbegin(nbrs_set), std::cend(nbrs_set), 1, std::multiplies<int> {}) };
	std::cout << "product on nbrs_set : " << product << std::endl;

	//Lambda function
	auto dash_fold = [](std::string a, int b) {
		return std::move(a) + '-' + std::to_string(b);
	};

	std::string s = std::accumulate(
		std::next(nbrs_set.begin()), // on a d�j� trait� le premier �l�ment, donc next
		nbrs_set.end(),
		std::to_string(*(nbrs_set.begin())), // start with first element
		dash_fold
	);

	std::cout << "dash-separated string: " << s << '\n';

	//Surchage des op�rateurs ==
	Message message("Test");
	std::string msg("Test");
	if (msg == message) {
		// do stuff...
	}

	//Assert pour v�rifier les erreurs
	//assert s�utilise non pas pour les erreurs de l�utilisateur mais bel et bien pour celles du programmeur.
	std::vector<int> const tab{ -4, 8, 452, -9 };
	int const index{ 2 };
	assert(index >= 0 && "L'index ne doit pas �tre n�gatif.");

	auto division_result = division(5.1, 2.0);

	//Memo Tests
	/*
	Un test unitaire, abr�g� TU est un morceau de code dont le seul but est de tester un autre morceau de code, afin de v�rifier si celui-ci respecte ses contrats.
	Les tests d�int�gration, qui v�rifient que diff�rents modules s�int�grent bien entre eux. On peut tester, par exemple, que le module de payement s�int�gre bien au reste de l�application d�j� d�velopp�.
	Les tests fonctionnels, qui v�rifient que le produit correspond bien � ce qu�on a demand�. Des tests fonctionnels sur une calculatrice v�rifieront que celle-ci offre bien les fonctionnalit�s demand�es (addition, logarithme, etc) par rapport � ce qui avait �t� d�fini et pr�vu (si l�on avait demand� le calcul de cosinus, il faut que la calculatrice l�impl�mente).
	Les tests d�UI (interface utilisateur, de l�anglais user interface), qui v�rifient, dans le cas d�une application graphique, que les boutons sont bien au bon endroit, les raccourcis, les menus et sous-menus, etc.
	*/

	//Catch des Exceptions
	try
	{
		// Essayez avec un nombre tr�s tr�s grand ou bien avec des lettres pour observer le comportement de std::stoi.
		int entier{ std::stoi("1000000000000000000000000000000000000000000000000000000") };
		std::cout << "Entier : " << entier << std::endl;
	}
	catch (std::invalid_argument const& exception)
	{
		std::cout << "Argument invalide : " << exception.what() << std::endl;
	}
	catch (std::out_of_range const& exception)
	{
		std::cout << "Cha�ne trop longue : " << exception.what() << std::endl;
	}
	catch (std::exception const& exception) //Le Catch g�n�rique toujour en dernier
	{
		// Message g�n�rique pour tous les autres types d'exception possibles.
		std::cout << "Erreur : " << exception.what() << std::endl;
	}

	//Utilisation des lambdas, �vite de cr�er des fonctions � port�e globale alors qu'elles sont � usage unique.
	std::vector<int> const nombres{ 1, 2, 3, 4, 5, 6, -7 };
	//Pr�ferer l'utilisation d'auto
	typedef bool (*lambda_signature)(int nbr);
	lambda_signature lambda = [](int nombre) -> bool { return nombre < 0; };
	if (std::any_of(std::cbegin(nombres), std::cend(nombres), lambda))
	{
		std::cout << "Au moins un nombre est n�gatif." << std::endl;
	}
	else
	{
		std::cout << "Tous les nombres sont positifs." << std::endl;
	}

	auto est_pair = [](int val) -> bool {return !(val % 2); };

	int entier;
	//Le mot-clef 'mutable' permet de modifier les valeurs captur�s dans le lambda
	auto lambdaMutable = [entier]() mutable -> void
	{
		entier = 0;
		std::cout << "L'entier vaut " << entier << " dans la lambda." << std::endl;
	};

	//utilisation des tuple
	using namespace std::literals;
	auto infos = std::make_tuple("Clem"s, "Lagrume"s, "Fruit"s, 4);

	//C++17, avant il fallait utiliser std::tie
	/*
	 double cosinus {};
	 double sinus {};
	 std::tie(cosinus, sinus) =  g(M_PI / 4.);
	*/
	auto [cosinus, sinus] = g(M_PI / 4.);
	std::cout << "Voici le cosinus de PI / 4 : " << cosinus << std::endl;
	std::cout << "Voici le sinus de PI / 4 : " << sinus << std::endl;

	return 0;
}

double division(double numerateur, double denominateur)
{
	assert(denominateur != 0.0 && "Le d�nominateur ne peut pas valoir z�ro.");
	return numerateur / denominateur;
}