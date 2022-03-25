# Runs TIM adaptively as a blackbox
# Usage: ./blackbox.sh [dataset] [k] [realizations]
dataset=${1}
k=${2}
r=${3}

echo "Copying initial graph state"

temp="temp"
rm -r ${temp}/
cp -r ${dataset}/ ${temp}/
cp ${temp}/graph_ic.inf ${temp}/graph_ic_full.inf

echo "Preparing output files"

rm seeds.txt
touch seeds.txt
rm influence.txt
touch influence.txt
rm spread.csv
touch spread.csv

# Add header to CSV file
echo "realization,seed,spread,seed_id,time" >> spread.csv

realization=0
total_influence=0

# For each realization until we reach r
while [ ${realization} -lt ${r} ]; do

    cp ${temp}/graph_ic_full.inf ${temp}/graph_ic.inf 

    echo "=========================================="
    i=0
    realization_influence=0
    remaining_nodes=`cat ${temp}/n.txt`

    # For each seed node until we reach k or there are no more edges to activate
    # while [[ -s ${temp}/graph_ic.inf && -s ${temp}/realization_${realization} && ${i} -lt ${k} ]]; do
    while [[ ${i} -lt ${k}  && ${remaining_nodes} -gt 0 ]]; do

        echo "=========================================="

        i=`expr $i + 1`
        echo "Realization nº ${realization}; Seed nº ${i}"

        echo "./iteration.sh ${temp} ${remaining_nodes} ${realization}"
        # gtime -f'%E' ./iteration.sh ${temp} ${remaining_nodes} ${realization} -o time.txt

        gtime -f'%E' -o time.txt ./tim -model IC -dataset ${temp} -epsilon 0.05 -k 1 -n ${remaining_nodes}; ./bfs ${temp} seed.txt ${realization}

        # ./tim -model IC -dataset ${temp} -epsilon 0.05 -k 1 -n ${remaining_nodes}
        # influence=`./bfs ${temp} seed.txt ${realization}` 

        iteration_time=`cat time.txt`
        influence=`cat ${temp}/visited_count.txt`
        realization_influence=`expr $realization_influence + $influence`
        echo "Influence for seed ${i}: ${realization_influence}"
        remaining_nodes=`expr ${remaining_nodes} - ${influence}`
        seed_id=`cat seed.txt`

        # Adds data to CSV file
        echo "${realization},${i},${realization_influence},${seed_id},${iteration_time}" >> spread.csv

        echo "Storing seed"
        cat seed.txt >> seeds.txt

    done

    echo "Influence for realization ${realization}: ${realization_influence}"

    realization=`expr $realization + 1`
    total_influence=`expr $total_influence + $realization_influence`

done

echo "Number of seeds selected: ${i}"
echo "Average influence: `expr ${total_influence} / ${r}`"
echo "(${total_influence} / ${r})"

# echo ${total_influence} > influence.txt