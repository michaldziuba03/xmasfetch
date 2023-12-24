#pragma once
#include <iostream>
#include <WbemIdl.h>
#include <comdef.h>
#include <codecvt>

#pragma comment(lib, "wbemuuid.lib")

void UninitWmi()
{
    CoUninitialize();
}

BOOL CALLBACK InitHandleFunction (PINIT_ONCE InitOnce, PVOID Parameter, PVOID *lpContext)
{
    HRESULT hres;

    hres = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    if (FAILED(hres))
    {
        std::cout << "Failed to initialize COM library. "
                  << "Error code = 0x"
                  << std::hex << hres << std::endl;
        return FALSE;
    }

    hres =  CoInitializeSecurity(
            nullptr,
            -1,
            nullptr,
            nullptr,
            RPC_C_AUTHN_LEVEL_DEFAULT,
            RPC_C_IMP_LEVEL_IMPERSONATE,
            nullptr,
            EOAC_NONE,
            nullptr
    );


    if (FAILED(hres))
    {
        std::cout << "Failed to initialize security. "
                  << "Error code = 0x"
                  << std::hex << hres << std::endl;
        CoUninitialize();
        return FALSE;
    }

    IWbemLocator *pLoc = nullptr;

    hres = CoCreateInstance(
            CLSID_WbemLocator,
            nullptr,
            CLSCTX_INPROC_SERVER,
            IID_IWbemLocator, (LPVOID *) &pLoc);

    if (FAILED(hres))
    {
        std::cout << "Failed to create IWbemLocator object. "
                  << "Error code = 0x"
                  << std::hex << hres << std::endl;
        CoUninitialize();
        return FALSE;
    }

    IWbemServices *pSvc = nullptr;

    hres = pLoc->ConnectServer(
            _bstr_t("ROOT\\CIMV2"),
            nullptr,
            nullptr,
            nullptr,
            0,
            nullptr,
            nullptr,
            &pSvc
    );

    if (FAILED(hres))
    {
        std::cout << "Could not connect. Error code = 0x"
                  << std::hex << hres << std::endl;
        pLoc->Release();
        CoUninitialize();
        return FALSE;
    }

    hres = CoSetProxyBlanket(
            pSvc,
            RPC_C_AUTHN_WINNT,
            RPC_C_AUTHZ_NONE,
            nullptr,
            RPC_C_AUTHN_LEVEL_CALL,
            RPC_C_IMP_LEVEL_IMPERSONATE,
            nullptr,
            EOAC_NONE
    );

    if (FAILED(hres))
    {
        std::cout << "Could not set proxy blanket. Error code = 0x"
                  << std::hex << hres << std::endl;
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return FALSE;
    }

    *lpContext = pSvc;
    pLoc->Release();
    atexit(UninitWmi); // make sure that connection is closed when application closes

    return TRUE;
}

INIT_ONCE g_InitOnce = INIT_ONCE_STATIC_INIT;

// https://stackoverflow.com/questions/2573834/c-convert-string-or-char-to-wstring-or-wchar-t/18597384#18597384
std::string wstring_to_string(const std::wstring& wstring)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.to_bytes(wstring);
}

class QueryResult
{
    IEnumWbemClassObject* pEnumerator;
    IWbemClassObject* clsObj = nullptr;
    int count = 0;

public:
    explicit QueryResult(IEnumWbemClassObject* pEnum)
    {
        pEnumerator = pEnum;
    }

    ~QueryResult()
    {
        pEnumerator->Release();
        if (clsObj) clsObj->Release();
    }

    int Count()
    {
        return count;
    }

    void Next()
    {
        pEnumerator->Next(WBEM_INFINITE, 1, &clsObj, (ULONG*)&count);
    }

    [[nodiscard]] std::string GetStr(const std::wstring& field) const
    {
        VARIANT vRet;
        VariantInit(&vRet);
        std::wstring result;

        if(SUCCEEDED(clsObj->Get(field.c_str(), 0, &vRet, nullptr, nullptr)) && vRet.vt == VT_BSTR)
        {
            result = vRet.bstrVal;
            VariantClear(&vRet);
        }

        return wstring_to_string(result);
    }
};

QueryResult SendWmiQuery(const std::string& query)
{
    PVOID lpContext;
    BOOL  bStatus;
    bStatus = InitOnceExecuteOnce(&g_InitOnce, InitHandleFunction, nullptr, &lpContext);

    if (!bStatus) {
        std::cout << "WMI Query failure" << std::endl;
        exit(1);
    }

    HRESULT hres;
    auto *pSvc = static_cast<IWbemServices *>(lpContext);
    IEnumWbemClassObject* pEnumerator = nullptr;

    hres = pSvc->ExecQuery(
            bstr_t("WQL"),
            bstr_t(query.c_str()),
            WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
            nullptr,
            &pEnumerator);

    if (FAILED(hres))
    {
        std::cout << "Query for processes failed. "
                  << "Error code = 0x"
                  << std::hex << hres << std::endl;
        pSvc->Release();
        CoUninitialize();
    }

    pSvc->Release();

    return QueryResult(pEnumerator);
}
