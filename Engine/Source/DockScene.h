#ifndef __DockScene_h__
#define __DockScene_h__

#include "Dock.h"
#include "MathGeoLib\include\Math\float2.h"

class DockScene : public Dock
{
	public:
		DockScene();
		~DockScene();

		void	Draw() override;

		bool	IsFocused() const;

	public:
		bool			focus		= false;

		math::float2	viewport	= math::float2::zero;

};

#endif // __DockScene_h__