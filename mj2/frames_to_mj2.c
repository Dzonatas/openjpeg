/*
* Copyright (c) 2003-2004, Fran�ois-Olivier Devaux
* Copyright (c) 2002-2004,  Communications and remote sensing Laboratory, Universite catholique de Louvain, Belgium
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
* 1. Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the distribution.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS `AS IS'
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*/

#include <openjpeg.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#ifndef DONT_HAVE_GETOPT
#include <getopt.h>
#else
#include "compat/getopt.h"
#endif
#include "mj2_convert.h"

void help_display()
{
  printf("HELP\n----\n\n");
  printf("- the -h option displays this help information on screen\n\n");


  printf("List of parameters for the coder JPEG 2000:\n");
  printf("\n");
  printf("REMARKS:\n");
  printf("---------\n");
  printf("\n");
  printf
    ("The markers written to the main_header are : SOC SIZ COD QCD COM.\n");
  printf
    ("COD and QCD never appear in the tile_header.\n");
  printf("\n");
  printf
    ("- This coder can encode a mega image, a test was made on a 24000x24000 pixels \n");
  printf
    ("color image.  You need enough disk space memory (twice the original) to encode \n");
  printf
    ("the image,i.e. for a 1.5 GB image you need a minimum of 3GB of disk memory)\n");
  printf("\n");
  printf("By default:\n");
  printf("------------\n");
  printf("\n");
  printf(" * Lossless\n");
  printf(" * 1 tile\n");
  printf(" * Size of precinct : 2^15 x 2^15 (means 1 precinct)\n");
  printf(" * Size of code-block : 64 x 64\n");
  printf(" * Number of resolutions: 6\n");
  printf(" * No SOP marker in the codestream\n");
  printf(" * No EPH marker in the codestream\n");
  printf(" * No sub-sampling in x or y direction\n");
  printf(" * No mode switch activated\n");
  printf(" * Progression order: LRCP\n");
  printf(" * No index file\n");
  printf(" * No ROI upshifted\n");
  printf(" * No offset of the origin of the image\n");
  printf(" * No offset of the origin of the tiles\n");
  printf(" * Reversible DWT 5-3\n");
  printf("\n");
  printf("Parameters:\n");
  printf("------------\n");
  printf("\n");
  printf
    ("Required Parameters (except with -h):\n");
  printf("\n");
  printf
    ("-i           : source file  (-i source.pnm also *.pgm, *.ppm) \n");
  printf("\n");
  printf
    ("-o           : destination file (-o dest.j2k or .jp2) \n");
  printf("\n");
  printf
    ("Optional Parameters:\n");
  printf("\n");
  printf("-h           : display the help information \n ");
  printf("\n");
  printf("-r           : different compression ratios for successive layers (-r 20,10,5)\n ");
  printf("	         - The rate specified for each quality level is the desired \n");
  printf("	           compression factor.\n");
  printf("		   Example: -r 20,10,1 means quality 1: compress 20x, \n");
  printf("		     quality 2: compress 10x and quality 3: compress lossless\n");
  printf("\n");
  printf("               (options -r and -q cannot be used together)\n ");
  printf("\n");

  printf("-q           : different psnr for successive layers (-q 30,40,50) \n ");

  printf("               (options -r and -q cannot be used together)\n ");

  printf("\n");
  printf("-n           : number of resolutions (-n 3) \n");
  printf("\n");
  printf("-b           : size of code block (-b 32,32) \n");
  printf("\n");
  printf("-c           : size of precinct (-c 128,128) \n");
  printf("\n");
  printf("-t           : size of tile (-t 512,512) \n");
  printf("\n");
  printf
    ("-p           : progression order (-p LRCP) [LRCP, RLCP, RPCL, PCRL, CPRL] \n");
  printf("\n");
  printf
    ("-s           : subsampling factor (-s 2,2) [-s X,Y] \n");
  printf("	     Remark: subsampling bigger than 2 can produce error\n");
  printf("\n");
  printf
    ("-SOP         : write SOP marker before each packet \n");
  printf("\n");
  printf
    ("-EPH         : write EPH marker after each header packet \n");
  printf("\n");
  printf
    ("-M           : mode switch (-M 3) [1=BYPASS(LAZY) 2=RESET 4=RESTART(TERMALL)\n");
  printf
    ("                 8=VSC 16=ERTERM(SEGTERM) 32=SEGMARK(SEGSYM)] \n");
  printf
    ("                 Indicate multiple modes by adding their values. \n");
  printf
    ("                 ex: RESTART(4) + RESET(2) + SEGMARK(32) = -M 38\n");
  printf("\n");
  printf
    ("-x           : create an index file *.Idx (-x index_name.Idx) \n");
  printf("\n");
  printf
    ("-ROI         : c=%%d,U=%%d : quantization indices upshifted \n");
  printf
    ("               for component c=%%d [%%d = 0,1,2]\n");
  printf
    ("               with a value of U=%%d [0 <= %%d <= 37] (i.e. -ROI:c=0,U=25) \n");
  printf("\n");
  printf
    ("-d           : offset of the origin of the image (-d 150,300) \n");
  printf("\n");
  printf
    ("-T           : offset of the origin of the tiles (-T 100,75) \n");
  printf("\n");
  printf("-I           : use the irreversible DWT 9-7 (-I) \n");
  printf("\n");
  printf("-W           : image width, height and the dx and dy subsampling \n");
  printf("               of the Cb and Cr components for YUV files \n");
  printf("               (default is '352,288,2,2' for CIF format's 352x288 and 4:2:0)\n");
  printf("\n");
  printf("-F           : video frame rate (set to 25 by default)\n");

  printf("\n");
  printf("IMPORTANT:\n");
  printf("-----------\n");
  printf("\n");
  printf("The index file has the structure below:\n");
  printf("---------------------------------------\n");
  printf("\n");
  printf("Image_height Image_width\n");
  printf("progression order\n");
  printf("Tiles_size_X Tiles_size_Y\n");
  printf("Components_nb\n");
  printf("Layers_nb\n");
  printf("decomposition_levels\n");
  printf("[Precincts_size_X_res_Nr Precincts_size_Y_res_Nr]...\n");
  printf("   [Precincts_size_X_res_0 Precincts_size_Y_res_0]\n");
  printf("Main_header_end_position\n");
  printf("Codestream_size\n");
  printf("Tile_0 start_pos end_Theader end_pos TotalDisto NumPix MaxMSE\n");
  printf("Tile_1   ''           ''        ''        ''       ''    ''\n");
  printf("...\n");
  printf("Tile_Nt   ''           ''        ''        ''       ''    ''\n");
  printf("Tpacket_0 Tile layer res. comp. prec. start_pos end_pos disto\n");
  printf("...\n");
  printf("Tpacket_Np ''   ''    ''   ''    ''       ''       ''     ''\n");

  printf("MaxDisto\n");

  printf("TotalDisto\n\n");
}

