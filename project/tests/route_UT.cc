/**
 *
 * @Copyright 2019 3081 Staff, All rights reserved.
 *
 * STUDENTS:  DO NOT EDIT THIS FILE.  INSTEAD, MODIFY YOUR OWN PROJECT
 * CODE TO FIT THE SPECIFICATION GIVEN BY THE TESTS IN THIS FILE.
 *
 * If you DO modify it, we overwrite it with a fresh version from our repo
 * when grading, so you can't use it to fudge the tests anyway.
 *
 * This file is used by the CS3081W auto-grading system.
 *
 * Please note, the assessment tests for grading, will use the same include
 * files, class names, and function names for accessing students' code that you
 * find in this file.  So students, if you write your code so that it passes
 * these feedback tests, you can be assured that the auto-grader will at least
 * be able to properly link with your code.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <list>
#include <random>
#include <ctime>
#include <string>
#include <fstream>
#include "../src/passenger.h"
#include "../src/stop.h"
#include "../src/route.h"
#include "../src/mypassenger_gen.h"
#include "../src/bus.h"

/******************************************************
* TEST FEATURE SetUp
*******************************************************/


class RouteTests  : public ::testing::Test {
 protected:
    Route* CC_EB;
    Route* CC_WB;


    virtual void SetUp() {
        Stop ** CC_EB_stops = new Stop *[4];
        Stop ** CC_WB_stops = new Stop *[4];
        std::list<Stop *> CC_EB_stops_list;
        std::list<Stop *> CC_WB_stops_list;

        Stop * stop_CC_EB_1 = new Stop(0, 44.972392, -93.243774);
        //   student union station
        Stop * stop_CC_EB_2 = new Stop(1, 44.973580, -93.235071);
        //   Oak St & Washington Ave
        Stop * stop_CC_EB_3 = new Stop(2, 44.975392, -93.226632);
        //   before transit
        Stop * stop_CC_EB_4 = new Stop(3, 44.975837, -93.222174);

        Stop * stop_CC_WB_1 = new Stop(8, 44.984630, -93.186352);
    //   Buford & Gartner
        Stop * stop_CC_WB_2 = new Stop(9, 44.984482, -93.181657);
        //   Fairgrounds
        Stop * stop_CC_WB_3 = new Stop(10, 44.983703, -93.178846);
        //   Tway
        Stop * stop_CC_WB_4 = new Stop(11, 44.980663, -93.180808);

        CC_EB_stops_list.push_back(stop_CC_EB_1);
        CC_EB_stops[0] = stop_CC_EB_1;
        CC_EB_stops_list.push_back(stop_CC_EB_2);
        CC_EB_stops[1] = stop_CC_EB_2;
        CC_EB_stops_list.push_back(stop_CC_EB_3);
        CC_EB_stops[2] = stop_CC_EB_3;
        CC_EB_stops_list.push_back(stop_CC_EB_4);
        CC_EB_stops[3] = stop_CC_EB_4;

        CC_WB_stops_list.push_back(stop_CC_WB_1);
        CC_WB_stops[0] = stop_CC_WB_1;
        CC_WB_stops_list.push_back(stop_CC_WB_2);
        CC_WB_stops[1] = stop_CC_WB_2;
        CC_WB_stops_list.push_back(stop_CC_WB_3);
        CC_WB_stops[2] = stop_CC_WB_3;
        CC_WB_stops_list.push_back(stop_CC_WB_4);
        CC_WB_stops[3] = stop_CC_WB_4;

        double * CC_EB_distances = new double[4];
        double * CC_WB_distances = new double[4];
        CC_EB_distances[0] = 2;
        CC_EB_distances[1] = 2;
        CC_EB_distances[2] = 2;
        CC_EB_distances[3] = 2;

        CC_WB_distances[0] = 2;
        CC_WB_distances[1] = 2;
        CC_WB_distances[2] = 2;
        CC_WB_distances[3] = 2;

        std::list<double> CC_EB_probs;  // realistic .15, .3, .025, .05, .05, 0
        CC_EB_probs.push_back(.15);   // WB
        CC_EB_probs.push_back(.3);    // CMU
        CC_EB_probs.push_back(.025);  // O&W
        CC_EB_probs.push_back(.05);   // Pre-transit

        std::list<double> CC_WB_probs;  // realistic .35, .05, .01, .01, .2, 0
        CC_WB_probs.push_back(.35);     // SPSC
        CC_WB_probs.push_back(.05);     // Buford
        CC_WB_probs.push_back(.01);     // State fair
        CC_WB_probs.push_back(.01);

        MyPassengerGen * CC_EB_generator
            = new MyPassengerGen(CC_EB_probs, CC_EB_stops_list);
        MyPassengerGen * CC_WB_generator
            = new MyPassengerGen(CC_WB_probs, CC_WB_stops_list);


        CC_EB_generator->GeneratePassengers();
        CC_WB_generator->GeneratePassengers();


       CC_EB = new Route("Campus Connector - Eastbound", CC_EB_stops,
                            CC_EB_distances, 4, CC_EB_generator);
       CC_WB = new Route("Campus Connector - Westbound", CC_WB_stops,
                            CC_WB_distances, 4, CC_WB_generator);
    }

