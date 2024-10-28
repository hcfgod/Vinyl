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
        public enum BodyType { Static = 0, Dynamic, Kinematic }

        public Vector2 LinearVelocity
        {
            get
            {
                InternalCalls.Rigidbody2DComponent_GetLinearVelocity(Entity.EntityID, out Vector2 linearVelocity);
                return linearVelocity;
            }

            set
            {
                InternalCalls.Rigidbody2DComponent_SetLinearVelocity(Entity.EntityID, ref value);
            }
        }

        public BodyType Type
        {
            get => InternalCalls.Rigidbody2DComponent_GetType(Entity.EntityID);
            set => InternalCalls.Rigidbody2DComponent_SetType(Entity.EntityID, value);
        }

        public void ApplyLinearImpulse(Vector2 impulse, Vector2 worldPosition, bool wake)
        {
            InternalCalls.Rigidbody2DComponent_ApplyLinearImpulse(Entity.EntityID, ref impulse, ref worldPosition, wake);
        }

        public void ApplyLinearImpulse(Vector2 impulse, bool wake)
        {
            InternalCalls.Rigidbody2DComponent_ApplyLinearImpulseToCenter(Entity.EntityID, ref impulse, wake);
        }
    }

    public class TextComponent : Component
    {
        public string Text
        {
            get => InternalCalls.TextComponent_GetText(Entity.EntityID);
            set => InternalCalls.TextComponent_SetText(Entity.EntityID, value);
        }

        public Vector4 Color
        {
            get
            {
                InternalCalls.TextComponent_GetColor(Entity.EntityID, out Vector4 color);
                return color;
            }
            set
            {
                InternalCalls.TextComponent_SetColor(Entity.EntityID, ref value);
            }
        }

        public float Kerning
        {
            get => InternalCalls.TextComponent_GetKerning(Entity.EntityID);
            set => InternalCalls.TextComponent_SetKerning(Entity.EntityID, value);
        }

        public float LineSpacing
        {
            get => InternalCalls.TextComponent_GetLineSpacing(Entity.EntityID);
            set => InternalCalls.TextComponent_SetLineSpacing(Entity.EntityID, value);
        }
    }

    public class BoxCollider2DComponent : Component { }
    public class CircleCollider2DComponent : Component { }

    public class SpriteRendererComponent : Component { }
    public class CircleRendererComponent : Component { }

    public class ScriptComponent : Component { }
    //public class NativeScriptComponent : Component { }
}