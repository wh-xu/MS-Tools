export PXD=001468
export emb="GLEAMS_PXD"${PXD}
export ep=0.3

gleams embed /dataset/PXD${PXD}/*.mgf --embed_name ${emb}_emb | tee log/$emb.log

for ep in 0.3
do
    gleams cluster --embed_name ${emb}_emb --cluster_name ${emb}_ep_${ep}_cluster --distance_threshold $ep | tee log/$emb.log -a
    python parse_cluster.py ${emb}_emb.parquet ${emb}_ep_${ep}_cluster.npy
done

