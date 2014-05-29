#pragma once

#include "BsPrerequisites.h"
#include "BsGUIMaterialInfo.h"
#include "BsVector2I.h"
#include "BsRectI.h"

namespace BansheeEngine
{
	enum SpriteAnchor
	{
		SA_TopLeft,
		SA_TopCenter,
		SA_TopRight,
		SA_MiddleLeft,
		SA_MiddleCenter,
		SA_MiddleRight,
		SA_BottomLeft,
		SA_BottomCenter,
		SA_BottomRight
	};

	struct SpriteRenderElement
	{
		SpriteRenderElement()
			:vertices(nullptr), uvs(nullptr), indexes(nullptr), numQuads(0)
		{ }

		Vector2* vertices;
		Vector2* uvs;
		UINT32* indexes;
		UINT32 numQuads;
		GUIMaterialInfo matInfo;
	};

	class BS_EXPORT Sprite
	{
	public:
		Sprite();
		virtual ~Sprite();

		RectI getBounds(const Vector2I& offset, const RectI& clipRect) const;

		/**
		 * @brief	Returns the number of separate render elements in the sprite. Normally this is one, but some sprites
		 * 			may consist of multiple materials, in which case each will require it's own mesh (render element)
		 * 			
		 * @return	The number render elements.
		 */
		UINT32 getNumRenderElements() const;

		/**
		 * @brief	Gets a material for the specified render element index.
		 * 			
		 * @see getNumRenderElements()
		 * 		
		 * @return	Handle to the material.
		 */
		const GUIMaterialInfo& getMaterial(UINT32 renderElementIdx) const;

		/**
		 * @brief	Returns the number of quads that the specified render element will use. You will need this
		 * 			value when creating the buffers before calling "fillBuffer".
		 * 			
		 * @see getNumRenderElements()
		 * @see fillBuffer()
		 * 		
		 * @note	Number of vertices = Number of quads * 4
		 *			Number of indices = Number of quads * 6
		 *			
		 * @return	Number of quads for the specified render element. 
		 */
		UINT32 getNumQuads(UINT32 renderElementIdx) const;

		/**
		 * @brief	Fill the pre-allocated vertex, uv and index buffers with the mesh data for the
		 * 			specified render element.
		 * 			
		 * @see getNumRenderElements()
		 * @see	getNumQuads()
		 *
		 * @param	vertices			Previously allocated buffer where to store the vertices.
		 * @param	uv					Previously allocated buffer where to store the uv coordinates.
		 * @param	indices				Previously allocated buffer where to store the indices.
		 * @param	startingQuad		At which quad should the method start filling the buffer.
		 * @param	maxNumQuads			Total number of quads the buffers were allocated for. Used only
		 * 								for memory safety.
		 * @param	vertexStride		Number of bytes between of vertices in the provided vertex and uv data.
		 * @param	indexStride			Number of bytes between two indexes in the provided index data.
		 * @param	renderElementIdx	Zero-based index of the render element.
		 */
		UINT32 fillBuffer(UINT8* vertices, UINT8* uv, UINT32* indices, UINT32 startingQuad, UINT32 maxNumQuads, 
			UINT32 vertexStride, UINT32 indexStride, UINT32 renderElementIdx, const Vector2I& offset, const RectI& clipRect, bool clip = true) const;

		static void clipToRect(UINT8* vertices, UINT8* uv, UINT32 numQuads, UINT32 vertStride, const RectI& clipRect);
		static Vector2I getAnchorOffset(SpriteAnchor anchor, UINT32 width, UINT32 height);
	protected:
		mutable RectI mBounds;
		mutable Vector<SpriteRenderElement> mCachedRenderElements;

		void updateBounds() const;
		void clearMesh() const;
	};
}