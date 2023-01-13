#!/usr/bin/env python

# This script automatically runs tests for mcmas - all of the tests in the test directory tree.
# Test specifications must be followed by a comment indicating if the formula is expected to be true or false.

import os
import subprocess
import sys

def run_mcmas(relpath):
    if 'finite-traces' in relpath:
        s = subprocess.check_output(["../mcmas", "-ldlf", relpath])
    else:
        s = subprocess.check_output(["../mcmas", relpath])

    actuals = [];
    for l in filter(lambda y : 'Formula' in y, s.split('\n')):
        actuals.append('TRUE' in l)
    return actuals

def get_lines(relpath):
    ispl_file = open(relpath, 'r')
    ispl_lines = ispl_file.read().split('\n')

    in_formulae = False
    formulae = []

    for line in ispl_lines:
        line = line.strip()
        if in_formulae:
            if line == 'end Formulae':
                in_formulae = False
            else:
                # This line is a formula
                components = line.split('--')
                if len(components) != 2:
                    if ('-v' in sys.argv):
                        print 'Error in ' + relpath + ': there was a formula line [' + components[0] + '] without indication if true or false, or other test syntax error. Skipping.'
                else:
                    formulae.append((components[0], 'True' in components[1]))
        elif line == 'Formulae':
            in_formulae = True

    return formulae

def main():
    all_tests = 0
    all_failures = 0
    for root, dirs, files in os.walk('.'):
        for f in filter(lambda x : x.endswith('ispl'), files):
            relpath = os.path.join(root, f)
            if ('expensive' in relpath and not ('-e' in sys.argv)):
                continue
            expecteds = get_lines(relpath)
            try:
                actuals = run_mcmas(relpath)
            except subprocess.CalledProcessError as exc:
                print relpath + ': ERROR, nonzero exit code.'
                all_tests += len(expecteds)
                all_failures += len(expecteds)
                continue
            incorrect = 0
            for (index, (formula, indicator)) in enumerate(expecteds):
                if actuals[index] != indicator:
                    incorrect = incorrect + 1
                    print relpath + ': fail ' + formula
            total_tests = len(expecteds)
            if incorrect == 0:
                print '\033[1;32m\033[1;1mpass\033[0m ' + relpath + ' (' + str(total_tests - incorrect) + '/' + str(total_tests) + ')'
            else:
                print '\033[1;31m\033[1;1mfail\033[0m ' + relpath + ' (' + str(total_tests - incorrect) + '/' + str(total_tests) + ')'

            all_tests += total_tests
            all_failures += incorrect

    print 'Tests complete, ' + str(all_failures) + ' failures'
    print 'i.e. ' + str(all_tests - all_failures) + ' of ' + str(all_tests) + ' tests passed.'

    if (not '-e' in sys.argv):
        print "(to run more expensive tests use the '-e' option)"

    if all_failures > 0:
        sys.exit(1);


if __name__ == '__main__':
    main()
