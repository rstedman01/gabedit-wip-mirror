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

#ifndef __GABEDIT_GABEDITTYPE_H__
#define __GABEDIT_GABEDITTYPE_H__

#define MAXISOTOP 10
typedef void (*GabeditSignalFunc)(GtkWidget*);
typedef enum
{
  GABEDIT_NETWORK_FTP_RSH = 0,
  GABEDIT_NETWORK_SSH
} GabEditNetWork;

typedef struct _SAtomsProp
{
	gchar *name;
	gchar *symbol;
	guint atomicNumber;
	gdouble covalentRadii;
	gdouble bondOrderRadii;
	gdouble vanDerWaalsRadii;
	gdouble radii;
	guint maximumBondValence;
	gdouble masse;
	gdouble electronegativity;
	GdkColor color;
	gint nIsotopes;
	gint iMass[MAXISOTOP];
	gdouble rMass[MAXISOTOP];
	gdouble abundances[MAXISOTOP];
}SAtomsProp;
typedef enum
{
  GABEDIT_TYPEWIN_GEOM,
  GABEDIT_TYPEWIN_ORB,
  GABEDIT_TYPEWIN_OTHER,
} GabEditTypeWin;
typedef enum
{
  GABEDIT_TYPETEXTURE_1,
  GABEDIT_TYPETEXTURE_2,
  GABEDIT_TYPETEXTURE_3,
  GABEDIT_TYPETEXTURE_NONE
} GabEditTypeTexture;
typedef enum
{
  GABEDIT_TYPENODE_DEMON=0,
  GABEDIT_TYPENODE_FIREFLY,
  GABEDIT_TYPENODE_GAMESS,
  GABEDIT_TYPENODE_GAUSSIAN,
  GABEDIT_TYPENODE_MOLCAS,
  GABEDIT_TYPENODE_MOLPRO,
  GABEDIT_TYPENODE_MOPAC,
  GABEDIT_TYPENODE_MPQC,
  GABEDIT_TYPENODE_NWCHEM,
  GABEDIT_TYPENODE_PSICODE,
  GABEDIT_TYPENODE_ORCA,
  GABEDIT_TYPENODE_QCHEM,
  GABEDIT_TYPENODE_GABEDIT,
  GABEDIT_TYPENODE_XYZ,
  GABEDIT_TYPENODE_MOL2,
  GABEDIT_TYPENODE_TINKER,
  GABEDIT_TYPENODE_PDB,
  GABEDIT_TYPENODE_GZMAT,
  GABEDIT_TYPENODE_MZMAT,
  GABEDIT_TYPENODE_HIN,
  GABEDIT_TYPENODE_OTHER
} GabEditTypeNode;
typedef enum
{
  GABEDIT_TYPEFILE_GAUSSIAN,
  GABEDIT_TYPEFILE_GAUSSIAN_ANHARMONIC,
  GABEDIT_TYPEFILE_GAUSSIAN_SCANOPT,
  GABEDIT_TYPEFILE_GAUSSIAN_IRCOPT,
  GABEDIT_TYPEFILE_MOLCAS,
  GABEDIT_TYPEFILE_MOLPRO,
  GABEDIT_TYPEFILE_DALTON,
  GABEDIT_TYPEFILE_DEMON,
  GABEDIT_TYPEFILE_GAMESS,
  GABEDIT_TYPEFILE_GAMESS_ANHARMONIC,
  GABEDIT_TYPEFILE_TURBOMOLE,
  GABEDIT_TYPEFILE_MOLPRO_LOG,
  GABEDIT_TYPEFILE_MOLDEN,
  GABEDIT_TYPEFILE_GABEDIT,
  GABEDIT_TYPEFILE_MOBCAL,
  GABEDIT_TYPEFILE_XYZ,
  GABEDIT_TYPEFILE_GAMESSIRC,
  GABEDIT_TYPEFILE_MOL2,
  GABEDIT_TYPEFILE_MOL,
  GABEDIT_TYPEFILE_TINKER,
  GABEDIT_TYPEFILE_PDB,
  GABEDIT_TYPEFILE_GZMAT,
  GABEDIT_TYPEFILE_MZMAT,
  GABEDIT_TYPEFILE_HIN,
  GABEDIT_TYPEFILE_AIMALL,
  GABEDIT_TYPEFILE_CCHEMI,
  GABEDIT_TYPEFILE_DEMONINPUT,
  GABEDIT_TYPEFILE_GAMESSINPUT,
  GABEDIT_TYPEFILE_GAUSSIANINPUT,
  GABEDIT_TYPEFILE_GAUSSIAN_FCHK,
  GABEDIT_TYPEFILE_MOLCASINPUT,
  GABEDIT_TYPEFILE_MOLPROINPUT,
  GABEDIT_TYPEFILE_MPQCINPUT,
  GABEDIT_TYPEFILE_ORCAINPUT,
  GABEDIT_TYPEFILE_FIREFLYINPUT,
  GABEDIT_TYPEFILE_QCHEMINPUT,
  GABEDIT_TYPEFILE_NWCHEMINPUT,
  GABEDIT_TYPEFILE_PSICODEINPUT,
  GABEDIT_TYPEFILE_MOPACINPUT,
  GABEDIT_TYPEFILE_MPQC,
  GABEDIT_TYPEFILE_JPEG,
  GABEDIT_TYPEFILE_PPM,
  GABEDIT_TYPEFILE_BMP,
  GABEDIT_TYPEFILE_PNG,
  GABEDIT_TYPEFILE_TIF,
  GABEDIT_TYPEFILE_PS,
  GABEDIT_TYPEFILE_ADF,
  GABEDIT_TYPEFILE_ORCA,
  GABEDIT_TYPEFILE_VASPOUTCAR,
  GABEDIT_TYPEFILE_VASPPOSCAR,
  GABEDIT_TYPEFILE_CIF,
  GABEDIT_TYPEFILE_VASPXML,
  GABEDIT_TYPEFILE_FIREFLY,
  GABEDIT_TYPEFILE_QCHEM,
  GABEDIT_TYPEFILE_NWCHEM,
  GABEDIT_TYPEFILE_PSICODE,
  GABEDIT_TYPEFILE_MOPAC,
  GABEDIT_TYPEFILE_MOPAC_AUX,
  GABEDIT_TYPEFILE_MOPAC_SCAN,
  GABEDIT_TYPEFILE_MOPAC_IRC,
  GABEDIT_TYPEFILE_CUBEGAUSS,
  GABEDIT_TYPEFILE_CUBEMOLPRO,
  GABEDIT_TYPEFILE_CUBEADF,
  GABEDIT_TYPEFILE_MOLCASGRID,
  GABEDIT_TYPEFILE_CUBEMOLCAS,
  GABEDIT_TYPEFILE_CUBEQCHEM,
  GABEDIT_TYPEFILE_CUBEGABEDIT,
  GABEDIT_TYPEFILE_CUBEDX,
  GABEDIT_TYPEFILE_TRJ,
  GABEDIT_TYPEFILE_TXT,
  GABEDIT_TYPEFILE_NBO_BASIS,
  GABEDIT_TYPEFILE_NBO,
  GABEDIT_TYPEFILE_XML,
  GABEDIT_TYPEFILE_IGVPT2,
  GABEDIT_TYPEFILE_WFX,
  GABEDIT_TYPEFILE_UNKNOWN,
} GabEditTypeFile;

