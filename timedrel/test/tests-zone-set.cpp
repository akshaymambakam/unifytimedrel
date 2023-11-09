#include "catch.hpp"
#include "timedrel/zone_set.hpp"
#include "timedrel/utils.hpp"

using namespace timedrel;

// TEST_CASE( "Construction" ) {

//     SECTION( "Normalization 1" ) {

//         auto zs1 = zone_set<int>();

//         zs.add(zone<int>::make({2,8,2,8,0,6}));

//     }

// }

TEST_CASE( "Construction" ) {

    SECTION( "From Period" ) {

        auto zs1 = zone_set<int>();

        zs1.add_from_period(3, 5);

        auto expected = zone_set<int>();
        expected.add({3,5,3,5,0,2});

        CHECK( !zs1.empty() );
        CHECK( zs1 == expected );

    }

    SECTION( "From Period: Rise" ) {

        auto zs1 = zone_set<int>();

        zs1.add_from_period_rise_anchor(3, 5);

        auto expected = zone_set<int>();
        expected.add({3,3,3,5,0,2}, {1,1,0,1,0,1});

        CHECK( !zs1.empty() );
        CHECK( zs1 == expected );

    }

    SECTION( "From Period: Fall" ) {

        auto zs1 = zone_set<int>();

        zs1.add_from_period_fall_anchor(3, 5);

        auto expected = zone_set<int>();
        expected.add({3,5,5,5,0,2}, {1,0,1,1,0,1});

        CHECK( !zs1.empty() );
        CHECK( zs1 == expected );

    }

    SECTION( "From Period: Both edges" ) {

        auto zs1 = zone_set<int>();

        zs1.add_from_period_both_anchor(3, 5);

        auto expected = zone_set<int>();
        expected.add({3,5,5,5,2,2}, {1,1,1,1,1,1});

        CHECK( !zs1.empty() );
        CHECK( zs1 == expected );

    }

}

TEST_CASE( "Insertion" ) {

    SECTION( "Don't add already included regions" ) {

        auto zs = zone_set<int>();

        zs.add({0,9,0,9,0,9});
        zs.add({0,6,0,6,0,6});
        zs.add({2,8,2,8,0,6});

        zs = zone_set<int>::filter(zs);

        auto expected = zone_set<int>();
        expected.add({0,9,0,9,0,9});

        CHECK( zs == expected );

    }

    // SECTION( "Include" ) {

    //     auto zs = zone_set<int>();

    //     zs.add({0,6,0,6,0,6});
    //     zs.add({2,8,2,8,0,6});

    //     zs = zone_set<int>::filter(zs);

    //     auto expected = zone_set<int>();
    //     expected.add({2,8,2,8,0,6});
    //     expected.add({0,6,0,6,0,6});

    //     CHECK( zs == expected );

    // }

    SECTION( "Remove included zones" ) {

        auto zs = zone_set<int>();

        zs.add({2,8,2,8,0,6});
        zs.add({0,6,0,6,0,6});
        zs.add({0,9,0,9,0,9});

        zs = zone_set<int>::filter(zs);

        auto expected = zone_set<int>();
        expected.add({0,9,0,9,0,9});

        CHECK( zs == expected );

    }

}

TEST_CASE( "Intersection" ) {

    SECTION( "Intersecting Boxes" ) {

        auto zs1 = zone_set<int>();
        auto zs2 = zone_set<int>();

        zs1.add({0,6,9,16,3,16});
        zs1.add({8,16,18,24,2,16});

        zs2.add({4,10,13,21,3,17});
        zs2.add({14,20,22,28,2,14});

        auto result = zone_set<int>::intersection(zs1, zs2);

        auto expected = zone_set<int>();
        expected.add({4,6,13,16,7,12});
        expected.add({8,10,18,21,8,13});
        expected.add({14,16,22,24,6,10});

        CHECK( result == expected );

    }

}

TEST_CASE( "Pairwise Inclusion" ) {

    SECTION( "Empty set behavior" ) {

        auto empty = zone_set<int>();

        auto zs1 = zone_set<int>();
        zs1.add({1, 4, 2, 4, 0, 3});

        CHECK( zone_set<int>::includes(empty, empty) );
        CHECK( zone_set<int>::includes(zs1, empty) );
        CHECK( !zone_set<int>::includes(empty, zs1) );

    }

    SECTION( "Equivalent zone sets include each other" ) {

        auto zs1 = zone_set<int>();
        auto zs2 = zone_set<int>();

        zs1.add({1, 4, 2, 4, 0, 3});
        zs2.add({1, 4, 2, 4, 0, 3});

        CHECK( zone_set<int>::includes(zs1, zs2) );
        CHECK( zone_set<int>::includes(zs2, zs1) );

    }

    SECTION( "Equivalent zone sets include each other 2" ) {

        auto zs1 = zone_set<int>();
        auto zs2 = zone_set<int>();

        zs1.add({1, 4, 2, 4, 0, 3});
        zs1.add({3, 9, 3, 9, 3, 6});

        zs2.add({3, 9, 3, 9, 3, 6});
        zs2.add({1, 4, 2, 4, 0, 3});

        CHECK( zone_set<int>::includes(zs1, zs2) );
        CHECK( zone_set<int>::includes(zs2, zs1) );

    }

    SECTION( "Inclusion 1" ) {

        auto zs1 = zone_set<int>();
        auto zs2 = zone_set<int>();

        zs1.add({0,6,9,16,3,16});
        zs2.add({1,5,10,15,4,15});

        CHECK( zone_set<int>::includes(zs1, zs2) );
        CHECK( not zone_set<int>::includes(zs2, zs1) );
    }

    SECTION( "Inclusion 2" ) {

        auto zs1 = zone_set<int>();
        auto zs2 = zone_set<int>();

        zs1.add({1, 4, 2, 4, 0, 3});
        zs1.add({3, 9, 3, 9, 3, 6});

        zs2.add({3, 9, 3, 9, 3, 6});
        zs2.add({1, 4, 2, 4, 0, 3});
        zs2.add({7, 10, 7, 10, 0, 3});

        CHECK( not zone_set<int>::includes(zs1, zs2) );
        CHECK( zone_set<int>::includes(zs2, zs1) );

    }

}

