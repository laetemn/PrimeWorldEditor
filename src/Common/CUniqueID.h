#ifndef CUNIQUEID_H
#define CUNIQUEID_H

#include "TString.h"
#include "types.h"
#include <FileIO/FileIO.h>

enum EUIDLength
{
    e32Bit = 4,
    e64Bit = 8,
    e128Bit = 16,
    eInvalidUIDLength = 0
};

class CUniqueID
{
    EUIDLength mLength;
    u8 mID[16];

public:
    CUniqueID();
    CUniqueID(u64 ID);
    CUniqueID(u64 ID, EUIDLength Length);
    CUniqueID(u64 Part1, u64 Part2);
    CUniqueID(const char* pkID);
    CUniqueID(IInputStream& rInput, EUIDLength Length);
    u32 ToLong() const;
    u64 ToLongLong() const;
    TString ToString() const;
    void Reverse();
    EUIDLength Length() const;
    void SetLength(EUIDLength Length);
    bool IsValid() const;

    // Operators
    void operator=(const u64& rkInput);
    void operator=(const char *pkInput);
    bool operator==(const CUniqueID& rkOther) const;
    bool operator!=(const CUniqueID& rkOther) const;
    bool operator>(const CUniqueID& rkOther) const;
    bool operator>=(const CUniqueID& rkOther) const;
    bool operator<(const CUniqueID& rkOther) const;
    bool operator<=(const CUniqueID& rkOther) const;
    bool operator==(u64 Other) const;
    bool operator!=(u64 Other) const;

    // Static
    static CUniqueID FromString(const TString& rkString);
    static CUniqueID FromData(void *pkData, EUIDLength Length);
    static CUniqueID RandomID();

    static CUniqueID skInvalidID32;
    static CUniqueID skInvalidID64;
    static CUniqueID skInvalidID128;
};

#endif // CUNIQUEID_H