typedef enum
{
  GABEDIT_TYPEFILEGEOM_NEW,

  GABEDIT_TYPEFILEGEOM_GABEDIT,
  GABEDIT_TYPEFILEGEOM_MOLDEN,

  GABEDIT_TYPEFILEGEOM_XYZ,
  GABEDIT_TYPEFILEGEOM_MOL,
  GABEDIT_TYPEFILEGEOM_MOL2,
  GABEDIT_TYPEFILEGEOM_TINKER,
  GABEDIT_TYPEFILEGEOM_PDB,
  GABEDIT_TYPEFILEGEOM_HIN,
  GABEDIT_TYPEFILEGEOM_AIMALL,

  GABEDIT_TYPEFILEGEOM_DALTONIN,
  GABEDIT_TYPEFILEGEOM_DALTONFIRST,
  GABEDIT_TYPEFILEGEOM_DALTONLAST,

  GABEDIT_TYPEFILEGEOM_DEMONIN,
  GABEDIT_TYPEFILEGEOM_DEMONFIRST,
  GABEDIT_TYPEFILEGEOM_DEMONLAST,

  GABEDIT_TYPEFILEGEOM_GAMESSIN,
  GABEDIT_TYPEFILEGEOM_GAMESSFIRST,
  GABEDIT_TYPEFILEGEOM_GAMESSLAST,

  GABEDIT_TYPEFILEGEOM_GAUSSIN,
  GABEDIT_TYPEFILEGEOM_GAUSSOUTFIRST,
  GABEDIT_TYPEFILEGEOM_GAUSSOUTLAST,
  GABEDIT_TYPEFILEGEOM_GAUSSIAN_FCHK,

  GABEDIT_TYPEFILEGEOM_MOLCASIN,
  GABEDIT_TYPEFILEGEOM_MOLCASOUTFIRST,
  GABEDIT_TYPEFILEGEOM_MOLCASOUTLAST,

  GABEDIT_TYPEFILEGEOM_MOLPROIN,
  GABEDIT_TYPEFILEGEOM_MOLPROOUTFIRST,
  GABEDIT_TYPEFILEGEOM_MOLPROOUTLAST,

  GABEDIT_TYPEFILEGEOM_MPQCIN,
  GABEDIT_TYPEFILEGEOM_MPQCOUTFIRST,
  GABEDIT_TYPEFILEGEOM_MPQCOUTLAST,

  GABEDIT_TYPEFILEGEOM_ORCAIN,
  GABEDIT_TYPEFILEGEOM_ORCAOUTFIRST,
  GABEDIT_TYPEFILEGEOM_ORCAOUTLAST,

  GABEDIT_TYPEFILEGEOM_VASPIN,
  GABEDIT_TYPEFILEGEOM_VASPPOSCAR,
  GABEDIT_TYPEFILEGEOM_VASPOUTFIRST,
  GABEDIT_TYPEFILEGEOM_VASPOUTLAST,
  GABEDIT_TYPEFILEGEOM_VASPXMLFIRST,
  GABEDIT_TYPEFILEGEOM_VASPXMLLAST,

  GABEDIT_TYPEFILEGEOM_CIF,

  GABEDIT_TYPEFILEGEOM_QCHEMIN,
  GABEDIT_TYPEFILEGEOM_QCHEMOUTFIRST,
  GABEDIT_TYPEFILEGEOM_QCHEMOUTLAST,

  GABEDIT_TYPEFILEGEOM_NWCHEMIN,
  GABEDIT_TYPEFILEGEOM_NWCHEMOUTFIRST,
  GABEDIT_TYPEFILEGEOM_NWCHEMOUTLAST,

  GABEDIT_TYPEFILEGEOM_PSICODEIN,
  GABEDIT_TYPEFILEGEOM_PSICODEOUTFIRST,
  GABEDIT_TYPEFILEGEOM_PSICODEOUTLAST,


  GABEDIT_TYPEFILEGEOM_MOPACIN,
  GABEDIT_TYPEFILEGEOM_MOPACOUTFIRST,
  GABEDIT_TYPEFILEGEOM_MOPACOUTLAST,
  GABEDIT_TYPEFILEGEOM_MOPACAUX,
  GABEDIT_TYPEFILEGEOM_MOPACOUTSCAN,

  GABEDIT_TYPEFILEGEOM_FIREFLYIN,
  GABEDIT_TYPEFILEGEOM_FIREFLYFIRST,
  GABEDIT_TYPEFILEGEOM_FIREFLYLAST,

  GABEDIT_TYPEFILEGEOM_GAMESSIRC,

  GABEDIT_TYPEFILEGEOM_TURBOMOLEFIRST,
  GABEDIT_TYPEFILEGEOM_TURBOMOLELAST,


  GABEDIT_TYPEFILEGEOM_GAUSSIAN_ZMATRIX,
  GABEDIT_TYPEFILEGEOM_MOPAC_ZMATRIX,

  GABEDIT_TYPEFILEGEOM_WFX,

  GABEDIT_TYPEFILEGEOM_UNKNOWN
} GabEditTypeFileGeom;

