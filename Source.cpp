#include<iostream>
#include<vector>
#include<math.h>
using namespace std;

vector<bool> generation()
{
	vector<bool> check;
	for (size_t i = 0; i < 128; i++)
	{
		int random = rand() % 5729;
		bool binary = random % 2;
		check.push_back(binary);
	}
	return check;
}

void test_1(vector<bool> check)
{
	double sum = 0;
	for (auto i : check)
	{
		if (i == 0)
		{
			sum += -1;
		}
		else
		{
			sum += 1;
		}
	}
	sum /= sqrt(128);
	cout << " First test: " << erfc(sum / sqrt(2));
}

void test_2(vector<bool> check)
{
	double psi = 0;
	for (auto i : check) if (i == 1) psi++;
	psi /= 128;
	if (fabs(psi - 0.5) >= 2 / sqrt(128)) cout << 0;
	else
	{
		int V_n = 0;
		for (size_t i = 0; i < check.size() - 1; i++)
			if (check[i] != check[i + 1]) V_n++;
		cout << "Second test: " << erfc(fabs(V_n - 256 * psi * (1 - psi)) / (32 * psi * (1 - psi)));
	}
}

void test_3(vector<bool> check)
{
	vector<size_t> v = { 0, 0, 0, 0 };
	for (size_t i = 0; i < check.size(); i += 8) {
		size_t count = 0, max = 0;
		for (size_t j = i; j < (i + 8); j++) {
			if (check[j] == 1) {
				count++;
			}
			else {
				if (count > max)max = count;
				count = 0;
			}
		}
		if (count > max)max = count;
		if (max <= 1)v[0] += 1;
		if (max == 2)v[1] += 1;
		if (max == 3)v[2] += 1;
		if (max >= 4)v[3] += 1;
	}
	double pi[4] = { 0.2148, 0.3672, 0.2305, 0.1875 }, xi = 0;
	for (int i = 0; i < 4; i++)
	{
		xi += pow(v[i] - 16 * pi[i], 2) / (16 * pi[i]);
	}
	cout << "Third test: " << xi / 2;
}
int main()
{
	vector<bool> check = generation();
	for (auto i : check) cout << i;
	cout << endl;
	test_1(check);
	cout << endl;
	test_2(check);
	cout << endl;
	test_3(check);
	return 0;
}