TEST_CASE( "Filter" ) {

    SECTION( "Filter" ) {

        auto zs1 = zone_set<int>();

        zs1.add({1,5,11,12,6,11});
        zs1.add({1,5,13,16,8,15});
        zs1.add({2,3,17,18,14,16});
        zs1.add({3,4,14,15,10,12});

        auto result = zone_set<int>::filter(zs1);

        auto expected = zone_set<int>();
        expected.add({1,5,11,12,6,11});
        expected.add({1,5,13,16,8,15});
        expected.add({2,3,17,18,14,16});

        CHECK( result == expected );

    }

}

TEST_CASE( "Concatenation" ) {

    SECTION( "Self-Concatenation" ) {

        auto zs1 = zone_set<int>();
        auto zs2 = zone_set<int>();

        zs1.add({0,10,0,10,3,4});
        zs2.add({0,10,0,10,3,4});

        auto result = zone_set<int>::concatenation(zs1, zs2);

        auto expected = zone_set<int>();
        expected.add({0,10,0,10,6,8});

        CHECK( result == expected );
    }

    SECTION( "Closure" ) {

        auto zs1 = zone_set<int>();
        zs1.add({0,20,0,20,3,4});

        auto result = zone_set<int>::transitive_closure(zs1);

        auto expected = zone_set<int>();
        expected.add({0,20,0,20,3,4});
        expected.add({0,20,0,20,6,8});
        expected.add({0,20,0,20,9,12});
        expected.add({0,20,0,20,12,16});
        expected.add({0,20,0,20,15,20});

        CHECK( result == expected );

    }

}

TEST_CASE( "Complementation" ) {

    SECTION( "Empty and Universal" ) {

        auto zs1 = zone_set<int>();

        auto not_zs1 = zone_set<int>::complementation(zs1);
        auto expected = zone_set<int>();
        expected.add(zone<int>::universal());

        CHECK( not_zs1 == expected );

        auto result = zone_set<int>::complementation(not_zs1);
        CHECK( result == zs1 );

    }

    SECTION( "Double complementation" ) {

        auto zs1 = zone_set<int>();
        zs1.add({1, 7, 4, 9, 1, 5});

        auto not_zs1 = zone_set<int>::complementation(zs1);
        // std::cout << not_zs1 << std::endl; 

        auto result = zone_set<int>::complementation(not_zs1);
        // std::cout << result << std::endl; 

        CHECK( zone_set<int>::includes(result, zs1) );
        CHECK( zone_set<int>::includes(zs1, result) );


    }

    SECTION( "Double complementation merges zones if possible" ) {

        auto zs1 = zone_set<int>();
        zs1.add({10, 12, 16, 19, 0, 20});
        zs1.add({10, 12, 19, 21, 0, 20});

        auto not_zs1 = zone_set<int>::complementation(zs1);
        auto result = zone_set<int>::complementation(not_zs1);

        auto expected = zone_set<int>();
        expected.add({10,12,16,21,4,11});

        CHECK( zone_set<int>::includes(result, expected) );
        CHECK( zone_set<int>::includes(expected, result) );

    }

    SECTION( "Set difference" ) {

        auto zs1 = zone_set<int>();
        zs1.add({10, 12, 16, 19, 0, 20});
        zs1.add({10, 12, 19, 21, 0, 20});

        auto zs2 = zone_set<int>();
        zs2.add({10, 12, 18, 19, 0, 20});

        auto result = zone_set<int>::set_difference(zs1, zs2);

        auto expected = zone_set<int>();
        expected.add({10,12,16,18,4,8});
        expected.add({10,12,19,21,7,11});

        CHECK( result == expected );

    }

}

TEST_CASE( "General" ) {

    SECTION( "rvalues" ) {

        auto zs1 = zone_set<int>();
        auto zs2 = zone_set<int>();

        zs1.add({0,10,0,10,3,4});
        zs2.add({0,10,0,10,0,10});

        auto result = zone_set<int>::concatenation(zs1, zone_set<int>::duration_restriction(zs2,3,4));

        auto expected = zone_set<int>();
        expected.add({0,10,0,10,6,8});

        CHECK( result == expected );
    }

}
