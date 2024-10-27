namespace Vinyl
{
    public class Component
    {
        public Entity Entity { get; internal set; }
    }

    public class CameraComponent : Component { }

    public class TransformComponent : Component
    {
        public Vector3 Translation
        {
            get
            {
                InternalCalls.TransformComponent_GetTranslation(Entity.EntityID, out Vector3 translation);
                return translation;
            }

            set
            {
                InternalCalls.TransformComponent_SetTranslation(Entity.EntityID, ref value);
            }
        }
    }
    public class Rigidbody2DComponent : Component
    {
        public void ApplyLinearImpulse(Vector2 impulse, Vector2 worldPosition, bool wake)
        {
            InternalCalls.Rigidbody2DComponent_ApplyLinearImpulse(Entity.EntityID, ref impulse, ref worldPosition, wake);
        }

        public void ApplyLinearImpulse(Vector2 impulse, bool wake)
        {
            InternalCalls.Rigidbody2DComponent_ApplyLinearImpulseToCenter(Entity.EntityID, ref impulse, wake);
        }
    }
    public class BoxCollider2DComponent : Component { }
    public class CircleCollider2DComponent : Component { }

    public class SpriteRendererComponent : Component { }
    public class CircleRendererComponent : Component { }

    public class ScriptComponent : Component { }
    //public class NativeScriptComponent : Component { }
}