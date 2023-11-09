#include "catch.hpp"

#include "timedrel/bound.hpp"
#include "timedrel/utils.hpp"

using namespace timedrel;

// TEST_CASE( "Addition" ) {

// 	SECTION( "Add bounds" ) {

// 		auto b1 = bound<int>(3,1);
//     	auto b2 = bound<int>(2,0);

// 		CHECK( bound<int>::add(b1,b2) == bound<int>(5,0) );
// 	}
// }

// TEST_CASE( "Minimum" ) {

//     // REQUIRE( z1 == z2 );

// 	SECTION( "Min bounds" ) {

// 		auto b1 = bound<int>(3,1);
//     	auto b2 = bound<int>(2,0);

// 		CHECK( bound<int>::add(b1,b2) == bound<int>(5,0) );
// 	}
// }

TEST_CASE( "Inclusion" ) {

    // REQUIRE( z1 == z2 );

    SECTION( "Lower bound inclusion 1" ) {

        auto b1 = lower_bound<int>::closed(3);
        auto b2 = lower_bound<int>::open(4);

        CHECK( lower_bound<int>::includes(b1,b2) );
        CHECK( !lower_bound<int>::includes(b2,b1) );
    }

    SECTION( "Lower bound inclusion 2" ) {

        auto b1 = lower_bound<int>::closed(3);
        auto b2 = lower_bound<int>::open(3);

        CHECK( lower_bound<int>::includes(b1,b2) );
        CHECK( !lower_bound<int>::includes(b2,b1) );
    }

    SECTION( "Lower bound inclusion 3" ) {

        auto b1 = lower_bound<int>::closed(3);
        auto b2 = lower_bound<int>::closed(3);

        CHECK( lower_bound<int>::includes(b1,b2) );
        CHECK( lower_bound<int>::includes(b2,b1) );
    }

    SECTION( "Upper bound inclusion 1" ) {

        auto b1 = upper_bound<int>::closed(3);
        auto b2 = upper_bound<int>::open(4);

        CHECK( !upper_bound<int>::includes(b1,b2) );
        CHECK( upper_bound<int>::includes(b2,b1) );
    }

    SECTION( "Upper bound inclusion 2" ) {

        auto b1 = upper_bound<int>::closed(3);
        auto b2 = upper_bound<int>::open(3);

        CHECK( upper_bound<int>::includes(b1,b2) );
        CHECK( !upper_bound<int>::includes(b2,b1) );
    }

    SECTION( "Upper bound inclusion 3" ) {

        auto b1 = upper_bound<int>::closed(3);
        auto b2 = upper_bound<int>::closed(3);

        CHECK( upper_bound<int>::includes(b1,b2) );
        CHECK( upper_bound<int>::includes(b2,b1) );
    }
}

TEST_CASE( "Tightness" ) {

    SECTION( "Get tighter" ) {

        auto b1 = lower_bound<int>::closed(3);
        auto b2 = lower_bound<int>::open(4);

        CHECK( lower_bound<int>::intersection(b1,b2) == b2);
    }

}

TEST_CASE( "Sorting Order" ) {

    SECTION( "Lower bounds" ) {

        auto b1 = lower_bound<int>::closed(3);
        auto b2 = lower_bound<int>::open(3);
        auto b3 = lower_bound<int>::closed(4);

        CHECK( b1 < b2 ); CHECK( b2 < b3 );
    }

    SECTION( "Upper bounds" ) {

        auto b1 = upper_bound<int>::open(3);
        auto b2 = upper_bound<int>::closed(3);
        auto b3 = upper_bound<int>::open(4);

        CHECK( b1 < b2 ); CHECK( b2 < b3 );
    }

}

TEST_CASE( "Addition" ) {

    SECTION( "Lower bounds" ) {

        auto b1 = lower_bound<int>::closed(3);
        auto b2 = lower_bound<int>::open(3);
        auto b3 = lower_bound<int>::closed(4);

        CHECK( b1 < b2 ); CHECK( b2 < b3 );
    }

    SECTION( "Upper bounds" ) {

        auto b1 = upper_bound<int>::open(3);
        auto b2 = upper_bound<int>::closed(3);
        auto b3 = upper_bound<int>::open(4);

        CHECK( b1 < b2 ); CHECK( b2 < b3 );
    }

}

TEST_CASE( "Complementation" ) {

    SECTION( "LOW2UP1" ) {

        auto b1 = lower_bound<int>::closed(3);

        auto expected = upper_bound<int>::open(3);

        CHECK( b1.complement() == expected);
    }


    SECTION( "LOW2UP2" ) {

        auto b1 = lower_bound<int>::open(3);

        auto expected = upper_bound<int>::closed(3);

        CHECK( b1.complement() == expected);
    }

    SECTION( "UP2LOW1" ) {

        auto b1 = upper_bound<int>::closed(3);

        auto expected = lower_bound<int>::open(3);

        CHECK( b1.complement() == expected);
    }

    SECTION( "UP2LOW2" ) {

        auto b1 = upper_bound<int>::open(3);

        auto expected = lower_bound<int>::closed(3);

        CHECK( b1.complement() == expected);
    }

}