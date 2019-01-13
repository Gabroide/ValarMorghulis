#ifndef __ModuleRender_h__
#define __ModuleRender_h__

#include "Module.h"

class ComponentCamera;
class QuadTreeNode;

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
		
		void			PrintQuadNode(QuadTreeNode* quadNode) const;

	private:
		void			InitSDL();
		void			InitOpenGL() const;
		void			SetViewMatrix(ComponentCamera* camera) const;
		void			SetProjectionMatrix(ComponentCamera* camera) const;
		void			DrawDebugData(ComponentCamera* camera) const;
		void			GenerateBlockUniforms();
		void			PrintQuadTreeNode(QuadTreeNode* quadTreeNode) const;

	public:
		unsigned		ubo						= 0u;

		bool			cullingFromGameCamera	= true;
		bool			vsyncEnabled			= false;

	public:
		void*			context					= nullptr;

	protected:
		bool			showQuad				= true;
		
};

#endif // __ModuleRender_h__
