#include "pch.h"
#include "CppUnitTest.h"
#include "../One_Dimensional_Array/Array.h"
#include "../One_Dimensional_Array/Exception.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ArrayADTTests
{
	TEST_CLASS(ArrayADTTests)
	{
		public:
			TEST_METHOD(TestDefaultArrayConstructor)
			{
				int expectedLength = 0;
				int expectedStartIndex = 0;

				Array<int> ra;

				Assert::AreEqual(expectedLength, ra.getLength());
				Assert::AreEqual(expectedStartIndex, ra.getStartIndex());
			}
			
			TEST_METHOD(TestOneArgConstructorValidLength)
			{
				int expectedLength = 5;
				int expectedStartIndex = 0;

				Array<int> ra(expectedLength);

				Assert::AreEqual(expectedLength, ra.getLength());
				Assert::AreEqual(expectedStartIndex, ra.getStartIndex());
			}

			void CreateInvalidLengthArray()
			{
				int expectedLength = -5;
				Array<int> ra(expectedLength, 0);
			}

			TEST_METHOD(TestOneArgConstructorInvalidLength)
			{
				// Syntax for lambda expression
				auto func = [this] { CreateInvalidLengthArray(); };
				
				Assert::ExpectException<Exception>(func);
			}

			TEST_METHOD(TestNonZeroPositiveStartingIndex)
			{
				int expectedLength = 5;
				int expectedStartingIndex = 10;
				int expectedValue = 25;

				Array<int> ra(expectedLength, expectedStartingIndex);

				ra[expectedStartingIndex] = expectedValue;

				Assert::AreEqual(expectedStartingIndex, ra.getStartIndex());
				Assert::AreEqual(expectedValue, ra[expectedStartingIndex]);
			}

			TEST_METHOD(TestNonZeroNegativeStartingIndex)
			{
				int expectedLength = 5;
				int expectedStartingIndex = -10;
				int expectedValue = 25;

				Array<int> ra(expectedLength, expectedStartingIndex);

				ra[expectedStartingIndex] = expectedValue;

				Assert::AreEqual(expectedStartingIndex, ra.getStartIndex());
				Assert::AreEqual(expectedValue, ra[expectedStartingIndex]);
			}

			TEST_METHOD(TestUpdatedStartingIndex)
			{
				int expectedLength = 5;
				int expectedStartingIndex = 5;
				int expectedValue = 25;

				Array<int> ra(expectedLength, expectedStartingIndex);
				ra[expectedStartingIndex] = expectedValue;

				int expectedNewStartIndex = 10;
				ra.setStartIndex(expectedNewStartIndex);

				Assert::AreEqual(expectedLength, ra.getLength());
				Assert::AreEqual(expectedNewStartIndex, ra.getStartIndex());
				Assert::AreEqual(expectedValue, ra[expectedNewStartIndex]);
			}

			TEST_METHOD(TestCopyConstructor)
			{
				int expectedLength = 5;
				int expectedStartingIndex = 10;
				int expectedValue = 25;

				Array<int> ra(expectedLength, expectedStartingIndex);
				ra[expectedStartingIndex] = expectedValue;

				Array<int> copyOfRa(ra);
				Assert::AreEqual(expectedLength, copyOfRa.getLength());
				Assert::AreEqual(expectedStartingIndex, copyOfRa.getStartIndex());
				Assert::AreEqual(expectedValue, copyOfRa[expectedStartingIndex]);
			}

			TEST_METHOD(TestOverloadedAssignmentOperator)
			{
				int expectedLength = 5;
				int expectedStartingIndex = 10;
				int expectedValue = 25;

				Array<int> ra(expectedLength, expectedStartingIndex);
				ra[expectedStartingIndex] = expectedValue;

				Array<int> raAssignment = ra;
				Assert::AreEqual(expectedLength, raAssignment.getLength());
				Assert::AreEqual(expectedStartingIndex, raAssignment.getStartIndex());
				Assert::AreEqual(expectedValue, raAssignment[expectedStartingIndex]);
			}

			void TriggerLowerOutOfBoundsException()
			{
				int expectedLength = 5;

				Array<int> ra(expectedLength);
				ra[-3];
			}

			TEST_METHOD(TestOutOfLowerBoundsIndexException)
			{
				auto func = [this] { TriggerLowerOutOfBoundsException(); };

				Assert::ExpectException<Exception>(func);
			}

			void TriggerUpperOutOfBoundsException()
			{
				int expectedLength = 5;

				Array<int> ra(expectedLength);
				ra[expectedLength + 1];
			}

			TEST_METHOD(TestOutOfUpperBoundsException)
			{
				auto func = [this] { TriggerUpperOutOfBoundsException(); };

				Assert::ExpectException<Exception>(func);
			}

			TEST_METHOD(TestResizeArrayToSmallerSize)
			{
				int expectedLength = 10;
				int expectedStartIndex = 0;
				int expectedValue = 25;

				Array<int> ra(expectedLength);
				ra[4] = expectedValue;

				int expectedNewLength = 5;
				ra.setLength(expectedNewLength);

				Assert::AreEqual(expectedNewLength, ra.getLength());
				Assert::AreEqual(expectedStartIndex, ra.getStartIndex());
				Assert::AreEqual(expectedValue, ra[expectedNewLength - 1]);
			}

			void TriggerOutOfBoundsExceptionAfterResize()
			{
				int expectedLength = 10;
				int expectedStartIndex = 0;
				int expectedValue = 25;

				Array<int> ra(expectedLength, expectedStartIndex);
				ra[4] = expectedValue;

				int expectedNewLength = 5;
				ra.setLength(expectedNewLength);

				ra[expectedLength - 1];
			}

			TEST_METHOD(TestResizeArrayToSmallerSizeWithUpperOutOfBoundException)
			{
				auto func = [this] { TriggerOutOfBoundsExceptionAfterResize(); };

				Assert::ExpectException<Exception>(func);
			}

			TEST_METHOD(TestConstantArrayMethods)
			{
				int expectedLength = 5;
				int expectedStartingIndex = 10;
				int expectedValue = 25;

				Array<int> ra(expectedLength, expectedStartingIndex);
				ra[expectedStartingIndex] = expectedValue;

				const Array<int> raAssignment = ra;
				Assert::AreEqual(expectedLength, raAssignment.getLength());
				Assert::AreEqual(expectedStartingIndex, raAssignment.getStartIndex());
				Assert::AreEqual(expectedValue, raAssignment[expectedStartingIndex]);
			}
	};
}
