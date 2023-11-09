#include "catch.hpp"
#include "timedrel/zone_set.hpp"
#include "timedrel/utils.hpp"

using namespace timedrel;

TEST_CASE( "Diamond Meets" ) {

    SECTION( "Meets" ) {

        auto zs = zone_set<int>();
        zs.add({3,9,12,19,7,11}, {1,0,0,1,0,1});

        auto result = zone_set<int>::diamond_meets(zs, 3, 5);

        auto expected = zone_set<int>();
        expected.add({12,19,0,100,3,5}, {0,1,0,1,0,1});

        CHECK( result == expected );

    }

    SECTION( "MetBy" ) {

        auto zs = zone_set<int>();
        zs.add({6,9,12,19,0,100}, {1,0,0,1,0,1});

        auto result = zone_set<int>::diamond_met_by(zs, 0, 3);

        auto expected = zone_set<int>();
        expected.add({0, 100, 6, 9, 0, 3}, {0,1,1,0,0,1});

        // std::cout << result << std::endl;

        CHECK( result == expected );

    }

    SECTION( "Begins" ) {

        auto zs = zone_set<int>();
        zs.add({6,9,12,17,5,10}, {1,0,0,1,0,1});

        auto result = zone_set<int>::diamond_starts(zs, 3, 5);

        auto expected = zone_set<int>();
        expected.add({6, 9, 7, 14, 0, 7}, {1,0,0,0,0,0});

        // std::cout << result << std::endl;

        CHECK( result == expected );

    }

    SECTION( "Begun" ) {

        auto zs = zone_set<int>();
        zs.add({6,9,12,17,5,10}, {1,0,0,1,0,1});

        auto result = zone_set<int>::diamond_started_by(zs, 3, 5);

        auto expected = zone_set<int>();
        expected.add({6, 9, 15, 22, 8, 15}, {1,0,0,1,0,1});

        // std::cout << result << std::endl;

        CHECK( result == expected );

    }

    SECTION( "Finished" ) {

        auto zs = zone_set<int>();
        zs.add({6,10,12,19,2,10}, {1,0,0,1,0,1});

        auto result = zone_set<int>::diamond_finished_by(zs, 3, 5);

        auto expected = zone_set<int>();
        expected.add({1, 7, 12, 19, 5, 15}, {1,0,0,1,0,1});

        // std::cout << zs << std::endl;

        CHECK( result == expected );

    }

    SECTION( "Finishes" ) {

        auto zs = zone_set<int>();
        zs.add({6,9,12,17,5,10}, {1,0,0,1,0,1});

        auto result = zone_set<int>::diamond_finishes(zs, 3, 5);

        auto expected = zone_set<int>();
        expected.add({9, 14, 12, 17, 0, 7}, {0,0,0,1,0,0});

        // std::cout << zs << std::endl;

        CHECK( result == expected );

    }
}