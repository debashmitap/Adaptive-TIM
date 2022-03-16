# Adaptive-TIM

The algorithm uses *TIM https://arxiv.org/pdf/1404.0900v2.pdf* as a blackbox to select the best seed node at every step of the adptive seed selection process.

1. To compile the project, run ./compile.sh in your terminal.
2. To generate the realizations on the nethept dataset, run ./realizations.sh nethept (no. of realizations). Eg. for *50 realizations*, `./realizations.sh nethept 50`
3. Finally, use ./blackbox.sh nethept (no. of seeds) (no. of realizations) to get the results which will be stored in spread.csv file. (Eg. ./blackbox.sh nethept 100 20 for 100 seeds and 20 realizations)


# Changing the diffusion model and the epsilon

The default underlying diffusion model is set to the **independent cascade (IC) model**. In order to change it to **Linear Threshold**, visit **line 48** of **blackbox.sh** and change it to ./tim -model LT -dataset ${temp} -epsilon 0.05 -k 1.

The *epsilon* value can also be modified in the same line from *0.05* to any value of your choice.
