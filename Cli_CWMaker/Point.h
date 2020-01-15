#pragma once

namespace CWM
{

	ref class Point
	{
	public:
		int top, left;

		Point(int top, int left)
		{
			this->top = top;
			this->left = left;
		}
		Point(Point^ other)
		{
			this->top = other->top;
			this->left = other->left;
		}
	};

}
