#ifndef NET_HEADER
#define NET_HEADER
#include "neuron.hpp"
#include <iostream>

class nnet
{
public:
	nnet(int startNumber = 5, int endNumber = 5, int rows = 3);
	nnet(std::string fileName);
	~nnet();
	nnet* child();
	bool toDoc(std::string fileName);
	bool loadDoc(std::string fileName);

	int addNeuron(int row, neuronType typeIn = HIDDEN, double weight = .5);
	void removeNeuron(int id);

	void addConnection(int idStart, int idEnd, double weight = .5);
	void changeConnection(int idStart, int idEnd, double weight);
	void removeConnection(int idStart, int idEnd);

	std::vector<double> nnet::run(std::vector<double> input);

private:
	std::map<int, neuron*> * net;
	std::vector<std::vector<neuron*>> layout;
	int maxId = 0;
	int rowCount = 0;


};























#endif