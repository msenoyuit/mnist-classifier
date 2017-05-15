#include "net.hpp"

nnet::nnet(int startNumber, int endNumber, int rows)
{
	rowCount = rows;

}

nnet::nnet(std::string fileName)
{
	loadDoc(fileName);
}

nnet::~nnet()
{
}

bool nnet::toDoc(std::string fileName)
{
	return false;
}

bool nnet::loadDoc(std::string fileName)
{
	return false;
}

int nnet::addNeuron(int row, neuronType typeIn, double weight)
{
	//neuron::neuron(int idIn, neuronType typeIn, int rowIn, std::map<int, neuron*> * netIn)
	++maxId;
	neuron * newNer = new neuron(maxId, typeIn, row, net);
	net->insert(std::pair<int, neuron*>(maxId, newNer));
	if (rowCount < row) { throw std::invalid_argument("Error: tried to put neuron in invalid row"); }
	layout[row].push_back(newNer);

	if(row > 0)
	{
		for (auto const& dedendrite : layout[row - 1]) {
			newNer->addDendrite(dedendrite->getId(), weight);
		}
	}
	return maxId;
}

void nnet::addConnection(int idStart, int idEnd, double weight)
{
	neuron * start = (*net)[idStart];
	neuron * end = (*net)[idEnd];
	if(start->getRow() >= end->getRow()) { throw std::invalid_argument("Error: neuron tried to connect to neuron in lower row"); }
	end->addDendrite(idStart, weight);
}

void nnet::changeConnection(int idStart, int idEnd, double weight)
{
	neuron * end = (*net)[idEnd];
	end->changeDendrite(idStart, weight);
}

void nnet::removeConnection(int idStart, int idEnd) 
{
	neuron * end = (*net)[idEnd];
	end->removeDendrite(idStart);
}

std::vector<double> nnet::run()
{
	return std::vector<double>();
}

void nnet::removeNeuron(int id)
{
	neuron * doomed = (*net)[id];
	int doomedRow = doomed->getRow();

	for(int row = doomedRow + 1; row < rowCount; row++)
	{
		for (auto & ner : layout[row]) 
		{
			ner->removeDendrite(id);
		}
	}

	for (auto it = layout[doomedRow].begin(); it != layout[doomedRow].end(); ++it) {
	{
		if ((*it)->getId() == id)
		{
			std::swap(*it, layout[doomedRow].back());
			layout[doomedRow].pop_back();
			break;
		}
	}
	net->erase(net->find(id));
}
