#ifndef __REGULARFRAGMENTMODEL_H__
#define __REGULARFRAGMENTMODEL_H__

#include "FragmentModel.h"

// a regular fragment with intensity
typedef enum ScoreModelFields_RI {
	RI_CONST,                          

	RI_LOG_LOCAL_RANK,		RI_LOG_GLOBAL_RANK,		RI_ISO_LEVEL,
	
	RI_IND_LOG_INTEN_LESS1,  RI_LOG_INTEN_LESS1,
	RI_IND_LOG_INTEN_LESS2,  RI_LOG_INTEN_LESS2,
	RI_IND_LOG_INTEN_LESS3,  RI_LOG_INTEN_LESS3,
	RI_IND_LOG_INTEN_LESS4,  RI_LOG_INTEN_LESS4,
	RI_IND_LOG_INTEN_MORE,   RI_LOG_INTEN_MORE,

	RI_IND_DIS_FROM_MINMAX_LESS_50,		RI_DIS_FROM_MINMAX0,	RI_LOG_INTEN_DIS50,
	RI_IND_DIS_FROM_MINMAX_LESS_150,	RI_DIS_FROM_MINMAX50,	RI_LOG_INTEN_DIS150,
	RI_IND_DIS_FROM_MINMAX_LESS_250,	RI_DIS_FROM_MINMAX150,	RI_LOG_INTEN_DIS250,
	RI_IND_DIS_FROM_MINMAX_MORE,		RI_DIS_FROM_MINMAX250,	RI_LOG_INTEN_DISMORE,

	RI_REL_POS0, RI_REL_POS1, RI_REL_POS2, RI_REL_POS3, RI_REL_POS4,
	RI_REL_POS5, RI_REL_POS6, RI_REL_POS7, RI_REL_POS8, RI_REL_POS9,

	RI_IND_NUM_PARENTS_WITH_INTEN_IS_0,	RI_IND_NUM_PARENTS_WITH_INTEN_IS_1,
	RI_IND_NUM_PARENTS_WITH_INTEN_IS_2,	RI_IND_NUM_PARENTS_WITH_INTEN_IS_3,
	RI_IND_NUM_PARENTS_WITH_INTEN_IS_4,	RI_IND_NUM_PARENTS_WITH_INTEN_IS_5,
	RI_IND_NUM_PARENTS_WITH_INTEN_IS_6,	RI_IND_NUM_PARENTS_WITH_INTEN_IS_MORE6,

	// exact combo for top 4 parents (if not viz, assume frag is present)
	RI_IND_PARENT_COMBO_0,	RI_IND_PARENT_COMBO_1, RI_IND_PARENT_COMBO_2, RI_IND_PARENT_COMBO_3,
	RI_IND_PARENT_COMBO_4,	RI_IND_PARENT_COMBO_5, RI_IND_PARENT_COMBO_6, RI_IND_PARENT_COMBO_7,
	RI_IND_PARENT_COMBO_8,	RI_IND_PARENT_COMBO_9, RI_IND_PARENT_COMBO_10, RI_IND_PARENT_COMBO_11,
	RI_IND_PARENT_COMBO_12,	RI_IND_PARENT_COMBO_13, RI_IND_PARENT_COMBO_14, RI_IND_PARENT_COMBO_15,

	RI_IND_GOT_BOTH_ORIS,	   RI_IND_GOT_PREFIX,	   RI_IND_GOT_SUFFIX,

	RI_IND_PARENT1_NOT_VIZ,	   RI_IND_PARENT1_NO_INTEN,	RI_PARENT1_ISO_LEVEL,
	RI_IND_PARENT1_INTEN_MORE, RI_PARENT1_INTEN_DIFF_MORE,
	RI_IND_PARENT1_INTEN_LESS, RI_PARENT1_INTEN_DIFF_LESS,

	RI_IND_PARENT2_NOT_VIZ,	   RI_IND_PARENT2_NO_INTEN,	RI_PARENT2_ISO_LEVEL,
	RI_IND_PARENT2_INTEN_MORE, RI_PARENT2_INTEN_DIFF_MORE,
	RI_IND_PARENT2_INTEN_LESS, RI_PARENT2_INTEN_DIFF_LESS,

	RI_IND_PARENT3_NOT_VIZ,	   RI_IND_PARENT3_NO_INTEN,	RI_PARENT3_ISO_LEVEL,
	RI_IND_PARENT3_INTEN_MORE, RI_PARENT3_INTEN_DIFF_MORE,
	RI_IND_PARENT3_INTEN_LESS, RI_PARENT3_INTEN_DIFF_LESS,

	RI_IND_PARENT4_NOT_VIZ,	   RI_IND_PARENT4_NO_INTEN, RI_PARENT4_ISO_LEVEL,	
	RI_IND_PARENT4_INTEN_MORE, RI_PARENT4_INTEN_DIFF_MORE,
	RI_IND_PARENT4_INTEN_LESS, RI_PARENT4_INTEN_DIFF_LESS,

	RI_IND_PARENT5_NOT_VIZ,	   RI_IND_PARENT5_NO_INTEN,	RI_PARENT5_ISO_LEVEL,
	RI_IND_PARENT5_INTEN_MORE, RI_PARENT5_INTEN_DIFF_MORE,
	RI_IND_PARENT5_INTEN_LESS, RI_PARENT5_INTEN_DIFF_LESS,

	RI_IND_PARENT6_NOT_VIZ,	   RI_IND_PARENT6_NO_INTEN,	RI_PARENT6_ISO_LEVEL,
	RI_IND_PARENT6_INTEN_MORE, RI_PARENT6_INTEN_DIFF_MORE,
	RI_IND_PARENT6_INTEN_LESS, RI_PARENT6_INTEN_DIFF_LESS,

	RI_IND_PARENT7_NOT_VIZ,	   RI_IND_PARENT7_NO_INTEN,	RI_PARENT7_ISO_LEVEL,
	RI_IND_PARENT7_INTEN_MORE, RI_PARENT7_INTEN_DIFF_MORE,
	RI_IND_PARENT7_INTEN_LESS, RI_PARENT7_INTEN_DIFF_LESS,

	RI_IND_PARENT8_NOT_VIZ,	   RI_IND_PARENT8_NO_INTEN,	RI_PARENT8_ISO_LEVEL,
	RI_IND_PARENT8_INTEN_MORE, RI_PARENT8_INTEN_DIFF_MORE,
	RI_IND_PARENT8_INTEN_LESS, RI_PARENT8_INTEN_DIFF_LESS,

	// variable aa features
	RI_IND_N_IS_GAP,	RI_IND_C_IS_GAP,

	RI_IND_N_HAS_N_TERM, RI_IND_N_HAS_C_TERM, RI_IND_N_HAS_Gap, RI_IND_N_HAS_Xle, RI_IND_N_HAS_Ala, RI_IND_N_HAS_Arg, RI_IND_N_HAS_Asn,
	RI_IND_N_HAS_Asp,    RI_IND_N_HAS_Cys,    RI_IND_N_HAS_Gln, RI_IND_N_HAS_Glu, RI_IND_N_HAS_Gly, RI_IND_N_HAS_His, RI_IND_N_HAS_Ile,
	RI_IND_N_HAS_Leu,    RI_IND_N_HAS_Lys,    RI_IND_N_HAS_Met, RI_IND_N_HAS_Phe, RI_IND_N_HAS_Pro, RI_IND_N_HAS_Ser, RI_IND_N_HAS_Thr,
	RI_IND_N_HAS_Trp,    RI_IND_N_HAS_Tyr,    RI_IND_N_HAS_Val,

	RI_N_N_TERM_SELF_INTEN, RI_N_C_TERM_SELF_INTEN, RI_N_Gap_SELF_INTEN, RI_N_Xle_SELF_INTEN, RI_N_Ala_SELF_INTEN, RI_N_Arg_SELF_INTEN, RI_N_Asn_SELF_INTEN,
	RI_N_Asp_SELF_INTEN,    RI_N_Cys_SELF_INTEN,    RI_N_Gln_SELF_INTEN, RI_N_Glu_SELF_INTEN, RI_N_Gly_SELF_INTEN, RI_N_His_SELF_INTEN, RI_N_Ile_SELF_INTEN,
	RI_N_Leu_SELF_INTEN,    RI_N_Lys_SELF_INTEN,    RI_N_Met_SELF_INTEN, RI_N_Phe_SELF_INTEN, RI_N_Pro_SELF_INTEN, RI_N_Ser_SELF_INTEN, RI_N_Thr_SELF_INTEN,
	RI_N_Trp_SELF_INTEN,    RI_N_Tyr_SELF_INTEN,    RI_N_Val_SELF_INTEN,

	RI_IND_C_HAS_N_TERM, RI_IND_C_HAS_C_TERM, RI_IND_C_HAS_Gap, RI_IND_C_HAS_Xle, RI_IND_C_HAS_Ala, RI_IND_C_HAS_Arg, RI_IND_C_HAS_Asn,
	RI_IND_C_HAS_Asp,    RI_IND_C_HAS_Cys,    RI_IND_C_HAS_Gln, RI_IND_C_HAS_Glu, RI_IND_C_HAS_Gly, RI_IND_C_HAS_His, RI_IND_C_HAS_Ile,
	RI_IND_C_HAS_Leu,    RI_IND_C_HAS_Lys,    RI_IND_C_HAS_Met, RI_IND_C_HAS_Phe, RI_IND_C_HAS_Pro, RI_IND_C_HAS_Ser, RI_IND_C_HAS_Thr,
	RI_IND_C_HAS_Trp,    RI_IND_C_HAS_Tyr,    RI_IND_C_HAS_Val,

	RI_C_N_TERM_SELF_INTEN, RI_C_C_TERM_SELF_INTEN, RI_C_Gap_SELF_INTEN, RI_C_Xle_SELF_INTEN, RI_C_Ala_SELF_INTEN, RI_C_Arg_SELF_INTEN, RI_C_Asn_SELF_INTEN,
	RI_C_Asp_SELF_INTEN,    RI_C_Cys_SELF_INTEN,    RI_C_Gln_SELF_INTEN, RI_C_Glu_SELF_INTEN, RI_C_Gly_SELF_INTEN, RI_C_His_SELF_INTEN, RI_C_Ile_SELF_INTEN,
	RI_C_Leu_SELF_INTEN,    RI_C_Lys_SELF_INTEN,    RI_C_Met_SELF_INTEN, RI_C_Phe_SELF_INTEN, RI_C_Pro_SELF_INTEN, RI_C_Ser_SELF_INTEN, RI_C_Thr_SELF_INTEN,
	RI_C_Trp_SELF_INTEN,    RI_C_Tyr_SELF_INTEN,    RI_C_Val_SELF_INTEN,

	RI_NUM_FEATURES

} ScoreModelFields_RI;



