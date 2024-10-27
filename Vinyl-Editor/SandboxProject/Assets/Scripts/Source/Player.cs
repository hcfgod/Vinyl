using System;
using Vinyl;

namespace Sandbox
{
    public class Player : Entity
    {
        private TransformComponent m_Transform;
        private Rigidbody2DComponent m_Rigidbody;

        void OnCreate()
        {
            Console.WriteLine($"Player.OnCreate - {EntityID}");

            m_Transform = GetComponent<TransformComponent>();
            m_Rigidbody = GetComponent<Rigidbody2DComponent>();
        }

        void OnUpdate(float timestep)
        {
            if(m_Rigidbody == null) return;

            float speed = 0.01f;
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
            m_Rigidbody.ApplyLinearImpulse(velocity.XY, true);
        }
    }
}