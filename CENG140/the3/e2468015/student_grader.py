import os
### run with Python3 ###

def calculate_grade(student_outputs, correct_outputs):
    """
    :param student_outputs: should contain your outputs. Your outputs should be name input1.txt, input2.txt...
     (i.e. if inputs, outputs and the3 executable are in the same directory
    input like this to get the desired output name: './the3 < inputs/inputX.txt > outputs/inputX.txt')
    :param correct_outputs: path of the directory that contains the correct outputs. These outputs are named
     input1.txt, input2.txt...
    :return: grade: your total grade. In addition to this, a file named 'grading_info.txt' is created that contains
     a more detailed information about each test case.
    """
    # holds the inputs you had problems with.
    incorrect_inputs = []
    # points for each of the 20 test cases are accumulated in total_test_points and then averaged
    total_test_points = 0
    # holds the logs to be written to grading_info.txt
    grading_info = ""

    for file in os.listdir(student_outputs):
        if file.endswith('.txt'):
            points = 100 # initially 100, hope it stays that way

            # read the correct answer and convert it to a list of floats
            with open(os.path.join(correct_outputs, file)) as f:
                correct_answer = f.read().strip().split(' ')
                correct_answer = [float(x) for x in correct_answer]
            grading_info += f"starting {file}\n"
            # read the students answer and convert it to a list of floats
            with open(os.path.join(student_outputs, file), 'r') as f:
                try:
                    student_answer = f.read().strip().split(' ')
                    student_answer = [float(x) for x in student_answer]
                except:
                    # if there is an error that means your output is incorrect :(
                    # no need to continue the rest of this test case
                    grading_info += f"\tstudent output is erroneous for {file}\n"
                    incorrect_inputs.append(file)
                    continue

            # First check if the output lengths match
            if not len(student_answer) == len(correct_answer):
                grading_info += f"\tOutput lengths for {file} does not match\n"
                points -= 100
                incorrect_inputs.append(file)
                continue

            x_min_s = student_answer[0]
            x_max_s = student_answer[1]
            x_min_c = correct_answer[0]
            x_max_c = correct_answer[1]
            n_intervals = len(student_answer) - 2 # number of intervals

            # error margin for min and max values
            interval_error_margin = abs(x_min_c - x_max_c) * 0.1

            # If the difference between interval limits are less than interval_error_margin
            # you got full points. If it is between interval_error_margin and 5*interval_error_margin
            # there is a 10 point penalty. Otherwise you got 0 from this input, as too much difference in
            # interval limits would make the probability of intervals meaningless
            if interval_error_margin < abs(x_min_c - x_min_s) < interval_error_margin * 5:
                grading_info += "\t-10 points for min interval diff\n"
                points -= 10
                if file not in incorrect_inputs:
                    incorrect_inputs.append(file)

            elif abs(x_min_c - x_min_s) > interval_error_margin * 5:
                # too much difference in interval limits, probabilities are meaningless
                grading_info += "\t-100 points for too much min interval diff\n"
                points = 0
                if file not in incorrect_inputs:
                    incorrect_inputs.append(file)

            if interval_error_margin < abs(x_max_c - x_max_s) < interval_error_margin * 5:
                grading_info += "\t-10 points for max interval diff\n"
                points -= 10
                if file not in incorrect_inputs:
                    incorrect_inputs.append(file)
            elif abs(x_max_c - x_max_s) > interval_error_margin * 5:
                # too much difference in interval limits, probabilities are meaningless
                grading_info += "\t-100 points for too much max interval diff\n"
                points = 0
                if file not in incorrect_inputs:
                    incorrect_inputs.append(file)

            incorrect_intervals = 0
            for j in range(2, len(student_answer)):
                # 0.02 is the error margin for probabilities. It is 20 times of the required precision!
                # considering number of experiments are at least 10 million, it is pretty generous
                if abs(student_answer[j] - correct_answer[j]) > 0.02:
                    grading_info += f"\tdistance between probabilities are greater than 0.02 for of interval {j - 2}\n"
                    incorrect_intervals += 1
                    if file not in incorrect_inputs:
                        incorrect_inputs.append(file)

            # probabilities are worth total of 80 points.
            points_lost_from_intervals = 80 * (incorrect_intervals / n_intervals)
            points -= points_lost_from_intervals

            if points < 0:
                points = 0

            grading_info += f"\tpoints for {file}:{points}\n\n"
            total_test_points += points

    if len(incorrect_inputs):
        grading_info += f"had problems in: {incorrect_inputs}\n"

    # 20 is the number of text cases
    grade = round(total_test_points / 20, 1)
    grading_info += f"Total points:{grade}\n"
    # write the log to the file
    with open(os.path.join('grading_info.txt'), 'w+') as f:
        f.write(grading_info)
    print("check grading_info.txt!")
    return grade


if __name__ == '__main__':
    calculate_grade('outputs', 'correct_outputs')