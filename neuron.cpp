#include "neuron.hpp"

neuron::neuron(int idIn, neuronType typeIn, int rowIn, std::map<int, neuron*> * netIn)
{
	id = idIn;
	type = typeIn;
	row = rowIn;
	net = netIn;
}

neuron::~neuron()
{
	dendrite.clear();
}

void neuron::run(int set)
{
	if (set != -1)
	{
		axon = set;
		return;
	}
	axon = 0;
	for (auto const& axIn : dendrite) {
		if (net->count(axIn.first) != 1 || (*net)[axIn.first]->getRow() >= row)
		{
			fprintf(stderr, "bad net\n\n");
			continue;
		}
		axon = axon + axIn.second * (*net)[axIn.first]->getAxon();
	}
}

std::string neuron::toText()
{
	//#type #row #id #in
	//n      1    2   1
	std::string line = "";
	if (type == start)
	{
		line.append("s ");
	}
	else if (type == end)
	{
		line.append("e ");
	}
	else
	{
		line.append("h ");
	}
	line.append(std::to_string(row));
	line.append(" ");
	line.append(std::to_string(id));
	line.append(" ");
	line.append(std::to_string(dendrite.size()));

	//#type #id #weight
	//c 1 .444
	for (auto const& axIn : dendrite) {
		line.append("\nc ");
		line.append(std::to_string(axIn.first));
		line.append(" ");
		line.append(std::to_string(axIn.second));
	}
	return line;
}

void neuron::addDendrite(int id, double weight)
{
	dendrite.push_back(std::pair<int, double>(id, weight));
}
