import os
import random

# Re-create directories after state reset
os.makedirs("circle", exist_ok=True)


# Function to determine the state of the circles
def circle_state(x1, y1, r1, x2, y2, r2):
    distance_squared = (x2 - x1) ** 2 + (y2 - y1) ** 2
    r_sum = r1 + r2
    r_diff = abs(r1 - r2)
    if distance_squared > r_sum ** 2:
        return "outside"  # Circles are separate
    elif r_diff ** 2 <= distance_squared <= r_sum ** 2:
        return "touch"   # Circles collide (either inside or outside)
    else:
        return "inside"  # One circle is completely inside the other


# Counters for each type of state
outside_count = 0
inside_count = 0
touch_count = 0

# Total number of each case needed
total_cases = 33
test_cases = []

while outside_count < total_cases or inside_count < total_cases or touch_count < total_cases:
    # Randomly generate positions and radii for two circles
    x1, y1 = random.randint(-1000, 1000), random.randint(-1000, 1000)
    r1 = random.randint(1, 1000)
    x2, y2 = random.randint(-1000, 1000), random.randint(-1000, 1000)
    r2 = random.randint(1, 1000)

    # Calculate the state
    result = circle_state(x1, y1, r1, x2, y2, r2)

    # Ensure equal distribution of test cases
    if result == "outside" and outside_count < total_cases:
        outside_count += 1
    elif result == "inside" and inside_count < total_cases:
        inside_count += 1
    elif result == "touch" and touch_count < total_cases:
        touch_count += 1
    else:
        continue

    test_cases.append((x1, y1, r1, x2, y2, r2, result))

# Shuffle the test cases
random.shuffle(test_cases)

# Write the shuffled test cases to files
for i, (x1, y1, r1, x2, y2, r2, result) in enumerate(test_cases, start=1):
    with open(f"circle/input{i}.in", "w") as input_file:
        input_file.write(f"{x1} {y1} {r1} {x2} {y2} {r2}\n")
    with open(f"circle/output{i}.out", "w") as output_file:
        output_file.write(f"{result}\n")
