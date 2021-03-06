#ifndef __AMINOACIDPROBS_H__
#define __AMINOACIDPROBS_H__


#include "ME_REG.h"
#include "Config.h"


// used to score aa that are not connected to the terminals or the digest nodes

typedef enum ScoreModelFields_SAA { 
	
	SAA_CONST,

	SAA_IND_SEQ_RANK_1,  SAA_IND_SEQ_RANK_2, SAA_IND_SEQ_RANK_3, SAA_IND_SEQ_RANK_4, SAA_IND_SEQ_RANK_5,
	SAA_IND_SEQ_RANK_6,  SAA_IND_SEQ_RANK_8, SAA_IND_SEQ_RANK_10, SAA_IND_SEQ_RANK_12, SAA_IND_SEQ_RANK_14,
	SAA_IND_SEQ_RANK_16,  SAA_IND_SEQ_RANK_20, SAA_IND_SEQ_RANK_MORE,

	// relatice position in terms of mass and amount of node score before the N-terminal (rounded up)
	SAA_IND_AA_POS_20, SAA_IND_AA_POS_40, SAA_IND_AA_POS_60, SAA_IND_AA_POS_80, SAA_IND_AA_POS_100,
	SAA_IND_AA_REL_SCORE_20, SAA_IND_AA_REL_SCORE_40, SAA_IND_AA_REL_SCORE_60, SAA_IND_AA_REL_SCORE_80, SAA_IND_AA_REL_SCORE_100,

	SAA_MAX_NODE_SCORE,			  SAA_MIN_NODE_SCORE,

	SAA_N_SCORE_ABOVE_TWO_THIRDS, SAA_C_SCORE_ABOVE_TWO_THIRDS, SAA_IND_TWO_THIRDS_BOTH_ABOVE,
	SAA_N_SCORE_ABOVE_THIRD,	  SAA_C_SCORE_ABOVE_THIRD,		SAA_IND_THIRD_BOTH_ABOVE,
	SAA_N_SCORE_ABOVE_ZERO,		  SAA_C_SCORE_ABOVE_ZERO,	    SAA_IND_ZERO_BOTH_ABOVE,

	SAA_MAX_SCORE_RANK,	SAA_MIN_SCORE_RANK,		SAA_N_SCORE_RANK,   SAA_C_SCORE_RANK, SAA_SCORE_RANK_SUM,
	SAA_SCORE_RANK_DIFF,	SAA_SCORE_RANK_ABS_DIFF, 
	SAA_N_NUM_FRAGS,   SAA_C_NUM_FRAGS, SAA_NUM_FRAG_DIFF, SAA_ABS_NUM_FRAG_DIFF,
	SAA_IND_N_STRONGER_INTEN, SAA_N_STRONGER_LOG_NC_INTEN_RATIO,      // max val +- 5 
	SAA_IND_C_STRONGER_INTEN, SAA_C_STRONGER_LOG_NC_INTEN_RATIO,      // max val +- 5 

	SAA_IND_N_IS_MAX_IDX_TO_C,   SAA_IND_C_IS_MAX_IDX_FROM_N,  SAA_DIFF_N_MAX_IN_C_SCORE_RANKS, 
	SAA_IND_N_NOT_MAX_IDX_TO_C,  SAA_IND_C_NOT_MAX_IDX_FROM_N, SAA_DIFF_C_MAX_OUT_N_SCORE_RANKS,

	SAA_IND_BOTH_CONNECT_TO_MAX, 

	SAA_NODE_MASS_DIFF,     SAA_NODE_SQR_MASS_DIFF,    SAA_NUM_FRAG_PAIRS,
	SAA_AVG_PEAK_DIFF,      SAA_AVG_PEAK_SQR_DIFF,
	SAA_BEST_PEAK_DIFF,     SAA_BEST_PEAK_SQR_DIFF,    SAA_IND_NO_PEAK_DIFF,

	SAA_AVG_PEAK_DIFF_TIMES_SCORE_RANK_SUM,
	SAA_AVG_PEAK_DIFF_TIMES_SCORE_ABS_DIFF,
	SAA_AVG_PEAK_DIFF_DIV_NUM_FRAG_PAIRS,

	SAA_IND_BOTH_CONNECT_TO_MAX_TIMES_AVG_DIFF,

	SAA_IND_N_SCORE_MORE_THAN_MIRROR, SAA_IND_C_SCORE_MORE_THAN_MIRROR, SAA_IND_BOTH_SCORE_MORE_THAN_MIRROR,
	SAA_LOG_DIFF_MORE_THAN_MIRROR,	  SAA_LOG_DIFF_LESS_THAN_MIRROR,    SAA_NO_MIRROR,

	SAA_IND_AA_N_TERM,	SAA_IND_AA_C_TERM,	SAA_IND_AA_Gap,	SAA_IND_AA_Xle,	SAA_IND_AA_Ala,
	SAA_IND_AA_Arg,		SAA_IND_AA_Asn,		SAA_IND_AA_Asp,	SAA_IND_AA_Cys,	SAA_IND_AA_Gln,
	SAA_IND_AA_Glu,		SAA_IND_AA_Gly,		SAA_IND_AA_His,	SAA_IND_AA_Ile,	SAA_IND_AA_Leu,
	SAA_IND_AA_Lys,		SAA_IND_AA_Met,		SAA_IND_AA_Phe,	SAA_IND_AA_Pro,	SAA_IND_AA_Ser,
	SAA_IND_AA_Thr,		SAA_IND_AA_Trp,		SAA_IND_AA_Tyr,	SAA_IND_AA_Val,

	SAA_SCORE_RANK_SUM_N_TERM,	SAA_SCORE_RANK_SUM_C_TERM,	SAA_SCORE_RANK_SUM_Gap,	SAA_SCORE_RANK_SUM_Xle,	SAA_SCORE_RANK_SUM_Ala,
	SAA_SCORE_RANK_SUM_Arg,		SAA_SCORE_RANK_SUM_Asn,		SAA_SCORE_RANK_SUM_Asp,	SAA_SCORE_RANK_SUM_Cys,	SAA_SCORE_RANK_SUM_Gln,
	SAA_SCORE_RANK_SUM_Glu,		SAA_SCORE_RANK_SUM_Gly,		SAA_SCORE_RANK_SUM_His,	SAA_SCORE_RANK_SUM_Ile,	SAA_SCORE_RANK_SUM_Leu,
	SAA_SCORE_RANK_SUM_Lys,		SAA_SCORE_RANK_SUM_Met,		SAA_SCORE_RANK_SUM_Phe,	SAA_SCORE_RANK_SUM_Pro,	SAA_SCORE_RANK_SUM_Ser,
	SAA_SCORE_RANK_SUM_Thr,		SAA_SCORE_RANK_SUM_Trp,		SAA_SCORE_RANK_SUM_Tyr,	SAA_SCORE_RANK_SUM_Val,
	
	SAA_SCORE_RANK_DIFF_N_TERM,	SAA_SCORE_RANK_DIFF_C_TERM,	SAA_SCORE_RANK_DIFF_Gap,	SAA_SCORE_RANK_DIFF_Xle,	SAA_SCORE_RANK_DIFF_Ala,
	SAA_SCORE_RANK_DIFF_Arg,	SAA_SCORE_RANK_DIFF_Asn,	SAA_SCORE_RANK_DIFF_Asp,	SAA_SCORE_RANK_DIFF_Cys,	SAA_SCORE_RANK_DIFF_Gln,
	SAA_SCORE_RANK_DIFF_Glu,	SAA_SCORE_RANK_DIFF_Gly,	SAA_SCORE_RANK_DIFF_His,	SAA_SCORE_RANK_DIFF_Ile,	SAA_SCORE_RANK_DIFF_Leu,
	SAA_SCORE_RANK_DIFF_Lys,	SAA_SCORE_RANK_DIFF_Met,	SAA_SCORE_RANK_DIFF_Phe,	SAA_SCORE_RANK_DIFF_Pro,	SAA_SCORE_RANK_DIFF_Ser,
	SAA_SCORE_RANK_DIFF_Thr,	SAA_SCORE_RANK_DIFF_Trp,	SAA_SCORE_RANK_DIFF_Tyr,	SAA_SCORE_RANK_DIFF_Val,

	SAA_NUM_FIELDS
} ScoreModelFields_SAA;


