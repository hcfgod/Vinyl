namespace Vinyl
{
    public class Input
    {
        public static bool IsKeyDown(KeyCode keycode)
        {
            return InternalCalls.Input_IsKeyDown(keycode);
        }

        public static bool IsMouseDown(MouseCode mousecode)
        {
            return InternalCalls.Input_IsMouseDown(mousecode);
        }
    }
}