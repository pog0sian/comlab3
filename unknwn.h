#ifndef UNKNWN_H
#define UNKNWN_H

class IUnknown {
public:
    typedef int HRESULT;

    virtual HRESULT QueryInterface(const IID& iid, void** ppv) = 0;
    virtual unsigned long AddRef() = 0;
    virtual unsigned long Release() = 0;

};

#endif
