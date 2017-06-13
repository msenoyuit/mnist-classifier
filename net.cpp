#include "net.hpp"

nnet::nnet(int startNumber, int endNumber, int rows)
{
	std::vector<neuron*> row;
	std::map<int, neuron*> * net = new std::map<int, neuron*>();
	rowCount = rows;
	for (int j = 0; j < startNumber; j++)
	{
		neuron * newNer = new neuron(++maxId, START, 0, net);
		(*net)[maxId] = newNer;
		row.push_back(newNer);
	}
	layout.push_back(row);
	row.clear();

	for (int i = 1; i < (rowCount-1); i++)
	{
		for (int j = 0; j < startNumber; j++)
		{
			neuron * newNer = new neuron(++maxId, HIDDEN, i, net);
			for (auto startNeuron : layout[i - 1])
			{
				newNer->addDendrite(startNeuron->getId());
			}
			(*net)[maxId] = newNer;
			row.push_back(newNer);
		}
		layout.push_back(row);
		row.clear();
	}


	for (int j = 0; j < startNumber; j++)
	{
		//neuron(int idIn, neuronType typeIn, int rowIn, std::map<int, neuron*> * netIn);
		neuron * newNer = new neuron(++maxId, END, rowCount-1, net);
		for (auto startNeuron : layout[rowCount - 2])
		{
			newNer->addDendrite(startNeuron->getId());
		}
		(*net)[maxId] = newNer;
		row.push_back(newNer);
	}
	layout.push_back(row);
	row.clear();

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
	for (auto layer : layout)
	{
		for (auto ner : layer)
		{
			std::cout << ner->toText() << '\n';
		}

	}
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

std::vector<double> nnet::run(std::vector<double> input)
{
	std::vector<double> results;
	if (input.size() != layout[0].size()) { throw std::invalid_argument("Error: wrong number of inputs"); }
	int inputCounter = 0;
	for (auto ner : layout[0])
	{
		//std::cout << ner->getId() << " " << ner->getAxon() << " " << inputCounter <<'\n';
		ner->run(input[inputCounter++]);
	}
	for (unsigned int i = 1; i < layout.size(); i++)
	{
		for (auto ner : layout[i])
		{
			//std::cout << ner->getId() << " " << ner->getAxon() << '\n';
			ner->run();
		}
	}
	/*
	for (auto  layer : layout)
	{
		for (auto ner : layer)
		{
			ner->run();
		}

	}
	*/


	for (auto last : layout[rowCount-1])
	{
		results.push_back(last->getAxon());
	}

	return results;
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

	for (auto it = layout[doomedRow].begin(); it != layout[doomedRow].end(); ++it) 
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
