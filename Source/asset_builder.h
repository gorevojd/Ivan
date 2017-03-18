#ifndef ASSET_BUILDER_H

#include <stdio.h>
#include <stdlib.h>

#include "ivan_platform.h"
#include "ivan_math.h"
#include "ivan_render_math.h"
#include "ivan_intrinsics.h"
#include "ivan_file_formats.h"


enum asset_type{
	AssetType_Sound,
	AssetType_Bitmap,
	AssetType_Model,
	AssetType_Font,

	AssetType_Count,
};

struct asset_source{
	asset_type Type;
	char* FileName;
	unsigned int FirstSampleIndex;
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



#define ASSET_BUILDER_H
#endif