typedef enum ScoreModelFields_SAANCD { 	
	SAANCD_CONST,

	SAANCD_IND_SEQ_RANK_1,  SAANCD_IND_SEQ_RANK_2, SAANCD_IND_SEQ_RANK_3, SAANCD_IND_SEQ_RANK_4, SAANCD_IND_SEQ_RANK_5,
	SAANCD_IND_SEQ_RANK_6,  SAANCD_IND_SEQ_RANK_8, SAANCD_IND_SEQ_RANK_10, SAANCD_IND_SEQ_RANK_12, SAANCD_IND_SEQ_RANK_14,
	SAANCD_IND_SEQ_RANK_16,  SAANCD_IND_SEQ_RANK_20, SAANCD_IND_SEQ_RANK_MORE,

	SAANCD_IND_CONNECTS_TO_NODE_WITH_NO_FRAGS,
	SAANCD_IND_CONNECTS_TO_N_TERMINAL,
	SAANCD_IND_CONNECTS_TO_C_TERMINAL,
	SAANCD_IND_CONNECTS_TO_DIGEST,

	SAANCD_IND_HAS_MAX_SCORE_FROM_N,  	SAANCD_SCORE_FROM_N,
	SAANCD_IND_HAS_MAX_SCORE_TO_C,      SAANCD_SCORE_TO_C,
	SAANCD_IND_HAS_MAX_SCORE_TO_DIGEST, SAANCD_SCORE_TO_DIGEST,

	SAANCD_NODE_MASS_DIFF_FROM_N,     SAANCD_NODE_SQR_MASS_DIFF_FROM_N,
	SAANCD_NODE_MASS_DIFF_TO_C,       SAANCD_NODE_SQR_MASS_DIFF_TO_C,
	SAANCD_NODE_MASS_DIFF_TO_DIGEST,  SAANCD_NODE_SQR_MASS_DIFF_TO_DIGEST,

	SAANCD_IND_TERM_TO_DIGEST, SAANCD_IND_TERM_TO_DIGEST_WITH_FRAGS,  SAANCD_IND_TERM_TO_DIGEST_W_POS_SCORE,

	SAANCD_IND_NT_AA_N_TERM,	SAANCD_IND_NT_AA_C_TERM,	SAANCD_IND_NT_AA_Gap,	SAANCD_IND_NT_AA_Xle,	SAANCD_IND_NT_AA_Ala,
	SAANCD_IND_NT_AA_Arg,		SAANCD_IND_NT_AA_Asn,		SAANCD_IND_NT_AA_Asp,	SAANCD_IND_NT_AA_Cys,	SAANCD_IND_NT_AA_Gln,
	SAANCD_IND_NT_AA_Glu,		SAANCD_IND_NT_AA_Gly,		SAANCD_IND_NT_AA_His,	SAANCD_IND_NT_AA_Ile,	SAANCD_IND_NT_AA_Leu,
	SAANCD_IND_NT_AA_Lys,		SAANCD_IND_NT_AA_Met,		SAANCD_IND_NT_AA_Phe,	SAANCD_IND_NT_AA_Pro,	SAANCD_IND_NT_AA_Ser,
	SAANCD_IND_NT_AA_Thr,		SAANCD_IND_NT_AA_Trp,		SAANCD_IND_NT_AA_Tyr,	SAANCD_IND_NT_AA_Val,

	SAANCD_NUM_FIELDS
} ScoreModelFields_SAANCD;


