/********************************************************************
Vireio Perception: Open-Source Stereoscopic 3D Driver
Copyright (C) 2012 Andres Hernandez

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
********************************************************************/

#ifndef D3DPROXYDEVICE_H_INCLUDED
#define D3DPROXYDEVICE_H_INCLUDED

#include "Direct3DDevice9.h"
#include "D3D9ProxySurface.h"
#include "D3D9ProxyTexture.h"
#include "Direct3DSwapChain9.h"
#include "Direct3DVertexBuffer9.h"
#include "Direct3DIndexBuffer9.h"
#include "Direct3DPixelShader9.h"
#include "Direct3DVertexShader9.h"
#include "Direct3DVertexDeclaration9.h"
#include "Direct3DQuery9.h"
#include "Direct3DStateBlock9.h"
#include "ProxyHelper.h"
#include "StereoView.h"
#include "MotionTracker.h"
#include <d3dx9.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "WrapperUtils.h"

class StereoView;

class D3DProxyDevice : public BaseDirect3DDevice9
{
public:
	D3DProxyDevice(IDirect3DDevice9* pDevice, BaseDirect3D9* pCreatedBy);
	virtual ~D3DProxyDevice();

	virtual void Init(ProxyHelper::ProxyConfig& cfg);
	
	virtual HRESULT WINAPI Reset(D3DPRESENT_PARAMETERS* pPresentationParameters);
	void SetupOptions(ProxyHelper::ProxyConfig& cfg);
	void SetupMatrices();
	void ComputeViewTranslation();
	void SetupText();
	void HandleControls(void);
	void HandleTracking(void);
	bool validRegister(UINT reg);
	
	
	virtual HRESULT WINAPI EndScene();
	virtual HRESULT WINAPI CreateVertexBuffer(UINT Length,DWORD Usage,DWORD FVF,D3DPOOL Pool,IDirect3DVertexBuffer9** ppVertexBuffer,HANDLE* pSharedHandle);
	virtual HRESULT WINAPI CreateIndexBuffer(UINT Length,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DIndexBuffer9** ppIndexBuffer,HANDLE* pSharedHandle);
	virtual HRESULT WINAPI CreateRenderTarget(UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Lockable,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle);
	virtual HRESULT WINAPI CreateDepthStencilSurface(UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Discard,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle);
	virtual HRESULT WINAPI CreateOffscreenPlainSurface(UINT Width,UINT Height,D3DFORMAT Format,D3DPOOL Pool,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle);
	virtual HRESULT WINAPI CreateTexture(UINT Width,UINT Height,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DTexture9** ppTexture,HANDLE* pSharedHandle);
	virtual HRESULT WINAPI CreateCubeTexture(UINT EdgeLength,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DCubeTexture9** ppCubeTexture,HANDLE* pSharedHandle);
	virtual HRESULT WINAPI CreateVolumeTexture(UINT Width,UINT Height,UINT Depth,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DVolumeTexture9** ppVolumeTexture,HANDLE* pSharedHandle);
	virtual HRESULT WINAPI CreatePixelShader(CONST DWORD* pFunction,IDirect3DPixelShader9** ppShader);
	virtual HRESULT WINAPI CreateVertexShader(CONST DWORD* pFunction,IDirect3DVertexShader9** ppShader);
	virtual HRESULT WINAPI CreateVertexDeclaration(CONST D3DVERTEXELEMENT9* pVertexElements,IDirect3DVertexDeclaration9** ppDecl);
	virtual HRESULT WINAPI CreateQuery(D3DQUERYTYPE Type,IDirect3DQuery9** ppQuery);
	virtual HRESULT WINAPI CreateStateBlock(D3DSTATEBLOCKTYPE Type,IDirect3DStateBlock9** ppSB);
	virtual HRESULT WINAPI Clear(DWORD Count,CONST D3DRECT* pRects,DWORD Flags,D3DCOLOR Color,float Z,DWORD Stencil);
	virtual HRESULT WINAPI ColorFill(IDirect3DSurface9* pSurface,CONST RECT* pRect,D3DCOLOR color);
	virtual HRESULT WINAPI DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType,UINT StartVertex,UINT PrimitiveCount);
	virtual HRESULT WINAPI DrawIndexedPrimitive(D3DPRIMITIVETYPE PrimitiveType,INT BaseVertexIndex,UINT MinVertexIndex,UINT NumVertices,UINT startIndex,UINT primCount);
	virtual HRESULT WINAPI DrawPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType,UINT PrimitiveCount,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride);
	virtual HRESULT WINAPI DrawIndexedPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType,UINT MinVertexIndex,UINT NumVertices,UINT PrimitiveCount,CONST void* pIndexData,D3DFORMAT IndexDataFormat,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride);
	virtual HRESULT WINAPI DrawRectPatch(UINT Handle,CONST float* pNumSegs,CONST D3DRECTPATCH_INFO* pRectPatchInfo);
	virtual HRESULT WINAPI DrawTriPatch(UINT Handle,CONST float* pNumSegs,CONST D3DTRIPATCH_INFO* pTriPatchInfo);
	virtual HRESULT WINAPI ProcessVertices(UINT SrcStartIndex,UINT DestIndex,UINT VertexCount,IDirect3DVertexBuffer9* pDestBuffer,IDirect3DVertexDeclaration9* pVertexDecl,DWORD Flags);
	virtual HRESULT WINAPI SetIndices(IDirect3DIndexBuffer9* pIndexData);
	virtual HRESULT WINAPI GetIndices(IDirect3DIndexBuffer9** ppIndexData);
	virtual HRESULT WINAPI SetStreamSource(UINT StreamNumber,IDirect3DVertexBuffer9* pStreamData,UINT OffsetInBytes,UINT Stride);
	virtual HRESULT WINAPI GetStreamSource(UINT StreamNumber,IDirect3DVertexBuffer9** ppStreamData,UINT* pOffsetInBytes,UINT* pStride);
	virtual HRESULT WINAPI SetRenderTarget(DWORD RenderTargetIndex,IDirect3DSurface9* pRenderTarget);
	virtual HRESULT WINAPI GetRenderTarget(DWORD RenderTargetIndex,IDirect3DSurface9** ppRenderTarget);
	virtual HRESULT WINAPI SetDepthStencilSurface(IDirect3DSurface9* pNewZStencil);
	virtual HRESULT WINAPI GetDepthStencilSurface(IDirect3DSurface9** ppZStencilSurface);
	virtual HRESULT WINAPI SetTexture(DWORD Stage,IDirect3DBaseTexture9* pTexture);
	virtual HRESULT WINAPI GetTexture(DWORD Stage,IDirect3DBaseTexture9** ppTexture);	
	virtual HRESULT WINAPI SetPixelShader(IDirect3DPixelShader9* pShader);
	virtual HRESULT WINAPI GetPixelShader(IDirect3DPixelShader9** ppShader);
	virtual HRESULT WINAPI SetVertexShader(IDirect3DVertexShader9* pShader);
	virtual HRESULT WINAPI GetVertexShader(IDirect3DVertexShader9** ppShader);
	virtual HRESULT WINAPI SetVertexDeclaration(IDirect3DVertexDeclaration9* pDecl);
	virtual HRESULT WINAPI GetVertexDeclaration(IDirect3DVertexDeclaration9** ppDecl);
	virtual HRESULT WINAPI EndStateBlock(IDirect3DStateBlock9** ppSB);
	virtual HRESULT WINAPI Present(CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion);
	virtual HRESULT WINAPI GetBackBuffer(UINT iSwapChain,UINT iBackBuffer,D3DBACKBUFFER_TYPE Type,IDirect3DSurface9** ppBackBuffer);
	virtual HRESULT WINAPI CreateAdditionalSwapChain(D3DPRESENT_PARAMETERS* pPresentationParameters,IDirect3DSwapChain9** pSwapChain);
	virtual HRESULT WINAPI GetSwapChain(UINT iSwapChain,IDirect3DSwapChain9** pSwapChain);
	virtual HRESULT WINAPI GetFrontBufferData(UINT iSwapChain,IDirect3DSurface9* pDestSurface);
	virtual HRESULT WINAPI GetRenderTargetData(IDirect3DSurface9* pRenderTarget,IDirect3DSurface9* pDestSurface);
	

	D3DXMATRIX matProjection;
	D3DXMATRIX matProjectionInv;
	D3DXMATRIX matViewTranslation;

	float* currentMatrix;

	// view translation settings
	int yaw_mode;			// 0 disabled, 1 enabled
	int pitch_mode;			// 0 disabled, 1 enabled
	int roll_mode;			// 0 disabled, 1 enabled
	int translation_mode;	// for head translation

	// Projection Matrix variables
	float n;	//Minimum z-value of the view volume
	float f;	//Maximum z-value of the view volume
	float l;	//Minimum x-value of the view volume
	float r;	//Maximum x-value of the view volume
	float t;	//Minimum y-value of the view volume
	float b;	//Maximum y-value of the view volume

	bool trackingOn;

	int eyeShutter;
	int game_type;
	float separation;
	float convergence;
	float aspect_multiplier;
	float yaw_multiplier;
	float pitch_multiplier;
	float roll_multiplier;
	float offset;
	float aspectRatio;
	bool swap_eyes;
	ProxyHelper::ProxyConfig config;
	int matrixIndex;
	bool saveDebugFile;
	std::ofstream debugFile;
	StereoView* stereoView;
	ID3DXFont *hudFont;

	time_t lastInputTime;

	MotionTracker* tracker;
	bool trackerInitialized;
	bool *m_keys;
	int SHOCT_mode;
	float centerlineR;
	float centerlineL;


	static enum ProxyTypes
	{
		MONO = 0,
		FIXED = 10,
		SOURCE = 100,
		SOURCE_L4D = 101,
		UNREAL = 200,
		UNREAL_MIRROR = 201,
		UNREAL_UT3 = 202,
		UNREAL_BIOSHOCK = 203,
		EGO = 300,
		EGO_DIRT = 301,
		REALV = 400,
		REALV_ARMA = 401,
		UNITY = 500,
		UNITY_SLENDER = 501,
		ADVANCED = 600,
		ADVANCED_SKYRIM = 601
	};


