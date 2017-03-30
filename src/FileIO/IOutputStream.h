#ifndef IOUTPUTSTREAM_H
#define IOUTPUTSTREAM_H

#include "IOUtil.h"
#include <string>

class IOutputStream
{
protected:
    IOUtil::EEndianness mDataEndianness;
    std::string mDataDest;

public:
    void WriteBool(bool Val);
    void WriteByte(char Val);
    void WriteShort(short Val);
    void WriteLong(long Val);
    void WriteLongLong(long long Val);
    void WriteFloat(float Val);
    void WriteDouble(double Val);
    void WriteFourCC(long Val);
    void WriteString(const std::string& rkVal);
    void WriteString(const std::string& rkVal, unsigned long Count, bool Terminate = false);
    void WriteSizedString(const std::string& rkVal);
    void WriteWideString(const std::wstring& rkVal);
    void WriteWideString(const std::wstring& rkVal, unsigned long Count, bool Terminate = false);
    void WriteSizedWideString(const std::wstring& rkVal);

    bool GoTo(long Address);
    bool Skip(long SkipAmount);

    void WriteToBoundary(unsigned long Boundary, unsigned char Fill);
    void SetEndianness(IOUtil::EEndianness Endianness);
    void SetDestString(const std::string& rkDest);
    IOUtil::EEndianness GetEndianness() const;
    std::string GetDestString() const;

    virtual ~IOutputStream();
    virtual void WriteBytes(const void *pkSrc, unsigned long Count) = 0;
    virtual bool Seek(long Offset, long Origin) = 0;
    virtual bool Seek64(long long Offset, long Origin);
    virtual long Tell() const = 0;
    virtual long long Tell64() const;
    virtual bool EoF() const = 0;
    virtual bool IsValid() const = 0;
    virtual long Size() const = 0;
};
#endif // COUTPUTSTREAM_H
