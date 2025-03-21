/* MPQCLib.c */
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

#include "../../Config.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <glib/gi18n.h>
#include "../Common/GabeditType.h"
#include "../Utils/Utils.h"
#include "../Utils/Constants.h"
#include "../MPQC/MPQCLib.h"
/********************************************************************************/
GList* getMPQCBasisList(gchar* Symb, gchar* message)
{
	GList *glist = NULL;
	gchar *filename = g_strdup_printf("%s%smpqcBasis",gabedit_directory(), G_DIR_SEPARATOR_S);
	gchar* basisName= NULL;
	gchar symb[6];
	gint nbas = 0;
	gint n = 0;
	gint j;
	gchar* t = NULL;
	gchar* dump = NULL;
	gint k;

	FILE* fin = FOpen(filename,"r");
	if(!fin)
	{
		create_mpqc_basis_file();
		fin = FOpen(filename,"r");
	}
	if(!fin)
	{
		sprintf(message,_("Sorry the mpqcBasis is corrupted.\nPlease reinstall gabedit\n"));
		return NULL;
	}
  

	t = g_malloc(BSIZE*sizeof(gchar));
	dump = g_malloc(BSIZE*sizeof(gchar));
	basisName= g_malloc(BSIZE*sizeof(gchar));

    	{ char* e = fgets(t,BSIZE,fin);} /* number of atoms */
	while(!feof(fin))
	{
		if(!fgets(t,BSIZE,fin)) break;
		if(strstr(t,"Atom") && strstr(t,Symb) && sscanf(t,"%s %s",dump,symb)==2 && strcmp(Symb,symb) ==0 )
		{
			if(!fgets(t,BSIZE,fin)) break;
			sscanf(t,"%d",&nbas);
			for(j=0;j<nbas;j++)
			{
				if(!fgets(t,BSIZE,fin)) break;
				n = sscanf(t,"%s %s",symb, basisName);
				if(n<2)
				{
					nbas = 0;
		       			g_list_free(glist);
					glist = NULL;
					sprintf(message,_("Sorry the mpqcBasis is corrupted.\nPlease reinstall gabedit\n"));
					break;
				}
				for(k=0;k<(gint)strlen(basisName);k++) if (t[k]=='#') t[k] = ' ';
		       		glist = g_list_append(glist,g_strdup(basisName));
			}
			break;
		}
	}

	fclose(fin);
	g_free(t);
	g_free(dump);
	g_free(basisName);
	return glist;
}
/********************************************************************************/
GList* getMPQCBasisListOfAtoms(GList* atomsList, gchar* message)
{
	GList *basisList = NULL;
	gchar *filename = g_strdup_printf("%s%smpqcBasis",gabedit_directory(), G_DIR_SEPARATOR_S);
	gchar* basisName= NULL;
	gchar symb[6];
	gint nbas = 0;
	gint n = 0;
	gint i;
	gint j;
	gint k;
	gchar* t = NULL;
	gchar* dump = NULL;
	gboolean Ok;
	gboolean first = TRUE;
	gchar** list1 = NULL;
	gchar** list2 = NULL;
	gint n1 = 0;
	gint n2 = 0;

	FILE* fin = FOpen(filename,"r");

	sprintf(message,"No problem");

	if(!fin)
	{
		create_mpqc_basis_file();
		fin = FOpen(filename,"r");
	}
	if(!fin)
	{
		sprintf(message,_("Sorry the mpqcBasis is corrupted.\nPlease reinstall gabedit\n"));
		return NULL;
	}

	t = g_malloc(BSIZE*sizeof(gchar));
	dump = g_malloc(BSIZE*sizeof(gchar));
	basisName= g_malloc(BSIZE*sizeof(gchar));

    	{ char* e = fgets(t,BSIZE,fin);} /* number of atoms */
	while(!feof(fin))
	{
		if(!fgets(t,BSIZE,fin)) break;
		Ok = FALSE;
		if(strstr(t,"Atom") && sscanf(t,"%s %s",dump,symb)==2)
		{
			GList* l = atomsList;
			while(l)
			{
				if(strcmp(l->data,symb)==0)
				{
					Ok = TRUE;
					break;
				}
				l = l->next;
			}

		}
		if(Ok)
		{
			if(!fgets(t,BSIZE,fin)) break;
			sscanf(t,"%d",&nbas);
			if(nbas>0)
			{
				if(first)
				{
					list1 = g_malloc(nbas*sizeof(gchar*));
					n1 = nbas;
				}
				else
				{
					list2 = g_malloc(nbas*sizeof(gchar*));
					n2 = nbas;
				}
			}
			for(j=0;j<nbas;j++)
			{
				if(!fgets(t,BSIZE,fin)) break;
				n = sscanf(t,"%s %s",symb, basisName);
				for(k=0;k<(gint)strlen(basisName);k++) if (basisName[k]=='#') basisName[k] = ' ';
				if(n<2)
				{
					nbas = -1;
					basisList = NULL;
					sprintf(message,_("Sorry the mpqcBasis is corrupted.\nPlease reinstall gabedit\n"));
					break;
				}
				if(first)
				{
		       			list1[j] =g_strdup(basisName);
				}
				else
				{
		       			list2[j] =g_strdup(basisName);
				}
			}
			if(nbas == -1) break;
			if(!first)
			{
				for(i=0;i<n1;i++)
				{
					if(!list1[i]) continue;
					Ok = FALSE;
					for(j=0;j<n2;j++)
					{
						if(strcmp(list1[i],list2[j])==0)
						{
							Ok = TRUE;
							break;
						}
					}
					if(!Ok)
					{
						if(list1[i]) g_free(list1[i]);
						list1[i] = NULL;
					}
				}
				if(list2)
				{
					for(j=0;j<n2;j++) if(list2[j])g_free(list2[j]);
					g_free(list2);
					n2 = 0;
				}

			}
			if(nbas>0) first = FALSE;
		}
		else
		{
			if(!fgets(t,BSIZE,fin)) break;
			sscanf(t,"%d",&nbas);
			for(j=0;j<nbas;j++) if(!fgets(t,BSIZE,fin)) break;
		}
	}
	for(i=0;i<n1;i++)
	{
		if(list1[i]) basisList = g_list_append(basisList,list1[i]);
	}
	if(list1) g_free(list1); /* but not for(...) g_free(list1[i]);*/

	fclose(fin);
	g_free(t);
	g_free(dump);
	g_free(basisName);
	return basisList;
}
/********************************************************************************/
gboolean create_mpqc_basis_file()
{
        gchar *fileName =  g_strdup_printf("%s/mpqcBasis",gabedit_directory());  
	FILE* file = fopen(fileName,"w");

	g_free(fileName);

	if(file==NULL)
	{
		return FALSE;
	}
	fprintf(file,"NAtoms = 104\n");
	fprintf(file,"Atom  H\n");
	fprintf(file,"40\n");
	fprintf(file,"H STO-2G \n");
	fprintf(file,"H STO-3G \n");
	fprintf(file,"H STO-3G* \n");
	fprintf(file,"H STO-6G \n");
	fprintf(file,"H MINI#(Huzinaga) \n");
	fprintf(file,"H MINI#(Scaled) \n");
	fprintf(file,"H MIDI#(Huzinaga) \n");
	fprintf(file,"H DZ#(Dunning) \n");
	fprintf(file,"H DZP#(Dunning) \n");
	fprintf(file,"H DZP#+#Diffuse#(Dunning) \n");
	fprintf(file,"H 3-21G \n");
	fprintf(file,"H 3-21G* \n");
	fprintf(file,"H 3-21++G \n");
	fprintf(file,"H 3-21++G* \n");
	fprintf(file,"H 4-31G \n");
	fprintf(file,"H 4-31G* \n");
	fprintf(file,"H 4-31G** \n");
	fprintf(file,"H 6-31G \n");
	fprintf(file,"H 6-31G* \n");
	fprintf(file,"H 6-31G** \n");
	fprintf(file,"H 6-31+G* \n");
	fprintf(file,"H 6-31++G \n");
	fprintf(file,"H 6-31++G* \n");
	fprintf(file,"H 6-31++G** \n");
	fprintf(file,"H 6-311G \n");
	fprintf(file,"H 6-311G* \n");
	fprintf(file,"H 6-311G** \n");
	fprintf(file,"H 6-311G(2df,2pd) \n");
	fprintf(file,"H 6-311++G** \n");
	fprintf(file,"H 6-311++G(2d,2p) \n");
	fprintf(file,"H 6-311++G(3df,3pd) \n");
	fprintf(file,"H cc-pVDZ \n");
	fprintf(file,"H cc-pVTZ \n");
	fprintf(file,"H cc-pVQZ \n");
	fprintf(file,"H cc-pV5Z \n");
	fprintf(file,"H aug-cc-pVDZ \n");
	fprintf(file,"H aug-cc-pVTZ \n");
	fprintf(file,"H aug-cc-pVQZ \n");
	fprintf(file,"H aug-cc-pV5Z \n");
	fprintf(file,"H NASA#Ames#ANO \n");
	fprintf(file,"Atom  He\n");
	fprintf(file,"36\n");
	fprintf(file,"He STO-2G \n");
	fprintf(file,"He STO-3G \n");
	fprintf(file,"He STO-3G* \n");
	fprintf(file,"He STO-6G \n");
	fprintf(file,"He MINI#(Huzinaga) \n");
	fprintf(file,"He MINI#(Scaled) \n");
	fprintf(file,"He MIDI#(Huzinaga) \n");
	fprintf(file,"He 3-21G \n");
	fprintf(file,"He 3-21G* \n");
	fprintf(file,"He 3-21++G \n");
	fprintf(file,"He 3-21++G* \n");
	fprintf(file,"He 4-31G \n");
	fprintf(file,"He 4-31G* \n");
	fprintf(file,"He 4-31G** \n");
	fprintf(file,"He 6-31G \n");
	fprintf(file,"He 6-31G* \n");
	fprintf(file,"He 6-31G** \n");
	fprintf(file,"He 6-31+G* \n");
	fprintf(file,"He 6-31++G \n");
	fprintf(file,"He 6-31++G* \n");
	fprintf(file,"He 6-31++G** \n");
	fprintf(file,"He 6-311G \n");
	fprintf(file,"He 6-311G* \n");
	fprintf(file,"He 6-311G** \n");
	fprintf(file,"He 6-311G(2df,2pd) \n");
	fprintf(file,"He 6-311++G** \n");
	fprintf(file,"He 6-311++G(2d,2p) \n");
	fprintf(file,"He 6-311++G(3df,3pd) \n");
	fprintf(file,"He cc-pVDZ \n");
	fprintf(file,"He cc-pVTZ \n");
	fprintf(file,"He cc-pVQZ \n");
	fprintf(file,"He cc-pV5Z \n");
	fprintf(file,"He aug-cc-pVDZ \n");
	fprintf(file,"He aug-cc-pVTZ \n");
	fprintf(file,"He aug-cc-pVQZ \n");
	fprintf(file,"He aug-cc-pV5Z \n");
	fprintf(file,"Atom  Li\n");
	fprintf(file,"31\n");
	fprintf(file,"Li STO-2G \n");
	fprintf(file,"Li STO-3G \n");
	fprintf(file,"Li STO-3G* \n");
	fprintf(file,"Li STO-6G \n");
	fprintf(file,"Li MINI#(Huzinaga) \n");
	fprintf(file,"Li MINI#(Scaled) \n");
	fprintf(file,"Li MIDI#(Huzinaga) \n");
	fprintf(file,"Li DZ#(Dunning) \n");
	fprintf(file,"Li DZP#(Dunning) \n");
	fprintf(file,"Li 3-21G \n");
	fprintf(file,"Li 3-21G* \n");
	fprintf(file,"Li 3-21++G \n");
	fprintf(file,"Li 3-21++G* \n");
	fprintf(file,"Li 4-31G \n");
	fprintf(file,"Li 4-31G* \n");
	fprintf(file,"Li 4-31G** \n");
	fprintf(file,"Li 6-31G \n");
	fprintf(file,"Li 6-31G* \n");
	fprintf(file,"Li 6-31G** \n");
	fprintf(file,"Li 6-31+G* \n");
	fprintf(file,"Li 6-31++G \n");
	fprintf(file,"Li 6-31++G* \n");
	fprintf(file,"Li 6-31++G** \n");
	fprintf(file,"Li 6-311G \n");
	fprintf(file,"Li 6-311G* \n");
	fprintf(file,"Li 6-311G** \n");
	fprintf(file,"Li 6-311G(2df,2pd) \n");
	fprintf(file,"Li 6-311++G** \n");
	fprintf(file,"Li 6-311++G(2d,2p) \n");
	fprintf(file,"Li 6-311++G(3df,3pd) \n");
	fprintf(file,"Li cc-pV5Z \n");
	fprintf(file,"Atom  Be\n");
	fprintf(file,"29\n");
	fprintf(file,"Be STO-2G \n");
	fprintf(file,"Be STO-3G \n");
	fprintf(file,"Be STO-3G* \n");
	fprintf(file,"Be STO-6G \n");
	fprintf(file,"Be MINI#(Huzinaga) \n");
	fprintf(file,"Be MINI#(Scaled) \n");
	fprintf(file,"Be MIDI#(Huzinaga) \n");
	fprintf(file,"Be 3-21G \n");
	fprintf(file,"Be 3-21G* \n");
	fprintf(file,"Be 3-21++G \n");
	fprintf(file,"Be 3-21++G* \n");
	fprintf(file,"Be 4-31G \n");
	fprintf(file,"Be 4-31G* \n");
	fprintf(file,"Be 4-31G** \n");
	fprintf(file,"Be 6-31G \n");
	fprintf(file,"Be 6-31G* \n");
	fprintf(file,"Be 6-31G** \n");
	fprintf(file,"Be 6-31+G* \n");
	fprintf(file,"Be 6-31++G \n");
	fprintf(file,"Be 6-31++G* \n");
	fprintf(file,"Be 6-31++G** \n");
	fprintf(file,"Be 6-311G \n");
	fprintf(file,"Be 6-311G* \n");
	fprintf(file,"Be 6-311G** \n");
	fprintf(file,"Be 6-311G(2df,2pd) \n");
	fprintf(file,"Be 6-311++G** \n");
	fprintf(file,"Be 6-311++G(2d,2p) \n");
	fprintf(file,"Be 6-311++G(3df,3pd) \n");
	fprintf(file,"Be cc-pV5Z \n");
	fprintf(file,"Atom  B\n");
	fprintf(file,"47\n");
	fprintf(file,"B STO-2G \n");
	fprintf(file,"B STO-3G \n");
	fprintf(file,"B STO-3G* \n");
	fprintf(file,"B MINI#(Huzinaga) \n");
	fprintf(file,"B MINI#(Scaled) \n");
	fprintf(file,"B MIDI#(Huzinaga) \n");
	fprintf(file,"B DZ#(Dunning) \n");
	fprintf(file,"B DZP#(Dunning) \n");
	fprintf(file,"B DZP#+#Diffuse#(Dunning) \n");
	fprintf(file,"B 3-21G \n");
	fprintf(file,"B 3-21G* \n");
	fprintf(file,"B 3-21++G \n");
	fprintf(file,"B 3-21++G* \n");
	fprintf(file,"B 4-31G \n");
	fprintf(file,"B 4-31G* \n");
	fprintf(file,"B 4-31G** \n");
	fprintf(file,"B 6-31G \n");
	fprintf(file,"B 6-31G* \n");
	fprintf(file,"B 6-31G** \n");
	fprintf(file,"B 6-31+G* \n");
	fprintf(file,"B 6-31++G \n");
	fprintf(file,"B 6-31++G* \n");
	fprintf(file,"B 6-31++G** \n");
	fprintf(file,"B 6-311G \n");
	fprintf(file,"B 6-311G* \n");
	fprintf(file,"B 6-311G** \n");
	fprintf(file,"B 6-311G(2df,2pd) \n");
	fprintf(file,"B 6-311++G** \n");
	fprintf(file,"B 6-311++G(2d,2p) \n");
	fprintf(file,"B 6-311++G(3df,3pd) \n");
	fprintf(file,"B cc-pVDZ \n");
	fprintf(file,"B cc-pVTZ \n");
	fprintf(file,"B cc-pVQZ \n");
	fprintf(file,"B cc-pV5Z \n");
	fprintf(file,"B aug-cc-pVDZ \n");
	fprintf(file,"B aug-cc-pVTZ \n");
	fprintf(file,"B aug-cc-pVQZ \n");
	fprintf(file,"B aug-cc-pV5Z \n");
	fprintf(file,"B cc-pCVDZ \n");
	fprintf(file,"B cc-pCVTZ \n");
	fprintf(file,"B cc-pCVQZ \n");
	fprintf(file,"B cc-pCV5Z \n");
	fprintf(file,"B aug-cc-pCVDZ \n");
	fprintf(file,"B aug-cc-pCVTZ \n");
	fprintf(file,"B aug-cc-pCVQZ \n");
	fprintf(file,"B aug-cc-pCV5Z \n");
	fprintf(file,"B NASA#Ames#ANO \n");
	fprintf(file,"Atom  C\n");
	fprintf(file,"48\n");
	fprintf(file,"C STO-2G \n");
	fprintf(file,"C STO-3G \n");
	fprintf(file,"C STO-3G* \n");
	fprintf(file,"C STO-6G \n");
	fprintf(file,"C MINI#(Huzinaga) \n");
	fprintf(file,"C MINI#(Scaled) \n");
	fprintf(file,"C MIDI#(Huzinaga) \n");
	fprintf(file,"C DZ#(Dunning) \n");
	fprintf(file,"C DZP#(Dunning) \n");
	fprintf(file,"C DZP#+#Diffuse#(Dunning) \n");
	fprintf(file,"C 3-21G \n");
	fprintf(file,"C 3-21G* \n");
	fprintf(file,"C 3-21++G \n");
	fprintf(file,"C 3-21++G* \n");
	fprintf(file,"C 4-31G \n");
	fprintf(file,"C 4-31G* \n");
	fprintf(file,"C 4-31G** \n");
	fprintf(file,"C 6-31G \n");
	fprintf(file,"C 6-31G* \n");
	fprintf(file,"C 6-31G** \n");
	fprintf(file,"C 6-31+G* \n");
	fprintf(file,"C 6-31++G \n");
	fprintf(file,"C 6-31++G* \n");
	fprintf(file,"C 6-31++G** \n");
	fprintf(file,"C 6-311G \n");
	fprintf(file,"C 6-311G* \n");
	fprintf(file,"C 6-311G** \n");
	fprintf(file,"C 6-311G(2df,2pd) \n");
	fprintf(file,"C 6-311++G** \n");
	fprintf(file,"C 6-311++G(2d,2p) \n");
	fprintf(file,"C 6-311++G(3df,3pd) \n");
	fprintf(file,"C cc-pVDZ \n");
	fprintf(file,"C cc-pVTZ \n");
	fprintf(file,"C cc-pVQZ \n");
	fprintf(file,"C cc-pV5Z \n");
	fprintf(file,"C aug-cc-pVDZ \n");
	fprintf(file,"C aug-cc-pVTZ \n");
	fprintf(file,"C aug-cc-pVQZ \n");
	fprintf(file,"C aug-cc-pV5Z \n");
	fprintf(file,"C cc-pCVDZ \n");
	fprintf(file,"C cc-pCVTZ \n");
	fprintf(file,"C cc-pCVQZ \n");
	fprintf(file,"C cc-pCV5Z \n");
	fprintf(file,"C aug-cc-pCVDZ \n");
	fprintf(file,"C aug-cc-pCVTZ \n");
	fprintf(file,"C aug-cc-pCVQZ \n");
	fprintf(file,"C aug-cc-pCV5Z \n");
	fprintf(file,"C NASA#Ames#ANO \n");
	fprintf(file,"Atom  N\n");
	fprintf(file,"48\n");
	fprintf(file,"N STO-2G \n");
	fprintf(file,"N STO-3G \n");
	fprintf(file,"N STO-3G* \n");
	fprintf(file,"N STO-6G \n");
	fprintf(file,"N MINI#(Huzinaga) \n");
	fprintf(file,"N MINI#(Scaled) \n");
	fprintf(file,"N MIDI#(Huzinaga) \n");
	fprintf(file,"N DZ#(Dunning) \n");
	fprintf(file,"N DZP#(Dunning) \n");
	fprintf(file,"N DZP#+#Diffuse#(Dunning) \n");
	fprintf(file,"N 3-21G \n");
	fprintf(file,"N 3-21G* \n");
	fprintf(file,"N 3-21++G \n");
	fprintf(file,"N 3-21++G* \n");
	fprintf(file,"N 4-31G \n");
	fprintf(file,"N 4-31G* \n");
	fprintf(file,"N 4-31G** \n");
	fprintf(file,"N 6-31G \n");
	fprintf(file,"N 6-31G* \n");
	fprintf(file,"N 6-31G** \n");
	fprintf(file,"N 6-31+G* \n");
	fprintf(file,"N 6-31++G \n");
	fprintf(file,"N 6-31++G* \n");
	fprintf(file,"N 6-31++G** \n");
	fprintf(file,"N 6-311G \n");
	fprintf(file,"N 6-311G* \n");
	fprintf(file,"N 6-311G** \n");
	fprintf(file,"N 6-311G(2df,2pd) \n");
	fprintf(file,"N 6-311++G** \n");
	fprintf(file,"N 6-311++G(2d,2p) \n");
	fprintf(file,"N 6-311++G(3df,3pd) \n");
	fprintf(file,"N cc-pVDZ \n");
	fprintf(file,"N cc-pVTZ \n");
	fprintf(file,"N cc-pVQZ \n");
	fprintf(file,"N cc-pV5Z \n");
	fprintf(file,"N aug-cc-pVDZ \n");
	fprintf(file,"N aug-cc-pVTZ \n");
	fprintf(file,"N aug-cc-pVQZ \n");
	fprintf(file,"N aug-cc-pV5Z \n");
	fprintf(file,"N cc-pCVDZ \n");
	fprintf(file,"N cc-pCVTZ \n");
	fprintf(file,"N cc-pCVQZ \n");
	fprintf(file,"N cc-pCV5Z \n");
	fprintf(file,"N aug-cc-pCVDZ \n");
	fprintf(file,"N aug-cc-pCVTZ \n");
	fprintf(file,"N aug-cc-pCVQZ \n");
	fprintf(file,"N aug-cc-pCV5Z \n");
	fprintf(file,"N NASA#Ames#ANO \n");
	fprintf(file,"Atom  O\n");
	fprintf(file,"48\n");
	fprintf(file,"O STO-2G \n");
	fprintf(file,"O STO-3G \n");
	fprintf(file,"O STO-3G* \n");
	fprintf(file,"O STO-6G \n");
	fprintf(file,"O MINI#(Huzinaga) \n");
	fprintf(file,"O MINI#(Scaled) \n");
	fprintf(file,"O MIDI#(Huzinaga) \n");
	fprintf(file,"O DZ#(Dunning) \n");
	fprintf(file,"O DZP#(Dunning) \n");
	fprintf(file,"O DZP#+#Diffuse#(Dunning) \n");
	fprintf(file,"O 3-21G \n");
	fprintf(file,"O 3-21G* \n");
	fprintf(file,"O 3-21++G \n");
	fprintf(file,"O 3-21++G* \n");
	fprintf(file,"O 4-31G \n");
	fprintf(file,"O 4-31G* \n");
	fprintf(file,"O 4-31G** \n");
	fprintf(file,"O 6-31G \n");
	fprintf(file,"O 6-31G* \n");
	fprintf(file,"O 6-31G** \n");
	fprintf(file,"O 6-31+G* \n");
	fprintf(file,"O 6-31++G \n");
	fprintf(file,"O 6-31++G* \n");
	fprintf(file,"O 6-31++G** \n");
	fprintf(file,"O 6-311G \n");
	fprintf(file,"O 6-311G* \n");
	fprintf(file,"O 6-311G** \n");
	fprintf(file,"O 6-311G(2df,2pd) \n");
	fprintf(file,"O 6-311++G** \n");
	fprintf(file,"O 6-311++G(2d,2p) \n");
	fprintf(file,"O 6-311++G(3df,3pd) \n");
	fprintf(file,"O cc-pVDZ \n");
	fprintf(file,"O cc-pVTZ \n");
	fprintf(file,"O cc-pVQZ \n");
	fprintf(file,"O cc-pV5Z \n");
	fprintf(file,"O aug-cc-pVDZ \n");
	fprintf(file,"O aug-cc-pVTZ \n");
	fprintf(file,"O aug-cc-pVQZ \n");
	fprintf(file,"O aug-cc-pV5Z \n");
	fprintf(file,"O cc-pCVDZ \n");
	fprintf(file,"O cc-pCVTZ \n");
	fprintf(file,"O cc-pCVQZ \n");
	fprintf(file,"O cc-pCV5Z \n");
	fprintf(file,"O aug-cc-pCVDZ \n");
	fprintf(file,"O aug-cc-pCVTZ \n");
	fprintf(file,"O aug-cc-pCVQZ \n");
	fprintf(file,"O aug-cc-pCV5Z \n");
	fprintf(file,"O NASA#Ames#ANO \n");
	fprintf(file,"Atom  F\n");
	fprintf(file,"48\n");
	fprintf(file,"F STO-2G \n");
	fprintf(file,"F STO-3G \n");
	fprintf(file,"F STO-3G* \n");
	fprintf(file,"F STO-6G \n");
	fprintf(file,"F MINI#(Huzinaga) \n");
	fprintf(file,"F MINI#(Scaled) \n");
	fprintf(file,"F MIDI#(Huzinaga) \n");
	fprintf(file,"F DZ#(Dunning) \n");
	fprintf(file,"F DZP#(Dunning) \n");
	fprintf(file,"F DZP#+#Diffuse#(Dunning) \n");
	fprintf(file,"F 3-21G \n");
	fprintf(file,"F 3-21G* \n");
	fprintf(file,"F 3-21++G \n");
	fprintf(file,"F 3-21++G* \n");
	fprintf(file,"F 4-31G \n");
	fprintf(file,"F 4-31G* \n");
	fprintf(file,"F 4-31G** \n");
	fprintf(file,"F 6-31G \n");
	fprintf(file,"F 6-31G* \n");
	fprintf(file,"F 6-31G** \n");
	fprintf(file,"F 6-31+G* \n");
	fprintf(file,"F 6-31++G \n");
	fprintf(file,"F 6-31++G* \n");
	fprintf(file,"F 6-31++G** \n");
	fprintf(file,"F 6-311G \n");
	fprintf(file,"F 6-311G* \n");
	fprintf(file,"F 6-311G** \n");
	fprintf(file,"F 6-311G(2df,2pd) \n");
	fprintf(file,"F 6-311++G** \n");
	fprintf(file,"F 6-311++G(2d,2p) \n");
	fprintf(file,"F 6-311++G(3df,3pd) \n");
	fprintf(file,"F cc-pVDZ \n");
	fprintf(file,"F cc-pVTZ \n");
	fprintf(file,"F cc-pVQZ \n");
	fprintf(file,"F cc-pV5Z \n");
	fprintf(file,"F aug-cc-pVDZ \n");
	fprintf(file,"F aug-cc-pVTZ \n");
	fprintf(file,"F aug-cc-pVQZ \n");
	fprintf(file,"F aug-cc-pV5Z \n");
	fprintf(file,"F cc-pCVDZ \n");
	fprintf(file,"F cc-pCVTZ \n");
	fprintf(file,"F cc-pCVQZ \n");
	fprintf(file,"F cc-pCV5Z \n");
	fprintf(file,"F aug-cc-pCVDZ \n");
	fprintf(file,"F aug-cc-pCVTZ \n");
	fprintf(file,"F aug-cc-pCVQZ \n");
	fprintf(file,"F aug-cc-pCV5Z \n");
	fprintf(file,"F NASA#Ames#ANO \n");
	fprintf(file,"Atom  Ne\n");
	fprintf(file,"46\n");
	fprintf(file,"Ne STO-2G \n");
	fprintf(file,"Ne STO-3G \n");
	fprintf(file,"Ne STO-3G* \n");
	fprintf(file,"Ne STO-6G \n");
	fprintf(file,"Ne MINI#(Huzinaga) \n");
	fprintf(file,"Ne MINI#(Scaled) \n");
	fprintf(file,"Ne MIDI#(Huzinaga) \n");
	fprintf(file,"Ne DZ#(Dunning) \n");
	fprintf(file,"Ne DZP#(Dunning) \n");
	fprintf(file,"Ne DZP#+#Diffuse#(Dunning) \n");
	fprintf(file,"Ne 3-21G \n");
	fprintf(file,"Ne 3-21G* \n");
	fprintf(file,"Ne 3-21++G \n");
	fprintf(file,"Ne 3-21++G* \n");
	fprintf(file,"Ne 4-31G \n");
	fprintf(file,"Ne 4-31G* \n");
	fprintf(file,"Ne 4-31G** \n");
	fprintf(file,"Ne 6-31G \n");
	fprintf(file,"Ne 6-31G* \n");
	fprintf(file,"Ne 6-31G** \n");
	fprintf(file,"Ne 6-31+G* \n");
	fprintf(file,"Ne 6-31++G \n");
	fprintf(file,"Ne 6-31++G* \n");
	fprintf(file,"Ne 6-31++G** \n");
	fprintf(file,"Ne 6-311G \n");
	fprintf(file,"Ne 6-311G* \n");
	fprintf(file,"Ne 6-311G** \n");
	fprintf(file,"Ne 6-311G(2df,2pd) \n");
	fprintf(file,"Ne 6-311++G** \n");
	fprintf(file,"Ne 6-311++G(2d,2p) \n");
	fprintf(file,"Ne 6-311++G(3df,3pd) \n");
	fprintf(file,"Ne cc-pVDZ \n");
	fprintf(file,"Ne cc-pVTZ \n");
	fprintf(file,"Ne cc-pVQZ \n");
	fprintf(file,"Ne cc-pV5Z \n");
	fprintf(file,"Ne aug-cc-pVDZ \n");
	fprintf(file,"Ne aug-cc-pVTZ \n");
	fprintf(file,"Ne aug-cc-pVQZ \n");
	fprintf(file,"Ne aug-cc-pV5Z \n");
	fprintf(file,"Ne cc-pCVDZ \n");
	fprintf(file,"Ne cc-pCVTZ \n");
	fprintf(file,"Ne cc-pCVQZ \n");
	fprintf(file,"Ne cc-pCV5Z \n");
	fprintf(file,"Ne aug-cc-pCVTZ \n");
	fprintf(file,"Ne aug-cc-pCVQZ \n");
	fprintf(file,"Ne NASA#Ames#ANO \n");
	fprintf(file,"Atom  Na\n");
	fprintf(file,"22\n");
	fprintf(file,"Na STO-2G \n");
	fprintf(file,"Na STO-3G \n");
	fprintf(file,"Na STO-3G* \n");
	fprintf(file,"Na STO-6G \n");
	fprintf(file,"Na MINI#(Huzinaga) \n");
	fprintf(file,"Na MINI#(Scaled) \n");
	fprintf(file,"Na MIDI#(Huzinaga) \n");
	fprintf(file,"Na 3-21G \n");
	fprintf(file,"Na 3-21G* \n");
	fprintf(file,"Na 3-21++G \n");
	fprintf(file,"Na 3-21++G* \n");
	fprintf(file,"Na 6-31G \n");
	fprintf(file,"Na 6-31G* \n");
	fprintf(file,"Na 6-31G** \n");
	fprintf(file,"Na 6-31+G* \n");
	fprintf(file,"Na 6-31++G \n");
	fprintf(file,"Na 6-31++G* \n");
	fprintf(file,"Na 6-31++G** \n");
	fprintf(file,"Na 6-311G \n");
	fprintf(file,"Na 6-311G* \n");
	fprintf(file,"Na 6-311G** \n");
	fprintf(file,"Na 6-311++G(3df,3pd) \n");
	fprintf(file,"Atom  Mg\n");
	fprintf(file,"21\n");
	fprintf(file,"Mg STO-2G \n");
	fprintf(file,"Mg STO-3G \n");
	fprintf(file,"Mg STO-3G* \n");
	fprintf(file,"Mg STO-6G \n");
	fprintf(file,"Mg MINI#(Huzinaga) \n");
	fprintf(file,"Mg MINI#(Scaled) \n");
	fprintf(file,"Mg 3-21G \n");
	fprintf(file,"Mg 3-21G* \n");
	fprintf(file,"Mg 3-21++G \n");
	fprintf(file,"Mg 3-21++G* \n");
	fprintf(file,"Mg 6-31G \n");
	fprintf(file,"Mg 6-31G* \n");
	fprintf(file,"Mg 6-31G** \n");
	fprintf(file,"Mg 6-31+G* \n");
	fprintf(file,"Mg 6-31++G \n");
	fprintf(file,"Mg 6-31++G* \n");
	fprintf(file,"Mg 6-31++G** \n");
	fprintf(file,"Mg 6-311G \n");
	fprintf(file,"Mg 6-311G* \n");
	fprintf(file,"Mg 6-311G** \n");
	fprintf(file,"Mg 6-311++G(3df,3pd) \n");
	fprintf(file,"Atom  Al\n");
	fprintf(file,"32\n");
	fprintf(file,"Al STO-2G \n");
	fprintf(file,"Al STO-3G \n");
	fprintf(file,"Al STO-3G* \n");
	fprintf(file,"Al STO-6G \n");
	fprintf(file,"Al MINI#(Huzinaga) \n");
	fprintf(file,"Al MINI#(Scaled) \n");
	fprintf(file,"Al DZ#(Dunning) \n");
	fprintf(file,"Al DZP#(Dunning) \n");
	fprintf(file,"Al 3-21G \n");
	fprintf(file,"Al 3-21G* \n");
	fprintf(file,"Al 3-21++G \n");
	fprintf(file,"Al 3-21++G* \n");
	fprintf(file,"Al 6-31G \n");
	fprintf(file,"Al 6-31G* \n");
	fprintf(file,"Al 6-31G** \n");
	fprintf(file,"Al 6-31+G* \n");
	fprintf(file,"Al 6-31++G \n");
	fprintf(file,"Al 6-31++G* \n");
	fprintf(file,"Al 6-31++G** \n");
	fprintf(file,"Al 6-311G \n");
	fprintf(file,"Al 6-311G* \n");
	fprintf(file,"Al 6-311G** \n");
	fprintf(file,"Al 6-311++G(3df,3pd) \n");
	fprintf(file,"Al cc-pVDZ \n");
	fprintf(file,"Al cc-pVTZ \n");
	fprintf(file,"Al cc-pVQZ \n");
	fprintf(file,"Al cc-pV5Z \n");
	fprintf(file,"Al aug-cc-pVDZ \n");
	fprintf(file,"Al aug-cc-pVTZ \n");
	fprintf(file,"Al aug-cc-pVQZ \n");
	fprintf(file,"Al aug-cc-pV5Z \n");
	fprintf(file,"Al NASA#Ames#ANO \n");
	fprintf(file,"Atom  Si\n");
	fprintf(file,"31\n");
	fprintf(file,"Si STO-2G \n");
	fprintf(file,"Si STO-3G \n");
	fprintf(file,"Si STO-3G* \n");
	fprintf(file,"Si STO-6G \n");
	fprintf(file,"Si MINI#(Huzinaga) \n");
	fprintf(file,"Si MINI#(Scaled) \n");
	fprintf(file,"Si DZ#(Dunning) \n");
	fprintf(file,"Si DZP#(Dunning) \n");
	fprintf(file,"Si 3-21G \n");
	fprintf(file,"Si 3-21G* \n");
	fprintf(file,"Si 3-21++G \n");
	fprintf(file,"Si 3-21++G* \n");
	fprintf(file,"Si 6-31G \n");
	fprintf(file,"Si 6-31G* \n");
	fprintf(file,"Si 6-31G** \n");
	fprintf(file,"Si 6-31+G* \n");
	fprintf(file,"Si 6-31++G \n");
	fprintf(file,"Si 6-31++G* \n");
	fprintf(file,"Si 6-31++G** \n");
	fprintf(file,"Si 6-311G \n");
	fprintf(file,"Si 6-311G* \n");
	fprintf(file,"Si 6-311G** \n");
	fprintf(file,"Si 6-311++G(3df,3pd) \n");
	fprintf(file,"Si cc-pVDZ \n");
	fprintf(file,"Si cc-pVTZ \n");
	fprintf(file,"Si cc-pVQZ \n");
	fprintf(file,"Si cc-pV5Z \n");
	fprintf(file,"Si aug-cc-pVDZ \n");
	fprintf(file,"Si aug-cc-pVTZ \n");
	fprintf(file,"Si aug-cc-pVQZ \n");
	fprintf(file,"Si aug-cc-pV5Z \n");
	fprintf(file,"Atom  P\n");
	fprintf(file,"35\n");
	fprintf(file,"P STO-2G \n");
	fprintf(file,"P STO-3G \n");
	fprintf(file,"P STO-3G* \n");
	fprintf(file,"P STO-6G \n");
	fprintf(file,"P MINI#(Huzinaga) \n");
	fprintf(file,"P MINI#(Scaled) \n");
	fprintf(file,"P DZ#(Dunning) \n");
	fprintf(file,"P DZP#(Dunning) \n");
	fprintf(file,"P 3-21G \n");
	fprintf(file,"P 3-21G* \n");
	fprintf(file,"P 3-21++G \n");
	fprintf(file,"P 3-21++G* \n");
	fprintf(file,"P 4-31G \n");
	fprintf(file,"P 4-31G* \n");
	fprintf(file,"P 4-31G** \n");
	fprintf(file,"P 6-31G \n");
	fprintf(file,"P 6-31G* \n");
	fprintf(file,"P 6-31G** \n");
	fprintf(file,"P 6-31+G* \n");
	fprintf(file,"P 6-31++G \n");
	fprintf(file,"P 6-31++G* \n");
	fprintf(file,"P 6-31++G** \n");
	fprintf(file,"P 6-311G \n");
	fprintf(file,"P 6-311G* \n");
	fprintf(file,"P 6-311G** \n");
	fprintf(file,"P 6-311++G(3df,3pd) \n");
	fprintf(file,"P cc-pVDZ \n");
	fprintf(file,"P cc-pVTZ \n");
	fprintf(file,"P cc-pVQZ \n");
	fprintf(file,"P cc-pV5Z \n");
	fprintf(file,"P aug-cc-pVDZ \n");
	fprintf(file,"P aug-cc-pVTZ \n");
	fprintf(file,"P aug-cc-pVQZ \n");
	fprintf(file,"P aug-cc-pV5Z \n");
	fprintf(file,"P NASA#Ames#ANO \n");
	fprintf(file,"Atom  S\n");
	fprintf(file,"34\n");
	fprintf(file,"S STO-2G \n");
	fprintf(file,"S STO-3G \n");
	fprintf(file,"S STO-3G* \n");
	fprintf(file,"S STO-6G \n");
	fprintf(file,"S MINI#(Huzinaga) \n");
	fprintf(file,"S MINI#(Scaled) \n");
	fprintf(file,"S DZ#(Dunning) \n");
	fprintf(file,"S DZP#(Dunning) \n");
	fprintf(file,"S 3-21G \n");
	fprintf(file,"S 3-21G* \n");
	fprintf(file,"S 3-21++G \n");
	fprintf(file,"S 3-21++G* \n");
	fprintf(file,"S 4-31G \n");
	fprintf(file,"S 4-31G* \n");
	fprintf(file,"S 4-31G** \n");
	fprintf(file,"S 6-31G \n");
	fprintf(file,"S 6-31G* \n");
	fprintf(file,"S 6-31G** \n");
	fprintf(file,"S 6-31+G* \n");
	fprintf(file,"S 6-31++G \n");
	fprintf(file,"S 6-31++G* \n");
	fprintf(file,"S 6-31++G** \n");
	fprintf(file,"S 6-311G \n");
	fprintf(file,"S 6-311G* \n");
	fprintf(file,"S 6-311G** \n");
	fprintf(file,"S 6-311++G(3df,3pd) \n");
	fprintf(file,"S cc-pVDZ \n");
	fprintf(file,"S cc-pVTZ \n");
	fprintf(file,"S cc-pVQZ \n");
	fprintf(file,"S cc-pV5Z \n");
	fprintf(file,"S aug-cc-pVDZ \n");
	fprintf(file,"S aug-cc-pVTZ \n");
	fprintf(file,"S aug-cc-pVQZ \n");
	fprintf(file,"S aug-cc-pV5Z \n");
	fprintf(file,"Atom  Cl\n");
	fprintf(file,"34\n");
	fprintf(file,"Cl STO-2G \n");
	fprintf(file,"Cl STO-3G \n");
	fprintf(file,"Cl STO-3G* \n");
	fprintf(file,"Cl STO-6G \n");
	fprintf(file,"Cl MINI#(Huzinaga) \n");
	fprintf(file,"Cl MINI#(Scaled) \n");
	fprintf(file,"Cl DZ#(Dunning) \n");
	fprintf(file,"Cl DZP#(Dunning) \n");
	fprintf(file,"Cl 3-21G \n");
	fprintf(file,"Cl 3-21G* \n");
	fprintf(file,"Cl 3-21++G \n");
	fprintf(file,"Cl 3-21++G* \n");
	fprintf(file,"Cl 4-31G \n");
	fprintf(file,"Cl 4-31G* \n");
	fprintf(file,"Cl 4-31G** \n");
	fprintf(file,"Cl 6-31G \n");
	fprintf(file,"Cl 6-31G* \n");
	fprintf(file,"Cl 6-31G** \n");
	fprintf(file,"Cl 6-31+G* \n");
	fprintf(file,"Cl 6-31++G \n");
	fprintf(file,"Cl 6-31++G* \n");
	fprintf(file,"Cl 6-31++G** \n");
	fprintf(file,"Cl 6-311G \n");
	fprintf(file,"Cl 6-311G* \n");
	fprintf(file,"Cl 6-311G** \n");
	fprintf(file,"Cl 6-311++G(3df,3pd) \n");
	fprintf(file,"Cl cc-pVDZ \n");
	fprintf(file,"Cl cc-pVTZ \n");
	fprintf(file,"Cl cc-pVQZ \n");
	fprintf(file,"Cl cc-pV5Z \n");
	fprintf(file,"Cl aug-cc-pVDZ \n");
	fprintf(file,"Cl aug-cc-pVTZ \n");
	fprintf(file,"Cl aug-cc-pVQZ \n");
	fprintf(file,"Cl aug-cc-pV5Z \n");
	fprintf(file,"Atom  Ar\n");
	fprintf(file,"29\n");
	fprintf(file,"Ar STO-2G \n");
	fprintf(file,"Ar STO-3G \n");
	fprintf(file,"Ar STO-3G* \n");
	fprintf(file,"Ar STO-6G \n");
	fprintf(file,"Ar MINI#(Huzinaga) \n");
	fprintf(file,"Ar MINI#(Scaled) \n");
	fprintf(file,"Ar 3-21G \n");
	fprintf(file,"Ar 3-21G* \n");
	fprintf(file,"Ar 3-21++G \n");
	fprintf(file,"Ar 3-21++G* \n");
	fprintf(file,"Ar 6-31G \n");
	fprintf(file,"Ar 6-31G* \n");
	fprintf(file,"Ar 6-31G** \n");
	fprintf(file,"Ar 6-31+G* \n");
	fprintf(file,"Ar 6-31++G \n");
	fprintf(file,"Ar 6-31++G* \n");
	fprintf(file,"Ar 6-31++G** \n");
	fprintf(file,"Ar 6-311G \n");
	fprintf(file,"Ar 6-311G* \n");
	fprintf(file,"Ar 6-311G** \n");
	fprintf(file,"Ar 6-311++G(3df,3pd) \n");
	fprintf(file,"Ar cc-pVDZ \n");
	fprintf(file,"Ar cc-pVTZ \n");
	fprintf(file,"Ar cc-pVQZ \n");
	fprintf(file,"Ar cc-pV5Z \n");
	fprintf(file,"Ar aug-cc-pVDZ \n");
	fprintf(file,"Ar aug-cc-pVTZ \n");
	fprintf(file,"Ar aug-cc-pVQZ \n");
	fprintf(file,"Ar aug-cc-pV5Z \n");
	fprintf(file,"Atom  K\n");
	fprintf(file,"6\n");
	fprintf(file,"K STO-2G \n");
	fprintf(file,"K STO-3G \n");
	fprintf(file,"K STO-6G \n");
	fprintf(file,"K MINI#(Huzinaga) \n");
	fprintf(file,"K MINI#(Scaled) \n");
	fprintf(file,"K 3-21G \n");
	fprintf(file,"Atom  Ca\n");
	fprintf(file,"6\n");
	fprintf(file,"Ca STO-2G \n");
	fprintf(file,"Ca STO-3G \n");
	fprintf(file,"Ca STO-6G \n");
	fprintf(file,"Ca MINI#(Huzinaga) \n");
	fprintf(file,"Ca MINI#(Scaled) \n");
	fprintf(file,"Ca 3-21G \n");
	fprintf(file,"Atom  Sc\n");
	fprintf(file,"3\n");
	fprintf(file,"Sc STO-3G \n");
	fprintf(file,"Sc STO-6G \n");
	fprintf(file,"Sc 3-21G \n");
	fprintf(file,"Atom  Ti\n");
	fprintf(file,"4\n");
	fprintf(file,"Ti STO-3G \n");
	fprintf(file,"Ti STO-6G \n");
	fprintf(file,"Ti 3-21G \n");
	fprintf(file,"Ti NASA#Ames#ANO \n");
	fprintf(file,"Atom  V\n");
	fprintf(file,"3\n");
	fprintf(file,"V STO-3G \n");
	fprintf(file,"V STO-6G \n");
	fprintf(file,"V 3-21G \n");
	fprintf(file,"Atom  Cr\n");
	fprintf(file,"3\n");
	fprintf(file,"Cr STO-3G \n");
	fprintf(file,"Cr STO-6G \n");
	fprintf(file,"Cr 3-21G \n");
	fprintf(file,"Atom  Mn\n");
	fprintf(file,"3\n");
	fprintf(file,"Mn STO-3G \n");
	fprintf(file,"Mn STO-6G \n");
	fprintf(file,"Mn 3-21G \n");
	fprintf(file,"Atom  Fe\n");
	fprintf(file,"4\n");
	fprintf(file,"Fe STO-3G \n");
	fprintf(file,"Fe STO-6G \n");
	fprintf(file,"Fe 3-21G \n");
	fprintf(file,"Fe NASA#Ames#ANO \n");
	fprintf(file,"Atom  Co\n");
	fprintf(file,"3\n");
	fprintf(file,"Co STO-3G \n");
	fprintf(file,"Co STO-6G \n");
	fprintf(file,"Co 3-21G \n");
	fprintf(file,"Atom  Ni\n");
	fprintf(file,"4\n");
	fprintf(file,"Ni STO-3G \n");
	fprintf(file,"Ni STO-6G \n");
	fprintf(file,"Ni 3-21G \n");
	fprintf(file,"Ni NASA#Ames#ANO \n");
	fprintf(file,"Atom  Cu\n");
	fprintf(file,"3\n");
	fprintf(file,"Cu STO-3G \n");
	fprintf(file,"Cu STO-6G \n");
	fprintf(file,"Cu 3-21G \n");
	fprintf(file,"Atom  Zn\n");
	fprintf(file,"3\n");
	fprintf(file,"Zn STO-3G \n");
	fprintf(file,"Zn STO-6G \n");
	fprintf(file,"Zn 3-21G \n");
	fprintf(file,"Atom  Ga\n");
	fprintf(file,"8\n");
	fprintf(file,"Ga STO-3G \n");
	fprintf(file,"Ga STO-6G \n");
	fprintf(file,"Ga 3-21G \n");
	fprintf(file,"Ga 6-311G \n");
	fprintf(file,"Ga 6-311G* \n");
	fprintf(file,"Ga 6-311G** \n");
	fprintf(file,"Ga cc-pVDZ \n");
	fprintf(file,"Ga cc-pVTZ \n");
	fprintf(file,"Atom  Ge\n");
	fprintf(file,"8\n");
	fprintf(file,"Ge STO-3G \n");
	fprintf(file,"Ge STO-6G \n");
	fprintf(file,"Ge 3-21G \n");
	fprintf(file,"Ge 6-311G \n");
	fprintf(file,"Ge 6-311G* \n");
	fprintf(file,"Ge 6-311G** \n");
	fprintf(file,"Ge cc-pVDZ \n");
	fprintf(file,"Ge cc-pVTZ \n");
	fprintf(file,"Atom  As\n");
	fprintf(file,"8\n");
	fprintf(file,"As STO-3G \n");
	fprintf(file,"As STO-6G \n");
	fprintf(file,"As 3-21G \n");
	fprintf(file,"As 6-311G \n");
	fprintf(file,"As 6-311G* \n");
	fprintf(file,"As 6-311G** \n");
	fprintf(file,"As cc-pVDZ \n");
	fprintf(file,"As cc-pVTZ \n");
	fprintf(file,"Atom  Se\n");
	fprintf(file,"8\n");
	fprintf(file,"Se STO-3G \n");
	fprintf(file,"Se STO-6G \n");
	fprintf(file,"Se 3-21G \n");
	fprintf(file,"Se 6-311G \n");
	fprintf(file,"Se 6-311G* \n");
	fprintf(file,"Se 6-311G** \n");
	fprintf(file,"Se cc-pVDZ \n");
	fprintf(file,"Se cc-pVTZ \n");
	fprintf(file,"Atom  Br\n");
	fprintf(file,"7\n");
	fprintf(file,"Br STO-3G \n");
	fprintf(file,"Br STO-6G \n");
	fprintf(file,"Br 3-21G \n");
	fprintf(file,"Br 6-311G \n");
	fprintf(file,"Br 6-311G* \n");
	fprintf(file,"Br 6-311G** \n");
	fprintf(file,"Br cc-pVDZ \n");
	fprintf(file,"Atom  Kr\n");
	fprintf(file,"7\n");
	fprintf(file,"Kr STO-3G \n");
	fprintf(file,"Kr STO-6G \n");
	fprintf(file,"Kr 3-21G \n");
	fprintf(file,"Kr 6-311G \n");
	fprintf(file,"Kr 6-311G* \n");
	fprintf(file,"Kr 6-311G** \n");
	fprintf(file,"Kr cc-pVDZ \n");
	fprintf(file,"Atom  Rb\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Sr\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Y\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Zr\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Nb\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Mo\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Tc\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Ru\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Rh\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Pd\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Ag\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Cd\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  In\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Sn\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Sb\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Te\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  I\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Xe\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Cs\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Ba\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  La\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Hf\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Ta\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  W\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Re\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Os\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Ir\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Pt\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Au\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Hg\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Tl\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Pb\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Bi\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Po\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  At\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Rn\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Fr\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Ra\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Ac\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Ce\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Pr\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Nd\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Pm\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Sm\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Eu\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Gd\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Tb\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Dy\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Ho\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Er\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Tm\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Yb\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Lu\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  X\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Th\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Pa\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  U\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Np\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Pu\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Am\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Cm\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Bk\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Cf\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Es\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Fm\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Md\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  No\n");
	fprintf(file,"0\n");
	fprintf(file,"Atom  Lr\n");
	fprintf(file,"0\n");
	fclose(file);
	return TRUE;
}
