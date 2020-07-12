import subprocess
from calls_and_outs import calls, outs


def test_my_code():
	for i in range(len(calls)):
		call = calls[i]
		out = outs[i]
		print i, ":", call
		
		# This runs your code and gets the output
		p = subprocess.Popen(call, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)
		my_output, err = p.communicate()
		err_code = p.returncode
		
		if err_code == 0: # If there is no error
			print 'My output:'
			print my_output
			print 'Answer:'
			print out
		else:
			print '\tError in test'
			print err
		print

test_my_code()
