using System;

namespace Vinyl
{
    public class Main
    {
        public float FloatVar { get; set; }

        public Main()
        {
            Console.WriteLine("Main Constructor");
        }

        public void PrintMessage()
        {
            Console.Write("Hello from c#");
        }

        public void PrintCustomMessage(string message)
        {
            Console.Write($"C# Says: {message}");
        }
    }
}