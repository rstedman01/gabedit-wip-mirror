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
#ifndef __GABEDIT_ANIMATIONMD_H__
#define __GABEDIT_ANIMATIONMD_H__

typedef struct _AtomMD
{
	gchar symbol[5];
	gdouble C[3];
	gdouble V[3];

	gchar mmType[10];
	gchar pdbType[10];
	gchar resName[50];
	gint resNumber;
	gdouble partialCharge;
	gboolean variable;
	gdouble nuclearCharge;
}AtomMD;
typedef struct _GeometryMD
{
	gint numberOfAtoms;
	AtomMD* listOfAtoms;
	gdouble energy;
	gdouble time;
	gchar* comments;
	long int filePos;
}GeometryMD;

typedef struct _GeometriesMD
{
	gchar* fileName;
	GabEditTypeFile typeOfFile;
	gint numberOfGeometries;
	GeometryMD* geometries;
	gdouble velocity;
}GeometriesMD;
void initGeometryMD();
void geometriesMDDlg();

extern GeometriesMD geometriesMD;

#endif /* __GABEDIT_ANIMATIONMD_H__ */

