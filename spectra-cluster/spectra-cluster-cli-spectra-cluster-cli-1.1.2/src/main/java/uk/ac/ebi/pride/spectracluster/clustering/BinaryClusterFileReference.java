package uk.ac.ebi.pride.spectracluster.clustering;

import java.io.File;

/**
 * This class holds basic information about
 * a clustering result file
 *
 * Created by jg on 13.03.16.
 */
public class BinaryClusterFileReference implements Comparable<BinaryClusterFileReference> {
    /**
     * The actual binary result file
     */
    private final File resultFile;
    /**
     * Lowest precursor m/z found in the file
     */
    private final double minMz;
    /**
     * Maxixmum precursor m/z found in the file
     */
    private final double maxMz;
    /**
     * Number of spectra in the file
     */
    private final int nSpectra;

    public BinaryClusterFileReference(File resultFile, double minMz, double maxMz, int nSpectra) {
        this.resultFile = resultFile;
        this.minMz = minMz;
        this.maxMz = maxMz;
        this.nSpectra = nSpectra;
    }

    public File getResultFile() {
        return resultFile;
    }

    public double getMinMz() {
        return minMz;
    }

    public double getMaxMz() {
        return maxMz;
    }

    public int getnSpectra() {
        return nSpectra;
    }

    @Override
    /**
     * Naturally sorts according to min m/z
     */
    public int compareTo(BinaryClusterFileReference o) {
        return Double.compare(getMinMz(), o.getMinMz());
    }
}
