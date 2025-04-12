#ifndef OBJBASE_H
#define OBJBASE_H

struct IID {
    unsigned long  Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char  Data4[8];

    bool operator==(const IID& other) const {
        return Data1 == other.Data1 &&
               Data2 == other.Data2 &&
               Data3 == other.Data3 &&
               std::equal(std::begin(Data4), std::end(Data4), std::begin(other.Data4));
    }
};

extern const IID IID_IX;
extern const IID IID_IY;
extern const IID IID_IZ;
extern const IID IID_IUnknown1;

#endif