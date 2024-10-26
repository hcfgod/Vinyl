#include "vlpch.h"
#include "ScriptEngine.h"

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/object.h>

namespace Vinyl
{
	struct ScriptEngineData
	{
		MonoDomain* RootDomain = nullptr;
		MonoDomain* AppDomain = nullptr;

		MonoAssembly* CoreAssembly = nullptr;
	};

	static ScriptEngineData* s_Data = nullptr;

	void ScriptEngine::Init()
	{
		s_Data = new ScriptEngineData();
		InitMono();
	}

	void ScriptEngine::Shutdown()
	{
		ShutdownMono();
		delete s_Data;
	}

	char* ReadBytes(const std::string& filepath, uint32_t* outSize)
	{
		std::ifstream stream(filepath, std::ios::binary | std::ios::ate);

		if (!stream)
		{
			// Failed to open the file
			return nullptr;
		}

		std::streampos end = stream.tellg();
		stream.seekg(0, std::ios::beg);
		uint32_t size = end - stream.tellg();

		if (size == 0)
		{
			// File is empty
			return nullptr;
		}

		char* buffer = new char[size];
		stream.read((char*)buffer, size);
		stream.close();

		*outSize = size;
		return buffer;
	}

	MonoAssembly* LoadCSharpAssembly(const std::string& assemblyPath)
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

		MonoAssembly* assembly = mono_assembly_load_from_full(image, assemblyPath.c_str(), &status, 0);
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

	MonoClass* GetClassInAssembly(MonoAssembly* assembly, const char* namespaceName, const char* className)
	{
		MonoImage* image = mono_assembly_get_image(assembly);
		MonoClass* klass = mono_class_from_name(image, namespaceName, className);

		if (klass == nullptr)
		{
			// Log error here
			return nullptr;
		}

		return klass;
	}

	MonoObject* InstantiateClass(const char* namespaceName, const char* className)
	{
		// Get a reference to the class we want to instantiate
		MonoClass* Klass = GetClassInAssembly(s_Data->CoreAssembly, namespaceName, className);

		// Allocate an instance of our class
		MonoObject* classInstance = mono_object_new(s_Data->AppDomain, Klass);

		if (classInstance == nullptr)
		{
			VL_CORE_ERROR("classInstance is nullptr");
		}

		// Call the parameterless (default) constructor
		mono_runtime_object_init(classInstance);

		return classInstance;
	}

	void CallPrintMessage(MonoObject* objectInstance)
	{
		// Get the MonoClass pointer from the instance
		MonoClass* instanceClass = mono_object_get_class(objectInstance);

		// Get a reference to the method in the class
		MonoMethod* method = mono_class_get_method_from_name(instanceClass, "PrintMessage", 0);

		if (method == nullptr)
		{
			// No method called "PrintFloatVar" with 0 parameters in the class, log error or something
			VL_CORE_ERROR("No method called 'PrintMessage' with 0 parameters in the class");
			return;
		}

		// Call the C# method on the objectInstance instance, and get any potential exceptions
		MonoObject* exception = nullptr;
		mono_runtime_invoke(method, objectInstance, nullptr, &exception);
	}

	void CallPrintCustomMessage(MonoObject* objectInstance, const char* message)
	{
		// Get the MonoClass pointer from the instance
		MonoClass* instanceClass = mono_object_get_class(objectInstance);

		// Get a reference to the method in the class
		MonoMethod* method = mono_class_get_method_from_name(instanceClass, "PrintCustomMessage", 1);

		if (method == nullptr)
		{
			// No method called "PrintFloatVar" with 0 parameters in the class, log error or something
			VL_CORE_ERROR("No method called 'PrintCustomMessage' with 1 parameter in the class");
			return;
		}

		// Call the C# method on the objectInstance instance, and get any potential exceptions
		MonoObject* exception = nullptr;

		MonoString* monoString = mono_string_new(s_Data->AppDomain, message);

		void* params[1] =
		{
			monoString
		};

		mono_runtime_invoke(method, objectInstance, params, &exception);
	}

	void ScriptEngine::InitMono()
	{
		mono_set_assemblies_path("mono/lib");

		MonoDomain* rootDomain = mono_jit_init("VinylJITRuntime");
		VL_CORE_ASSERT(rootDomain, "(Error) rootDomain");

		// Store the root domain pointer
		s_Data->RootDomain = rootDomain;

		// Create an App Domain
		s_Data->AppDomain = mono_domain_create_appdomain((char*)"VinylScriptRuntime", nullptr);
		mono_domain_set(s_Data->AppDomain, true);

		// Move this maybe
		s_Data->CoreAssembly = LoadCSharpAssembly("Resources/Scripts/Vinyl-ScriptCore.dll");
		if (!s_Data->CoreAssembly)
		{
			// Log an error message and handle failure
			VL_CORE_ERROR("Failed to load CoreAssembly\n");
			return;
		}

		PrintAssemblyTypes(s_Data->CoreAssembly);

		// Call the parameterless (default) constructor
		MonoObject* testInstance = InstantiateClass("Vinyl", "Main");
		CallPrintCustomMessage(testInstance, "Hello From Keith!");
	}

	void ScriptEngine::ShutdownMono()
	{
		mono_jit_cleanup(s_Data->RootDomain);

		s_Data->AppDomain = nullptr;
		s_Data->RootDomain = nullptr;
	}
}