typedef enum
{
  GABEDIT_TYPEGRID_ORBITAL,
  GABEDIT_TYPEGRID_EDENSITY,
  GABEDIT_TYPEGRID_DDENSITY,
  GABEDIT_TYPEGRID_ADENSITY,
  GABEDIT_TYPEGRID_SDENSITY,
  GABEDIT_TYPEGRID_ELFBECKE,
  GABEDIT_TYPEGRID_ELFSAVIN,
  GABEDIT_TYPEGRID_FEDELECTROPHILIC,
  GABEDIT_TYPEGRID_FEDNUCLEOPHILIC,
  GABEDIT_TYPEGRID_FEDRADICAL,
  GABEDIT_TYPEGRID_NCI,
  GABEDIT_TYPEGRID_SAS,
  GABEDIT_TYPEGRID_SASMAP,
  GABEDIT_TYPEGRID_MEP_CHARGES,
  GABEDIT_TYPEGRID_MEP_MULTIPOL,
  GABEDIT_TYPEGRID_MEP_CG,
  GABEDIT_TYPEGRID_MEP_MG,
  GABEDIT_TYPEGRID_MEP_EXACT,
} GabEditTypeGrid;

typedef enum
{
  GABEDIT_TYPEGEOM_NO,
  GABEDIT_TYPEGEOM_BALLSTICK,
  GABEDIT_TYPEGEOM_STICK,
  GABEDIT_TYPEGEOM_SPACE,
  GABEDIT_TYPEGEOM_WIREFRAME
} GabEditTypeGeom;

