#ifndef NEURON_HEADER
#define NEURON_HEADER

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <random>
#include <iterator>


enum neuronType {START, END, HIDDEN};

class neuron
{
public:
	neuron(int idIn, neuronType typeIn, int rowIn, std::map<int, neuron*> * netIn, double weightIn = 1);
	~neuron();

	void run(double set = -1);
	std::string toText();

	int getId() { return id; };
	int getRow() { return row; };
	neuronType getType() { return type; };
	double getAxon() { return axon; };
	double getWeight() { return weight;};
	void setWeight(double weightIn);

	void changeDendrite(int id, double weight);
	void mutateDendrite(double amount);
	void removeDendrite(int id);
	void addDendrite(int id, double weight = .5);
	std::vector<std::pair<int, double>> getDendrite() { return dendrite; };

private:
	int id;
	neuronType type;
	double axon;
	double weight;
	std::vector<std::pair<int, double>>  dendrite;
	int row;
	std::map<int, neuron*> * net;
};


#endif
