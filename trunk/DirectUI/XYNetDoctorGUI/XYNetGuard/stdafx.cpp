// stdafx.cpp : source file that includes just the standard includes
// beikesafe.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file

void CreateBitmapMask( CBitmap &pBmpSource, CBitmap &pBmpMask, COLORREF clrpTransColor, int iTransPixelX, int iTransPixelY)
{
	BITMAP bm;

	// Get the dimensions of the source bitmap
	pBmpSource.GetBitmap(&bm);

	// Create the mask bitmap
	//pBmpMask.DeleteObject();
	pBmpMask.CreateBitmap( bm.bmWidth, bm.bmHeight, 1, 1, NULL);

	// We will need two DCs to work with. One to hold the Image
	// (the source), and one to hold the mask (destination).
	// When blitting onto a monochrome bitmap from a color, pixels
	// in the source color bitmap that are equal to the background
	// color are blitted as white. All the remaining pixels are
	// blitted as black.

	CDC hdcSrc, hdcDst;

	hdcSrc.CreateCompatibleDC(NULL);
	hdcDst.CreateCompatibleDC(NULL);

	// Load the bitmaps into memory DC
	HBITMAP hbmSrcT = hdcSrc.SelectBitmap(pBmpSource);
	HBITMAP hbmDstT = hdcDst.SelectBitmap(pBmpMask);

	// Dynamically get the transparent color
	COLORREF clrTrans;
	if (clrpTransColor == NULL)
	{
		// User did not specify trans color so get it from bmp
		clrTrans = hdcSrc.GetPixel(iTransPixelX, iTransPixelY);
	}
	else
	{
		clrTrans = clrpTransColor;
	}

	// Change the background to trans color
	COLORREF clrSaveBk  = hdcSrc.SetBkColor(clrTrans);

	// This call sets up the mask bitmap.
	hdcDst.BitBlt(0, 0, bm.bmWidth, bm.bmHeight, hdcSrc, 0, 0, SRCCOPY);

	// Now, we need to paint onto the original image, making
	// sure that the "transparent" area is set to black. What
	// we do is AND the monochrome image onto the color Image
	// first. When blitting from mono to color, the monochrome
	// pixel is first transformed as follows:
	// if  1 (black) it is mapped to the color set by SetTextColor().
	// if  0 (white) is is mapped to the color set by SetBkColor().
	// Only then is the raster operation performed.

	COLORREF clrSaveDstText = hdcSrc.SetTextColor(RGB(255,255,255));
	hdcSrc.SetBkColor(RGB(0,0,0));

	hdcSrc.BitBlt(0,0,bm.bmWidth, bm.bmHeight, hdcDst,0,0,SRCAND);

	// Clean up by deselecting any objects, and delete the
	// DC's.
	hdcDst.SetTextColor(clrSaveDstText);

	hdcSrc.SetBkColor(clrSaveBk);
	hdcSrc.SelectBitmap(hbmSrcT);
	hdcDst.SelectBitmap(hbmDstT);

	hdcSrc.DeleteDC();
	hdcDst.DeleteDC();
}