protected:
	
	

	enum EyeSide
	{
		Left = 1,
		Right = 2
	};


	
	virtual void OnCreateOrRestore();

	// Use to specify the side that you want to draw to
	bool setDrawingSide(enum EyeSide side);
	bool switchDrawingSide();

	


private:

	void ReleaseEverything();

	
	
	D3D9ProxySurface* m_pStereoBackBuffer;
	D3D9ProxySurface* m_pActiveStereoDepthStencil;
	BaseDirect3DIndexBuffer9* m_pActiveIndicies;
	BaseDirect3DPixelShader9* m_pActivePixelShader;
	BaseDirect3DVertexShader9* m_pActiveVertexShader;
	BaseDirect3DVertexDeclaration9* m_pActiveVertexDeclaration;
	BaseDirect3DSwapChain9* m_pPrimarySwapChain;

	// The render targets that are currently in use.
	std::vector<D3D9ProxySurface*> m_activeRenderTargets;
	
	// Textures assigned to stages. See (Get/Set)Texture
	std::unordered_map<DWORD, IDirect3DBaseTexture9*> m_activeTextureStages;
	std::unordered_map<UINT, BaseDirect3DVertexBuffer9*> m_activeVertexBuffers;



	enum EyeSide m_currentRenderingSide;



	
	
};

#endif