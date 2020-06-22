In this homework, you are supposed to write a GA with CUDA to find “HELLO WORLD” form alphabet letters. In other words, the phrase“HELLO WROLD” is the optimal solution, and all the possible genes are letters “A” to “Z” and “ ”. You can model each Character as a Gene, and consider the Chromosome Length as 11.
-At first, you should generate a list of possible solutions (Initialize Population).
-The fitness criterion for this problem is the similarity of each chromosome to the phrase “HELLO WORLD”, and you shoulddefine afitness score for each chromosome.
-In the Selection phase, you have to sort all chromosomes based on their fitness score and select a percentage of better chromosomes for the next iteration of the algorithm.
-You are free to implement a good policy for the Mutation and Crossover phases (Single point is the simplestway).
-You should test your code with different Initial populations (100, 500, 1000, 10000), and report the execution time for each.
-Finally, you should profile your codes using NVIDIA Visual Profiler or nvrof and analyze the results provided, and determine what have you done to improve the performance according to your analyze.
-(20% Bonus)You can use CUDA streams for transferring data between host and device.