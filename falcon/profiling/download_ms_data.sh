if [ ! -d "test_spectra" ]; then
    mkdir -p test_spectra && cd test_spectra && \
    wget -O Adult_CD4Tcells_bRP_Elite_28_f14.mzML "https://gnps-external.ucsd.edu/massiveftpproxy?ftppath=ftp://massive.ucsd.edu/MSV000079514/ccms_peak/CD4 Tcells/LTQ-Orbitrap Elite/28/Adult_CD4Tcells_bRP_Elite_28_f14.mzML" && \
    wget -O Adult_CD4Tcells_bRP_Elite_28_f15.mzML "https://gnps-external.ucsd.edu/massiveftpproxy?ftppath=ftp://massive.ucsd.edu/MSV000079514/ccms_peak/CD4 Tcells/LTQ-Orbitrap Elite/28/Adult_CD4Tcells_bRP_Elite_28_f15.mzML"
    wget -O Adult_CD4Tcells_bRP_Elite_28_f16.mzML "https://gnps-external.ucsd.edu/massiveftpproxy?ftppath=ftp://massive.ucsd.edu/MSV000079514/ccms_peak/CD4 Tcells/LTQ-Orbitrap Elite/28/Adult_CD4Tcells_bRP_Elite_28_f16.mzML"
fi
