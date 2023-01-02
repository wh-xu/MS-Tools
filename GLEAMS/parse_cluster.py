import sys
import numpy as np
import pandas as pd

meta_file = sys.argv[1]
cluster_file = sys.argv[2]
csv_file = cluster_file[:-4] + '.csv'

cluster_label = np.load(cluster_file)
meta = pd.read_parquet(meta_file)
idx_s = meta['filename'].str.rfind('/')+1
idx_e = meta['filename'].str.rfind('.')
meta['identifier'] = [str_i[idx_s[i]: idx_e[i]] for i, str_i in enumerate(list(meta['filename']))]
meta.drop(columns=['filename', 'dataset'], inplace=True)

meta['cluster'] = cluster_label
meta.rename({'charge': 'precursor_charge', 'mz': 'precursor_mz'}, axis=1, inplace=True)

out_file = csv_file[:-4]+'.parquet'
meta.to_parquet(out_file, compression='snappy')
print('Saving to ', out_file)
