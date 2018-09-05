using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace getLucky
{
    class Program
    {
        static int Main(string[] args)
        {
            if (args.Count() != 1)
            {
                return -1;
            }
            int getNum = int.Parse(args[0]);
            int LuckyNum = 0;
            if (getNum > 0)
            {
                double squrt = Math.Log(getNum,2);
                int k = (int)Math.Log(getNum, 2);
                LuckyNum = 2 * (getNum -(int)Math.Pow(2,k)) + 1;
            }
            else
            {
                return -1;
            }
            Console.WriteLine("the lucky number :" + LuckyNum);
            return 0;
        }
    }
}
