#pragma once
class Util
{
public:
	static int min(int A, int B);
};

int Util::min(int A, int B)
{
	if (A < B)
		return A;
	else
		return B;
}

