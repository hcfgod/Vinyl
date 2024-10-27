namespace Vinyl
{
    public class Input
    {
        public static bool IsKeyHeld(KeyCode keycode)
        {
            return InternalCalls.Input_IsKeyHeld(keycode);
        }

        public static bool IsMouseButtonHeld(MouseButton mousebutton)
        {
            return InternalCalls.Input_IsMouseButtonHeld(mousebutton);
        }
    }
}