#ifndef NEURON_HEADER
#define NEURON_HEADER

#include <string>
#include <vector>
#include <map>


enum neuronType {START, END, HIDDEN};

class neuron
{
public:
	neuron(int idIn, neuronType typeIn, int rowIn, std::map<int, neuron*> * netIn);
	~neuron();
	void run(int set = -1);
	int getId() { return id; };
	int getRow() { return row; };
	neuronType getType() { return type; };
	double getAxon() { return axon; };
	std::string toText();
	void changeDendrite(int id, double weight);
	void removeDendrite(int id);
	void addDendrite(int id, double weight = .5);

private:
	int id;
	neuronType type;
	double axon;
	std::vector<std::pair<int, double>>  dendrite;
	int row;
	std::map<int, neuron*> * net;
};


#endif
