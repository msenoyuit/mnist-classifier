#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include <cstdio>



TEST_CASE( "Empty Test", "[empty]" )
{
	REQUIRE(true);
}