typedef enum ScoreModelFields_DAA { 
	
	DAA_CONST,

	DAA_IND_SEQ_RANK_1,  DAA_IND_SEQ_RANK_2, DAA_IND_SEQ_RANK_3, DAA_IND_SEQ_RANK_4, DAA_IND_SEQ_RANK_5,
	DAA_IND_SEQ_RANK_6,  DAA_IND_SEQ_RANK_8, DAA_IND_SEQ_RANK_10, DAA_IND_SEQ_RANK_12, DAA_IND_SEQ_RANK_14,
	DAA_IND_SEQ_RANK_16,  DAA_IND_SEQ_RANK_20, DAA_IND_SEQ_RANK_MORE,


	// relatice position in terms of mass and amount of node score before the N-terminal (rounded up)
	DAA_IND_AA_POS_20, DAA_IND_AA_POS_40, DAA_IND_AA_POS_60, DAA_IND_AA_POS_80, DAA_IND_AA_POS_100,
	DAA_IND_AA_REL_SCORE_20, DAA_IND_AA_REL_SCORE_40, DAA_IND_AA_REL_SCORE_60, DAA_IND_AA_REL_SCORE_80, DAA_IND_AA_REL_SCORE_100,

	DAA_MAX_NODE_SCORE,			  DAA_MIN_NODE_SCORE,

	DAA_N_SCORE_ABOVE_TWO_THIRDS, DAA_C_SCORE_ABOVE_TWO_THIRDS,
	DAA_IND_TWO_THIRDS_BOTH_ABOVE,

	DAA_N_SCORE_ABOVE_THIRD, DAA_C_SCORE_ABOVE_THIRD,
	DAA_IND_THIRD_BOTH_ABOVE,

	DAA_N_SCORE_ABOVE_ZERO, DAA_C_SCORE_ABOVE_ZERO,
	DAA_IND_ZERO_BOTH_ABOVE,

	DAA_IND_BOTH_ABOVE_FIVE,
	DAA_IND_N_ABOVE_FIVE, DAA_IND_C_ABOVE_FIVE,

	DAA_MAX_SCORE_RANK, DAA_MIN_SCORE_RANK,  
	DAA_N_SCORE_RANK,   DAA_C_SCORE_RANK, DAA_SCORE_RANK_SUM,
	DAA_SCORE_RANK_DIFF, DAA_SCORE_RANK_ABS_DIFF, 
	DAA_N_NUM_FRAGS,   DAA_C_NUM_FRAGS, DAA_NUM_FRAG_DIFF, DAA_ABS_NUM_FRAG_DIFF,
	
	DAA_IND_N_IS_MAX_IDX_TO_C,   
	DAA_IND_C_IS_MAX_IDX_FROM_N, DAA_DIFF_N_MAX_IN_C_SCORE_RANKS, 
	DAA_IND_N_NOT_MAX_IDX_TO_C,   
	DAA_IND_C_NOT_MAX_IDX_FROM_N, DAA_DIFF_C_MAX_OUT_N_SCORE_RANKS,

	DAA_IND_BOTH_CONNECT_TO_MAX, 

	DAA_NODE_MASS_DIFF,     DAA_NODE_SQR_MASS_DIFF,    DAA_NUM_FRAG_PAIRS,
	DAA_AVG_PEAK_DIFF,      DAA_AVG_PEAK_SQR_DIFF,
	DAA_BEST_PEAK_DIFF,     DAA_BEST_PEAK_SQR_DIFF,    DAA_IND_NO_PEAK_DIFF,

	DAA_AVG_PEAK_DIFF_TIMES_SCORE_RANK_SUM,
	DAA_AVG_PEAK_DIFF_TIMES_SCORE_ABS_DIFF,
	DAA_AVG_PEAK_DIFF_DIV_NUM_FRAG_PAIRS,

	DAA_IND_BOTH_CONNECT_TO_MAX_TIMES_AVG_DIFF,

	DAA_NUM_DOUBLE_EDGE_ROUTES, 
	DAA_IND_NO_DOUBLE_EDGE_ROUTES,
	DAA_SCORE_RANK_DOUBLE_EDGE_ROUTES,
	DAA_IND_IND_MAX_SCORE_ALTERNATE_MORE_THAN_ZERO,
	DAA_IND_MAX_ALTERNATE_IS_MAX_OUT_N,
	DAA_IND_MAX_ALTERNATE_IS_MAX_IN_C,
	DAA_NODE_OFFSETS_ALTERNTE,
	DAA_SQR_NODE_ODFFSETS_ALTERNATE,

	DAA_IND_N_SCORE_MORE_THAN_MIRROR, DAA_IND_C_SCORE_MORE_THAN_MIRROR, DAA_IND_BOTH_SCORE_MORE_THAN_MIRROR,
	DAA_LOG_DIFF_MORE_THAN_MIRROR,	  DAA_LOG_DIFF_LESS_THAN_MIRROR,	DAA_NO_MIRROR,

	DAA_IND_PROBLEMATIC_PAIR_OF_AAS,

	DAA_IND_N_AA_N_TERM,	DAA_IND_N_AA_C_TERM,	DAA_IND_N_AA_Gap,	DAA_IND_N_AA_Xle,	DAA_IND_N_AA_Ala,
	DAA_IND_N_AA_Arg,		DAA_IND_N_AA_Asn,		DAA_IND_N_AA_Asp,	DAA_IND_N_AA_Cys,	DAA_IND_N_AA_Gln,
	DAA_IND_N_AA_Glu,		DAA_IND_N_AA_Gly,		DAA_IND_N_AA_His,	DAA_IND_N_AA_Ile,	DAA_IND_N_AA_Leu,
	DAA_IND_N_AA_Lys,		DAA_IND_N_AA_Met,		DAA_IND_N_AA_Phe,	DAA_IND_N_AA_Pro,	DAA_IND_N_AA_Ser,
	DAA_IND_N_AA_Thr,		DAA_IND_N_AA_Trp,		DAA_IND_N_AA_Tyr,	DAA_IND_N_AA_Val,

	DAA_SCORE_RANK_SUM_N_N_TERM,	DAA_SCORE_RANK_SUM_N_C_TERM,	DAA_SCORE_RANK_SUM_N_Gap,	DAA_SCORE_RANK_SUM_N_Xle,	DAA_SCORE_RANK_SUM_N_Ala,
	DAA_SCORE_RANK_SUM_N_Arg,		DAA_SCORE_RANK_SUM_N_Asn,		DAA_SCORE_RANK_SUM_N_Asp,	DAA_SCORE_RANK_SUM_N_Cys,	DAA_SCORE_RANK_SUM_N_Gln,
	DAA_SCORE_RANK_SUM_N_Glu,		DAA_SCORE_RANK_SUM_N_Gly,		DAA_SCORE_RANK_SUM_N_His,	DAA_SCORE_RANK_SUM_N_Ile,	DAA_SCORE_RANK_SUM_N_Leu,
	DAA_SCORE_RANK_SUM_N_Lys,		DAA_SCORE_RANK_SUM_N_Met,		DAA_SCORE_RANK_SUM_N_Phe,	DAA_SCORE_RANK_SUM_N_Pro,	DAA_SCORE_RANK_SUM_N_Ser,
	DAA_SCORE_RANK_SUM_N_Thr,		DAA_SCORE_RANK_SUM_N_Trp,		DAA_SCORE_RANK_SUM_N_Tyr,	DAA_SCORE_RANK_SUM_N_Val,	
	
	DAA_SCORE_RANK_DIFF_N_N_TERM,	DAA_SCORE_RANK_DIFF_N_C_TERM,	DAA_SCORE_RANK_DIFF_N_Gap,	DAA_SCORE_RANK_DIFF_N_Xle,	DAA_SCORE_RANK_DIFF_N_Ala,
	DAA_SCORE_RANK_DIFF_N_Arg,	DAA_SCORE_RANK_DIFF_N_Asn,	DAA_SCORE_RANK_DIFF_N_Asp,	DAA_SCORE_RANK_DIFF_N_Cys,	DAA_SCORE_RANK_DIFF_N_Gln,
	DAA_SCORE_RANK_DIFF_N_Glu,	DAA_SCORE_RANK_DIFF_N_Gly,	DAA_SCORE_RANK_DIFF_N_His,	DAA_SCORE_RANK_DIFF_N_Ile,	DAA_SCORE_RANK_DIFF_N_Leu,
	DAA_SCORE_RANK_DIFF_N_Lys,	DAA_SCORE_RANK_DIFF_N_Met,	DAA_SCORE_RANK_DIFF_N_Phe,	DAA_SCORE_RANK_DIFF_N_Pro,	DAA_SCORE_RANK_DIFF_N_Ser,
	DAA_SCORE_RANK_DIFF_N_Thr,	DAA_SCORE_RANK_DIFF_N_Trp,	DAA_SCORE_RANK_DIFF_N_Tyr,	DAA_SCORE_RANK_DIFF_N_Val,

	DAA_IND_C_AA_N_TERM,	DAA_IND_C_AA_C_TERM,	DAA_IND_C_AA_Gap,	DAA_IND_C_AA_Xle,	DAA_IND_C_AA_Ala,
	DAA_IND_C_AA_Arg,		DAA_IND_C_AA_Asn,		DAA_IND_C_AA_Asp,	DAA_IND_C_AA_Cys,	DAA_IND_C_AA_Gln,
	DAA_IND_C_AA_Glu,		DAA_IND_C_AA_Gly,		DAA_IND_C_AA_His,	DAA_IND_C_AA_Ile,	DAA_IND_C_AA_Leu,
	DAA_IND_C_AA_Lys,		DAA_IND_C_AA_Met,		DAA_IND_C_AA_Phe,	DAA_IND_C_AA_Pro,	DAA_IND_C_AA_Ser,
	DAA_IND_C_AA_Thr,		DAA_IND_C_AA_Trp,		DAA_IND_C_AA_Tyr,	DAA_IND_C_AA_Val,

	DAA_SCORE_RANK_SUM_C_N_TERM,	DAA_SCORE_RANK_SUM_C_C_TERM,	DAA_SCORE_RANK_SUM_C_Gap,	DAA_SCORE_RANK_SUM_C_Xle,	DAA_SCORE_RANK_SUM_C_Ala,
	DAA_SCORE_RANK_SUM_C_Arg,		DAA_SCORE_RANK_SUM_C_Asn,		DAA_SCORE_RANK_SUM_C_Asp,	DAA_SCORE_RANK_SUM_C_Cys,	DAA_SCORE_RANK_SUM_C_Gln,
	DAA_SCORE_RANK_SUM_C_Glu,		DAA_SCORE_RANK_SUM_C_Gly,		DAA_SCORE_RANK_SUM_C_His,	DAA_SCORE_RANK_SUM_C_Ile,	DAA_SCORE_RANK_SUM_C_Leu,
	DAA_SCORE_RANK_SUM_C_Lys,		DAA_SCORE_RANK_SUM_C_Met,		DAA_SCORE_RANK_SUM_C_Phe,	DAA_SCORE_RANK_SUM_C_Pro,	DAA_SCORE_RANK_SUM_C_Ser,
	DAA_SCORE_RANK_SUM_C_Thr,		DAA_SCORE_RANK_SUM_C_Trp,		DAA_SCORE_RANK_SUM_C_Tyr,	DAA_SCORE_RANK_SUM_C_Val,

	DAA_SCORE_RANK_DIFF_C_N_TERM,	DAA_SCORE_RANK_DIFF_C_C_TERM,	DAA_SCORE_RANK_DIFF_C_Gap,	DAA_SCORE_RANK_DIFF_C_Xle,	DAA_SCORE_RANK_DIFF_C_Ala,
	DAA_SCORE_RANK_DIFF_C_Arg,	DAA_SCORE_RANK_DIFF_C_Asn,	DAA_SCORE_RANK_DIFF_C_Asp,	DAA_SCORE_RANK_DIFF_C_Cys,	DAA_SCORE_RANK_DIFF_C_Gln,
	DAA_SCORE_RANK_DIFF_C_Glu,	DAA_SCORE_RANK_DIFF_C_Gly,	DAA_SCORE_RANK_DIFF_C_His,	DAA_SCORE_RANK_DIFF_C_Ile,	DAA_SCORE_RANK_DIFF_C_Leu,
	DAA_SCORE_RANK_DIFF_C_Lys,	DAA_SCORE_RANK_DIFF_C_Met,	DAA_SCORE_RANK_DIFF_C_Phe,	DAA_SCORE_RANK_DIFF_C_Pro,	DAA_SCORE_RANK_DIFF_C_Ser,
	DAA_SCORE_RANK_DIFF_C_Thr,	DAA_SCORE_RANK_DIFF_C_Trp,	DAA_SCORE_RANK_DIFF_C_Tyr,	DAA_SCORE_RANK_DIFF_C_Val,

	DAA_NUM_FIELDS
} ScoreModelFields_DAA;


