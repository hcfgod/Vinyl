#include "vlpch.h"

#include "Vinyl/Scripting/ScriptEngine.h"
#include "Vinyl/Scripting/ScriptGlue.h"
#include "Vinyl/Scene/Scene.h"
#include "Vinyl/Scene/Entity.h"

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>

#include <glm/vec3.hpp>

namespace Vinyl
{
	namespace Utils {

		// TODO: move to FileSystem class
		static char* ReadBytes(const std::filesystem::path& filepath, uint32_t* outSize)
		{
			std::ifstream stream(filepath, std::ios::binary | std::ios::ate);

			if (!stream)
			{
				// Failed to open the file
				return nullptr;
			}

			std::streampos end = stream.tellg();
			stream.seekg(0, std::ios::beg);
			uint64_t size = end - stream.tellg();

			if (size == 0)
			{
				// File is empty
				return nullptr;
			}

			char* buffer = new char[size];
			stream.read((char*)buffer, size);
			stream.close();

			*outSize = (uint32_t)size;
			return buffer;
		}

		static MonoAssembly* LoadMonoAssembly(const std::filesystem::path& assemblyPath)
		{
			uint32_t fileSize = 0;
			char* fileData = ReadBytes(assemblyPath, &fileSize);

			// NOTE: We can't use this image for anything other than loading the assembly because this image doesn't have a reference to the assembly
			MonoImageOpenStatus status;
			MonoImage* image = mono_image_open_from_data_full(fileData, fileSize, 1, &status, 0);

			if (status != MONO_IMAGE_OK)
			{
				const char* errorMessage = mono_image_strerror(status);
				// Log some error message using the errorMessage data
				return nullptr;
			}

			std::string pathString = assemblyPath.string();
			MonoAssembly* assembly = mono_assembly_load_from_full(image, pathString.c_str(), &status, 0);
			mono_image_close(image);

			// Don't forget to free the file data
			delete[] fileData;

			return assembly;
		}

		void PrintAssemblyTypes(MonoAssembly* assembly)
		{
			MonoImage* image = mono_assembly_get_image(assembly);
			const MonoTableInfo* typeDefinitionsTable = mono_image_get_table_info(image, MONO_TABLE_TYPEDEF);
			int32_t numTypes = mono_table_info_get_rows(typeDefinitionsTable);

			for (int32_t i = 0; i < numTypes; i++)
			{
				uint32_t cols[MONO_TYPEDEF_SIZE];
				mono_metadata_decode_row(typeDefinitionsTable, i, cols, MONO_TYPEDEF_SIZE);

				const char* nameSpace = mono_metadata_string_heap(image, cols[MONO_TYPEDEF_NAMESPACE]);
				const char* name = mono_metadata_string_heap(image, cols[MONO_TYPEDEF_NAME]);
				VL_CORE_TRACE("{}.{}", nameSpace, name);
			}
		}
	}

	struct ScriptEngineData
	{
		MonoDomain* RootDomain = nullptr;
		MonoDomain* AppDomain = nullptr;

		MonoAssembly* CoreAssembly = nullptr;
		MonoImage* CoreAssemblyImage = nullptr;

		ScriptClass EntityClass;

		std::unordered_map<std::string, Ref<ScriptClass>> EntityClasses;
		std::unordered_map<UUID, Ref<ScriptInstance>> EntityInstances;

		// Runtime
		Scene* SceneContext = nullptr;
	};

	static ScriptEngineData* s_Data = nullptr;

#if 0 example/testing
	void CallPrintMessage(MonoObject* objectInstance)
	{
		MonoMethod* printMessageFunc = s_Data->EntityClass.GetMethod("PrintMessage", 0);
		if (printMessageFunc == nullptr)
		{
			// No method called "PrintFloatVar" with 0 parameters in the class, log error or something
			VL_CORE_ERROR("No method called 'PrintMessage' with 0 parameters in the class");
			return;
		}

		s_Data->EntityClass.InvokeMethod(objectInstance, printMessageFunc);
	}