typedef enum ScoreModelFields_RNI {
	RNI_CONST,                          

	RNI_IND_DIS_FROM_MINMAX_LESS_50,	RNI_DIS_FROM_MINMAX0,
	RNI_IND_DIS_FROM_MINMAX_LESS_150,	RNI_DIS_FROM_MINMAX50,
	RNI_IND_DIS_FROM_MINMAX_LESS_250,	RNI_DIS_FROM_MINMAX150,
	RNI_IND_DIS_FROM_MINMAX_MORE,		RNI_DIS_FROM_MINMAX250,

	RNI_REL_POS0, RNI_REL_POS1, RNI_REL_POS2, RNI_REL_POS3, RNI_REL_POS4,
	RNI_REL_POS5, RNI_REL_POS6, RNI_REL_POS7, RNI_REL_POS8, RNI_REL_POS9,

	RNI_IND_NUM_PARENTS_WITH_INTEN_IS_0,	RNI_IND_NUM_PARENTS_WITH_INTEN_IS_1,
	RNI_IND_NUM_PARENTS_WITH_INTEN_IS_2,	RNI_IND_NUM_PARENTS_WITH_INTEN_IS_3,
	RNI_IND_NUM_PARENTS_WITH_INTEN_IS_4,	RNI_IND_NUM_PARENTS_WITH_INTEN_IS_5,
	RNI_IND_NUM_PARENTS_WITH_INTEN_IS_6,	RNI_IND_NUM_PARENTS_WITH_INTEN_IS_MORE6,

	// exact combo for top 4 parents (if not viz, assume frag is present)
	RNI_IND_PARENT_COMBO_0,	RNI_IND_PARENT_COMBO_1, RNI_IND_PARENT_COMBO_2, RNI_IND_PARENT_COMBO_3,
	RNI_IND_PARENT_COMBO_4,	RNI_IND_PARENT_COMBO_5, RNI_IND_PARENT_COMBO_6, RNI_IND_PARENT_COMBO_7,
	RNI_IND_PARENT_COMBO_8,	RNI_IND_PARENT_COMBO_9, RNI_IND_PARENT_COMBO_10, RNI_IND_PARENT_COMBO_11,
	RNI_IND_PARENT_COMBO_12, RNI_IND_PARENT_COMBO_13, RNI_IND_PARENT_COMBO_14, RNI_IND_PARENT_COMBO_15,

	RNI_IND_GOT_BOTH_ORIS,	   RNI_IND_GOT_PREFIX,	   RNI_IND_GOT_SUFFIX,

	RNI_IND_PARENT1_NOT_VIZ, RNI_IND_PARENT1_NO_INTEN, RNI_PARENT1_LOG_INTEN, RNI_PARENT1_LOG_GLOBAL_RANK, RNI_PARENT1_ISO_LEVEL,	
	RNI_IND_PARENT2_NOT_VIZ, RNI_IND_PARENT2_NO_INTEN, RNI_PARENT2_LOG_INTEN, RNI_PARENT2_LOG_GLOBAL_RANK, RNI_PARENT2_ISO_LEVEL,
	RNI_IND_PARENT3_NOT_VIZ, RNI_IND_PARENT3_NO_INTEN, RNI_PARENT3_LOG_INTEN, RNI_PARENT3_LOG_GLOBAL_RANK, RNI_PARENT3_ISO_LEVEL,
	RNI_IND_PARENT4_NOT_VIZ, RNI_IND_PARENT4_NO_INTEN, RNI_PARENT4_LOG_INTEN, RNI_PARENT4_LOG_GLOBAL_RANK, RNI_PARENT4_ISO_LEVEL,
	RNI_IND_PARENT5_NOT_VIZ, RNI_IND_PARENT5_NO_INTEN, RNI_PARENT5_LOG_INTEN, RNI_PARENT5_LOG_GLOBAL_RANK, RNI_PARENT5_ISO_LEVEL,
	RNI_IND_PARENT6_NOT_VIZ, RNI_IND_PARENT6_NO_INTEN, RNI_PARENT6_LOG_INTEN, RNI_PARENT6_LOG_GLOBAL_RANK, RNI_PARENT6_ISO_LEVEL,
	RNI_IND_PARENT7_NOT_VIZ, RNI_IND_PARENT7_NO_INTEN, RNI_PARENT7_LOG_INTEN, RNI_PARENT7_LOG_GLOBAL_RANK, RNI_PARENT7_ISO_LEVEL,
	RNI_IND_PARENT8_NOT_VIZ, RNI_IND_PARENT8_NO_INTEN, RNI_PARENT8_LOG_INTEN, RNI_PARENT8_LOG_GLOBAL_RANK, RNI_PARENT8_ISO_LEVEL,

	// variable aa features
	RNI_IND_N_IS_GAP,	RNI_IND_C_IS_GAP,

	RNI_IND_N_HAS_N_TERM, RNI_IND_N_HAS_C_TERM, RNI_IND_N_HAS_Gap, RNI_IND_N_HAS_Xle, RNI_IND_N_HAS_Ala, RNI_IND_N_HAS_Arg, RNI_IND_N_HAS_Asn,
	RNI_IND_N_HAS_Asp,    RNI_IND_N_HAS_Cys,    RNI_IND_N_HAS_Gln, RNI_IND_N_HAS_Glu, RNI_IND_N_HAS_Gly, RNI_IND_N_HAS_His, RNI_IND_N_HAS_Ile,
	RNI_IND_N_HAS_Leu,    RNI_IND_N_HAS_Lys,    RNI_IND_N_HAS_Met, RNI_IND_N_HAS_Phe, RNI_IND_N_HAS_Pro, RNI_IND_N_HAS_Ser, RNI_IND_N_HAS_Thr,
	RNI_IND_N_HAS_Trp,    RNI_IND_N_HAS_Tyr,    RNI_IND_N_HAS_Val,

	RNI_IND_C_HAS_N_TERM, RNI_IND_C_HAS_C_TERM, RNI_IND_C_HAS_Gap, RNI_IND_C_HAS_Xle, RNI_IND_C_HAS_Ala, RNI_IND_C_HAS_Arg, RNI_IND_C_HAS_Asn,
	RNI_IND_C_HAS_Asp,    RNI_IND_C_HAS_Cys,    RNI_IND_C_HAS_Gln, RNI_IND_C_HAS_Glu, RNI_IND_C_HAS_Gly, RNI_IND_C_HAS_His, RNI_IND_C_HAS_Ile,
	RNI_IND_C_HAS_Leu,    RNI_IND_C_HAS_Lys,    RNI_IND_C_HAS_Met, RNI_IND_C_HAS_Phe, RNI_IND_C_HAS_Pro, RNI_IND_C_HAS_Ser, RNI_IND_C_HAS_Thr,
	RNI_IND_C_HAS_Trp,    RNI_IND_C_HAS_Tyr,    RNI_IND_C_HAS_Val,


	RNI_NUM_FEATURES

} ScoreModelFields_RNI;




