
1. C#命令行参数和输出
// cmdline1.cs
// arguments: A B C
using System;

public class CommandLine
{
   public static void Main(string[] args)
   {
       // The Length property is used to obtain the length of the array. 
       // Notice that Length is a read-only property:
       Console.WriteLine("Number of command line parameters = {0}",
          args.Length);
       for(int i = 0; i < args.Length; i++)
       {
           Console.WriteLine("Arg[{0}] = [{1}]", i, args[i]);
       }
   }
}

The output will be:
Number of command line parameters = 3
Arg[0] = [A]
Arg[1] = [B]
Arg[2] = [C]


2、数组

int[] numbers; // declare numbers as an int array of any size
numbers = new int[10];  // numbers is a 10-element array
numbers = new int[20];  // now it's a 20-element array
