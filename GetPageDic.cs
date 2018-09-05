using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace getPageDic
{
    class Program
    {
        static int Main(string[] args)
        {
            if (args.Count() != 1)
            {
                return -1;
            }
            int[] allDic = new int[10];
            Dictionary<int, int> theDictionary = new Dictionary<int, int>();
            int getNum = int.Parse(args[0]);
            if (getNum > 1)
            {
                int thePage = 0,k = 0;
                for (int i = 1; i <= getNum; i++)
                {
                    thePage = i;
                    while (thePage>0)
                    {

                        allDic[thePage%10]++;
                        thePage = thePage / 10; 
                    }
                    
                }
            }
            else
            {
                return -1;
            }
            for (int i = 0; i < 10; i++)
            {
                Console.WriteLine("{0}的数 = {1}",i, allDic[i]);
                theDictionary.Add(i, allDic[i]);
            }
            return 0;
        }
    }
}
