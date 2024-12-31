import os
import math
import random


def is_square(n):
    if n < 0:
        return False
    root = int(math.sqrt(n))
    return root * root == n


def generate_test_cases():
    # Ensure the output directory exists
    os.makedirs("square", exist_ok=True)

    test_cases = []

    # Generate 50 YES cases
    for _ in range(51):
        root = random.randint(0, int(math.sqrt(10000)))
        test_input = root * root
        test_cases.append((test_input, "YES"))

    # Generate 30 NO cases
    while len(test_cases) < 100:
        test_input = random.randint(0, 10000)
        if not is_square(test_input):
            test_cases.append((test_input, "NO"))

    # Shuffle the test cases
    random.shuffle(test_cases)

    # Write the test cases to files
    for i, (test_input, test_output) in enumerate(test_cases, start=1):
        input_filename = f"square/input{i}.in"
        with open(input_filename, "w") as infile:
            infile.write(f"{test_input}\n")

        output_filename = f"square/output{i}.out"
        with open(output_filename, "w") as outfile:
            outfile.write(f"{test_output}\n")


if __name__ == "__main__":
    generate_test_cases()
