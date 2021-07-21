package uk.ac.ebi.pride.spectracluster.cli;

import org.apache.commons.cli.CommandLine;
import org.apache.commons.cli.CommandLineParser;
import org.apache.commons.cli.GnuParser;
import org.apache.commons.cli.HelpFormatter;
import uk.ac.ebi.pride.spectracluster.cdf.*;
import uk.ac.ebi.pride.spectracluster.implementation.ClusteringSettings;
import uk.ac.ebi.pride.spectracluster.implementation.ScoreCalculator;
import uk.ac.ebi.pride.spectracluster.implementation.SpectraClusterStandalone;
import uk.ac.ebi.pride.spectracluster.util.Defaults;
import uk.ac.ebi.pride.spectracluster.util.IProgressListener;
import uk.ac.ebi.pride.spectracluster.util.MissingParameterException;
import uk.ac.ebi.pride.spectracluster.util.ProgressUpdate;
import uk.ac.ebi.pride.spectracluster.util.function.peak.BinnedHighestNPeakFunction;
import uk.ac.ebi.pride.spectracluster.util.function.peak.HighestNPeakFunction;
import uk.ac.ebi.pride.spectracluster.util.function.spectrum.RemoveReporterIonPeaksFunction;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.security.InvalidParameterException;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

/**
 * Created with IntelliJ IDEA.
 * User: jg
 * Date: 9/15/13
 * Time: 11:19 AM
 * To change this template use File | Settings | File Templates.
 */
public class SpectraClusterCliMain implements IProgressListener {
    public static final boolean DELETE_TEMPORARY_CLUSTERING_RESULTS = true;

    private boolean verbose;

    public static void main(String[] args) {
        SpectraClusterCliMain instance = new SpectraClusterCliMain();
        instance.run(args);
    }