int give_progression(char progression[4])
{
  if (progression[0] == 'L' && progression[1] == 'R'
      && progression[2] == 'C' && progression[3] == 'P') {
    return 0;
  } else {
    if (progression[0] == 'R' && progression[1] == 'L'
	&& progression[2] == 'C' && progression[3] == 'P') {
      return 1;
    } else {
      if (progression[0] == 'R' && progression[1] == 'P'
	  && progression[2] == 'C' && progression[3] == 'L') {
	return 2;
      } else {
	if (progression[0] == 'P' && progression[1] == 'C'
	    && progression[2] == 'R' && progression[3] == 'L') {
	  return 3;
	} else {
	  if (progression[0] == 'C' && progression[1] == 'P'
	      && progression[2] == 'R' && progression[3] == 'L') {
	    return 4;
	  } else {
	    return -1;
	  }
	}
      }
    }
  }
}

double dwt_norms_97[4][10] = {
  {1.000, 1.965, 4.177, 8.403, 16.90, 33.84, 67.69, 135.3, 270.6, 540.9},
  {2.022, 3.989, 8.355, 17.04, 34.27, 68.63, 137.3, 274.6, 549.0},
  {2.022, 3.989, 8.355, 17.04, 34.27, 68.63, 137.3, 274.6, 549.0},
  {2.080, 3.865, 8.307, 17.18, 34.71, 69.59, 139.3, 278.6, 557.2}
};

