/*
 * Tests.cpp
 *
 *  Created on: 25 апр. 2015
 *      Author: vadim
 */

#include "Tests.h"
#include "GetAnglesRangeBy3PointsPredicate.h"
#include <iostream>
using namespace std;

Tests::Tests()
{
}

Tests::~Tests()
{
}

void Tests::test_functor_IsAngleInShortPathBetweenTwo()
{
	//left side test
	{
		GetAnglesRangeBy3PointsPredicate IsBetween( 230, 240, true, 235 );
		bool is = IsBetween.getIsTestAngleInRange();
		cout << "expected true is=" << ( ( is == true ) ? "true" : "false" ) << endl << flush;
		int minAngle = IsBetween.getMinAngle();
		int maxAngle = IsBetween.getMaxAngle();
		cout << "min 230=" << minAngle << "; max 235=" << maxAngle << endl << flush;
	}
	{
		GetAnglesRangeBy3PointsPredicate IsBetween( 240, 230, true, 235 );
		bool is = IsBetween.getIsTestAngleInRange();
		cout << "expected true is=" << ( ( is == true ) ? "true" : "false" ) << endl << flush;
		int minAngle = IsBetween.getMinAngle();
		int maxAngle = IsBetween.getMaxAngle();
		cout << "min 235=" << minAngle << "; max 240=" << maxAngle << endl << flush;
	}
	{
		GetAnglesRangeBy3PointsPredicate IsBetween( 30, 240, false, 200 );
		bool is = IsBetween.getIsTestAngleInRange();
		cout << "expected true is=" << ( ( is == true ) ? "true" : "false" ) << endl << flush;
		int minAngle = IsBetween.getMinAngle();
		int maxAngle = IsBetween.getMaxAngle();
		cout << "min 30=" << minAngle << "; max 200=" << maxAngle << endl << flush;
	}
	{
		GetAnglesRangeBy3PointsPredicate IsBetween( 240, 30, false, 200 );
		bool is = IsBetween.getIsTestAngleInRange();
		cout << "expected true is=" << ( ( is == true ) ? "true" : "false" ) << endl << flush;
		int minAngle = IsBetween.getMinAngle();
		int maxAngle = IsBetween.getMaxAngle();
		cout << "min 200=" << minAngle << "; max 240=" << maxAngle << endl << flush;
	}

	//right side test
	{
		GetAnglesRangeBy3PointsPredicate IsBetween( 230, 240, false, 10 );
		bool is = IsBetween.getIsTestAngleInRange();
		cout << "expected true is=" << ( ( is == true ) ? "true" : "false" ) << endl << flush;
		int minAngle = IsBetween.getMinAngle();
		int maxAngle = IsBetween.getMaxAngle();
		cout << "min 10=" << minAngle << "; max 230=" << maxAngle << endl << flush;
	}
	{
		GetAnglesRangeBy3PointsPredicate IsBetween( 240, 230, false, 300 );
		bool is = IsBetween.getIsTestAngleInRange();
		cout << "expected true is=" << ( ( is == true ) ? "true" : "false" ) << endl << flush;
		int minAngle = IsBetween.getMinAngle();
		int maxAngle = IsBetween.getMaxAngle();
		cout << "min -120=" << minAngle << "; max -60=" << maxAngle << endl << flush;
	}
	{
		GetAnglesRangeBy3PointsPredicate IsBetween( 30, 240, true, 10 );
		bool is = IsBetween.getIsTestAngleInRange();
		cout << "expected true is=" << ( ( is == true ) ? "true" : "false" ) << endl << flush;
		int minAngle = IsBetween.getMinAngle();
		int maxAngle = IsBetween.getMaxAngle();
		cout << "min 10=" << minAngle << "; max 30=" << maxAngle << endl << flush;
	}
	{
		GetAnglesRangeBy3PointsPredicate IsBetween( 240, 30, true, 300 );
		bool is = IsBetween.getIsTestAngleInRange();
		cout << "expected true is=" << ( ( is == true ) ? "true" : "false" ) << endl << flush;
		int minAngle = IsBetween.getMinAngle();
		int maxAngle = IsBetween.getMaxAngle();
		cout << "min -120=" << minAngle << "; max -60=" << maxAngle << endl << flush;
	}
	{
		GetAnglesRangeBy3PointsPredicate IsBetween( 200, 0, true, 300 );
		bool is = IsBetween.getIsTestAngleInRange();
		cout << "expected true is=" << ( ( is == true ) ? "true" : "false" ) << endl << flush;
		int minAngle = IsBetween.getMinAngle();
		int maxAngle = IsBetween.getMaxAngle();
		cout << "min -160=" << minAngle << "; max -60=" << maxAngle << endl << flush;
	}
	{
		GetAnglesRangeBy3PointsPredicate IsBetween( 0, 90, false, 138 );
		bool is = IsBetween.getIsTestAngleInRange();
		cout << "expected true is=" << ( ( is == true ) ? "true" : "false" ) << endl << flush;
		int minAngle = IsBetween.getMinAngle();
		int maxAngle = IsBetween.getMaxAngle();
		cout << "min -222=" << minAngle << "; max 0=" << maxAngle << endl << flush;
	}
	{
		GetAnglesRangeBy3PointsPredicate IsBetween( 354, 206, false, 193 );
		bool is = IsBetween.getIsTestAngleInRange();
		cout << "expected true is=" << ( ( is == true ) ? "true" : "false" ) << endl << flush;
		int minAngle = IsBetween.getMinAngle();
		int maxAngle = IsBetween.getMaxAngle();
		cout << "min -6=" << minAngle << "; max 193=" << maxAngle << endl << flush;
	}
}








