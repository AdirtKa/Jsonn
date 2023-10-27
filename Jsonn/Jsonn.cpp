#include <iostream>
#include <iomanip>
#include "Planet.hpp"

using namespace nlohmann;

std::vector <Planet> readPlanetsFromJson(const std::string& filename);
void writePlanetsToJson(const std::string& filename, const std::vector <Planet>& planets);
void printPlanetNames(const std::vector <Planet>& planets);
Planet makePlanet();
void printActions(const int& planetsCount);

int main()
{
	std::string filename;
	std::cout << "Enter a filename: "; std::cin >> filename;
	filename = filename + ".json";
	//filename = "planets.json";

	std::vector <Planet> planets = readPlanetsFromJson(filename);
	while (true)
	{
		system("cls");
		printPlanetNames(planets);
		int choice, planetsCount;
		planetsCount = planets.size();
		printActions(planetsCount);
		std::cout << "Enter a action: "; std::cin >> choice;
		if (choice < 0 || choice > planetsCount + 3) {
			std::cout << "Invalid action" << std::endl; 
			continue;
		}
		if (choice == 0) {
			return 0;
		}
		else if (choice == planetsCount + 1) {
			planets.push_back(makePlanet());
		}
		else if (choice == planetsCount + 2) {
			int planetToEraseIndex;
			std::cout << "Which planet do you want to delete? "; std::cin >> planetToEraseIndex;
			planets.erase(planets.begin() + planetToEraseIndex - 1);
		}
		else if (choice == planetsCount + 3) {
			writePlanetsToJson(filename, planets);
		}
		else if (choice < planetsCount + 1) {
			planets[choice - 1].print_planet();
			system("pause");
		}
	}

	writePlanetsToJson(filename, planets);

	return 0;
}

std::vector <Planet> readPlanetsFromJson(const std::string& filename) {
	std::ifstream file(filename);
	std::vector <Planet> planets;

	if (file) {
		json PlanetsNode;
		file >> PlanetsNode;
		for (json& planetNode : PlanetsNode) {
			planets.push_back(Planet(planetNode));
		}
	}

	return planets;
}

void writePlanetsToJson(const std::string& filename, const std::vector <Planet>& planets) {
	json planetsNode;
	for (Planet planet : planets) {
		planetsNode.emplace_back(planet.getJson());
	}
	std::ofstream file(filename);
	file << std::setw(4) << planetsNode;
}

void printPlanetNames(const std::vector <Planet>& planets) {
	if (planets.empty()) {
		std::cout << "There is no planets" << std::endl;
		return;
	}

	std::cout << "Available planets: " << std::endl; 
	for (int i = 0; i < planets.size(); i++) {
		std::cout << i + 1 << ". " << planets[i].name << std::endl;
	}
}

Planet makePlanet() {
	std::string name;
	double radius, weight;
	std::vector <std::string> satelites;
	int satelitesCount;

	std::cout << "Enter the name of the planet: "; std::cin >> name;
	std::cout << "Enter the radius of the planet: "; std::cin >> radius;
	std::cout << "Enter the weight of the planet: "; std::cin >> weight;
	std::cout << "Enter the number of planet's satelites: "; std::cin >> satelitesCount;

	for (int i = 0; i < satelitesCount; i++) {
		std::string satellite;
		std::cout << "Enter the name of the satellite: "; std::cin >> satellite;
		satelites.push_back(satellite);
	}

	return Planet(name, radius, weight, satelites);
}

void printActions(const int& planetsCount) {
	std::cout << std::endl << "Available actions: " << std::endl;
	std::cout << "0. Exit" << std::endl;
	if (planetsCount == 1) {
		std::cout << "1. Print the details of the planet" << std::endl;
	}
	else if (planetsCount > 1) {
		std::cout << 1 << '-' << planetsCount << ". Print the details of the planets" << std::endl;
	}
	std::cout << planetsCount + 1 << ". Add a planet" << std::endl;
	std::cout << planetsCount + 2 << ". Remove a planet" << std::endl;
	std::cout << planetsCount + 3 << ". Save the planets to a json file" << std::endl;
}
