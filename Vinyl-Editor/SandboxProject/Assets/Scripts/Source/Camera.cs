using Vinyl;

namespace Sandbox
{
    public class Camera : Entity
    {
        public Entity OtherEntity;
        public float DistanceFromPlayer = 5.0f;

        private TransformComponent transform;
        private TransformComponent playerTransform;
        private Entity m_Player;

        void OnCreate()
        {
            transform = Transform;
            m_Player = FindEntityByName("Player");
            playerTransform = m_Player.Transform;
        }

        void OnUpdate(float timestep)
        {
            if (m_Player != null)
            {
                transform.Translation = new Vector3(playerTransform.Translation.XY, DistanceFromPlayer);
            }

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