//---------------------------------------------------------------------------
// Almost no programming at all by Hens Zimmerman
// Borland C++Builder 4 PRO
// 07/07/1999 - freeware
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <jpeg.hpp>
//---------------------------------------------------------------------------
int WINAPI DllEntryPoint(HINSTANCE, DWORD, PVOID){
    return 1;
}
//---------------------------------------------------------------------------
extern "C" __declspec(dllexport) BOOL PASCAL TransferJPEG(
        PCSTR jpegFile,
        PCSTR bmpFile){
    // attempts to xfer jpegFile to destination as a BMP
    TJPEGImage *bmp1 = new TJPEGImage();
    Graphics::TBitmap *bmp2 = new Graphics::TBitmap();
    BOOL bRet = TRUE;
    try{
        bmp1->LoadFromFile(jpegFile);
        bmp2->Assign(bmp1);
        bmp2->SaveToFile(bmpFile);
    }
    catch(...){
        bRet = FALSE;
    }
    delete bmp2;
    delete bmp1;
    return bRet;
}
//---------------------------------------------------------------------------
