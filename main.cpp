#include <iostream>
#include "objbase.h"
#include "unknwn.h"


class IX : public IUnknown {
    virtual void Fx() = 0;
};

class IY : public IUnknown {
    virtual void Fy() = 0;
};

class IZ : public IUnknown {
    virtual void Fz() = 0;
};

class CA : public IX, public IY {

    const int S_OK = 0;
    const int E_NOINTERFACE = 1;

    virtual unsigned long AddRef() { return 0; }
    virtual unsigned long Release() { return 0; }

    virtual HRESULT QueryInterface(const IID& iid, void** ppv) {
        if (iid == IID_IUnknown1) {
            std::cout << "QueryInterface: return pointer to IUnknown" << std::endl;
            *ppv = static_cast<IX*>(this);
        } else if (iid == IID_IX) {
            std::cout << "QueryInterface: return pointer to IX" << std::endl;
            *ppv = static_cast<IX*>(this);
        } else if (iid == IID_IY) {
            std::cout << "QueryInterface: return pointer to IY" << std::endl;
            *ppv = static_cast<IY*>(this);
        } else {
            std::cout << "Interface not supported" << std::endl;
            *ppv = NULL;
            return E_NOINTERFACE;
        }
        reinterpret_cast<IUnknown*>(*ppv)->AddRef();
        return S_OK;
    }

    virtual void Fx() { std::cout << "CA::Fx" << std::endl; }

    virtual void Fy() { std::cout << "CA::Fy" << std::endl; }
};

IUnknown* CreateInstance() {
    IUnknown* pI = static_cast<IX*>(new CA);
    pI->AddRef();
    return pI;
}

int main() {

    std::cout << "Hello, World!" << std::endl;

    typedef int hr;

    std::cout << "Client: get pointer to IUnknown" << std::endl;
    IUnknown* pIUnknown = CreateInstance();

    std::cout << "\nClient: get pointer to IX" << std::endl;
    IX* pIX = NULL;
    hr = pIUnknown->QueryInterface(IID_IX, (void**)&pIX);
    if (SUCCEEDED(hr)) {
        std::cout << "Client: IX received successfully" << std::endl;
        pIX->Fx();
    }

    std::cout << "\nClient: get pointer to IY" << std::endl;
    IY* pIY = NULL;
    hr = pIUnknown->QueryInterface(IID_IY, (void**)&pIY);
    if (SUCCEEDED(hr)) {
        std::cout << "Client: IY received successfully" << std::endl;
        pIY->Fy();
    }

    std::cout << "\nClient: Get unsupported interface" << std::endl;
    IZ* pIZ = NULL;
    hr = pIUnknown->QueryInterface(IID_IZ, (void**)&pIZ);
    if (SUCCEEDED(hr)) {
        std::cout << "Client: interface IZ get successfully" << std::endl;
    } else {
        std::cout << "Client: Can not get interface IZ" << std::endl;
    }

    std::cout << "\nClient: Get pointer to IY from IX" << std::endl;
    IY* pIYfromIx = NULL;
    hr = pIX->QueryInterface(IID_IY, (void**)&pIYfromIx);
    if (SUCCEEDED(hr)) {
        std::cout << "Client: IY received successfully" << std::endl;
        pIYfromIx->Fy();
    } else {
        std::cout << "Client: Can not get IY from IX" << std::endl;
    }

    std::cout << "\nClient: Get pointer to IUnknown from IY" << std::endl;
    IUnknown* pIUnknownFromIY = NULL;
    hr = pIY->QueryInterface(IID_IUnknown1, (void**)&pIUnknownFromIY);
    if (SUCCEEDED(hr)) {
        std::cout << "Eq" << std::endl;
        if (pIUnknownFromIY == pIUnknown) {
            std::cout << "YES" << std::endl;
        } else {
            std::cout << "NO" << std::endl;
        }
    }

    delete pIUnknown;

    return 0;
}