	void CallPrintCustomMessage(MonoObject* objectInstance, const char* message)
	{
		// Get a reference to the method in the class
		MonoMethod* PrintCustomMessageFunc = s_Data->EntityClass.GetMethod("PrintCustomMessage", 1);

		if (PrintCustomMessageFunc == nullptr)
		{
			// No method called "PrintFloatVar" with 0 parameters in the class, log error or something
			VL_CORE_ERROR("No method called 'PrintCustomMessage' with 1 parameter in the class");
			return;
		}

		MonoString* monoString = mono_string_new(s_Data->AppDomain, "Hello World from C++!");
		MonoMethod* printCustomMessageFunc = s_Data->EntityClass.GetMethod("PrintCustomMessage", 1);
		void* stringParam = monoString;
		s_Data->EntityClass.InvokeMethod(objectInstance, printCustomMessageFunc, &stringParam);
	}
#endif

	void ScriptEngine::Init()
	{
		s_Data = new ScriptEngineData();
		InitMono();
		LoadAssembly("Resources/Scripts/Vinyl-ScriptCore.dll");
		LoadAssemblyClasses(s_Data->CoreAssembly);

		ScriptGlue::RegisterFunctions();

		// Retrieve and instantiate class (with constructor)
		s_Data->EntityClass = ScriptClass("Vinyl", "Entity");

#if 0 example/testing
		//CallPrintMessage(instance);
		//CallPrintCustomMessage(instance, "Hello From Keith!");
#endif
	}

	void ScriptEngine::Shutdown()
	{
		ShutdownMono();
		delete s_Data;
	}

	void ScriptEngine::InitMono()
	{
		mono_set_assemblies_path("mono/lib");

		MonoDomain* rootDomain = mono_jit_init("VinylJITRuntime");
		VL_CORE_ASSERT(rootDomain, "(Error) rootDomain");

		// Store the root domain pointer
		s_Data->RootDomain = rootDomain;
	}

	void ScriptEngine::ShutdownMono()
	{
		if (s_Data->AppDomain)
		{
			// Switch back to the root domain before unloading the AppDomain
			mono_domain_set(s_Data->RootDomain, false);

			// Unload the AppDomain to clean up loaded assemblies
			mono_domain_unload(s_Data->AppDomain);
			s_Data->AppDomain = nullptr;
		}

		// Cleanup the JIT after unloading domains
		if (s_Data->RootDomain)
		{
			mono_jit_cleanup(s_Data->RootDomain);
			s_Data->RootDomain = nullptr;
		}
	}

	void ScriptEngine::LoadAssembly(const std::filesystem::path& filePath)
	{
		// Create an App Domain
		s_Data->AppDomain = mono_domain_create_appdomain((char*)"VinylScriptRuntime", nullptr);
		mono_domain_set(s_Data->AppDomain, true);

		s_Data->CoreAssembly = Utils::LoadMonoAssembly(filePath);
		s_Data->CoreAssemblyImage = mono_assembly_get_image(s_Data->CoreAssembly);

		//Utils::PrintAssemblyTypes(s_Data->CoreAssembly);
	}

	void ScriptEngine::OnRuntimeStart(Scene* scene)
	{
		s_Data->SceneContext = scene;
	}

	void ScriptEngine::OnRuntimeStop()
	{
		s_Data->SceneContext = nullptr;
		s_Data->EntityInstances.clear();
	}

	bool ScriptEngine::EntityClassExists(const std::string& fullClassName)
	{
		return s_Data->EntityClasses.find(fullClassName) != s_Data->EntityClasses.end();
	}

	void ScriptEngine::OnCreateEntity(Entity entity)
	{
		const auto& scriptComponent = entity.GetComponent<ScriptComponent>();

		if (ScriptEngine::EntityClassExists(scriptComponent.ClassName))
		{
			Ref<ScriptInstance> scriptInstance = CreateRef<ScriptInstance>(s_Data->EntityClasses[scriptComponent.ClassName], entity);
			s_Data->EntityInstances[entity.GetUUID()] = scriptInstance;

			scriptInstance->InvokeOnCreate();
		}
	}

	void ScriptEngine::OnUpdateEntity(Entity entity, TimeStep timestep)
	{
		UUID entityUUID = entity.GetUUID();
		VL_CORE_ASSERT(s_Data->EntityInstances.find(entity.GetUUID()) != s_Data->EntityInstances.end(), "");

		Ref<ScriptInstance> scriptInstance =  s_Data->EntityInstances[entityUUID];
		scriptInstance->InvokeOnUpdate((float)timestep);
	}

