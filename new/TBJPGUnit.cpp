//---------------------------------------------------------------------------

// JPEG DLL for ToolBook.
// Update January 16, 2003.
// Borland C++Builder 5 PRO patch #1.
// By Hens Zimmerman <henszimmerman@hotmail.com>
// and Richard Rickenbacher <rickenbacher@opentrain.ch>
// FREEWARE! Use at your own risk.

//---------------------------------------------------------------------------

#include <vcl.h>
#include <windows.h>

#pragma hdrstop

#include <clipbrd.hpp>
#include <jpeg.hpp>
#include <memory>

//---------------------------------------------------------------------------

int WINAPI DllEntryPoint(HINSTANCE, unsigned long, void*)
{
  return 1;
}

//---------------------------------------------------------------------------

// Kept here for compatibility with old code.

extern "C" __declspec(dllexport) DWORD __stdcall TransferJPEG
(
  PCSTR JpegFileName,
  PCSTR BmpFileName
)
{

  std::auto_ptr <TJPEGImage> Jpeg(new TJPEGImage);
  std::auto_ptr <Graphics::TBitmap> Bmp(new Graphics::TBitmap);

  try
  {
    Jpeg->LoadFromFile(JpegFileName);
    Bmp->Assign(Jpeg.get());
    Bmp->SaveToFile(BmpFileName);
  }
  catch(...)
  {
    return 0;
  }

  return 1;
}


//---------------------------------------------------------------------------

// Same function as above with a more sensible name.

extern "C" __declspec(dllexport) DWORD __stdcall CopyJpegToFile
(
  PCSTR JpegFileName,
  PCSTR BmpFileName
)
{

  std::auto_ptr <TJPEGImage> Jpeg(new TJPEGImage);
  std::auto_ptr <Graphics::TBitmap> Bmp(new Graphics::TBitmap);

  try
  {
    Jpeg->LoadFromFile(JpegFileName);
    Bmp->Assign(Jpeg.get());
    Bmp->SaveToFile(BmpFileName);
  }
  catch(...)
  {
    return 0;
  }

  return 1;
}

//---------------------------------------------------------------------------

extern "C" __declspec(dllexport) DWORD __stdcall CopyJpegToClipboard
(
  PCSTR JpegFileName
)
{

  std::auto_ptr <TJPEGImage> Jpeg(new TJPEGImage);
  std::auto_ptr <Graphics::TBitmap> Bmp(new Graphics::TBitmap);

  try
  {
    Jpeg->LoadFromFile(JpegFileName);
    Bmp->Assign(Jpeg.get());

    unsigned short MyFormat;
    unsigned int DataHandle;
    HPALETTE Palette;

    Bmp->SaveToClipboardFormat(MyFormat, DataHandle, Palette);

    Clipboard()->SetAsHandle(MyFormat, DataHandle);

    // Do not delete a handle after passing it to SetAsHandle.
    // The handle belongs to the clipboard, which will free it.
  }
  catch(...)
  {
    return 0;
  }

  return 1;
}

//---------------------------------------------------------------------------

