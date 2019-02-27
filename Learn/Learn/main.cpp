#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <vector>
#include <map>
#include "Data.h"

using namespace std;
vector<Data> s_DataVec;
Data s_DataMean;
vector<double> s_DataMeanVec;
double s_Weight = 0.5;
map<int,double> s_Value;

void Init()
{
	for (size_t i = 0; i < 36; i++)
	{
		s_Value[i] = 0;
	}
	for (size_t i = 0; i < 8; i++)
	{
		s_DataMean.m_DataVec.push_back(0);
	}
}

void ReadTxt(string file)
{
	
	ifstream infile;
	infile.open(file.data());   //将文件流对象与文件连接起来 
	assert(infile.is_open());   //若失败,则输出错误消息,并终止程序运行 

	string s;
	while (getline(infile, s))
	{
		Data dData;
		dData.SetData(s);
		cout << s << endl;
		s_DataVec.push_back(dData);
	}
	infile.close();            //关闭文件输入流 
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
	//for (size_t i = 0; i < 36; i++)
	//{
	//	s_Value[i] = s_Value[i] / s_DataVec.size();
	//}
}

void FindWeight()
{
	for (size_t i = 0; i < s_DataVec.size(); i++)
	{
		for (size_t j = 0; j < s_DataVec[i].m_DataVec.size(); j++)
		{
			s_Value[s_DataVec[i].m_DataVec[j]] = s_Value[s_DataVec[i].m_DataVec[j]] * (1 - pow(s_Weight, s_DataVec.size() - i));
		}
	}
	map<int, double>::iterator iter;

	for (iter = s_Value.begin(); iter != s_Value.end(); iter++)
	{
		printf("%d  %f  \n", iter->first, iter->second);
	}
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
	FindWeight();
	return 0;
}