#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include<algorithm>
#include "Data.h"

using namespace std;
vector<Data> s_DataVec;
Data s_DataMean;
vector<double> s_DataMeanVec;
double s_Weight = 0.1;
map<int,double> s_Value;

void Init()
{
	for (size_t i = 1; i < 36; i++)
	{
		s_Value[i] = 0;
	}
	for (size_t i = 1; i < 8; i++)
	{
		s_DataMean.m_DataVec.push_back(0);
	}
}

void ReadTxt(string file)
{
	ifstream infile;
	infile.open(file.data());   
	assert(infile.is_open());   

	string s;
	while (getline(infile, s))
	{
		Data dData;
		dData.SetData(s);
		cout << s << endl;
		s_DataVec.push_back(dData);
	}
	infile.close();
}

void FindMean()
{
	for (size_t i = 0; i < s_DataVec.size(); i++)
	{
		for (size_t j = 0; j < s_DataVec[i].m_DataVec.size(); j++)
		{
			s_DataMean.m_DataVec[j] = s_DataVec[i].m_DataVec[j] + s_DataMean.m_DataVec[j];
		}
	}
	for (size_t i = 0; i < s_DataMean.m_DataVec.size(); i++)
	{
		s_DataMeanVec.push_back((double)s_DataMean.m_DataVec[i] / s_DataVec.size());
	}
}

void FindValueData()
{
	for (size_t i = 0; i < s_DataVec.size(); i++)
	{
		for (size_t j = 0; j < s_DataVec[i].m_DataVec.size(); j++)
		{
			s_Value[s_DataVec[i].m_DataVec[j]] = s_Value[s_DataVec[i].m_DataVec[j]] + 1;
		}
	}
	map<int, double>::iterator iter;
	for (iter = s_Value.begin(); iter != s_Value.end(); iter++)
	{
		printf("%d  %f  \n", iter->first, iter->second);
	}
}

bool cmp(const pair<int, double>& a, const pair<int, double>& b) {
	return a.second > b.second;
}

void FindWeight()
{
	for (size_t i = 0; i < s_DataVec.size(); i++)
	{
		for (size_t j = 0; j < s_DataVec[i].m_DataVec.size(); j++)
		{
			s_Value[s_DataVec[i].m_DataVec[j]] = s_Value[s_DataVec[i].m_DataVec[j]] * (1 - pow(s_Weight, i + 1));
		}
	}
	map<int, double>::iterator iter;

	for (iter = s_Value.begin(); iter != s_Value.end(); iter++)
	{
		printf("%d  %f  \n", iter->first, iter->second);
	}
	ofstream outfile;
	outfile.open("data.csv", ios::app);
	//assert(infile.is_open());
	vector<pair<int, double>> vec(s_Value.begin(), s_Value.end());
	//对线性的vector进行排序
	sort(vec.begin(), vec.end(), cmp);
	for (int i = 1; i < 10; ++i)
	{
		cout << vec[i].first << "   ==  " << vec[i].second << endl;
		outfile << vec[i].first << "," ;
	}
	outfile << endl;
	outfile.close();
}

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		printf("it is not input");
	}
	Init();
	ReadTxt(argv[1]);
	for (size_t i = 0; i < s_DataVec.size(); i++)
	{
		for (size_t j = 0; j < s_DataVec[i].m_DataVec.size(); j++)
		{
			printf("%d  ", s_DataVec[i].m_DataVec[j]);
		}
		printf("\n");
	}
	FindMean();
	
	for (size_t i = 0; i < s_DataMeanVec.size(); i++)
	{
		printf("%f  ", s_DataMeanVec[i]);
	}
	printf("\n");
	FindValueData();
	for (size_t i = 0; i < 9; i++)
	{
		Init();
		FindValueData();
		s_Weight = 0.1 + i*0.1;
		FindWeight();
	}
	return 0;
}