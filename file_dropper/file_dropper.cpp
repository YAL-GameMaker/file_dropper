/// @author YellowAfterlife

#include <oleidl.h>
#include "stdafx.h"
#include "gml_async_glue.h"
#include "tiny_string.h"

static tiny_string utf8c;
static UINT GMDropTarget_refCount = 0;

struct GMDropTarget : IDropTarget {
    // Inherited via IDropTarget
    virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppvObject) override {
        if (IsEqualIID(riid, IID_IDropTarget) || IsEqualIID(riid, IID_IUnknown)) {
            *ppvObject = this;
            this->AddRef();
            return NOERROR;
        } else {
            *ppvObject = nullptr;
            return E_NOINTERFACE;
        }
    }
    virtual ULONG __stdcall AddRef(void) override {
        return ++GMDropTarget_refCount;
    }
    virtual ULONG __stdcall Release(void) override {
        return --GMDropTarget_refCount;
    }
    virtual HRESULT __stdcall DragEnter(IDataObject* pDataObj, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect) override {
        return S_OK;
    }
    virtual HRESULT __stdcall DragOver(DWORD grfKeyState, POINTL pt, DWORD* pdwEffect) override {
        return S_OK;
    }
    virtual HRESULT __stdcall DragLeave(void) override {
        return S_OK;
    }
    virtual HRESULT __stdcall Drop(IDataObject* pDataObj, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect) override {
        //trace("drop");
        FORMATETC formatEtc;
        formatEtc.cfFormat = CF_HDROP;
        formatEtc.dwAspect = DVASPECT_CONTENT;
        formatEtc.lindex = -1;
        formatEtc.ptd = NULL;
        formatEtc.tymed = TYMED_HGLOBAL;

        STGMEDIUM medium;
        auto hr = pDataObj->GetData(&formatEtc, &medium);
        if (FAILED(hr)) return hr;
        if (medium.tymed != TYMED_HGLOBAL) return S_OK;

        auto drop = (HDROP)medium.hGlobal;
        auto fileCount = DragQueryFileW(drop, UINT32_MAX, NULL, 0);
        //trace("fileCount=%d", fileCount);
        for (auto k = 0u; k < fileCount; k++) {
            auto nameLen = DragQueryFileW(drop, k, nullptr, 0);
            if (nameLen == 0) continue;

            auto wname = malloc_arr<wchar_t>(nameLen + 1);
            DragQueryFile(drop, k, wname, nameLen + 1);
            auto name = utf8c.conv(wname);

            gml_async_event e("file_drop");
            e.set("filename", name);
            e.dispatch(75); // async system
            delete wname;
        }
        return S_OK;
    }
};
static GMDropTarget* dropTarget = nullptr;

dllg bool file_dropper_init(GAME_HWND hwnd) {
    if (dropTarget != nullptr) return true;

    auto hr = OleInitialize(0);
    if (hr != S_OK && hr != S_FALSE) {
        trace("OleInitialize failed, hresult=0x%x", hr);
        return false;
    }

    dropTarget = new GMDropTarget();
    utf8c.init();
    hr = RegisterDragDrop(hwnd, dropTarget);
    if (FAILED(hr)) trace("RegisterDragDrop failed, hresult=0x%x", hr);
    return SUCCEEDED(hr);
}
