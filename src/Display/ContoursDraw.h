/**********************************************************************************************************
Copyright (c) 2002-2021 Abdul-Rahman Allouche. All rights reserved

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
documentation files (the Gabedit), to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all copies or substantial portions
  of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
************************************************************************************************************/

#ifndef __GABEDIT_CONTOURSDRAW_H__
#define __GABEDIT_CONTOURSDRAW_H__

void set_dotted_negative_contours(gboolean dotted);
gboolean get_dotted_negative_contours();
gdouble* GetGapVector(Grid* plansgrid,gint i0,gint i1,gint numplan,gdouble gap);
GLuint ContoursGenLists(GLuint contourslist,Grid* plansgrid,gint Ncontours,gdouble* values,gint i0,gint i1,gint numplan,gdouble gap);
void ContoursShowLists(GLuint list);
void showColorMapContours();
void hideColorMapContours();

#endif /* __GABEDIT_CONTOURSDRAW_H__ */

