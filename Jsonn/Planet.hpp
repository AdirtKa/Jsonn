#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>

using namespace nlohmann;


struct Planet
{
public:
	std::string name;
	double weight, radius;
	std::vector <std::string> satelites;
	Planet(const std::string& name="Uknown", const double& weight=0.0, const double& radius= 0.0, std::vector <std::string> satelites = {}) : name(name), weight(weight), radius(radius), satelites(satelites) {}
	
	json getJson(){	
		json node;
		node["name"] = name;
		node["weight"] = weight;
		node["radius"] = radius;
		node["satelites"] = satelites;
		return node;
	}

	void print_planet() {
		std::cout <<
			"Name: " << name << std::endl <<
			"Weight: " << weight << std::endl <<
			"radius: " << radius << std::endl;
	}
};