	Scene* ScriptEngine::GetSceneContext()
	{
		return s_Data->SceneContext;
	}

	std::unordered_map<std::string, Ref<ScriptClass>> ScriptEngine::GetEntityClasses()
	{
		return s_Data->EntityClasses;
	}

	void ScriptEngine::LoadAssemblyClasses(MonoAssembly* monoAssembly)
	{
		s_Data->EntityClasses.clear();

		MonoImage* image = mono_assembly_get_image(monoAssembly);
		const MonoTableInfo* typeDefinitionsTable = mono_image_get_table_info(image, MONO_TABLE_TYPEDEF);
		int32_t numTypes = mono_table_info_get_rows(typeDefinitionsTable);

		MonoClass* entityClass = mono_class_from_name(image, "Vinyl", "Entity");

		for (int32_t i = 0; i < numTypes; i++)
		{
			uint32_t cols[MONO_TYPEDEF_SIZE];
			mono_metadata_decode_row(typeDefinitionsTable, i, cols, MONO_TYPEDEF_SIZE);

			const char* nameSpace = mono_metadata_string_heap(image, cols[MONO_TYPEDEF_NAMESPACE]);
			const char* name = mono_metadata_string_heap(image, cols[MONO_TYPEDEF_NAME]);
			std::string fullName;
			if (strlen(nameSpace) != 0)
			{
				fullName = fmt::format("{}.{}", nameSpace, name);
			}
			else
			{
				fullName = name;
			}

			MonoClass* monoClass = mono_class_from_name(image, nameSpace, name);

			if (monoClass == entityClass) continue;

			bool isEntityClass = mono_class_is_subclass_of(monoClass, entityClass, false);
			if (isEntityClass)
			{
				s_Data->EntityClasses[fullName] = CreateRef<ScriptClass>(nameSpace, name);
			}
		}
	}

	static MonoClass* GetClassInAssembly(MonoAssembly* assembly, const char* namespaceName, const char* className)
	{
		MonoImage* image = mono_assembly_get_image(assembly);
		MonoClass* monoClass = mono_class_from_name(image, namespaceName, className);

		if (monoClass == nullptr)
		{
			// Log error here
			return nullptr;
		}

		return monoClass;
	}

	MonoObject* ScriptEngine::InstantiateClass(MonoClass* monoClass)
	{
		MonoObject* instance = mono_object_new(s_Data->AppDomain, monoClass);
		mono_runtime_object_init(instance);
		return instance;
	}

	ScriptClass::ScriptClass(const std::string& classNamespace, const std::string& className) : m_ClassNamespace(classNamespace), m_ClassName(className)
	{
		m_MonoClass = mono_class_from_name(s_Data->CoreAssemblyImage, classNamespace.c_str(), className.c_str());
	}

	MonoObject* ScriptClass::Instantiate()
	{
		return ScriptEngine::InstantiateClass(m_MonoClass);
	}

	MonoMethod* ScriptClass::GetMethod(const std::string& name, int parameterCount)
	{
		return mono_class_get_method_from_name(m_MonoClass, name.c_str(), parameterCount);
	}

	MonoObject* ScriptClass::InvokeMethod(MonoObject* instance, MonoMethod* method, void** params)
	{
		return mono_runtime_invoke(method, instance, params, nullptr);
	}

	ScriptInstance::ScriptInstance(Ref<ScriptClass> scriptClass, Entity entity) : m_ScriptClass(scriptClass)
	{
		m_Instance = scriptClass->Instantiate();

		m_Constructor = s_Data->EntityClass.GetMethod(".ctor", 1);
		m_OnCreateMethod = scriptClass->GetMethod("OnCreate", 0); 
		m_OnUpdateMethod = scriptClass->GetMethod("OnUpdate", 1);

		// Call Entity Constructor
		{
			UUID entityID = entity.GetUUID();
			void* param = &entityID;

			m_ScriptClass->InvokeMethod(m_Instance, m_Constructor, &param);
		}
	}

	void ScriptInstance::InvokeOnCreate()
	{
		m_ScriptClass->InvokeMethod(m_Instance, m_OnCreateMethod);
	}

	void ScriptInstance::InvokeOnUpdate(float timestep)
	{
		void* param = &timestep;
		m_ScriptClass->InvokeMethod(m_Instance, m_OnUpdateMethod, &param);
	}
}