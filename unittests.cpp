#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include <cstdio>
#include "net.hpp"
#include "mnistNet.cpp"


TEST_CASE( "Empty Test", "[empty]" )
{
	REQUIRE(true);
}


TEST_CASE("Test neuron class", "[neuron]")
{
	//neuron(int idIn, neuronType typeIn, int rowIn, )
	std::map<int, neuron*> * net = new std::map<int, neuron*>();
	neuron *n1 = new neuron(1, START, 1, net);
	neuron *n2 = new neuron(2, START, 1, net);
	neuron *n3 = new neuron(3, HIDDEN, 2, net);
	neuron *n4 = new neuron(4, END, 3, net);
	neuron *n5 = new neuron(5, END, 3, net);
	
	(*net)[1] = n1;
	(*net)[2] = n2;
	(*net)[3] = n3;
	(*net)[4] = n4;
	(*net)[5] = n5;

	n1->run(1);
	n2->run(2);

	REQUIRE(n1->getAxon() == 1);
	REQUIRE(n2->getAxon() == 2);

	n3->addDendrite(1, .25);
	n3->addDendrite(2, .125);
	n4->addDendrite(3, 4);
	n5->addDendrite(2);

	n3->run();
	n4->run();
	n5->run();

	REQUIRE(n3->getAxon() == .25);
	REQUIRE(n4->getAxon() == 1);
	REQUIRE(n5->getAxon() == 1);
	REQUIRE(n1->toText().compare("s 1 1 0 1.000000") == 0);
	REQUIRE(n3->toText().compare("h 2 3 2 1.000000\nc 1 0.250000\nc 2 0.125000") == 0);
	REQUIRE(n5->toText().compare("e 3 5 1 1.000000\nc 2 0.500000") == 0);
	n3->removeDendrite(1); 
	REQUIRE(n3->toText().compare("h 2 3 1 1.000000\nc 2 0.125000") == 0);
	delete n1, n2, n3, n4, n5;
	std::cout << "end neuron test" << '\n';
}

TEST_CASE("Net Test", "[net]")
{
	std::vector<double> input = {3,3};
	Nnet net1 = Nnet(2, 2, 3);// = Nnet();
	Nnet net1Copy = net1;
	//net1.toDoc("asdf");
	//net1Copy.toDoc("asdf");
	std::vector<double> results = net1.run(input);
	input.push_back(1);
	REQUIRE_THROWS(net1.run(input));
	for (auto num : results)
	{
		//std::cout << num << '\n';
	}
	net1.toDoc("asdf");
	for (int i = 0; i < 1000; i++)
	{
		net1.mutate(.1);
	}

	net1.toDoc(" ");
} 