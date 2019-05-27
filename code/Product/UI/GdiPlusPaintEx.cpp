#include "..\\..\\stdafx.h"
#include "GdiPlusPaintEx.h"

GdiPlusPaintEx::GdiPlusPaintEx(){
	m_rotateAngle = 0;
	m_supportTransparent = true;
}

GdiPlusPaintEx::~GdiPlusPaintEx(){
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GdiPlusPaintEx::beginPaint(HDC hDC, const FCRect& wRect, const FCRect& pRect){
	m_pRect = pRect;
	m_wRect = wRect;
	int width = m_wRect.right - m_wRect.left;
	int height = m_wRect.bottom - m_wRect.top;
	if(!m_bitmap || width > (int)m_bitmap->GetWidth() || height > (int)m_bitmap->GetHeight()){
		m_bitmap = new Bitmap(width, height);
		m_g = Graphics::FromImage(m_bitmap);
	}
	m_hDC = hDC;
	if(m_rotateAngle == 0){
		Color color(0, 0, 0);
		m_g->Clear(color);
	}
	m_g->SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
	m_opacity = 1;
	m_resourcePath = L"";
	m_g->ResetTransform();
	if(m_rotateAngle != 0){
		int px = width - width * m_rotateAngle / 720;
		int py = height - height * m_rotateAngle / 720;
		m_g->TranslateTransform((REAL)px, (REAL)py);
		m_g->RotateTransform((REAL)m_rotateAngle);
		double scale = (double)(m_rotateAngle) / 1440;
		m_g->ScaleTransform((REAL)scale, (REAL)scale);
	}
}

void GdiPlusPaintEx::drawTextEx(LPCWSTR strText, Long dwPenColor, FCFont *font, const FCRect& rect){
	if(dwPenColor == FCColor_None) return;
	if(!m_emptyStringFormat){
		m_emptyStringFormat = (StringFormat*)StringFormat::GenericTypographic();
		m_emptyStringFormat->SetFormatFlags(::StringFormatFlagsMeasureTrailingSpaces);
    }
	if (m_scaleFactorX != 1 || m_scaleFactorY != 1){
		int strX = (int)(m_scaleFactorX * (rect.left + m_offsetX));
		int strY = (int)(m_scaleFactorY * (rect.top + m_offsetY));
		PointF gdiPlusPoint((REAL)strX, (REAL)strY);
		float fontSize = (float)(font->m_fontSize * (m_scaleFactorX + m_scaleFactorY) / 2);
		FCFont scaleFont(font->m_fontFamily, fontSize, font->m_bold, font->m_underline, font->m_italic);
		Gdiplus::Font *gdiFont = getFont(&scaleFont);
		GraphicsState state = m_g->Save();
		m_g->TranslateTransform((REAL)gdiPlusPoint.X, (REAL)(gdiPlusPoint.Y + (int)(m_scaleFactorX * 1.8 * (rect.bottom - rect.top))));
		m_g->RotateTransform((REAL)3);
		m_g->ScaleTransform((REAL)1, (REAL)-1);
		Long color = getColor(dwPenColor);
		int a = 0, r = 0, g = 0, b = 0;
		FCColor::toArgb(0, color, &a, &r, &g, &b);
		PointF bkPoint((REAL)0, (REAL)0);
		m_g->DrawString(strText, -1, gdiFont, bkPoint, m_emptyStringFormat, getBrush(FCColor::argb((int)(a * 0.1), r, g, b)));
		m_g->Restore(state);
		m_g->DrawString(strText, -1, gdiFont, gdiPlusPoint, m_emptyStringFormat, getBrush(dwPenColor));
		delete gdiFont;
		gdiFont = 0;
	}
	else{
		PointF gdiPlusPoint((REAL)(rect.left + m_offsetX), (REAL)(rect.top + m_offsetY));
		Gdiplus::Font *gdiFont = getFont(font);
		GraphicsState state = m_g->Save();
		m_g->TranslateTransform((REAL)gdiPlusPoint.X, (REAL)(gdiPlusPoint.Y + 1.8 * (rect.bottom - rect.top)));
		m_g->RotateTransform((REAL)3);
		m_g->ScaleTransform((REAL)1, (REAL)-1);
		Long color = getColor(dwPenColor);
		int a = 0, r = 0, g = 0, b = 0;
		FCColor::toArgb(0, color, &a, &r, &g, &b);
		PointF bkPoint((REAL)0, (REAL)0);
		m_g->DrawString(strText, -1, gdiFont, bkPoint, m_emptyStringFormat, getBrush(FCColor::argb((int)(a * 0.1), r, g, b)));
		m_g->Restore(state);
		m_g->DrawString(strText, -1, gdiFont, gdiPlusPoint, m_emptyStringFormat, getBrush(dwPenColor));
		delete gdiFont;
		gdiFont = 0;
	}
}

Long GdiPlusPaintEx::getColor(Long dwPenColor){
	if (dwPenColor <=  FCColor_None){
		return FCDraw::getBlackColor(dwPenColor);
    }
    else{
		return GdiPlusPaint::getColor(dwPenColor);
    }
}

void GdiPlusPaintEx::setRotateAngle(int rotateAngle){
	m_rotateAngle = rotateAngle;
}

void GdiPlusPaintEx::setSupportTransparent(bool supportTransparent){
	m_supportTransparent = supportTransparent;
}

bool GdiPlusPaintEx::supportTransparent(){
	return m_supportTransparent;
}