import tkinter as tk
from tkinter import ttk
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import threading
import serial
import time
import com

def update_ui():
    telemetry_data = {
        'battery': com.BATTERYLEVEL,
        'speed': com.MOTORSPEED,
        'position': 50,  # Placeholder value
        'power': 0  # Placeholder value
    }
    update_telemetry(telemetry_data)
    root.after(1000, update_ui) 

# Function to draw the occupancy grid
def draw_occupancy_grid(grid: list[list[int]]):
    fig, ax = plt.subplots(figsize=(5, 5))
    ax.imshow(grid, cmap='Greys', interpolation='none')
    vehicle_x, vehicle_y = len(grid[0]) // 2, len(grid) // 2
    ax.plot(vehicle_x, vehicle_y, 'ro')  # Mark the vehicle position with a red dot
    return fig

# Function to update signs information
def update_signs(signs_info: str) -> None:
    signs_var.set(f"Signs Info: {signs_info}")

# Function to update system telemetry with separate progress bars
def update_telemetry(telemetry_info: dict[str, int]) -> None:
    battery_level = telemetry_info['battery']
    speed = telemetry_info['speed']
    position_in_lane = telemetry_info['position']
    power_draw = telemetry_info['power']

    battery_progress['value'] = battery_level
    speed_progress['value'] = speed
    position_progress['value'] = position_in_lane
    power_progress['value'] = power_draw

    battery_var.set(f"Battery: {battery_level}%")
    speed_var.set(f"Speed: {speed} km/h")
    position_var.set(f"Position in Lane: {position_in_lane}")
    power_var.set(f"Power Draw: {power_draw} kW")

# Functions to be called by the start and stop buttons
def start_vehicle() -> None:
    print("Vehicle started")

def stop_vehicle() -> None:
    print("Vehicle stopped")

# Set up the tkinter window
root = tk.Tk()
root.title("Vehicle Control Panel")

# Use grid layout
root.grid_rowconfigure(0, weight=1)
root.grid_columnconfigure(0, weight=1)
root.grid_columnconfigure(1, weight=1)

# Frame for grid map and controls
left_frame = tk.Frame(root)
left_frame.grid(row=0, column=0, sticky="nsew")

# Frame for telemetry
right_frame = tk.Frame(root)
right_frame.grid(row=0, column=1, sticky="nsew")

# Draw the occupancy grid in the left frame
grid = [
    [0, 0, 0, 1, 0, 0, 0, 1, 0, 0],
    [0, 0, 1, 1, 0, 0, 1, 1, 0, 0],
    [0, 1, 0, 0, 1, 1, 0, 0, 1, 0],
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 1],
    [0, 1, 0, 1, 1, 1, 1, 0, 1, 0],
    [0, 0, 1, 0, 0, 0, 0, 1, 0, 0],
    [0, 0, 0, 1, 1, 1, 1, 0, 0, 0],
    [0, 1, 0, 0, 0, 0, 0, 0, 1, 0],
    [0, 0, 1, 1, 0, 0, 1, 1, 0, 0],
    [0, 0, 0, 0, 0, 1, 0, 0, 0, 0]
]
fig = draw_occupancy_grid(grid)
canvas = FigureCanvasTkAgg(fig, master=left_frame)
canvas.draw()
canvas.get_tk_widget().pack(expand=True)

# Add start and stop buttons in the left frame
button_frame = tk.Frame(left_frame)
button_frame.pack(side=tk.BOTTOM, pady=10)
start_button = ttk.Button(button_frame, text="Start", command=start_vehicle)
start_button.pack(side=tk.LEFT, padx=10)
stop_button = ttk.Button(button_frame, text="Stop", command=stop_vehicle)
stop_button.pack(side=tk.LEFT, padx=10)

# Add signs information section in the right frame
signs_var = tk.StringVar()
signs_label = tk.Label(right_frame, textvariable=signs_var, font=('Arial', 12))
signs_label.pack(pady=10)
update_signs("None")

# Telemetry section with separate progress bars and labels
battery_var = tk.StringVar()
battery_label = tk.Label(right_frame, textvariable=battery_var, font=('Arial', 12))
battery_label.pack()
battery_progress = ttk.Progressbar(right_frame, orient='horizontal', length=200, mode='determinate', maximum=100)
battery_progress.pack()

speed_var = tk.StringVar()
speed_label = tk.Label(right_frame, textvariable=speed_var, font=('Arial', 12))
speed_label.pack()
speed_progress = ttk.Progressbar(right_frame, orient='horizontal', length=200, mode='determinate', maximum=200)  # Assuming max speed is 200 km/h
speed_progress.pack()

position_var = tk.StringVar()
position_label = tk.Label(right_frame, textvariable=position_var, font=('Arial', 12))
position_label.pack()
position_progress = ttk.Progressbar(right_frame, orient='horizontal', length=200, mode='determinate', maximum=100)  # Adjust maximum value as needed
position_progress.pack()

power_var = tk.StringVar()
power_label = tk.Label(right_frame, textvariable=power_var, font=('Arial', 12))
power_label.pack()
power_progress = ttk.Progressbar(right_frame, orient='horizontal', length=200, mode='determinate', maximum=500)  # Assuming

# Assuming max power draw is 500 kW
power_progress = ttk.Progressbar(right_frame, orient='horizontal', length=200, mode='determinate', maximum=500)
power_progress.pack()

# Example telemetry data update - this part will likely come from your vehicle's data
telemetry_data = {
    'battery': com.BATTERYLEVEL,  # Example battery level percentage
    'speed': com.MOTORSPEED,  # Example speed in km/h
    'position': 50,  # Example position in lane (0-100, with 50 being centered)
    'power': 0  # Example power draw in kW
}
update_telemetry(telemetry_data)

# Initialize serial communication
ser = serial.Serial(port="COM3", baudrate=115200, timeout=1)
# ser = None
time.sleep(3)
com.start_reading(ser)  # Start the separate thread for reading serial data
# com.start_updating()  # Start the background thread to update values

root.after(1000, update_ui)
# Call update_ui for the first time to start the periodic update

root.mainloop()