using System;

namespace Vinyl
{
    public class Entity
    {
        internal protected Entity()
        {
            EntityID = 0;
        }

        internal Entity(ulong entityID)
        {
            EntityID = entityID;
        }

        public readonly ulong EntityID;

        public TransformComponent Transform 
        {
            get
            {
                return GetComponent<TransformComponent>();
            }
        }

        public bool HasComponent<T>() where T : Component, new()
        {
            Type componentType = typeof(T);
            return InternalCalls.Entity_HasComponent(EntityID, componentType);
        }

        // TODO: Create a component caching system so we dont have to create a new component everytime we call GetComponent
        public T GetComponent<T>() where T : Component, new()
        {
            if(!HasComponent<T>()) return null;

            T component = new T() { Entity = this };
            return component;
        }

        public Entity FindEntityByName(string name)
        {
            ulong entityID = InternalCalls.Entity_FindEntityByName(name);
            if (entityID == 0)
                return null;
            return new Entity(entityID);
        }

        public T As<T>() where T : Entity, new()
        {
            object instance = InternalCalls.GetScriptInstance(EntityID);
            return instance as T;
        }
    }
}