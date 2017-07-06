#include "net.hpp"

Nnet::Nnet(int startNumber, int endNumber, int rows)
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
	std::cout << "1 - net" << '\n';
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

Nnet::Nnet(std::string fileName)
{
	loadDoc(fileName);
}

Nnet::~Nnet()
{
}

Nnet::Nnet(Nnet & oldNet)
{
	std::vector<neuron*> rowNew;
	std::map<int, neuron*> * net = new std::map<int, neuron*>();

	for (std::vector<neuron*> rowOld : oldNet.layout)
	{
		rowNew.clear();
		for (neuron* nerOld : rowOld)
		{
			neuron * newNer = new neuron(nerOld->getId(), nerOld->getType(), nerOld->getRow(), net, nerOld->getWeight());
			for (auto dendrite : nerOld->getDendrite())
			{
				newNer->addDendrite(dendrite.first, dendrite.second);
			}
			(*net)[nerOld->getId()] = newNer;
			rowNew.push_back(newNer);
		}
		layout.push_back(rowNew);
	}
	rowCount = oldNet.layout.size();
	maxId = oldNet.maxId;
}

bool Nnet::toDoc(std::string fileName)
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

bool Nnet::loadDoc(std::string fileName)
{
	return false;
}

int Nnet::addNeuron(int row, neuronType typeIn, double weight)
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

void Nnet::addConnection(int idStart, int idEnd, double weight)
{
	neuron * start = (*net)[idStart];
	neuron * end = (*net)[idEnd];
	if(start->getRow() >= end->getRow()) { throw std::invalid_argument("Error: neuron tried to connect to neuron in lower row"); }
	end->addDendrite(idStart, weight);
}

void Nnet::changeConnection(int idStart, int idEnd, double weight)
{
	neuron * end = (*net)[idEnd];
	end->changeDendrite(idStart, weight);
}

void Nnet::removeConnection(int idStart, int idEnd) 
{
	neuron * end = (*net)[idEnd];
	end->removeDendrite(idStart);
}

int Nnet::mutate(double chance)
{
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<> dis(0, 100000);
	std::normal_distribution<double> nDis(0, .1);
	int numb = 0;
	int count = 0;

	double random;
	for (std::vector<neuron*> row : layout)
	{
		for (neuron* ner: row)
		{
			numb = dis(gen);
			random = (double)numb / 100000;
			//std::cout << random << '\n';

			if (random < chance)
			{
				//std::cout << "mutate " << ner->getId() << '\n';
				count++;
				if ((random / chance) > .75 || ner->getRow() == 0)
				{
					//std::cout << "weight " << ner->getId() << '\n';
					ner->setWeight(ner->getWeight() * (1 + nDis(gen)));
				}
				else
				{
					//std::cout << "dend " << ner->getId() << '\n';
					ner->setWeight(ner->getWeight() * (1 + nDis(gen)));
					ner->mutateDendrite(chance);
				}
			}
		}
	}
	
	return count;
}

int Nnet::getColCount(int col)
{
	if (col >= rowCount) { throw std::invalid_argument("Error: Col not in Layout"); }
	return layout[col].size();
}

std::vector<double> Nnet::run(std::vector<double> input)
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

void Nnet::removeNeuron(int id)
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