typedef enum
{
  GABEDIT_SURFSHOW_NO,
  GABEDIT_SURFSHOW_POSNEG,
  GABEDIT_SURFSHOW_POSITIVE,
  GABEDIT_SURFSHOW_NEGATIVE
} GabEditTypeSurfShow;

typedef enum
{
  GABEDIT_BLEND_NO,
  GABEDIT_BLEND_YES
} GabEditTypeBlend;

typedef enum
{
  GABEDIT_POS_WIREFRAME_NO,
  GABEDIT_POS_WIREFRAME_YES,
  GABEDIT_NEG_WIREFRAME_NO,
  GABEDIT_NEG_WIREFRAME_YES
} GabEditTypeWireFrame;

typedef enum
{
  GABEDIT_PROGORB_UNK,
  GABEDIT_PROGORB_READGEOM,
  GABEDIT_PROGORB_SAVEGEOM,
  GABEDIT_PROGORB_COMPISOSURFACE,
  GABEDIT_PROGORB_COMPGRID,
  GABEDIT_PROGORB_COMPINTEG,
  GABEDIT_PROGORB_SCALEGRID,
  GABEDIT_PROGORB_SUBSGRID,
  GABEDIT_PROGORB_READGRID,
  GABEDIT_PROGORB_SAVEGRID,
  GABEDIT_PROGORB_MAPGRID,
  GABEDIT_PROGORB_SCANFILEGRID,
  GABEDIT_PROGORB_COMPMULTIPOL,
  GABEDIT_PROGORB_COMPLAPGRID,
  GABEDIT_PROGORB_COMPGRADGRID,
  GABEDIT_PROGORB_COMPNCIGRID,
  GABEDIT_PROGORB_COMPL2GRID,
  GABEDIT_PROGORB_COMPMEPGRID,
} GabEditTypeProgressOrb;

