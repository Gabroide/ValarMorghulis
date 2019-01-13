#ifndef __QuadTreeValar_h__
#define __QuadTreeValar_h__

#include <list>

#include "MathGeoLib\include\Geometry\AABB.h"

class GameObject;

class QuadTreeNode
{
	public:
		QuadTreeNode();
		QuadTreeNode(const math::AABB& aabb);
		~QuadTreeNode();

		bool	IsLeaf() const;

		void	Insert(GameObject* gameObject);
		void	CreateChilds();
		void	RecalculateSpace();

	public:
		int						maxItems	= 1;

		float					minSize		= 1000.0f;

		math::AABB				aabb;
		
	public:
		QuadTreeNode*			parent		= nullptr;
		QuadTreeNode*			childs[4];

		std::list<GameObject*>	goList;

};

class QuadTreeValar
{
	public:
		QuadTreeValar();
		~QuadTreeValar();

		void					InitQuadTree(const math::AABB& aabb, bool clearAllGameObjects = false);
		void					Insert(GameObject* gameObject, bool addToAllGameObjects = false);
		void					Remove(GameObject* gameObject);
		void					Clear();
		void					ExpandLimits(GameObject* gameObject);

	public:
		float					expansionValue	= 0.0f;

		math::AABB				quadLimits;
	
	public:
		QuadTreeNode*			root			= nullptr;
		
		std::list<GameObject*>	allGO;

};

#endif // __QuadTreeValar_h__