typedef enum ScoreModelFields_DAANCD { 
	DAANCD_CONST,

	DAANCD_IND_SEQ_RANK_1,  DAANCD_IND_SEQ_RANK_2, DAANCD_IND_SEQ_RANK_3, DAANCD_IND_SEQ_RANK_4, DAANCD_IND_SEQ_RANK_5,
	DAANCD_IND_SEQ_RANK_6,  DAANCD_IND_SEQ_RANK_8, DAANCD_IND_SEQ_RANK_10, DAANCD_IND_SEQ_RANK_12, DAANCD_IND_SEQ_RANK_14,
	DAANCD_IND_SEQ_RANK_16,  DAANCD_IND_SEQ_RANK_20, DAANCD_IND_SEQ_RANK_MORE,

	DAANCD_IND_CONNECTS_TO_NODE_WITH_NO_FRAGS,
	DAANCD_IND_CONNECTS_TO_N_TERMINAL,
	DAANCD_IND_CONNECTS_TO_C_TERMINAL,
	DAANCD_IND_CONNECTS_TO_DIGEST,

	DAANCD_IND_HAS_MAX_SCORE_FROM_N,  	DAANCD_SCORE_FROM_N,
	DAANCD_IND_HAS_MAX_SCORE_TO_C,      DAANCD_SCORE_TO_C,
	DAANCD_IND_HAS_MAX_SCORE_TO_DIGEST, DAANCD_SCORE_TO_DIGEST,

	DAANCD_NODE_MASS_DIFF_FROM_N,     DAANCD_NODE_SQR_MASS_DIFF_FROM_N,
	DAANCD_NODE_MASS_DIFF_TO_C,     DAANCD_NODE_SQR_MASS_DIFF_TO_C,
	DAANCD_NODE_MASS_DIFF_TO_DIGEST,     DAANCD_NODE_SQR_MASS_DIFF_TO_DIGEST,

	DAANCD_NUM_DOUBLE_EDGE_ROUTES, 
	DAANCD_IND_NO_DOUBLE_EDGE_ROUTES,
	DAANCD_SCORE_RANK_DOUBLE_EDGE_ROUTES,
	DAANCD_IND_IND_MAX_SCORE_ALTERNATE_MORE_THAN_ZERO,
	DAANCD_IND_MAX_ALTERNATE_IS_MAX_OUT_N,
	DAANCD_IND_MAX_ALTERNATE_IS_MAX_IN_C,
	DAANCD_NODE_OFFSETS_ALTERNTE,
	DAANCD_SQR_NODE_ODFFSETS_ALTERNATE,

	DAANCD_IND_DIGEST_AA_IS_GOOD,

	// for N-terminal pairs
	DAANCD_IND_NT_N_AA_N_TERM,	DAANCD_IND_NT_N_AA_C_TERM,	DAANCD_IND_NT_N_AA_Gap,	DAANCD_IND_NT_N_AA_Xle,	DAANCD_IND_NT_N_AA_Ala,
	DAANCD_IND_NT_N_AA_Arg,		DAANCD_IND_NT_N_AA_Asn,		DAANCD_IND_NT_N_AA_Asp,	DAANCD_IND_NT_N_AA_Cys,	DAANCD_IND_NT_N_AA_Gln,
	DAANCD_IND_NT_N_AA_Glu,		DAANCD_IND_NT_N_AA_Gly,		DAANCD_IND_NT_N_AA_His,	DAANCD_IND_NT_N_AA_Ile,	DAANCD_IND_NT_N_AA_Leu,
	DAANCD_IND_NT_N_AA_Lys,		DAANCD_IND_NT_N_AA_Met,		DAANCD_IND_NT_N_AA_Phe,	DAANCD_IND_NT_N_AA_Pro,	DAANCD_IND_NT_N_AA_Ser,
	DAANCD_IND_NT_N_AA_Thr,		DAANCD_IND_NT_N_AA_Trp,		DAANCD_IND_NT_N_AA_Tyr,	DAANCD_IND_NT_N_AA_Val,

	DAANCD_IND_NT_C_AA_N_TERM,	DAANCD_IND_NT_C_AA_C_TERM,	DAANCD_IND_NT_C_AA_Gap,	DAANCD_IND_NT_C_AA_Xle,	DAANCD_IND_NT_C_AA_Ala,
	DAANCD_IND_NT_C_AA_Arg,		DAANCD_IND_NT_C_AA_Asn,		DAANCD_IND_NT_C_AA_Asp,	DAANCD_IND_NT_C_AA_Cys,	DAANCD_IND_NT_C_AA_Gln,
	DAANCD_IND_NT_C_AA_Glu,		DAANCD_IND_NT_C_AA_Gly,		DAANCD_IND_NT_C_AA_His,	DAANCD_IND_NT_C_AA_Ile,	DAANCD_IND_NT_C_AA_Leu,
	DAANCD_IND_NT_C_AA_Lys,		DAANCD_IND_NT_C_AA_Met,		DAANCD_IND_NT_C_AA_Phe,	DAANCD_IND_NT_C_AA_Pro,	DAANCD_IND_NT_C_AA_Ser,
	DAANCD_IND_NT_C_AA_Thr,		DAANCD_IND_NT_C_AA_Trp,		DAANCD_IND_NT_C_AA_Tyr,	DAANCD_IND_NT_C_AA_Val,

	DAANCD_NUM_FIELDS
} ScoreModelFields_DAANCD;


