#ifndef __ModuleRender_h__
#define __ModuleRender_h__

#include "Module.h"

#include <list>
#include <vector>

#include "ImGuizmo\ImGuizmo.h"

class GameObject;
class QuadTreeNode;
class ComponentMesh;
class ComponentCamera;

class ModuleRender : public Module
{
	public:
		ModuleRender();
		~ModuleRender();

		bool			Init()			override;
		bool			CleanUp()		override;

		update_status	PreUpdate()		override;
		update_status	Update()		override;
		update_status	PostUpdate()	override;
	
		void			DrawImGuizmo(float width, float height, float winPosX, float winPosY);

	private:
		void			InitSDL();
		void			InitOpenGL() const;
		void			SetViewMatrix(ComponentCamera* camera) const;
		void			SetProjectionMatrix(ComponentCamera* camera) const;
		void			GenerateBlockUniforms();
		void			GenerateFallBackMaterial();
		void			DrawMeshes(ComponentCamera* camera);
		void			DrawDebugData(ComponentCamera* camera) const;
		void			PrintQuadNode(QuadTreeNode* quadNode) const;
		void			DrawWithoutCulling(ComponentMesh* mesh) const;
		void			CullingFromQuadTree(ComponentCamera* camera, ComponentMesh* mesh);
		void			CullingFromFrustum(ComponentCamera* camera, ComponentMesh* mesh) const;
		void			PrintRayCast() const;

	public:
		bool			frustCulling			= true;
		bool			vsyncEnabled			= false;
		bool			showQuad				= false;
		bool			showRayCast				= false;
		bool			selectAncestorOnClick	= true;

		unsigned		fallback				= 0u;
		unsigned		ubo						= 0u;

		int				frustumCullingType		= 0;
		int				imGuizmoActivity		= 0;
		int				imGuizmoMode			= 0;

		float			sceneViewportX			= 0.0f;
		float			sceneViewportY			= 0.0f;

	public:
		void*			context					= nullptr;

		std::list<ComponentMesh*> meshes;
	
		std::vector<GameObject*> quadGOCollided;

};

#endif // __ModuleRender_h__
