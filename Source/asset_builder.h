#ifndef ASSET_BUILDER_H

#include <stdio.h>
#include <stdlib.h>


#include "ivan_platform.h"
#include "ivan_math.h"
#include "ivan_render_math.h"
#include "ivan_intrinsics.h"
#include "ivan_file_formats.h"

#include "ivan_voxel_shared.h"

#if BUILD_WITH_ASSIMP
#include <iostream>
#include <map>
#include <vector>

#include <assimp/Importer.hpp> 
#include <assimp/scene.h>     
#include <assimp/postprocess.h>
#include <assimp/cimport.h>
#endif

#define USE_FONTS_FROM_WINDOWS 0

#if USE_FONTS_FROM_WINDOWS
#include <Windows.h>
#define MAX_FONT_WIDTH 1024
#define MAX_FONT_HEIGHT 1024

GLOBAL_VARIABLE VOID* GlobalFontBits;
GLOBAL_VARIABLE HDC GlobalFontDeviceContext;
#else
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"
#endif

#define ONE_PAST_MAX_FONT_CODEPOINT (0x10FFFF + 1)

#define MAX_BONE_COUNT DDA_MAX_BONE_COUNT
#define MAX_INFLUENCE_BONE_COUNT DDA_MAX_INFLUENCE_BONE_COUNT
#define MAX_VERTICES_COUNT 100000
#define MAX_INDICES_COUNT 150000

enum asset_type{
	AssetType_Sound,
	AssetType_Bitmap,
	AssetType_Font,
	AssetType_FontGlyph,
	AssetType_VoxelAtlas,
	AssetType_VoxelAtlasTexture,

	//TODO(Dima): Do I actually need it???
	AssetType_Mesh,
	AssetType_Animation,
	AssetType_Model,

	AssetType_AnimatedModel,

	AssetType_Count,
};

struct loaded_font{

#if USE_FONTS_FROM_WINDOWS
	HFONT Win32Handle;
	TEXTMETRIC TextMetric;
#else
	void* FileContents;
	stbtt_fontinfo FontInfo;
	float Scale;
	float AscenderHeight;
	float DescenderHeight;
	float ExternalLeading;
#endif
	float LineAdvance;

	dda_font_glyph* Glyphs;
	float* HorizontalAdvance;

	uint32 MinCodePoint;
	uint32 MaxCodePoint;

	uint32 MaxGlyphCount;
	uint32 GlyphCount;

	uint32* GlyphIndexFromCodePoint;
	uint32 OnePastHighestCodepoint;
};

struct loaded_voxel_atlas{
	dda_voxel_atlas_texture AtlasTexture;
	voxel_tex_coords_set Materials[VoxelMaterial_Count];

	char* TextureFileName;

	uint32 TextureCount;
	uint32 MaxTextureCount;

	uint32 AtlasWidth;
	uint32 OneTextureWidth;
};

#if BUILD_WITH_ASSIMP
struct translation_key_frame{
    vec3 Translation;

    float TimeStamp;
};

struct rotation_key_frame{
    quat Rotation;

    float TimeStamp;
};

struct scaling_key_frame{
    vec3 Scaling;

    float TimeStamp;
};

struct joint_animation{
    uint32 TranslationFramesByteSize;
    uint32 RotationFramesByteSize;
    uint32 ScalingFramesByteSize;
    
    translation_key_frame* TranslationFrames;
    uint32 TranslationFramesCount;

    rotation_key_frame* RotationFrames;
    uint32 RotationFramesCount;

    scaling_key_frame* ScalingFrames;
    uint32 ScalingFramesCount;

    void* Free;
};

struct loaded_animation{
    joint_animation JointAnims[DDA_ANIMATION_MAX_BONE_COUNT];
    uint32 JointAnimsCount;

    uint32 Type;

    float LengthTime;
    float PlayCursorTime;
    float PlaybackSpeed;

    float TicksPerSecond;
};

struct loaded_animations_result{
    loaded_animation* Animations;
    uint32 AnimationsCount;

    void* Free;
};

struct bone_transform_info {
	char* Name;

	mat4 Offset;
	mat4 FinalTransformation;

	uint32* Children;
	uint32 ChildrenCount;
};

struct loaded_skeleton {
	std::map<std::string, uint32> BoneMapping;
	std::vector<bone_transform_info> Bones;
};

struct simple_vertex {
	vec3 P;
	vec2 UV;
	vec3 N;
	vec3 T;
};

struct skinned_vertex {
	vec3 P;
	vec2 UV;
	vec3 N;
	vec3 T;
	float Weights[MAX_INFLUENCE_BONE_COUNT];
	uint8 BoneIDs[MAX_INFLUENCE_BONE_COUNT];
};

struct loaded_mesh {
	union {
		simple_vertex SimpleVertices[MAX_VERTICES_COUNT];
		skinned_vertex SkinnedVertices[MAX_VERTICES_COUNT];
	};
	uint32 VerticesCount;

