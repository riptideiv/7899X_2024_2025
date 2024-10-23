import json
import time

import matplotlib.pyplot as plt
import matplotlib.animation as animation

GRID_SIZE = 1000

# Function to read the latest JSON object from the log file
def read_latest_log_entry(log_file_path):
    with open(log_file_path, 'r') as log_file:
        lines = log_file.readlines()
        if lines:
            latest_log = lines[-1]
            return json.loads(latest_log)
    return None

# Function to update the plot
def update_plot(frame, log_file_path, scatter):
    log_entry = read_latest_log_entry(log_file_path)
    if log_entry:
        odomX = log_entry.get('odomX', 0)
        odomY = log_entry.get('odomY', 0)
        scatter.set_offsets([[odomX+GRID_SIZE/2, odomY+GRID_SIZE/2]])
    return scatter,

def main():
    log_file_path = './brain.log'  # Update this path to your actual log file path

    fig, ax = plt.subplots()
    ax.set_xlim(0, GRID_SIZE)
    ax.set_ylim(0, GRID_SIZE)
    scatter = ax.scatter([], [])

    ani = animation.FuncAnimation(fig, update_plot, fargs=(log_file_path, scatter), interval=250)
    plt.show()

if __name__ == "__main__":
    main()