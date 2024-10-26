using System;

namespace Vinyl
{
    public struct Vector3
    {
        public float X, Y, Z;

        public Vector3(float x, float y, float z)
        {
            X = x; 
            Y = y; 
            Z = z;
        }

        public override string ToString()
        {
            return $"{X}, {Y}, {Z}";
        }
    }

    public class Entity
    {
        public float FloatVar { get; set; }

        public Entity()
        {
            Console.WriteLine("Main Constructor");
            Log("Keith", 8058);

            Vector3 pos = new Vector3(5.0f, 2.0f, 1.0f);
            Vector3 result = Log(pos);
            Console.WriteLine(result.ToString());
        }

        public void PrintMessage()
        {
            Console.WriteLine("Hello from c#");
        }

        public void PrintCustomMessage(string message)
        {
            Console.Write($"C# Says: {message}");
        }

        private void Log(string text, int paramater)
        {
            InternalCalls.NativeLog(text, paramater);
        }

        private Vector3 Log(Vector3 paramater)
        {
            InternalCalls.NativeLog_Vector(ref paramater, out Vector3 result);
            return result;
        }
    }
}