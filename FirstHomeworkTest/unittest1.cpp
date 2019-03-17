#include "stdafx.h"
#include "CppUnitTest.h"
#include "../FirstHomework/Matrix.h"
#include<string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FirstHomeworkTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Matrix mat = Matrix("../FirstHomework/matrica.txt");

		}

	};
}