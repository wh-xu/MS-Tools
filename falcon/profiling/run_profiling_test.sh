# python3 -m cProfile -s time ./falcon_profiling.py test_spectra/*.mzML test_results --export_representatives --precursor_tol 20 ppm --fragment_tol 0.05 --eps 0.10

#python ./falcon_profiling.py test_spectra/*.mzML test_results --export_representatives --precursor_tol 20 ppm --fragment_tol 0.05 --eps 0.10

python ./falcon_profiling.py ~/bio/ms-dataset/PXD001197/OrbiElite045*.mgf ./clusters_PXD001197 --export_representatives --precursor_tol 20 ppm --fragment_tol 0.05 --eps 0.10