typedef struct _LXYZ LXYZ;
struct _LXYZ
{
	gdouble Coef;
	gint l[3];
};

typedef struct _Zlm Zlm;
struct _Zlm
{
	gint l;
	gint m;
	gint numberOfCoefficients;
	LXYZ* lxyz;
};

typedef struct _GTF
{
 gdouble Ex;
 gdouble Coef;
 gint l[3];
 gdouble C[3]; 
}GTF;

typedef struct _AO
{
 gint L;
 gint N;
 gdouble* Ex;
 gdouble* Coef;
 }AO;

typedef struct _TYPE
{
 char* Symb;
 gint N; /* Number of electrons*/
 gint Norb;
 AO *Ao;
 }TYPE;

typedef struct _CGTF
{
 gint numberOfFunctions;
 gint NumCenter;
 GTF* Gtf;
 gint L; /* used if spherical basis*/
 gint M; /* used if spherical basis*/
 }CGTF;
typedef struct _RGBColor
{
  guchar rgb[3];

}RGBColor;

typedef struct _TypeGeomOrb
{
	gchar* Symb;
	gdouble C[3];
	gdouble partialCharge;
	gdouble nuclearCharge;
	gboolean variable;
	SAtomsProp Prop;
	guint Sphere;
	gint N;
	gint NumType;
	gint NAOrb;
	gint* NumOrb;
	gint NOrb;
	gint NAlphaOrb;
	gint NBetaOrb;
	gdouble **CoefAlphaOrbitals;
	gdouble *OccAlphaOrbitals;
	gdouble *EnerAlphaOrbitals;
	gchar	**SymAlphaOrbitals;
	gdouble **CoefBetaOrbitals;
	gdouble *EnerBetaOrbitals;
	gdouble *OccBetaOrbitals;
	gchar	**SymBetaOrbitals;
}TypeGeomOrb;

typedef struct _TypeFontsStyle
{
 gchar *fontname;
 GdkColor BaseColor;
 GdkColor TextColor;
}TypeFontsStyle;
typedef gdouble	 (*Func3d)(gdouble ,gdouble,gdouble,gint);

typedef struct _STF
{
 gdouble Ex;
 gdouble Coef;
 gint l[3];
 gdouble C[3]; 
 gint pqn;
}STF;

typedef struct _CSTF
{
 gint N;
 gint NumCenter;
 STF* Stf;
 gint L; /* used if spherical basis*/
 gint M; /* used if spherical basis*/
 }CSTF;

typedef struct _OpenGLOptions
{
	gint rgba;
	gint doubleBuffer;
	gint alphaSize;
	gint depthSize;
	gint numberOfSubdivisionsCylindre; 
	gint numberOfSubdivisionsSphere; 
	gint activateText;
}OpenGLOptions;
typedef enum
{
  GABEDIT_BONDTYPE_SINGLE = 0,
  GABEDIT_BONDTYPE_DOUBLE,
  GABEDIT_BONDTYPE_TRIPLE,
  GABEDIT_BONDTYPE_HYDROGEN,
} GabEditBondType;
typedef struct _BondType BondType;
struct _BondType
{
	gint n1;
	gint n2;
	GabEditBondType bondType;
};
typedef struct _DipoleDef
{
 gboolean def;
 gdouble origin[3];
 gdouble value[3];
 gdouble radius;
 gdouble color[3];
}DipoleDef;


#endif /* __GABEDIT_GABEDITTYPE_H__ */