/************************************************************************
Model for fragments not designated "strong" in the regional fragments.
*************************************************************************/
class RegularFragmentModel : public FragmentModel  {
	friend class RegionalPrmNodeScoreModel;
public:

	RegularFragmentModel() : num_parents(0), parent_idx_with_same_charge_ori(-1) {}

	void fill_combo_vectors(Spectrum *spec, 
							mass_t pm_with_19,  
							const Breakage *breakage,
							const vector<BreakageInfo>& infos,
							vector< ME_Regression_Sample > & samples) const;

	void fill_single_frag_vector(Spectrum *spec, 
							mass_t pm_with_19,  
							const Breakage *breakage,
							BreakageInfo& info,
							vector< fval >& f_vals) const;




	bool read_model(const Config *config, istream& is, bool silent_ind);

	bool write_model (ostream& os) const;

	int get_model_frag_idx() const { return model_frag_idx; }

protected:

	
	int num_parents;
	int parent_idx_with_same_charge_ori;

	vector<int> parent_idxs;


	

	void fill_constant_vals(Spectrum *spec, 
							mass_t pm_with_19,  
							const Breakage *breakage, 
							vector<fval>& f_vals) const;

	void fill_aa_variable_vals( Spectrum *spec, 
							   mass_t pm_with_19,  
							   const Breakage *breakage,
							   const BreakageInfo* info,
							   vector<fval>& f_vals) const;


};


#endif

