PXD=PXD001511
#PXD_PATH=PXD001197
RUN=1
out_file=profiling_${PXD}_${RUN}.log

lscpu > $out_file
free -h >> -a $out_file 


# python3 -m cProfile -s time ./falcon_profiling.py test_spectra/*.mzML test_results --export_representatives --precursor_tol 20 ppm --fragment_tol 0.05 --eps 0.10

#python ./falcon_profiling.py test_spectra/*.mzML test_results --export_representatives --precursor_tol 20 ppm --fragment_tol 0.05 --eps 0.10

#python ./falcon_profiling.py ~/bio/ms-dataset/PXD001197/OrbiElite*.mgf ./clusters_PXD001197 --export_representatives --precursor_tol 20 ppm --fragment_tol 0.05 --eps 0.10

python ./falcon_profiling.py ~/bio/ms-dataset/${PXD}/*.mgf ./clusters_${PXD} --export_representatives --precursor_tol 20 ppm --fragment_tol 0.05 --eps 0.10 | tee $out_file

