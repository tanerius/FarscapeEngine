#include "fspch.h"
#include "ScriptEngineRegistry.h"

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Scene/Entity.h"
#include "ScriptWrappers.h"
#include <iostream>

namespace Farscape {

    std::unordered_map<MonoType*, std::function<bool(Entity&)>> s_HasComponentFuncs;
    std::unordered_map<MonoType*, std::function<void(Entity&)>> s_CreateComponentFuncs;

    extern MonoImage* s_CoreAssemblyImage;

#define Component_RegisterType(Type) \
	{\
		MonoType* type = mono_reflection_type_from_name("Farscape." #Type, s_CoreAssemblyImage);\
		if (type) {\
			uint32_t id = mono_type_get_type(type);\
			s_HasComponentFuncs[type] = [](Entity& entity) { return entity.HasComponent<Type>(); };\
			s_CreateComponentFuncs[type] = [](Entity& entity) { entity.AddComponent<Type>(); };\
		} else {\
			HZ_CORE_ERROR("No C# component class found for " #Type "!");\
		}\
	}

    static void InitComponentTypes()
    {
        Component_RegisterType(TagComponent);
        Component_RegisterType(TransformComponent);
        Component_RegisterType(MeshComponent);
        Component_RegisterType(ScriptComponent);
        Component_RegisterType(CameraComponent);
        Component_RegisterType(SpriteRendererComponent);
    }

    void ScriptEngineRegistry::RegisterAll()
    {
        InitComponentTypes();

        mono_add_internal_call("Farscape.Noise::PerlinNoise_Native", Farscape::Script::Farscape_Noise_PerlinNoise);

        mono_add_internal_call("Farscape.Entity::GetTransform_Native", Farscape::Script::Farscape_Entity_GetTransform);
        mono_add_internal_call("Farscape.Entity::SetTransform_Native", Farscape::Script::Farscape_Entity_SetTransform);
        mono_add_internal_call("Farscape.Entity::CreateComponent_Native", Farscape::Script::Farscape_Entity_CreateComponent);
        mono_add_internal_call("Farscape.Entity::HasComponent_Native", Farscape::Script::Farscape_Entity_HasComponent);

        mono_add_internal_call("Farscape.MeshComponent::GetMesh_Native", Farscape::Script::Farscape_MeshComponent_GetMesh);
        mono_add_internal_call("Farscape.MeshComponent::SetMesh_Native", Farscape::Script::Farscape_MeshComponent_SetMesh);

        mono_add_internal_call("Farscape.Input::IsKeyPressed_Native", Farscape::Script::Farscape_Input_IsKeyPressed);

        mono_add_internal_call("Farscape.Texture2D::Constructor_Native", Farscape::Script::Farscape_Texture2D_Constructor);
        mono_add_internal_call("Farscape.Texture2D::Destructor_Native", Farscape::Script::Farscape_Texture2D_Destructor);
        mono_add_internal_call("Farscape.Texture2D::SetData_Native", Farscape::Script::Farscape_Texture2D_SetData);

        mono_add_internal_call("Farscape.Material::Destructor_Native", Farscape::Script::Farscape_Material_Destructor);
        mono_add_internal_call("Farscape.Material::SetFloat_Native", Farscape::Script::Farscape_Material_SetFloat);
        mono_add_internal_call("Farscape.Material::SetTexture_Native", Farscape::Script::Farscape_Material_SetTexture);

        mono_add_internal_call("Farscape.MaterialInstance::Destructor_Native", Farscape::Script::Farscape_MaterialInstance_Destructor);
        mono_add_internal_call("Farscape.MaterialInstance::SetFloat_Native", Farscape::Script::Farscape_MaterialInstance_SetFloat);
        mono_add_internal_call("Farscape.MaterialInstance::SetVector3_Native", Farscape::Script::Farscape_MaterialInstance_SetVector3);
        mono_add_internal_call("Farscape.MaterialInstance::SetTexture_Native", Farscape::Script::Farscape_MaterialInstance_SetTexture);

        mono_add_internal_call("Farscape.Mesh::Constructor_Native", Farscape::Script::Farscape_Mesh_Constructor);
        mono_add_internal_call("Farscape.Mesh::Destructor_Native", Farscape::Script::Farscape_Mesh_Destructor);
        mono_add_internal_call("Farscape.Mesh::GetMaterial_Native", Farscape::Script::Farscape_Mesh_GetMaterial);
        mono_add_internal_call("Farscape.Mesh::GetMaterialByIndex_Native", Farscape::Script::Farscape_Mesh_GetMaterialByIndex);
        mono_add_internal_call("Farscape.Mesh::GetMaterialCount_Native", Farscape::Script::Farscape_Mesh_GetMaterialCount);

        mono_add_internal_call("Farscape.MeshFactory::CreatePlane_Native", Farscape::Script::Farscape_MeshFactory_CreatePlane);

        // static bool IsKeyPressed(KeyCode key) { return s_Instance->IsKeyPressedImpl(key); }
        // 
        // static bool IsMouseButtonPressed(MouseCode button) { return s_Instance->IsMouseButtonPressedImpl(button); }
        // static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
        // static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
        // static float GetMouseY() { return s_Instance->GetMouseYImpl(); }
    }

}