    private void run(String[] args) {
        CommandLineParser parser = new GnuParser();

        try {
            CommandLine commandLine = parser.parse(CliOptions.getOptions(), args);

            // HELP
            if (commandLine.hasOption(CliOptions.OPTIONS.HELP.getValue())) {
                printUsage();
                return;
            }

            // create the clustering standalone object
            SpectraClusterStandalone spectraClusterStandalone = new SpectraClusterStandalone();

            // RESULT FILE PATH
            if (!commandLine.hasOption(CliOptions.OPTIONS.OUTPUT_PATH.getValue()))
                throw new MissingParameterException("Missing required option " + CliOptions.OPTIONS.OUTPUT_PATH.getValue());
            File finalResultFile = new File(commandLine.getOptionValue(CliOptions.OPTIONS.OUTPUT_PATH.getValue()));

            if (finalResultFile.exists())
                throw new Exception("Result file " + finalResultFile + " already exists");

            // NUMBER OF JOBS
            int paralellJobs = 4;
            if (commandLine.hasOption(CliOptions.OPTIONS.MAJOR_PEAK_JOBS.getValue())) {
                paralellJobs = Integer.parseInt(commandLine.getOptionValue(CliOptions.OPTIONS.MAJOR_PEAK_JOBS.getValue()));
                spectraClusterStandalone.setParallelJobs(paralellJobs);
            }

            // NUMBER OF ROUNDS
            int rounds = 5;
            if (commandLine.hasOption(CliOptions.OPTIONS.ROUNDS.getValue()))
                rounds = Integer.parseInt(commandLine.getOptionValue(CliOptions.OPTIONS.ROUNDS.getValue()));

            // START THRESHOLD
            float startThreshold = 1F;
            if (commandLine.hasOption(CliOptions.OPTIONS.START_THRESHOLD.getValue()))
                startThreshold = Float.parseFloat(commandLine.getOptionValue(CliOptions.OPTIONS.START_THRESHOLD.getValue()));

            // END THRESHOLD
            float endThreshold = 0.99F;
            if (commandLine.hasOption(CliOptions.OPTIONS.END_THRESHOLD.getValue()))
                endThreshold = Float.parseFloat(commandLine.getOptionValue(CliOptions.OPTIONS.END_THRESHOLD.getValue()));

            List<Float> thresholds = spectraClusterStandalone.generateClusteringThresholds(startThreshold, endThreshold, rounds);

            // PRECURSOR TOLERANCE
            if (commandLine.hasOption(CliOptions.OPTIONS.PRECURSOR_TOLERANCE.getValue())) {
                float precursorTolerance = Float.parseFloat(commandLine.getOptionValue(CliOptions.OPTIONS.PRECURSOR_TOLERANCE.getValue()));
                Defaults.setDefaultPrecursorIonTolerance(precursorTolerance);
            }

            // PRECURSOR TOLERANCE UNIT
            if (commandLine.hasOption(CliOptions.OPTIONS.PRECURSOR_TOELRANCE_UNIT.getValue())) {
                String unit = commandLine.getOptionValue(CliOptions.OPTIONS.PRECURSOR_TOELRANCE_UNIT.getValue()).toLowerCase();

                if ("ppm".equals(unit)) {
                    // adapt the precursor tolerance
                    float userTolerance = Defaults.getDefaultPrecursorIonTolerance();
                    float ppmFraction = userTolerance / 1000000;

                    // set the "precursor" tolerance based on a high m/z
                    Defaults.setDefaultPrecursorIonTolerance(ppmFraction * 3500);

                    // set the actual ppm tolerance
                    ClusteringSettings.ppmThreshold = userTolerance;
                }
            }

            // FRAGMENT ION TOLERANCE
            if (commandLine.hasOption(CliOptions.OPTIONS.FRAGMENT_TOLERANCE.getValue())) {
                float fragmentTolerance = Float.parseFloat(commandLine.getOptionValue(CliOptions.OPTIONS.FRAGMENT_TOLERANCE.getValue()));
                Defaults.setFragmentIonTolerance(fragmentTolerance);
            }

            // BINARY TMP DIR
            if (commandLine.hasOption(CliOptions.OPTIONS.BINARY_TMP_DIR.getValue())) {
                File binaryTmpDirectory = new File(commandLine.getOptionValue(CliOptions.OPTIONS.BINARY_TMP_DIR.getValue()));
                spectraClusterStandalone.setTemporaryDirectory(binaryTmpDirectory);
            }

            // KEEP BINARY FILES
            if (commandLine.hasOption(CliOptions.OPTIONS.KEEP_BINARY_FILE.getValue())) {
                spectraClusterStandalone.setKeepBinaryFiles(true);
            }

            // FAST MODE
            if (commandLine.hasOption(CliOptions.OPTIONS.FAST_MODE.getValue())) {
                spectraClusterStandalone.setUseFastMode(true);
            }

            // LOADING MODE
            if (commandLine.hasOption(CliOptions.OPTIONS.ONLY_IDENTIFIED.getValue()) && commandLine.hasOption(CliOptions.OPTIONS.ONLY_UNIDENTIFIED.getValue())) {
                throw new Exception(CliOptions.OPTIONS.ONLY_IDENTIFIED.getValue() + " and " + CliOptions.OPTIONS.ONLY_UNIDENTIFIED.getValue() +
                " cannot be used together");
            }
            if (commandLine.hasOption(CliOptions.OPTIONS.ONLY_IDENTIFIED.getValue())) {
                ClusteringSettings.setLoadingMode(ClusteringSettings.LOADING_MODE.ONLY_IDENTIFIED);
            }
            if (commandLine.hasOption(CliOptions.OPTIONS.ONLY_UNIDENTIFIED.getValue())) {
                ClusteringSettings.setLoadingMode(ClusteringSettings.LOADING_MODE.ONLY_UNIDENTIFIED);
            }

            // VERBOSE
            if (commandLine.hasOption(CliOptions.OPTIONS.VERBOSE.getValue())) {
                spectraClusterStandalone.setVerbose(true);
                Defaults.setSaveDebugInformation(true);
                Defaults.setSaveAddingScore(true);
            }

            // REMOVE QUANT PEAKS
            if (commandLine.hasOption(CliOptions.OPTIONS.REMOVE_REPORTER_PEAKS.getValue())) {
                String quantTypeString = commandLine.getOptionValue(CliOptions.OPTIONS.REMOVE_REPORTER_PEAKS.getValue());
                RemoveReporterIonPeaksFunction.REPORTER_TYPE reporterType;

                if (quantTypeString.toLowerCase().equals("itraq")) {
                    reporterType = RemoveReporterIonPeaksFunction.REPORTER_TYPE.ITRAQ;
                }
                else if (quantTypeString.toLowerCase().equals("tmt")) {
                    reporterType = RemoveReporterIonPeaksFunction.REPORTER_TYPE.TMT;
                }
                else if (quantTypeString.toLowerCase().equals("all")) {
                    reporterType = RemoveReporterIonPeaksFunction.REPORTER_TYPE.ALL;
                }
                else {
                    throw new MissingParameterException("Invalid reporter type defined. Valid values are " +
                            "'ITRAQ', 'TMT', and 'ALL'.");
                }

                spectraClusterStandalone.setReporterType(reporterType);
            }

            // FILES TO PROCESS
            String[] peaklistFilenames = commandLine.getArgs();

            // RE-USE BINARY FILES
            boolean reUseBinaryFiles = commandLine.hasOption(CliOptions.OPTIONS.REUSE_BINARY_FILES.getValue());

            // if re-use is set, binaryTmpDirectory is required and merging is impossible
            if (reUseBinaryFiles && !commandLine.hasOption(CliOptions.OPTIONS.BINARY_TMP_DIR.getValue()))
                throw new MissingParameterException("Missing required option '" + CliOptions.OPTIONS.BINARY_TMP_DIR.getValue() + "' with " + CliOptions.OPTIONS.REUSE_BINARY_FILES.getValue());

            if (reUseBinaryFiles && peaklistFilenames.length > 0)
                System.out.println("WARNING: " + CliOptions.OPTIONS.REUSE_BINARY_FILES.getValue() + " set, input files will be ignored");

            // make sure input files were set
            if (!reUseBinaryFiles && peaklistFilenames.length < 1)
                throw new MissingParameterException("No spectrum files passed. Please list the peak list files to process after the command.");

            // add the filters
            List<String> addedFilters = new ArrayList<String>();
            if (commandLine.hasOption(CliOptions.OPTIONS.FILTER.getValue())) {
                for (String filterName : commandLine.getOptionValues(CliOptions.OPTIONS.FILTER.getValue())) {
                    ClusteringSettings.SPECTRUM_FILTER filter = ClusteringSettings.SPECTRUM_FILTER.getFilterForName(filterName);

                    if (filter == null) {
                        throw new InvalidParameterException("Error: Unknown filter name passed: '" + filterName + "'");
                    }

                    ClusteringSettings.addIntitalSpectrumFilter(filter.filter);
                    addedFilters.add(filterName);
                }
            }

            /**
             * Advanced options
             */
            // MIN NUMBER COMPARISONS
            // By default, use the SpectraPerBinNumberComparisonAssessor
            // if the command line option is set, use the MinNumberComparisonAssessor instead.
            if (commandLine.hasOption(CliOptions.OPTIONS.ADVANCED_MIN_NUMBER_COMPARISONS.getValue())) {
                int minComparisons = Integer.parseInt(commandLine.getOptionValue(CliOptions.OPTIONS.ADVANCED_MIN_NUMBER_COMPARISONS.getValue()));
                Defaults.setNumberOfComparisonAssessor(new MinNumberComparisonsAssessor(minComparisons));
            }
            // adaptive version with a min number of spectra set
            else if (commandLine.hasOption(CliOptions.OPTIONS.ADVANCED_MIN_ADAPTIVE_COMPARISONS.getValue())) {
                int minComparisons = Integer.parseInt(commandLine.getOptionValue(CliOptions.OPTIONS.ADVANCED_MIN_ADAPTIVE_COMPARISONS.getValue()));
                Defaults.setNumberOfComparisonAssessor(new SpectraPerBinNumberComparisonAssessor(Defaults.getDefaultPrecursorIonTolerance(),
                        minComparisons));
            } else {
                Defaults.setNumberOfComparisonAssessor(new SpectraPerBinNumberComparisonAssessor(Defaults.getDefaultPrecursorIonTolerance()));
            }

            // N HIGHEST PEAKS
            if (commandLine.hasOption(CliOptions.OPTIONS.ADVANCED_NUMBER_PREFILTERED_PEAKS.getValue())) {
                int nHighestPeaks = Integer.parseInt(commandLine.getOptionValue(CliOptions.OPTIONS.ADVANCED_NUMBER_PREFILTERED_PEAKS.getValue()));
                ClusteringSettings.setLoadingSpectrumFilter(new HighestNPeakFunction(nHighestPeaks));
            }

            // FILTER PEAKS PER MZ
            if (commandLine.hasOption(CliOptions.OPTIONS.ADVANCED_FILTER_PEAKS_PER_MZ.getValue())) {
                ClusteringSettings.setLoadingSpectrumFilter(new BinnedHighestNPeakFunction(10, 100, 30));
            }

            // MIN CONSENSUS PEAKS TO KEEP
            if (commandLine.hasOption(CliOptions.OPTIONS.ADVANCED_MIN_CONSENSUS_PEAKS_TO_KEEP.getValue())) {
                Defaults.setDefaultConsensusMinPeaks(Integer.parseInt(
                        commandLine.getOptionValue(CliOptions.OPTIONS.ADVANCED_MIN_CONSENSUS_PEAKS_TO_KEEP.getValue())));
            }

            // MGF COMMENT SUPPORT
            ClusteringSettings.disableMGFCommentSupport = commandLine.hasOption(CliOptions.OPTIONS.ADVANCED_DISABLE_MGF_COMMENTS.getValue());

            // MERGE BINARY FILES
            boolean mergeBinaryFilesMode = commandLine.hasOption(CliOptions.OPTIONS.ADVANCED_MERGE_BINARY_FILES.getValue());

            /**
             * ------ Convert CLS mode ----
             */
            if (commandLine.hasOption(CliOptions.OPTIONS.ADVANCED_CONVERT_CGF.getValue())) {
                convertToCgf(peaklistFilenames, finalResultFile);
                return;
            }

            /**
             * ------ Learn the CDF if set --------
             */
            if (commandLine.hasOption(CliOptions.OPTIONS.ADVANCED_LEARN_CDF.getValue())) {
                String cdfOuputFilename = commandLine.getOptionValue(CliOptions.OPTIONS.ADVANCED_LEARN_CDF.getValue());
                File cdfOutputFile = new File(cdfOuputFilename);

                if (cdfOutputFile.exists()) {
                    throw new Exception("CDF output file " + cdfOuputFilename + " already exists.");
                }

                CdfLearner cdfLearner = new CdfLearner();
                System.out.println("Learning CDF...");
                CdfResult cdfResult = cdfLearner.learnCumulativeDistribution(peaklistFilenames, paralellJobs);

                // write it to the file
                FileWriter writer = new FileWriter(cdfOutputFile);
                writer.write(cdfResult.toString());
                writer.close();

                System.out.println("CDF successfully written to " + cdfOuputFilename);
                return;
            }

            /**
             * ------ Load the CDF from file -------
             */
            if (commandLine.hasOption(CliOptions.OPTIONS.ADVANCED_LOAD_CDF_FILE.getValue())) {
                BufferedReader reader = new BufferedReader(
                        new FileReader(
                                commandLine.getOptionValue(CliOptions.OPTIONS.ADVANCED_LOAD_CDF_FILE.getValue())));

                StringBuilder cdfString = new StringBuilder();
                String line;
                while ((line = reader.readLine()) != null) {
                    cdfString.append(line);
                }
                reader.close();

                Defaults.setCumulativeDistributionFunction(CumulativeDistributionFunction.fromString(cdfString.toString()));
            }

            /**
             * ------- THE ACTUAL LOGIC STARTS HERE -----------
             */
            printSettings(finalResultFile, paralellJobs, startThreshold, endThreshold, rounds, spectraClusterStandalone.isKeepBinaryFiles(),
                    spectraClusterStandalone.getTemporaryDirectory(), peaklistFilenames, reUseBinaryFiles, spectraClusterStandalone.isUseFastMode(),
                    addedFilters);

            spectraClusterStandalone.addProgressListener(this);

	    long global_start_time = System.nanoTime();
	    System.out.println("Started timing!");

            // merge mode
            if (mergeBinaryFilesMode) {
                System.out.println("Binary file merging mode set.");

                if (commandLine.hasOption(CliOptions.OPTIONS.ADD_SCORES.getValue())) {
                    System.out.println("Error: Scores cannot be added in binary file merging mode");
                    System.exit(1);
                }

                spectraClusterStandalone.mergeBinaryFiles(peaklistFilenames, thresholds, finalResultFile);
                System.exit(0);
            }

            // make sure binary files exist
            if (reUseBinaryFiles) {
                File binaryFileDirectory = new File(spectraClusterStandalone.getTemporaryDirectory(), "spectra");
                if (!binaryFileDirectory.isDirectory()) {
                    reUseBinaryFiles = false;
                    System.out.println("No binary files found. Re-creating them...");
                }
            }
	    
	    
            if (reUseBinaryFiles) {
                spectraClusterStandalone.clusterExistingBinaryFiles(
                        spectraClusterStandalone.getTemporaryDirectory(), thresholds, finalResultFile);
            }
            else {
                List<File> peaklistFiles = new ArrayList<File>(peaklistFilenames.length);
                for (String filename : peaklistFilenames) {
                    peaklistFiles.add(new File(filename));
                }

                spectraClusterStandalone.clusterPeaklistFiles(peaklistFiles, thresholds, finalResultFile);
            }

            // add the scores if set
            if (commandLine.hasOption(CliOptions.OPTIONS.ADD_SCORES.getValue())) {
                // get the directories of the MGF files
                Set<File> directories = new HashSet<>();
                for (String peakListFile : peaklistFilenames) {
                    directories.add(new File(peakListFile).getParentFile());
                }
                File[] mgfDirs = new File[directories.size()];
                directories.toArray(mgfDirs);

                System.out.println("Adding scores to output file...");
                ScoreCalculator scoreCalculator = new ScoreCalculator();
                scoreCalculator.processClusteringResult(finalResultFile, mgfDirs);
            }

	    long global_end_time = System.nanoTime();
	    double elapsed_time = (double) (global_end_time - global_start_time) / 1000000000.00001;
	    System.out.println("Total elapsed time: " + elapsed_time);

        } catch (MissingParameterException e) {
            System.out.println("Error: " + e.getMessage() + "\n\n");
            printUsage();

            System.exit(1);
        } catch (Exception e) {
            e.printStackTrace();
            System.out.println("Error: " + e.getMessage());

            System.exit(1);
        }
    }

