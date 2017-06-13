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

void neuron::run(double set)
{
	//std::cout << this->getId() << '\n';
	if (set > 0)
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
		//std::cout << "axon begin " << axon << '\n';
		//std::cout << axIn.second << " " << axIn.first << " " << (*net)[axIn.first]->getAxon() << '\n';
		axon = axon + axIn.second * (*net)[axIn.first]->getAxon();
		//std::cout << "axon end " << axon << '\n';
	}

	axon = axon / dendrite.size();
}

std::string neuron::toText()
{
	//#type #row #id #in
	//n      1    2   1
	std::string line = "";
	if (type == START)
	{
		line.append("s ");
	}
	else if (type == END)
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


void neuron::changeDendrite(int id, double weight)
{
	for (auto & dend : dendrite) {
		if (dend.first == id)
		{
			dend.second = weight;
			return;
		}
	}
}

void neuron::removeDendrite(int id)
{
	for (auto it = dendrite.begin(); it != dendrite.end(); ++it) {
		if (it->first == id)
		{
			std::swap(*it, dendrite.back());
			dendrite.pop_back();
		}
	}
}
