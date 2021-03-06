#ifndef IVAN_RENDER_GROUP_H
#define IVAN_RENDER_GROUP_H

#include "ivan_platform.h"
#include "ivan_intrinsics.h"
#include "ivan_render_math.h"

enum camera_transform_flag{
	CameraTransform_IsOrthographic = 0x1,
	CameraTransform_IsInfinitePerspective = 0x2,
	CameraTransform_IsInfiniteOrthographic = 0x4,
};

struct loaded_bitmap{
	void* Memory;
	int32 Width;
	int32 Height;

	real32 WidthOverHeight;
	vec2 AlignPercentage;

	void* TextureHandle;
};

enum render_group_entry_type{
	RenderGroupEntry_render_entry_clear = 1,
	RenderGroupEntry_render_entry_rectangle,
	RenderGroupEntry_render_entry_bitmap,
	RenderGroupEntry_render_entry_coordinate_system,
	RenderGroupEntry_render_entry_voxel_mesh,
	RenderGroupEntry_render_entry_cube,
	RenderGroupEntry_render_entry_mesh,
};

struct render_group_entry_header{
	render_group_entry_type Type;
};

struct push_buffer_result{
	render_group_entry_header* Header;
};

struct render_entry_coordinate_system{
	vec2 Origin;
	vec2 XAxis;
	vec2 YAxis;
	vec4 Color;
	loaded_bitmap* Texture;
};

struct render_entry_clear{
	vec4 Color;
};

struct render_entry_rectangle{
	vec2 Dim;
	vec2 P;
	vec4 Color;
};

struct render_entry_bitmap{
	loaded_bitmap* Bitmap;
	vec2 P;
	vec4 Color;
	vec2 Size;
};

struct render_setup{
	vec3 CameraP;
	mat4 Projection;
	mat4 CameraTransform;

	vec4 Planes[6];

	vec3 DirLightDirection;
	vec3 DirLightDiffuse;
	vec3 DirLightAmbient;
};

struct render_entry_mesh{
	loaded_mesh* Mesh;
	vec3 P;

	render_setup Setup;
};

enum camera_plane_index{
	CameraPlane_Near,
	CameraPlane_Far,
	CameraPlane_Left,
	CameraPlane_Right,
	CameraPlane_Bottom,
	CameraPlane_Top,

	CameraPlane_Count,
};

struct voxel_chunk_mesh;
struct render_entry_voxel_mesh{
	voxel_chunk_mesh* Mesh;
	loaded_bitmap* Bitmap;
	vec3 P;
	int32 OneTextureWidth;

	render_setup Setup;
};

struct bitmap_dimension{
	vec2 Size;
	vec2 Align;
	vec3 P;
};

struct render_group_transform{
	bool32 Orthographic;

	real32 MetersToPixels;
	vec2 ScreenCenter;

	real32 FocalLength;
	real32 DistanceAboveTarget;

	vec3 OffsetP;
	real32 Scale;
};

struct render_group{
	struct game_assets* Assets;
	real32 GlobalAlphaChannel;

	vec2 MonitorHalfDimInMeters;
	render_group_transform Transform;

	render_setup LastRenderSetup;

	game_render_commands* Commands;
	uint32 GenerationID;
};

#endif