int floorlog2(int a)
{
  int l;
  for (l = 0; a > 1; l++) {
    a >>= 1;
  }
  return l;
}

void encode_stepsize(int stepsize, int numbps, int *expn, int *mant)
{
  int p, n;
  p = floorlog2(stepsize) - 13;
  n = 11 - floorlog2(stepsize);
  *mant = (n < 0 ? stepsize >> -n : stepsize << n) & 0x7ff;
  *expn = numbps - p;
}

void calc_explicit_stepsizes(j2k_tccp_t * tccp, int prec)
{
  int numbands, bandno;
  numbands = 3 * tccp->numresolutions - 2;
  for (bandno = 0; bandno < numbands; bandno++) {
    double stepsize;

    int resno, level, orient, gain;
    resno = bandno == 0 ? 0 : (bandno - 1) / 3 + 1;
    orient = bandno == 0 ? 0 : (bandno - 1) % 3 + 1;
    level = tccp->numresolutions - 1 - resno;
    gain =
      tccp->qmfbid == 0 ? 0 : (orient ==
			       0 ? 0 : (orient == 1
					|| orient == 2 ? 1 : 2));
    if (tccp->qntsty == J2K_CCP_QNTSTY_NOQNT) {
      stepsize = 1.0;
    } else {
      double norm = dwt_norms_97[orient][level];
      stepsize = (1 << (gain + 1)) / norm;
    }
    encode_stepsize((int) floor(stepsize * 8192.0), prec + gain,
		    &tccp->stepsizes[bandno].expn,
		    &tccp->stepsizes[bandno].mant);
  }
}

