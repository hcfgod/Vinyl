using System;
using Vinyl;

namespace Sandbox
{
    public class Player : Entity
    {
        private float speed = 1.0f;
        private Vector3 velocity = Vector3.Zero;

        void OnCreate()
        {
            Console.WriteLine($"Player.OnCreate - {EntityID}");
        }

        void OnUpdate(float timestep)
        {
            if(Input.IsKeyDown(KeyCode.W))
            {
                velocity.Y = 1.0f;
            }
            if (Input.IsKeyDown(KeyCode.S))
            {
                velocity.Y = -1.0f;
            }

            if (Input.IsKeyDown(KeyCode.A))
            {
                velocity.X = -1.0f;
            }
            if (Input.IsKeyDown(KeyCode.D))
            {
                velocity.X = 1.0f;
            }

            velocity *= speed;

            Vector3 translation = Translation;
            translation += velocity * timestep;

            Translation = translation;
        }
    }
}