typedef enum AAProbTypes { AAP_SAA, AAP_SAANCD, AAP_DAA, AAP_DAANCD, AAP_NUM_TYPES } AAProbTypes;


class AminoAcidProbs {
public:

	AminoAcidProbs() : ind_model_was_initialized(false) {};

	bool read_model(const Config *config, char *model_name);

	float calc_variant_prob(const void *prm_ptr, int me_idx, int* variant_ptr, int seq_rank = 5) const;

	bool get_ind_initialized() const { return ind_model_was_initialized; }

//	void train_amino_acid_prob_models(const FileManager& fm, void *model, 
//									  int specific_charge=-1, int specific_size_idx=-1);

	void read_amino_acid_prob_models(Config *config, char *file_name);

	void write_amino_acid_prob_models(const char *path) const;

private:
	
	bool ind_model_was_initialized;

	// models divided according to charge/size_idx/AAEdgeTypes same model handles all amino acids
	vector< vector< vector<ME_Regression_Model *> > > aa_prob_me_models;  

	int  get_edge_type(const void* prm_void_ptr, int me_idx) const;

	void fill_aa_prob_fval_vector(int type,
						  const void* prm_void_ptr, 
						  const int me_idx, 
						  const int* variant_ptr, 
						  const int  seq_rank,
						  ME_Regression_Sample& sam) const;

};





#endif