	dda_mesh_type Type;

	uint32 Indices[MAX_INDICES_COUNT];
	uint32 IndicesCount;
};

#define MAX_ANIMATIONS_PER_MODEL 32
struct loaded_animated_model {
	loaded_animation* Animations[MAX_ANIMATIONS_PER_MODEL];
	uint32 AnimationsCount;

	bool32 IsSkinned;

	loaded_skeleton Skeleton;

	loaded_mesh Mesh;
};
#endif

struct asset_source_font{
	loaded_font* Font;
};

struct asset_source_font_glyph{
	loaded_font* Font;
	uint32 Codepoint;
};

struct asset_source_bitmap{
	char* FileName;
};

struct asset_source_sound{
	char* FileName;
	uint32 FirstSampleIndex;
};

struct asset_source_voxel_atlas{
	loaded_voxel_atlas* Atlas;
};

struct asset_source_voxel_atlas_texture{
	char* FileName;

	loaded_voxel_atlas* Atlas;
};

#if BUILD_WITH_ASSIMP
struct asset_source_animation{
	loaded_animation* Animation;
};

struct asset_source_mesh {
	loaded_mesh* Mesh;
};

struct asset_source_animated_model {
	loaded_animated_model* AnimatedModel;
};
#endif

struct asset_source{
	asset_type Type;
	union{
		asset_source_bitmap Bitmap;
		asset_source_sound Sound;
		asset_source_font Font;
		asset_source_font_glyph Glyph;
		asset_source_voxel_atlas VoxelAtlas;
		asset_source_voxel_atlas_texture VoxelAtlasTexture;
#if BUILD_WITH_ASSIMP
		asset_source_mesh Mesh;
		asset_source_animation Animation;
		asset_source_animated_model AnimatedModel;
#endif
	};
};

#define IVAN_NUMBER_OF_ASSETS_TO_ALLOC 4096

struct game_assets{
	unsigned int TagCount;
	dda_tag Tags[IVAN_NUMBER_OF_ASSETS_TO_ALLOC];

	unsigned int AssetTypeCount;
	dda_asset_type AssetTypes[Asset_Count];

	unsigned int AssetCount;
	asset_source AssetSources[IVAN_NUMBER_OF_ASSETS_TO_ALLOC];
	dda_asset Assets[IVAN_NUMBER_OF_ASSETS_TO_ALLOC];

	dda_asset_type* DEBUGAssetType;
	unsigned int AssetIndex;
};

struct bone_vertex_info{
	float Weights[MAX_INFLUENCE_BONE_COUNT];
	uint32 BoneIDs[MAX_INFLUENCE_BONE_COUNT];
};

inline void AddBoneVertexInfo(bone_vertex_info* Info, float Weight, uint32 BoneID){
	for(uint32 InfluenceIndex = 0;
		InfluenceIndex < MAX_INFLUENCE_BONE_COUNT;
		InfluenceIndex++)
	{
		if(Info->Weights[InfluenceIndex] == 0.0f){
			Info->Weights[InfluenceIndex] = Weight;
			Info->BoneIDs[InfluenceIndex] = BoneID;
			break;
		}
	}
}


#if BUILD_WITH_ASSIMP
inline mat4 AiMatToOurs(aiMatrix4x4* aiMatr){
	mat4 Result;

	Result.E[0] = aiMatr->a1;
	Result.E[1] = aiMatr->a2;
	Result.E[2] = aiMatr->a3;
	Result.E[3] = aiMatr->a4;
	Result.E[4] = aiMatr->b1;
	Result.E[5] = aiMatr->b2;
	Result.E[6] = aiMatr->b3;
	Result.E[7] = aiMatr->b4;
	Result.E[8] = aiMatr->c1;
	Result.E[9] = aiMatr->c2;
	Result.E[10] = aiMatr->c3;
	Result.E[11] = aiMatr->c4;
	Result.E[12] = aiMatr->d1;
	Result.E[13] = aiMatr->d2;
	Result.E[14] = aiMatr->d3;
	Result.E[15] = aiMatr->d4;

	return(Result);
}

inline vec3 AiVec3ToOurs(aiVector3D aiVec){
	vec3 Result;
	Result.x = aiVec.x;
	Result.y = aiVec.y;
	Result.z = aiVec.z;
	return(Result);
}


inline vec2 AiVec2ToOurs(aiVector2D aiVec){
	vec2 Result;
	Result.x = aiVec.x;
	Result.y = aiVec.y;
	return(Result);
}

inline quat AiQuatToOurs(aiQuaternion quater){
	quat Result;
	Result.x = quater.x;
	Result.y = quater.y;
	Result.z = quater.z;
	Result.w = quater.w;
	return(Result);
}
#endif

#define ASSET_BUILDER_H
#endif