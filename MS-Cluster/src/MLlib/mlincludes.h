#ifndef __MLINCLUDES_H__
#define __MLINCLUDES_H__

#include "../Common/includes.h"

typedef enum SCORE_MODEL_TYPES { SMT_LOGISTIC_CG, 
								 SMT_LOGISTIC_LMBFGS,
								 SMT_MAXIMUM_ENTROPY_LMBFGS,
								 SMT_MAXIMUM_ENTROPY_CG_FR,
								 SMT_MAXIMUM_ENTROPY_CG_PR,
								 SMT_RANKBOOST_ADA,
								 SMT_RANKBOOST_LOGIT,
								 SMT_RANKBOOST_SMOOTH,
								 SMT_NUM_SCORE_MODEL_TYPES } SCORE_MODEL_TYPES;

const char * const SCORE_MODEL_NAMES[SMT_NUM_SCORE_MODEL_TYPES] = {
	"LOGISTIC_CG", "LOGISTIC_BFGS", "MAXENT_LMBFGS", "MAXENT_CG_FR", "MAXENT_CG_PR", "RANKBOOST_ADA",
	"RANKBOOST_LOGIT", "RANKBOOST_SMOOTH"};

typedef enum FEATURE_datasetIdx_TYPES { FGT_REGRESSION, FGT_RANKING } FEATURE_datasetIdx_TYPES;



#endif