    virtual void TearDown() {
        delete CC_EB;
        delete CC_WB;
    }
};

TEST_F(RouteTests, Constructor) {
	CC_EB->UpdateRouteData();
	RouteData route_data1 = CC_EB->GetRouteData();
	EXPECT_EQ(route_data1.id, "Campus Connector - Eastbound");
	EXPECT_EQ((CC_EB->GetStops()).size(), 4);

}

TEST_F(RouteTests, IsAtEndTest) {
    EXPECT_EQ(CC_WB->IsAtEnd(), false);
    EXPECT_EQ(CC_EB->IsAtEnd(), false);
    for (int i =0; i< 4; i ++) {
        CC_WB->NextStop();
        CC_EB->NextStop();
    }
    EXPECT_EQ(CC_WB->IsAtEnd(), true);
    EXPECT_EQ(CC_EB->IsAtEnd(), true);
}

TEST_F(RouteTests, GetDestinationStopTest) {
    Stop* dest;
    dest = CC_EB->GetDestinationStop();
    EXPECT_EQ(dest->GetId(), 0);
    dest = CC_WB->GetDestinationStop();
    EXPECT_EQ(dest->GetId(), 8);
}

TEST_F(RouteTests, NextStopTest) {
    Stop* curstop;
    Stop* nextstop;
    curstop = CC_EB->GetDestinationStop();
    EXPECT_EQ(curstop->GetId(), 0);
    CC_EB->NextStop();
    nextstop = CC_EB->GetDestinationStop();
    EXPECT_EQ(nextstop->GetId(), 1);
    curstop = CC_WB->GetDestinationStop();
    EXPECT_EQ(curstop->GetId(), 8);
    CC_WB->NextStop();
    nextstop = CC_WB->GetDestinationStop();
    EXPECT_EQ(nextstop->GetId(), 9);
}

TEST_F(RouteTests, GetTotalRouteDistanceTest) {
    EXPECT_EQ(CC_WB->GetTotalRouteDistance(), 6.0);
    EXPECT_EQ(CC_EB->GetTotalRouteDistance(), 6.0);
}

TEST_F(RouteTests, GetNextStopDistanceTest) {
    CC_WB->NextStop();
    double get = CC_WB->GetNextStopDistance();
    EXPECT_EQ(get, 2.0);
    CC_EB->NextStop();
    EXPECT_EQ(CC_EB->GetNextStopDistance(), 2.0);
}

TEST_F(RouteTests, CloneTest) {
    Route* clone_route_;
    clone_route_ = CC_EB->Clone();
    EXPECT_EQ(clone_route_->GetTotalRouteDistance(),
              CC_EB->GetTotalRouteDistance());
}