# Runs TIM adaptively as a blackbox
# Usage: ./blackbox.sh [dataset] [k] [realizations]
dataset=${1}
k=${2}
r=${3}
epsilon=${4}

echo "Copying initial graph state"

temp="${dataset}_temp"
rm -r ${temp}/
mkdir ${temp}/
# cp -r ${dataset}/ ${temp}/
# cp ${temp}/graph_ic.inf ${temp}/graph_ic_full.inf

echo "Preparing output files"

rm ${temp}/seeds.txt
touch ${temp}/seeds.txt
rm ${temp}/influence.txt
touch ${temp}/influence.txt
output="${dataset}/spread_${epsilon}.csv"
rm ${output}
touch ${output}

# Add header to CSV file
echo "realization,seed,spread,seed_id" >> ${output}

# realization=0
total_influence=0

# For each realization until we reach r
# while [ ${realization} -lt ${r} ]; do

# cp ${temp}/graph_ic_full.inf ${temp}/graph_ic.inf 

echo "=========================================="

j=0
rm ${temp}/visited.txt
touch ${temp}/visited.txt

# For each seed node until we reach k or there are no more edges to activate
# while [[ -s ${temp}/graph_ic.inf && -s ${temp}/realization_${realization} && ${i} -lt ${k} ]]; do
while [[ ${j} -lt ${r} ]]; do
    # while [[ ${i} -lt ${k}  && ${remaining_nodes} -gt 0 ]]; do

    cp ${dataset}/graph_ic.inf ${temp}/
    cp ${dataset}/attribute.txt ${temp}/
    cp ${dataset}/realization_${j} ${temp}/
    cp ${dataset}/n.txt ${temp}/
    remaining_nodes=`cat ${dataset}/n.txt`

    i=0
    realization_influence=0

    while read seed
    do

        i=`expr $i + 1`
        

        # echo "./iteration.sh ${temp} ${remaining_nodes} ${r}"
        # gtime -f'%E' ./iteration.sh ${temp} ${remaining_nodes} ${realization} -o time.txt

        # gtime -f'%E' -o ${temp}/time.txt ./tim -model IC -dataset ${temp} -epsilon 0.05 -k 1 -n ${remaining_nodes}
        echo ${seed} > ${temp}/seed.txt
        
        ./bfs ${temp} ${j}

        # ./tim -model IC -dataset ${temp} -epsilon 0.05 -k 1 -n ${remaining_nodes}
        # influence=`./bfs ${temp} seed.txt ${realization}` 

        influence=`cat ${temp}/visited_count.txt`
        realization_influence=`expr $realization_influence + $influence`
        remaining_nodes=`expr ${remaining_nodes} - ${influence}`
        seed_id=`cat ${temp}/seed.txt`

        # Adds data to CSV file
        echo "> Realization nº ${j}; Seed nº ${i}; Influence: ${realization_influence}"
        echo "${j},${i},${realization_influence},${seed_id}" >> ${output}

        cat ${temp}/seed.txt >> ${temp}/seeds.txt

    done < ${dataset}/seeds_${epsilon}.txt
    echo "> Influence for realization ${j}: ${realization_influence}"
    total_influence=`expr $total_influence + $realization_influence`
    j=`expr $j + 1`

done

echo "Number of seeds selected: ${i}"
echo "Average influence: `expr ${total_influence} / ${j}`"
echo "(${total_influence} / ${j})"

# echo ${total_influence} > influence.txt