    /**
     * Convert the passed files from the .cgf format to the .clustering format.
     * @param inputFiles
     * @param outputFile
     */
    private void convertToCgf(String[] inputFiles, File outputFile) throws Exception {
        SpectraClusterStandalone spectraClusterStandalone = new SpectraClusterStandalone();
        spectraClusterStandalone.addProgressListener(this);

        if (inputFiles.length != 1) {
            System.out.println("Error: Only one cgf file can be converted to one .clustering file");
            return;
        }

        spectraClusterStandalone.convertCgfToClustering(new File(inputFiles[0]), outputFile, 0.99F);
    }

    private void printSettings(File finalResultFile, int nMajorPeakJobs, float startThreshold,
                                      float endThreshold, int rounds, boolean keepBinaryFiles, File binaryTmpDirectory,
                                      String[] peaklistFilenames, boolean reUseBinaryFiles, boolean fastMode,
                                      List<String> addedFilters) {
        System.out.println("spectra-cluster API Version 1.0.11");
        System.out.println("Created by Rui Wang & Johannes Griss\n");

        System.out.println("-- Settings --");
        System.out.println("Number of threads: " + String.valueOf(nMajorPeakJobs));
        System.out.println("Thresholds: " + String.valueOf(startThreshold) + " - " + String.valueOf(endThreshold) + " in " + rounds + " rounds");
        System.out.println("Keeping binary files: " + (keepBinaryFiles ? "true" : "false"));
        System.out.println("Binary file directory: " + binaryTmpDirectory);
        System.out.println("Result file: " + finalResultFile);
        System.out.println("Reuse binary files: " + (reUseBinaryFiles ? "true" : "false"));
        System.out.println("Input files: " + peaklistFilenames.length);
        System.out.println("Using fast mode: " + (fastMode ? "yes" : "no"));
        if (ClusteringSettings.getLoadingMode() == ClusteringSettings.LOADING_MODE.ONLY_IDENTIFIED) {
            System.out.println("Loading only identified spectra");
        }
        if (ClusteringSettings.getLoadingMode() == ClusteringSettings.LOADING_MODE.ONLY_UNIDENTIFIED) {
            System.out.println("Loading only unidentified spectra");
        }

        System.out.println("\nOther settings:");
        if (ClusteringSettings.ppmThreshold != null)
            System.out.println("Precursor tolerance: " + ClusteringSettings.ppmThreshold + " ppm");
        else
            System.out.println("Precursor tolerance: " + Defaults.getDefaultPrecursorIonTolerance() + " m/z");

        System.out.println("Fragment ion tolerance: " + Defaults.getFragmentIonTolerance());

        // loading peak filter
        if (ClusteringSettings.getLoadingSpectrumFilter().getClass() == HighestNPeakFunction.class) {
            System.out.println("Loading filter: Filtering top N peaks per spectrum");
        }
        if (ClusteringSettings.getLoadingSpectrumFilter().getClass() == BinnedHighestNPeakFunction.class) {
            System.out.println("Loading filter: Filtering top 10 peaks / 100 m/z");
        }

        // used filters
        System.out.print("Added filters: ");
        for (int i = 0; i < addedFilters.size(); i++) {
            if (i > 0) {
                System.out.print(", ");
            }
            System.out.print(addedFilters.get(i));
        }
        System.out.println("");

        // number of comparisons
        if (Defaults.getNumberOfComparisonAssessor().getClass() == MinNumberComparisonsAssessor.class) {
            MinNumberComparisonsAssessor assessor = (MinNumberComparisonsAssessor) Defaults.getNumberOfComparisonAssessor();
            System.out.println("Minimum number of comparisons: " + assessor.getMinNumberComparisons());
        } else {
            System.out.println("Minimum number of comparisons: adaptive");
        }

        System.out.println();
    }

    private void printUsage() {
        HelpFormatter formatter = new HelpFormatter();
        formatter.printHelp("Spectra Cluster - Clusterer",
                "Clusters the spectra found in a MGF files or .clustering files and writes the results in a text-based file.\n",
                CliOptions.getOptions(), "\n\n", true);
    }

    @Override
    public void onProgressUpdate(ProgressUpdate progressUpdate) {
        System.out.println(progressUpdate.getMessage());
    }
}
