using Vinyl;

namespace Sandbox
{
    public class Camera : Entity
    {
        private TransformComponent transform;

        void OnCreate()
        {
            transform = Transform;
        }

        void OnUpdate(float timestep)
        {
            float speed = 1.0f;
            Vector3 velocity = Vector3.Zero;

            if (Input.IsKeyHeld(KeyCode.W))
            {
                velocity.Y = 1.0f;
            }    
            else if (Input.IsKeyHeld(KeyCode.S))
            {
                velocity.Y = -1.0f;
            }

            if (Input.IsKeyHeld(KeyCode.A))
            {
                velocity.X = -1.0f;
            }
            else if (Input.IsKeyHeld(KeyCode.D))
            {
                velocity.X = 1.0f;
            }

            velocity *= speed;

            Vector3 translation = transform.Translation;
            translation += velocity * timestep;

            transform.Translation = translation;
        }
    }
}