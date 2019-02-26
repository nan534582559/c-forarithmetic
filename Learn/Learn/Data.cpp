#include "Data.h"


void SplitString(const string& s, vector<string>& v, const string& c)
{
	string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while (string::npos != pos2)
	{
		v.push_back(s.substr(pos1, pos2 - pos1));

		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));
}

void Data::SetData(string str)
{
	vector<string> NumVec;
	SplitString(str, NumVec, " ");
	for (size_t i = 1; i < NumVec.size(); i++)
	{
		m_DataVec.push_back(atoi(NumVec[i].c_str()));

	}
}