int main(int argc, char **argv)
{
  int NumResolution, numD_min;	/*   NumResolution : number of resolution                     */
  int Tile_arg;			/*   Tile_arg = 0 (not in argument) ou = 1 (in argument)      */
  int CSty;			/*   CSty : coding style                                      */
  int Prog_order;		/*   progression order (default LRCP)                         */
  char progression[4];
  int numpocs, numpocs_tile;	/*   Number of progression order change (POC) default 0       */
  int prcw_init[J2K_MAXRLVLS];	/*   Initialisation Precinct width                            */
  int prch_init[J2K_MAXRLVLS];	/*   Initialisation Precinct height                           */
  //int prcw_init, prch_init;                     /*   Initialisation precincts' size                           */
  int cblockw_init, cblockh_init;	/*   Initialisation codeblocks' size                          */
  int mode, value;		/*   Mode switch (cblk_style)                                 */
  int subsampling_dx, subsampling_dy;	/* subsampling value for dx and dy                    */
  int ROI_compno, ROI_shift;	/*   region of interrest                                      */
  int Dim[2];			/*   portion of the image coded                               */
  int TX0, TY0;			/*   tile off-set                                             */
  mj2_movie_t movie;
  j2k_cp_t cp, cp_init;		/*   cp_init is used to initialise in multiple tiles          */
  j2k_tcp_t *tcp, *tcp_init;	/*   tcp_init is used to initialise in multiple tile          */
  j2k_poc_t POC[32];		/*   POC : used in case of Progression order change           */
  j2k_poc_t *tcp_poc;
  j2k_tccp_t *tccp;
  int i, tileno, j;
  char *infile = 0;
  char *outfile = 0;
  char *index = 0;
  char *s, S1, S2, S3;
  int ir = 0;
  int res_spec = 0;		/*   For various precinct sizes specification                 */
  char sep;
  int w;			/*   Width of YUV file                                        */
  int h;			/*   Height of YUV file                                       */
  int CbCr_subsampling_dx;	/*   Sample rate of YUV 4:4:4 4:2:2 or 4:2:0                  */
  int CbCr_subsampling_dy;	/*   Sample rate of YUV 4:4:4 4:2:2 or 4:2:0                  */
  int output_image_type = -1;
  int frame_rate;		/*   Video Frame Rate                                         */
  int numcomps;			/*   In YUV files, numcomps always considered as 3            */
  int prec;			/*   In YUV files, precision always considered as 8           */
  int x1, y1;


  /* default value */
  /* ------------- */
  NumResolution = 6;
  CSty = 0;
  cblockw_init = 64;
  cblockh_init = 64;
  cp.tw = 1;
  cp.th = 1;
  cp.index_on = 0;
  Prog_order = 0;
  numpocs = 0;
  mode = 0;
  subsampling_dx = 1;
  subsampling_dy = 1;
  ROI_compno = -1;		/* no ROI */
  ROI_shift = 0;
  Dim[0] = 0;
  Dim[1] = 0;
  TX0 = 0;
  TY0 = 0;
  cp.comment = NULL;
  cp.disto_alloc = 0;
  cp.fixed_alloc = 0;
  cp.fixed_quality = 0;		//add fixed_quality
  w = 352;			// CIF default value
  h = 288;			// CIF default value
  CbCr_subsampling_dx = 2;	// CIF default value
  CbCr_subsampling_dy = 2;	// CIF default value
  frame_rate = 25;


  Tile_arg = 0;
  cp_init.tcps = (j2k_tcp_t *) malloc(sizeof(j2k_tcp_t));	/* initialisation if only one tile */
  tcp_init = &cp_init.tcps[0];
  tcp_init->numlayers = 0;

  cp.intermed_file = 0;		// Don't store each tile in a file during processing 

  while (1) {
    int c = getopt(argc, argv,
		   "i:o:r:q:f:t:n:c:b:x:p:s:d:h:P:S:E:M:R:T:C:I:W:F:");
    if (c == -1)
      break;
    switch (c) {
    case 'i':			/* IN fill */
      infile = optarg;
      s = optarg;
      while (*s) {
	s++;
      }
      s--;
      S3 = *s;
      s--;
      S2 = *s;
      s--;
      S1 = *s;

      if ((S1 == 'y' && S2 == 'u' && S3 == 'v')
	  || (S1 == 'Y' && S2 == 'U' && S3 == 'V')) {
	cp.image_type = 3;
	break;
      }
      fprintf(stderr,
	      "!! Unrecognized format for infile : %c%c%c [accept only *.yuv] !!\n\n",
	      S1, S2, S3);
      return 1;
      break;
      /* ----------------------------------------------------- */
    case 'o':			/* OUT fill */
      outfile = optarg;
      while (*outfile) {
	outfile++;
      }
      outfile--;
      S3 = *outfile;
      outfile--;
      S2 = *outfile;
      outfile--;
      S1 = *outfile;

      outfile = optarg;

      if ((S1 == 'm' && S2 == 'j' && S3 == '2')
	  || (S1 == 'M' && S2 == 'J' && S3 == '2'))
	cp.JPEG2000_format = 2;
      else {
	fprintf(stderr,
		"Unknown output format image *.%c%c%c [only *.mj2]!! \n",
		S1, S2, S3);
	return 1;
      }



      break;
      /* ----------------------------------------------------- */
    case 'r':			/* rates rates/distorsion */
      s = optarg;
      while (sscanf(s, "%d", &tcp_init->rates[tcp_init->numlayers])
	     == 1) {
	tcp_init->numlayers++;
	while (*s && *s != ',') {
	  s++;
	}
	if (!*s)
	  break;
	s++;
      }
      cp.disto_alloc = 1;
      cp.matrice = NULL;
      break;
      /* ----------------------------------------------------- */
    case 'q':			/* add fixed_quality */
      s = optarg;
      while (sscanf
	     (s, "%f", &tcp_init->distoratio[tcp_init->numlayers]) == 1) {
	tcp_init->numlayers++;
	while (*s && *s != ',') {
	  s++;
	}
	if (!*s)
	  break;
	s++;
      }
      cp.fixed_quality = 1;
      cp.matrice = NULL;
      break;
      /* dda */
      /* ----------------------------------------------------- */
    case 'f':			/* mod fixed_quality (before : -q) */
      s = optarg;
      sscanf(s, "%d", &tcp_init->numlayers);
      s++;
      if (tcp_init->numlayers > 9)
	s++;
      cp.matrice =
	(int *) malloc(tcp_init->numlayers * NumResolution * 3 *
		       sizeof(int));
      s = s + 2;
      for (i = 0; i < tcp_init->numlayers; i++) {
	tcp_init->rates[i] = 1;
	sscanf(s, "%d,", &cp.matrice[i * NumResolution * 3]);
	s += 2;
	if (cp.matrice[i * NumResolution * 3] > 9)
	  s++;
	cp.matrice[i * NumResolution * 3 + 1] = 0;
	cp.matrice[i * NumResolution * 3 + 2] = 0;
	for (j = 1; j < NumResolution; j++) {
	  sscanf(s, "%d,%d,%d",
		 &cp.matrice[i * NumResolution * 3 + j * 3 + 0],
		 &cp.matrice[i * NumResolution * 3 + j * 3 + 1],
		 &cp.matrice[i * NumResolution * 3 + j * 3 + 2]);
	  s += 6;
	  if (cp.matrice[i * NumResolution * 3 + j * 3] > 9)
	    s++;
	  if (cp.matrice[i * NumResolution * 3 + j * 3 + 1] > 9)
	    s++;
	  if (cp.matrice[i * NumResolution * 3 + j * 3 + 2] > 9)
	    s++;
	}
	if (i < tcp_init->numlayers - 1)
	  s++;
      }
      cp.fixed_alloc = 1;
      break;
      /* ----------------------------------------------------- */
    case 't':			/* tiles */
      sscanf(optarg, "%d,%d", &cp.tdx, &cp.tdy);
      Tile_arg = 1;
      break;
      /* ----------------------------------------------------- */
    case 'n':			/* resolution */
      sscanf(optarg, "%d", &NumResolution);
      break;
      /* ----------------------------------------------------- */
    case 'c':			/* precinct dimension */
      s = optarg;
      do {
	sep = 0;
	sscanf(s, "[%d,%d]%c", &prcw_init[res_spec],
	       &prch_init[res_spec], &sep);
	CSty |= 0x01;
	res_spec++;
	s = strpbrk(s, "]") + 2;
      } while (sep == ',');
      break;
      /* ----------------------------------------------------- */
    case 'b':			/* code-block dimension */
      sscanf(optarg, "%d,%d", &cblockw_init, &cblockh_init);
      if (cblockw_init * cblockh_init > 4096 || cblockw_init > 1024
	  || cblockw_init < 4 || cblockh_init > 1024 || cblockh_init < 4) {
	fprintf(stderr,
		"!! Size of code_block error (option -b) !!\n\nRestriction :\n    * width*height<=4096\n    * 4<=width,height<= 1024\n\n");
	return 1;
      }
      break;
      /* ----------------------------------------------------- */
    case 'x':			/* creation of index file */
      index = optarg;
      cp.index_on = 1;
      break;
      /* ----------------------------------------------------- */
    case 'p':			/* progression order */
      s = optarg;
      for (i = 0; i < 4; i++) {
	progression[i] = *s;
	s++;
      }
      Prog_order = give_progression(progression);

      if (Prog_order == -1) {
	fprintf(stderr,
		"Unrecognized progression order [LRCP, RLCP, RPCL, PCRL, CPRL] !!\n");
	return 1;
      }
      break;
      /* ----------------------------------------------------- */
    case 's':			/* subsampling factor */
      if (sscanf(optarg, "%d,%d", &subsampling_dx, &subsampling_dy)
	  != 2) {
	fprintf(stderr,
		"'-s' sub-sampling argument error !  [-s dx,dy]\n");
	return 1;
      }
      break;
      /* ----------------------------------------------------- */
    case 'd':			/* coordonnate of the reference grid */
      if (sscanf(optarg, "%d,%d", &Dim[0], &Dim[1]) != 2) {
	fprintf(stderr,
		"-d 'coordonnate of the reference grid' argument error !! [-d x0,y0]\n");
	return 1;
      }
      break;
      /* ----------------------------------------------------- */
    case 'h':			/* Display an help description */
      help_display();
      return 0;
      break;
      /* ----------------------------------------------------- */
    case 'P':			/* POC */
      fprintf(stderr, "/----------------------------------\\\n");
      fprintf(stderr, "|  POC option not fully tested !!  |\n");
      fprintf(stderr, "\\----------------------------------/\n");

      s = optarg;
      while (sscanf(s, "T%d=%d,%d,%d,%d,%d,%s", &POC[numpocs].tile,
		    &POC[numpocs].resno0, &POC[numpocs].compno0,
		    &POC[numpocs].layno1, &POC[numpocs].resno1,
		    &POC[numpocs].compno1, POC[numpocs].progorder) == 7) {
	POC[numpocs].prg = give_progression(POC[numpocs].progorder);
	/* POC[numpocs].tile; */
	numpocs++;
	while (*s && *s != '/') {
	  s++;
	}
	if (!*s)
	  break;
	s++;
      }
      break;
      /* ------------------------------------------------------ */
    case 'S':			/* SOP marker */
      CSty |= 0x02;
      break;
      /* ------------------------------------------------------ */
    case 'E':			/* EPH marker */
      CSty |= 0x04;
      break;
      /* ------------------------------------------------------ */
    case 'M':			/* Mode switch pas tous au point !! */
      if (sscanf(optarg, "%d", &value) == 1) {
	for (i = 0; i <= 5; i++) {
	  int cache = value & (1 << i);
	  if (cache)
	    mode |= (1 << i);
	}
      }
      break;
      /* ------------------------------------------------------ */
    case 'R':			/* ROI */
      if (sscanf(optarg, "OI:c=%d,U=%d", &ROI_compno, &ROI_shift) != 2) {
	fprintf(stderr, "ROI error !! [-ROI:c='compno',U='shift']\n");
	return 1;
      }
      break;
      /* ------------------------------------------------------ */
    case 'T':			/* Tile offset */
      if (sscanf(optarg, "%d,%d", &TX0, &TY0) != 2) {
	fprintf(stderr, "-T 'tile offset' argument error !! [-T X0,Y0]");
	return 1;
      }
      break;
      /* ------------------------------------------------------ */
    case 'C':			/* Add a comment */
      cp.comment = optarg;
      break;
      /* ------------------------------------------------------ */
    case 'I':			/* reversible or not */
      ir = 1;
      break;
      /* ------------------------------------------------------ */
    case 'W':			/* Width and Height and Cb and Cr subsampling in case of YUV format files */
      if (sscanf
	  (optarg, "%d,%d,%d,%d", &w, &h, &CbCr_subsampling_dx,
	   &CbCr_subsampling_dy) != 4) {
	fprintf(stderr, "-W argument error");
	return 1;
      }
      break;
      /* ------------------------------------------------------ */
    case 'F':			/* Video frame rate */
      if (sscanf(optarg, "%d", &frame_rate) != 1) {
	fprintf(stderr, "-F argument error");
	return 1;
      }
      break;
      /* ------------------------------------------------------ */
    default:
      return 1;
    }
  }

  cp.tx0 = TX0;
  cp.ty0 = TY0;

  /* Error messages */
  /* -------------- */
  if (!infile || !outfile) {
    fprintf(stderr,
	    "usage: frames_to_mj2 -i yuv-file -o mj2-file (+ options)\n");
    return 1;
  }

  if ((cp.disto_alloc || cp.fixed_alloc || cp.fixed_quality)
      && (!(cp.disto_alloc ^ cp.fixed_alloc ^ cp.fixed_quality))) {
    fprintf(stderr,
	    "Error: options -r -q and -f can not be used together !!\n");
    return 1;
  }				// mod fixed_quality

  /* if no rate entered, lossless by default */
  if (tcp_init->numlayers == 0) {
    tcp_init->rates[tcp_init->numlayers] = 0;   //MOD antonin : losslessbug
    tcp_init->numlayers++;
    cp.disto_alloc = 1;
  }

  if (TX0 > Dim[0] || TY0 > Dim[1]) {
    fprintf(stderr,
	    "Error: Tile offset dimension is unnappropriate --> TX0(%d)<=IMG_X0(%d) TYO(%d)<=IMG_Y0(%d) \n",
	    TX0, Dim[0], TY0, Dim[1]);
    return 1;
  }

  for (i = 0; i < numpocs; i++) {
    if (POC[i].prg == -1) {
      fprintf(stderr,
	      "Unrecognized progression order in option -P (POC n %d) [LRCP, RLCP, RPCL, PCRL, CPRL] !!\n",
	      i + 1);
    }
  }

  /* to respect profile - 0 */
  /* ---------------------- */
  numD_min = 0;

  x1 = !Dim[0] ? (w - 1) * subsampling_dx + 1 : Dim[0] + (w -
							  1) *
    subsampling_dx + 1;
  y1 = !Dim[1] ? (h - 1) * subsampling_dy + 1 : Dim[1] + (h -
							  1) *
    subsampling_dy + 1;

  if (Tile_arg == 1) {
    cp.tw = int_ceildiv(x1 - cp.tx0, cp.tdx);
    cp.th = int_ceildiv(y1 - cp.ty0, cp.tdy);
  } else {
    cp.tdx = x1 - cp.tx0;
    cp.tdy = y1 - cp.ty0;
  }


  /* Initialization for PPM marker */
  cp.ppm = 0;
  cp.ppm_data = NULL;
  cp.ppm_previous = 0;
  cp.ppm_store = 0;

  numcomps = 3;			/* Because YUV files only have 3 components */

  tcp_init->mct = 0;		/* No component transform needed */

  prec = 8;			/* Because in YUV files, components have 8-bit depth */

  /* Init the mutiple tiles */
  /* ---------------------- */
  cp.tcps = (j2k_tcp_t *) malloc(cp.tw * cp.th * sizeof(j2k_tcp_t));

  for (tileno = 0; tileno < cp.tw * cp.th; tileno++) {
    tcp = &cp.tcps[tileno];
    tcp->numlayers = tcp_init->numlayers;
    for (j = 0; j < tcp->numlayers; j++) {
      if (cp.fixed_quality)	// add fixed_quality
	tcp->distoratio[j] = tcp_init->distoratio[j];
      else
	tcp->rates[j] = tcp_init->rates[j];
    }
    tcp->csty = CSty;
    tcp->prg = Prog_order;
    tcp->mct = tcp_init->mct;
    tcp->ppt = 0;
    tcp->ppt_data = NULL;
    tcp->ppt_store = 0;

    numpocs_tile = 0;
    tcp->POC = 0;
    if (numpocs) {
      /* intialisation of POC */
      tcp->POC = 1;
      for (i = 0; i < numpocs; i++) {
	if (tileno == POC[i].tile - 1 || POC[i].tile == -1) {
	  tcp_poc = &tcp->pocs[numpocs_tile];
	  tcp_poc->resno0 = POC[numpocs_tile].resno0;
	  tcp_poc->compno0 = POC[numpocs_tile].compno0;
	  tcp_poc->layno1 = POC[numpocs_tile].layno1;
	  tcp_poc->resno1 = POC[numpocs_tile].resno1;
	  tcp_poc->compno1 = POC[numpocs_tile].compno1;
	  tcp_poc->prg = POC[numpocs_tile].prg;
	  tcp_poc->tile = POC[numpocs_tile].tile;
	  numpocs_tile++;
	}
      }
    }
    tcp->numpocs = numpocs_tile;
    tcp->tccps = (j2k_tccp_t *) malloc(numcomps * sizeof(j2k_tccp_t));

    for (i = 0; i < numcomps; i++) {
      tccp = &tcp->tccps[i];
      tccp->csty = CSty & 0x01;	/* 0 => one precinct || 1 => custom precinct  */
      tccp->numresolutions = NumResolution;
      tccp->cblkw = int_floorlog2(cblockw_init);
      tccp->cblkh = int_floorlog2(cblockh_init);
      tccp->cblksty = mode;
      tccp->qmfbid = ir ? 0 : 1;
      tccp->qntsty = ir ? J2K_CCP_QNTSTY_SEQNT : J2K_CCP_QNTSTY_NOQNT;
      tccp->numgbits = 2;
      if (i == ROI_compno)
	tccp->roishift = ROI_shift;
      else
	tccp->roishift = 0;
      if (CSty & J2K_CCP_CSTY_PRT) {
	int p = 0;
	for (j = tccp->numresolutions - 1; j >= 0; j--) {
	  if (p < res_spec) {
	    if (prcw_init[p] < 1)
	      tccp->prcw[j] = 1;
	    else
	      tccp->prcw[j] = int_floorlog2(prcw_init[p]);

	    if (prch_init[p] < 1)
	      tccp->prch[j] = 1;
	    else
	      tccp->prch[j] = int_floorlog2(prch_init[p]);
	  } else {
	    int size_prcw, size_prch;
	    size_prcw = prcw_init[res_spec - 1] >> (p - (res_spec - 1));
	    size_prch = prch_init[res_spec - 1] >> (p - (res_spec - 1));
	    if (size_prcw < 1)
	      tccp->prcw[j] = 1;
	    else
	      tccp->prcw[j] = int_floorlog2(size_prcw);
	    if (size_prch < 1)
	      tccp->prch[j] = 1;
	    else
	      tccp->prch[j] = int_floorlog2(size_prch);
	  }
	  p++;
	  /*printf("\nsize precinct pour level %d : %d,%d\n", j,
	     tccp->prcw[j], tccp->prch[j]); */
	}
      } else {
	for (j = 0; j < tccp->numresolutions; j++) {
	  tccp->prcw[j] = 15;
	  tccp->prch[j] = 15;
	}
      }
      calc_explicit_stepsizes(tccp, prec);
    }
  }

  movie.tk = (mj2_tk_t *) malloc(sizeof(mj2_tk_t));
  movie.num_vtk = 1;
  movie.num_stk = 0;
  movie.num_htk = 0;

  movie.tk[0].imagefile = infile;
  movie.tk[0].track_type = 0;	// Video Track
  movie.tk[0].track_ID = 1;
  movie.mj2file = outfile;
  movie.tk[0].subsampling_dx = subsampling_dx;
  movie.tk[0].subsampling_dy = subsampling_dy;
  movie.tk[0].Dim[0] = Dim[0];
  movie.tk[0].Dim[1] = Dim[1];
  movie.tk[0].w = w;
  movie.tk[0].h = h;
  movie.tk[0].CbCr_subsampling_dx = CbCr_subsampling_dx;
  movie.tk[0].CbCr_subsampling_dy = CbCr_subsampling_dy;
  movie.tk[0].sample_rate = frame_rate;

  if (mj2_init_stdmovie(&movie)) {
    fprintf(stderr, "Error with movie initialization");
    return 1;
  };
  if (mj2_encode(&movie, &cp, index)) {
    fprintf(stderr, "Error encoding movie");
    return 1;
  };
  mj2_memory_free(&movie);

  /* Free cp memory */
  free(cp_init.tcps);
  if (tcp_init->numlayers > 9)
    free(cp.matrice);
  for (tileno = 0; tileno < cp.tw * cp.th; tileno++)
    free(cp.tcps[tileno].tccps);
  free(cp.tcps);

  return 0;
}
