#include "catch.hpp"

#include "timedrel/zone.hpp"
#include "timedrel/utils.hpp"

using namespace timedrel;

TEST_CASE( "Construction" ) {

    SECTION( "Normalization 1" ) {

        auto z1 = zone<int>::make({0,6,0,6,0,9});
        auto z2 = zone<int>::make({0,6,0,6,0,6});

        CHECK( z1 == z2 );

    }

    SECTION( "Normalization 2" ) {

        auto z1 = zone<int>::make({0,6,0,6,3,4});
        auto z2 = zone<int>::make({0,3,3,6,3,4});

        CHECK( z1 == z2 );

    }

    SECTION( "Universal" ) {

        auto z1 = zone<int>::universal();
        auto z2 = zone<int>::make({0,1000000000,0,1000000000,0,1000000000});

        CHECK( zone<int>::includes(z1, z2) );

    }

    SECTION( "Integral Infinities" ) {

        auto z1 = zone<int>::make({0,6,0,6,3,bound<int>::infinity});

        CHECK( z1.is_nonempty() );

    }

    SECTION( "Floating Infinities" ) {

        auto z1 = zone<float>::make({0,bound<float>::infinity,0,bound<float>::infinity,0, bound<float>::infinity});

        CHECK( z1.is_nonempty() );

    }
}

TEST_CASE( "Inclusion" ) {

	SECTION( "Equivalent zones include each other" ) {

		auto z1 = zone<int>::make({0,9,0,9,0,9});
    	auto z2 = zone<int>::make({0,9,0,9,0,9});

    	REQUIRE( z1 == z2 );

		CHECK( zone<int>::includes(z1,z2) );
		CHECK( zone<int>::includes(z2,z1) );
	}

	SECTION( "Incomparable" ) {

		auto z1 = zone<int>::make({0,6,0,6,1,5});
    	auto z2 = zone<int>::make({3,9,3,9,0,6});

		CHECK( not zone<int>::includes(z1,z2) );
		CHECK( not zone<int>::includes(z2,z1) );
	}

	SECTION( "Bounds" ) {

		auto z = zone<int>::make({0,9,0,9,0,9}, {1,1,1,1,1,1});

    	auto z1 = zone<int>::make({0,9,0,9,0,9}, {0,1,1,1,1,1});
    	auto z2 = zone<int>::make({0,9,0,9,0,9}, {1,0,1,1,1,1});
    	auto z3 = zone<int>::make({0,9,0,9,0,9}, {1,1,0,1,1,1});
    	auto z4 = zone<int>::make({0,9,0,9,0,9}, {1,1,1,0,1,1});
    	auto z5 = zone<int>::make({0,9,0,9,0,9}, {1,1,1,1,0,1});
    	auto z6 = zone<int>::make({0,9,0,9,0,9}, {1,1,1,1,1,0});

		CHECK( zone<int>::includes(z,z1) );
		CHECK( zone<int>::includes(z,z2) );
		CHECK( zone<int>::includes(z,z3) );
		CHECK( zone<int>::includes(z,z4) );
		CHECK( zone<int>::includes(z,z5) );
		CHECK( zone<int>::includes(z,z6) );

		CHECK( not zone<int>::includes(z1,z) );
		CHECK( not zone<int>::includes(z2,z) );
		CHECK( not zone<int>::includes(z3,z) );
		CHECK( not zone<int>::includes(z4,z) );
		CHECK( not zone<int>::includes(z5,z) );
		CHECK( not zone<int>::includes(z6,z) );
	}

}

TEST_CASE( "intersectionion" ) {

    SECTION( "Simple" ) {

        auto z1 = zone<int>::make({0,6,0,6,0,6});
        auto z2 = zone<int>::make({3,9,3,9,0,6});

        auto result = zone<int>::intersection(z1,z2);
        auto expected = zone<int>::make({3,6,3,6,0,3});

        CHECK( result == expected );

    }

    SECTION( "Emptiness" ) {

        auto z1 = zone<int>::make({0,3,3,6,0,6});
        auto z2 = zone<int>::make({3,6,3,6,0,3});

        auto result = zone<int>::intersection(z1,z2);

        CHECK( !result.is_nonempty() );

    }

}

TEST_CASE( "Duration Restriction" ) {

    SECTION( "Simple" ) {

        auto z1 = zone<int>::make({0,6,0,6,0,6});

        auto result = zone<int>::duration_restriction(z1, 3, 4);
        auto expected = zone<int>::make({0,3,3,6,3,4});

        CHECK( result == expected );

    }

}

TEST_CASE( "Concatenation" ) {

    SECTION( "Simple" ) {

        auto z1 = zone<int>::make({0,6,0,6,0,6});
        auto z2 = zone<int>::make({6,9,6,9,0,3});

        auto result = zone<int>::concatenation(z1,z2);
        auto expected = zone<int>::make({0,6,6,9,0,9});

        CHECK( result == expected );

    }

    SECTION( "Complex" ) {

        auto z1 = zone<int>::make({0,3,0,3,1,2});
        auto z2 = zone<int>::make({2,7,2,7,1,2});

        auto result = zone<int>::concatenation(z1,z2);
        auto expected = zone<int>::make({0,6,6,9,2,4});

        // CHECK( result == expected );

    }

    // SECTION( "Emptiness" ) {

    //     auto z1 = zone<int>::make_unique({0,3,3,6,0,6});
    //     auto z2 = zone<int>::make_unique({3,6,3,6,1,2});

    //     auto result = intersection(z1,z2);

    //     CHECK( is_empty(result) );

    // }

}