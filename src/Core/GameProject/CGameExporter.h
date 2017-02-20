#ifndef CGAMEEXPORTER_H
#define CGAMEEXPORTER_H

#include "CAssetNameMap.h"
#include "CGameInfo.h"
#include "CGameProject.h"
#include "CResourceStore.h"
#include <Common/CAssetID.h>
#include <Common/Flags.h>
#include <Common/TString.h>
#include <Common/types.h>
#include <map>
#include <nod/nod.hpp>

class CGameExporter
{
    // Project Data
    CGameProject *mpProject;
    TWideString mProjectPath;
    CResourceStore *mpStore;
    EGame mGame;
    ERegion mRegion;
    TString mGameName;
    TString mGameID;
    float mBuildVersion;
    TWideString mDolPath;
    TWideString mApploaderPath;
    TWideString mPartitionHeaderPath;
    u32 mFilesystemAddress;

    // Directories
    TWideString mExportDir;
    TWideString mDiscDir;
    TWideString mContentDir;
    TWideString mCookedDir;

    TWideString mWorldsDirName;

    // Files
    nod::DiscBase *mpDisc;

    // Resources
    TWideStringList mPaks;
    std::map<CAssetID, bool> mAreaDuplicateMap;
    CAssetNameMap *mpNameMap;
    CGameInfo *mpGameInfo;

    struct SResourceInstance
    {
        TWideString PakFile;
        CAssetID ResourceID;
        CFourCC ResourceType;
        u32 PakOffset;
        u32 PakSize;
        bool Compressed;
        bool Exported;
    };
    std::map<CAssetID, SResourceInstance> mResourceMap;

public:
    CGameExporter(EGame Game, ERegion Region, const TString& rkGameName, const TString& rkGameID, float BuildVersion);
    bool Export(nod::DiscBase *pDisc, const TString& rkOutputDir, CAssetNameMap *pNameMap, CGameInfo *pGameInfo);
    void LoadResource(const CAssetID& rkID, std::vector<u8>& rBuffer);

    inline TWideString ProjectPath() const  { return mProjectPath; }

protected:
    bool ExtractDiscData();
    bool ExtractDiscNodeRecursive(const nod::Node *pkNode, const TWideString& rkDir, const nod::ExtractionContext& rkContext);
    void LoadPaks();
    void LoadResource(const SResourceInstance& rkResource, std::vector<u8>& rBuffer);
    void ExportCookedResources();
    void ExportResourceEditorData();
    void ExportResource(SResourceInstance& rRes);
    TString MakeWorldName(CAssetID WorldID);

    // Convenience Functions
    inline SResourceInstance* FindResourceInstance(const CAssetID& rkID)
    {
        u64 IntegralID = rkID.ToLongLong();
        auto Found = mResourceMap.find(IntegralID);
        return (Found == mResourceMap.end() ? nullptr : &Found->second);
    }
};

#endif // CGAMEEXPORTER_H
