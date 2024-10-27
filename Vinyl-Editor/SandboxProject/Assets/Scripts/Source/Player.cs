using System;
using Vinyl;

namespace Sandbox
{
    public class Player : Entity
    {
        public float m_Speed = 0.0f;

        private TransformComponent m_Transform;
        private Rigidbody2DComponent m_Rigidbody;
        private Vector3 velocity = Vector3.Zero;

        void OnCreate()
        {
            Console.WriteLine($"Player.OnCreate - {EntityID}");

            m_Transform = GetComponent<TransformComponent>();
            m_Rigidbody = GetComponent<Rigidbody2DComponent>();
        }

        void OnUpdate(float timestep)
        {
            if (m_Rigidbody == null) return;

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

            velocity *= m_Speed * timestep;
            m_Rigidbody.ApplyLinearImpulse(velocity.XY, true);
        }
    }
}