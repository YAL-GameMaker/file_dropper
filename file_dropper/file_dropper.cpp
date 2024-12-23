/// @author YellowAfterlife

#include <oleidl.h>
#include <shlobj.h>
#include <objbase.h>
#include <shellapi.h>
#include <string>

#include "stdafx.h"
#include "gml_async_glue.h"
#include "tiny_string.h"

static tiny_string utf8c;
static tiny_wstring utf8wc;
namespace GMDropTargetState {
    UINT refCount = 0;
    //
    bool defaultAllow = true;
    int defaultEffect = DROPEFFECT_COPY;
    //
    bool allow = true;
    int effect = DROPEFFECT_COPY;
};

///
enum class file_dropper_mk : int {
    lbutton = 1,
    rbutton = 2,  
    shift = 4,
    control = 8,
    mbutton = 16,
    alt = 32,
};
///
enum class file_dropper_effect : int{
    none = 0,
    copy = 1,
    move = 2,
    link = 4,
};

void file_dropper_preinit() {
    static_assert((int)file_dropper_mk::lbutton == MK_LBUTTON, "MK_LBUTTON");
    static_assert((int)file_dropper_mk::rbutton == MK_RBUTTON, "MK_RBUTTON");
    static_assert((int)file_dropper_mk::mbutton == MK_MBUTTON, "MK_MBUTTON");
    //
    static_assert((int)file_dropper_mk::alt == MK_ALT, "MK_ALT");
    static_assert((int)file_dropper_mk::shift == MK_SHIFT, "MK_SHIFT");
    static_assert((int)file_dropper_mk::control == MK_CONTROL, "MK_CONTROL");
    //
    utf8c.init();
    utf8wc.init();
    GMDropTargetState::refCount = 0;
    GMDropTargetState::defaultAllow = true;
    GMDropTargetState::defaultEffect = DROPEFFECT_COPY;
    GMDropTargetState::allow = true;
    GMDropTargetState::effect = DROPEFFECT_COPY;
}

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
        return ++GMDropTargetState::refCount;
    }
    virtual ULONG __stdcall Release(void) override {
        return --GMDropTargetState::refCount;
    }
    virtual HRESULT __stdcall DragEnter(IDataObject* pDataObj, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect) override {
        // there should be at least one valid file in the batch
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
        auto found = false;
        for (auto k = 0u; k < fileCount; k++) {
            auto pathLen = DragQueryFileW(drop, k, nullptr, 0);
            if (pathLen == 0) continue;
            if (!found) {
                gml_async_event e("file_drag_enter_start");
                e.setPosKeyState(pt, grfKeyState);
                e.dispatchSystem();
                found = true;
            }
            //
            auto wpath = utf8wc.prepare(pathLen + 1);
            DragQueryFileW(drop, k, wpath, pathLen + 1);
            auto path = utf8c.conv(wpath);
            //
            gml_async_event e("file_drag_enter_file");
            e.setPosKeyState(pt, grfKeyState);
            e.set("filename", path);
            e.dispatchSystem();
        }
        if (found) {
            GMDropTargetState::allow = GMDropTargetState::defaultAllow;
            GMDropTargetState::effect = GMDropTargetState::defaultEffect;
            *pdwEffect = GMDropTargetState::effect;
            //
            gml_async_event e("file_drag_enter");
            e.setPosKeyState(pt, grfKeyState);
            e.dispatchSystem();
            return S_OK;
        }
        return S_FALSE;
    }
    virtual HRESULT __stdcall DragOver(DWORD grfKeyState, POINTL pt, DWORD* pdwEffect) override {
        // dispatches often, but what can we do about it
        gml_async_event e("file_drag_over");
        e.setPosKeyState(pt, grfKeyState);
        e.dispatchSystem();
        if (GMDropTargetState::allow) {
            *pdwEffect = GMDropTargetState::effect;
            return S_OK;
        } else return S_FALSE;
    }
    virtual HRESULT __stdcall DragLeave(void) override {
        gml_async_event e("file_drag_leave");
        e.dispatchSystem();
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
        *pdwEffect = GMDropTargetState::effect;

        auto drop = (HDROP)medium.hGlobal;
        auto fileCountBase = DragQueryFileW(drop, UINT32_MAX, NULL, 0);

        // collect the file names:
        auto filenames = malloc_arr<char*>(fileCountBase);
        auto fileCount = 0u;
        for (auto k = 0u; k < fileCountBase; k++) {
            auto wnameLen = DragQueryFileW(drop, k, nullptr, 0);
            if (wnameLen == 0) continue;
            auto wname = utf8wc.prepare(wnameLen + 1);
            DragQueryFileW(drop, k, wname, wnameLen + 1);
            //
            auto nameLen = WideCharToMultiByte(CP_UTF8, 0, wname, -1, NULL, 0, NULL, NULL);
            auto name = malloc_arr<char>(nameLen);
            WideCharToMultiByte(CP_UTF8, 0, wname, -1, name, nameLen, NULL, NULL);
            filenames[fileCount++] = name;
        }

        // start:
        {
            gml_async_event e("file_drop_start");
            e.setPosKeyState(pt, grfKeyState);
            e.set("file_count", fileCount);
            e.dispatchSystem();
        }

        // per-file events:
        for (auto k = 0u; k < fileCount; k++) {
            gml_async_event e("file_drop");
            e.setPosKeyState(pt, grfKeyState);
            e.set("filename", filenames[k]);
            e.dispatchSystem(); // async system
            free(filenames[k]);
        }
        free(filenames);

        // end:
        {
            gml_async_event e("file_drop_end");
            e.setPosKeyState(pt, grfKeyState);
            e.set("file_count", fileCount);
            e.dispatchSystem();
        }
        //
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
    hr = RegisterDragDrop(hwnd, dropTarget);
    if (FAILED(hr)) trace("RegisterDragDrop failed, hresult=0x%x", hr);
    return SUCCEEDED(hr);
}

//
dllg bool file_dropper_get_allow() {
    return GMDropTargetState::allow;
}
dllg void file_dropper_set_allow(bool allow) {
    GMDropTargetState::allow = allow;
}
//
dllg double file_dropper_get_effect(int effect) {
    return GMDropTargetState::effect;
}
dllg double file_dropper_set_effect(int effect) {
    GMDropTargetState::effect = effect;
    return 1;
}
//
dllg bool file_dropper_get_default_allow() {
    return GMDropTargetState::defaultAllow;
}
dllg void file_dropper_set_default_allow(bool allow) {
    GMDropTargetState::defaultAllow = allow;
}
//
dllg double file_dropper_get_default_effect(int effect) {
    return GMDropTargetState::defaultEffect;
}
dllg double file_dropper_set_default_effect(int effect) {
    GMDropTargetState::defaultEffect = effect;
    return 1;
}