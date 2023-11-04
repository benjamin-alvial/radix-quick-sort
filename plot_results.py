import pandas as pd
import matplotlib.pyplot as plt

file_path = 'performance_results.txt'
column_names = ['u', 'k', 'rep', 'cpu_rs', 'cpu_qs']

# Specify the chunk size
NUMBER_REPS = 1

# Create an empty DataFrame to store the results
result_df = pd.DataFrame(columns=['chunk', 'u', 'k', 'avg_cpu_rs', 'avg_cpu_qs'])

# Iterate through chunks of the CSV file
for chunk_number, chunk_df in enumerate(pd.read_csv(file_path, names=column_names, delimiter=',', chunksize=NUMBER_REPS)):
    chunk_df = chunk_df.reset_index(drop=True)

    # Calculate the average for the fourth and fifth columns
    u = chunk_df['u'][0]
    k = chunk_df['k'][0]
    avg_cpu_rs = chunk_df['cpu_rs'].mean()
    avg_cpu_qs = chunk_df['cpu_qs'].mean()

    # Append the results to the result DataFrame
    result_df = result_df._append({'chunk': chunk_number + 1, 'u': u, 'k': k, 'avg_cpu_rs': avg_cpu_rs, 'avg_cpu_qs': avg_cpu_qs}, ignore_index=True)

# Display the result DataFrame
print(result_df)

# ============ Experiment 1 ============
# Analyzes effect of number of bits k and size of universe u
# in the time taken by radix sort.
print("============ Experiment 1 ============")
exp1_df = result_df
u_values_to_plot = [2**10, 2**30, 2**60]

# Plotting
plt.figure(figsize=(10, 6))

for u in u_values_to_plot:
    by_u_df = exp1_df[exp1_df['u']==u]
    print(by_u_df)

    # Plot the u column as a function of the radix sort time column
    plt.plot(by_u_df['k'], by_u_df['avg_cpu_rs'], label='radix sort'+str(u))

# Set labels and title
plt.xlabel('k')
plt.ylabel('radix sort time (s)')

# Show legend
plt.legend()

plt.savefig('exp1.png')
plt.show()
plt.clf()

# ============ Experiment 2 ============
# Compares radix sort and quicksort as a function of u.
# The best results for radix sort time should be considered,
# considering multiple values of k and optimal k must be chosen.
print("============ Experiment 2 ============")
exp2_df = result_df.loc[result_df.groupby('u')['avg_cpu_rs'].idxmin()]
print(exp2_df)

# Plotting
plt.figure(figsize=(10, 6))

plt.xscale('log', base=2)

# Plot the u column as a function of the radix sort time column
plt.plot(exp2_df['u'], exp2_df['avg_cpu_rs'], label='radix sort')

# Plot the u column as a function of the quicksort time column
plt.plot(exp2_df['u'], exp2_df['avg_cpu_qs'], label='quicksort')

# Set labels and title
plt.xlabel('u')
plt.ylabel('time (s)')

# Show legend
plt.legend()

# Show the plot
plt.savefig('exp2.png')
plt.show()
